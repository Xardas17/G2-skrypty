unit DecompDXTC;

{*******************************************************}
{                                                       }
{       S3TC/DXTC texture decompression                 }
{                                                       }
{       Copyright (c) 2001, Nico Bendlin                }
{                                                       }
{ ToDo:                                                 }
{    DXT4 and DXT5 currently not implemented            }
{                                                       }
{*******************************************************}

{$ALIGN ON}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface

uses
  Windows;

type
  PTextureFormatS3TC = ^TTextureFormatS3TC;
  TTextureFormatS3TC = (
    tfs3tcUnknown,
    tfs3tcDXT1,
    tfs3tcDXT1A,
    tfs3tcDXT2,
    tfs3tcDXT3,
    tfs3tcDXT4,
    tfs3tcDXT5
  );

{ Decompresses an S3TC/DXCT texture into an buffer as 24/32-bit RGB(A).
  Width and Height are the dimensions in pixels/texels of the texture.
  RGB color values are not corrected on DXT2 or DXT4 (premultiplied).
  On error use GetLastError for details. }
function DXTCDecompress(Width, Height: ULONG; DXTCFormat: TTextureFormatS3TC;
  DXTCData, Buffer: Pointer; BufferSize: ULONG): BOOL; stdcall;

{ Caculates the size in bytes of an S3TC/DXCT compressed mipmap.
  MipMap is 0 indexed.
  Width and Height are the dimensions in pixels of the texture (mipmap 0).
  On error 0 is returned--use GetLastError for details. }
function DXTCMipMapSize(Width, Height: ULONG; DXTCFormat: TTextureFormatS3TC;
  MipMap: Word): ULONG; stdcall;

{ Caculates the needed size in bytes for decompressing an S3TC/DXCT mipmap.
  MipMap is 0 indexed.
  Width and Height are the dimensions in pixels of the texture (mipmap 0).
  On error 0 is returned--use GetLastError for details. }
function DXTCBufferSize(Width, Height: ULONG; DXTCFormat: TTextureFormatS3TC;
  MipMap: Word): ULONG; stdcall;

implementation

type
  PDXTColorBlock = ^TDXTColorBlock;
  TDXTColorBlock = packed record
    Color0: Word;
    Color1: Word;
    Rows  : array [0..3] of Byte;
  end;

type
  PDXTAlphaBlockExplicit = ^TDXTAlphaBlockExplicit;
  TDXTAlphaBlockExplicit = record
    Rows: array [0..3] of Word;
  end;

type
  PColor565 = ^TColor565;
  TColor565 = Word;

const
  Color565Red   = TColor565($001F);
  Color565Green = TColor565($07E0);
  Color565Blue  = TColor565($F800);

type
  PColor888 = ^TColor888;
  TColor888 = packed record
    Red  : Byte;
    Green: Byte;
    Blue : Byte;
  end;

type
  PColor8888 = ^TColor8888;
  TColor8888 = packed record
    Red  : Byte;
    Green: Byte;
    Blue : Byte;
    Alpha: Byte;
  end;

{------------------------------------------------------------------------------}

procedure GetColorBlockColors(ColorBlock: PDXTColorBlock;
  out Color0, Color1, Color2, Color3: TColor8888; DXT1: Boolean);
var
	Color: PColor565;
begin
	Color := PColor565(@ColorBlock.Color0);
  Color0.Red := (Color^ and Color565Red) shl 3;
	Color0.Green := (Color^ and Color565Green) shr 3;
	Color0.Blue := (Color^ and Color565Blue) shr 8;
	Color0.Alpha := $FF;
	Color := PColor565(@ColorBlock.Color1);
  Color1.Red := (Color^ and Color565Red) shl 3;
	Color1.Green := (Color^ and Color565Green) shr 3;
	Color1.Blue := (Color^ and Color565Blue) shr 8;
	Color1.Alpha := $FF;
	if (not DXT1) or (ColorBlock.Color0 > ColorBlock.Color1) then
  begin
		Color2.Red := Byte((Word(Color0.Red) * 2 + Word(Color1.Red)) div 3);
		Color2.Green := Byte((Word(Color0.Green) * 2 + Word(Color1.Green)) div 3);
		Color2.Blue := Byte((Word(Color0.Blue) * 2 + Word(Color1.Blue)) div 3);
		Color2.Alpha := $FF;
		Color3.Red := Byte((Word(Color0.Red) + Word(Color1.Red) * 2) div 3);
		Color3.Green := Byte((Word(Color0.Green) + Word(Color1.Green) * 2) div 3);
		Color3.Blue := Byte((Word(Color0.Blue) + Word(Color1.Blue) * 2) div 3);
		Color3.Alpha := $FF;
  end
  else
  begin
		Color2.Red := Byte((Word(Color0.Red) + Word(Color1.Red)) div 2);
		Color2.Green := Byte((Word(Color0.Green) + Word(Color1.Green)) div 2);
		Color2.Blue := Byte((Word(Color0.Blue) + Word(Color1.Blue)) div 2);
		Color2.Alpha := $FF;
		Color3.Red := $00;
		Color3.Green := $00;
		Color3.Blue := $00;
		Color3.Alpha := $00;
  end;
end;

procedure DecodeColorBlock24(ImagePos: PColor888; ColorBlock: PDXTColorBlock;
  BlockWidthUsed, BlockHeightUsed: Byte; MapWidth: ULONG;
  const Color0, Color1, Color2, Color3: TColor8888);
const
	Masks: array [0..3] of ULONG = (3, 12, 3 shl 4, 3 shl 6);
	Shift: array [0..3] of Integer = (0, 2, 4, 6);
var
  Row: Byte;
  Texel: Byte;
begin
  for Row := 0 to BlockHeightUsed - 1 do
  begin
    for Texel := 0 to BlockWidthUsed - 1 do
    begin
			case (ColorBlock.Rows[Row] and Masks[Texel]) shr Shift[Texel] of
        0: ImagePos^ := PColor888(@Color0)^;
        1: ImagePos^ := PColor888(@Color1)^;
        2: ImagePos^ := PColor888(@Color2)^;
        3: ImagePos^ := PColor888(@Color3)^;
      end;
      Inc(ImagePos);
    end;
    Inc(ImagePos, Integer(MapWidth - BlockWidthUsed));
  end;
end;

procedure DecodeColorBlock32(ImagePos: PULONG; ColorBlock: PDXTColorBlock;
  BlockWidthUsed, BlockHeightUsed: Byte; MapWidth: ULONG;
  const Color0, Color1, Color2, Color3: TColor8888);
const
	Masks: array [0..3] of ULONG = (3, 12, 3 shl 4, 3 shl 6);
	Shift: array [0..3] of Integer = (0, 2, 4, 6);
var
  Row: Byte;
  Num: Byte;
begin
  for Row := 0 to BlockHeightUsed - 1 do
  begin
    for Num := 0 to BlockWidthUsed - 1 do
    begin
			case (ColorBlock.Rows[Row] and Masks[Num]) shr Shift[Num] of
        0: ImagePos^ := PULONG(@Color0)^;
        1: ImagePos^ := PULONG(@Color1)^;
        2: ImagePos^ := PULONG(@Color2)^;
        3: ImagePos^ := PULONG(@Color3)^;
      end;
      Inc(ImagePos);
    end;
    Inc(ImagePos, Integer(MapWidth - BlockWidthUsed));
  end;
end;

procedure DecodeAlphaExplicit(ImagePos: PULONG;
 AlphaBlock: PDXTAlphaBlockExplicit; BlockWidthUsed, BlockHeightUsed: Byte;
 MapWidth, AlphaZero: ULONG);
var
  Row: Byte;
  Pixel: Byte;
  Mask: Word;
  Color: TColor8888;
begin
  Color.Blue := 0;
  Color.Green := Color.Blue;
  Color.Red := Color.Green;
	for Row := 0 to BlockHeightUsed - 1 do
  begin
		Mask := AlphaBlock.Rows[Row];
		for Pixel := 0 to BlockWidthUsed - 1 do
    begin
			ImagePos^ := ImagePos^ and AlphaZero;
      Color.Alpha := Mask and $000F;
      Color.Alpha := Color.Alpha or (Color.Alpha shl 4);
      ImagePos^ := ImagePos^ or PULONG(@Color)^;
			Mask := Mask shr 4;
			Inc(ImagePos);
    end;
    Inc(ImagePos, Integer(MapWidth - BlockWidthUsed));
  end;
end;

{------------------------------------------------------------------------------}


function DecompressDXT1(Width, Height: ULONG; DXTCData, Buffer: Pointer;
  BufferSize: ULONG): Boolean;
var
  BlocksX: ULONG;
  BlocksY: ULONG;
  Row: ULONG;
	Texel: ULONG;
	ImagePos: PColor888;
  ColorBlock: PDXTColorBlock;
	Color0: TColor8888;
  Color1: TColor8888;
  Color2: TColor8888;
  Color3: TColor8888;
  LastBlockWidth: Byte;
  LastBlockHeight: Byte;
begin
  Result := False;
  if (Width = 0) or (Height = 0) or (DXTCData = nil) or (Buffer = nil) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if BufferSize < Width * Height * SizeOf(TColor888) then
    SetLastError(ERROR_INSUFFICIENT_BUFFER)
  else
  begin
    LastBlockWidth := Width mod 4;
    if LastBlockWidth = 0 then
      LastBlockWidth := 4;
    LastBlockHeight := Height mod 4;
    if LastBlockHeight = 0 then
      LastBlockHeight := 4;
    BlocksX := (Width - 1) div 4 + 1;
    BlocksY := (Height - 1) div 4 + 1;
    for Row := 0 to BlocksY - 1 do
    begin
      ColorBlock := PDXTColorBlock(ULONG(DXTCData) + ULONG(Row * BlocksX * 8));
      for Texel := 0 to BlocksX - 1 do
      begin
        GetColorBlockColors(ColorBlock, Color0, Color1, Color2, Color3, True);
        ImagePos := PColor888(ULONG(Buffer) + ULONG(Texel * 12) +
          ULONG(Row * 4) * Width * SizeOf(TColor888));
        if (Row < BlocksY - 1) and (Texel < BlocksX - 1) then
          DecodeColorBlock24(ImagePos, ColorBlock, 4, 4, Width, Color0, Color1,
            Color2, Color3)
        else
          DecodeColorBlock24(ImagePos, ColorBlock, LastBlockWidth,
            LastBlockHeight, Width, Color0, Color1, Color2, Color3);
        Inc(ColorBlock);
      end;
    end;
    Result := True;
  end;
end;

function DecompressDXT1A(Width, Height: ULONG; DXTCData, Buffer: Pointer;
  BufferSize: ULONG): Boolean;
var
  BlocksX: ULONG;
  BlocksY: ULONG;
  Row: ULONG;
	Texel: ULONG;
	ImagePos: PULONG;
  ColorBlock: PDXTColorBlock;
	Color0: TColor8888;
  Color1: TColor8888;
  Color2: TColor8888;
  Color3: TColor8888;
  LastBlockWidth: Byte;
  LastBlockHeight: Byte;
begin
  Result := False;
  if (Width = 0) or (Height = 0) or (DXTCData = nil) or (Buffer = nil) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if BufferSize < Width * Height * SizeOf(TColor8888) then
    SetLastError(ERROR_INSUFFICIENT_BUFFER)
  else
  begin
    LastBlockWidth := Width mod 4;
    if LastBlockWidth = 0 then
      LastBlockWidth := 4;
    LastBlockHeight := Height mod 4;
    if LastBlockHeight = 0 then
      LastBlockHeight := 4;
    BlocksX := (Width - 1) div 4 + 1;
    BlocksY := (Height - 1) div 4 + 1;
    for Row := 0 to BlocksY - 1 do
    begin
      ColorBlock := PDXTColorBlock(ULONG(DXTCData) + ULONG(Row * BlocksX * 8));
      for Texel := 0 to BlocksX - 1 do
      begin
        GetColorBlockColors(ColorBlock, Color0, Color1, Color2, Color3, True);
        ImagePos := PULONG(ULONG(Buffer) + ULONG(Texel * 16) +
          ULONG(Row * 4) * Width * SizeOf(TColor8888));
        if (Row < BlocksY - 1) and (Texel < BlocksX - 1) then
          DecodeColorBlock32(ImagePos, ColorBlock, 4, 4, Width, Color0, Color1,
            Color2, Color3)
        else
          DecodeColorBlock32(ImagePos, ColorBlock, LastBlockWidth,
            LastBlockHeight, Width, Color0, Color1, Color2, Color3);
        Inc(ColorBlock);
      end;
    end;
    Result := True;
  end;
end;

function DecompressDXT3(Width, Height: ULONG; DXTCData, Buffer: Pointer;
  BufferSize: ULONG): Boolean;
var
  BlocksX: ULONG;
  BlocksY: ULONG;
  Row: ULONG;
	Texel: ULONG;
	ImagePos: PULONG;
  ColorBlock: PDXTColorBlock;
	AlphaBlock: PDXTAlphaBlockExplicit;
	Color0: TColor8888;
  Color1: TColor8888;
  Color2: TColor8888;
  Color3: TColor8888;
  AlphaZero: ULONG;
  LastBlockWidth: Byte;
  LastBlockHeight: Byte;
begin
  Result := False;
  if (Width = 0) or (Height = 0) or (DXTCData = nil) or (Buffer = nil) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if BufferSize < Width * Height * SizeOf(ULONG) then
    SetLastError(ERROR_INSUFFICIENT_BUFFER)
  else
  begin
    Color0.Alpha := 0;
    Color0.Blue := $FF;
    Color0.Green := Color0.Blue;
    Color0.Red := Color0.Green;
    AlphaZero := PULONG(@Color0)^;
    LastBlockWidth := Width mod 4;
    if LastBlockWidth = 0 then
      LastBlockWidth := 4;
    LastBlockHeight := Height mod 4;
    if LastBlockHeight = 0 then
      LastBlockHeight := 4;
    BlocksX := (Width - 1) div 4 + 1;
    BlocksY := (Height - 1) div 4 + 1;
    for Row := 0 to BlocksY - 1 do
    begin
      ColorBlock := PDXTColorBlock(ULONG(DXTCData) + ULONG(Row * BlocksX * 16));
      for Texel := 0 to BlocksX - 1 do
      begin
        AlphaBlock := PDXTAlphaBlockExplicit(ColorBlock);
        Inc(ColorBlock);
        GetColorBlockColors(ColorBlock, Color0, Color1, Color2, Color3, False);
        ImagePos := PULONG(ULONG(Buffer) + ULONG(Texel * 16) +
          ULONG(Row * 4) * Width * SizeOf(TColor8888));
        if (Row < BlocksY - 1) and (Texel < BlocksX - 1) then
        begin
          DecodeColorBlock32(ImagePos, ColorBlock, 4, 4, Width, Color0, Color1,
            Color2, Color3);
          DecodeAlphaExplicit(ImagePos, AlphaBlock, 4, 4, Width, AlphaZero);
        end
        else
        begin
          DecodeColorBlock32(ImagePos, ColorBlock, LastBlockWidth,
            LastBlockHeight, Width, Color0, Color1, Color2, Color3);
          DecodeAlphaExplicit(ImagePos, AlphaBlock, LastBlockWidth,
            LastBlockHeight, Width, AlphaZero);
        end;
        Inc(ColorBlock);
      end;
    end;
    Result := True;
  end;
end;

function DecompressDXT5(Width, Height: ULONG; DXTCData, Buffer: Pointer;
  BufferSize: ULONG): Boolean;
begin
  Result := False;
  // todo
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
end;

function DXTCDecompress(Width, Height: ULONG; DXTCFormat: TTextureFormatS3TC;
  DXTCData, Buffer: Pointer; BufferSize: ULONG): BOOL; stdcall;
begin
  Result := False;
  if (Width = 0) or (Height = 0) or (DXTCData = nil) or (Buffer = nil) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else
  begin
    case DXTCFormat of
      tfs3tcDXT1:
        Result := DecompressDXT1(Width, Height, DXTCData, Buffer, BufferSize);
      tfs3tcDXT1A:
        Result := DecompressDXT1A(Width, Height, DXTCData, Buffer, BufferSize);
      tfs3tcDXT2,
      tfs3tcDXT3:
        Result := DecompressDXT3(Width, Height, DXTCData, Buffer, BufferSize);
      tfs3tcDXT4,
      tfs3tcDXT5:
        Result := DecompressDXT5(Width, Height, DXTCData, Buffer, BufferSize);
    else
      SetLastError(ERROR_INVALID_PIXEL_FORMAT);
    end;
  end;
end;

function DXTCMipMapSize(Width, Height: ULONG; DXTCFormat: TTextureFormatS3TC;
  MipMap: Word): ULONG; stdcall;
var
  MapX: ULONG;
  MapY: ULONG;
  BlocksX: ULONG;
  BlocksY: ULONG;
begin
  Result := 0;
  MapX := Width shr MipMap;
  MapY := Height shr MipMap;
  if (Width = 0) or (Height = 0) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if (MapX shl MipMap <> Width) or (MapY shl MipMap <> Height) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else
  begin
    BlocksX := (MapX - 1) div 4 + 1;
    BlocksY := (MapY - 1) div 4 + 1;
    case DXTCFormat of
      tfs3tcDXT1,
      tfs3tcDXT1A:
        Result := BlocksX * BlocksY * SizeOf(TDXTColorBlock);
      tfs3tcDXT2,
      tfs3tcDXT3,
      tfs3tcDXT4,
      tfs3tcDXT5:
        Result := BlocksX * BlocksY * 2 * SizeOf(TDXTColorBlock);
    else
      SetLastError(ERROR_INVALID_PIXEL_FORMAT);
    end;
  end;
end;

function DXTCBufferSize(Width, Height: ULONG; DXTCFormat: TTextureFormatS3TC;
  MipMap: Word): ULONG; stdcall;
var
  MapX: ULONG;
  MapY: ULONG;
begin
  Result := 0;
  MapX := Width shr MipMap;
  MapY := Height shr MipMap;
  if (Width = 0) or (Height = 0) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if (MapX shl MipMap <> Width) or (MapY shl MipMap <> Height) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else
  begin
    case DXTCFormat of
      tfs3tcDXT1:
        Result := MapX * MapY * SizeOf(TColor888);
      tfs3tcDXT1A,
      tfs3tcDXT2,
      tfs3tcDXT3,
      tfs3tcDXT4,
      tfs3tcDXT5:
        Result := MapX * MapY * SizeOf(TColor8888);
    else
      SetLastError(ERROR_INVALID_PIXEL_FORMAT);
    end;
  end;
end;

end.

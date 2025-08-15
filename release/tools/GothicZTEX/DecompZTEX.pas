unit DecompZTEX;

{*******************************************************}
{                                                       }
{       ZenGin TEXture (ZTEX) decompression             }
{                                                       }
{       Copyright (c) 2001, Nico Bendlin                }
{                                                       }
{*******************************************************}

{$ALIGN ON}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface

uses
  Windows, ZTEX, DecompDXTC;

{ Decompresses an ZTEX texture into an buffer as 24/32-bit RGB(A).
  Width and Height are the dimensions in pixels/texels of the texture.
  On error use GetLastError for details. }
function ZTEXDecompress(Header: TZTEXFileHeader; Data, Buffer: Pointer;
  BufferSize: ULONG): BOOL; stdcall;

{ Caculates the size in bytes of an ZTEX compressed mipmap.
  MipMap is 0 indexed.
  Width and Height are the dimensions in pixels of the texture (mipmap 0).
  On error 0 is returned--use GetLastError for details. }
function ZTEXMipMapSize(Header: TZTEXFileHeader; MipMap: Word): ULONG; stdcall;

{ Caculates the needed size in bytes for decompressing an ZTEX mipmap.
  MipMap is 0 indexed.
  Width and Height are the dimensions in pixels of the texture (mipmap 0).
  On error 0 is returned--use GetLastError for details. }
function ZTEXBufferSize(Header: TZTEXFileHeader; MipMap: Word): ULONG; stdcall;

{ Get the pixel depth (24/32) of decompressed data.
  On error 0 is returned--use GetLastError for details. }
function ZTEXPixelDepth(Header: TZTEXFileHeader): Byte; stdcall;

implementation

type
  PColor4444 = ^TColor4444;
  TColor4444 = Word;

const
  Color4444Red   = TColor4444($000F);
  Color4444Green = TColor4444($00F0);
  Color4444Blue  = TColor4444($0F00);
  Color4444Alpha = TColor4444($F000);

type
  PColor1555 = ^TColor1555;
  TColor1555 = Word;

const
  Color1555Red   = TColor1555($001F);
  Color1555Green = TColor1555($03E0);
  Color1555Blue  = TColor1555($7C00);
  Color1555Alpha = TColor1555($8000);

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

function ZTexCodeToDXTCFormat(ZTEXFormat: ULONG): TTextureFormatS3TC;
begin
  case ZTEXFormat of
    ZTEX_TF_DXT1:
      Result := tfs3tcDXT1;
    ZTEX_TF_DXT1A:
      Result := tfs3tcDXT1A;
    ZTEX_TF_DXT3:
      Result := tfs3tcDXT3;
    ZTEX_TF_DXT5:
      Result := tfs3tcDXT5;
  else
    Result := tfs3tcUnknown;
  end;
end;

{------------------------------------------------------------------------------}

function Decompress4444(Width, Height: ULONG; Data, Buffer: Pointer;
  BufferSize: ULONG): Boolean;
var
  Row: ULONG;
  Texel: ULONG;
  TexPos: PColor4444;
  ImagePos: PColor8888;
begin
  Result := False;
  if (Width = 0) or (Height = 0) or (Data = nil) or (Buffer = nil) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if BufferSize < Width * Height * SizeOf(TColor8888) then
    SetLastError(ERROR_INSUFFICIENT_BUFFER)
  else
  begin
    TexPos := Data;
    ImagePos := Buffer;
    for Row := 0 to Height - 1 do
    begin
      for Texel := 0 to Width - 1 do
      begin
        ImagePos^.Red := (TexPos^ and Color4444Red) * 17;
        ImagePos^.Green := (TexPos^ and Color4444Green) shr 4 * 17;
        ImagePos^.Blue := (TexPos^ and Color4444Blue) shr 8  * 17;
        ImagePos^.Alpha := (TexPos^ and Color4444Alpha) shr 12  * 17;
        Inc(TexPos);
        Inc(ImagePos);
      end;
    end;
    Result := True;
  end;
end;

function Decompress1555(Width, Height: ULONG; Data, Buffer: Pointer;
  BufferSize: ULONG): Boolean;
var
  Row: ULONG;
  Texel: ULONG;
  TexPos: PColor1555;
  ImagePos: PColor8888;
begin
  Result := False;
  if (Width = 0) or (Height = 0) or (Data = nil) or (Buffer = nil) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if BufferSize < Width * Height * SizeOf(TColor8888) then
    SetLastError(ERROR_INSUFFICIENT_BUFFER)
  else
  begin
    TexPos := Data;
    ImagePos := Buffer;
    for Row := 0 to Height - 1 do
    begin
      for Texel := 0 to Width - 1 do
      begin
        ImagePos^.Red := (TexPos^ and Color1555Red) shl 3;
        ImagePos^.Green := (TexPos^ and Color1555Green) shr 2;
        ImagePos^.Blue := (TexPos^ and Color1555Blue) shr 7;
        if SmallInt(TexPos^) < 0 then
          ImagePos^.Alpha := $FF
        else
          ImagePos^.Alpha := $00;
        Inc(TexPos);
        Inc(ImagePos);
      end;
    end;
    Result := True;
  end;
end;

function Decompress565(Width, Height: ULONG; Data, Buffer: Pointer;
  BufferSize: ULONG): Boolean;
var
  Row: ULONG;
  Texel: ULONG;
  TexPos: PColor565;
  ImagePos: PColor888;
begin
  Result := False;
  if (Width = 0) or (Height = 0) or (Data = nil) or (Buffer = nil) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if BufferSize < Width * Height * SizeOf(TColor888) then
    SetLastError(ERROR_INSUFFICIENT_BUFFER)
  else
  begin
    TexPos := Data;
    ImagePos := Buffer;
    for Row := 0 to Height - 1 do
    begin
      for Texel := 0 to Width - 1 do
      begin
        ImagePos^.Red := (TexPos^ and Color565Red) shl 3;
        ImagePos^.Green := (TexPos^ and Color565Green) shr 3;
        ImagePos^.Blue := (TexPos^ and Color565Blue) shr 8;
        Inc(TexPos);
        Inc(ImagePos);
      end;
    end;
    Result := True;
  end;
end;

function Decompress8888(Width, Height: ULONG; Data, Buffer: Pointer;
  BufferSize: ULONG): Boolean;
begin
  Result := False;
  if (Width = 0) or (Height = 0) or (Data = nil) or (Buffer = nil) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else if BufferSize < Width * Height * SizeOf(TColor8888) then
    SetLastError(ERROR_INSUFFICIENT_BUFFER)
  else
  begin
    CopyMemory(Buffer, Data, Width * Height * 4);
    Result := True;
  end;
end;

{------------------------------------------------------------------------------}

function ZTEXDecompress(Header: TZTEXFileHeader; Data, Buffer: Pointer;
  BufferSize: ULONG): BOOL; stdcall;
begin
  Result := False;
  if (Data <> nil) and (Buffer <> nil) then
  begin
    with Header do
    case Format of
      ZTEX_TF_RGB4444:
        Result := Decompress4444(Width, Height, Data, Buffer, BufferSize);
      ZTEX_TF_RGB1555:
        Result := Decompress1555(Width, Height, Data, Buffer, BufferSize);
      ZTEX_TF_RGB565:
        Result := Decompress565(Width, Height, Data, Buffer, BufferSize);
      ZTEX_TF_RGB8888:
        Result := Decompress8888(Width, Height, Data, Buffer, BufferSize);
      ZTEX_TF_DXT1,
      ZTEX_TF_DXT1A,
      ZTEX_TF_DXT3,
      ZTEX_TF_DXT5:
        Result := DXTCDecompress(Width, Height, ZTexCodeToDXTCFormat(Format),
          Data, Buffer, BufferSize);
    else
      SetLastError(ERROR_INVALID_PARAMETER);
    end;
  end;
end;

function ZTEXMipMapSize(Header: TZTEXFileHeader; MipMap: Word): ULONG; stdcall;
var
  MapX: ULONG;
  MapY: ULONG;
begin
  Result := 0;
  with Header do
  begin
    MapX := Width shr MipMap;
    MapY := Height shr MipMap;
    if (Width = 0) or (Height = 0) then
      SetLastError(ERROR_INVALID_PARAMETER)
    else if (MapX shl MipMap <> Width) or (MapY shl MipMap <> Height) then
      SetLastError(ERROR_INVALID_PARAMETER)
    else
    begin
      case Format of
        ZTEX_TF_RGB4444,
        ZTEX_TF_RGB1555,
        ZTEX_TF_RGB565:
          Result := MapX * MapY * 2;
        ZTEX_TF_RGB8888:
          Result := MapX * MapY * 4;
        ZTEX_TF_DXT1,
        ZTEX_TF_DXT1A,
        ZTEX_TF_DXT3,
        ZTEX_TF_DXT5:
          Result := DXTCMipMapSize(Width, Height, ZTexCodeToDXTCFormat(Format),
            MipMap);
      else
        SetLastError(ERROR_INVALID_PARAMETER);
      end;
    end;
  end;
end;

function ZTEXBufferSize(Header: TZTEXFileHeader; MipMap: Word): ULONG; stdcall;
var
  MapX: ULONG;
  MapY: ULONG;
begin
  Result := 0;
  with Header do
  begin
    MapX := Width shr MipMap;
    MapY := Height shr MipMap;
    if (Width = 0) or (Height = 0) then
      SetLastError(ERROR_INVALID_PARAMETER)
    else if (MapX shl MipMap <> Width) or (MapY shl MipMap <> Height) then
      SetLastError(ERROR_INVALID_PARAMETER)
    else
    begin
      case Format of
        ZTEX_TF_RGB565:
          Result := MapX * MapY * 3;
        ZTEX_TF_RGB4444,
        ZTEX_TF_RGB1555,
        ZTEX_TF_RGB8888:
          Result := MapX * MapY * 4;
        ZTEX_TF_DXT1,
        ZTEX_TF_DXT1A,
        ZTEX_TF_DXT3,
        ZTEX_TF_DXT5:
          Result := DXTCBufferSize(Width, Height, ZTexCodeToDXTCFormat(Format),
            MipMap);
      else
        SetLastError(ERROR_INVALID_PIXEL_FORMAT);
      end;
    end;
  end;
end;

function ZTEXPixelDepth(Header: TZTEXFileHeader): Byte; stdcall;
begin
  Result := 0;
  with Header do
    case Format of
      ZTEX_TF_RGB565,
      ZTEX_TF_DXT1:
        Result := 24;
      ZTEX_TF_RGB4444,
      ZTEX_TF_RGB1555,
      ZTEX_TF_RGB8888,
      ZTEX_TF_DXT1A,
      ZTEX_TF_DXT3,
      ZTEX_TF_DXT5:
        Result := 32;
    else
      SetLastError(ERROR_INVALID_PIXEL_FORMAT);
    end;
end;

end.

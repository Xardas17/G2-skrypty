unit GothicZtexUtil;

interface

uses
  Windows, Messages, CommCtrl, ShlObj, ActiveX,
  GothicZtexGlob,
  ZTEX, DecompZTEX;

function ZTexToTga(ZTEXFile, TGAFile: THandle): Boolean;

function FileExists(Filename: PChar): Boolean;
function FileIsEqual(Filename: PChar): Boolean;
procedure AppendBackSlash(Path: PChar);
procedure MakeFullPath(Root, Path, Name: PChar; Buffer: PChar);
procedure IntToStrGrp(Value: ULONG; Buffer: PChar);

type
  PTraceType = ^TTraceType;
  TTraceType = (
    ttText,
    ttNumber,
    ttProcessed,
    ttSkipped,
    ttError
  );

var
  FilesProcessed: ULONG;
  FilesSkipped: ULONG;
  FilesError: ULONG;

procedure ResetCounter;
procedure Trace(Dlg: HWND; Reason: TTraceType; Text: PChar);
procedure ProcessMessages(Dlg: HWND);
procedure EnableDlgItem(Dlg: HWND; Item: Integer; Enable: Boolean);
procedure SetStatusText(Dlg: HWND; Text: PChar);

function InitFileList: Boolean;
procedure FreeFileList;
procedure MakeFullPathFromList(Root, Path, Name: PChar; Buffer: PChar);

function SelectDirectory(Wnd: HWND; Path, Title, Select: PChar): Boolean;

procedure InitProgress(Dlg: HWND; MaxRange: Integer);
procedure IncProgress(Dlg: HWND; Increment: Integer = 1);

function MakeSureDirectoryPathExists(DirPath: LPCSTR): BOOL; stdcall;

implementation

type
  PPathList = ^TPathList;
  TPathList = record
    Count: Integer;
    Paths: array [0..0] of PChar;
  end;

  PFileListEntry = ^TFileListEntry;
  TFileListEntry = record
    Path: Integer;
    Name: PChar;
  end;

  PFileList = ^TFileList;
  TFileList = record
    Count: Integer;
    Files: array [0..0] of TFileListEntry;
  end;

var
  PathList: PPathList = nil;
  FileList: PFileList = nil;

function InitFileList: Boolean;
const
  BufferSize = 32 * 1024 - 1;
var
  IniName: array [0..MAX_PATH] of Char;
  SecBuff: Pointer;
  Section: PChar;
  LstBuff: Pointer;
  LstLine: PChar;
begin
  Result := False;
  GetModuleFileName(0, IniName, SizeOf(IniName));
  lstrcpy(@IniName[lstrlen(IniName) - 4], '.ini');
  SecBuff := GetMemory(BufferSize);
  LstBuff := GetMemory(BufferSize);
  PathList := GetMemory(SizeOf(TPathList));
  FileList := GetMemory(SizeOf(TFileList));
  if (SecBuff <> nil) and (LstBuff <> nil) and
    (PathList <> nil) and (FileList <> nil) then
  begin
    PathList.Count := 0;
    FileList.Count := 0;
    if GetPrivateProfileSectionNames(SecBuff, BufferSize, IniName) > 0 then
    begin
      Result := True;
      Section := SecBuff;
      repeat
        Inc(PathList.Count);
        PathList := ReallocMemory(PathList,
          PathList.Count * SizeOf(PChar) + SizeOf(Integer));
        if PathList = nil then
        begin
          Result := False;
          Break;
        end;
        PathList.Paths[PathList.Count - 1] := GetMemory(lstrlen(Section) + 1);
        if PathList.Paths[PathList.Count - 1] = nil then
        begin
          Result := False;
          Break;
        end;
        lstrcpy(PathList.Paths[PathList.Count - 1], Section);
        if GetPrivateProfileSection(Section, LstBuff, BufferSize, IniName) > 0 then
        begin
          LstLine := LstBuff;
          repeat
            Inc(FileList.Count);
            FileList := ReallocMemory(FileList,
              FileList.Count * SizeOf(TFileListEntry) + SizeOf(Integer));
            if FileList = nil then
            begin
              Result := False;
              Break;
            end;
            FileList.Files[FileList.Count - 1].Path := PathList.Count - 1;
            FileList.Files[FileList.Count - 1].Name := GetMemory(lstrlen(LstLine) + 1);
            if FileList.Files[FileList.Count - 1].Name = nil then
            begin
              Result := False;
              Break;
            end;
            lstrcpy(FileList.Files[FileList.Count - 1].Name, LstLine);
            LstLine := PChar(@LstLine[lstrlen(LstLine) + 1]);
          until LstLine[0] = #0;
        end;
        if not Result then
          Break;
        Section := PChar(@Section[lstrlen(Section) + 1]);
      until Section[0] = #0;
    end;
  end;
  if SecBuff <> nil then
    FreeMemory(SecBuff);
  if LstBuff <> nil then
    FreeMemory(LstBuff);
  if not Result then
    FreeFileList;
end;

procedure FreeFileList;
var
  Loop: Integer;
begin
  if FileList <> nil then
  begin
    for Loop := 0 to FileList.Count - 1 do
      if FileList.Files[Loop].Name <> nil then
      begin
        FreeMemory(FileList.Files[Loop].Name);
        FileList.Files[Loop].Name := nil;
      end;
    FreeMemory(FileList);
    FileList := nil;
  end;
  if PathList <> nil then
  begin
    for Loop := 0 to PathList.Count - 1 do
      if PathList.Paths[Loop] <> nil then
      begin
        FreeMemory(PathList.Paths[Loop]);
        PathList.Paths[Loop] := nil;
      end;
    FreeMemory(PathList);
    PathList := nil;
  end;
end;

var
  LastIndex: Integer = 0;

procedure MakeFullPathFromList(Root, Path, Name: PChar; Buffer: PChar);
var
  TRoot: array [0..MAX_PATH] of Char;
  Index: Integer;
  Loop: Integer;
begin
  Index := -1;
  if (Name <> nil) and
    (FileList <> nil) and (PathList <> nil) and
    (FileList.Count > 0) and (PathList.Count > 0) then
  begin
    if (LastIndex < FileList.Count - 1) and
      (lstrcmpi(FileList.Files[LastIndex + 1].Name, Name) = 0) then
      Index := LastIndex + 1
    else for Loop := 0 to FileList.Count - 1 do
      if lstrcmpi(FileList.Files[Loop].Name, Name) = 0 then
      begin
        Index := Loop;
        Break;
      end;
  end;
  if Index >= 0 then
  begin
    MakeFullPath(Root, Path, nil, TRoot);
    MakeFullPath(TRoot, PathList.Paths[FileList.Files[Index].Path],
      FileList.Files[Index].Name, Buffer);
    LastIndex := Index;
  end
  else
    MakeFullPath(Root, Path, Name, Buffer);
end;

{------------------------------------------------------------------------------}

function SwapImageVertikal(Rows, Size: ULONG; Data: Pointer): Boolean;
var
  Width: ULONG;
  Line: Pointer;
  Row: ULONG;
  Top: Pointer;
  Bottom: Pointer;
begin
  Result := False;
  if (Rows = 0) or (Size = 0) then
    SetLastError(ERROR_INVALID_PARAMETER)
  else
  begin
    Width := Size div Rows;
    Line := GetMemory(Width);
    if Width * Rows <> Size then
      SetLastError(ERROR_INVALID_PARAMETER)
    else if Line = nil then
      SetLastError(ERROR_NOT_ENOUGH_MEMORY)
    else
    begin
      Top := Data;
      Bottom := Pointer(ULONG(Data) + Size - Width);
      for Row := 1 to Rows div 2 do
      begin
        CopyMemory(Line, Top, Width);
        CopyMemory(Top, Bottom, Width);
        CopyMemory(Bottom, Line, Width);
        Top := Pointer(ULONG(Top) + Width);
        Bottom := Pointer(ULONG(Bottom) - Width);
      end;
      Result := True;
    end;
    if Line <> nil then
      FreeMemory(Line);
  end;
end;

type
  PTGAFileHeader = ^TTGAFileHeader;
  TTGAFileHeader = packed record
    IdLength   : Byte;
    MapType    : Byte;
    ImageType  : Byte;
    MapOrigin  : Word;
    MapLength  : Word;
    MapWidth   : Byte;
    OriginX    : Word;
    OriginY    : Word;
    ImageWidth : Word;
    ImageHeight: Word;
    PixelDepth : Byte;
    ImageDesc  : Byte;
  end;

type
  PTGAFileFooter = ^TTGAFileFooter;
  TTGAFileFooter = packed record
    ExtAreaOffset: ULONG;
    DevDirOffset : ULONG;
    Signature    : array [0..17] of Char;
  end;

const
  TGAFileFooterSignatur = 'TRUEVISION-XFILE.';

function FileExists(Filename: PChar): Boolean;
var
  FileHandle: THandle;
begin
  Result := False;
  FileHandle := CreateFile(Filename, 0, FILE_SHARE_READ or FILE_SHARE_WRITE,
    nil, OPEN_EXISTING, 0, 0);
  if FileHandle <> INVALID_HANDLE_VALUE then
  begin
    Result := True;
    CloseHandle(FileHandle);
  end;
end;

function FileIsEqual(Filename: PChar): Boolean;
var
  FindFile: THandle;
  FindData: TWin32FindData;
begin
  Result := False;
  FindFile := FindFirstFile(Filename, FindData);
  if FindFile <> INVALID_HANDLE_VALUE then
  begin
    Result := lstrcmp(FindData.cFileName,
      PChar(@Filename[lstrlen(Filename) - lstrlen(FindData.cFileName)])) = 0;
    FindClose(FindFile);
  end;
end;

function ZTexToTga(ZTEXFile, TGAFile: THandle): Boolean;
var
  ZTEXHead: TZTEXFileHeader;
  ZTEXSize: ULONG;
  ZTEXData: Pointer;
  TGAHead: TTGAFileHeader;
  TGAFoot: TTGAFileFooter;
  TGASize: ULONG;
  TGAData: Pointer;
  Written: ULONG;
  Skipped: Boolean;
  MipMap: Word;
begin
  Result := False;
  if not ReadFile(ZTEXFile, ZTEXHead, SizeOf(TZTEXFileHeader), Written, nil) or
    (Written <> SizeOf(TZTEXFileHeader)) then
    SetLastError(ERROR_FILE_CORRUPT)
  else if ZTEXHead.Magic <> ZenGinTexMagic then
    SetLastError(ERROR_INVALID_DATATYPE)
  else
  begin
    Skipped := True;
    for MipMap := ZTEXHead.Maps - 1 downto 1 do
    begin
      ZTEXSize := ZTEXMipMapSize(ZTEXHead, MipMap);
      if ZTEXSize = 0 then
        SetLastError(ERROR_INVALID_DATATYPE)
      else if SetFilePointer(ZTEXFile, ZTEXSize, nil, FILE_CURRENT) <> MAXDWORD then
        Continue;
      Skipped := False;
      SetLastError(ERROR_HANDLE_EOF);
      Break;
    end;
    if Skipped then
    begin
      ZTEXSize := ZTEXMipMapSize(ZTEXHead, 0);
      TGASize := ZTEXBufferSize(ZTEXHead, 0);
      if (ZTEXSize = 0) or (TGASize = 0) then
        SetLastError(ERROR_INVALID_DATATYPE)
      else
      begin
        ZTEXData := GetMemory(ZTEXSize);
        TGAData := GetMemory(TGASize);
        if (ZTEXData = nil) or (TGAData = nil) then
          SetLastError(ERROR_NOT_ENOUGH_MEMORY)
        else
        begin
          if not ReadFile(ZTEXFile, ZTEXData^, ZTEXSize, Written, nil) or
            (Written <> ZTEXSize) then
            SetLastError(ERROR_HANDLE_EOF)
          else
          begin
            ZeroMemory(@TGAHead, SizeOf(TTGAFileHeader));
            TGAHead.ImageType := 2;  // Uncompressed image data
            TGAHead.ImageWidth := ZTexHead.Width;
            TGAHead.ImageHeight := ZTexHead.Height;
            TGAHead.PixelDepth := ZTEXPixelDepth(ZTEXHead);
            TGAHead.ImageDesc := TGAHead.PixelDepth - 24;  // xAlpha/LeftBottom
            TGAFoot.ExtAreaOffset := 0;
            TGAFoot.DevDirOffset := 0;
            lstrcpy(TGAFoot.Signature, TGAFileFooterSignatur);
            if ZTEXDecompress(ZTEXHead, ZTEXData, TGAData, TGASize) and
              SwapImageVertikal(ZTEXHead.Height, TGASize, TGAData) then
            begin
              if WriteFile(TGAFile, TGAHead, SizeOf(TTGAFileHeader), Written, nil) and
                (Written = SizeOf(TTGAFileHeader)) and
                WriteFile(TGAFile, TGAData^, TGASize, Written, nil) and
                (Written = TGASize) and
                WriteFile(TGAFile, TGAFoot, SizeOf(TTGAFileFooter), Written, nil) and
                (Written = SizeOf(TTGAFileFooter)) then
              begin
                Result := True;
              end;
            end;
          end;
        end;
        if ZTEXData <> nil then
          FreeMemory(ZTEXData);
        if TGAData <> nil then
          FreeMemory(TGAData);
      end;
    end;
  end;
end;

{------------------------------------------------------------------------------}

procedure AppendBackSlash(Path: PChar);
begin
  if (Path <> nil) and (lstrlen(Path) > 0) and
    (Path[lstrlen(Path) - 1] <> '\') then
    lstrcat(Path, '\');
end;

procedure MakeFullPath(Root, Path, Name: PChar; Buffer: PChar);
var
  Temp: array [0..MAX_PATH] of Char;
begin
  Temp[0] := #0;
  if (Root <> nil) and (lstrlen(Root) > 0) then
  begin
    lstrcpy(Temp, Root);
    AppendBackSlash(Temp);
  end;
  if (Path <> nil) and (lstrlen(Path) > 0) then
    lstrcat(Temp, Path);
  if lstrlen(Temp) > 0 then
    AppendBackSlash(Temp);
  lstrcat(Temp, Name);
  lstrcpy(Buffer, Temp);
end;

procedure IntToStrGrp(Value: ULONG; Buffer: PChar);
const
  FrmtStd = '%u,';
  FrmtBig = '%3.3u,';
var
  Divider: ULONG;
  Frmt: array [0..10] of Char;
  Group: ULONG;
begin
  Buffer[0] := #0;
  lstrcpy(Frmt, FrmtStd);
  Divider := 1000000000;
  while Divider >= 1000 do
  begin
    if Value >= Divider then
    begin
      Group := Value div Divider;
      wvsprintf(PChar(@Buffer[lstrlen(Buffer)]), Frmt, PChar(@Group));
      lstrcpy(Frmt, FrmtBig);
      Value := Value mod Divider;
    end;
    Divider := Divider div 1000;
  end;
  Frmt[lstrlen(Frmt) - 1] := #0;
  wvsprintf(PChar(@Buffer[lstrlen(Buffer)]), Frmt, PChar(@Value));
end;

{------------------------------------------------------------------------------}

procedure ResetCounter;
begin
  FilesProcessed := 0;
  FilesSkipped := 0;
  FilesError := 0;
end;

procedure AddTrace(Dlg: HWND; Text: PChar);
var
  Edit: HWND;
  Count: LPARAM;
begin
  Edit := GetDlgItem(Dlg, IDC_EDTRACE);
  if Edit <> 0 then
  begin
    Count := SendMessage(Edit, WM_GETTEXTLENGTH, 0, 0);
    SendMessage(Edit, EM_SETSEL, Count, Count);
    SendMessage(Edit, EM_SCROLLCARET, 0, 0);
    SendMessage(Edit, EM_REPLACESEL, WPARAM(False), LPARAM(Text));
    SendMessage(Edit, EM_SCROLLCARET, 0, 0);
  end;
end;

procedure Trace(Dlg: HWND; Reason: TTraceType; Text: PChar);
var
  Buffer: array [0..4096] of Char;
  ErrLen: Integer;
  ErrText: array [0..255] of Char;
begin
  case Reason of
    ttText:
      begin
        AddTrace(Dlg, Text);
      end;
    ttNumber:
      begin
        IntToStrGrp(ULONG(Text), Buffer);
        AddTrace(Dlg, Buffer);
      end;
    ttProcessed:
      Inc(FilesProcessed);
    ttSkipped:
      begin
        lstrcpy(Buffer, 'skipped: ');
        lstrcat(Buffer, Text);
        lstrcat(Buffer, #13#10);
        AddTrace(Dlg, Buffer);
        Inc(FilesProcessed);
        Inc(FilesSkipped);
      end;
    ttError:
      begin
        lstrcpy(Buffer, 'ERROR: ');
        lstrcat(Buffer, Text);
        lstrcat(Buffer, ' (');
        ErrLen := FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM or
          FORMAT_MESSAGE_ARGUMENT_ARRAY, nil, GetLastError, 0, ErrText,
          SizeOf(ErrText), nil);
        ErrText[ErrLen] := #0;
        for ErrLen := lstrlen(ErrText) - 1 downto 0 do
          if (ErrText[ErrLen] in [#0..#32]) then
            ErrText[ErrLen] := ' ';
        lstrcat(Buffer, ErrText);
        lstrcat(Buffer, ')'#13#10);
        AddTrace(Dlg, Buffer);
        Inc(FilesProcessed);
        Inc(FilesError);
      end;
  end;
end;

{------------------------------------------------------------------------------}

procedure ProcessMessages(Dlg: HWND);
var
  Msg: TMsg;
begin
  while PeekMessage(Msg, Dlg, 0, 0, PM_REMOVE) do
    if not IsDialogMessage(Dlg, Msg) then
    begin
      TranslateMessage(Msg);
      DispatchMessage(Msg);
    end;
end;

procedure EnableDlgItem(Dlg: HWND; Item: Integer; Enable: Boolean);
var
  Wnd: HWND;
begin
  Wnd := GetDlgItem(Dlg, Item);
  if Wnd <> 0 then
    EnableWindow(Wnd, Enable);
end;

procedure SetStatusText(Dlg: HWND; Text: PChar);
begin
  if Text = nil then
    SetDlgItemText(Dlg, IDC_TXTINFO, '')
  else
    SetDlgItemText(Dlg, IDC_TXTINFO, Text);
end;

{------------------------------------------------------------------------------}

function BffCallBack(Wnd: HWND; Msg: UINT; IDList: PItemIDList; Select: PChar): Integer stdcall;
var
  Filename: array [0..MAX_PATH] of Char;
  Valid: Boolean;
begin
  Result := 0;
  case Msg of
    BFFM_INITIALIZED:
      if Select <> nil then
        SendMessage(Wnd, BFFM_SETSELECTION, Ord(True), LPARAM(Select));
    BFFM_SELCHANGED:
      if IDList <> nil then
      begin
        Valid := SHGetPathFromIDList(IDList, Filename);
        SendMessage(Wnd, BFFM_ENABLEOK, 0, LPARAM(Valid));
      end;
  end;
end;

function SelectDirectory(Wnd: HWND; Path, Title, Select: PChar): Boolean;
const
  BIF_NEWDIALOGSTYLE = $0040;
var
  DisplayName: array [0..MAX_PATH] of Char;
  Browse: TBrowseInfo;
  IDList: PItemIDList;
  Malloc: IMalloc;
begin
  Result := False;
  DisplayName[0] := #0;
  ZeroMemory(@Browse, SizeOf(Browse));
  Browse.hwndOwner := Wnd;
  Browse.pszDisplayName := DisplayName;
  Browse.lpszTitle := Title;
  Browse.lpfn := TFNBFFCallBack(@BffCallBack);
  Browse.ulFlags := BIF_RETURNONLYFSDIRS or BIF_NEWDIALOGSTYLE;
  Browse.lParam := LPARAM(Select);
  IDList := SHBrowseForFolder(Browse);
  if IDList <> nil then
  begin
    Path[0] := #0;
    Result := SHGetPathFromIDList(IDList, Path);
    SHGetMalloc(Malloc);
    Malloc.Free(IDList);
  end;
end;

procedure InitProgress(Dlg: HWND; MaxRange: Integer);
var
  PB: HWND;
begin
  PB := GetDlgItem(Dlg, IDC_PRGFILE);
  if PB <> 0 then
  begin
    SendMessage(PB, PBM_SETPOS, 0, 0);
    SendMessage(PB, PBM_SETRANGE32, 0, MaxRange);
  end;
end;

procedure IncProgress(Dlg: HWND; Increment: Integer = 1);
begin
  SendDlgItemMessage(Dlg, IDC_PRGFILE, PBM_DELTAPOS, Increment, 0);
end;

function DirectoryExists(DirPath: PChar): Boolean;
const
  INVALID_FILE_ATTRIBUTES = DWORD(-1);
var
  Attrib: DWORD;
begin
  Attrib := GetFileAttributes(DirPath);
  Result := (Attrib <> INVALID_FILE_ATTRIBUTES) and
    (Attrib and FILE_ATTRIBUTE_DIRECTORY = FILE_ATTRIBUTE_DIRECTORY);
end;

function MakeSureDirectoryPathExists(DirPath: LPCSTR): BOOL; stdcall;
var
  Path: array [0..MAX_PATH] of Char;
  Loop: Cardinal;
begin
  Result := True;
  if (DirPath <> nil) and (DirPath[0] <> #0) then
  try
    lstrcpy(Path, DirPath);
    for Loop := lstrlen(Path) - 1 downto 0 do
     if (Path[Loop] <> '\') then
       Path[Loop] := #0
     else
       Break;
    if (Path[0] <> #0) and not DirectoryExists(Path) then
      for Loop := 1 to MAX_PATH do
      begin
        if Path[Loop] = #0 then
          Break;
        if (Path[Loop] = '\') and (Path[Loop - 1] <> ':') then
        begin
          Path[Loop] := #0;
          if not DirectoryExists(Path) and not CreateDirectory(Path, nil) then
          begin
            Result := False;
            Break;
          end;
          Path[Loop] := '\';
        end;
      end;
  except
    Result := False;
  end;
end;

end.

unit GothicVdfsUtil;

interface

uses
  Windows, Messages, CommCtrl, RichEdit, ShlObj, ActiveX,
  VdfsDef, GothicVdfsGlob, GothicVdfsHint;

function OptionsWriteString(Option: PChar; Value: PChar): Boolean;
function OptionsWriteBoolean(Option: PChar; Value: DWORD): Boolean;
function OptionsReadString(Option: PChar; Value: PChar; Size: DWORD): Boolean;
function OptionsReadBoolean(Option: PChar; var Value: DWORD): Boolean;

function DetectGothicFileType(Filename: PChar): TGothicFileType;

function SelectDirectory(Wnd: HWND; Path, Title, Select: PChar): Boolean;

function FileExists(Filename: PChar): Boolean;
procedure ProcessMessages(Dlg: HWND);
procedure EnableDlgItem(Dlg: HWND; Item: Integer; Enable: Boolean);
procedure IntToStrGrp(Value: ULONG; Buffer: PChar);
procedure AttribToStr(Value: ULONG; Buffer: PChar);
procedure AppendBackSlash(Path: PChar);
procedure MakeFullPath(Root, Path, Name: PChar; Buffer: PChar);

procedure DisplayTime(Dlg: HWND; const Time: TSystemTime);
procedure ReadTime(Dlg: HWND; var Time: TSystemTime);
procedure InitProgress(Dlg: HWND; MaxRange: Integer; Mode: TVdfsDialogMode);
procedure IncProgress(Dlg: HWND; Mode: TVdfsDialogMode; Increment: Integer = 1);
procedure SetStatusText(Text: PChar; Mode: TVdfsDialogMode);

{$IFDEF USECOLORS}
procedure SetListViewColor(Dlg, DlgItem: Integer);
{$ENDIF}
procedure InsertListViewColumn(Dlg: HWND; DlgItem, Col: Integer;
  Text: PChar; Width: Integer = 0; Space: Integer = 0; Frmt: Integer = LVCFMT_LEFT);
procedure SetRichEditProp(Dlg, DlgItem: Integer; ReadOnly: Boolean; Limit: Integer = 0);

procedure ResetViewer(Dlg: HWND);
procedure EnableViewer(Dlg: HWND; Enabled: Boolean; ButtonsOnly: Boolean = True);
procedure EnableBuilder(Dlg: HWND; Enabled: Boolean);
procedure EnableExit(Dlg: HWND; Enabled: Boolean);
procedure SwitchMode(Dlg: HWND; Mode: TVdfsDialogMode);

type
  PTraceType = ^TTraceType;
  TTraceType = (
    ttText,
    ttNumber,
    ttOverride,
    ttError
  );

procedure Trace(Dlg: HWND; Reason: TTraceType; Text: PChar);

function MakeSureDirectoryPathExists(DirPath: LPCSTR): BOOL; stdcall;

implementation

function OptionsOpen(var Key: HKEY): Boolean;
begin
  Key := 0;
  Result := (RegCreateKeyEx(OptionsRoot, OptionsPath, 0, nil, 0, KEY_ALL_ACCESS, nil, Key, nil) = ERROR_SUCCESS);
end;

procedure OptionsClose(Key: HKEY);
begin
  if (Key <> 0) then
    RegCloseKey(Key);
end;

function OptionsWriteString(Option: PChar; Value: PChar): Boolean;
var
  Key: HKEY;
begin
  Result := False;
  if OptionsOpen(Key) then
  begin
    Result := (RegSetValueEx(Key, Option, 0, REG_SZ, Value, lstrlen(Value) + 1) = ERROR_SUCCESS);
    OptionsClose(Key);
  end;
end;

function OptionsWriteBoolean(Option: PChar; Value: DWORD): Boolean;
var
  Key: HKEY;
begin
  Result := False;
  if OptionsOpen(Key) then
  begin
    Result := (RegSetValueEx(Key, Option, 0, REG_DWORD, @Value, SizeOf(DWORD)) = ERROR_SUCCESS);
    OptionsClose(Key);
  end;
end;

function OptionsReadString(Option: PChar; Value: PChar; Size: DWORD): Boolean;
var
  Key: HKEY;
  _Type: DWORD;
begin
  Result := False;
  if OptionsOpen(Key) then
  begin
    _Type := REG_SZ;
    Result := (RegQueryValueEx(Key, Option, nil, @_Type, PByte(Value), @Size) = ERROR_SUCCESS);
    OptionsClose(Key);
  end;
end;

function OptionsReadBoolean(Option: PChar; var Value: DWORD): Boolean;
var
  Key: HKEY;
  Size: DWORD;
  _Type: DWORD;
begin
  Result := False;
  if OptionsOpen(Key) then
  begin
    Size := SizeOf(DWORD);
    Result := (RegQueryValueEx(Key, Option, nil, @_Type, PByte(@Value), @Size) = ERROR_SUCCESS);
    OptionsClose(Key);
  end;
end;

function DetectGothicFileType(Filename: PChar): TGothicFileType;
const
  VdfsScriptBegin = '[BEGINVDF]';
var
  FileHandle: THandle;
  Header: TVdfsHeader;
  Written: ULONG;
  ScriptBegin: array [0..Length(VdfsScriptBegin) - 1] of Char;
//FilePart: PChar;
//SearchBuffer: array [0..MAX_PATH] of Char;
//Buffer: array [0..4096] of Char;
begin
  Result := gftUnknown;
  FileHandle := CreateFile(Filename, GENERIC_READ, FILE_SHARE_READ, nil,
    OPEN_EXISTING, 0, 0);
  if FileHandle <> INVALID_HANDLE_VALUE then
  begin
    if ReadFile(FileHandle, Header, SizeOf(TVdfsHeader), Written, nil) and
      (Written = SizeOf(TVdfsHeader)) and
      ((Header.Version = VdfsVersionText) or (Header.Version = VdfsVersionText2)) then
      Result := gftVolume
    else if (SetFilePointer(FileHandle, 0, nil, FILE_BEGIN) = 0) and
      ReadFile(FileHandle, ScriptBegin, SizeOf(ScriptBegin), Written, nil) and
      (Written = SizeOf(ScriptBegin)) and
      (ScriptBegin = VdfsScriptBegin) then
      Result := gftScript;
    CloseHandle(FileHandle);
  end;
(*
  if (Result = gftUnknown) then
  begin
    if (GetPrivateProfileString(VdfsMgrScriptSegGlobal, VdfsMgrScriptKeyVDFName,
      '', Buffer, SizeOf(Buffer), Filename) > 0) then
      Result := gftScript
    else
    begin
      FilePart := nil;
      if (SearchPath(nil, Filename, nil, SizeOf(SearchBuffer), SearchBuffer, FilePart) > 0) and
        (lstrcpy(Filename, SearchBuffer) <> nil) and
        (GetPrivateProfileString(VdfsMgrScriptSegGlobal, VdfsMgrScriptKeyVDFName,
        '', Buffer, SizeOf(Buffer), Filename) > 0) then
        Result := gftScript;
    end;
  end;
*)
end;

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

function FileExists(Filename: PChar): Boolean;
var
  FindFile: THandle;
  FindData: TWin32FindData;
begin
  Result := False;
  FindFile := FindFirstFile(Filename, FindData);
  if FindFile <> INVALID_HANDLE_VALUE then
  begin
    Result := True;
    FindClose(FindFile);
  end;
end;

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
      wvsprintf(PChar(@Buffer[lstrlen(Buffer)]), PChar(@Frmt), PChar(@Group));
      lstrcpy(Frmt, FrmtBig);
      Value := Value mod Divider;
    end;
    Divider := Divider div 1000;
  end;
  Frmt[lstrlen(Frmt) - 1] := #0;
  wvsprintf(PChar(@Buffer[lstrlen(Buffer)]), PChar(@Frmt), PChar(@Value));
end;

procedure AttribToStr(Value: ULONG; Buffer: PChar);
const
  FILE_ATTRIBUTE_DEVICE = $00000040;
begin
  Buffer[0] := #0;
  if (Value and FILE_ATTRIBUTE_READONLY <> 0) then
    lstrcpy(Buffer, 'R');
  if (Value and FILE_ATTRIBUTE_HIDDEN <> 0) then
    lstrcat(Buffer, 'H');
  if (Value and FILE_ATTRIBUTE_SYSTEM <> 0) then
    lstrcat(Buffer, 'S');
  if (Value and FILE_ATTRIBUTE_ARCHIVE <> 0) then
    lstrcat(Buffer, 'A');
end;

procedure AppendBackSlash(Path: PChar);
begin
  if (Path <> nil) and (lstrlen(Path) > 0) and
    (Path[lstrlen(Path) - 1] <> '\') then
    lstrcat(Path, '\');
end;

procedure MakeFullPath(Root, Path, Name: PChar; Buffer: PChar);
begin
  Buffer[0] := #0;
  if (Root <> nil) and (lstrlen(Root) > 0) then
  begin
    lstrcpy(Buffer, Root);
    AppendBackSlash(Buffer);
  end;
  if (Path <> nil) and (lstrlen(Path) > 0) then
    lstrcat(Buffer, Path);
  if lstrlen(Buffer) > 0 then
    AppendBackSlash(Buffer);
  lstrcat(Buffer, Name);
end;

procedure DisplayTime(Dlg: HWND; const Time: TSystemTime);
begin
  SendDlgItemMessage(Dlg, IDC_SPINYEAR, UDM_SETPOS, 0, Time.wYear);
  SendDlgItemMessage(Dlg, IDC_SPINMONTH, UDM_SETPOS, 0, Time.wMonth);
  SendDlgItemMessage(Dlg, IDC_SPINDAY, UDM_SETPOS, 0, Time.wDay);
  SendDlgItemMessage(Dlg, IDC_SPINHOUR, UDM_SETPOS, 0, Time.wHour);
  SendDlgItemMessage(Dlg, IDC_SPINMIN, UDM_SETPOS, 0, Time.wMinute);
  SendDlgItemMessage(Dlg, IDC_SPINSEC, UDM_SETPOS, 0, Time.wSecond);
end;

procedure ReadTime(Dlg: HWND; var Time: TSystemTime);
begin
  ZeroMemory(@Time, SizeOf(TSystemTime));
  Time.wYear := Word(SendDlgItemMessage(Dlg, IDC_SPINYEAR, UDM_GETPOS, 0, 0));
  Time.wMonth := Word(SendDlgItemMessage(Dlg, IDC_SPINMONTH, UDM_GETPOS, 0, 0));
  Time.wDay := Word(SendDlgItemMessage(Dlg, IDC_SPINDAY, UDM_GETPOS, 0, 0));
  Time.wHour := Word(SendDlgItemMessage(Dlg, IDC_SPINHOUR, UDM_GETPOS, 0, 0));
  Time.wMinute := Word(SendDlgItemMessage(Dlg, IDC_SPINMIN, UDM_GETPOS, 0, 0));
  Time.wSecond := Word(SendDlgItemMessage(Dlg, IDC_SPINSEC, UDM_GETPOS, 0, 0));
end;

procedure InitProgress(Dlg: HWND; MaxRange: Integer; Mode: TVdfsDialogMode);
var
  PB: HWND;
begin
  PB := 0;
  if Mode = modeViewer then
    PB := GetDlgItem(Dlg, IDC_PROGVIEW)
  else if Mode = modeBuilder then
    PB := GetDlgItem(Dlg, IDC_PROGBUILD);
  if PB <> 0 then
  begin
    SendMessage(PB, PBM_SETPOS, 0, 0);
    SendMessage(PB, PBM_SETRANGE32, 0, MaxRange);
  end;
end;

procedure IncProgress(Dlg: HWND; Mode: TVdfsDialogMode; Increment: Integer = 1);
begin
  if Mode = modeViewer then
    SendDlgItemMessage(Dlg, IDC_PROGVIEW, PBM_DELTAPOS, Increment, 0)
  else if Mode = modeBuilder then
    SendDlgItemMessage(Dlg, IDC_PROGBUILD, PBM_DELTAPOS, Increment, 0);
end;

procedure SetStatusText(Text: PChar; Mode: TVdfsDialogMode);
begin
  if (MainFormStatus <> 0) then
    if Mode = CurrDlgMode then
      if Text = nil then
        SendMessage(MainFormStatus, SB_SETTEXT, 0, LPARAM(PChar('')))
      else
        SendMessage(MainFormStatus, SB_SETTEXT, 0, LPARAM(Text));
end;

{$IFDEF USECOLORS}
procedure SetListViewColor(Dlg, DlgItem: Integer);
var
  Item: HWND;
begin
  Item := GetDlgItem(Dlg, DlgItem);
  if Item <> 0 then
  begin
    SendMessage(Item, LVM_SETBKCOLOR, 0, DialogBackColor);
    SendMessage(Item, LVM_SETTEXTCOLOR, 0, DialogTextColor);
    SendMessage(Item, LVM_SETTEXTBKCOLOR, 0, DialogBackColor);
  end;
end;
{$ENDIF}

procedure InsertListViewColumn(Dlg: HWND; DlgItem, Col: Integer;
  Text: PChar; Width: Integer = 0; Space: Integer = 0; Frmt: Integer = LVCFMT_LEFT);
var
  Item: HWND;
  Column: TLVColumn;
  Rect: TRect;
begin
  Item := GetDlgItem(Dlg, DlgItem);
  if Item <> 0 then
  begin
    ZeroMemory(@Column, SizeOf(TLVColumn));
    Column.mask := LVCF_FMT;
    Column.fmt := Frmt;
    if Text <> nil then
    begin
      Column.mask := Column.mask or LVCF_TEXT;
      Column.pszText := Text;
    end;
    if Width + Space <> 0 then
    begin
      Column.mask := Column.mask or LVCF_WIDTH;
      if (Space <> 0) and GetClientRect(Item, Rect) then
        Column.cx := Rect.Right - Rect.Left - Space - GetSystemMetrics(SM_CXVSCROLL);
      if Column.cx = 0 then
        Column.cx := Width;
      if Column.cx = 0 then
        Column.mask := Column.mask and not LVCF_WIDTH;
    end;
    SendMessage(Item, LVM_INSERTCOLUMN, Col, LPARAM(@Column));
  end;
end;

procedure SetRichEditProp(Dlg, DlgItem: Integer; ReadOnly: Boolean; Limit: Integer = 0);
var
  Item: HWND;
{$IFDEF USECOLORS}
  CharFormat: TCharFormat;
{$ENDIF}
begin
  Item := GetDlgItem(Dlg, DlgItem);
  if Item <> 0 then
  begin
{$IFDEF USECOLORS}
    ZeroMemory(@CharFormat, SizeOf(TCharFormat));
    CharFormat.cbSize := SizeOf(TCharFormat);
    CharFormat.dwMask := CFM_COLOR;
    if ReadOnly then
      CharFormat.crTextColor := DialogTextColor
    else
      CharFormat.crTextColor := EditTextColor;
    SendMessage(Item, EM_SETCHARFORMAT, SCF_ALL, LPARAM(@CharFormat));
    if ReadOnly then
      CharFormat.crTextColor := DialogBackColor
    else
      CharFormat.crTextColor := EditBackColor;
    SendMessage(Item, EM_SETBKGNDCOLOR, 0, CharFormat.crTextColor);
{$ENDIF}
    SendMessage(Item, EM_SETREADONLY, WPARAM(ReadOnly), 0);
    if Limit <> 0 then
      SendMessage(Item, EM_SETLIMITTEXT, Limit, 0);
  end;
end;

procedure ResetViewer(Dlg: HWND);
var
  Time: TSystemTime;
begin
  if CurrDlgMode = modeViewer then
  begin
    SetDlgItemText(Dlg, IDC_EDITFILE, '');
    SetDlgItemText(Dlg, IDC_EDITTEXT, '');
    ZeroMemory(@Time, SizeOf(TSystemTime));
    DisplayTime(Dlg, Time);
  end;
  SendDlgItemMessage(Dlg, IDC_TREEVIEW, TVM_DELETEITEM, 0, LPARAM(TVI_ROOT));
  SendDlgItemMessage(Dlg, IDC_LISTVIEW, LVM_DELETEALLITEMS, 0, 0);
  if ViewerFile <> 0 then
    CloseHandle(ViewerFile);
  ViewerFile := 0;
  if ViewerTable <> nil then
    FreeMemory(ViewerTable);
  ViewerTable := nil;
  ZeroMemory(@ViewerHeader, SizeOf(TVdfsHeader));
end;

procedure EnableViewer(Dlg: HWND; Enabled: Boolean; ButtonsOnly: Boolean = True);
var
  Loop: Integer;
begin
  ViewerWorkInProgress := not Enabled;
  if CurrDlgMode = modeViewer then
  begin
    EnableDlgItem(Dlg, IDC_BTNFILE, Enabled);
    EnableDlgItem(Dlg, IDC_BTNROOT, Enabled);
  end;
  for Loop := IDC_BTNVOL to IDC_CHECKFULL do
    EnableDlgItem(Dlg, Loop, Enabled);
  if Enabled or (not ButtonsOnly) then
  begin
    EnableDlgItem(Dlg, IDC_TREEVIEW, Enabled);
    EnableDlgItem(Dlg, IDC_LISTVIEW, Enabled);
  end;
end;

procedure EnableBuilder(Dlg: HWND; Enabled: Boolean);
var
  Loop: Integer;
begin
  BuilderWorkInProgress := not Enabled;
  if CurrDlgMode = modeBuilder then
  begin
    EnableDlgItem(Dlg, IDC_BTNFILE, Enabled);
    EnableDlgItem(Dlg, IDC_BTNROOT, Enabled);
    SetRichEditProp(Dlg, IDC_EDITTEXT, BuilderWorkInProgress);
    Loop := IDC_EDITYEAR;
    while Loop <= IDC_EDITSEC do
    begin
      SendDlgItemMessage(Dlg, Loop, EM_SETREADONLY, WPARAM(BuilderWorkInProgress), 0);
      EnableDlgItem(Dlg, Loop + 1, Enabled);
      Inc(Loop, 2);
    end;
  end;
  EnableDlgItem(Dlg, IDC_CHECKSORT, Enabled);
  for Loop := IDC_EDITFILES to IDC_CHECKSORT do
    case Loop of
      IDC_LISTFILES,
      IDC_LISTEX,
      IDC_LISTIN,
      IDC_PROGBUILD: ;
    else
      EnableDlgItem(Dlg, Loop, Enabled);
    end;
end;

procedure EnableExit(Dlg: HWND; Enabled: Boolean);
var
  Menu: HMENU;
begin
  EnableDlgItem(Dlg, IDC_BTNEXIT, Enabled);
  if Enabled then
    SetClassLong(Dlg, GCL_STYLE, GetClassLong(Dlg, GCL_STYLE) and not CS_NOCLOSE)
  else
    SetClassLong(Dlg, GCL_STYLE, GetClassLong(Dlg, GCL_STYLE) or CS_NOCLOSE);
  Menu := GetSystemMenu(Dlg, False);
  if (Menu <> 0) then
  begin
    if Enabled then
      EnableMenuItem(Menu, SC_CLOSE, MF_BYCOMMAND or MF_ENABLED)
    else
      EnableMenuItem(Menu, SC_CLOSE, MF_BYCOMMAND or MF_DISABLED or MF_GRAYED);
    DrawMenuBar(Dlg);
  end;
end;

procedure SwitchMode(Dlg: HWND; Mode: TVdfsDialogMode);
var
  Show: Integer;
  Enabled: Boolean;
  Loop: Integer;
  SystemTime: TSystemTime;
  FileTime: TFileTime;
  TempTime: TFileTime;
  FatDate: Word;
  FatTime: Word;
begin
  if Mode <> CurrDlgMode then
  begin
    if Mode = modeViewer then
      Show := SW_SHOW
    else
      Show := SW_HIDE;
    for Loop := IDC_TREEVIEW to IDC_PROGVIEW do
      ShowWindow(GetDlgItem(Dlg, Loop), Show);
    if Mode = modeBuilder then
      Show := SW_SHOW
    else
      Show := SW_HIDE;
    for Loop := IDC_EDITFILES to IDC_CHECKSORT do
      ShowWindow(GetDlgItem(Dlg, Loop), Show);
    Enabled := Mode = modeBuilder;
    Loop := IDC_EDITYEAR;
    while Loop <= IDC_EDITSEC do
    begin
      SendDlgItemMessage(Dlg, Loop, EM_SETREADONLY, WPARAM(not Enabled), 0);
      EnableDlgItem(Dlg, Loop + 1, Enabled);
      Inc(Loop, 2);
    end;
    if CurrDlgMode = modeBuilder then
    begin
      GetDlgItemText(Dlg, IDC_EDITTEXT, BuilderHeader.Comment, SizeOf(TVdfsComment));
      ReadTime(Dlg, SystemTime);
      if SystemTimeToFileTime(SystemTime, FileTime) then
      begin
        if IsDlgButtonChecked(Dlg, IDC_CHECKUTC) = BST_UNCHECKED then
        begin
          if LocalFileTimeToFileTime(FileTime, TempTime) then
            FileTime := TempTime;
        end;
        if FileTimeToDosDateTime(FileTime, FatDate, FatTime) then
          BuilderHeader.Params.TimeStamp := FatDate shl 16 or FatTime;
      end;
    end;
    CurrDlgMode := Mode;
    {*} SetStatusText(nil, CurrDlgMode);
    case Mode of
      modeViewer:
        begin
          SetDlgItemText(Dlg, IDC_EDITFILE, ViewerFilename);
          SetDlgItemText(Dlg, IDC_EDITROOT, ViewerRoot);
          SetDlgItemText(Dlg, IDC_EDITTEXT, ViewerHeader.Comment);
          ZeroMemory(@SystemTime, SizeOf(TSystemTime));
          // FIXME_Time
          ViewerHeader.Params.TimeStamp := $2F2F8245;
          if (ViewerHeader.Params.TimeStamp <> 0) and
            DosDateTimeToFileTime(HiWord(ViewerHeader.Params.TimeStamp),
              Word(ViewerHeader.Params.TimeStamp), FileTime) then
          begin
            if IsDlgButtonChecked(Dlg, IDC_CHECKUTC) = BST_UNCHECKED then
            begin
              if FileTimeToLocalFileTime(FileTime, TempTime) then
                FileTime := TempTime;
            end;
            FileTimeToSystemTime(FileTime, SystemTime);
          end;
          DisplayTime(Dlg, SystemTime);
          EnableViewer(Dlg, not ViewerWorkInProgress, IsWindowEnabled(GetDlgItem(Dlg, IDC_LISTVIEW)));
          SetRichEditProp(Dlg, IDC_EDITTEXT, True);
        end;
      modeBuilder:
        begin
          SetDlgItemText(Dlg, IDC_EDITFILE, BuilderFilename);
          SetDlgItemText(Dlg, IDC_EDITROOT, BuilderRoot);
          SetDlgItemText(Dlg, IDC_EDITTEXT, BuilderHeader.Comment);
          ZeroMemory(@SystemTime, SizeOf(TSystemTime));
          if BuilderHeader.Params.TimeStamp = 0 then
            GetSystemTime(SystemTime)
          else if DosDateTimeToFileTime(HiWord(BuilderHeader.Params.TimeStamp),
            Word(BuilderHeader.Params.TimeStamp), FileTime) then
          begin
            if IsDlgButtonChecked(Dlg, IDC_CHECKUTC) = BST_UNCHECKED then
            begin
              if FileTimeToLocalFileTime(FileTime, TempTime) then
                FileTime := TempTime;
            end;
            FileTimeToSystemTime(FileTime, SystemTime);
          end;
          DisplayTime(Dlg, SystemTime);
          EnableBuilder(Dlg, not BuilderWorkInProgress);
        end;
    end;
    SwitchModeToolTip(Mode);
  end;
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
      AddTrace(Dlg, Text);
    ttNumber:
      begin
        IntToStrGrp(ULONG(Text), Buffer);
        AddTrace(Dlg, Buffer);
      end;
//  ttProcessed:
//    Inc(FilesProcessed);
    ttOverride:
      begin
        lstrcpy(Buffer, 'override: ');
        lstrcat(Buffer, Text);
        lstrcat(Buffer, #13#10);
        AddTrace(Dlg, Buffer);
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
        Inc(AutoExtractErrors);
      end;
  end;
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

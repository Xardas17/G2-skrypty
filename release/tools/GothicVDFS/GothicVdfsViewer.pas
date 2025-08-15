unit GothicVdfsViewer;

interface

uses
  Windows, Messages, CommCtrl, CommDlg,
  VdfsDef, GothicVdfsGlob, GothicVdfsUtil;

function GetVdfsEntryByIndex(const Header: TVdfsHeader; Table: PVdfsTable;
  var Entry: TVdfsEntry; Index: ULONG): Boolean;
function IsVdfsEntryDirectory(const Header: TVdfsHeader; Table: PVdfsTable; Index: ULONG): Boolean;
function GetVdfsDataSize(const Header: TVdfsHeader; Table: PVdfsTable;
  Index: ULONG; var Dirs, Files: ULONG; StartWith: ULONG = 0): ULONG;
function GetSelectedDataSize(LV: HWND; const Header: TVdfsHeader; Table: PVdfsTable;
  IncDir: Integer = 1): ULONG;

function SaveVdfsEntryToDisk(Dlg: HWND; VolFile: THandle; const Header: TVdfsHeader;
  Table: PVdfsTable; Index: ULONG; Root, Path: PChar): Boolean;
function SaveVdfsDirectoryToDisk(Dlg: HWND; VolFile: THandle;
  const Header: TVdfsHeader; Table: PVdfsTable; Index: ULONG;
  Root, Path: PChar): Boolean;
function SaveVdfsVolumeToDisk(Dlg: HWND; VolFile: THandle;
  const Header: TVdfsHeader; Table: PVdfsTable; Root: PChar): Boolean;

procedure GetSelectedPath(Dlg: HWND; Path: PChar);
procedure ExtractSelectedVdfsEntries(Dlg, LV: HWND; const Header: TVdfsHeader;
  Table: PVdfsTable; VolFile: THandle; UsePath: Boolean);
procedure ListViewInsertVdfsEntries(LV: HWND; const Header: TVdfsHeader;
  Table: PVdfsTable; Index: ULONG);
procedure TreeViewInsertVdfsEntries(TV: HWND; Root: HTREEITEM;
  const Header: TVdfsHeader; Table: PVdfsTable; Index: ULONG);
procedure ViewerSetStatus(Dirs, Files, Data: ULONG);

procedure FillViewer(Dlg: HWND; Filename: PChar);
function OpenVdfs(Dlg: HWND; Filename: PChar): Boolean;

implementation

procedure HandleError(Dlg: HWND; Text: PChar);
begin
  if AutoExtractVolume then
    Trace(Dlg, ttError, Text)
  else
    MessageBox(Dlg, Text, nil, MB_OK);
end;

function GetVdfsEntryByIndex(const Header: TVdfsHeader; Table: PVdfsTable;
  var Entry: TVdfsEntry; Index: ULONG): Boolean;
var
  Loop: Integer;
begin
  Result := False;
  if Index < Header.Params.EntryCount then
  begin
    Entry := Table[Index];
    Loop := High(Entry.Name);
    while (Loop >= 0) and (Entry.Name[Loop] = ' ') do
    begin
      Entry.Name[Loop] := #0;
      Dec(Loop);
    end;
    Result := True;
  end;
end;

function IsVdfsEntryDirectory(const Header: TVdfsHeader; Table: PVdfsTable; Index: ULONG): Boolean;
var
  Entry: TVdfsEntry;
begin
  Result := False;
  if GetVdfsEntryByIndex(Header, Table, Entry, Index) then
    Result := (Entry.Flags and VDFS_FILE_DIRECTORY = VDFS_FILE_DIRECTORY);
end;

function GetVdfsDataSize(const Header: TVdfsHeader; Table: PVdfsTable;
  Index: ULONG; var Dirs, Files: ULONG; StartWith: ULONG = 0): ULONG;
var
  CurrIndex: ULONG;
  Entry: TVdfsEntry;
begin
  Result := StartWith;
  CurrIndex := Index;
  while GetVdfsEntryByIndex(Header, Table, Entry, CurrIndex) do
  begin
    if (Entry.Flags and VDFS_FILE_DIRECTORY = VDFS_FILE_DIRECTORY) then
    begin
      Inc(Dirs);
      Result := GetVdfsDataSize(Header, Table, Entry.Offset, Dirs, Files, Result);
    end
    else
    begin
      Inc(Files);
      Inc(Result, Entry.Size);
    end;
    Inc(CurrIndex);
    if (Entry.Flags and VDFS_FILE_LASTENTRY = VDFS_FILE_LASTENTRY) then
      Break;
  end;
end;

function GetSelectedDataSize(LV: HWND; const Header: TVdfsHeader; Table: PVdfsTable;
  IncDir: Integer = 1): ULONG;
var
  SelIndex: Integer;
  Item: TLVItem;
  Entry: TVdfsEntry;
begin
  Result := 0;
  if UINT(SendMessage(LV, LVM_GETSELECTEDCOUNT, 0, 0)) > 0 then
  begin
    SelIndex := SendMessage(LV, LVM_GETNEXTITEM, -1, LVNI_ALL or LVNI_SELECTED);
    while SelIndex <> -1 do
    begin
      ZeroMemory(@Item, SizeOf(TLVItem));
      Item.iItem := SelIndex;
      Item.mask := LVIF_PARAM;
      if BOOL(SendMessage(LV, LVM_GETITEM, 0, LPARAM(@Item))) and
        GetVdfsEntryByIndex(Header, Table, Entry, Item.lParam) then
      begin
        if (Entry.Flags and VDFS_FILE_DIRECTORY = VDFS_FILE_DIRECTORY) then
          Inc(Result, IncDir)
        else
          Inc(Result, Entry.Size);
      end;
      SelIndex := SendMessage(LV, LVM_GETNEXTITEM, SelIndex, LVNI_ALL or LVNI_SELECTED);
    end;
  end;
end;

function SaveVdfsEntryToDisk(Dlg: HWND; VolFile: THandle; const Header: TVdfsHeader;
  Table: PVdfsTable; Index: ULONG; Root, Path: PChar): Boolean;
const
  INVALID_FILE_ATTRIBUTES = ULONG(-1);
  BlockSize = 4096;
var
  Entry: TVdfsEntry;
  Filename: array [0..MAX_PATH] of Char;
  Block: array [0..BlockSize] of Byte;
  Blocks: ULONG;
  Loop: ULONG;
  NewFile: THandle;
  ToWrite: DWORD;
  Written: DWORD;
  SysFileTime: TFileTime;
  FileTime: TFileTime;
  RelFilename: array [0..MAX_PATH] of Char;
begin
  Result := False;
  if not GetVdfsEntryByIndex(Header, Table, Entry, Index) then
    HandleError(Dlg, 'Cannot Save Entry - Invalid Index!')
  else
  begin
    MakeFullPath(Root, Path, PChar(string(Entry.Name)), @Filename[0]);
    {*} SetStatusText(PChar('Processing: ' + Entry.Name + '...'), modeViewer);
    if (Entry.Flags and VDFS_FILE_DIRECTORY = VDFS_FILE_DIRECTORY) then
    begin
      AppendBackSlash(Filename);
      if not MakeSureDirectoryPathExists(Filename) then
        HandleError(Dlg, PChar('Cannot Create Directory: ' + Filename))
      else
      begin
        IncProgress(Dlg, modeViewer);
        Result := True;
      end;
    end
    else if SetFilePointer(VolFile, Entry.Offset, nil, FILE_BEGIN) = 0 then
      HandleError(Dlg, 'Cannot Access File Data (truncated volume?)!')
    else
    begin
      if not MakeSureDirectoryPathExists(Filename) then
        HandleError(Dlg, PChar('Cannot Create Directory for file: ' + Filename))
      else
      begin
        if FileExists(Filename) then
        begin
          MakeFullPath(nil, Path, PChar(string(Entry.Name)), @RelFilename[0]);
          Trace(Dlg, ttOverride, RelFilename);
        end;
        NewFile := CreateFile(Filename, GENERIC_WRITE, FILE_SHARE_READ, nil,
          CREATE_ALWAYS, (Entry.Attrib and VDFS_FILE_ATTRIBUTE_MASK), 0);
        if NewFile = INVALID_HANDLE_VALUE then
          HandleError(Dlg, PChar('Cannot Create/Override File: ' + Filename))
        else
        begin
          Blocks := Entry.Size div BlockSize;
          Loop := 0;
          repeat
            if Loop < Blocks then
              ToWrite := BlockSize
            else
              ToWrite := Entry.Size mod BlockSize;
            if ToWrite > 0 then
            begin
              if not ReadFile(VolFile, Block, ToWrite, Written, nil) or (Written <> ToWrite) then
              begin
                HandleError(Dlg, PChar('Cannot Read Data from Volume!: ' + Filename));
                Break;
              end;
              if not WriteFile(NewFile, Block, ToWrite, Written, nil) or (Written <> ToWrite) then
              begin
                HandleError(Dlg, PChar('Cannot Write Data to File: ' + Filename));
                Break;
              end;
              IncProgress(Dlg, modeViewer, ToWrite);
            end;
            Inc(Loop);
            ProcessMessages(Dlg);
          until Loop > Blocks;
          GetSystemTimeAsFileTime(SysFileTime);
          if DosDateTimeToFileTime(HiWord(Header.Params.TimeStamp),
            Word(Header.Params.TimeStamp), FileTime) then
            SetFileTime(NewFile, @SysFileTime, @SysFileTime, @FileTime);
          CloseHandle(NewFile);
        end;
        Result := True;
      end;
    end;
  end;
end;

function SaveVdfsDirectoryToDisk(Dlg: HWND; VolFile: THandle;
  const Header: TVdfsHeader; Table: PVdfsTable; Index: ULONG;
  Root, Path: PChar): Boolean;
var
  SavePath: array [0..MAX_PATH] of Char;
  SubPath: array [0..MAX_PATH] of Char;
  CurrIndex: ULONG;
  Entry: TVdfsEntry;
begin
  Result := True;
  SavePath[0] := #0;
  if Path <> nil then
  begin
    lstrcpy(SavePath, Path);
    if SavePath[0] <> #0 then
      AppendBackSlash(SavePath);
  end;
  CurrIndex := Index;
  while GetVdfsEntryByIndex(Header, Table, Entry, CurrIndex) do
  begin
    if not SaveVdfsEntryToDisk(Dlg, VolFile, Header, Table, CurrIndex, Root, SavePath) then
    begin
      Result := False;
      Break;
    end;
    ProcessMessages(Dlg);
    if (Entry.Flags and VDFS_FILE_DIRECTORY = VDFS_FILE_DIRECTORY) then
    begin
      lstrcpy(SubPath, SavePath);
      if lstrlen(SubPath) > 0 then
        AppendBackSlash(SubPath);
      lstrcat(SubPath, Entry.Name);
      if not SaveVdfsDirectoryToDisk(Dlg, VolFile, Header, Table, Entry.Offset, Root, SubPath) then
      begin
        Result := False;
        Break;
      end;
    end;
    Inc(CurrIndex);
    if (Entry.Flags and VDFS_FILE_LASTENTRY = VDFS_FILE_LASTENTRY) then
      Break;
  end;
  {*} SetStatusText(nil, modeViewer);
end;

function SaveVdfsVolumeToDisk(Dlg: HWND; VolFile: THandle;
  const Header: TVdfsHeader; Table: PVdfsTable; Root: PChar): Boolean;
begin
  AutoExtractErrors := 0;
  EnableViewer(Dlg, False, True);
  InitProgress(Dlg, ViewerHeader.Params.DataSize + ViewerHeader.Params.EntryCount -
    ViewerHeader.Params.FileCount, modeViewer);
  Result := SaveVdfsDirectoryToDisk(Dlg, VolFile, Header, Table, 0, Root, '');
  InitProgress(Dlg, 1, modeViewer);
  EnableViewer(Dlg, True);
  {*} SetStatusText(nil, modeViewer);
  if AutoExtractVolume then
  begin
    Trace(Dlg, ttText, #13#10#13#10'Summary:'#13#10'  EntryCount: ');
    Trace(Dlg, ttNumber, PChar(ViewerHeader.Params.EntryCount));
    Trace(Dlg, ttText, #13#10'  FileCount: ');
    Trace(Dlg, ttNumber, PChar(ViewerHeader.Params.FileCount));
    Trace(Dlg, ttText, #13#10'  Errors: ');
    Trace(Dlg, ttNumber, PChar(AutoExtractErrors));
    Trace(Dlg, ttText, #13#10);
  end;
end;

procedure GetSelectedPath(Dlg: HWND; Path: PChar);
var
  TV: HWND;
  Item: HTREEITEM;
  Data: TTVItem;
  Name: array [0..MAX_PATH] of Char;
  Temp: array [0..MAX_PATH] of Char;
begin
  Path[0] := #0;
  TV := GetDlgItem(Dlg, IDC_TREEVIEW);
  if TV <> 0 then
  begin
    Item := HTREEITEM(SendMessage(TV, TVM_GETNEXTITEM, TVGN_CARET, LPARAM(nil)));
    while Item <> nil do
    begin
      ZeroMemory(@Name, SizeOf(Name));
      ZeroMemory(@Data, SizeOf(TTVItem));
      Data.hItem := Item;
      Data.mask := TVIF_TEXT or TVIF_PARAM;
      Data.pszText := @Name[0];
      Data.cchTextMax := SizeOf(Name);
      if BOOL(SendMessage(TV, TVM_GETITEM, 0, LPARAM(@Data))) and
        (Data.lParam <> -1) then
      begin
        lstrcpy(Temp, Path);
        lstrcpy(Path, Name);
        if Path[0] <> #0 then
          AppendBackSlash(Path);
        lstrcat(Path, Temp);
      end;
      Item := HTREEITEM(SendMessage(TV, TVM_GETNEXTITEM, TVGN_PARENT, LPARAM(Item)));
    end;
  end;
end;

procedure ExtractSelectedVdfsEntries(Dlg, LV: HWND; const Header: TVdfsHeader;
  Table: PVdfsTable; VolFile: THandle; UsePath: Boolean);
var
  SelCount: UINT;
  SelIndex: Integer;
  Item: TLVItem;
  Buffer: array [0..MAX_PATH] of Char;
  Path: PChar;
begin
  SelCount := UINT(SendMessage(LV, LVM_GETSELECTEDCOUNT, 0, 0));
  if SelCount = 0 then
  begin
    HandleError(Dlg, 'No Entries Selected.');
  end
  else
  begin
    EnableViewer(Dlg, False);
    InitProgress(Dlg, Integer(GetSelectedDataSize(LV, Header, Table)), modeViewer);
    SelIndex := SendMessage(LV, LVM_GETNEXTITEM, -1, LVNI_ALL or LVNI_SELECTED);
    while SelIndex <> -1 do
    begin
      ZeroMemory(@Item, SizeOf(TLVItem));
      Item.iItem := SelIndex;
      Item.mask := LVIF_PARAM;
      if not BOOL(SendMessage(LV, LVM_GETITEM, 0, LPARAM(@Item))) then
      begin
        HandleError(Dlg, 'Error on Getting Item Data!');
        Break;
      end;
      Path := nil;
      if UsePath then
      begin
        GetSelectedPath(Dlg, @Buffer[0]);
        Path := @Buffer[0];
      end;
      if not SaveVdfsEntryToDisk(Dlg, VolFile, Header, Table, Item.lParam, ViewerRoot, Path) then
        Break;
      ProcessMessages(Dlg);
      SelIndex := SendMessage(LV, LVM_GETNEXTITEM, SelIndex, LVNI_ALL or LVNI_SELECTED);
    end;
    EnableViewer(Dlg, True);
    InitProgress(Dlg, 1, modeViewer);
    {*} SetStatusText(nil, modeViewer);
  end;
end;

procedure ListViewInsertVdfsEntries(LV: HWND; const Header: TVdfsHeader;
  Table: PVdfsTable; Index: ULONG);
var
  CurrIndex: ULONG;
  Entry: TVdfsEntry;
  Item: TLVItem;
  ItemIndex: Integer;
  Buffer: array [0..50] of Char;
begin
  SendMessage(LV, LVM_DELETEALLITEMS, 0, 0);
  CurrIndex := Index;
  if CurrIndex = ULONG(-1) then
    CurrIndex := 0
  else if IsVdfsEntryDirectory(Header, Table, CurrIndex) then
    if GetVdfsEntryByIndex(Header, Table, Entry, CurrIndex) then
      CurrIndex := Entry.Offset;
  ItemIndex := 0;
  while GetVdfsEntryByIndex(Header, Table, Entry, CurrIndex) do
  begin
    ZeroMemory(@Item, SizeOf(TLVItem));
    Item.mask := LVIF_TEXT or LVIF_PARAM or LVIF_IMAGE;
    Item.iItem := ItemIndex;
    Item.pszText := Entry.Name;
    Item.iImage := 4;
    Item.lParam := CurrIndex;
    if (Entry.Flags and VDFS_FILE_DIRECTORY = VDFS_FILE_DIRECTORY) then
      Item.iImage := 0;
    ItemIndex := SendMessage(LV, LVM_INSERTITEM, 0, LPARAM(@Item));
    if ItemIndex <> -1 then
    begin
      Item.mask := LVIF_TEXT;
      Item.iItem := ItemIndex;
      Inc(Item.iSubItem);
      IntToStrGrp(Entry.Size, Buffer);
      Item.pszText := Buffer;
      SendMessage(LV, LVM_SETITEM, 0, LPARAM(@Item));
      Inc(Item.iSubItem);
      AttribToStr(Entry.Attrib, Buffer);
      SendMessage(LV, LVM_SETITEM, 0, LPARAM(@Item));
    end;
    Inc(ItemIndex);
    Inc(CurrIndex);
    if (Entry.Flags and VDFS_FILE_LASTENTRY = VDFS_FILE_LASTENTRY) then
      Break;
  end;
end;

procedure TreeViewInsertVdfsEntries(TV: HWND; Root: HTREEITEM;
  const Header: TVdfsHeader; Table: PVdfsTable; Index: ULONG);
var
  CurrIndex: ULONG;
  Entry: TVdfsEntry;
  Item: TTVInsertStruct;
  Node: HTREEITEM;
begin
  CurrIndex := Index;
  while GetVdfsEntryByIndex(Header, Table, Entry, CurrIndex) do
  begin
    if (Entry.Flags and VDFS_FILE_DIRECTORY = VDFS_FILE_DIRECTORY) then
    begin
      ZeroMemory(@Item, SizeOf(TTVInsertStruct));
      Item.hParent := Root;
      Item.hInsertAfter := TVI_LAST;
      Item.item.mask := TVIF_PARAM or TVIF_IMAGE or TVIF_SELECTEDIMAGE or TVIF_TEXT;
      Item.item.lParam := CurrIndex;
      Item.item.iImage := 0;
      Item.item.iSelectedImage := 1;
      Item.item.pszText := Entry.Name;
      Node := HTREEITEM(SendMessage(TV, TVM_INSERTITEM, 0, LPARAM(@Item)));
      if Node <> nil then
      begin
        TreeViewInsertVdfsEntries(TV, Node, Header, Table, Entry.Offset);
        SendMessage(TV, TVM_EXPAND, TVE_EXPAND, LPARAM(Node));
        SendMessage(TV, TVM_EXPAND, TVE_EXPAND, LPARAM(Root));
      end;
    end;
    Inc(CurrIndex);
    if (Entry.Flags and VDFS_FILE_LASTENTRY = VDFS_FILE_LASTENTRY) then
      Break;
  end;
end;

procedure ViewerSetStatus(Dirs, Files, Data: ULONG);
var
  Msg: array [0..4096] of Char;
begin
  Msg[0] := #0;
  if Dirs > 0 then
  begin
    lstrcpy(Msg, 'Directories: ');
    IntToStrGrp(Dirs, @Msg[lstrlen(Msg)]);
  end;
  if Files > 0 then
  begin
    lstrcat(Msg, '  Files: ');
    IntToStrGrp(Files, @Msg[lstrlen(Msg)]);
  end;
  if Data > 0 then
  begin
    lstrcat(Msg, '  Size: ');
    IntToStrGrp(Data, @Msg[lstrlen(Msg)]);
  end;
  {*} SetStatusText(Msg, modeViewer);
end;

procedure FillViewer(Dlg: HWND; Filename: PChar);
var
  Loop: Integer;
  FileTime: TFileTime;
  TempTime: TFileTime;
  SystemTime: TSystemTime;
  Name: PChar;
  Item: TTVInsertStruct;
  TV: HWND;
  Root: HTREEITEM;
  Buffer: array [0..MAX_PATH] of Char;
begin
  Loop := High(TVdfsComment);
  while (Loop >= 0) and (ViewerHeader.Comment[Loop] = VdfsFillByte) do
  begin
    ViewerHeader.Comment[Loop] := #0;
    Dec(Loop);
  end;
  SetDlgItemText(Dlg, IDC_EDITTEXT, ViewerHeader.Comment);
  ZeroMemory(@SystemTime, SizeOf(TSystemTime));
  if DosDateTimeToFileTime(HiWord(ViewerHeader.Params.TimeStamp),
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
  Name := PChar(@Filename[lstrlen(Filename)]);
  while (Name > Filename) and not (Name[-1] in ['\', ':']) do
    Dec(Name);
  lstrcpy(Buffer, Name);
  AnsiUpper(Buffer);
  TV := GetDlgItem(Dlg, IDC_TREEVIEW);
  if TV <> 0 then
  begin
    ZeroMemory(@Item, SizeOf(TTVInsertStruct));
    Item.hInsertAfter := TVI_ROOT;
    Item.item.mask := TVIF_PARAM or TVIF_IMAGE or TVIF_SELECTEDIMAGE or TVIF_TEXT or TVIF_STATE;
    Item.item.lParam := -1;
    Item.item.iImage := 2;
    Item.item.iSelectedImage := 3;
    Item.item.state := TVIS_BOLD;
    Item.item.stateMask := TVIS_BOLD;
    Item.item.pszText := Buffer;
    Root := HTREEITEM(SendMessage(TV, TVM_INSERTITEM, 0, LPARAM(@Item)));
    if Root <> nil then
    begin
      SendMessage(TV, TVM_EXPAND, TVE_EXPAND, LPARAM(Root));
      TreeViewInsertVdfsEntries(TV, Root, ViewerHeader, ViewerTable, 0);
      SendMessage(TV, TVM_SELECTITEM, TVGN_CARET, LPARAM(Root));
    end;
  end;
end;

function OpenVdfs(Dlg: HWND; Filename: PChar): Boolean;
var
  Success: Boolean;
  VdfsFile: THandle;
  VdfsHeader: TVdfsHeader;
  BytesRead: DWORD;
  TableSize: DWORD;
  VdfsTable: PVdfsTable;
  Index: ULONG;
begin
  Success := False;
  if (Filename <> nil) or GetOpenFileName(ViewerOfn) then
  begin
    VdfsTable := nil;
    if Filename <> nil then
      lstrcpy(ViewerNameBuff, Filename);
    OptionsWriteString(OptionsViewerFilename, ViewerNameBuff);
    {*} SetStatusText(PChar('Open volume: ' + string(ViewerNameBuff) + '...'), modeViewer);
    VdfsFile := CreateFile(ViewerNameBuff, GENERIC_READ, FILE_SHARE_READ,
      nil, OPEN_EXISTING, 0, 0);
    if VdfsFile = INVALID_HANDLE_VALUE then
      HandleError(Dlg, 'Cannot Open File for Read Access!')
    else if not (ReadFile(VdfsFile, VdfsHeader, SizeOf(TVdfsHeader), BytesRead, nil) and
      (BytesRead = SizeOf(TVdfsHeader))) then
      HandleError(Dlg, 'Error on Reading File Header!')
    else if SetFilePointer(VdfsFile, VdfsHeader.Params.TableOffset, nil, FILE_BEGIN) = 0 then
      HandleError(Dlg, 'Invalid Table Offset!')
    else if not (((VdfsHeader.Version = VdfsVersionText) or (VdfsHeader.Version = VdfsVersionText2))
      and (VdfsHeader.Params.EntrySize = SizeOf(TVdfsEntry))) then
      HandleError(Dlg, 'Unexpected VDFS Version!')
    else
    begin
      {*} SetStatusText('Getting file table...', modeViewer);
      TableSize := VdfsHeader.Params.EntryCount * SizeOf(TVdfsEntry);
      VdfsTable := GetMemory(TableSize);
      if VdfsTable = nil then
        HandleError(Dlg, 'Error on Allocating Memory for File Table!')
      else if not (ReadFile(VdfsFile, VdfsTable^, TableSize, BytesRead, nil) and
        (BytesRead = TableSize)) then
        HandleError(Dlg, 'Error on Reading File Table!')
      else
      begin
        Success := True;
(**)    // Gothic I Volume
        if (VdfsHeader.Version = VdfsVersionText) then
          for Index := 0 to VdfsHeader.Params.EntryCount - 1 do
            VdfsTable^[Index].Attrib := VdfsTable^[Index].Attrib and not
              VDFS_FILE_ATTRIBUTE_MASK;
(**)
        ResetViewer(Dlg);
        lstrcpy(ViewerFilename, ViewerNameBuff);
        SendMessage(GetDlgItem(Dlg, IDC_EDITFILE), WM_SETTEXT, 0, LPARAM(@ViewerFilename[0]));
        ViewerFile := VdfsFile;
        ViewerHeader := VdfsHeader;
        ViewerTable := VdfsTable;
        FillViewer(Dlg, ViewerFilename);
      end;
    end;
    if not Success then
    begin
      if VdfsFile <> INVALID_HANDLE_VALUE then
        CloseHandle(VdfsFile);
      if VdfsTable <> nil then
        FreeMemory(VdfsTable);
      {*} SetStatusText(nil, modeViewer);
    end
    else with ViewerHeader.Params do
      {*} ViewerSetStatus(EntryCount - FileCount, FileCount, DataSize);
  end;
  Result := Success;
end;

end.

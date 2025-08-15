program GothicVDFS;

{$R 'res\Resource.res' 'res\Resource.rc'}

uses
  Windows,
  Messages,
  CommCtrl,
  CommDlg,
  RichEdit,
  VdfsDef in 'VdfsDef.pas',
  GothicVdfsGlob in 'GothicVdfsGlob.pas',
  GothicVdfsUtil in 'GothicVdfsUtil.pas',
  GothicVdfsViewer in 'GothicVdfsViewer.pas',
  GothicVdfsBuilder in 'GothicVdfsBuilder.pas',
  GothicVdfsHint in 'GothicVdfsHint.pas';

function MainFormInitDialog(Dlg: HWND): BOOL; forward;
function MainFormClose(Dlg: HWND; Return: Integer): BOOL; forward;
function MainFormDestroy(Dlg: HWND): BOOL; forward;
{$IFDEF USECOLORS}
function MainFormCtlColor(Dlg: HWND; Msg: UINT; WParam: HDC): HBRUSH; forward;
{$ENDIF}
function MainFormCommand(Dlg: HWND; NotifyCode, ID: Word; Ctl: HWND): BOOL; forward;
function MainFormNotify(Dlg: HWND; CtrlId: Integer; Header: PNMHdr): BOOL; forward;
function MainFormOpenFile(Dlg: HWND; FileType: TGothicFileType; Auto: Boolean): BOOL; forward;

var
  AutoFileName: array [0..MAX_PATH] of Char;

const
  AutoTimeout = 10000;
  WM_OPENFILE = WM_USER + 531;

function MainFormDlgProc(Dlg: HWND; Msg: UINT; WParam: WPARAM; LParam: LPARAM): BOOL; stdcall;
begin
  case Msg of
    WM_INITDIALOG:
      Result := MainFormInitDialog(Dlg);
    WM_CLOSE:
      Result := MainFormClose(Dlg, 0);
    WM_DESTROY:
      Result := MainFormDestroy(Dlg);
{$IFDEF USECOLORS}
    WM_CTLCOLORMSGBOX..WM_CTLCOLORSTATIC:
      Result := BOOL(MainFormCtlColor(Dlg, Msg, HDC(WParam)));
{$ENDIF}
    WM_COMMAND:
      Result := MainFormCommand(Dlg, HiWord(WParam), LoWord(WParam), HWND(LParam));
    WM_NOTIFY:
      Result := MainFormNotify(Dlg, WParam, PNMHdr(LParam));
    WM_OPENFILE:
      Result := MainFormOpenFile(Dlg, TGothicFileType(WParam), Boolean(LParam));
  else
    Result := False;
  end;
end;

function MainFormInitDialog(Dlg: HWND): BOOL;
{$IFDEF USECOLORS}
const
  TVM_SETLINECOLOR = TV_FIRST + 40;
{$ENDIF}
var
  TV: HWND;
  LV: HWND;
  Bmp: HBITMAP;
  Lst: HIMAGELIST;
  Prm: Char;
{$IFDEF USECOLORS}
  Prog: HWND;
{$ENDIF}
begin
  if not AutoExtractVolume then
    MainFormStatus := CreateStatusWindow(WS_CHILD or WS_VISIBLE, nil, Dlg, IDC_MAINSTAT);
  ViewerOfn.hWndOwner := Dlg;
  BuilderOfn.hWndOwner := Dlg;
  ListOfn.hWndOwner := Dlg;
  OpenScriptOfn.hWndOwner := Dlg;
  SaveScriptOfn.hWndOwner := Dlg;
  SendMessage(Dlg, WM_SETICON, ICON_BIG, LPARAM(LoadIcon(HInstance, IDI_MAINICON)));
  SetRicheditProp(Dlg, IDC_EDITFILE, True, MAX_PATH);
  SetRicheditProp(Dlg, IDC_EDITROOT, True, MAX_PATH);
  SetRicheditProp(Dlg, IDC_EDITTEXT, True, SizeOf(TVdfsComment) - 1);
  SendDlgItemMessage(Dlg, IDC_SPINYEAR, UDM_SETRANGE, 0, LPARAM(MakeLong(2039, 1980)));
  SendDlgItemMessage(Dlg, IDC_SPINMONTH, UDM_SETRANGE, 0, LPARAM(MakeLong(12, 1)));
  SendDlgItemMessage(Dlg, IDC_SPINDAY, UDM_SETRANGE, 0, LPARAM(MakeLong(31, 1)));
  SendDlgItemMessage(Dlg, IDC_SPINHOUR, UDM_SETRANGE, 0, LPARAM(MakeLong(23, 0)));
  SendDlgItemMessage(Dlg, IDC_SPINMIN, UDM_SETRANGE, 0, LPARAM(MakeLong(59, 0)));
  SendDlgItemMessage(Dlg, IDC_SPINSEC, UDM_SETRANGE, 0, LPARAM(MakeLong(59, 0)));
  CheckDlgButton(Dlg, IDC_CHECKUTC, BST_CHECKED);
  CheckDlgButton(Dlg, IDC_CHECKFULL, BST_CHECKED);
  CheckDlgButton(Dlg, IDC_CHECKFILES, BST_CHECKED);
  CheckDlgButton(Dlg, IDC_CHECKEX, BST_CHECKED);
  CheckDlgButton(Dlg, IDC_CHECKIN, BST_CHECKED);
  CheckDlgButton(Dlg, IDC_CHECKSORT, BST_CHECKED);
  TV := GetDlgItem(Dlg, IDC_TREEVIEW);
  LV := GetDlgItem(Dlg, IDC_LISTVIEW);
{$IFDEF USECOLORS}
  SendMessage(TV, TVM_SETBKCOLOR, 0, DialogBackColor);
  SendMessage(TV, TVM_SETTEXTCOLOR, 0, DialogTextColor);
  SendMessage(TV, TVM_SETLINECOLOR, 0, DialogTextColor);
  SetListViewColor(Dlg, IDC_LISTVIEW);
  Prog := GetDlgItem(Dlg, IDC_PROGVIEW);
  SendMessage(Prog, PBM_SETBKCOLOR, 0, DialogBackColor);
  SendMessage(Prog, PBM_SETBARCOLOR, 0, DialogTextColor);
  Prog := GetDlgItem(Dlg, IDC_PROGBUILD);
  SendMessage(Prog, PBM_SETBKCOLOR, 0, DialogBackColor);
  SendMessage(Prog, PBM_SETBARCOLOR, 0, DialogTextColor);
  SetListViewColor(Dlg, IDC_LISTFILES);
  SetListViewColor(Dlg, IDC_LISTEX);
  SetListViewColor(Dlg, IDC_LISTIN);
  SendMessage(MainFormStatus, SB_SETBKCOLOR, 0, DialogBackColor);
{$ENDIF}
  Bmp := LoadBitmap(HInstance, IDB_FOLDER);
  if Bmp <> 0 then
  begin
    Lst := ImageList_Create(16, 16, ILC_MASK or ILC_COLOR16, 5, 5);
    if Lst <> 0 then
    begin
      ImageList_AddMasked(Lst, Bmp, $00FF00FF);
      ImageList_SetBkColor(Lst, CLR_NONE);
      SendMessage(TV, TVM_SETIMAGELIST, 0, Lst);
      SendMessage(LV, LVM_SETIMAGELIST, LVSIL_SMALL, Lst);
    end;
    DeleteObject(Bmp);
  end;
  InsertListViewColumn(Dlg, IDC_LISTVIEW, 0, 'Filename', 0, 100 + 60 + 4);
  InsertListViewColumn(Dlg, IDC_LISTVIEW, 1, 'Size', 100, 0, LVCFMT_RIGHT);
  InsertListViewColumn(Dlg, IDC_LISTVIEW, 2, 'Attributes', 60, 0, LVCFMT_RIGHT);
  InsertListViewColumn(Dlg, IDC_LISTFILES, 0, 'File(mask)(s) to search for', 0, 2);
  InsertListViewColumn(Dlg, IDC_LISTEX, 0, 'File(mask)(s) to exclude', 0, 2);
  InsertListViewColumn(Dlg, IDC_LISTIN, 0, 'File(mask)(s) to include', 0, 2);

  // Options Viewer
  if (not OptionsReadString(OptionsViewerFilename, ViewerNameBuff, SizeOf(ViewerNameBuff))) or (not FileExists(ViewerNameBuff)) then
    ViewerNameBuff[0] := #0;
  if OptionsReadString(OptionsViewerRootpath, ViewerRoot, SizeOf(ViewerRoot)) and FileExists(ViewerRoot) then
    SetDlgItemText(Dlg, IDC_EDITROOT, ViewerRoot)
  else
    ViewerRoot[0] := #0;
  // Options Builder
  if (not OptionsReadString(OptionsBuilderFilename, BuilderNameBuff, SizeOf(BuilderNameBuff))) or (not FileExists(BuilderNameBuff)) then
    BuilderNameBuff[0] := #0;
  if (not OptionsReadString(OptionsBuilderRootpath, BuilderRoot, SizeOf(BuilderRoot))) or (not FileExists(BuilderRoot)) then
    BuilderRoot[0] := #0;
  if (not OptionsReadString(OptionsBuilderScriptname, ScriptNameBuff, SizeOf(ScriptNameBuff))) or (not FileExists(ScriptNameBuff)) then
    ScriptNameBuff[0] := #0;

  InitToolTips(Dlg);
  SwitchModeToolTip(modeViewer);

  // Parameter parsing
  if (ParamCount = 1) and FileExists(PChar(ParamStr(1))) then
  begin
    lstrcpy(AutoFileName, PChar(ParamStr(1)));
    case DetectGothicFileType(AutoFileName) of
      gftVolume:
        PostMessage(Dlg, WM_OPENFILE, WPARAM(gftVolume), LPARAM(False));
      gftScript:
        PostMessage(Dlg, WM_OPENFILE, WPARAM(gftScript), LPARAM(False));
    end;
  end
  else if (ParamCount >= 2) and (Length(ParamStr(1)) = 2) then
  begin
    Prm := ParamStr(1)[2];
    case Prm of
      'B', 'b':
        begin
          SwitchMode(Dlg, modeBuilder);
          if FileExists(PChar(ParamStr(2))) then
          begin
            lstrcpy(AutoFileName, PChar(ParamStr(2)));
            if DetectGothicFileType(AutoFileName) = gftScript then
              PostMessage(Dlg, WM_OPENFILE, WPARAM(gftScript), LPARAM(True));
          end;
        end;
      'X', 'x':
        begin
          SwitchMode(Dlg, modeViewer);
          if FileExists(PChar(ParamStr(2))) then
          begin
            lstrcpy(AutoFileName, PChar(ParamStr(2)));
            GetCurrentDirectory(SizeOf(ViewerRoot), ViewerRoot);
            if (ParamCount >= 3) then
              if SetCurrentDirectory(PChar(ParamStr(3))) then
                GetCurrentDirectory(SizeOf(ViewerRoot), ViewerRoot)
              else
              begin
                MessageBox(0, 'Invalid Parameter (root)!', 'GothicVDFS', MB_OK or MB_ICONERROR);
                ExitProcess(1);
              end;
            SetDlgItemText(Dlg, IDC_EDITROOT, ViewerRoot);
            if DetectGothicFileType(AutoFileName) = gftVolume then
              PostMessage(Dlg, WM_OPENFILE, WPARAM(gftVolume), LPARAM(True));
          end;
        end;
    end;
  end;

  Result := False;
  // FIXME
//SetFocus(GetDlgItem(Dlg, IDC_BTNFILE));
  SetFocus(GetDlgItem(Dlg, IDC_BTNVOL));
end;

function MainFormClose(Dlg: HWND; Return: Integer): BOOL;
begin
  Result := BOOL(1);
  if AutoExtractVolume and (AutoExtractErrors <> 0) then
    ExitProcess(1);
  if ViewerWorkInProgress or BuilderWorkInProgress then
  begin
    if MessageBox(Dlg, 'Do you want to terminate the program?',
      'Work is in progress!', MB_YESNO or MB_ICONQUESTION or MB_DEFBUTTON2) = IDYES then
    begin
      Result := BOOL(0);
      if ViewerWorkInProgress or BuilderWorkInProgress then
        ExitProcess(1);
      EndDialog(Dlg, Return);
    end;
  end
  else
    EndDialog(Dlg, Return);
end;

function MainFormDestroy(Dlg: HWND): BOOL;
begin
  Result := BOOL(0);
{$IFDEF USECOLORS}
  if EditBrush <> 0 then
    DeleteObject(EditBrush);
  if DialogBrush <> 0 then
    DeleteObject(DialogBrush);
{$ENDIF}
  ResetViewer(Dlg);
end;

{$IFDEF USECOLORS}
function MainFormCtlColor(Dlg: HWND; Msg: UINT; WParam: HDC): HBRUSH;
begin
  case Msg of
    WM_CTLCOLOREDIT:
      begin
        SetTextColor(WParam, EditTextColor);
        SetBkColor(WParam, EditBackColor);
        if EditBrush = 0 then
          EditBrush := CreateBrushIndirect(EditLogBrush);
        Result := EditBrush;
      end;
  else
    SetTextColor(WParam, DialogTextColor);
    SetBkColor(WParam, DialogBackColor);
    if DialogBrush = 0 then
      DialogBrush := CreateBrushIndirect(DialogLogBrush);
    Result := DialogBrush;
  end;
end;
{$ENDIF}

function MainFormCommand(Dlg: HWND; NotifyCode, ID: Word; Ctl: HWND): BOOL;
var
  Filename: array [0..MAX_PATH] of Char;
  SysTime: TSystemTime;
  CurrTime: TFileTime;
  ConvTime: TFileTime;
  LV: HWND;
  LVItem: TLVItem;
  TV: HWND;
  Item: HTREEITEM;
  Data: TTVItem;
  Entry: TVdfsEntry;
  Info: TMsgBoxParams;
  Dirs: ULONG;
  Files: ULONG;
begin
  Result := BOOL(0);
  if Ctl <> 0 then
  begin
    if NotifyCode = BN_CLICKED then
    begin
      case ID of
        IDC_BTNEXIT:
          MainFormClose(Dlg, 0);
        IDC_BTNFILE:
          if CurrDlgMode = modeViewer then
            OpenVdfs(Dlg, nil)
          else
            SelectModFilename(Dlg, nil);
        IDC_BTNROOT:
          if CurrDlgMode = modeViewer then
          begin
            if SelectDirectory(Dlg, Filename, 'Extract base directory :', ViewerRoot) then
            begin
              lstrcpy(ViewerRoot, Filename);
              SetDlgItemText(Dlg, IDC_EDITROOT, Filename);
              OptionsWriteString(OptionsViewerRootpath, Filename);
            end;
          end
          else if CurrDlgMode = modeBuilder then
          begin
            if SelectDirectory(Dlg, Filename, 'Base directory for search:', BuilderRoot) then
            begin
              lstrcpy(BuilderRoot, Filename);
              SetDlgItemText(Dlg, IDC_EDITROOT, Filename);
              OptionsWriteString(OptionsBuilderRootpath, Filename);
            end;
          end;
        IDC_CHECKUTC:
          begin
            Result := BOOL(-1);
            ReadTime(Dlg, SysTime);
            if SystemTimeToFileTime(SysTime, CurrTime) then
            begin
              if IsDlgButtonChecked(Dlg, ID) = BST_CHECKED then
                LocalFileTimeToFileTime(CurrTime, ConvTime)
              else
                FileTimeToLocalFileTime(CurrTime, ConvTime);
              if FileTimeToSystemTime(ConvTime, SysTime) then
              begin
                DisplayTime(Dlg, SysTime);
                Result := BOOL(0);
              end;
            end;
            if Ord(Result) <> 0 then
              if IsDlgButtonChecked(Dlg, ID) = BST_CHECKED then
                CheckDlgButton(Dlg, ID, BST_UNCHECKED)
              else
                CheckDlgButton(Dlg, ID, BST_CHECKED);
          end;
        IDC_BTNVOL:
          SaveVdfsVolumeToDisk(Dlg, ViewerFile, ViewerHeader, ViewerTable, ViewerRoot);
        IDC_BTNNODE:
          begin
            TV := GetDlgItem(Dlg, IDC_TREEVIEW);
            if TV <> 0 then
            begin
              Item := HTREEITEM(SendMessage(TV, TVM_GETNEXTITEM, TVGN_CARET, LPARAM(nil)));
              if Item = nil then
                MessageBox(Dlg, 'No directory selected.', nil, 0)
              else
              begin
                ZeroMemory(@Data, SizeOf(TTVItem));
                Data.hItem := Item;
                Data.mask := TVIF_PARAM;
                if BOOL(SendMessage(TV, TVM_GETITEM, 0, LPARAM(@Data))) then
                begin
                  if Data.lParam = -1 then
                    SaveVdfsVolumeToDisk(Dlg, ViewerFile, ViewerHeader, ViewerTable, ViewerRoot)
                  else if GetVdfsEntryByIndex(ViewerHeader, ViewerTable, Entry, Data.lParam) then
                  begin
                    Filename[0] := #0;
                    if IsDlgButtonChecked(Dlg, IDC_CHECKFULL) = BST_CHECKED then
                      GetSelectedPath(Dlg, Filename);
                    Dirs := 0;
                    Files := 0;
                    InitProgress(Dlg, Integer(GetVdfsDataSize(ViewerHeader, ViewerTable, Entry.Offset
                      Dirs, Files)), modeViewer);
                    EnableViewer(Dlg, False);
                    SaveVdfsDirectoryToDisk(Dlg, ViewerFile, ViewerHeader, ViewerTable,
                      Entry.Offset, ViewerRoot, Filename);
                    EnableViewer(Dlg, True);
                    InitProgress(Dlg, 1, modeViewer);
                  end;
                end;
              end;
            end;
          end;
        IDC_BTNSEL:
          begin
            EnableViewer(Dlg, False, False);
            ExtractSelectedVdfsEntries(Dlg, GetDlgItem(Dlg, IDC_LISTVIEW),
              ViewerHeader, ViewerTable, ViewerFile,
              IsDlgButtonChecked(Dlg, IDC_CHECKFULL) = BST_CHECKED);
            EnableViewer(Dlg, True);
          end;
        IDC_BTNFILES1, IDC_BTNEX1, IDC_BTNIN1:
          if GetDlgItemText(Dlg, ID - (IDC_BTNFILES1 - IDC_EDITFILES), Filename, MAX_PATH) > 0 then
          begin
            LV := GetDlgItem(Dlg, ID + IDC_LISTFILES - IDC_BTNFILES1);
            if LV <> 0 then
            begin
              ZeroMemory(@LVItem, SizeOf(TLVItem));
              LVItem.iItem := SendMessage(LV, LVM_GETNEXTITEM, -1, MakeLParam(LVNI_SELECTED, 0));
              if LVItem.iItem = -1 then
                LVItem.iItem := SendMessage(LV, LVM_GETITEMCOUNT, 0, 0);
              LVItem.mask := LVIF_TEXT or LVIF_PARAM;
              LVItem.pszText := Filename;
              LVItem.lParam := Ord(
                IsDlgButtonChecked(Dlg, ID + IDC_CHECKFILES - IDC_BTNFILES1) = BST_CHECKED);
              SendMessage(LV, LVM_INSERTITEM, 0, LPARAM(@LVItem));
            end;
          end;
        IDC_BTNFILES2, IDC_BTNEX2, IDC_BTNIN2:
          if GetDlgItemText(Dlg, ID - (IDC_BTNFILES2 - IDC_EDITFILES), Filename, MAX_PATH) > 0 then
          begin
            LV := GetDlgItem(Dlg, ID + IDC_LISTFILES - IDC_BTNFILES2);
            if LV <> 0 then
            begin
              ZeroMemory(@LVItem, SizeOf(TLVItem));
              LVItem.iItem := SendMessage(LV, LVM_GETNEXTITEM, -1, MakeLParam(LVNI_SELECTED, 0));
              if LVItem.iItem <> -1 then
              begin
                SendMessage(LV, LVM_DELETEITEM, LVItem.iItem, 0);
                LVItem.state := LVIS_SELECTED;
                LVItem.stateMask := LVIS_SELECTED;
                SendMessage(LV, LVM_SETITEMSTATE, LVItem.iItem, LPARAM(@LVItem));
              end;
            end;
          end;
        IDC_BTNFILES3, IDC_BTNEX3, IDC_BTNIN3:
          if GetDlgItemText(Dlg, ID - (IDC_BTNFILES3 - IDC_EDITFILES), Filename, MAX_PATH) > 0 then
          begin
            LV := GetDlgItem(Dlg, ID + IDC_LISTFILES - IDC_BTNFILES3);
            if LV <> 0 then
            begin
              ZeroMemory(@LVItem, SizeOf(TLVItem));
              LVItem.iItem := SendMessage(LV, LVM_GETNEXTITEM, -1, MakeLParam(LVNI_SELECTED, 0));
              if LVItem.iItem >= 0 then
              begin
                LVItem.mask := LVIF_TEXT or LVIF_PARAM;
                LVItem.pszText := Filename;
                LVItem.lParam := Ord(
                  IsDlgButtonChecked(Dlg, ID + IDC_CHECKFILES - IDC_BTNFILES3) = BST_CHECKED);
                SendMessage(LV, LVM_SETITEM, 0, LPARAM(@LVItem));
              end;
            end;
          end;
        IDC_BTNFILES4, IDC_BTNEX4, IDC_BTNIN4:
          begin
            if GetSaveFileName(ListOfn) then
            begin
              if (lstrcpyn(Filename, ListNameBuff, lstrlen(BuilderRoot) + 1) <> nil) and
                (lstrcmpi(Filename, BuilderRoot) <> 0) then
                MessageBox(Dlg, 'Seleted file(mask) is not in root', nil, 0)
              else
              begin
                AppendBackSlash(Filename);
                SetDlgItemText(Dlg, ID - (IDC_BTNFILES4 - IDC_EDITFILES), @ListNameBuff[lstrlen(Filename)]);
              end;
            end;
          end;
        IDC_BTNOPEN:
          ReadModScript(Dlg, nil);
        IDC_BTNSAVE:
          SaveModScript(Dlg, nil);
        IDC_BTNBUILD:
          begin
            EnableBuilder(Dlg, False);
            BuildMod(Dlg, nil);
            EnableBuilder(Dlg, True);
          end;
        IDC_CHECKSORT:
          if IsDlgButtonChecked(Dlg, IDC_CHECKSORT) = BST_CHECKED then
            BuilderSortLits := True
          else
            BuilderSortLits := False;
        IDC_BTNINFO:
          MainFormCommand(Dlg, 0, ID_MENUINFO, 0);
      else
        Result := BOOL(1);
      end;
    end
    else
      Result := BOOL(1);
  end
  else
  begin
    case ID of
      ID_MENUVIEW:
        SwitchMode(Dlg, modeViewer);
      ID_MENUMODS:
        SwitchMode(Dlg, modeBuilder);
      ID_MENUINFO:
        begin
          ZeroMemory(@Info, SizeOf(TMsgBoxParams));
          Info.cbSize := SizeOf(TMsgBoxParams);
          Info.hwndOwner := Dlg;
          Info.hInstance := HInstance;
{$IFDEF MODKIT}
          Info.lpszText := 'GothicVDFS 2.6 (mod)    '#13#10#13#10 +
            'Extract/Build VDFS Volumes for Gothic II     '#13#10 +
            #169' 2003 Nico Bendlin <nicode@gmx.net>     '#13#10;
{$ELSE}
          Info.lpszText := 'GothicVDFS 2.6    '#13#10#13#10 +
            '(for internal usage only)     '#13#10 +
            #169' 2003 Nico Bendlin <nicode@gmx.net>     '#13#10;
{$ENDIF}
          Info.lpszCaption := 'About';
          Info.dwStyle := MB_USERICON;
          Info.lpszIcon := IDI_MAINICON;
          MessageBoxIndirect(Info);
        end;
    end;
  end;
end;

function MainFormNotify(Dlg: HWND; CtrlId: Integer; Header: PNMHdr): BOOL;
var
  LVItem: TLVItem;
  TV: HWND;
  TVItem: TTVItem;
  Node: HTREEITEM;
  Index: Integer;
  Buffer: array [0..MAX_PATH] of Char;
  Entry: TVdfsEntry;
  Dirs: ULONG;
  Files: ULONG;
  Data: ULONG;
begin
  Result := BOOL(0);
  case CtrlId of
    IDC_TREEVIEW:
      if Header.code = TVN_SELCHANGED then
      begin
        ListViewInsertVdfsEntries(GetDlgItem(Dlg, IDC_LISTVIEW), ViewerHeader,
          ViewerTable, PNMTreeView(Header).itemNew.lParam);
        if PNMTreeView(Header).itemNew.lParam = -1 then
          with ViewerHeader.Params do
            ViewerSetStatus(EntryCount - FileCount, FileCount, DataSize)
        else if GetVdfsEntryByIndex(ViewerHeader, ViewerTable, Entry,
          ULONG(PNMTreeView(Header).itemNew.lParam)) then
        begin
          Dirs := 0;
          Files := 0;
          Data := GetVdfsDataSize(ViewerHeader, ViewerTable, Entry.Offset, Dirs, Files);
          ViewerSetStatus(Dirs, Files, Data);
        end
        else
          ViewerSetStatus(0, 0, 0);
      end;
    IDC_LISTVIEW:
      if Header.code = NM_DBLCLK then
      begin
        ZeroMemory(@LVItem, SizeOf(TLVItem));
        LVItem.iItem := SendMessage(Header.hwndFrom, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
        LVItem.mask := LVIF_PARAM;
        TV := GetDlgItem(Dlg, IDC_TREEVIEW);
        if (LVItem.iItem <> -1) and (SendMessage(Header.hwndFrom, LVM_GETITEM, 0,
          LPARAM(@LVItem)) <> -1) and (TV <> 0) then
        begin
          Node := HTREEITEM(SendMessage(TV, TVM_GETNEXTITEM, TVGN_CARET, LPARAM(nil)));
          if Node <> nil then
            Node := HTREEITEM(SendMessage(TV, TVM_GETNEXTITEM, TVGN_CHILD, LPARAM(Node)));
          while Node <> nil do
          begin
            ZeroMemory(@TVItem, SizeOf(TTVItem));
            TVItem.mask := TVIF_HANDLE;
            TVItem.hItem := Node;
            if BOOL(SendMessage(TV, TVM_GETITEM, 0, LPARAM(@TVItem))) then
              if TVItem.lParam = LVItem.lParam then
              begin
                SendMessage(TV, TVM_SELECTITEM, TVGN_CARET, LPARAM(Node));
                Break;
              end;
            Node := HTREEITEM(SendMessage(TV, TVM_GETNEXTITEM, TVGN_NEXT, LPARAM(Node)));
          end;
        end;
      end;
    IDC_LISTFILES, IDC_LISTEX, IDC_LISTIN:
      if SendMessage(Header.hwndFrom, LVM_GETSELECTEDCOUNT, 0, 0) > 0 then
      begin
        Index := SendMessage(Header.hwndFrom, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
        Buffer[0] := #0;
        ZeroMemory(@LVItem, SizeOf(TLVItem));
        LVItem.mask := LVIF_TEXT or LVIF_PARAM;
        LVItem.iItem := Index;
        LVItem.pszText := @Buffer[0];
        LVItem.cchTextMax := SizeOf(Buffer);
        if SendMessage(Header.hwndFrom, LVM_GETITEM, 0, LPARAM(@LVItem)) > 0 then
        begin
          SetDlgItemText(Dlg, CtrlId - (IDC_LISTFILES - IDC_EDITFILES), Buffer);
          CheckDlgButton(Dlg, CtrlId - (IDC_LISTFILES - IDC_CHECKFILES), LVItem.lParam);
        end;
      end;
  end;
end;

function MainFormOpenFile(Dlg: HWND; FileType: TGothicFileType; Auto: Boolean): BOOL;
begin
  Result := False;
  if AutoFileName[0] <> #0 then
  begin
    case FileType of
      gftVolume:
        begin
          SwitchMode(Dlg, modeViewer);
          if OpenVdfs(Dlg, AutoFileName) then
            if Auto then
            begin
              EnableExit(Dlg, False);
              EnableBuilder(Dlg, False);
              Result := SaveVdfsVolumeToDisk(Dlg, ViewerFile, ViewerHeader, ViewerTable, ViewerRoot);
              EnableBuilder(Dlg, True);
              EnableExit(Dlg, True);
              if Result and (AutoExtractErrors = 0) then
                ExitProcess(0);
            end
            else
              Result := True;
        end;
      gftScript:
        begin
          SwitchMode(Dlg, modeBuilder);
          if ReadModScript(Dlg, AutoFileName) then
            if Auto then
            begin
              EnableExit(Dlg, False);
              EnableViewer(Dlg, False);
              Result := BuildMod(Dlg, BuilderFilename);
              EnableViewer(Dlg, True);
              EnableExit(Dlg, True);
              if Result then
                SendMessage(Dlg, WM_CLOSE, 0, 0);
            end
            else
              Result := True;
        end;
    end;
    AutoFileName[0] := #0;
  end;
end;

const
  RichEditLibName = 'riched32.dll';

var
  InitCtrls: TInitCommonControlsEx = (
    dwSize: SizeOf(TInitCommonControlsEx);
    dwICC : ICC_TREEVIEW_CLASSES or ICC_LISTVIEW_CLASSES or ICC_UPDOWN_CLASS or
      ICC_PROGRESS_CLASS;
  );

var
  Prm: Char;
begin
  LoadLibrary(RichEditLibName);
  InitCommonControls();
  InitCommonControlsEx(InitCtrls);
  AutoExtractVolume := False;
  if (ParamCount >= 2) and (Length(ParamStr(1)) = 2) then
  begin
    Prm := ParamStr(1)[2];
    case Prm of
      'X', 'x':
        if FileExists(PChar(ParamStr(2))) and
          (DetectGothicFileType(PChar(ParamStr(2))) = gftVolume) then
          AutoExtractVolume := True
        else
        begin
          MessageBox(0, 'Invalid Parameter (file)!', 'GothicVDFS', MB_OK or MB_ICONERROR);
          ExitProcess(1);
        end;
    end;
  end;
  if AutoExtractVolume then
  begin
    DialogBoxParam(HInstance, IDD_XVOLFORM, 0, @MainFormDlgProc, 0);
    ExitProcess(0);
  end;
  ExitCode := DialogBoxParam(HInstance, IDD_MAINFORM, 0, @MainFormDlgProc, 0);
end.


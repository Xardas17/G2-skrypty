unit GothicVdfsHint;

interface

uses
  Windows, Messages, CommCtrl,
  GothicVdfsGlob;

function InitToolTips(Dlg: HWND): Boolean;
procedure SwitchModeToolTip(Mode: TVdfsDialogMode);

implementation

type
  PToolTipListEntry = ^TToolTipListEntry;
  TToolTipListEntry = record
    Ctl: Integer;
    Tip: PChar;
  end;

const
  GeneralToolTipList: array [0..7] of TToolTipListEntry = (
    (Ctl: IDC_EDITYEAR ; Tip: 'Year.'),
    (Ctl: IDC_EDITMONTH; Tip: 'Month.'),
    (Ctl: IDC_EDITDAY  ; Tip: 'Day.'),
    (Ctl: IDC_EDITHOUR ; Tip: 'Hour.'),
    (Ctl: IDC_EDITMIN  ; Tip: 'Minutes.'),
    (Ctl: IDC_EDITSEC  ; Tip: 'Seconds (only even--because it is an MS-DOS timestamp).'),
    (Ctl: IDC_CHECKUTC ; Tip: 'Toogle between UTC and your locale time (display only).'),
    (Ctl: IDC_EDITBINFO; Tip: nil)
  );

const
  ViewerToolTipList: array [0..13] of TToolTipListEntry = (
    (Ctl: IDC_EDITFILE ; Tip: 'Filename of the selected volume.'),
    (Ctl: IDC_BTNFILE  ; Tip: 'Open the volume file to view/extract from.'),
    (Ctl: IDC_EDITROOT ; Tip: 'Base directory for extracted files.'),
    (Ctl: IDC_BTNROOT  ; Tip: 'Choose base directory for extracting files.'),
    (Ctl: IDC_EDITTEXT ; Tip: 'Volume comment.'),
    (Ctl: IDC_TREEVIEW ; Tip: nil),
    (Ctl: IDC_LISTVIEW ; Tip: nil),
    (Ctl: IDC_BTNVOL   ; Tip: 'Extract the whole volume to disk.'),
    (Ctl: IDC_BTNNODE  ; Tip: 'Extract selected directory (with all subdirectories).'),
    (Ctl: IDC_BTNSEL   ; Tip: 'Extract selected files in list (directories will be created only).'),
    (Ctl: IDC_CHECKFULL; Tip: 'Toogle between relative and absolute path (always under root).'),
    (Ctl: IDC_PROGVIEW ; Tip: nil),

    (Ctl: 0; Tip: ''),
    (Ctl: 0; Tip: '')
  );

const
  BuilderButton1Text = 'Add the filename/mask to the list.';
  BuilderButton2Text = 'Remove the selected entry from the list.';
  BuilderButton3Text = 'Update the selected entry in the list.';
  BuilderButton4Text = 'Open an dialog to choose an filename/mask.';
  BuilderCheckRText  = 'Toogle between recursive or not.';

const
  BuilderToolTipList: array [0..30] of TToolTipListEntry = (
    (Ctl: IDC_EDITFILE  ; Tip: 'Name of the volume file to create.'),
    (Ctl: IDC_BTNFILE   ; Tip: 'Choose the filename of the volume to create.'),
    (Ctl: IDC_EDITROOT  ; Tip: 'Base directory for search and root of the volume.'),
    (Ctl: IDC_BTNROOT   ; Tip: 'Choose base directory for file search (root of the volume too).'),
    (Ctl: IDC_EDITTEXT  ; Tip: 'Volume comment (%%D will be replaced with the Timestamp as text.'),
    (Ctl: IDC_EDITFILES ; Tip: nil),
    (Ctl: IDC_BTNFILES1 ; Tip: BuilderButton1Text),
    (Ctl: IDC_BTNFILES2 ; Tip: BuilderButton2Text),
    (Ctl: IDC_BTNFILES3 ; Tip: BuilderButton3Text),
    (Ctl: IDC_BTNFILES4 ; Tip: BuilderButton4Text),
    (Ctl: IDC_CHECKFILES; Tip: BuilderCheckRText),
    (Ctl: IDC_LISTFILES ; Tip: 'List of files/masks to add to the volume.'),
    (Ctl: IDC_EDITEX    ; Tip: nil),
    (Ctl: IDC_BTNEX1    ; Tip: BuilderButton1Text),
    (Ctl: IDC_BTNEX2    ; Tip: BuilderButton2Text),
    (Ctl: IDC_BTNEX3    ; Tip: BuilderButton3Text),
    (Ctl: IDC_BTNEX4    ; Tip: BuilderButton4Text),
    (Ctl: IDC_CHECKEX   ; Tip: BuilderCheckRText),
    (Ctl: IDC_LISTEX    ; Tip: 'List of files/masks to exclude from the volume (overrides add-list).'),
    (Ctl: IDC_EDITIN    ; Tip: nil),
    (Ctl: IDC_BTNIN1    ; Tip: BuilderButton1Text),
    (Ctl: IDC_BTNIN2    ; Tip: BuilderButton2Text),
    (Ctl: IDC_BTNIN3    ; Tip: BuilderButton3Text),
    (Ctl: IDC_BTNIN4    ; Tip: BuilderButton4Text),
    (Ctl: IDC_CHECKIN   ; Tip: BuilderCheckRText),
    (Ctl: IDC_LISTIN    ; Tip: 'List of files/masks to include explicit (overrides exclude-list).'),
    (Ctl: IDC_BTNOPEN   ; Tip: 'Load parameters from saved script file.'),
    (Ctl: IDC_BTNSAVE   ; Tip: 'Save current parameters to an script file.'),
    (Ctl: IDC_BTNBUILD  ; Tip: 'Search and build the MOD file.'),
    (Ctl: IDC_PROGBUILD ; Tip: nil),
    (Ctl: IDC_CHECKSORT ; Tip: 'Toogle file list sorting after search (recommend).')
  );

function CreateToolTip(Dlg: HWND; out ToolTip: HWND): Boolean;
begin
  Result := False;
  ToolTip := CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, nil,
    WS_POPUP or TTS_NOPREFIX or TTS_ALWAYSTIP, Integer(CW_USEDEFAULT),
    Integer(CW_USEDEFAULT), Integer(CW_USEDEFAULT), Integer(CW_USEDEFAULT),
    Dlg, 0, HInstance, nil);
  if ToolTip <> 0 then
  begin
    SetWindowPos(ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE or SWP_NOSIZE or SWP_NOACTIVATE);
    Result := True;
  end;
end;

var
  GeneralToolTipWnd: HWND;
  ViewerToolTipWnd: HWND;
  BuilderToolTipWnd: HWND;

function InitToolTips(Dlg: HWND): Boolean;
var
  ToolInfo: TToolInfo;
  Loop: Integer;
  Rect: TRect;
begin
  Result := False;
  if CreateToolTip(Dlg, GeneralToolTipWnd) and
    CreateToolTip(Dlg, ViewerToolTipWnd) and
    CreateToolTip(Dlg, BuilderToolTipWnd) then
  begin
    ZeroMemory(@ToolInfo, SizeOf(TToolInfo));
    ToolInfo.cbSize := SizeOf(TToolInfo);
    ToolInfo.uFlags := TTF_SUBCLASS;
    ToolInfo.hInst := HInstance;
    for Loop := 0 to High(GeneralToolTipList) do
    begin
      ToolInfo.hwnd := GetDlgItem(Dlg, GeneralToolTipList[Loop].Ctl);
      if (GeneralToolTipList[Loop].Tip <> nil) and (ToolInfo.hwnd <> 0) and
        GetClientRect(ToolInfo.hwnd, Rect) then
      begin
        ToolInfo.uId := 0;
        ToolInfo.lpszText := GeneralToolTipList[Loop].Tip;
        ToolInfo.Rect.Left := Rect.Left;
        ToolInfo.Rect.Top := Rect.Top;
        ToolInfo.Rect.Right := Rect.Right;
        ToolInfo.Rect.Bottom := Rect.Bottom;
        SendMessage(GeneralToolTipWnd, TTM_ADDTOOL, 0, LPARAM(@ToolInfo));
      end;
    end;
    for Loop := 0 to High(ViewerToolTipList) do
    begin
      ToolInfo.hwnd := GetDlgItem(Dlg, ViewerToolTipList[Loop].Ctl);
      if (ViewerToolTipList[Loop].Tip <> nil) and (ToolInfo.hwnd <> 0) and
        GetClientRect(ToolInfo.hwnd, Rect) then
      begin
        ToolInfo.uId := 0;
        ToolInfo.lpszText := ViewerToolTipList[Loop].Tip;
        ToolInfo.Rect.Left := Rect.Left;
        ToolInfo.Rect.Top := Rect.Top;
        ToolInfo.Rect.Right := Rect.Right;
        ToolInfo.Rect.Bottom := Rect.Bottom;
        SendMessage(ViewerToolTipWnd, TTM_ADDTOOL, 0, LPARAM(@ToolInfo));
      end;
    end;
    for Loop := 0 to High(BuilderToolTipList) do
    begin
      ToolInfo.hwnd := GetDlgItem(Dlg, BuilderToolTipList[Loop].Ctl);
      if (BuilderToolTipList[Loop].Tip <> nil) and (ToolInfo.hwnd <> 0) and
        GetClientRect(ToolInfo.hwnd, Rect) then
      begin
        ToolInfo.uId := 0;
        ToolInfo.lpszText := BuilderToolTipList[Loop].Tip;
        ToolInfo.Rect.Left := Rect.Left;
        ToolInfo.Rect.Top := Rect.Top;
        ToolInfo.Rect.Right := Rect.Right;
        ToolInfo.Rect.Bottom := Rect.Bottom;
        SendMessage(BuilderToolTipWnd, TTM_ADDTOOL, 0, LPARAM(@ToolInfo));
      end;
    end;
    Result := True;
  end;
end;

procedure SwitchModeToolTip(Mode: TVdfsDialogMode);
begin
  if ViewerToolTipWnd <> 0 then
    SendMessage(ViewerToolTipWnd, TTM_ACTIVATE, WPARAM(Mode = modeViewer), 0);
  if BuilderToolTipWnd <> 0 then
    SendMessage(BuilderToolTipWnd, TTM_ACTIVATE, WPARAM(Mode = modeBuilder), 0);
  if GeneralToolTipWnd <> 0 then
    SendMessage(GeneralToolTipWnd, TTM_ACTIVATE, WPARAM(Mode in [modeViewer, modeBuilder]), 0);
end;

end.

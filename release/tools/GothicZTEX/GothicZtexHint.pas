unit GothicZtexHint;

interface

uses
  Windows, Messages, CommCtrl,
  GothicZtexGlob;

function InitToolTips(Dlg: HWND): Boolean;

implementation

type
  PToolTipListEntry = ^TToolTipListEntry;
  TToolTipListEntry = record
    Ctl: Integer;
    Tip: PChar;
  end;

const
  ToolTipList: array [0..3] of TToolTipListEntry = (
    (Ctl: IDC_EDTROOT; Tip: 'Base directory for search/conversion'),
    (Ctl: IDC_BTNROOT; Tip: 'Set working directory'),
    (Ctl: IDC_BTNDOIT; Tip: 'Convert all textures (_compiled\*-C.TEX into ...\*.tga)'),
    (Ctl: IDC_EDTRACE; Tip: 'Trace for errors, hints, and summary')
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
    SetWindowPos(ToolTip, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE or SWP_NOSIZE or
      SWP_NOACTIVATE);
    Result := True;
  end;
end;

var
  ToolTipWnd: HWND;

function InitToolTips(Dlg: HWND): Boolean;
var
  ToolInfo: TToolInfo;
  Loop: Integer;
  Rect: TRect;
begin
  Result := False;
  if CreateToolTip(Dlg, ToolTipWnd) then
  begin
    ZeroMemory(@ToolInfo, SizeOf(TToolInfo));
    ToolInfo.cbSize := SizeOf(TToolInfo);
    ToolInfo.uFlags := TTF_SUBCLASS;
    ToolInfo.hInst := HInstance;
    for Loop := 0 to High(ToolTipList) do
    begin
      ToolInfo.hwnd := GetDlgItem(Dlg, ToolTipList[Loop].Ctl);
      if (ToolTipList[Loop].Tip <> nil) and (ToolInfo.hwnd <> 0) and
        GetClientRect(ToolInfo.hwnd, Rect) then
      begin
        ToolInfo.uId := 0;
        ToolInfo.lpszText := ToolTipList[Loop].Tip;
        ToolInfo.Rect.Left := Rect.Left;
        ToolInfo.Rect.Top := Rect.Top;
        ToolInfo.Rect.Right := Rect.Right;
        ToolInfo.Rect.Bottom := Rect.Bottom;
        SendMessage(ToolTipWnd, TTM_ADDTOOL, 0, LPARAM(@ToolInfo));
      end;
    end;
    Result := True;
  end;
end;

end.

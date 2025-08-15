program GothicZTEX;

{$R 'res\Resource.res' 'res\Resource.rc'}

uses
  Windows, Messages, CommCtrl, RichEdit,
  ZTEX,
  GothicZtexGlob in 'GothicZtexGlob.pas',
  GothicZtexUtil in 'GothicZtexUtil.pas',
  GothicZtexHint in 'GothicZtexHint.pas';

function MainFormInitDialog(Dlg: HWND): BOOL; forward;
function MainFormClose(Dlg: HWND; Return: Integer): BOOL; forward;
function MainFormDestroy(Dlg: HWND): BOOL; forward;
function MainFormCommand(Dlg: HWND; NotifyCode, ID: Word; Ctl: HWND): BOOL; forward;

var
  AutoActive: Boolean;
  AutoFailed: Boolean;
  AutoTimer: UINT = 531;

function MainFormDlgProc(Dlg: HWND; Msg: UINT; WParam: WPARAM; LParam: LPARAM): BOOL; stdcall;
begin
  case Msg of
    WM_INITDIALOG:
      Result := MainFormInitDialog(Dlg);
    WM_CLOSE:
      Result := MainFormClose(Dlg, 0);
    WM_DESTROY:
      Result := MainFormDestroy(Dlg);
    WM_COMMAND:
      Result := MainFormCommand(Dlg, HiWord(WParam), LoWord(WParam), HWND(LParam));
    WM_TIMER:
      if AutoActive and (UINT(WParam) = AutoTimer) and (AutoTimer <> 0) then
      begin
        KillTimer(Dlg, AutoTimer);
        AutoTimer := 0;
        Result := MainFormCommand(Dlg, BN_CLICKED, IDC_BTNDOIT, GetDlgItem(Dlg, IDC_BTNDOIT));
      end
      else
        Result := False;
    WM_SHOWWINDOW:
      begin
        if AutoActive and (WParam <> 0) then
        begin
          ProcessMessages(Dlg);
          PostMessage(Dlg, WM_TIMER, AutoTimer, 0);
        end;
        Result := False;
      end;
  else
    Result := False;
  end;
end;

function MainFormInitDialog(Dlg: HWND): BOOL;
var
  Para: Char;
  Root: array [0..MAX_PATH] of Char;
begin
  AutoActive := False;
  if (ParamCount() >= 1) and (Length(ParamStr(1)) = 2) then
  begin
    Para := ParamStr(1)[2];
    case Para of
      'C', 'c':
        begin
          if (ParamCount() = 1) then
            AutoActive := True
          else if (ParamCount() = 2) then
            AutoActive := SetCurrentDirectory(PChar(ParamStr(2)));
          if AutoActive then
            AutoTimer := SetTimer(Dlg, AutoTimer, 1000, nil)
          else
          begin
            MessageBox(Dlg, 'Invalid parameters!', 'GothicVDFS', MB_OK or MB_ICONERROR);
            ExitProcess(1);
          end;
        end;
    end;
  end;
  if not AutoActive then
    SetCurrentDirectory('..\..\data\Textures');
  SendMessage(Dlg, WM_SETICON, ICON_BIG, LPARAM(LoadIcon(HInstance, IDI_MAINICON)));
  InitToolTips(Dlg);
  if not InitFileList then
  begin
    MessageBox(Dlg, 'Error on reading INI file!', nil, MB_ICONWARNING);
    ExitProcess(1);
  end
  else
  begin
    Root[0] := #0;
    GetCurrentDirectory(SizeOf(Root), Root);
    SetDlgItemText(Dlg, IDC_EDTROOT, Root);
  end;
  Result := False;
  SetFocus(GetDlgItem(Dlg, IDC_BTNDOIT));
end;

function MainFormClose(Dlg: HWND; Return: Integer): BOOL;
begin
  Result := BOOL(1);
  if InProgress then
  begin
    if MessageBox(Dlg, 'Do you want to terminate the program?',
      'Work is in progress!', MB_YESNO or MB_ICONQUESTION or
      MB_DEFBUTTON2) = IDYES then
    begin
      Result := BOOL(0);
      EndDialog(Dlg, Return);
      if InProgress then
        ExitProcess(1);
    end;
  end
  else
    EndDialog(Dlg, Return);
end;

function MainFormDestroy(Dlg: HWND): BOOL;
begin
  Result := BOOL(0);
  FreeFileList;
end;

function MainFormCommand(Dlg: HWND; NotifyCode, ID: Word; Ctl: HWND): BOOL;
const
//SearchRoot = '.';
  SearchPath = '_compiled';
  SearchMask = '*-C.TEX';
  TgaFileExt = '.tga';
var
  Info: TMsgBoxParams;
  FileCount: Cardinal;
  FindFile: THandle;
  FindData: TWin32FindData;
  Filename: array [0..MAX_PATH] of Char;
  ZTEXName: array [0..MAX_PATH] of Char;
  TGAName: array [0..MAX_PATH] of Char;
  ZTEXFile: THandle;
  TGAFile: THandle;
  FileTime: TFileTime;
  Menu: HMENU;
begin
  Result := BOOL(0);
  if Ctl <> 0 then
  begin
    if NotifyCode = BN_CLICKED then
    begin
      case ID of
        IDC_BTNROOT:
          begin
            Filename[0] := #0;
            GetCurrentDirectory(MAX_PATH, Filename);
            if SelectDirectory(Dlg, Filename,
              'Base directory for search/conversion:'#13#10'(usually ...\_work\data\Textures)',
              Filename) then
              SetCurrentDirectory(Filename);
            Filename[0] := #0;
            GetCurrentDirectory(MAX_PATH, Filename);
            SetDlgItemText(Dlg, IDC_EDTROOT, Filename);
          end;
        IDC_BTNINFO:
          begin
            ZeroMemory(@Info, SizeOf(TMsgBoxParams));
            Info.cbSize := SizeOf(TMsgBoxParams);
            Info.hwndOwner := Dlg;
            Info.hInstance := HInstance;
            Info.lpszText := 'GothicZTEX 2.6    '#13#10#13#10 +
              'Convert Zengin TEXtures into TGA images    '#13#10 +
              #169' 2003 Nico Bendlin <nicode@gmx.net>     '#13#10;
            Info.lpszCaption := 'About';
            Info.dwStyle := MB_USERICON;
            Info.lpszIcon := IDI_MAINICON;
            MessageBoxIndirect(Info);
          end;
        IDC_BTNDOIT:
          begin
            SetDlgItemText(Dlg, IDC_EDTRACE, '');
            InProgress := True;
            EnableDlgItem(Dlg, IDC_BTNROOT, False);
            EnableDlgItem(Dlg, IDC_BTNDOIT, False);
            if AutoActive then
            begin
              AutoFailed := True;
              EnableDlgItem(Dlg, IDC_BTNEXIT, False);
              Menu := GetSystemMenu(Dlg, False);
              if (Menu <> 0) then
              begin
                EnableMenuItem(Menu, SC_CLOSE, MF_BYCOMMAND or MF_DISABLED or MF_GRAYED);
                DrawMenuBar(Dlg);
              end;
            end;
            FileCount := 0;
            ResetCounter;
            MakeFullPath(nil, SearchPath, SearchMask, Filename);
            FindFile := FindFirstFile(Filename, FindData);
            if FindFile = INVALID_HANDLE_VALUE then
              MessageBox(Dlg, 'No textures found.', nil, 0)
            else
            begin
              repeat
                Inc(FileCount);
                ProcessMessages(Dlg);
              until not FindNextFile(FindFile, FindData);
              FindClose(FindFile);
              InitProgress(Dlg, FileCount);
              FindFile := FindFirstFile(Filename, FindData);
              if FindFile <> INVALID_HANDLE_VALUE then
              repeat
//              SetStatusText(Dlg, FindData.cFileName);
                ProcessMessages(Dlg);
                MakeFullPath(nil, SearchPath, FindData.cFileName, ZTEXName);
                ZTEXFile := CreateFile(ZTEXName, GENERIC_READ,
                  FILE_SHARE_READ or FILE_SHARE_WRITE, nil, OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL, 0);
                if ZTEXFile = INVALID_HANDLE_VALUE then
                  Trace(Dlg, ttError, FindData.cFileName)
                else
                begin
                  lstrcpy(Filename, FindData.cFileName);
                  lstrcpy(@Filename[lstrlen(Filename) - Length(SearchMask) + 1], TgaFileExt);
                  MakeFullPathFromList(nil, nil, Filename, TGAName);
                  if not MakeSureDirectoryPathExists(TGAName) then
                    Trace(Dlg, ttError, TGAName)
                  else
                  begin
                    MakeFullPath(nil, nil, Filename, Filename);
                    if FileExists(Filename) then
                    begin
                      MoveFile(Filename, TGAName);
                      Trace(Dlg, ttProcessed, nil);
                    end
                    else if FileExists(TGAName) then
                    begin
                      if FileIsEqual(TGAName) then
                        Trace(Dlg, ttSkipped, TGAName)
                      else
                      begin
                        MoveFile(TGAName, TGAName);
                        Trace(Dlg, ttSkipped, TGAName);
                      end;
                    end
                    else
                    begin

                      TGAFile := CreateFile(TGAName, GENERIC_WRITE,
                        FILE_SHARE_READ, nil, OPEN_ALWAYS, 0, 0);
                      if TGAFile = INVALID_HANDLE_VALUE then
                        Trace(Dlg, ttError, TGAName)
                      else
                      begin
                        if not ZTexToTga(ZTEXFile, TGAFile) then
                        begin
                          Trace(Dlg, ttError, ZTEXName);
                          CloseHandle(TGAFile);
                          TGAFile := INVALID_HANDLE_VALUE;
                          ProcessMessages(Dlg);
                          DeleteFile(TGAName);
                        end
                        else
                        begin
                          if GetFileTime(ZTEXFile, nil, nil, @FileTime) then
                            SetFileTime(TGAFile, nil, nil, @FileTime);
                          Trace(Dlg, ttProcessed, nil);
                        end;
                      end;
                      if TGAFile <> INVALID_HANDLE_VALUE then
                        CloseHandle(TGAFile);

                    end;
                  end;
                  CloseHandle(ZTEXFile);
                end;
//              SetStatusText(Dlg, nil);
                IncProgress(Dlg, 1);
                ProcessMessages(Dlg);
              until not FindNextFile(FindFile, FindData);
              FindClose(FindFile);
              InitProgress(Dlg, 1);
              Trace(Dlg, ttText, #13#10#13#10'Summary:'#13#10'  Processed: ');
              Trace(Dlg, ttNumber, PChar(FilesProcessed));
              Trace(Dlg, ttText, #13#10'  Skipped: ');
              Trace(Dlg, ttNumber, PChar(FilesSkipped));
              Trace(Dlg, ttText, #13#10'  Errors: ');
              Trace(Dlg, ttNumber, PChar(FilesError));
              Trace(Dlg, ttText, #13#10);
              if AutoActive then
                AutoFailed := (FilesError <> 0);
            end;
            EnableDlgItem(Dlg, IDC_BTNDOIT, True);
            if not AutoActive then
              EnableDlgItem(Dlg, IDC_BTNROOT, True)
            else if not AutoFailed then
              ExitProcess(0);
            EnableDlgItem(Dlg, IDC_BTNEXIT, True);
            Menu := GetSystemMenu(Dlg, False);
            if (Menu <> 0) then
            begin
              EnableMenuItem(Menu, SC_CLOSE, MF_BYCOMMAND or MF_ENABLED);
              DrawMenuBar(Dlg);
            end;
            InProgress := False;
          end;
        IDC_BTNEXIT:
          MainFormClose(Dlg, 0);
      else
        Result := BOOL(1);
      end;
    end
    else
      Result := BOOL(1);
  end;
end;

const
  RichEditLibName = 'riched32.dll';

var
  InitCtrls: TInitCommonControlsEx = (
    dwSize: SizeOf(TInitCommonControlsEx);
    dwICC : ICC_PROGRESS_CLASS
  );

begin
  LoadLibrary(RichEditLibName);
  InitCommonControls();
  InitCommonControlsEx(InitCtrls);
  DialogBoxParam(HInstance, IDD_MAINFORM, 0, @MainFormDlgProc, 0);
  if AutoActive and AutoFailed then
    ExitCode := 1;
end.


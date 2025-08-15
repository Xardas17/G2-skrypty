unit GothicVdfsGlob;

interface

uses
  Windows, CommDlg,
  VdfsDef;

const
  IDI_MAINICON   = MakeIntResource(101);
  IDD_MAINFORM   = MakeIntResource(102);
  IDM_MAINMENU   = MakeIntResource(103);
  IDD_INFOBUILD  = MakeIntResource(104);
  IDB_FOLDER     = MakeIntResource(105);
  IDD_XVOLFORM   = MakeIntResource(202);
  IDC_BTNEXIT    = 1001;
  IDC_EDITFILE   = 1002;
  IDC_BTNFILE    = 1003;
  IDC_EDITROOT   = 1004;
  IDC_BTNROOT    = 1005;
  IDC_EDITTEXT   = 1006;
  IDC_EDITYEAR   = 1007;
  IDC_SPINYEAR   = 1008;
  IDC_EDITMONTH  = 1009;
  IDC_SPINMONTH  = 1010;
  IDC_EDITDAY    = 1011;
  IDC_SPINDAY    = 1012;
  IDC_EDITHOUR   = 1013;
  IDC_SPINHOUR   = 1014;
  IDC_EDITMIN    = 1015;
  IDC_SPINMIN    = 1016;
  IDC_EDITSEC    = 1017;
  IDC_SPINSEC    = 1018;
  IDC_CHECKUTC   = 1019;
  IDC_TREEVIEW   = 1020;
  IDC_LISTVIEW   = 1021;
  IDC_BTNVOL     = 1022;
  IDC_BTNNODE    = 1023;
  IDC_BTNSEL     = 1024;
  IDC_CHECKFULL  = 1025;
  IDC_PROGVIEW   = 1026;
  IDC_EDITFILES  = 1027;
  IDC_BTNFILES1  = 1028;
  IDC_BTNFILES2  = 1029;
  IDC_BTNFILES3  = 1030;
  IDC_BTNFILES4  = 1031;
  IDC_CHECKFILES = 1032;
  IDC_LISTFILES  = 1033;
  IDC_EDITEX     = 1034;
  IDC_BTNEX1     = 1035;
  IDC_BTNEX2     = 1036;
  IDC_BTNEX3     = 1037;
  IDC_BTNEX4     = 1038;
  IDC_CHECKEX    = 1039;
  IDC_LISTEX     = 1040;
  IDC_EDITIN     = 1041;
  IDC_BTNIN1     = 1042;
  IDC_BTNIN2     = 1043;
  IDC_BTNIN3     = 1044;
  IDC_BTNIN4     = 1045;
  IDC_CHECKIN    = 1046;
  IDC_LISTIN     = 1047;
  IDC_BTNOPEN    = 1048;
  IDC_BTNSAVE    = 1049;
  IDC_BTNBUILD   = 1050;
  IDC_PROGBUILD  = 1051;
  IDC_CHECKSORT  = 1052;
  IDC_EDITBINFO  = 1053;
  IDC_BTNINFO    = 1054;
  IDC_EDTRACE    = 1055;
  ID_MENUVIEW    = 40001;
  ID_MENUMODS    = 40002;
  ID_MENUINFO    = 40003;

  IDC_LASTCTL    = IDC_EDITBINFO;
  IDC_MAINSTAT   = IDC_LASTCTL + 1;

{$IFDEF USECOLORS}
const
  DialogTextColor = $00702010;
  DialogBackColor = $00B0C0A0;
  EditTextColor   = $00803020;
  EditBackColor   = $00C0D0B0;
  DialogLogBrush: TLogBrush =(
    lbStyle: BS_SOLID;
    lbColor: DialogBackColor;
  );
  EditLogBrush: TLogBrush =(
    lbStyle: BS_SOLID;
    lbColor: EditBackColor;
  );

var
  DialogBrush: HBRUSH;
  EditBrush: HBRUSH;
{$ENDIF}

var
  MainFormStatus: HWND;

type
  TVdfsDialogMode = (modeViewer, modeBuilder);
  TGothicFileType = (gftUnknown, gftVolume, gftScript);

var
  CurrDlgMode: TVdfsDialogMode = modeViewer;

var
  ViewerWorkInProgress: Boolean;
  BuilderWorkInProgress: Boolean;

var
  ViewerFile: THandle;
  ViewerHeader: TVdfsHeader;
  ViewerTable: PVdfsTable;
  ViewerRoot: array [0..MAX_PATH] of Char = #0;

const
  ViewerFilter = 'All Volumes (*.vdf;*.mod)'#0'*.vdf;*.vdf.disabled;*.mod;*.mod.disabled'#0 +
    'Virtual Disk File (*.vdf)'#0'*.vdf;*.vdf.disabled'#0 +
    'GothicMOD File (*.mod)'#0'*.mod;*.mod.disabled'#0 +
    'All Files (*.*)'#0'*.*'#0#0;

const
  OPENFILENAME_SIZE_VERSION_400 = 76;

var
  ViewerFilename: array [0..MAX_PATH] of Char = #0;
  ViewerNameBuff: array [0..MAX_PATH] of Char = #0;
  ViewerOfn: TOpenFilename =(
    lStructSize: OPENFILENAME_SIZE_VERSION_400;
    lpstrFilter: ViewerFilter;
    lpstrFile: ViewerNameBuff;
    nMaxFile: SizeOf(ViewerNameBuff);
    lpstrTitle: 'Select Volume...';
    Flags: (* OFN_EXPLORER or OFN_ENABLESIZING or *) OFN_HIDEREADONLY or
      OFN_NOCHANGEDIR or OFN_NOTESTFILECREATE or
      OFN_PATHMUSTEXIST or OFN_FILEMUSTEXIST;
  );

const
  RecursiveSuffix = ' -r';

const
  BuilderAllUpper: Boolean = True;

var
  BuilderSortLits: Boolean = True;

var
  BuilderFile: THandle;
  BuilderHeader: TVdfsHeader;
  BuilderTable: PVdfsTable;
  BuilderRoot: array [0..MAX_PATH] of Char = #0;

const
{$IFDEF MODKIT}
  BuilderFilter = 'GothicMOD file (*.mod)'#0'*.mod'#0 +
    'All Files (*.*)'#0'*.*'#0#0;
{$ELSE}
  BuilderFilter = 'Virtual Disk File (*.vdf)'#0'*.vdf'#0 +
    'GothicMOD file (*.mod)'#0'*.mod'#0 +
    'All Files (*.*)'#0'*.*'#0#0;
{$ENDIF}

var
  BuilderFilename: array [0..MAX_PATH] of Char = #0;
  BuilderNameBuff: array [0..MAX_PATH] of Char = #0;
  BuilderOfn: TOpenFilename =(
    lStructSize: OPENFILENAME_SIZE_VERSION_400;
    lpstrFilter: BuilderFilter;
    lpstrFile: BuilderNameBuff;
    nMaxFile: SizeOf(BuilderNameBuff);
    lpstrTitle: 'Select volume filename...';
    Flags: (* OFN_EXPLORER or OFN_ENABLESIZING or *) OFN_HIDEREADONLY or
      OFN_NOCHANGEDIR or OFN_NOTESTFILECREATE or
      OFN_PATHMUSTEXIST or OFN_OVERWRITEPROMPT or OFN_NOREADONLYRETURN;
{$IFDEF MODKIT}
    lpstrDefExt: '.mod';
{$ELSE}
    lpstrDefExt: '.vdf';
{$ENDIF}
  );

const
  ListFilter = 'All Files (*.*)'#0'*.*'#0#0;

var
  ListNameBuff: array [0..MAX_PATH] of Char = #0;
  ListOfn: TOpenFilename =(
    lStructSize: OPENFILENAME_SIZE_VERSION_400;
    lpstrFilter: ListFilter;
    lpstrFile: ListNameBuff;
    nMaxFile: SizeOf(ListNameBuff);
    lpstrTitle: 'Choose file(mask)...';
    Flags: (* OFN_EXPLORER or OFN_ENABLESIZING or *) OFN_HIDEREADONLY or
      OFN_NOCHANGEDIR or OFN_NOTESTFILECREATE or
      OFN_NOVALIDATE;
  );

const
  ScriptFilter = 'VDFS Manager script (*.vm)'#0'*.vm'#0 +
    'All Files (*.*)'#0'*.*'#0#0;

var
  ScriptNameBuff: array [0..MAX_PATH] of Char = #0;
  OpenScriptOfn: TOpenFilename =(
    lStructSize: OPENFILENAME_SIZE_VERSION_400;
    lpstrFilter: ScriptFilter;
    lpstrFile: ScriptNameBuff;
    nMaxFile: SizeOf(ScriptNameBuff);
    lpstrTitle: 'Open script...';
    Flags: (* OFN_EXPLORER or OFN_ENABLESIZING or *) OFN_HIDEREADONLY or
      OFN_NOCHANGEDIR or OFN_NOTESTFILECREATE or
      OFN_PATHMUSTEXIST or OFN_FILEMUSTEXIST;
  );
  SaveScriptOfn: TOpenFilename =(
    lStructSize: OPENFILENAME_SIZE_VERSION_400;
    lpstrFilter: ScriptFilter;
    lpstrFile: ScriptNameBuff;
    nMaxFile: SizeOf(ScriptNameBuff);
    lpstrTitle: 'Save script...';
    Flags: (* OFN_EXPLORER or OFN_ENABLESIZING or *) OFN_HIDEREADONLY or
      OFN_NOCHANGEDIR or OFN_NOTESTFILECREATE or
      OFN_PATHMUSTEXIST or OFN_OVERWRITEPROMPT or OFN_NOREADONLYRETURN;
    lpstrDefExt: '.vm';
  );

const
  VdfsMgrParamLine = '%%N';
  VdfsMgrParamDate = '%%D';

const
  VdfsMgrScriptSegGlobal  = 'BEGINVDF';
  VdfsMgrScriptKeyComment = 'Comment';
  VdfsMgrScriptKeyBaseDir = 'BaseDir';
  VdfsMgrScriptKeyVDFName = 'VDFName';
  VdfsMgrScriptSegFiles   = 'FILES';
  VdfsMgrScriptSegExclude = 'EXCLUDE';
  VdfsMgrScriptSegInclude = 'INCLUDE';
  VdfsMgrScriptSegEndTag  = 'ENDVDF';

var
  OptionsViewerLoaded: Boolean = False;
  OptionsBuilderLoaded: Boolean = False;

const
  OptionsRoot = HKEY_CURRENT_USER;
  OptionsPath = 'Software\Piranha Bytes\GothicVDFS';
  OptionsViewerFilename = 'Viewer.Filename';
  OptionsViewerRootpath = 'Viewer.Rootpath';
  OptionsBuilderFilename   = 'Builder.Filename';
  OptionsBuilderRootpath   = 'Builder.Rootpath';
  OptionsBuilderScriptname = 'Builder.Scriptname';

var
  AutoExtractVolume: Boolean;
  AutoExtractErrors: Cardinal;

implementation

end.

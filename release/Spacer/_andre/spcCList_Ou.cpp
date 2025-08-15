// spcCListCutsceneDlg.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "MainFrm.h"
#include "SpacerView.h"

// engine
#include "zoption.h"
#include "zParser.h"
#include "zCCSManager.h"
#include "zfilecsv.h"

// Spacer
#include "spcCList_ou.h"
#include "spcCScriptTool.h"
#include "spcCScriptWizard.h"
#include "spcCInputDialog.h"
#include "spcCWorkInfoDlg.h"
#include "spcCInfoBar.h"
#include "spcCConfiguration.h"

#ifdef COMPILING_GOTHIC
	#include "oNpc.h"
	#include "oNpcMessages.h"	
	#include "oFocus.h"
#endif

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////

const zSTRING CSV_TEXT_TRANSLATE = "TRL";
const zSTRING OU_PARSE_INFO_FILE = "_compiled\\ouinfo.inf";

// Makro und Consts zum FOrmatieren eines Datenfeldes

const zSTRING CSV_OU_MARKER = "[OU]";

/*
const zSTRING CSV_FIELD_DELIMITER = ";";
const zSTRING CSV_FIELD_FRAME = "\"";
const zSTRING CSV_SET_DELIMITER = "\n";
static zSTRING CSV_FieldFormat(zSTRING s) 
{
	return CSV_FIELD_FRAME + s + CSV_FIELD_FRAME;
};
static zSTRING CSV_GetField(zSTRING s, int nr)
{
	zSTRING result = s.PickWord(nr,CSV_FIELD_DELIMITER,CSV_FIELD_DELIMITER);
	result = result.PickWord(2,CSV_FIELD_FRAME,CSV_FIELD_FRAME);
	return result;
};
*/

/////////////////////////////////////////////////////////////////////////////
// spcCListCutsceneDlg dialog


spcCListCutsceneDlg::spcCListCutsceneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCListCutsceneDlg::IDD, pParent), ous(), selected(-1), changesOnCheck(false)
{
	//{{AFX_DATA_INIT(spcCListCutsceneDlg)
	// m_ou_filter = _T("");
	m_language = -1;
	//}}AFX_DATA_INIT
	winID = 0;
}


void spcCListCutsceneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCListCutsceneDlg)
	DDX_Control(pDX, IDC_LOAD, ctrl_button_load);
	DDX_Control(pDX, IDC_TEST, ctrl_button_test);
	DDX_Control(pDX, ID_CUTSCENE_UPDATEOU, ctrl_update_ou);
	DDX_Control(pDX, IDC_SEARCH, ctrl_search_edit);
	DDX_Control(pDX, IDC_SAVE, ctrl_button_save);
	DDX_Control(pDX, IDC_OU_REFRESH, ctrl_button_refresh);
	DDX_Control(pDX, IDC_DELETE_OU, ctrl_button_delete);	
	DDX_Control(pDX, IDC_OU_LANGUAGE, ctrl_language_list);
	DDX_Control(pDX, IDC_OU_LIST, ctrl_ou_list);
	//DDX_Control(pDX, IDC_OU_FILTER, ctrl_ou_filter);
	//DDX_CBString(pDX, IDC_OU_FILTER, m_ou_filter);
	DDX_CBIndex(pDX, IDC_OU_LANGUAGE, m_language);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCListCutsceneDlg, CDialog)
	//{{AFX_MSG_MAP(spcCListCutsceneDlg)
	// ON_CBN_SELCHANGE(IDC_OU_FILTER, OnSelchangeOuFilter)
	ON_CBN_SELCHANGE(IDC_OU_LANGUAGE, OnSelchangeOuLanguage)
	ON_BN_CLICKED(IDC_OU_REFRESH, OnOuRefresh)
	ON_LBN_SELCHANGE(IDC_OU_LIST, OnSelchangeOuList)
	ON_LBN_DBLCLK(IDC_OU_LIST, OnDblclkOuList)
	ON_BN_CLICKED(IDC_DELETE_OU, OnDeleteOu)	
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_EN_CHANGE(IDC_SEARCH, OnChangeSearch)
	ON_BN_CLICKED(ID_CUTSCENE_UPDATEOU, OnCutsceneUpdateOU)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCListCutsceneDlg message handlers

zSTRING spcCListCutsceneDlg::LanguageGrammalog(int nr)
{
	switch(nr) {
	case 0: return zSTRING("GER");
	case 1: return zSTRING("ENG");
	case 2: return zSTRING("FRE");
	case 3: return zSTRING("SPA");
	default : return zSTRING("GER");
	}
}


void spcCListCutsceneDlg::UpdateChanges()
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	zCCSManager* csmanager = CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	if (!csmanager) return;
	
	int entry=0;
	zCCSBlock* lBlock = csmanager->LibGetFirst(entry);
	int oz =0;

	while (lBlock)
	{
		while (oz<ous.GetNumInList() && ous[oz].lEntry<entry) oz++;
		if (oz>=ous.GetNumInList() || 
			ous[oz].lEntry>entry)
		{
			ous.Insert(COutputUnit());
			ous[ous.GetNumInList()-1].bez = lBlock->GetRoleName();
			ous[ous.GetNumInList()-1].lEntry = entry;
			ous[ous.GetNumInList()-1].file = zSTRING("U#");
			ous[ous.GetNumInList()-1].block = lBlock;
			ous[ous.GetNumInList()-1].type = 1; //Type des Blocks ist Nummer des Auswahldingsda
			ous[ous.GetNumInList()-1].rem = zSTRING("§");
		}
		lBlock = csmanager->LibGetNext(entry);
	}
	selected = -1;
}



void spcCListCutsceneDlg::OUHack()
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	zCCSManager* csmanager = CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	if (!csmanager) return;

	ous.DeleteList();

	int entry=0;
	zCCSBlock* lBlock = csmanager->LibGetFirst(entry);
	
	while (lBlock)
	{
		// wenn dieser Bezeichner schon vorhanden
		zSTRING dieser = lBlock->GetRoleName();
		int oz=0;
		while (oz<ous.GetNumInList() && ous[oz].bez!=dieser) oz++;
		
		if (oz!=ous.GetNumInList())
		{
			// dann aus Lib löschen
			csmanager->LibDelOU(entry);
		} 
		else 
		{
			ous.Insert(COutputUnit());
			ous[ous.GetNumInList()-1].bez = dieser;
			ous[ous.GetNumInList()-1].lEntry = entry;
			ous[ous.GetNumInList()-1].file = zSTRING("U#");
			ous[ous.GetNumInList()-1].block = lBlock;
			ous[ous.GetNumInList()-1].type = 1; //Type des Blocks ist Nummer des Auswahldingsda
			ous[ous.GetNumInList()-1].rem = "";
		}
		lBlock = csmanager->LibGetNext(entry);
	}

	// OnSave();

	ConstructList();
	UpdateList();
}

void spcCListCutsceneDlg::OnSelchangeOuLanguage() 
{
	UpdateData(true);
/*
	if (csplayer)
	{
		csplayer->LibChangeLang(LanguageGrammalog(m_language));
		ConstructList();
		UpdateList();
	}
	
	UpdateData(false);

	selected = -1;
*/
	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCListCutsceneDlg::OnSelchangeOuFilter() 
{
	UpdateData(true);		
	
	ConstructList();
	UpdateList();

	// Enable Delete-Button?
	/*
	ctrl_button_delete.EnableWindow(false);
	for (int i=0;i<spcConfig.OUFilterList.GetNumInList();i++)
	{
		if (spcConfig.OUFilterList[i]->GetName() == m_ou_filter) 
		{
			ctrl_button_delete.EnableWindow(spcConfig.OUFilterList[i]->AreEntriesDeletable());
		}
	}
	*/
	selected =-1;

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}

void spcCListCutsceneDlg::InitData()
{
	// ctrl_ou_filter.ResetContent();
	CString filterItem;
	zCList<spcCOutputUnitFilter> *node = spcConfig.OUFilterList.GetNextInList();
	while (node!=0)
	{
		filterItem = node->GetData()->GetName();
		// ctrl_ou_filter.AddString(filterItem);
		node = node->GetNextInList();
	}
	// set filter to first entry
	// ctrl_ou_filter.GetLBText(1, m_ou_filter);	
	// set Language to German
	m_language = 0;

	// ConstructList(); // welche sind schon da??
	// UpdateList();

	UpdateData(FALSE);		
}


BOOL spcCListCutsceneDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	spcCWindowResizeStyle* style;

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_ou_list,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_load,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_save,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);
	
	/*
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_language_list,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_LEFT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);
	*/

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_search_edit,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_test,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_delete,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_button_refresh,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_update_ou,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	winID = spcConfig.GetWindowID("winObjectList");
	spcTRegWindowInfo winInfo;
	spcConfig.GetWindowPosition(winID,winInfo);
	
	MoveWindow(
		winInfo.position.pos.x,
		winInfo.position.pos.y,
		winInfo.position.size.cx,
		winInfo.position.size.cy,
		TRUE);
	
	InitData();
	
	return TRUE;  
}


void spcCListCutsceneDlg::OnOuRefresh() 
{
//	Delete double Hack
	if (AfxMessageBox("Do you wan't to remove doubles from Lib?",MB_YESNO)==IDYES)
	{
		zERR_MESSAGE(4,0,"B: CSL: Refreshing OutputUnit-Library");
		OUHack();
	}
	UpdateList();
}

void spcCListCutsceneDlg::OnSelchangeOuList() 
{
	int index = ctrl_ou_list.GetCurSel();	
	if (index==LB_ERR) return;

	ctrl_ou_list.GetItemData(index);	
	
	selected = index;
	ctrl_ou_list.SetSel(index,TRUE);  // nochmal nachsetzen, falls sich was geändert hat

	spcCInfoBar* info = 0;
	if (CMainFrame::mainframe) info = CMainFrame::mainframe->GetInfoBar();	

	/*
	zCCSBlockBase* cs = GetSelected();
	bool start_enabled = 
		(result != LB_ERR)					// es muss was selektiert sien
		&& info								// InfoBar vorhanden
		&& info->GetActiveWorld()			// Welt geladen
		&& info->GetSelectedVob()			// Vob selektiert
		&& cs								// cs != NULL
		&& !dynamic_cast<zCCutscene*>(cs);// Keine Cutscene, nur OutputUnit
	*/
}

void spcCListCutsceneDlg::UpdateSelected()
{
	if (selected==-1) return;

	int ouEntry =ctrl_ou_list.GetItemData(selected);
	ctrl_ou_list.DeleteString(selected);

	int indexNew = ctrl_ou_list.AddString(CString(ous[ouEntry].bez.ToChar()));
	ous[ouEntry].rem = "";
	ctrl_ou_list.SetItemData(indexNew,ouEntry);
	ctrl_ou_list.SetSel(indexNew,TRUE);
	selected = indexNew;
}

zCCSBlockBase* spcCListCutsceneDlg::GetSelected()
{	
	int index = ctrl_ou_list.GetCurSel();
	if (index==LB_ERR) return 0;

	int ouEntry =ctrl_ou_list.GetItemData(index);
	if (ouEntry<0) return 0;
	return ous[ouEntry].block;
}

void spcCListCutsceneDlg::OnDblclkOuList() 
{
	int index = ctrl_ou_list.GetCurSel();	
	if (index==LB_ERR) return;
	
	int selEntry = ctrl_ou_list.GetItemData(index);
	if (ous[selEntry].type==0) return;
	CMainFrame::mainframe->CSSetOU(ous[selEntry].block);	
}

void spcCListCutsceneDlg::OnDeleteOu() 
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	//if (!csplayer) return;
	if (!csmanager) return;

	int numSelected = ctrl_ou_list.GetSelCount();
	if (numSelected<=0) return;

	if (AfxMessageBox("Do you wan't to remove the selected OutputUnits from Lib?",MB_YESNO)==IDYES)
	{
		::SetCursor(spcConfig.MouseWait);
			
		for (int i=ctrl_ou_list.GetCount()-1;i>=0;i--)
		{			
			if (ctrl_ou_list.GetSel(i)>0)
			{							
				DWORD itemData = ctrl_ou_list.GetItemData(i);
				if ((itemData>=0) && (ous[itemData].lEntry>=0)) csmanager->LibNullOU(ous[itemData].lEntry);
			}
		}		
		
		csmanager->LibCompact();
		ConstructList();		
		UpdateList();
		
		::SetCursor(spcConfig.MouseArrow);		
	}
}

void spcCListCutsceneDlg::OnNewOu() 
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	//if (!csplayer) return;
	if (!csmanager) return;

	spcCInputDialog dlg;
	if (dlg.DoModal()==IDOK && dlg.GetInput()!="")//dlg.m_edit!="")
	{
		::SetCursor(spcConfig.MouseWait);
		zSTRING newName = zSTRING(dlg.GetInput().GetBuffer(0));
		zCCSBlock* lBlock = new zCCSBlock();
		zCCSAtomicBlock* LAB = new zCCSAtomicBlock();
		zCEventMessage* newmsg = new oCMsgConversation(oCMsgConversation::EV_PLAYANISOUND,newName,zSTRING("default text"));
		LAB->SetCommand(newmsg);
		lBlock->SetRoleName(newName);
		csmanager->LibAddOU(lBlock);		
		UpdateChanges();
		UpdateList();
		::SetCursor(spcConfig.MouseArrow);
		zRELEASE(lBlock);
	}
}

void spcCListCutsceneDlg::UpdateWithScripts()
{
	zERR_MESSAGE(4,0,"B: CSL: Updating OutputUnit-Libary with scripts ...");

	CheckWithScripts();
	if (changesOnCheck)
	{
		UpdateChanges();
		changesOnCheck=false;

		UpdateData(FALSE);	
		UpdateList();
	}	
}

void spcCListCutsceneDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (winID>0 && IsWindowVisible())
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
	}

	bool result;
	spcCWindowResizeStyle* style;
	POSITION pos = childResizeList.GetHeadPosition();
	while (pos)
	{
		style = childResizeList.GetNext(pos);
		result = style->UpdateSize();		
		if (!result) return;
	};

}

void spcCListCutsceneDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	if (winID>0 && IsWindowVisible())
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
	}
	
}

void spcCListCutsceneDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	

	if (winID>0)
	{
		if (bShow)
		{
			spcTRegWindowInfo winInfo;
			spcConfig.GetWindowPosition(winID,winInfo);		
			MoveWindow(
				winInfo.position.pos.x,
				winInfo.position.pos.y,
				winInfo.position.size.cx,
				winInfo.position.size.cy,
				TRUE);		
		}	
	}				
}

void spcCListCutsceneDlg::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	// CDialog::OnCancel();
}

void spcCListCutsceneDlg::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	// CDialog::OnOK();
}

void spcCListCutsceneDlg::OnSave() 
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	//if (!csplayer) return;
	if (!csmanager) return;

	csmanager->LibStore();		
	ConstructList();
	UpdateList();
}

void spcCListCutsceneDlg::UpdateList()
{
	zERR_MESSAGE(6,0,"B: CSL: Updating list of OutputUnits");

	UpdateData(true);
	//int index = ctrl_ou_filter.GetCurSel();
	//if (index>=0) ctrl_ou_filter.GetLBText(index, m_ou_filter);	
	
	// change list content
	ctrl_ou_list.ResetContent();
	int indexNew = 0;

	for (int z=0; z<ous.GetNumInList(); z++)
	{
		// (ous[z].type==index) // kein Filter!!
		{
			if (ous[z].rem == zSTRING("§"))
			{
				indexNew = ctrl_ou_list.AddString(CString("* ")+CString(ous[z].bez.ToChar()));
			}
			else
			{
				indexNew = ctrl_ou_list.AddString(CString(ous[z].bez.ToChar()));
			}
			
			ctrl_ou_list.SetItemData(indexNew,z );
		}
	}

	UpdateData(false);
}


void spcCListCutsceneDlg::CheckWithScripts()
{	
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	//if (!csplayer) return;
	if (!csmanager) return;

	spcCWorkInfoDlg* dlg = new spcCWorkInfoDlg();
	dlg->Create(IDD_WORKING_DLG,NULL);	
	dlg->ShowWindow(SW_SHOWNORMAL);
	dlg->SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE);


	// Gehe sicher, dass die Lib geladen wurde
	if (!csmanager->LibIsLoaded()) 
	{
		dlg->AddMessage("Loading lib (ascii)");
		csmanager->LibLoad(zLIB_LOAD_ASCII);		
		ConstructList();
		changesOnCheck=true;
	}	
		
	zoptions->ChangeDir(DIR_SCRIPTS);		

	zSTRING checkString;	

	zSTRING	svmFileName(spcConfig.svmName.GetBuffer(0));	

	///
	// Analysing SMV.D
	///

	zFILE*	svmFile = zfactory->CreateZFile("");
	svmFile->SearchFile(svmFileName, zoptions->GetDirString(DIR_SCRIPTS));

	// reading svm.d to filebuffer
	zSTRING svmFileBuffer;
	if (svmFile->Exists())
	{	
		dlg->AddMessage("Reading file "+CString(svmFile->GetFullPath().ToChar()));

		svmFile->Open();
			long fileSize = svmFile->Size();
			char* fileContent = new char[fileSize+10];
			svmFile->Read(fileContent,fileSize);
			fileContent[fileSize]='\0';
			svmFileBuffer = fileContent;
		svmFile->Close();
	}
	else 
	{
		CString filename = "\""+CString(svmFileName.ToChar())+"\"";
		dlg->AddMessage("File not found: "+filename);
		MessageBox("File\r\n"+filename+"\r\ndoes not exist!");
		return;
	}

	// analysing svm.d
	dlg->AddMessage("Searching for new SVM-entries ...");
	spcCSVMManager* svmMan = new spcCSVMManager();	
	zSTRING s = svmMan->getFirstOU();
	while (s!=zSTRING("_ITER_END"))
	{	
		
		// Suchen, ob der Eintrag schon vorhanden ist
		int ouCount = 0;
		int numInList = ous.GetNumInList();
		while (ouCount<numInList && ous[ouCount].bez!=s) 
			ouCount++;

		if (!s.IsEmpty())
		{
			zCCSBlock*			lBlock	= 0;
			zCCSAtomicBlock*	LAB		= 0;
			
			// Falls noch nicht vorhanden: erzeugen ...
			if (ouCount==ous.GetNumInList()) 			
			{
				changesOnCheck = true;
				zERR_MESSAGE(5,0,"A: [NEW] "+s);
				dlg->AddMessage(CString("[NEW] ")+CString(s.ToChar()));
				if (s == "SVM_5_YouWonCoolFight")
				{
					dlg->AddMessage(CString("[NEW] ")+CString(s.ToChar()));
				};
				lBlock = new zCCSBlock();
				LAB = new zCCSAtomicBlock();
			}									
			
			zSTRING textStr;			
			zSTRING line;
			int index = svmFileBuffer.Search("\""+s+"\""); // Eintrag im File suchen
			if (index>=0)
			{
				int indexNL = svmFileBuffer.Search(index,"\n"); // Ende der Zeile
				int indexCM = svmFileBuffer.Search(index,"/");	// Anfang eines Kommentars
				if (indexCM>=0) // Kommentar gefunden?
				{
					if (indexNL<0) // kein weiteres Newline?
					{
						textStr = svmFileBuffer.Copied(indexCM);
					}
					else if (indexCM<indexNL) // Kommentar in gleicher Zeile?
					{
						textStr = svmFileBuffer.Copied(indexCM,indexNL-indexCM);
					};
				};
				if (!textStr.IsEmpty())
				{	
					textStr.TrimLeft();
					textStr.TrimLeft('/');
					textStr.TrimLeft();					
					char ch;
					int i = textStr.Length()-1;
					while (true) 
					{
						if (i<0) break;
						ch = textStr[i];
						if (ch!='\r' && ch!='\n' && ch!=' ' && ch!='\t') break;
						i--;
					};
					textStr.Delete(i+1);
				}
			}
			
			if (ouCount==ous.GetNumInList()) 
			{
				zCEventMessage* newmsg = csmanager->CreateOuMessage();
				newmsg->MD_SetInfo(s+zSTRING("#")+textStr);
				// newmsg->MD_SetInfo(textStr);

				LAB			->SetCommand(newmsg);
				lBlock		->InsertBlock(LAB);
				lBlock		->SetRoleName(s);
				csmanager	->LibAddOU(lBlock);				
			} 
			else 
			{
				// muß der Text aktualisiert werden?
				checkString = ous[ouCount].block->GetInfo();
				zBOOL changed = zBOOL( checkString!=textStr );
				if (changed)
				{
					changesOnCheck = true;
					// Text aktualisieren
					ous[ouCount].block->SetInfo(textStr);					
					zERR_MESSAGE(5,0,"A: [UPD] "+s);
					dlg->AddMessage(CString("[UPD] ")+CString(s.ToChar()));
				}
			}
			zRELEASE(lBlock);
		}
		s = svmMan->getNextOU();
	}
	delete svmMan;svmMan=0;
	delete svmFile;svmFile = 0;

	
	dlg->AddMessage("Searching for new OU-entries");
	dlg->AddMessage("... in file \""+CString(OU_PARSE_INFO_FILE.ToChar())+"\" ...");
	
	zoptions->ChangeDir(DIR_SCRIPTS);
	zFILE* infoFile = zfactory->CreateZFile(zSTRING(OU_PARSE_INFO_FILE));
		
	if (infoFile->Exists())
	{
		infoFile->Open();
		zSTRING bufferStr;
		while (!infoFile->Eof())
		{
			infoFile->Read(bufferStr);
			if (bufferStr.Search("FILE")!=-1)
			{
				zSTRING bufferStr2;
				infoFile->Read(bufferStr2);
				bufferStr2 = bufferStr2.PickWord(2,"{}","{}"); // Zeile aus Script
				// ermittel den Parameter
				zSTRING textStr;
				if (bufferStr2.Search ("AI_Output")!=-1)
				{
					s = bufferStr2.PickWord (2,"\"","\"");
					textStr = bufferStr2.PickWord(2,"/","/");
					textStr.TrimLeft();
					textStr.TrimRight();
				}
				else continue;
				
				int ouCount = 0;
				while (ouCount<ous.GetNumInList() && ous[ouCount].bez!=s) ouCount++;

				if (!s.IsEmpty())
				{
					// neue OU erzeugen
					if (ouCount==ous.GetNumInList()) 
					{
						zERR_MESSAGE(4,0,"A: [NEW] "+s);
						dlg->AddMessage(CString("[NEW] ")+CString(s.ToChar()));

						zCCSBlock*			lBlock	= new zCCSBlock();
						zCCSAtomicBlock*	LAB		= new zCCSAtomicBlock();

						zCEventMessage* newmsg	= csmanager->CreateOuMessage();
						newmsg->MD_SetInfo(s+zSTRING("#")+textStr);
						// newmsg->MD_SetInfo(textStr);
						LAB->SetCommand(newmsg);
						lBlock->InsertBlock(LAB);
						lBlock->SetRoleName(s);
						int entry = csmanager->LibAddOU(lBlock);

						ous.Insert(COutputUnit());
						ous[ous.GetNumInList()-1].bez		= lBlock->GetRoleName();
						ous[ous.GetNumInList()-1].lEntry	= entry;
						ous[ous.GetNumInList()-1].file		= zSTRING("U#");
						ous[ous.GetNumInList()-1].block		= lBlock;
						ous[ous.GetNumInList()-1].type		= 1; //Type des Blocks ist Nummer des Auswahldingsda
						ous[ous.GetNumInList()-1].rem		= zSTRING("§");
			
						changesOnCheck = true;

						zRELEASE(lBlock);
					} 
					else 
					{						
						// Hat sich der Text geaendert?
						checkString = ous[ouCount].block->GetInfo();						
						zBOOL changed = zBOOL(checkString!=textStr);
						if (changed)
						{
							changesOnCheck = true;
							// Text aktualisieren
							ous[ouCount].block->SetInfo(textStr);					
							zERR_MESSAGE(4,0,"A: [UPD] "+s);
							dlg->AddMessage(CString("[UPD] ")+CString(s.ToChar()));
						}
					}
				}
				infoFile->Read(bufferStr); // LINE überlesen
				infoFile->Read(bufferStr); // FILEPOS überlesen
			}
		}
		infoFile->Close();
		delete infoFile;
	}
	else
	{
		CString filename = "\""+CString(OU_PARSE_INFO_FILE.ToChar())+"\"";
		dlg->AddMessage("File "+filename+" does not exist");
		MessageBox("File \r\n"+filename+"\r\n does not exist.\r\nReparse scripts first!");
	};
		
	if (changesOnCheck) 
	{
		// dlg->AddMessage("store OULib...");
		// csmanager->LibStore();
	}

	dlg->CloseWindow();
	delete (dlg);
}


void spcCListCutsceneDlg::Extracttext()
{	
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	zCCSManager* csmanager = CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	if (!csmanager) return;
	
	zoptions->ChangeDir(DIR_CUTSCENES);

	CString filter = "Tabelle (*.csv)|*.csv||";
	CFileDialog dlg(false,"csv","Sprechliste",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,filter);	
	
	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result != IDOK) return;

	zSTRING fileName = dlg.GetPathName().GetBuffer(0);
	// zFILE* ouCSVFile = zfactory->CreateZFile(zSTRING(fileName));	
	zCFileCSV* ouCSVFile = new zCFileCSV(fileName);
	ouCSVFile->SetFormat(TRUE,";","\"");
	ouCSVFile->Create();	

	// Header
	ouCSVFile->AddNextHeader("Name(WAV)");
	ouCSVFile->AddNextHeader("Text");
	ouCSVFile->AddNextHeader("Filename");
	ouCSVFile->AddNextHeader("Translated Text");
	ouCSVFile->WriteHeader();

	zERR_MESSAGE(4,0,"A: SPC: Extract text from output-units to file \""+fileName+"\"");
	
	::SetCursor(spcConfig.MouseWait);
	
	int ou_index;
	for (int i=0; i<ctrl_ou_list.GetCount();i++)
	{
		ou_index = ctrl_ou_list.GetItemData(i);
		if (ous[ou_index].type==1) // das sind die tatsächlichen OUS
		{
			// CSV-Format
			ouCSVFile->AddNextField(ous[ou_index].bez);
			ouCSVFile->AddNextField(ous[ou_index].block->GetInfo());
			ouCSVFile->AddNextField(CSV_OU_MARKER);
			ouCSVFile->AddNextField(CSV_TEXT_TRANSLATE);
			ouCSVFile->WriteSet();
		}
		if (ous[ou_index].type==0) // das sind die CS
		{
			csmanager->OpenCSForIteration(ous[ou_index].file);
			zSTRING theToken = zSTRING(" ****** ");
			zSTRING theText;

			while ( csmanager->Next(theToken,theText) ) {
				if (theToken.IsEmpty()) theToken = zSTRING(" ****** ");
				
				ouCSVFile->AddNextField(theToken);
				ouCSVFile->AddNextField(theText);
				ouCSVFile->AddNextField(ous[ou_index].file);
				ouCSVFile->AddNextField(CSV_TEXT_TRANSLATE);
				ouCSVFile->WriteSet();

			}
			csmanager->CloseIteration();
		}
	}

	ouCSVFile->Close();
	delete ouCSVFile;

	::SetCursor(spcConfig.MouseArrow);
}

void spcCListCutsceneDlg::Importtext( CString & importFile )
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	//if (!csplayer) return;
	if (!csmanager) return;

/*	CString filter = "Tabelle (*.csv)|*.csv|All Files(*.*)|*.*||";
	CFileDialog* dlg = new CFileDialog(true,"csv","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);

	zFILE::DirectFileAccess(true);
	int result = dlg->DoModal();
	zFILE::DirectFileAccess(false);

	if (result != IDOK) return;
*/
	::SetCursor(spcConfig.MouseWait);

	bool libWasLocalized = false;
	zoptions->ChangeDir(DIR_CUTSCENES);
	zCFileCSV* ouListFile = new zCFileCSV(importFile.GetBuffer(0));
	ouListFile->SetFormat(TRUE,";","\"");
	if (ouListFile->Exists()) 
	{		
		zSTRING currentCS;
		ouListFile->Open();
		ouListFile->ReadHeader();	// Wichtig, da Header erst analysiert werden muss

		zSTRING rBuf;
		while (!ouListFile->Eof())
		{
			if (ouListFile->ReadSet())
			{			
				zSTRING t1 = ouListFile->GetNextField("Name(WAV)");
				zSTRING t2 = ouListFile->GetNextField("Text");
				zSTRING t3 = ouListFile->GetNextField("Filename");
				zSTRING t4 = ouListFile->GetNextField("Translated Text");

				if (t3!=zSTRING(CSV_OU_MARKER) && !t3.IsEmpty())
				{
					// Cutscene wird lokalisiert
					if (currentCS!=t3) 
					{
						if (!currentCS.IsEmpty())
						{
							csmanager->SaveCSForIteration(LanguageGrammalog(m_language)+zSTRING("\\")+currentCS);
							csmanager->CloseIteration();
						}
						csmanager->OpenCSForIteration(t3);
						currentCS=t3;
					}
					csmanager->Localize(t1,t4);
				} 
				if (t3==CSV_OU_MARKER) {
					libWasLocalized = true;
					csmanager->Localize(t1,t4);
				}
			}
		}
		if (!currentCS.IsEmpty())
		{
			csmanager->SaveCSForIteration(LanguageGrammalog(m_language)+zSTRING("\\")+currentCS);
			csmanager->CloseIteration();
		}
		ouListFile->Close(); 
		if (libWasLocalized) csmanager->LibStore();
	}
	delete ouListFile;
	::SetCursor(spcConfig.MouseArrow);
}

void spcCListCutsceneDlg::ConstructList()
{
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	//zCCSPlayer*  csplayer	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();
	//if (!csplayer) return;
	if (!csmanager) return;

	ous.DeleteList();

	int entry=0;
	zCCSBlock* lBlock = csmanager->LibGetFirst(entry);
	
	int num=0;
	while (lBlock)
	{
		ous.Insert(COutputUnit());
		ous[ous.GetNumInList()-1].bez = lBlock->GetRoleName();
		ous[ous.GetNumInList()-1].lEntry = entry;
		ous[ous.GetNumInList()-1].file = zSTRING("U#");
		ous[ous.GetNumInList()-1].block = lBlock;
		ous[ous.GetNumInList()-1].type = 1; //Type des Blocks ist Nummer des Auswahldingsda
		ous[ous.GetNumInList()-1].rem = "";

		lBlock = csmanager->LibGetNext(entry);
		num++;
	}
	zERR_MESSAGE(5,0,"B: SPC: Handled "+zSTRING(num)+" output-units");

	/*
	// Cutscenes
	
	zoptions->ChangeDir(DIR_CUTSCENES);
	if (m_language!=0) 
	{
		zFILE_FILE csFile(LanguageGrammalog(m_language)+zSTRING("\\"));
		csFile.ChangeDir();
		bool go = csFile.FindFirst(zSTRING("*.cs"));
		num=0;
		while (go)
		{
			ous.Insert(COutputUnit());
			ous[ous.GetNumInList()-1].bez = csFile.GetFilename();
			ous[ous.GetNumInList()-1].lEntry = -1;
			ous[ous.GetNumInList()-1].file = csFile.GetFilename();
			ous[ous.GetNumInList()-1].block = NULL;
			ous[ous.GetNumInList()-1].type = 0; //Type des Blocks ist Nummer des Auswahldingsda
			ous[ous.GetNumInList()-1].rem = "";
			go = csFile.FindNext();
			num++;
		}
		zERR_MESSAGE(5,0,"B: SPC: Handled "+zSTRING(num)+" cutscenes");
	} 
	else 
	{
		zFILE_FILE csFile;
		bool go = csFile.FindFirst(zSTRING("*.cs"));
		num=0;
		while (go)
		{
			ous.Insert(COutputUnit());
			ous[ous.GetNumInList()-1].bez = csFile.GetFilename();
			ous[ous.GetNumInList()-1].lEntry = -1;
			ous[ous.GetNumInList()-1].file = csFile.GetFilename();
			ous[ous.GetNumInList()-1].block = NULL;
			ous[ous.GetNumInList()-1].type = 0; //Type des Blocks ist Nummer des Auswahldingsda
			ous[ous.GetNumInList()-1].rem = "";
			go = csFile.FindNext();
			num++;
		}
		zERR_MESSAGE(5,0,"B: SPC: Read "+zSTRING(num)+" cutscenes");
	}
	*/
	selected = -1;
}



void spcCListCutsceneDlg::OnOuStart() 
{
	if (!CMainFrame::mainframe) return;
	spcCInfoBar* info = CMainFrame::mainframe->GetInfoBar();
	if (!info) return;

	//zCCSPlayer*  csplayer	= info->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= info->GetCurrentCutsceneManager();		
	//if (!csplayer) return;
	if (!csmanager) return;
	
	zCVob* pickedVob = info->GetSelectedVob();
	if (!pickedVob) return;
	
	zCCSBlockBase* cs = GetSelected();
	if (!cs) return;

	#ifdef COMPILING_GOTHIC

		oCNpc* npc = dynamic_cast<oCNpc*>(pickedVob);
		if (!npc) return;

		/*
		if (!oCNpc::player) 
		{ 
			oCNpc::player = new oCNpc();
			oCNpc::player->InitByScript(parser.GetIndex(zSTRING("PC_HERO")));
			if (!oCNpcFocus :: focus) oCNpcFocus :: InitFocusModes();
		}
		if (!oCNpc::player->GetAnictrl()) return;
		*/

		int ounr = csmanager->LibValidateOU(cs->GetRoleName());
		npc->state.StartOutputUnit(ounr);
	#endif	
}

void spcCListCutsceneDlg::OnChangeSearch() 
{
	CString text;
	ctrl_search_edit.GetWindowText(text);

	zSTRING searchtext(text.GetBuffer(0));
	zSTRING checktext;
	int z=0;
	zBOOL found=FALSE;
	
	CString entry;
	while (!found && z<ctrl_ou_list.GetCount())
	{
		ctrl_ou_list.GetText(z,entry);
		checktext = entry.GetBuffer(0);
		checktext.Copy(0,searchtext.Length());
		found = (checktext == searchtext);
		if (!found) z++;
	}
	if (found) ctrl_ou_list.SetTopIndex(z);	
}

void spcCListCutsceneDlg::OnCutsceneUpdateOU() 
{
	bool workingDlgOpened = false;
	if (!workingDlg)
	{
		workingDlg = new spcCWorkInfoDlg();
		workingDlg->Create(IDD_WORKING_DLG,NULL);	
		workingDlgOpened = true;
	}

	if (workingDlg) workingDlg->AddMessage("Updating OU ...");
	
	UpdateWithScripts();		

	if (workingDlgOpened)
	{
		workingDlg->CloseWindow();
		workingDlg->DestroyWindow();
		//delete workingDlg;
		workingDlg = 0;	
	};
}

void spcCListCutsceneDlg::OnTest() 
{
	if (!CMainFrame::mainframe) return;

	spcCInfoBar* info = CMainFrame::mainframe->GetInfoBar();
	if (!info) return;

	//zCCSPlayer*  csplayer	= info->GetCurrentCutscenePlayer();
	zCCSManager* csmanager	= info->GetCurrentCutsceneManager();		
	//if (!csplayer) return;
	if (!csmanager) return;
	
	zCVob* pickedVob = info->GetSelectedVob();
	if (!pickedVob) return;

	zCCSBlockBase* cs = GetSelected();
	if (!cs) return;

	#ifdef COMPILING_GOTHIC

		oCNpc* npc = dynamic_cast<oCNpc*>(pickedVob);
		if (!npc) return;

		/*
		if (!oCNpc::player) 
		{ 
			oCNpc::player = new oCNpc();
			oCNpc::player->InitByScript(parser.GetIndex(zSTRING("PC_HERO")));
			if (!oCNpcFocus :: focus) oCNpcFocus :: InitFocusModes();
		}
		if (!oCNpc::player->GetAnictrl()) return;
		*/

		int ounr = csmanager->LibValidateOU(cs->GetRoleName());
		npc->state.StartOutputUnit(ounr);
	#endif		
}

void spcCListCutsceneDlg::OnLoad() 
{
	UpdateData(true);

	if (!CMainFrame::mainframe->GetInfoBar()) return;
	zCCSManager* csmanager	= CMainFrame::mainframe->GetInfoBar()->GetCurrentCutsceneManager();		
	if (!csmanager) return;

	csmanager->LibLoad(zLIB_LOAD_ASCII);
	
	ConstructList();
	UpdateList();

	// Enable Delete-Button?
	/*
	ctrl_button_delete.EnableWindow(false);
	for (int i=0;i<spcConfig.OUFilterList.GetNumInList();i++)
	{
		if (spcConfig.OUFilterList[i]->GetName() == m_ou_filter) 
		{
			ctrl_button_delete.EnableWindow(spcConfig.OUFilterList[i]->AreEntriesDeletable());
		}
	}
	*/

	selected =-1;

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();
}


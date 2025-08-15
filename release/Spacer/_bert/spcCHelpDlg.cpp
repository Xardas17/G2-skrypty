// spcCHelpDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "mainfrm.h"

#include "spcCHelpDlg.h"
#include "spcCConfiguration.h"

#include "zoption.h"
#include "zdisk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const int MAX_TOPICS_IN_LIST = 1;

const zSTRING HELPFILE_SUBDIR = "help\\";
const zSTRING HELPFILE_FILTER = "*.sph";

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCHelpDlg 


spcCHelpDlg::spcCHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCHelpDlg)
	m_helptext = _T("");
	//}}AFX_DATA_INIT
	winID = 0;
}


void spcCHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCHelpDlg)
	DDX_Control(pDX, IDC_HELPTEXT, ctrl_helptext);
	DDX_Text(pDX, IDC_HELPTEXT, m_helptext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCHelpDlg, CDialog)
	//{{AFX_MSG_MAP(spcCHelpDlg)
	ON_WM_CLOSE()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCHelpDlg 


void spcCHelpDlg::SetHelpTopic(spcTHelpTopicType type, const zSTRING& topic)
{	
	if (topic.IsEmpty()) 
	{
		return;
	};

	zSTRING topicTypeText = HELP_TOPIC_TYPE_STRING[(int)type];		
	
	// Ist ein Klassenpfad angegeben
	zSTRING classPath = topic;
	zSTRING topicName = topic;
	bool hasClassPath = (classPath.Search(HELP_CLASS_DELIMITER)>=0);
	classPath.Delete(HELP_CLASS_DELIMITER,zSTR_TO);	
	topicName.Delete(HELP_CLASS_DELIMITER,zSTR_FROM);	

	zSTRING searchText;
	zSTRING topicText;
	bool ready = false;
	int nr=1;
	while (!ready)
	{		
// [BENDLIN] TEST
// #define	SPACER_HELP_LOG
#ifdef	SPACER_HELP_LOG
		zFILE_FILE::DirectFileAccess(true);
		zFILE_FILE* log = new zFILE_FILE;
		log->Open(zoptions->GetDirString(DIR_TOOLS_CONFIG) + HELPFILE_SUBDIR + "_topics_.log", true);
		log->Append();
#endif
		// Suchstring ermitteln
		if (hasClassPath)
		{
			zSTRING className = classPath.PickWord(nr,": ",": ");
			if (className.IsEmpty()) { topicText="";break;}
			nr++;			
			searchText = "[TOPIC "+topicTypeText+" '"+className+"::"+topicName+"']";
			topicText  = topicTypeText+": "+topicName+" ("+className+")" + "\r\n";
#ifdef	SPACER_HELP_LOG
			log->Write(className + "::" + topicName + "'] (" + topicTypeText + " - " + topic + ")\n");
#endif
		}
		else 
		{
			searchText = "[TOPIC "+topicTypeText+" '"+topicName+"']";
			topicText  = topicTypeText+": "+topicName + "\r\n";
			ready = true;
#ifdef	SPACER_HELP_LOG
			log->Write(topicName+ "'] (" + topicTypeText + " - " + topic + ")\n");
#endif
		}
#ifdef	SPACER_HELP_LOG
		log->Close();
		delete log;
		zFILE_FILE::DirectFileAccess(false);
#endif

		// Suchen
		zERR_MESSAGE(9,0,"B: SPC: Searching for online-help \""+searchText+"\"");
		int index = help_pool.Search(searchText);

		// Falls gefunden: Anzeigen und raus
		if (index>=0) 		
		{			
			zSTRING info = help_pool.Copied(index);		
			info.Delete("\n",zSTR_TO);	// Loesche TOPIC-Eintrag
			info.Delete("[",zSTR_FROM);	// Loesche nachfolgende Eintraege			
			topicText = topicText + info +"\r\n";
			ready=true;
		};
	}

	topicList.AddHead( CString(topicText.ToChar()) );
	if (topicList.GetCount()>MAX_TOPICS_IN_LIST) topicList.RemoveTail();

	m_helptext="";
	POSITION pos = topicList.GetHeadPosition();
	while (pos)
	{
		m_helptext += topicList.GetNext(pos);		
		m_helptext += "\r\n";
	};	
	
	UpdateData(false);

}

BOOL spcCHelpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	

	spcCWindowResizeStyle* style;
		
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_helptext,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	winID = spcConfig.GetWindowID("winInformation");
	spcTRegWindowInfo winInfo;
	spcConfig.GetWindowPosition(winID,winInfo);
	
	MoveWindow(
		winInfo.position.pos.x,
		winInfo.position.pos.y,
		winInfo.position.size.cx,
		winInfo.position.size.cy,
		TRUE);	
	
	// [BENDLIN] Addon Patch2 - Spacer-Help im _physikalischen_ Pfad /_work/data/help/
	
	// Loading help-files
	help_pool.Clear();
	zoptions->ChangeDir(DIR_TOOLS_CONFIG);
	zFILE_FILE path(HELPFILE_SUBDIR);
	path.ChangeDir();
	zFILE_FILE file("");
	bool found = file.FindFirst(HELPFILE_FILTER);
	zSTRING s;
	while (found)
	{	
		zERR_MESSAGE(3,0,"B: SPC: Reading Helpfile "+file.GetFile());
		if (file.Open()==zERR_NONE)
		{
			while (!file.Eof())
			{
				file.Read(s);
				s.Delete("//",zSTR_FROM);
				if (!s.IsEmpty()) help_pool = help_pool+"\r\n"+s;
			};
			file.Close();		
		}
		else
		{
			zERR_MESSAGE(3,0,"B: SPC: ... could not be opened");
		};
		found = file.FindNext();		
	};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCHelpDlg::OnClose() 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CDialog::OnClose();
}

void spcCHelpDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	if (winID>0)
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
		if (CMainFrame::mainframe) CMainFrame::mainframe->OnMoveChild();
	}	
}

void spcCHelpDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (winID)
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
		if (CMainFrame::mainframe) CMainFrame::mainframe->OnMoveChild();
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

void spcCHelpDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
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
		else
		{
			RECT rect;
			GetWindowRect(&rect);
			spcConfig.SetWindowPosition(winID,rect);
		};

	}			
}

void spcCHelpDlg::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	// CDialog::OnOK();
}

void spcCHelpDlg::OnCancel() 
{
	ShowWindow(SW_MINIMIZE);
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	// CDialog::OnCancel();
}

void spcCHelpDlg::ClearTopics()
{
	while (!topicList.IsEmpty()) topicList.RemoveTail();
	m_helptext="";
	UpdateData(false);
};

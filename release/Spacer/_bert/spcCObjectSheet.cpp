// spcCObjectSheet.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "SpacerDoc.h"
#include "mainfrm.h"
#include "spcCObjectSheet.h"
#include "spcCConfiguration.h"
#include "spcCWindowResizeStyle.h"

#include "zwaynet.h"
#include "zarchiver.h"
#include "zzone.h"
#include "zworld.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const ID_ACTION_BUTTON = WM_USER + 7205;

const char* BUTTON_TEXT_EMPTY				= "";
const char* BUTTON_TEXT_CREATE_ACTIVATE		= "Activate";
const char* BUTTON_TEXT_MODIFY_APPLY		= "Apply";


/////////////////////////////////////////////////////////////////////////////
// spcCObjectSheet

IMPLEMENT_DYNAMIC(spcCObjectSheet, CPropertySheet)

spcCObjectSheet::spcCObjectSheet()
{
	actionButton = 0;
	AddPages();
	winID = 0;
}

spcCObjectSheet::spcCObjectSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{	
	actionButton = 0;

	AddPages();
	winID = 0;
	Init(pszCaption,pParentWnd);
}


spcCObjectSheet::~spcCObjectSheet()
{
	zRELEASE(current_object);

	actionButton->CloseWindow();
	delete actionButton;
	actionButton = 0;

	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing ObjectSheet-Instance ...");	
	zERR_MESSAGE(7,zERR_END,"");
}

void spcCObjectSheet::Init(CString title, CWnd* parentWin)
{
	Create(parentWin
				//WS_BORDER | WS_CAPTION | WS_VISIBLE | WS_THICKFRAME,
				//WS_EX_TOOLWINDOW | WS_EX_TOPMOST 
			);			
	SetWindowText(title);
}

BEGIN_MESSAGE_MAP(spcCObjectSheet, CPropertySheet)
	//{{AFX_MSG_MAP(spcCObjectSheet)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_BN_CLICKED(ID_ACTION_BUTTON, OnActionButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCObjectSheet 

void spcCObjectSheet::AddPages()
{	
	/*
	m_psh.dwFlags |= PSH_MODELESS;
	m_psh.dwFlags &= ~PSH_NOAPPLYNOW;
	m_psh.dwFlags |= PSH_HASHELP;	 
	*/
	current_object = 0;
		
	AddPage(&creationPage);		
	AddPage(&modifyPage);	
	AddPage(&manipulatePage);	
}

BOOL spcCObjectSheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	
	return CPropertySheet::OnNotify(wParam, lParam, pResult);
}

BOOL spcCObjectSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// Style setzen
	ModifyStyle(WS_SYSMENU | WS_MAXIMIZEBOX, WS_THICKFRAME | DS_MODALFRAME,0);
	ModifyStyleEx(0,WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME,0);
		
	RECT rect;
	/*
	GetWindowRect(&rect);
	MoveWindow(
		rect.left,
		rect.top,
		rect.right-rect.left,
		rect.bottom-rect.top,
		TRUE);
	*/

	GetClientRect(&rect);

	rect.left		= rect.right	-	102;
	rect.top		= rect.top		+	2;

	rect.right		= rect.left		+	100;	
	rect.bottom		= rect.top		+	23;
	
	// Resizing-Elemente festlegen
	spcCWindowResizeStyle* style;

	SetActivePage(&manipulatePage);
	style = new spcCWindowResizeStyle;
	style->Init(&manipulatePage,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);		
	childResizeList.AddTail(style);			

	SetActivePage(&modifyPage);
	style = new spcCWindowResizeStyle;
	style->Init(&modifyPage,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);		
	childResizeList.AddTail(style);	

	SetActivePage(&creationPage);
	style = new spcCWindowResizeStyle;
	style->Init(&creationPage,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);		
	childResizeList.AddTail(style);		

	actionButton = new CButton();
	actionButton->Create("", BS_PUSHBUTTON|WS_VISIBLE|WS_CHILD|WS_TABSTOP, rect, this, ID_ACTION_BUTTON );
	SetActionButtonText(BUTTON_TEXT_CREATE_ACTIVATE);
	
	style = new spcCWindowResizeStyle;
	style->Init(actionButton,this, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_TOP);		
	childResizeList.AddTail(style);
	
	creationPage.Enable(true);
	manipulatePage.Enable(false);
	modifyPage.Enable(false);
	
	// Fensterposition ermitteln
	winID = spcConfig.GetWindowID("winObjectOperations");
	spcTRegWindowInfo winInfo;
	spcConfig.GetWindowPosition(winID,winInfo);
	
	MoveWindow(
		winInfo.position.pos.x,
		winInfo.position.pos.y,
		winInfo.position.size.cx,
		winInfo.position.size.cy,
		TRUE);

	SetWindowText("Objects");

	return bResult;
}

void spcCObjectSheet::SelectObject(zCObject* object, zBOOL show)
{	
	if (manipulatePage.isEnabled) return;	

	zRELEASE(current_object);
	current_object = object;
	if (current_object) current_object->AddRef();

	if (!object)
	{
		modifyPage.ClearContents();		
		SetActivePage(&creationPage);
		return;
	}

	// zCVob
	if (object->CheckInheritance(zCVob::GetStaticClassDef(),object->GetClassDef()))
	{
		SetBaseClass("zCVob");
	}
	else
	// zCMaterial	
	if (object->CheckInheritance(zCMaterial::GetStaticClassDef(),object->GetClassDef()))
	{
		SetBaseClass("zCMaterial");
	}
	else 
	// zCEventMessage
	if (object->CheckInheritance(zCEventMessage::GetStaticClassDef(),object->GetClassDef()))
	{
		SetBaseClass("zCEventMessage");
	}				

	// daten setzen		
	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);
	arch->SetStringEOL(zSTRING("\n"));	
	arch->WriteObject(object);
	zSTRING arcString;
	arch->GetBufferString(arcString);
	modifyPage.SetProperties(arcString);
	arch->Close();
	zRELEASE(arch);

	// Soll auch die Seite gewechselt werden?
	if (show)	
	{
		if (current_object)
		{
			SetActivePage(&modifyPage);
			modifyPage.Enable(true);		
		}
		else
		{
			SetActivePage(&creationPage);
			modifyPage.Enable(false);		
		};
	}

	actionButton->EnableWindow(current_object && !current_object->GetClassDef()->IsScriptedClass());
		
	// AfxGetMainWnd()->SetFocus();
};


void spcCObjectSheet::OnSize(UINT nType, int cx, int cy) 
{	
	CPropertySheet::OnSize(nType, cx, cy);

	RECT rect;   
    GetClientRect(&rect);

	CTabCtrl* ctrl_tab = GetTabControl();
	if (ctrl_tab)
	{
		ctrl_tab->AdjustRect(FALSE, &rect);
		ctrl_tab->MoveWindow(&rect, TRUE);   
	}

	if (winID>0 && IsWindowVisible())
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

void spcCObjectSheet::OnMove(int x, int y) 
{
	CPropertySheet::OnMove(x, y);
	
	if (winID>0 && IsWindowVisible())
	{
		RECT rect;
		GetWindowRect(&rect);
		spcConfig.SetWindowPosition(winID,rect);
		if (CMainFrame::mainframe) CMainFrame::mainframe->OnMoveChild();
	}
	
}

void spcCObjectSheet::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertySheet::OnShowWindow(bShow, nStatus);
	
	if (winID>0)
	{
		if (bShow && IsWindowVisible())
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

int spcCObjectSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{	
	EnableStackedTabs(FALSE);
	  
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;	
		
	return 0;
}


void spcCObjectSheet::OnActionButton()
{
	zERR_MESSAGE(6,0,"B: SPC: ActionButton");

	if (creationPage.IsWindowVisible())
	{
		CMainFrame::mainframe->OnObjStandardMode();
	}
	else if (modifyPage.IsWindowVisible())
	{	
		if (!current_object) return;		

		zCWaypoint* wp=0;
		if (dynamic_cast<zCVobWaypoint*>(current_object))
		{
			zCWorld* world = CSpacerDoc::doc->GetWorld();
			zCWayNet* waynet = (world)?world->GetWayNet():0;
			wp = (waynet)?waynet->SearchWaypoint(static_cast<zCVobWaypoint*>(current_object)):0;
		}
	
		zSTRING propString;
		modifyPage.GetProperties(propString);

		zCBuffer buf(propString.ToChar(),propString.Length());
		zCArchiver* arch = zarcFactory.CreateArchiverRead(&buf);
		arch->SetStringEOL(zSTRING("\n"));
						
		arch->ReadObject(current_object);
		arch->Close();		
		zRELEASE(arch);
	
		if (wp)
		{
			zSTRING name = current_object->GetObjectName();
			wp->SetName(name);
		};

		if (CMainFrame::mainframe) 
		{			
			CMainFrame::mainframe->HandleObjChange(current_object, UPDATE_FOCUS);
			CMainFrame::mainframe->SetFocus();		
		}

		//
		// Anzeige Aktualisieren?
		// Achtung: Neuaufbau des Property-Baumes
		//
		if (dynamic_cast<zCEventMessage*>(current_object))
		{
			current_object->AddRef();
			SelectObject(current_object);
			current_object->Release();
		};
	}
};

void spcCObjectSheet::SetActionButtonText(CString text)
{
	if (actionButton)
	{		
		actionButton->SetWindowText(text);
		if (text==BUTTON_TEXT_MODIFY_APPLY)
		{
			actionButton->ShowWindow(SW_SHOW);
			actionButton->EnableWindow(current_object && !current_object->GetClassDef()->IsScriptedClass() && !text.IsEmpty());
		}
		else if (text==BUTTON_TEXT_CREATE_ACTIVATE)
		{
			actionButton->ShowWindow(SW_SHOW);
			actionButton->EnableWindow(!text.IsEmpty());
		}
		else
		{
			actionButton->ShowWindow(SW_HIDE);
			actionButton->EnableWindow(FALSE);
		};
	}
};

zCObject* spcCObjectSheet::CreateNewObject()
{
	if (creationPage.IsWindowVisible())
	{
		zCObject* obj = creationPage.CreateNewObject();
		return obj;
	};
	return 0;
}

bool spcCObjectSheet::CreateNewObjectCheck(CString& classname)
{
	bool result = IsWindowVisible() && creationPage.IsWindowVisible();
	if (result) classname = creationPage.GetSelectedClassName();
	return result;
}

void spcCObjectSheet::StartEditBoundingBox()
{
	zCVob* vob = dynamic_cast<zCVob*>(current_object);
	if (!vob) return;	
	
	manipulatePage.Enable(true);

	SetActivePage(&manipulatePage);	
	manipulatePage.ActivateEditBoundingBox(vob);

	creationPage.Enable(false);
	modifyPage.Enable(false);		

	dragVobCtrl.StartDragging(vob);	
}

void spcCObjectSheet::StopEditBoundingBox()
{		
	dragVobCtrl.StopDragging();

	manipulatePage.ActivateEditBoundingBox(0);

	manipulatePage.Enable(false);
	creationPage.Enable(true);
	modifyPage.Enable(true);		
			
	if (current_object) SetActivePage(&modifyPage);			
	else SetActivePage(&creationPage);			

}


zBOOL spcCObjectSheet::GetBoundingbox(zTBBox3D& box)
{
	if (!dynamic_cast<zCVob*>(current_object)) return FALSE;
	
	box = dynamic_cast<zCVob*>(current_object)->GetBBox3DWorld();

	return TRUE;
};

zBOOL spcCObjectSheet::SetBoundingbox(zTBBox3D& box)
{
	if (!dynamic_cast<zCVob*>(current_object)) return FALSE;

	StopEditBoundingBox();
	dynamic_cast<zCVob*>(current_object)->SetBBox3DWorld(box);		
	StartEditBoundingBox();

	return TRUE;
};


zCVob* spcCObjectSheet::IsEditingBoundingBox()
{
	return dragVobCtrl.GetTargetVob();	
}

void spcCObjectSheet::UpdateEditingBoundingBox()
{
	dragVobCtrl.Process();
}


void spcCObjectSheet::SetBaseClass(zSTRING class_name)
{
	baseClass = class_name;
	bool changed = creationPage.SetBaseClass(baseClass);
	if (changed) SelectObject(0);
};

zCObject* spcCObjectSheet::UpdateObjectFromPreset(zCObject* obj)
{
	if (!obj) return 0;
	if (!creationPage.IsWindowVisible()) return 0;
	return creationPage.UpdateObjectFromPreset(obj);
};

void spcCObjectSheet::DisableCreationPage(bool disable)
{
	creationPage.Enable(!disable);
}


void spcCObjectSheet::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{	

};

void spcCObjectSheet::HandleVobRemove(zCVob* vob)
{
	if (vob==current_object) SelectObject(0);
};


void spcCObjectSheet::HandleObjSelect(zCObject* obj)
{
	SelectObject(obj);	
};

void spcCObjectSheet::HandleObjChange(zCObject* obj)
{
	SelectObject(obj);
};


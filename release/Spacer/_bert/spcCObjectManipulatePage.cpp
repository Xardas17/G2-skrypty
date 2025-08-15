// spcCObjectManipulatePage.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCObjectManipulatePage.h"
#include "spcCWindowResizeStyle.h"
#include "spcCObjectSheet.h"
#include "spcCBBoxDefineDlg.h"

#include "zvob.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const CString ACTION_NAME_STOP_BBOX = "Stop";

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite spcCObjectManipulatePage 

IMPLEMENT_DYNCREATE(spcCObjectManipulatePage, CPropertyPage)

spcCObjectManipulatePage::spcCObjectManipulatePage() : CPropertyPage(spcCObjectManipulatePage::IDD)
{
	//{{AFX_DATA_INIT(spcCObjectManipulatePage)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	isEnabled = true;
}

spcCObjectManipulatePage::~spcCObjectManipulatePage()
{
}

void spcCObjectManipulatePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCObjectManipulatePage)
	DDX_Control(pDX, IDC_INFORMATION, ctrl_information);
	DDX_Control(pDX, IDC_ACTION_RIGHT, ctrl_action_right);
	DDX_Control(pDX, IDC_ACTION_LEFT, ctrl_action_left);
	DDX_Control(pDX, IDC_ACTION_CENTER, ctrl_action_center);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCObjectManipulatePage, CPropertyPage)
	//{{AFX_MSG_MAP(spcCObjectManipulatePage)
	ON_WM_CLOSE()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_ACTION_CENTER, OnActionCenter)
	ON_BN_CLICKED(IDC_ACTION_LEFT, OnActionLeft)
	ON_BN_CLICKED(IDC_ACTION_RIGHT, OnActionRight)
	ON_BN_CLICKED(IDC_ACTION_DEFINE, OnActionDefine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCObjectManipulatePage 

void spcCObjectManipulatePage::OnClose() 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CPropertyPage::OnClose();
}

BOOL spcCObjectManipulatePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	spcCWindowResizeStyle* style;

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_action_left,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
		
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_action_center,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_action_right,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_information,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCObjectManipulatePage::OnMove(int x, int y) 
{
	CPropertyPage::OnMove(x, y);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

void spcCObjectManipulatePage::OnSize(UINT nType, int cx, int cy) 
{	
	CPropertyPage::OnSize(nType, cx, cy);	

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

void spcCObjectManipulatePage::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	if (bShow)	
	{		
		((spcCObjectSheet*)GetParent())->SetActionButtonText(BUTTON_TEXT_EMPTY);				
	};
}

void spcCObjectManipulatePage::ActivateEditBoundingBox(zCVob* vob)
{
	if (vob)
	{	
		EnableWindow(true);
		zSTRING infotext = 
			zSTRING("editing boundingbox\r\n\r\n")
			+zSTRING("of vob \r\n\r\n")
			+vob->GetClassDef()->GetClassName_()+zSTRING(":")
			+vob->GetVobName();

		ctrl_action_left.ShowWindow(SW_SHOW);
		ctrl_information.SetWindowText(infotext.ToChar());

		ctrl_action_left.ShowWindow(SW_SHOW);
		ctrl_action_left.SetWindowText(ACTION_NAME_STOP_BBOX);

		ctrl_action_center.ShowWindow(SW_HIDE);		
		ctrl_action_right.ShowWindow(SW_HIDE);		
	}
	else
	{
		EnableWindow(false);
		
		ctrl_information.SetWindowText("");
		ctrl_action_left.ShowWindow(SW_HIDE);
		ctrl_action_left.ShowWindow(SW_HIDE);
		ctrl_action_center.ShowWindow(SW_HIDE);
		ctrl_action_right.ShowWindow(SW_HIDE);
	};
}

void spcCObjectManipulatePage::DoAction(CString name)
{
	if (name == ACTION_NAME_STOP_BBOX)
	{
		((spcCObjectSheet*)GetParent())->StopEditBoundingBox();
	};
};

void spcCObjectManipulatePage::OnActionCenter() 
{
	CString title;
	ctrl_action_center.GetWindowText(title);
	DoAction(title);
}

void spcCObjectManipulatePage::OnActionLeft() 
{
	CString title;
	ctrl_action_left.GetWindowText(title);
	DoAction(title);
}

void spcCObjectManipulatePage::OnActionRight() 
{
	CString title;
	ctrl_action_right.GetWindowText(title);
	DoAction(title);
}

void spcCObjectManipulatePage::Enable(bool enabled)
{
	EnableWindow(enabled);

	ctrl_information.EnableWindow(enabled);
	ctrl_action_right.EnableWindow(enabled);
	ctrl_action_left.EnableWindow(enabled);
	ctrl_action_center.EnableWindow(enabled);

	isEnabled = enabled;	
}

void spcCObjectManipulatePage::OnActionDefine() 
{		
	zCVob* vob = ((spcCObjectSheet*)GetParent())->GetSelectedVob();
	if (vob)
	{		
		vob->AddRef();

		zPOINT3 centerPt = vob->GetPositionWorld();				
		zTBBox3D box;
		box = vob->GetBBox3DWorld();		

		spcCBBoxDefineDlg dlg;	
		dlg.m_dx = (float)((int)(box.maxs.n[VX] - box.mins.n[VX]));
		dlg.m_dy = (float)((int)(box.maxs.n[VY] - box.mins.n[VY]));
		dlg.m_dz = (float)((int)(box.maxs.n[VZ] - box.mins.n[VZ]));
		if (dlg.DoModal() == IDOK)
		{
			box.maxs.n[VX] = centerPt.n[VX]+int(dlg.m_dx/2);
			box.mins.n[VX] = centerPt.n[VX]-int(dlg.m_dx/2);
			
			box.maxs.n[VY] = centerPt.n[VY]+int(dlg.m_dy/2);
			box.mins.n[VY] = centerPt.n[VY]-int(dlg.m_dy/2);
			
			box.maxs.n[VZ] = centerPt.n[VZ]+int(dlg.m_dz/2);
			box.mins.n[VZ] = centerPt.n[VZ]-int(dlg.m_dz/2);
								
			((spcCObjectSheet*)GetParent())->StopEditBoundingBox();
			vob->SetBBox3DWorld(box);
			((spcCObjectSheet*)GetParent())->StartEditBoundingBox();
		};
		zRELEASE(vob);
	}
}

// spcCObjectScriptedDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCObjectScriptedDlg.h"
#include "spcCDibSection.h"

#include "zparser.h"
#include "zworld.h"
#include "zview.h"


// pfui pfui
#ifdef COMPILING_GOTHIC
	#include "oitem.h"
#endif

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCObjectScriptedDlg 


spcCObjectScriptedDlg::spcCObjectScriptedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCObjectScriptedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCObjectScriptedDlg)
	m_object_name = _T("");
	m_object_type = _T("");
	m_selected_instance = _T("");
	//}}AFX_DATA_INIT
	classDef = 0;	
	dib = NULL;	
	vob = NULL;
	dtp_item = NULL;
	// DEACTIVATED: world = new zCWorld();
	mouse_down = false;
}

spcCObjectScriptedDlg::~spcCObjectScriptedDlg()
{
	zRELEASE(vob);	
	// DEACTIVATED: zRELEASE(world);
};

void spcCObjectScriptedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCObjectScriptedDlg)
	// DEACTIVATED:  DDX_Control(pDX, IDC_VIEW, ctrl_viewport);
	DDX_Control(pDX, IDC_INSTANCE_LIST, ctrl_list);
	DDX_Control(pDX, IDC_INSERT_OBJECT, ctrl_insert);	
	DDX_Control(pDX, IDC_OBJECT_TYPE, ctrl_objecttype);	
	DDX_Text(pDX, IDC_OBJECT_NAME, m_object_name);
	DDX_Text(pDX, IDC_OBJECT_TYPE, m_object_type);
	DDX_LBString(pDX, IDC_INSTANCE_LIST, m_selected_instance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCObjectScriptedDlg, CDialog)
	//{{AFX_MSG_MAP(spcCObjectScriptedDlg)
	ON_BN_CLICKED(IDC_INSERT_OBJECT, OnInsertObject)
	ON_LBN_DBLCLK(IDC_INSTANCE_LIST, OnDblclkInstanceList)
	ON_LBN_SELCHANGE(IDC_INSTANCE_LIST, OnSelchangeInstanceList)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCObjectScriptedDlg 

void spcCObjectScriptedDlg::OnCancel() 
{	
	CDialog::OnCancel();
}

void spcCObjectScriptedDlg::OnInsertObject() 
{
	CDialog::OnOK();
}

void spcCObjectScriptedDlg::OnDblclkInstanceList() 
{
	/* DEACTIVATED:
#ifdef COMPILING_GOTHIC
	UpdateData(true);	

	if (vob) zRELEASE(vob);

	zSTRING instance = m_selected_instance.GetBuffer(0);
	
	vob = dynamic_cast<zCVob*>(zCObject::CreateNewInstance(classname));
	if (!vob) return;

	if (dynamic_cast<oCItem*>(vob))
	{
		dynamic_cast<oCItem*>(vob)->InitByScript(parser.GetIndex(instance));
	}
	else zRELEASE(vob);

	// vob->RotateLocal(1,0,0,90);

	OnPaint();
#endif
	*/
}

void spcCObjectScriptedDlg::OnSelchangeInstanceList() 
{
	UpdateData(true);
	
}

void spcCObjectScriptedDlg::SetObjectClass(zSTRING _classname)
{
	zERR_MESSAGE(9,0,"B: spcCObjectScriptedDlg: SetObjectClass");
	classname = _classname;	
	m_object_type = CString(classname.ToChar());
	classDef = zCObject::GetClassDef(classname);
	if (!classDef->IsScriptedClass()) classDef = 0;	
	zERR_MESSAGE(9,0,"B: spcCObjectScriptedDlg: SetObjectClass finished");
}

zSTRING spcCObjectScriptedDlg::GetObjectName()
{
	return zSTRING(m_object_name.GetBuffer(0));
}

zSTRING spcCObjectScriptedDlg::GetObjectInstance()
{	
	return zSTRING(m_selected_instance.GetBuffer(0));
}

BOOL spcCObjectScriptedDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	zERR_MESSAGE(9,0,"B: spcCObjectScriptedDlg: OnInitDialog");

	zSTRING scriptClassName="";
	if (classname == "oCItem") scriptClassName = "C_Item";
	else if (classname == "oCNpc") scriptClassName = "C_NPC";		
		
	if (classDef && !scriptClassName.IsEmpty())
	{
		if (!classDef->IsScriptedClass()) classDef = 0;
				
		instance_list.DeleteListDatas();
		instance_list.DeleteList();
					
		zERR_MESSAGE(9,0,"B: spcCObjectScriptedDlg: OnInitDialog: Fetching instances from parser... ");

		int pos,typ,anz,c,classindex;
		// zSTRING* s;
		CString f1,f2,f3;	
		classindex = parser.GetIndex(scriptClassName);
		if (classindex!=-1)
		{			
			parser.GetSymbolInfo(classindex,typ,anz);
			pos = parser.GetInstance(classindex,0);			

			zERR_MESSAGE(9,0,"B: spcCObjectScriptedDlg: OnInitDialog: Looping ... ");

			while (pos>=0)
			{				
				zSTRING s = parser.GetSymbolInfo(pos,typ,c);
				// instance_list.Insert(s);
				ctrl_list.AddString(s.ToChar());
				pos = parser.GetInstance(classindex,pos+1);			
			}

			zERR_MESSAGE(9,0,"B: spcCObjectScriptedDlg: OnInitDialog: Looping ... finished");
		
		}
	};
	
	// DEACTIVATED: ctrl_viewport.GetClientRect(&view_rect);
	view_size.cx = abs(view_rect.right  - view_rect.left);
	view_size.cy = abs(view_rect.bottom - view_rect.top);	
	if (view_size.cx % 2 !=0) view_size.cx++;

	mouse_down = false;

	// [EDENFELD] 1.33: eingefüge Script Objekte bleiben jetzt im Menu und müssen nicht immer wieder
	// umständlich neu aus der Objectliste geholt werden
	if (!m_selected_instance.IsEmpty())
	{
		ctrl_list.SelectString(0, m_selected_instance);
	}

	zERR_MESSAGE(9,0,"B: spcCObjectScriptedDlg::OnInitDialog finished");

	return TRUE;  
}

void spcCObjectScriptedDlg::OnPaint() 
{	
	CDialog::OnPaint();
	return; 
	/* DEACTIVATED:
		CPaintDC dc(this); // device context for painting

	#ifdef COMPILING_GOTHIC
		if (!dib)
		{
			dib = new spcCDibSection;		
			dib->Create(view_size.cx,view_size.cy,16);
			dtp_item = new zCView(0,0,screen->anx(view_size.cx),screen->any(view_size.cy),VIEW_VIEWPORT);
			screen->InsertItem(dtp_item);		
		}

		// draw texture 
		if (!vob) return;
		if (!dtp_item) return;

		CDC* pDC = ctrl_viewport.GetDC();

		// get material and texture		
		zrenderer->Vid_Clear(zCOLOR(100,100,100,255));
		if (dynamic_cast<oCItem*>(vob))
		{
			dynamic_cast<oCItem*>(vob)->oCItem::RenderItem(world,dtp_item,0.0);
		}
		
		screen->DrawItems();
		zrenderer->Vid_Blit();

	#endif
	*/
}

void spcCObjectScriptedDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (mouse_down && vob)
	{	
		int xmove=0, ymove=0, zmove=0;
		
		xmove = point.y-lastpoint.y;
		if (nFlags & MK_CONTROL) 
			 ymove = point.x-lastpoint.x;
		else zmove = point.x-lastpoint.x;
		
		vob->RotateWorld(1.0f,0.0f,0.0f,(float)xmove);
		vob->RotateWorld(0.0f,1.0f,0.0f,(float)ymove);
		vob->RotateWorld(0.0f,0.0f,1.0f,(float)zmove);
		
		OnPaint();
		
		lastpoint = point;
	}	

	CDialog::OnMouseMove(nFlags, point);
}

void spcCObjectScriptedDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	mouse_down = false;	
	ReleaseCapture();

	CDialog::OnLButtonUp(nFlags, point);
	OnPaint();	
}

void spcCObjectScriptedDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	mouse_down = true;	
	lastpoint = point;	
	SetCapture();

	CDialog::OnLButtonDown(nFlags, point);
}

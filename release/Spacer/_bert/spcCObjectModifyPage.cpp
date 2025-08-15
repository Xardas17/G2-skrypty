// spcCObjectModifyPage.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCObjectModifyPage.h"
#include "mainfrm.h"

#include "SpacerView.h"
#include "SpacerDoc.h"
#include "zoption.h"

#include "spcCObjectSheet.h"
#include "spcCWindowResizeStyle.h"
#include "spcCHelpDlg.h"
// z-includes
#include "zBuffer.h"
#include "zArchiver.h"
#include "zVob.h"
#include "zWorld.h"
#include "zdisk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const CString	VOB_BBOX_MEMBER = "bbox3DWS";
const zSTRING	SEP_PROP_START  = "----- Start of Properties -----";

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite spcCObjectModifyPage 

IMPLEMENT_DYNCREATE(spcCObjectModifyPage, CPropertyPage)

spcCObjectModifyPage::spcCObjectModifyPage() : CPropertyPage(spcCObjectModifyPage::IDD)
{
	//{{AFX_DATA_INIT(spcCObjectModifyPage)
	m_bool = FALSE;
	m_enum = _T("");
	m_raw = _T("");
	m_string = _T("");
	m_value = _T("");
	m_vec1 = _T("");
	m_vec2 = _T("");
	m_vec3 = _T("");
	m_edit_bbox = FALSE;
	//}}AFX_DATA_INIT

	isEnabled = true;
}

spcCObjectModifyPage::~spcCObjectModifyPage()
{
}

void spcCObjectModifyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCObjectModifyPage)
	DDX_Control(pDX, IDC_DYVALUE_SPIN, ctrl_dynvalue_spin);
	DDX_Control(pDX, IDC_EDIT_AREA, ctrl_edit_area);
	DDX_Control(pDX, IDC_EDIT_BBOX, ctrl_editbox);
	DDX_Control(pDX, IDC_STRING_FILE, ctrl_string_fileopen);
	DDX_Control(pDX, IDC_COLORVIEW, ctrl_colorview);
	DDX_Control(pDX, IDC_EDITCOLOR, ctrl_editcolor);
	DDX_Control(pDX, IDC_DYRAW, ctrl_raw);
	DDX_Control(pDX, IDC_DYVECTOR3, ctrl_vec3);
	DDX_Control(pDX, IDC_DYVECTOR2, ctrl_vec2);
	DDX_Control(pDX, IDC_DYVECTOR1, ctrl_vec1);
	DDX_Control(pDX, IDC_PROPTREE, ctrl_proptree);
	DDX_Control(pDX, IDC_DYVALUE, ctrl_value);
	DDX_Control(pDX, IDC_DYSTRING, ctrl_string);
	DDX_Control(pDX, IDC_DYENUM, ctrl_enum);
	DDX_Control(pDX, IDC_DYBOOL, ctrl_bool);
	DDX_Check(pDX, IDC_DYBOOL, m_bool);
	DDX_CBString(pDX, IDC_DYENUM, m_enum);
	DDX_Text(pDX, IDC_DYRAW, m_raw);
	DDX_Text(pDX, IDC_DYSTRING, m_string);
	DDX_Text(pDX, IDC_DYVALUE, m_value);
	DDX_Text(pDX, IDC_DYVECTOR1, m_vec1);
	DDX_Text(pDX, IDC_DYVECTOR2, m_vec2);
	DDX_Text(pDX, IDC_DYVECTOR3, m_vec3);
	DDX_Check(pDX, IDC_EDIT_BBOX, m_edit_bbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCObjectModifyPage, CPropertyPage)
	//{{AFX_MSG_MAP(spcCObjectModifyPage)
	ON_NOTIFY(TVN_SELCHANGED, IDC_PROPTREE, OnSelchangedProptree)	
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_DYBOOL, OnValChange)
	ON_BN_CLICKED(IDC_EDITCOLOR, OnEditcolor)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_HELP_BUTTON, OnHelpButton)	
	ON_EN_CHANGE(IDC_DYSTRING, OnChangeDystring)
	ON_EN_CHANGE(IDC_DYRAW, OnChangeDyraw)
	ON_EN_CHANGE(IDC_DYVALUE, OnChangeDyvalue)
	ON_EN_CHANGE(IDC_DYVECTOR1, OnChangeDyvector1)
	ON_EN_CHANGE(IDC_DYVECTOR2, OnChangeDyvector2)
	ON_EN_CHANGE(IDC_DYVECTOR3, OnChangeDyvector3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYVALUE_SPIN, OnDeltaposDyvalueSpin)
	ON_BN_CLICKED(IDC_STRING_FILE, OnStringFile)	
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_PROPTREE, OnEndlabeleditProptree)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_PROPTREE, OnBeginlabeleditProptree)
	ON_NOTIFY(NM_RCLICK, IDC_PROPTREE, OnRclickProptree)
	ON_NOTIFY(NM_DBLCLK, IDC_PROPTREE, OnDblclkProptree)	
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_DYENUM, OnValChange)	
	ON_BN_CLICKED(IDC_EDIT_BBOX, OnEditBbox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCObjectModifyPage 



void spcCObjectModifyPage::CreatePropTree()
{	
	if (treeCtrlImageList) ctrl_proptree.SetImageList(treeCtrlImageList, TVSIL_NORMAL);

	ctrl_proptree.DeleteAllItems();	
	// startPos = 0;
	int z=startPos;
	CreatePropTree(z,TVI_ROOT);
	
	HTREEITEM ITEM = ctrl_proptree.GetFirstVisibleItem();
	if (ITEM != 0) ctrl_proptree.Expand(ITEM,TVE_EXPAND);	

	UpdateWindow();
}

void spcCObjectModifyPage::CreatePropTree(int& n, HTREEITEM parent)
{
	// never call with n>=NumInList
	if (n>=propList.GetNumInList()) return;

	HTREEITEM newITEM = CreatePropTreeItem(propList[n],parent,n);	

	propList[n]->SetTreeItem(newITEM);
	
	if (propList[n]->GetPropType()==spcCObjPropertyElement::PETclass ||
		propList[n]->GetPropType()==spcCObjPropertyElement::PETgroup )
	{
		n++;
		while(	n<propList.GetNumInList() && 
				propList[n]->GetPropType() != spcCObjPropertyElement::PETchunkend)
		{
			CreatePropTree(n,newITEM);
			n++;
		}
	}
	if (propList[n]->GetName().Find("Internals",0)<0)
	{
		ctrl_proptree.Expand(newITEM, TVE_EXPAND);
	}
}

HTREEITEM spcCObjectModifyPage::CreatePropTreeItem(spcCObjPropertyElement *ele, HTREEITEM parent, int nr)
{
	if (!ele) return 0;

	CString name = ele->GetDescription();	
	
	int icon = ele->GetIconID();
	TVINSERTSTRUCT insertItem;
    insertItem.hParent = parent;
    insertItem.hInsertAfter = TVI_LAST;	
	insertItem.item.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	insertItem.item.iImage = icon;
	insertItem.item.iSelectedImage = icon;	
	insertItem.item.pszText = name.GetBuffer(0);	
	insertItem.item.cchTextMax = name.GetLength();
	insertItem.item.lParam = (LPARAM)nr;
	// insert
	HTREEITEM resultItem = ctrl_proptree.InsertItem(&insertItem);

	if (zSTRING(insertItem.item.pszText).Search("vobName")!=-1) this->selectTreeItem = resultItem;

	return resultItem;
}

void spcCObjectModifyPage::UpdatePropTree(HTREEITEM item)
{
	int n = ctrl_proptree.GetItemData(item);

	CString entry = propList[n]->GetDescription();
	ctrl_proptree.SetItemText(item,entry.GetBuffer(0));
}

void spcCObjectModifyPage::deactivateAll()
{	
	ctrl_dynvalue_spin.ShowWindow(SW_HIDE);
	m_value = "";	ctrl_value		.ShowWindow(SW_HIDE);
	m_enum = "";	ctrl_enum		.ShowWindow(SW_HIDE);
	m_string = "";	ctrl_string		.ShowWindow(SW_HIDE);
	m_raw = "";		ctrl_raw		.ShowWindow(SW_HIDE);	
	m_bool = false;	ctrl_bool		.ShowWindow(SW_HIDE);
	b_color=false;	ctrl_editcolor	.ShowWindow(SW_HIDE);
					ctrl_colorview	.ShowWindow(SW_HIDE);

	m_vec1 = "";m_vec2 = "";m_vec3 = "";
	ctrl_vec1						.ShowWindow(SW_HIDE);
	ctrl_vec2						.ShowWindow(SW_HIDE);
	ctrl_vec3						.ShowWindow(SW_HIDE);

	ctrl_string_fileopen			.ShowWindow(SW_HIDE);
	
	UpdateData(false);
}
void spcCObjectModifyPage::activateBool(bool v)
{
	ctrl_bool.ShowWindow(SW_SHOW);	
	ctrl_bool.BringWindowToTop();
	m_bool = v;
	UpdateData(false);
}
void spcCObjectModifyPage::activateValue(float v)
{
	ctrl_value.ShowWindow(SW_SHOW);	
	ctrl_value.SetActiveWindow();

	ctrl_value.SetFocus();
	ctrl_value.BringWindowToTop();
	ctrl_dynvalue_spin.ShowWindow(SW_SHOW);
	ctrl_dynvalue_spin.BringWindowToTop();

	m_value = CString(zSTRING(v).ToChar());
	UpdateData(false);
}
void spcCObjectModifyPage::activateEnum(int v)
{
	ctrl_enum.ShowWindow(SW_SHOW);	
	ctrl_enum.SetCurSel(v);
	ctrl_enum.BringWindowToTop();	
	UpdateData(true);  //m_enum setzen	
}
void spcCObjectModifyPage::activateString(CString v)
{
	ctrl_string.ShowWindow(SW_SHOW);	
	ctrl_string.SetActiveWindow();
	ctrl_string.SetFocus();
	ctrl_string.BringWindowToTop();
	m_string = v;	
	UpdateData(false);
}
void spcCObjectModifyPage::activateRaw(CString v)
{
/*	ctrl_raw.EnableWindow(true);
	m_raw = v+CString("\r\n");
	UpdateData(false);*/
	ctrl_string.ShowWindow(SW_SHOW);	
	ctrl_string.SetActiveWindow();
	ctrl_string.SetFocus();
	ctrl_string.BringWindowToTop();
	m_string = v;
	UpdateData(false);
}
void spcCObjectModifyPage::activateVector(zVEC3 v)
{
	ctrl_vec1.ShowWindow(SW_SHOW);	
	ctrl_vec2.ShowWindow(SW_SHOW);	
	ctrl_vec3.ShowWindow(SW_SHOW);	
	ctrl_vec1.BringWindowToTop();
	ctrl_vec2.BringWindowToTop();
	ctrl_vec3.BringWindowToTop();
	
	ctrl_vec1.SetActiveWindow();
	ctrl_vec1.SetFocus();
	m_vec1 = CString(zSTRING(v[0]).ToChar());
	m_vec2 = CString(zSTRING(v[1]).ToChar());
	m_vec3 = CString(zSTRING(v[2]).ToChar());
	UpdateData(false);
}
void spcCObjectModifyPage::activateColor(COLORREF col)
{
	// farbe anzeigen
	m_color = col;
	b_color= true;
	ctrl_editcolor.ShowWindow(SW_SHOW);	
	ctrl_editcolor.BringWindowToTop();
	ctrl_colorview.ShowWindow(SW_SHOW);	
	ctrl_colorview.BringWindowToTop();

	UpdateData(false);
	OnPaint();
}


/////////////////////////////////////////////////////////////////////////////
// spcCObjectModifyPage message handlers


void spcCObjectModifyPage::OnValChange() 
{
	spcCObjPropertyElement::TPropEditType type;
	int seli = 0;

	HTREEITEM selectedItem = ctrl_proptree.GetSelectedItem();
	if (selectedItem) selectTreeItem = selectedItem;
	selected		= ctrl_proptree.GetItemData(selectTreeItem);

	if ((selected<=0) || (selected>=propList.GetNumInList())) return;	

	if (propList[selected]->GetPropType()!=spcCObjPropertyElement::PETclass &&
		propList[selected]->GetPropType()!=spcCObjPropertyElement::PETgroup)
	{
		UpdateData(true);

		zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);
		if (!arch) return;				// [EDENFELD] neu 1.33 aus ModSource. Crash abgefangen

		bool isStringValid = arch->IsStringValid(m_string.GetBuffer(0)) ? true :false;
		bool isValueValid  = arch->IsStringValid(m_value.GetBuffer(0)) ? true :false;		
		arch->Close();
		zRELEASE(arch);

		type = propList[selected]->GetPropType();
		switch (type)
		{
		case spcCObjPropertyElement::PETint	: 			
			if (isValueValid) propList[selected]->SetByStr(m_value);
			break;
		case spcCObjPropertyElement::PETbool	:
			if (m_bool) 
				propList[selected]->SetByInt(1);
			else 
				propList[selected]->SetByInt(0);
			break;
		case spcCObjPropertyElement::PETfloat	:
			if (isValueValid) propList[selected]->SetByStr(m_value);
			break;
		case spcCObjPropertyElement::PETcolor:
		case spcCObjPropertyElement::PETstring:
			if (isStringValid) propList[selected]->SetByStr(m_string);
			break;
		case spcCObjPropertyElement::PETenum	:
			seli = ctrl_enum.GetCurSel();
			propList[selected]->SetByInt(seli);
			break;
		case spcCObjPropertyElement::PETraw	:
			if (isStringValid) propList[selected]->SetByStr(m_string);
			break;
		case spcCObjPropertyElement::PETvec3	:
			propList[selected]->SetByVec( zVEC3(
				zSTRING(m_vec1.GetBuffer(0)).ToFloat(),
				zSTRING(m_vec2.GetBuffer(0)).ToFloat(),
				zSTRING(m_vec3.GetBuffer(0)).ToFloat() )
				);
			break;		
			/*
		case spcCObjPropertyElement::PETcolor	:
			propList[selected]->SetByColor(m_color);
			break;		
			*/
		}

		UpdatePropTree(selectTreeItem);		

		if (!isStringValid)
		{
			MessageBox("String\r\n\""+m_string+"\"\r\nis not valid.");
			m_string="";			
			m_value="";			
		};

		if (!isValueValid)
		{
			MessageBox("Data\r\n\""+m_value+"\"\r\nis not valid.");
			m_value="";
			m_string="";
		};

		UpdateData(false);
	}		

}

void spcCObjectModifyPage::OnEditcolor() 
{	
	CColorDialog dlg(m_color);
	if (dlg.DoModal()==IDOK)
	{
		m_color = dlg.GetColor();
		propList[selected]->SetByColor(m_color);	// Wert durch gewaehlte Farbe setzen
		m_string = propList[selected]->GetStrVal(); // Stringwert setzen		
	}	
}

void spcCObjectModifyPage::OnPaint() 
{
	CPaintDC dc(this);

	if (b_color) 
	{		
		CDC* winDC = ctrl_colorview.GetWindowDC();

		RECT rect;
		ctrl_colorview.GetClientRect(&rect);
		winDC->FillSolidRect(&rect, m_color);
		//winDC.SelectObject(oldBrush);
	}	
}

void spcCObjectModifyPage::OnHelpButton() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}


void spcCObjectModifyPage::OnChangeDystring() 
{
	OnValChange();	
}

void spcCObjectModifyPage::OnChangeDyraw() 
{
	OnValChange();		
}

void spcCObjectModifyPage::OnChangeDyvalue() 
{
	OnValChange();	
}

void spcCObjectModifyPage::OnChangeDyvector1() 
{
	OnValChange();		
}

void spcCObjectModifyPage::OnChangeDyvector2() 
{
	OnValChange();	
}

void spcCObjectModifyPage::OnChangeDyvector3() 
{
	OnValChange();	
}

CONST hack_y = 20;
CONST hack_x = 4;

BOOL spcCObjectModifyPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	zERR_MESSAGE(6,zERR_BEGIN,"B: SPC: Initializing spcCObjectModifyPage-Instance");

	zERR_MESSAGE(7,0,"B: SPC: Imagelist ...");

	treeCtrlImageList = new CImageList;
	treeCtrlImageList->Create(IDR_ICONS_VOBPROPS, 12, 4, RGB(255,255,255));			

	zERR_MESSAGE(7,0,"B: SPC: Control-Positions ...");

	RECT rect;
	ctrl_edit_area.GetWindowRect(&rect);	
	ScreenToClient(&rect);

	RECT vecRect1,vecRect2,colRect, valRect, propRect;
	ctrl_vec1.GetWindowRect(&vecRect1);		ScreenToClient(&vecRect1);
	ctrl_vec2.GetWindowRect(&vecRect2);		ScreenToClient(&vecRect2);
	ctrl_colorview.GetWindowRect(&colRect);	ScreenToClient(&colRect);
	ctrl_value.GetWindowRect(&valRect);		ScreenToClient(&valRect);
	ctrl_proptree.GetWindowRect(&propRect);	ScreenToClient(&propRect);

	int addVec2 = abs(vecRect1.right - vecRect1.left)+5;
	int addVec3 = addVec2 + abs(vecRect2.right - vecRect2.left)+5;
	int addColButton = abs(colRect.right-colRect.left)+5;	
	int addValSpin = abs(valRect.right-valRect.left);	
	
	ctrl_bool.SetWindowPos(&wndTop, rect.left,rect.top,0,0,SWP_NOSIZE);	
	ctrl_enum.SetWindowPos(&wndTop, rect.left,rect.top,0,0,SWP_NOSIZE);
	ctrl_raw.SetWindowPos(&wndTop, rect.left,rect.top,0,0,SWP_NOSIZE);
	ctrl_string.SetWindowPos(&wndTop, rect.left,rect.top,0,0,SWP_NOSIZE);
	ctrl_value.SetWindowPos(&wndTop, rect.left,rect.top,0,0,SWP_NOSIZE);
	ctrl_vec1.SetWindowPos(&wndTop, rect.left,rect.top,0,0,SWP_NOSIZE);
	ctrl_vec2.SetWindowPos(&wndTop, rect.left+addVec2,rect.top,0,0,SWP_NOSIZE);
	ctrl_vec3.SetWindowPos(&wndTop, rect.left+addVec3,rect.top,0,0,SWP_NOSIZE);
	ctrl_dynvalue_spin.SetWindowPos(&wndTop, rect.left+addValSpin,rect.top,0,0,SWP_NOSIZE);

	ctrl_colorview.SetWindowPos(&wndTop, rect.left,rect.top,0,0,SWP_NOSIZE);	
	ctrl_editcolor.SetWindowPos(&wndTop, rect.left+addColButton,rect.top,0,0,SWP_NOSIZE);	
	
	ctrl_string_fileopen.ShowWindow(SW_SHOW);
	
	ctrl_editbox.SetWindowText("Edit the Bbox");

	zERR_MESSAGE(7,0,"B: SPC: Resize settings ...");

	spcCWindowResizeStyle* style;

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_proptree,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_string_fileopen,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_raw,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_string,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_editbox,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_vec1,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_vec2,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_vec3,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_value,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_colorview,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_editcolor,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_edit_area,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_bool,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_enum,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_dynvalue_spin,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM);	
	childResizeList.AddTail(style);

	deactivateAll();
		
	UpdateData(false);
			
	zERR_MESSAGE(6,zERR_END,"");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void spcCObjectModifyPage::OnStringFile() 
{
	zoptions->ChangeDir(DIR_DATA);	
	CFileDialog dlg(TRUE,"","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"All files (*.*)|*.*||");	
	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{
		m_string = dlg.GetFileName();		
	}
	UpdateData(FALSE);	
	OnChangeDystring();
}

void spcCObjectModifyPage::OnEditBbox() 
{
	StartEditBoundingBox();

	UpdateData(false);
}

void spcCObjectModifyPage::OnBeginlabeleditProptree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	TVITEM item = pTVDispInfo->item;	
		
	// short height = ctrl_proptree.GetItemHeight();

	spcCObjPropertyElement* element = propList.SearchElementByTreeitem(item.hItem);
	if (element)
	{			
		switch (element->GetPropType())
		{
		case spcCObjPropertyElement::PETbool: 			
		case spcCObjPropertyElement::PETint: 
		case spcCObjPropertyElement::PETfloat:
		case spcCObjPropertyElement::PETvec3:		
		case spcCObjPropertyElement::PETcolor:
		case spcCObjPropertyElement::PETenum: 
		case spcCObjPropertyElement::PETstring: 
		case spcCObjPropertyElement::PETraw:
			
			break;		
		case spcCObjPropertyElement::PETclass: 
		case spcCObjPropertyElement::PETgroup: 
		case spcCObjPropertyElement::PETchunkend:
			*pResult = 1;
			return;
			break;
		};
	}
	
	*pResult = 0;
}

void spcCObjectModifyPage::OnEndlabeleditProptree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	TVITEM item = pTVDispInfo->item;
	
	spcCObjPropertyElement* element = propList.SearchElementByTreeitem(item.hItem);
	if (element)
	{			
		CString newValue = item.pszText;
		newValue = spcCObjPropertyElement::PickValue(newValue);	

		element->SetByStr(newValue);
		CString description = element->GetDescription();
		item.pszText = description.GetBuffer(0);
		item.cchTextMax = description.GetLength();
		item.state = TVIF_TEXT;
		
		ctrl_proptree.SetItem(&item);
	};

	*pResult = 0;
}


void spcCObjectModifyPage::OnClose() 
{
	CPropertyPage::OnClose();
}

void spcCObjectModifyPage::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	//CPropertyPage::OnCancel();
}

void spcCObjectModifyPage::OnRclickProptree(NMHDR* pNMHDR, LRESULT* pResult) 
{		
	
	*pResult = 0;
}

void spcCObjectModifyPage::OnSelchangedProptree(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	NMTREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;		

	deactivateAll();
	
	selectTreeItem	= ctrl_proptree.GetSelectedItem();
	selected		= ctrl_proptree.GetItemData(selectTreeItem);	
	
	if (propList.GetNumInList()<=selected) return;

	bool showHelp = false;

	spcCObjPropertyElement::TPropEditType type = propList[selected]->GetPropType();
	switch (type)
	{
	case spcCObjPropertyElement::PETint: 
		activateValue(float(propList[selected]->GetIntVal())); 
		showHelp = true;
		break;
	case spcCObjPropertyElement::PETbool:
		activateBool(bool(propList[selected]->GetIntVal()!=0)); 
		ctrl_bool.SetWindowText(propList[selected]->GetName());
		showHelp = true;
		break;
	case spcCObjPropertyElement::PETfloat	: 
		activateValue(propList[selected]->GetFloatVal());
		showHelp = true;
		 break;	
	case spcCObjPropertyElement::PETcolor	:
	case spcCObjPropertyElement::PETstring	: 
		activateString(propList[selected]->GetStrVal()); 
		ctrl_string_fileopen.ShowWindow(SW_SHOW);
		showHelp = true;
		break;
	case spcCObjPropertyElement::PETenum	: 
		propList[selected]->GetEnumList(ctrl_enum);
		activateEnum(propList[selected]->GetIntVal()); 
		showHelp = true;
		break;
	case spcCObjPropertyElement::PETraw	: 
		activateRaw(propList[selected]->GetStrVal()); 
		showHelp = true;
		break;
	case spcCObjPropertyElement::PETvec3	: 
		activateVector(propList[selected]->GetVecVal()); 
		showHelp = true;
		break;
	/*
	case spcCObjPropertyElement::PETcolor	:
		activateColor(propList[selected]->GetColor()); 		
		showHelp = true;
		break;
	*/
	}

	// Hilfsfenster ?
	if (showHelp) 
	{
		CMainFrame::mainframe->GetHelpWindow()->SetHelpTopic(HELP_TOPIC_MEMBER,propList[selected]->GetName()+HELP_CLASS_DELIMITER+objTypeDescriptor);
	}

	*pResult = 0;
	UpdateWindow();
}




void spcCObjectModifyPage::OnDblclkProptree(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	NMTREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;		

	if (selected<0) return;
	
	UpdateData(true);

	selectTreeItem	= ctrl_proptree.GetSelectedItem();
	selected		= ctrl_proptree.GetItemData(selectTreeItem);	
	
	spcCObjPropertyElement* ele = propList[selected];
	spcCObjPropertyElement::TPropEditType type = ele->GetPropType();

	CString memberName = ele->GetName();
	CString memberValue = ele->GetStrVal();
	if (memberName == VOB_BBOX_MEMBER)
	{		
		spcCObjectSheet* sheet = (spcCObjectSheet*)GetParent();
		if (sheet->IsEditingBoundingBox())
			StopEditBoundingBox();
		else
			StartEditBoundingBox();
	}
	else if (memberValue.Find('.')+1 == memberValue.GetLength()-3)
	{
		OnStringFile();
	}
	else
	{
		switch (type)
		{
			case spcCObjPropertyElement::PETbool:
				ele->ToggleBoolVal();
				m_bool = (ele->GetIntVal()==1);
				break;
			case spcCObjPropertyElement::PETstring	: 
				ctrl_proptree.EditLabel(selectTreeItem);			
				break;
			case spcCObjPropertyElement::PETenum	: 
				ele->ToggleEnumVal();
				m_enum = ele->GetEnumVal();
				break;
			case spcCObjPropertyElement::PETcolor	:
				OnEditcolor();
				break;
		};
	}	
	UpdateData(false);
	
	OnValChange();
		
	*pResult = 0;
}

void spcCObjectModifyPage::OnDeltaposDyvalueSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	UpdateData(true);
	if (pNMUpDown->iDelta>0)
	{
		int value = zSTRING(m_value.GetBuffer(0)).ToInt();
		value--;
		m_value = zSTRING(value).ToChar();
	}
	else if (pNMUpDown->iDelta<0)
	{
		int value = zSTRING(m_value.GetBuffer(0)).ToInt();
		value++;
		m_value = zSTRING(value).ToChar();
	};	
	UpdateData(false);
	
	OnValChange();

	*pResult = 0;
}



void spcCObjectModifyPage::OnSize(UINT nType, int cx, int cy) 
{	
	bool result;
	spcCWindowResizeStyle* style;
	POSITION pos = childResizeList.GetHeadPosition();
	while (pos)
	{
		style = childResizeList.GetNext(pos);
		result = style->UpdateSize();		
		if (!result) return;
	};

	CPropertyPage::OnSize(nType, cx, cy);
}


void spcCObjectModifyPage::SetProperties(zSTRING& propString)
{	
	propList.DeleteList();
	
	// buffer auseinander nehmen	
	int z=1;
	zSTRING w = propString.PickWord(z,"\n\t","\n\t");
	while (w.Search("[")==-1)
	{
		spcCObjPropertyElement* ele = new spcCObjPropertyElement(w.ToChar());		
		propList.Insert(ele);		
		z++;
		w = propString.PickWord(z,"\n\t","\n\t");
	}

	// Leerzeile
	spcCObjPropertyElement* ele = new spcCObjPropertyElement("");		
	propList.Insert(ele);

	startPos = propList.GetNumInList();

	ele = new spcCObjPropertyElement(w.ToChar());
	propList.Insert(ele);	
	objTypeDescriptor = ele->GetName();
	while (!w.IsEmpty())
	{
		z++;
		w = propString.PickWord(z,"\n\t","\n\t");
		spcCObjPropertyElement* ele = new spcCObjPropertyElement(w.ToChar());	
		propList.Insert(ele);
		if (w.Search("vobName") != -1)
		{
			activateString(w.PickWord(2,":",":").ToChar());
		}
	}

	CreatePropTree();

	UpdateData(false);
};

void spcCObjectModifyPage::GetProperties(zSTRING& propString)
{
	propString.Clear();
	for (int z=0; z<propList.GetNumInList(); z++)
	{
		propString += propList[z];
		propString += zSTRING("\n");
		// if (propList[z]==SEP_PROP_START) propString += zSTRING("\n");
	}
};

void spcCObjectModifyPage::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	if (bShow)	
	{		
		((spcCObjectSheet*)GetParent())->SetActionButtonText(BUTTON_TEXT_MODIFY_APPLY);
	};	
}

void spcCObjectModifyPage::StartEditBoundingBox()
{
	if (!dynamic_cast<spcCObjectSheet*>(GetParent())) return;
	dynamic_cast<spcCObjectSheet*>(GetParent())->StartEditBoundingBox();	
}

void spcCObjectModifyPage::StopEditBoundingBox()
{
	if (!dynamic_cast<spcCObjectSheet*>(GetParent())) return;
	dynamic_cast<spcCObjectSheet*>(GetParent())->StopEditBoundingBox();	
}

void spcCObjectModifyPage::Enable(bool enabled)
{	
	EnableWindow(enabled);
	
	ctrl_editbox.EnableWindow(enabled);
	ctrl_string_fileopen.EnableWindow(enabled);
	ctrl_colorview.EnableWindow(enabled);
	ctrl_editcolor.EnableWindow(enabled);
	ctrl_raw.EnableWindow(enabled);
	ctrl_vec3.EnableWindow(enabled);
	ctrl_vec2.EnableWindow(enabled);
	ctrl_vec1.EnableWindow(enabled);
	ctrl_value.EnableWindow(enabled);
	ctrl_string.EnableWindow(enabled);
	ctrl_enum.EnableWindow(enabled);
	ctrl_bool.EnableWindow(enabled);
	ctrl_proptree.EnableWindow(enabled);

	isEnabled = enabled;
}


bool spcCObjectModifyPage::CheckStringValue(CString &s)
{
	bool result = true;
	int index;
	do
	{
		index = s.Find('[',0);
		if (index<0) index = s.Find(']',0);

		if (index>=0) 
		{
			result = false;
			s.SetAt(index,'_');
		}

	} while (index>=0);	
	
	return result;
}

void spcCObjectModifyPage::ClearContents()
{
	propList.DeleteList();
	ctrl_proptree.DeleteAllItems();	
}

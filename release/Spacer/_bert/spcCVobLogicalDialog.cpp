// spcCVobLogicalDialog.cpp : implementation file
//

#include "stdafx.h"
#include "zengine.h"

#include "Spacer.h"
#include "SpacerView.h"
#include "SpacerDoc.h"
#include "spcCVobLogicalDialog.h"
#include "spcCVobContainer.h"
#include "spcCObjPropList.h"
#include "spcCInfoBar.h"
#include "mainfrm.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// z-includes
#include "zBuffer.h"
#include "zArchiver.h"
#include "zVob.h"
#include "zWorld.h"
#include "zdisk.h"

const zSTRING	LIST_SEP		= "----------";
const zSTRING	LIST_ABSTRACT	= "[abstract class]";
const zSTRING	LIST_CORRUPT	= "[corrupt class]";
const zSTRING	LIST_SCRIPTED	= "(scripted)";

const char		LIST_PREFIX		= '.';
const char		LIST_POSTFIX	= ' ';

// Radiobuttons
const int LOG_TYPE_CONVERT = 0;
const int LOG_TYPE_COLLECT = 1;
const int LOG_TYPE_CORRECT = 2;
const int LOG_TYPE_REPLACE = 3;

/////////////////////////////////////////////////////////////////////////////
// spcCVobLogicalDialog dialog


spcCVobLogicalDialog::spcCVobLogicalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(spcCVobLogicalDialog::IDD, pParent), propList(),propListNew(), selected(-1), startPos(0),
	  selectedProp(NULL), cur_vob(0), new_vob(0), 
	  m_color(), b_color(false), lastClass()
{
	//{{AFX_DATA_INIT(spcCVobLogicalDialog)
	m_bool = FALSE;
	m_enum = _T("");
	m_string = _T("");
	m_value = _T("");
	m_vec1 = _T("");
	m_vec2 = _T("");
	m_vec3 = _T("");
	m_mode_new = FALSE;	
	m_classname_nc = _T("");
	m_effect_derived = FALSE;
	m_progress_found = _T("");			
	//}}AFX_DATA_INIT	
}


void spcCVobLogicalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCVobLogicalDialog)
	DDX_Control(pDX, IDC_ACTION_TYPE, ctrl_action_type);
	DDX_Control(pDX, IDC_LOGICNEW_OLD, ctrl_new_old);
	DDX_Control(pDX, IDC_PROGRESSBAR, ctrl_progress);
	DDX_Control(pDX, IDC_CLASSSELECTOR_NC, ctrl_classselector_nc);
	DDX_Control(pDX, IDC_CLASSSELECTOR, ctrl_classselector);
	DDX_Control(pDX, IDC_EDITCOLOR, ctrl_editcolor);
	DDX_Control(pDX, IDC_DYN_APPLY, ctrl_applybutton);
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
	DDX_Text(pDX, IDC_DYSTRING, m_string);
	DDX_Text(pDX, IDC_DYVALUE, m_value);
	DDX_Text(pDX, IDC_DYVECTOR1, m_vec1);
	DDX_Text(pDX, IDC_DYVECTOR2, m_vec2);
	DDX_Text(pDX, IDC_DYVECTOR3, m_vec3);
	DDX_Check(pDX, IDC_LOGICNEW_OLD, m_mode_new);
	DDX_CBString(pDX, IDC_CLASSSELECTOR_NC, m_classname_nc);
	DDX_Check(pDX, IDC_EFFECT_DERIVED, m_effect_derived);
	DDX_Text(pDX, IDC_PROGRESS_FOUND, m_progress_found);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCVobLogicalDialog, CDialog)
	//{{AFX_MSG_MAP(spcCVobLogicalDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_PROPTREE, OnSelchangedProptree)
	ON_NOTIFY(NM_DBLCLK, IDC_PROPTREE, OnDblclkProptree)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_DYBOOL, OnValChange)
	ON_BN_CLICKED(IDC_DYN_APPLY, OnDynApply)
	ON_BN_CLICKED(IDC_EDITCOLOR, OnEditcolor)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_CLASSSELECTOR, OnSelchangeClassselector)
	ON_BN_CLICKED(IDC_LOGICNEW_OLD, OnLogicnewOld)
	ON_EN_CHANGE(IDC_DYVALUE, OnChangeDyvalue)
	ON_EN_CHANGE(IDC_DYSTRING, OnChangeDystring)
	ON_EN_CHANGE(IDC_DYVECTOR1, OnChangeDyvector1)
	ON_EN_CHANGE(IDC_DYVECTOR2, OnChangeDyvector2)
	ON_EN_CHANGE(IDC_DYVECTOR3, OnChangeDyvector3)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_NOTIFY(NM_CLICK, IDC_PROPTREE, OnClickProptree)
	ON_CBN_SELCHANGE(IDC_DYENUM, OnValChange)
	ON_CBN_SELCHANGE(IDC_ACTION_TYPE, OnSelchangeActionType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Own Functions

/////////////////////////////////////////////
// VobLib

void spcCVobLogicalDialog::buildClassHierarchy (zCClassDef *parentClassDef, int depth, bool useNCCtrl)
{
	depth++;
	zSTRING baseName;
	zSTRING s;
	
	// Abgeleitete Klassen von parentClassDef ermitteln
	for (int i=0; i<zCClassDef::GetNum(); i++) 
	{
		zCClassDef* classDef = zCClassDef::GetClassDefByIndex(i);
		
		if (classDef->GetBaseClassDef()==parentClassDef) {

			zBOOL baseOK;
			if (classDef->GetBaseClassDef()) 
			{
				baseName= classDef->GetBaseClassDef()->GetClassName_();
				baseOK	= (baseName == classDef->GetBaseClassName());
			} else {
				baseOK	= (classDef->GetBaseClassName()=="NULL");
			};

			s = classDef->GetClassName_();
			if (!baseOK) s = s + LIST_POSTFIX + LIST_CORRUPT;

			// Eigenschaften
			if (classDef->IsAbstractClass()) s = s + LIST_POSTFIX + LIST_ABSTRACT;
			if (classDef->IsScriptedClass()) s = s + LIST_POSTFIX + LIST_SCRIPTED;			
			// Einruecken
			s = Characters(LIST_PREFIX,depth*2-2) + s;
			// Den Klassenbezeichner der entsprechenden Listebox hinzufuegen
			if (useNCCtrl) 
			{
				ctrl_classselector_nc.AddString(s.ToChar());
			}
			else 
			{				
				ctrl_classselector.AddString(s.ToChar());				
			}
			buildClassHierarchy (classDef,depth,useNCCtrl);
		};
	};
	
};

void spcCVobLogicalDialog::buildClassHierarchy ()
{
	int c =0;
	bool found = false;
	zCClassDef* vobClass = 0; 
	while ( c<zCClassDef::GetNum() && !found)
	{
			vobClass = zCClassDef::GetClassDefByIndex(c);
			found = (vobClass->GetClassName_()==zSTRING("zCVob")!=0);
			if ( !found ) c++;
	}
	if (found )
	{
		ctrl_classselector.ResetContent();
		zSTRING s = vobClass->GetClassName_();
		ctrl_classselector.AddString(s.ToChar());
		buildClassHierarchy(vobClass);
	}

//	UpdateData(false);
//	ctrl_classselector.SetCurSel(0);
	UpdateData(false);  //m_enum setzen
}

void spcCVobLogicalDialog::createPropTree()
{
	ctrl_proptree.DeleteAllItems();
	if (!cur_vob) return;
	int z=startPos;
	createPropTree(z,TVI_ROOT);
/*	if (cur_vob->GetClassName_()==lastClass)
	{
		ctrl_proptree.SelectItem(selectedProp);
	} else*/ {
		lastClass = cur_vob->GetClassName_();
		HTREEITEM ITEM = ctrl_proptree.GetFirstVisibleItem();
		if (ITEM != 0)
			ctrl_proptree.Expand(ITEM,TVE_EXPAND);
	}
}

void spcCVobLogicalDialog::createPropTree(int& n, HTREEITEM parent)
{
	// never call with n>=NumInList
	if (n>=propList.GetNumInList()) return ;
	CString entry;
	if (propList[n]->GetPropType()!=spcCObjPropertyElement::PETclass &&
		propList[n]->GetPropType()!=spcCObjPropertyElement::PETgroup )
	{
		if (propList[n]->IsChecked()) entry = "* ";
		else entry = "  ";
		entry = entry + propList[n]->GetName()+" : ";
		if (propList[n]->GetPropType()==spcCObjPropertyElement::PETenum)
			entry = entry+propList[n]->GetEnumVal();
		else if (propList[n]->GetPropType()==spcCObjPropertyElement::PETbool &&
				 propList[n]->GetIntVal()==0)
			entry = entry+CString("FALSE");
		else if (propList[n]->GetPropType()==spcCObjPropertyElement::PETbool &&
				 propList[n]->GetIntVal()==1)
			entry = entry+CString("TRUE");
		else
			entry = entry+propList[n]->GetStrVal();
		if (propListNew[n]->IsChecked())
		{
			entry = entry +" -> ";
			if (propListNew[n]->GetPropType()==spcCObjPropertyElement::PETenum)
				entry = entry+propListNew[n]->GetEnumVal();
			else if (propListNew[n]->GetPropType()==spcCObjPropertyElement::PETbool &&
					 propListNew[n]->GetIntVal()==0)
				entry = entry+CString("FALSE");
			else if (propListNew[n]->GetPropType()==spcCObjPropertyElement::PETbool &&
					 propListNew[n]->GetIntVal()==1)
				entry = entry+CString("TRUE");
			else
				entry = entry+propListNew[n]->GetStrVal();
		}
	} else entry = propList[n]->GetName()+" : ";

	HTREEITEM newITEM = ctrl_proptree.InsertItem(entry,parent);
	ctrl_proptree.SetItemData(newITEM,n);

	if (propList[n]->GetPropType()==spcCObjPropertyElement::PETclass ||
		propList[n]->GetPropType()==spcCObjPropertyElement::PETgroup )
	{
		n++;
		while(	n<propList.GetNumInList() && 
				propList[n]->GetPropType()!=spcCObjPropertyElement::PETchunkend)
		{
			createPropTree(n,newITEM);
			n++;
		}
	}
}

void spcCVobLogicalDialog::updatePropTree(HTREEITEM item)
{
	int n = ctrl_proptree.GetItemData(item);

	CString entry;
	if (propList[n]->GetPropType()!=spcCObjPropertyElement::PETclass &&
		propList[n]->GetPropType()!=spcCObjPropertyElement::PETgroup )
	{
		if (propList[n]->IsChecked()) entry = "* ";
		else entry = "  ";
		entry = entry + propList[n]->GetName()+" : ";
		if (propList[n]->GetPropType()==spcCObjPropertyElement::PETenum)
			entry = entry+propList[n]->GetEnumVal();
		else if (propList[n]->GetPropType()==spcCObjPropertyElement::PETbool &&
				 propList[n]->GetIntVal()==0)
			entry = entry+CString("FALSE");
		else if (propList[n]->GetPropType()==spcCObjPropertyElement::PETbool &&
				 propList[n]->GetIntVal()==1)
			entry = entry+CString("TRUE");
		else
			entry = entry+propList[n]->GetStrVal();
		if (propListNew[n]->IsChecked())
		{
			entry = entry +" -> ";
			if (propListNew[n]->GetPropType()==spcCObjPropertyElement::PETenum)
				entry = entry+propListNew[n]->GetEnumVal();
			else if (propListNew[n]->GetPropType()==spcCObjPropertyElement::PETbool &&
					 propListNew[n]->GetIntVal()==0)
				entry = entry+CString("FALSE");
			else if (propListNew[n]->GetPropType()==spcCObjPropertyElement::PETbool &&
					 propListNew[n]->GetIntVal()==1)
				entry = entry+CString("TRUE");
			else
				entry = entry+propListNew[n]->GetStrVal();
		}
	} else entry = propList[n]->GetName()+" : ";
	ctrl_proptree.SetItemText(item,entry.GetBuffer(0));
}

void spcCVobLogicalDialog::deactivateAll()
{
	UpdateData(true);
	m_bool = false;
	ctrl_bool.EnableWindow(false);
	m_value = "";
	ctrl_value.EnableWindow(false);
	m_enum = "";
	ctrl_enum.EnableWindow(false);
	m_string = "";
	ctrl_string.EnableWindow(false);
	m_vec1 = "";m_vec2 = "";m_vec3 = "";
	ctrl_vec1.EnableWindow(false);
	ctrl_vec2.EnableWindow(false);
	ctrl_vec3.EnableWindow(false);
	ctrl_editcolor.EnableWindow(false);
	b_color=false;
	UpdateData(false);
}
void spcCVobLogicalDialog::activateBool(bool v)
{
	UpdateData(true);
	ctrl_bool.EnableWindow(true);
	m_bool = v;
	UpdateData(false);
}
void spcCVobLogicalDialog::activateValue(float v)
{
	UpdateData(true);
	ctrl_value.EnableWindow(true);
	ctrl_value.SetActiveWindow();
	ctrl_value.SetFocus();
	m_value = CString(zSTRING(v).ToChar());
	UpdateData(false);
}
void spcCVobLogicalDialog::activateEnum(int v)
{
	UpdateData(true);
	ctrl_enum.EnableWindow(true);
	ctrl_enum.SetCurSel(v);
	//UpdateData(false);
	UpdateData(false);  //m_enum setzen
}
void spcCVobLogicalDialog::activateString(CString v)
{
	UpdateData(true);
	ctrl_string.EnableWindow(true);
	ctrl_string.SetActiveWindow();
	ctrl_string.SetFocus();
	m_string = v;
	UpdateData(false);
}
void spcCVobLogicalDialog::activateRaw(CString v)
{
	UpdateData(true);
/*	ctrl_raw.EnableWindow(true);
	m_raw = v+CString("\r\n");
	UpdateData(false);*/
	ctrl_string.EnableWindow(true);
	ctrl_string.SetActiveWindow();
	ctrl_string.SetFocus();
	m_string = v;
	UpdateData(false);
}
void spcCVobLogicalDialog::activateVector(zVEC3 v)
{
	UpdateData(true);
	ctrl_vec1.EnableWindow(true);
	ctrl_vec2.EnableWindow(true);
	ctrl_vec3.EnableWindow(true);
	ctrl_vec1.SetActiveWindow();
	ctrl_vec1.SetFocus();
	m_vec1 = CString(zSTRING(v[0]).ToChar());
	m_vec2 = CString(zSTRING(v[1]).ToChar());
	m_vec3 = CString(zSTRING(v[2]).ToChar());
	UpdateData(false);
}
void spcCVobLogicalDialog::activateColor(COLORREF col)
{
	UpdateData(true);
	// farbe anzeigen
	m_color = col;
	b_color= true;
	ctrl_editcolor.EnableWindow(true);
	UpdateData(false);
}

zCVob* spcCVobLogicalDialog::InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* vob)
{
	UpdateData(true);
	return 0;
	HTREEITEM sel = ctrl_proptree.GetSelectedItem();
	if (sel==NULL) return 0;

	CString name = ctrl_proptree.GetItemText(sel);

	new_vob = (zCVob*)zCObject::CreateNewInstance(zSTRING(name.GetBuffer(0)));	

	CSpacerDoc::doc->GetWorld()->AddVobAsChild(new_vob,vob);
	
	new_vob->SetPositionWorld(pos.n[VX]+dir.n[VX]*200,pos.n[VY]+dir.n[VY]*200,pos.n[VZ]+dir.n[VZ]*200);			

	UpdateData(false);
	return new_vob;
}

void spcCVobLogicalDialog::SelectVob(zCVob * pickedVob)
{	
	spcCObjPropertyElement* ele;

	UpdateData(true);
	if (!pickedVob || dynamic_cast<zCVobLevelCompo*>(pickedVob))
	{
		// dialog leer
		cur_vob = NULL;
		createPropTree();
		ctrl_applybutton.EnableWindow(false);
		UpdateData(false);
	}
	else
	{
		// daten setzen
		cur_vob = pickedVob;
		zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);
		arch->SetStringEOL(zSTRING("\n"));		
		arch->WriteObject(cur_vob);
		zSTRING archBuffer;
		arch->GetBufferString(archBuffer);
		
		// buffer auseinander nehmen
		propList.DeleteList();
		propListNew.DeleteList();
		int z=1;
		zSTRING w = archBuffer.PickWord(z,"\n\t","\n\t");
		while (w.Search("[")==-1)
		{
			ele = new spcCObjPropertyElement(w.ToChar());
			propList.Insert(ele);
			
			ele = new spcCObjPropertyElement(w.ToChar());
			propListNew.Insert(ele);
			
			startPos = propList.GetNumInList();
			z++;
			w = archBuffer.PickWord(z,"\n\t","\n\t");
		}
		
		ele = new spcCObjPropertyElement(w.ToChar());
		propList.Insert(ele);
			
		ele = new spcCObjPropertyElement(w.ToChar());
		propListNew.Insert(ele);

		while (!w.IsEmpty())
		{
			z++;
			w = archBuffer.PickWord(z,"\n\t","\n\t");

			ele = new spcCObjPropertyElement(w.ToChar());
			propList.Insert(ele);
			
			ele = new spcCObjPropertyElement(w.ToChar());
			propListNew.Insert(ele);

		}
		arch->Close();
		zRELEASE(arch);

		createPropTree();
		ctrl_applybutton.EnableWindow(true);
		
	}
	UpdateData(false);
}


/////////////////////////////////////////////////////////////////////////////
// spcCVobLogicalDialog message handlers

void spcCVobLogicalDialog::OnSelchangedProptree(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	//if (insertMode) return;

	spcCObjPropertyElement::TPropEditType type;

	selectedProp = ctrl_proptree.GetSelectedItem();
	selected = ctrl_proptree.GetItemData(selectedProp);
	
	deactivateAll();
	if (propList.GetNumInList()<=selected) return;

	type = propList[selected]->GetPropType();
	switch (type)
	{
	case spcCObjPropertyElement::PETint: 
		activateValue(float(propList[selected]->GetIntVal())); break;
	case spcCObjPropertyElement::PETbool:
		activateBool(bool(propList[selected]->GetIntVal()>0)); break;
	case spcCObjPropertyElement::PETfloat	: 
		activateValue(propList[selected]->GetFloatVal()); break;
	case spcCObjPropertyElement::PETstring	: 
		activateString(propList[selected]->GetStrVal()); break;
	case spcCObjPropertyElement::PETenum	: 
		propList[selected]->GetEnumList(ctrl_enum);
		activateEnum(propList[selected]->GetIntVal()); 
		break;
	case spcCObjPropertyElement::PETraw	: 
		activateRaw(propList[selected]->GetStrVal()); break;
	case spcCObjPropertyElement::PETvec3	: 
		activateVector(propList[selected]->GetVecVal()); break;
	case spcCObjPropertyElement::PETcolor	:
		activateColor(propList[selected]->GetColor()); break;
	}

	*pResult = 0;
}


void spcCVobLogicalDialog::OnClickProptree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(true);
/*
	if (selected>0 &&	propList[selected]->GetPropType()!=spcCObjPropertyElement::PETclass &&
						propList[selected]->GetPropType()!=spcCObjPropertyElement::PETgroup)
	{

		selectedProp	= ctrl_proptree.GetSelectedItem();
		selected		= ctrl_proptree.GetItemState(selectedProp);

		if (m_mode_new)
		{
			propListNew[selected].SetChecked(false);
		}
		else
		{
			propList[selected].SetChecked(false);
		};

		updatePropTree(selectedProp);
	}
*/
	UpdateData(false);
	*pResult = 0;
}

void spcCVobLogicalDialog::OnDblclkProptree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(true);
	//if (insertMode) return;

//	spcCObjPropertyElement::TPropEditType type;

	if (selected>0 &&	propList[selected]->GetPropType()!=spcCObjPropertyElement::PETclass &&
						propList[selected]->GetPropType()!=spcCObjPropertyElement::PETgroup)
	{
		if (m_mode_new) 
			propListNew[selected]->SetChecked(!propListNew[selected]->IsChecked());
		else 
			propList[selected]->SetChecked(!propList[selected]->IsChecked());

		updatePropTree(selectedProp);	
	}
	//ctrl_proptree.SetCurSel(ctrl_proptree.GetCurSel());
	OnSelchangedProptree(pNMHDR, pResult);

	UpdateData(false);
	*pResult = 0;	
}

void spcCVobLogicalDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	// CDialog::OnClose();
}

void spcCVobLogicalDialog::OnOK()
{
	OnValChange();
	ctrl_proptree.SetActiveWindow();
	ctrl_proptree.SetFocus();
}

void spcCVobLogicalDialog::OnValChange() 
{
	UpdateData(true);

	spcCObjPropertyElement::TPropEditType type;
	int seli = 0;

	if (selected<=0) return;

	if (m_mode_new) 
	{
		if (propListNew[selected]->GetPropType()!=spcCObjPropertyElement::PETclass &&
			propListNew[selected]->GetPropType()!=spcCObjPropertyElement::PETgroup)
		{
			UpdateData(TRUE);
			type = propListNew[selected]->GetPropType();
			switch (type)
			{
			case spcCObjPropertyElement::PETint	: 
				propListNew[selected]->SetByStr(m_value);
				break;
			case spcCObjPropertyElement::PETbool	:
				if (m_bool) 
					propListNew[selected]->SetByInt(1);
				else 
					propListNew[selected]->SetByInt(0);
				break;
			case spcCObjPropertyElement::PETfloat	:
				propListNew[selected]->SetByStr(m_value);
				break;
			case spcCObjPropertyElement::PETstring:
				propListNew[selected]->SetByStr(m_string);
				break;
			case spcCObjPropertyElement::PETenum	:
				seli = ctrl_enum.GetCurSel();
				propListNew[selected]->SetByInt(seli);
				break;
			case spcCObjPropertyElement::PETraw	:
				propListNew[selected]->SetByStr(m_string);
				break;
			case spcCObjPropertyElement::PETvec3	:
				propListNew[selected]->SetByVec( zVEC3(
					zSTRING(m_vec1.GetBuffer(0)).ToFloat(),
					zSTRING(m_vec2.GetBuffer(0)).ToFloat(),
					zSTRING(m_vec3.GetBuffer(0)).ToFloat() )
					);
				break;
			case spcCObjPropertyElement::PETcolor	:
				propListNew[selected]->SetByColor(m_color);
				break;
			}
		}
	}
	else
	{
		if (propList[selected]->GetPropType()!=spcCObjPropertyElement::PETclass &&
			propList[selected]->GetPropType()!=spcCObjPropertyElement::PETgroup)
		{
			UpdateData(TRUE);
			type = propList[selected]->GetPropType();
			switch (type)
			{
			case spcCObjPropertyElement::PETint	: 
				propList[selected]->SetByStr(m_value);
				break;
			case spcCObjPropertyElement::PETbool	:
				if (m_bool) 
					propList[selected]->SetByInt(1);
				else 
					propList[selected]->SetByInt(0);
				break;
			case spcCObjPropertyElement::PETfloat	:
				propList[selected]->SetByStr(m_value);
				break;
			case spcCObjPropertyElement::PETstring:
				propList[selected]->SetByStr(m_string);
				break;
			case spcCObjPropertyElement::PETenum	:
				seli = ctrl_enum.GetCurSel();
				propList[selected]->SetByInt(seli);
				break;
			case spcCObjPropertyElement::PETraw	:
				propList[selected]->SetByStr(m_string);
				break;
			case spcCObjPropertyElement::PETvec3	:
				propList[selected]->SetByVec( zVEC3(
					zSTRING(m_vec1.GetBuffer(0)).ToFloat(),
					zSTRING(m_vec2.GetBuffer(0)).ToFloat(),
					zSTRING(m_vec3.GetBuffer(0)).ToFloat() )
					);
				break;
			case spcCObjPropertyElement::PETcolor	:
				propList[selected]->SetByColor(m_color);
				break;
			}
		}
	}
	updatePropTree(selectedProp);
	UpdateData(false);
		
}

void spcCVobLogicalDialog::OnDynApply() 
{
	UpdateData(true);	

	if (ctrl_action_type.GetCurSel()==LOG_TYPE_COLLECT)
	{
		CMainFrame::mainframe->GetVobContainer()->SetMode(spcCVobContainer::VC_CUSTOM);
		// CMainFrame::mainframe->GetVobContainer()->ClearVoblist();
	};

	CSpacerDoc* pDoc = CSpacerView::view->GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc->GetWorld()) return;		
	
	zSTRING cn;

	// Such-Klasse
	int sel = ctrl_classselector.GetCurSel();
	CString selText;
	if (sel>=0) 
	{	
		ctrl_classselector.GetLBText(sel,selText);	
	}
	else
	{
		MessageBox("Please select a class first");
		return;
	};

	zSTRING classname = (selText.GetBuffer(0));
	cn = classname;
	classname = PickClassname(classname);

	if ( 
		(cn.Search(LIST_SEP)>=0) || 
		(cn.Search(LIST_ABSTRACT)>=0) ||
		(cn.Search(LIST_CORRUPT)>=0)		
		)
	{
		AfxMessageBox("\""+CString(classname.ToChar())+"\" is not a correct classname: \r\n\r\n"+CString(cn.ToChar()));
		return;
	};

	// Neue Klasse
	zSTRING new_classname = (m_classname_nc.GetBuffer(0));	
	cn = new_classname;
	new_classname = PickClassname(new_classname);

	if ( 
		(cn.Search(LIST_SEP)>=0) || 
		(cn.Search(LIST_ABSTRACT)>=0) ||
		(cn.Search(LIST_CORRUPT)>=0)
		)
	{
		AfxMessageBox("\""+CString(new_classname.ToChar())+"\" is not a correct classname: \r\n\r\n"+CString(cn.ToChar()));
		return;
	};	

	pDoc->SetDirty();

	int count =0;
	zCArray<zCVob*> result;
	pDoc->GetWorld()->SearchVobListByClass(cur_vob->GetClassDef(),result);	
	if (m_effect_derived) 
	{
		pDoc->GetWorld()->SearchVobListByBaseClass(cur_vob->GetClassDef(),result);
	}	
	CMainFrame::mainframe->GetInfoBar()->SetSelectedObject(0);

	::SetCursor(spcConfig.MouseWait);

	ctrl_progress.SetRange32(0,result.GetNumInList());
	ctrl_progress.SetPos(0);
	ctrl_progress.ShowWindow(SW_SHOW);
	
	zERR_MESSAGE(3,zERR_BEGIN,"B: Replacing vobs");

	int num = result.GetNumInList();
	for (int i=0; i<num; i++)
	{
		if (dynamic_cast<zCVobLevelCompo*>(result[i]))	continue;
		if (result[i] == CSpacerDoc::doc->camera_vob)	continue;

		zERR_MESSAGE(8,zERR_BEGIN,"B: Handling vob "+zVOB_DESCRIPTION(result[i]));

		if (ctrl_action_type.GetCurSel()!=LOG_TYPE_CONVERT)
		{
			if (HandleVob(result[i]))		count++; 
		}
		else if (new_classname.IsEmpty() || new_classname == result[i]->GetClassName_())
		{ 				
			if (HandleVob(result[i]))		count++; 
		}
		else 
		{
			if (HandleVobExt(result[i]))	count++;		
		}
		zERR_MESSAGE(8,zERR_END,"");
		m_progress_found.Format("%i/%i (%i found and processed)",i+1, num, count);
		ctrl_progress.SetPos(i);
		UpdateData(false);
		//RedrawWindow();
		UpdateWindow();
	}	

	zERR_MESSAGE(3,0,"Updating voblist ...");	

	CMainFrame::mainframe->UpdateVobList(pDoc->GetWorld());
	ctrl_progress.ShowWindow(SW_HIDE);

	::SetCursor(spcConfig.MouseArrow);

	CSpacerView::view->SetActiveWindow();
	CSpacerView::view->SetFocus();

	zERR_MESSAGE(3,zERR_END,"Finished");

	UpdateData(false);
}
bool spcCVobLogicalDialog::HandleVob(zCVob*& vob)
{
	if (!vob) return false;

	zERR_MESSAGE(8,zERR_BEGIN,"B: SPC: Checking vob "+vob->GetVobName());

	spcCObjPropertyElement* ele;

	// ** O[i] entpacken und matchen

	spcCObjPropertyList mpropList;
	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);
	arch->SetStringEOL(zSTRING("\n"));	
	arch->WriteObject(vob);
	zSTRING archBuffer;
	arch->GetBufferString(archBuffer);
	
	// buffer auseinander nehmen
	mpropList.DeleteList();
	int z=1;
	zSTRING w = archBuffer.PickWord(z,"\n\t","\n\t");
	while (w.Search("[")==-1)
	{
		ele = new spcCObjPropertyElement(w.ToChar());
		mpropList.Insert(ele);
		startPos = mpropList.GetNumInList();
		z++;
		w = archBuffer.PickWord(z,"\n\t","\n\t");
	}
	ele = new spcCObjPropertyElement(w.ToChar());
	mpropList.Insert(ele);
	while (!w.IsEmpty())
	{
		z++;
		w = archBuffer.PickWord(z,"\n\t","\n\t");

		ele = new spcCObjPropertyElement(w.ToChar());
		mpropList.Insert(ele);
	}
	arch->Close();
	zRELEASE(arch);

	// Testen, ob der Vob durch den Filter passt
	zBOOL match = TRUE;
	int i = 0;
	while (match && i<propList.GetNumInList())
	{
		if (propList[i]->IsChecked())
		{			
			match = FALSE;
			int pc =0;
			while (!match && pc<mpropList.GetNumInList())
			{
				if (mpropList[pc]->GetName()==propList[i]->GetName())
				{
					match = (zSTRING(*mpropList[pc]) == zSTRING(*propList[i]));
					if (match) zERR_MESSAGE(8,0,"B: SPC: match: "+zSTRING(*mpropList[pc])+" == "+zSTRING(*propList[i]));
					else zERR_MESSAGE(8,0,"B: SPC: dismatch: "+zSTRING(*mpropList[pc])+" != "+zSTRING(*propList[i]));
				}
				if (!match) pc++;
			}			
		}
		i++;
	}
	

	if (match)
	{		
		switch (ctrl_action_type.GetCurSel())
		{
		case LOG_TYPE_REPLACE:
			{
				zMATRIX4 trafo = vob->trafoObjToWorld;

				zCVob* parentVob = 0;
				if (vob->globalVobTreeNode && vob->globalVobTreeNode->GetParent())
				{
					parentVob = vob->globalVobTreeNode->GetParent()->GetData();
				}				
					
				zCVob* newvob = CSpacerDoc::doc->GetWorld()->MergeVobSubtree(zSTRING(m_replace_zen_file.GetBuffer(0)), parentVob);
				if (newvob)
				{				
					zBOOL lcddyn = newvob->GetCollDetDyn();
					zBOOL lcdstat = newvob->GetCollDetStat();
					newvob->SetCollDet(FALSE);
					newvob->SetTrafoObjToWorld(trafo);
					newvob->SetCollDetDyn(lcddyn);
					newvob->SetCollDetStat(lcdstat);
							
					CMainFrame::mainframe->HandleVobInsert(newvob,parentVob);			

					zERR_MESSAGE(8,0,"B: SPC: Replaced ZEN");
				}
				else
				{
					zERR_WARNING("B: SPC: ReplaceWithZen: Could not merge ZEN-File");
				};

				if (newvob) // vob loeschen, wenn ersetzt
				{
					vob->RemoveVobFromWorld();		
					vob = 0;
				}

				zERR_MESSAGE(8,zERR_END,"");
				return true; 
			}
			break;
		case LOG_TYPE_CORRECT:
			{
				zBOOL coldet_dyn = vob->GetCollDetDyn();
				zBOOL coldet_stat = vob->GetCollDetStat();
				vob->SetCollDetDyn(FALSE);
				vob->SetCollDetStat(FALSE);
				zMAT4 matrix = vob->GetTrafoLocal();
				matrix.MakeOrthonormal();	// beseitigt Ungenauigkeiten
				vob->SetTrafo (matrix);	// updatet intern auch trafoObjToWorld
				vob->SetCollDetDyn(coldet_dyn);
				vob->SetCollDetStat(coldet_stat);

				return true;
			}
			break;
		case LOG_TYPE_COLLECT:
			{
				CMainFrame::mainframe->GetVobContainer()->AddVob(vob);

				zERR_MESSAGE(8,zERR_END,"");
				return true;
			};
			break;
		case LOG_TYPE_CONVERT:
			{
				bool changed = false;
				for (i=0; i<propListNew.GetNumInList(); i++)
					if (propListNew[i]->IsChecked())
					{
						bool found = false;
						int pc =0;
						while (!found && pc<mpropList.GetNumInList())
						{
							found = mpropList[pc]->GetName()==propListNew[i]->GetName();
							if (!found) pc++;
						}
						if (found)
						{
							(*mpropList[pc])=(*propListNew[i]);
							changed = true;
						}
					}

				// Geaenderte Daten auf den Vob anwenden
				if (changed) 
				{			
					zSTRING zstrBuf;
					for (int zz=0; zz<mpropList.GetNumInList(); zz++)
					{
						zstrBuf += zSTRING(*mpropList[zz]) + "\n";
						if ( zSTRING(*mpropList[zz])==zSTRING("END")) zstrBuf += "\n";
					}
					zCBuffer zbuf(zstrBuf.ToChar(),zstrBuf.Length());

					zCArchiver* arch = zarcFactory.CreateArchiverRead(&zbuf);
					arch->SetStringEOL(zSTRING("\n"));
					arch->ReadObject(vob);
					arch->Close();
					zRELEASE(arch);
				}

				zERR_MESSAGE(8,zERR_END,"");
				return true;
			};			
			break;
		};		
	}	
	
	zERR_MESSAGE(8,zERR_END,"");
	return false;
}
bool spcCVobLogicalDialog::HandleVobExt(zCVob*& vob)
{
	if (!vob) return false;

	zERR_MESSAGE(8,zERR_BEGIN,"B: SPC: CheckingExt vob "+vob->GetVobName());

	spcCObjPropertyElement* ele;
	
	// ** O[i] entpacken und matchen
	spcCObjPropertyList mpropList;
	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);
	arch->SetStringEOL(zSTRING("\n"));
	arch->WriteObject(vob);
	
	zSTRING archBuffer;
	arch->GetBufferString(archBuffer);

	// buffer auseinander nehmen

	mpropList.DeleteList();
	int z=1;
	zSTRING w = archBuffer.PickWord(z,"\n\t","\n\t");
	
	while (w.Search("[")==-1)
	{
		ele = new spcCObjPropertyElement(w.ToChar());
		mpropList.Insert(ele);
		startPos = mpropList.GetNumInList();
		z++;
		w = archBuffer.PickWord(z,"\n\t","\n\t");
	}
	
	ele = new spcCObjPropertyElement(w.ToChar());
	mpropList.Insert(ele);
	
	while (!w.IsEmpty())
	{
		z++;
		w = archBuffer.PickWord(z,"\n\t","\n\t");

		ele = new spcCObjPropertyElement(w.ToChar());
		mpropList.Insert(ele);
	}
	
	arch->Close();
	zRELEASE(arch);	

	zBOOL match = TRUE;
	int i = 0;
	while (match && i<propList.GetNumInList())
	{
		if (propList[i]->IsChecked())
		{			
			match=FALSE;
			int pc =0;
			while (!match && pc<mpropList.GetNumInList())
			{
				if (mpropList[pc]->GetName()==propList[i]->GetName())
				{
					match = (zSTRING(*mpropList[pc])==zSTRING(*propList[i]));
					if (match) zERR_MESSAGE(8,0,"B: SPC: match: "+zSTRING(*mpropList[pc])+" == "+zSTRING(*propList[i]));
					else zERR_MESSAGE(8,0,"B: SPC: dismatch: "+zSTRING(*mpropList[pc])+" != "+zSTRING(*propList[i]));
				}
				if (!match) pc++;
			}			
		}

		i++;
	}

	//** test match : operation

	if (match)
	{
		// * NEW T
		//int sel =  ctrl_classselector_nc.GetCurSel();
		//CString selText;
		//ctrl_classselector.GetLBText(sel,selText);
		zSTRING new_classname = (m_classname_nc.GetBuffer(0));
		new_classname = PickClassname(new_classname);
		if (new_classname.IsEmpty()) new_classname=vob->GetClassName_();
		zCVob* newvob = (zCVob*)zCObject::CreateNewInstance(new_classname);
		if (!newvob) 
		{
			zERR_MESSAGE(8,zERR_END,"");
			return false;
		}

		// * Unarchive T - nproplist
		spcCObjPropertyList npropList;

		arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);		
		arch->WriteObject(newvob);
		arch->GetBufferString(archBuffer);
	
		// buffer auseinander nehmen
		npropList.DeleteList();
		z=1;		
		do
		{			
			w = archBuffer.PickWord(z,"\n\t","\n\t");
			if (w.Search("[")==-1) 
			{
				ele = new spcCObjPropertyElement(w.ToChar());
				npropList.Insert(ele);
			}
			z++;

		} while (w.Search("[")==-1);

		ele = new spcCObjPropertyElement(w.ToChar());
		npropList.Insert(ele);

		while (!w.IsEmpty())
		{			
			w = archBuffer.PickWord(z,"\n\t","\n\t");

			ele = new spcCObjPropertyElement(w.ToChar());
			npropList.Insert(ele);
			z++;
		}
		arch->Close();
		zRELEASE(arch);

		//* tranfmatch O[i] -> T

		for (i=startPos; i<mpropList.GetNumInList(); i++)
		{
			if (
				mpropList[i]->GetPropType()!=spcCObjPropertyElement::PETclass &&
				mpropList[i]->GetPropType()!=spcCObjPropertyElement::PETgroup &&
				mpropList[i]->GetPropType()!=spcCObjPropertyElement::PETchunkend
				)
			{
				bool	found	= false;
				int		pc		= 0;
				while (!found && pc<npropList.GetNumInList())
				{
					found = (npropList[pc]->GetName()==mpropList[i]->GetName());
					if (!found) pc++;
				}
				if (found) npropList[pc]=mpropList[i];
			}
		}

		for (i=startPos; i<propListNew.GetNumInList(); i++)
		{
			if (propListNew[i]->IsChecked())
			{
				bool	found = false;
				int		pc =0;
				while (!found && pc<npropList.GetNumInList())
				{
					found = (npropList[pc]->GetName()==propListNew[i]->GetName());
					if (!found) pc++;
				}
				if (found) npropList[pc]=propListNew[i];
			}
		}

		// Vob-Buffer erstellen (Archive-String)		
		zSTRING zstrBuf;
		int numEndSymbols=0;
		for (int zz=0; zz<npropList.GetNumInList(); zz++)
		{			
			zstrBuf += zSTRING(*npropList[zz]) + "\n";
			if ( zSTRING(*npropList[zz])==zSTRING("END")) 
			{
				numEndSymbols++;
				if (numEndSymbols>1) zstrBuf += "\n";			
			}
		}

		// Den Vob durch den erstellten Buffer aktualisieren		
		zCBuffer zbuf(zstrBuf.ToChar(),zstrBuf.Length());
		zCArchiver* arch = zarcFactory.CreateArchiverRead(&zbuf);
		arch->SetStringEOL(zSTRING("\n"));		
		arch->ReadObject(newvob);
		arch->Close();
		zRELEASE(arch);

		// *** object tausch
		SwapObject(vob,newvob);  // object wird aus welt entfernt
		vob=0;

		// den neuen Vob freigeben (wurde in die Welt eingefuegt)
		zRELEASE(newvob);		
	}

	zERR_MESSAGE(8,zERR_END,"");	
	return bool(match==TRUE);
}
void spcCVobLogicalDialog::SwapObject(zCVob* vob,zCVob* newVob)
{
	zCTree<zCVob>*	oldNode		= vob->globalVobTreeNode;
	zCTree<zCVob>*	parentNode	= oldNode->GetParent();
	zCWorld*		wld			= vob->GetHomeWorld();
	if (!wld) return;

	wld->AddVobAsChild(newVob,parentNode);

	zCTree<zCVob>* iNode = oldNode->GetFirstChild();
	while (iNode)
	{
		wld->MoveVobSubtreeTo(iNode->GetData(),newVob);
		iNode = iNode->GetNextChild();
	}
	wld->RemoveVob(vob);
}

void spcCVobLogicalDialog::OnEditcolor() 
{
	CColorDialog dlg(m_color);
	if (dlg.DoModal()==IDOK)
	{
		m_color = dlg.GetColor();
		OnValChange();
	}
}

void spcCVobLogicalDialog::OnPaint() 
{
	CPaintDC dc(this);

	if (b_color) {
		CBrush brush;
		brush.CreateSolidBrush(m_color);
		CBrush* oldBrush = dc.SelectObject(&brush);
		dc.Rectangle(CRect(CPoint(300,20),CPoint(360,80)));
		dc.SelectObject(oldBrush);
	}
	// Kein Aufruf von CDialog::OnPaint() für Zeichnungsnachrichten
}

void spcCVobLogicalDialog::OnSelchangeClassselector() 
{
	UpdateData(true);

	int sel = ctrl_classselector.GetCurSel();
	if (sel<0) return;

	CString selText;
	ctrl_classselector.GetLBText(sel,selText); // leerer Text->Crash
	
	zSTRING classname = (selText.GetBuffer(0));
	classname = PickClassname(classname);
	
	zRELEASE(cur_vob);
	cur_vob = (zCVob*)zCObject::CreateNewInstance(classname);

	SelectVob(cur_vob);

	int c =0;
	zBOOL found = FALSE;
	zCClassDef* vobClass = 0; 
	while ( c<zCClassDef::GetNum() && !found)
	{
			vobClass = zCClassDef::GetClassDefByIndex(c);
			found = zBOOL(vobClass->GetClassName_()==classname);
			if ( !found ) c++;
	}

	if (found )
	{		
		ctrl_classselector_nc.ResetContent();		

		ctrl_classselector_nc.AddString(vobClass->GetClassName_().ToChar());	// Eigener Klassennamen		

		ctrl_classselector_nc.AddString((LIST_SEP + " up-classing " + LIST_SEP).ToChar());

		// Baseclasses
		
		// Erstmal zaehlen, wieviele Basisklassen es denn gibt:
		int count=0;
		zCClassDef* classDef = vobClass;		
		while (classDef && classDef!=zCVob::GetStaticClassDef())
		{
			classDef = classDef->GetBaseClassDef();					
			if (classDef) count++;		
		};

		// Und nu ausgeben (immer vorne anfuegen, damit die Reihenfolge stimmt)
		int ins_pos = ctrl_classselector_nc.GetCount();
		classDef = vobClass;
		zSTRING s;
		while (classDef && classDef!=zCVob::GetStaticClassDef())
		{
			classDef = classDef->GetBaseClassDef();					
			if (classDef) 
			{
				count--;
				s = Characters(LIST_PREFIX,count*2)+classDef->GetClassName_();
				if (classDef->IsAbstractClass()) s = s + LIST_ABSTRACT;
				ctrl_classselector_nc.InsertString(ins_pos,s.ToChar());
			}			
		};		

		ctrl_classselector_nc.AddString((LIST_SEP + " down-classing " + LIST_SEP).ToChar());
				
		buildClassHierarchy(vobClass,1,true);									// Abgeleitete Klassen
		
		ctrl_classselector_nc.InsertString(0,"");

		ctrl_classselector_nc.SelectString(0,vobClass->GetClassName_().ToChar());
	}	

	m_effect_derived = false;
	UpdateData(false);
}

void spcCVobLogicalDialog::OnLogicnewOld() 
{
	UpdateData(true);
	
	UpdateDialogItems();
	
	if (m_mode_new) ctrl_new_old.SetWindowText("new"); 
	else ctrl_new_old.SetWindowText("old"); 
	UpdateData(false);
}

void spcCVobLogicalDialog::OnReset() 
{
	spcCObjPropertyElement* item;
	if (m_mode_new)
	{
		for (int i=0;i<propListNew.GetNumInList();i++)
		{
			item = propListNew.GetSafe(i);
			if (item) item->SetChecked(false);
			if (item) item->SetByStr("");
		}
	}
	else
	{
		for (int i=0;i<propList.GetNumInList();i++)
		{
			item = propList.GetSafe(i);
			if (item) item->SetChecked(false);
			if (item) item->SetByStr("");
		}
	};
	createPropTree();
}


void spcCVobLogicalDialog::OnChangeDyvalue() 
{
	OnValChange();
}

void spcCVobLogicalDialog::OnChangeDystring() 
{
	OnValChange();
}

void spcCVobLogicalDialog::OnChangeDyvector1() 
{
	OnValChange();
}

void spcCVobLogicalDialog::OnChangeDyvector2() 
{
	OnValChange();
}

void spcCVobLogicalDialog::OnChangeDyvector3() 
{
	OnValChange();
}

BOOL spcCVobLogicalDialog::OnInitDialog() 
{	
	CDialog::OnInitDialog();

	buildClassHierarchy ();
	
	ctrl_classselector.SelectString(-1,"");
	ctrl_classselector_nc.InsertString(-1,"");
	
	int c =0;
	zBOOL found = FALSE;
	zCClassDef* vobClass = 0; 
	while ( c<zCClassDef::GetNum() && !found)
	{
		vobClass = zCClassDef::GetClassDefByIndex(c);
		found = (vobClass->GetClassName_()==zSTRING("zCVob")!=0);
		if ( !found ) c++;
	}
	if (found) 
	{
		ctrl_classselector_nc.AddString("zCVob");
		buildClassHierarchy(vobClass,1,true);
	}
	ctrl_classselector_nc.SelectString(-1,"");
	ctrl_classselector_nc.EnableWindow(!m_delete_vobs && m_mode_new);	

	cur_vob = (zCVob*)zCObject::CreateNewInstance(zSTRING("zCVob"));
	SelectVob(cur_vob);

	if (m_mode_new) 
		ctrl_new_old.SetWindowText("new"); 
	else 
		ctrl_new_old.SetWindowText("old"); 

	ctrl_action_type.SetCurSel(LOG_TYPE_CONVERT);
	// UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

zSTRING spcCVobLogicalDialog::PickClassname(zSTRING classname)
{
	return classname.PickWord(1,zSTRING(LIST_PREFIX)+zSTRING(LIST_POSTFIX),zSTRING(LIST_PREFIX)+zSTRING(LIST_POSTFIX));
}


void spcCVobLogicalDialog::OnSelchangeActionType() 
{
	switch (ctrl_action_type.GetCurSel())
	{
	case LOG_TYPE_REPLACE:
		{
			UpdateData(true);
			zoptions->ChangeDir(DIR_WORLD);
			CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"All Files (*.*)|*.*||");
			zFILE::DirectFileAccess(true);
			int result = dlg.DoModal();
			zFILE::DirectFileAccess(false);
			if (result == IDOK)	
			{
				m_replace_zen_file = dlg.GetPathName();
			}
			else
			{
				ctrl_action_type.SetCurSel(LOG_TYPE_CONVERT);
			};
		};
		break;
	case LOG_TYPE_COLLECT:
		{
			CMainFrame::mainframe->GetVobContainer()->ShowWindow(SW_SHOW);
		};
		break;
	}
	UpdateDialogItems();
}

void spcCVobLogicalDialog::UpdateDialogItems()
{
	if (ctrl_action_type.GetCurSel()!=LOG_TYPE_CONVERT)
	{
		ctrl_classselector_nc.SetCurSel(-1);
	};
	ctrl_classselector_nc.EnableWindow(ctrl_action_type.GetCurSel()==LOG_TYPE_CONVERT && m_mode_new);

	ctrl_classselector.EnableWindow(!m_mode_new);
};

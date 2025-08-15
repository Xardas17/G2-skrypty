// spcCObjectCreationPage.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCObjectCreationPage.h"
#include "mainfrm.h"

#include "zarchiver.h"
#include "zvobmisc.h"
#include "zparser.h"

#include "spcCObjectSheet.h"
#include "spcCObjPropList.h"
#include "spcCObjPreset.h"
#include "spcCHelpDlg.h"
#include "spcCInputDialog.h"
#include "spcCWindowResizeStyle.h"
#include "spcCObjectScriptedDlg.h"

// pfui pfui
//#include "oitem.h"
//#include "onpc.h"



const CString PRESET_ENTRY_NEWOBJECT = "[NEW]";
const CString POSTFIX_CLASS_SCRIPTED = "scripted";
const CString POSTFIX_CLASS_ABSTRACT = "abstract";
const CString POSTFIX_CLASS_CURRUPT  = "currupt";


/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite spcCObjectCreationPage 

IMPLEMENT_DYNCREATE(spcCObjectCreationPage, CPropertyPage)

spcCObjectCreationPage::spcCObjectCreationPage() : CPropertyPage(spcCObjectCreationPage::IDD)
{
	//{{AFX_DATA_INIT(spcCObjectCreationPage)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT

	base_class_name = "";
	isEnabled = true;
}

spcCObjectCreationPage::~spcCObjectCreationPage()
{
}

void spcCObjectCreationPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCObjectCreationPage)
	DDX_Control(pDX, IDC_DEL_PRESET, ctrl_tools_del);
	DDX_Control(pDX, IDC_EXPORT_PRESETS, ctrl_tools_export);
	DDX_Control(pDX, IDC_PRESETLIST, ctrl_presetlist);
	DDX_Control(pDX, IDC_CLASSTREE, ctrl_classtree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCObjectCreationPage, CPropertyPage)
	//{{AFX_MSG_MAP(spcCObjectCreationPage)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CLASSTREE, OnSelchangedClasstree)	
	ON_WM_CLOSE()
	ON_NOTIFY(NM_RCLICK, IDC_CLASSTREE, OnRclickClasstree)
	ON_NOTIFY(NM_DBLCLK, IDC_CLASSTREE, OnDblclkClasstree)		
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_PRESETLIST, OnRclickPresetlist)
	ON_NOTIFY(LVN_KEYDOWN, IDC_PRESETLIST, OnKeydownPresetlist)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_PRESETLIST, OnBeginlabeleditPresetlist)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_PRESETLIST, OnEndlabeleditPresetlist)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_EXPORT_PRESETS, OnExportPresets)
	ON_BN_CLICKED(IDC_DEL_PRESET, OnDelPreset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCObjectCreationPage 















void spcCObjectCreationPage::BuildClassHierarchy (HTREEITEM parent, zCClassDef *parentClassDef)
{
	zSTRING baseName;
	zSTRING s;
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
				
			CString postfix = "";				
			if (!baseOK)
			{
				if (!postfix.IsEmpty()) postfix += ",";
				postfix += POSTFIX_CLASS_CURRUPT;
			}
			if (classDef->IsScriptedClass()) 
			{
				if (!postfix.IsEmpty()) postfix += ",";
				postfix += POSTFIX_CLASS_SCRIPTED;				
			}
			if (classDef->IsAbstractClass())
			{
				if (!postfix.IsEmpty()) postfix += ",";
				postfix += POSTFIX_CLASS_ABSTRACT;				
			}
			if (!postfix.IsEmpty()) s = s + " (" + postfix+")";
			
			HTREEITEM newITEM = ctrl_classtree.InsertItem(s.ToChar(),parent);
			
			BuildClassHierarchy (newITEM, classDef);
		};
	};
};

void spcCObjectCreationPage::BuildClassHierarchy ()
{		
	ctrl_classtree.DeleteAllItems();
	HTREEITEM newITEM1=0;
	HTREEITEM newITEM2=0;
	
	int c =0;
	BOOL found = FALSE;
	zCClassDef* vobClass = 0; 
	while ( c<zCClassDef::GetNum() && !found)
	{
		vobClass = zCClassDef::GetClassDefByIndex(c);
		found = (vobClass->GetClassName_()==base_class_name);
		if ( !found ) c++;
	}
	if (found )
	{		
		zSTRING s = vobClass->GetClassName_();
		newITEM1 = ctrl_classtree.InsertItem(s.ToChar(),TVI_ROOT);
		BuildClassHierarchy(newITEM1,vobClass);		
	}
	
	zSTRING base_class_name2 = "zCEventMessage";
	if (base_class_name != base_class_name2)
	{
		c =0;
		found = FALSE;
		vobClass = 0; 
		while ( c<zCClassDef::GetNum() && !found)
		{
			vobClass = zCClassDef::GetClassDefByIndex(c);
			found = (vobClass->GetClassName_()==base_class_name2);
			if ( !found ) c++;
		}
		if (found )
		{			
			zSTRING s = vobClass->GetClassName_();
			newITEM2 = ctrl_classtree.InsertItem(s.ToChar(),TVI_ROOT);
			BuildClassHierarchy(newITEM2,vobClass);			
		}
	}

	if (newITEM2) ctrl_classtree.Expand(newITEM2,TVE_EXPAND);
	if (newITEM1) ctrl_classtree.Expand(newITEM1,TVE_EXPAND);
	UpdateData(FALSE);
}




/////////////////////////////////////////////////////////////////////////////
// spcCObjectCreationPage message handlers


BOOL spcCObjectCreationPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	zERR_MESSAGE(6,zERR_BEGIN,"B: SPC: Initializing spcCObjectCreationPage-Instance");
		
	// Resizing-Elemente festlegen

	spcCWindowResizeStyle* style;

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_classtree,this, WIN_ALIGN_LEFT, WIN_ALIGN_TOP, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
		
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_presetlist,this, WIN_ALIGN_LEFT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);
	
	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_tools_export,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	style = new spcCWindowResizeStyle;
	style->Init(&ctrl_tools_del,this, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM, WIN_ALIGN_RIGHT, WIN_ALIGN_BOTTOM);
	childResizeList.AddTail(style);

	UpdateData(false);

	zERR_MESSAGE(6,zERR_END,"");

	base_class_name = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}



void spcCObjectCreationPage::OnClose() 
{
	CPropertyPage::OnClose();
}

void spcCObjectCreationPage::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	//CPropertyPage::OnCancel();
}

void spcCObjectCreationPage::OnRclickClasstree(NMHDR* pNMHDR, LRESULT* pResult) 
{		
	
	*pResult = 0;
}

void spcCObjectCreationPage::OnSelchangedClasstree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// NMTREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;		

	UpdateData(true);

	// Selektierte Klasse ermitteln
	CString classname = GetSelectedClassName();

	CreatePresetList(classname);

	// Hilfsfenster (Topic-Examples: "zCVob")
	if (CMainFrame::mainframe) CMainFrame::mainframe->GetHelpWindow()->SetHelpTopic(HELP_TOPIC_CLASS,classname.GetBuffer(0));

	UpdateData(false);

	*pResult = 0;
}

void spcCObjectCreationPage::OnDblclkClasstree(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	NMTREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;		
		
	*pResult = 0;

	if (!ctrl_classtree.IsWindowEnabled())
	{
		CMainFrame::mainframe->OnObjStandardMode();
	};
}


void spcCObjectCreationPage::OnSize(UINT nType, int cx, int cy) 
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

void spcCObjectCreationPage::ShowPopupMenue(CPoint point)
{
	return;
	if (!CMainFrame::mainframe) return;

	// get rectangle of view
	RECT rc;
	GetWindowRect(&rc);

	// get popup-menu
	CMenu mainmenu;		
	VERIFY(mainmenu.LoadMenu(IDR_POPUPS));
	CMenu* menu = NULL;			
	CString s;
	
	menu = mainmenu.GetSubMenu(2);
	ASSERT(menu != NULL);
	menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, rc.left+point.x, rc.top+point.y, AfxGetMainWnd());
}


void spcCObjectCreationPage::OnRclickPresetlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	//CPoint point;
	//ShowPopupMenue(point);
	*pResult = 0;
}

void spcCObjectCreationPage::OnKeydownPresetlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	
	switch (pLVKeyDow->wVKey)
	{
	case VK_DELETE:
		{		
			OnDelPreset();
			break;
		}
	};
		
	*pResult = 0;
}

void spcCObjectCreationPage::CreatePresetList(CString classname)
{
	if (!CMainFrame::mainframe) return;

	// Presetliste holen	
	presetView = 0;
	if (classname.IsEmpty()) classname = GetSelectedClassName();
	
	zSTRING name_of_class = zSTRING(classname.GetBuffer(0));
	presetView = CMainFrame::mainframe->presetLib.GetNewView(name_of_class);
	
	if (!presetView)
	{
		zERR_WARNING("B: SPC: No PresetView returned");
		return;
	};
	
	// Preset-Listebox
	ctrl_presetlist.DeleteAllItems();	
	
	ctrl_presetlist.InsertItem(0,PRESET_ENTRY_NEWOBJECT); // Eintraeg fuer "Neues Object"

	// Presets einfügen...
	zCObjPreset* preset;	
	CString presetname;
	int count = presetView->GetNumInList();
	for (int i=0;i<count;i++)
	{
		preset = (*presetView)[i];
		if (preset)
		{
			presetname = CString(preset->presetName.ToChar());
			ctrl_presetlist.InsertItem(i+1,presetname);
		}
	};

	UpdateData(false);
	UpdateWindow();
}
void spcCObjectCreationPage::OnBeginlabeleditPresetlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	presetname_in_work = GetSelectedPresetName();
	if (presetname_in_work==PRESET_ENTRY_NEWOBJECT)
	{		
		*pResult = 1;
		return;
	};	
	
	*pResult = 0;
}

void spcCObjectCreationPage::OnEndlabeleditPresetlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	CString newname = pDispInfo->item.pszText;
	newname.MakeUpper();
	zSTRING new_name = newname.GetBuffer(0);	
	if (newname.IsEmpty() || (newname==PRESET_ENTRY_NEWOBJECT))
	{			
		CreatePresetList();		
		*pResult = 0;
		return;
	};	
	
	RenamePreset(presetname_in_work,newname);
	
	*pResult = 0;
}

CString spcCObjectCreationPage::GetSelectedPresetName()
{
	// Presetnamen ermitteln
	POSITION pos = ctrl_presetlist.GetFirstSelectedItemPosition();
	CString presetname=PRESET_ENTRY_NEWOBJECT;
	if (pos) 
	{
		int index = ctrl_presetlist.GetNextSelectedItem(pos);
		presetname = ctrl_presetlist.GetItemText(index,0);
	}	
	return presetname;
}

CString spcCObjectCreationPage::GetSelectedClassName()
{
	HTREEITEM selectTreeItem;
	selectTreeItem = ctrl_classtree.GetSelectedItem();
	if (!selectTreeItem) return "";
	CString classname = ctrl_classtree.GetItemText(selectTreeItem);
	int index = classname.Find(' ',0);
	if (index>=0) classname.Delete(index,classname.GetLength()-index);
	classname.TrimLeft();
	classname.TrimRight();
	return classname;
}

void spcCObjectCreationPage::DeletePreset(CString presetName)
{		
	presetView->RemovePresetByName(presetName.GetBuffer(0));

	CreatePresetList();
}

void spcCObjectCreationPage::RenamePreset(CString oldname, CString newname)
{
	zCObjPreset* preset = presetView->GetPresetByName(oldname.GetBuffer(0));
	if (!preset) return;

	preset->presetName = newname;
	
	CreatePresetList();
}


void spcCObjectCreationPage::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	if (bShow)	
	{		
		CString classname = GetSelectedClassName();
		CreatePresetList(classname);
		((spcCObjectSheet*)GetParent())->SetActionButtonText(BUTTON_TEXT_CREATE_ACTIVATE);
	};
	
}

void spcCObjectCreationPage::Enable(bool enabled)
{
	EnableWindow(enabled);

	ctrl_presetlist.EnableWindow(enabled);
	ctrl_classtree.EnableWindow(enabled);

	isEnabled = enabled;
}

bool spcCObjectCreationPage::SetBaseClass(zSTRING class_name)
{
	if (base_class_name != class_name)
	{
		base_class_name = class_name;
	
		BuildClassHierarchy();

		return true; // changed
	}
	else
	{
		return false; // not changed
	};
};


zCObject* spcCObjectCreationPage::CreateNewObject()
{
	UpdateData(TRUE);	

	// Klassen- und Presetnamen ermitteln
	HTREEITEM sel = ctrl_classtree.GetSelectedItem();
	if (sel==NULL) return 0;	
	CString classname	= GetSelectedClassName();
	CString presetname	= GetSelectedPresetName();
	zCClassDef* classDef = zCObject::GetClassDef(classname.GetBuffer(0));

	if (!classDef || classDef->IsAbstractClass()) return 0;
	
	// Objekt erzeugen
	zCObject* obj = 0;	

	// Die Daten aus einem Script holen?
	if (classDef->IsScriptedClass())
	{
		obj = CreateNewObjectFromScript(classname);
	}	
	// Ein neues Object erstellen?
	else if (presetname==PRESET_ENTRY_NEWOBJECT)	
	{
		obj = zCObject::CreateNewInstance(zSTRING(classname.GetBuffer(0)));
	}
	// Ein Presetname wurde gewaehlt ...
	else if (!presetname.IsEmpty())
	{
		obj = CreateNewObjectFromPreset(presetname);
	}
		
	return obj;	
}

zCObject* spcCObjectCreationPage::CreateNewObjectFromPreset(CString presetname)
{
	zCObject* obj = 0;
	zSTRING name_of_preset = zSTRING(presetname.GetBuffer(0));
	// Referenzßobjekt holen und Kopie davon erzeugen		
	zCObject* refObject = CMainFrame::mainframe->presetLib.GetObjectByName(name_of_preset);
	obj = refObject->CreateCopy();
	// Presetnamen setzen
	zCVob* avob = dynamic_cast<zCVob*>(obj);
	if (avob) avob->SetVobPresetName(name_of_preset);		
	
	return obj;
}

// [EDENFELD] 1.33: eingefüge Script Objekte bleiben jetzt im Menu und müssen nicht immer wieder
// umständlich neu aus der Objectliste geholt werden
zCObject* spcCObjectCreationPage::CreateNewObjectFromScript(CString classname)
{
	static CString lastInstance = "";
	static CString lastObjectType = "";

	zCObject* obj=0;
	spcCObjectScriptedDlg dlg;
	dlg.SetObjectClass(classname.GetBuffer(0));

	if (!lastInstance.IsEmpty() && ( dlg.m_object_type==lastObjectType) ) 
	{
		dlg.m_selected_instance = lastInstance;
		
	}

	int result = dlg.DoModal();
	if (result == IDOK) 
	{
		zSTRING instance = dlg.GetObjectInstance();
		
		if (instance.IsEmpty()) return 0;
		
		obj = zCObject::CreateNewInstance(classname.GetBuffer(0));
		zCVob* vob = dynamic_cast<zCVob*>(obj);
		if (!vob) return 0;
		vob->SetByScriptInstance(&instance,-1);
		//vob->SetCollType(zVOB_COLL_TYPE_SMALL_OBJECT);
		
		// Vobnamen setzen
		zSTRING vobName = dlg.GetObjectName();
		if (!vobName.IsEmpty()) 
		{
			zCVob* avob = dynamic_cast<zCVob*>(obj);
			if (avob) avob->SetVobName(vobName);
		}

		lastInstance = instance.ToChar();
		lastObjectType = dlg.m_object_type;
	}

	return obj;
}

zCObject* spcCObjectCreationPage::UpdateObjectFromPreset(zCObject* obj)
{
	if (!obj) return 0;

	// Presetnamen ermitteln
	CString presetname	= GetSelectedPresetName();

	zCObject* newobj = 0;
	zSTRING name_of_preset = zSTRING(presetname.GetBuffer(0));
	// Referenzobjekt holen und Kopie davon erzeugen		
	zCObject* refObject = CMainFrame::mainframe->presetLib.GetObjectByName(name_of_preset);

	if (refObject->GetClassDef() != obj->GetClassDef()) return false;

	newobj = refObject->CreateCopy();
	// Presetnamen setzen
	zCVob* anewvob	= dynamic_cast<zCVob*>(newobj);
	zCVob* avob		= dynamic_cast<zCVob*>(obj);
	if (anewvob && avob) 
	{
		anewvob->SetTrafoObjToWorld(avob->trafoObjToWorld);
		anewvob->SetVobPresetName(name_of_preset);
	}
	
	return newobj;
};

void spcCObjectCreationPage::OnExportPresets() 
{
	if (ctrl_presetlist.GetSelectedCount()<=0) return;

	CString classname = GetSelectedClassName();	
					
	// Presetnamen ermitteln
	zCObject* obj;
	zSTRING zpresetname;
	POSITION pos = ctrl_presetlist.GetFirstSelectedItemPosition();
	CString presetname;
	zCArchiver* arch=0;
	while (pos) 
	{			
		int index = ctrl_presetlist.GetNextSelectedItem(pos);
		presetname = ctrl_presetlist.GetItemText(index,0);

		if (presetname!=PRESET_ENTRY_NEWOBJECT)
		{
			if (!arch)
			{
				zoptions->ChangeDir(DIR_DATA);
				CFileDialog dlg(FALSE,"zen",classname+"_presets.zen",OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"All Files (*.*)|*.*||");			
				zFILE::DirectFileAccess(true);
				int result = dlg.DoModal();
				zFILE::DirectFileAccess(false);
				if (result!=IDOK) return;				
				zSTRING filepath = zSTRING(dlg.GetPathName().GetBuffer(0));

				arch = zarcFactory.CreateArchiverWrite(filepath,zARC_MODE_ASCII,TRUE);										
			};
			zpresetname = zSTRING(presetname.GetBuffer(0));	
		
			obj = CMainFrame::mainframe->presetLib.GetObjectByName(zpresetname);
			arch->WriteObject(obj);
		}
	}		
	if (arch)
	{
		arch->Close();	
		zRELEASE(arch);
	}

}

void spcCObjectCreationPage::OnDelPreset() 
{
	CString presetname = GetSelectedPresetName();
	if (presetname==PRESET_ENTRY_NEWOBJECT) return;
	int result = AfxMessageBox("Really delete preset "+presetname+"?",MB_YESNO);
	if (result==IDYES)
	{				
		DeletePreset(presetname.GetBuffer(0));
	};
}

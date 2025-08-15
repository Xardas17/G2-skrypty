// spcCMacroDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "zengine.h"
#include "zwaynet.h"

#include "Spacer.h"

// Spacer
#include "MainFrm.h"
#include "SpacerDoc.h"
#include "SpacerView.h"

// spc

#include "spcCMacroDlg.h"
#include "spcCInputDialog.h"
#include "spcCCompileAction.h"
#include "spcCWorkInfoDlg.h"
#include "spcCViewProgressBar.h"
// z-files
#include "zdisk.h"
#include "zworld.h"
#include "zwin32.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

spcCMacro::spcCMacro()
{	
	props = "";
	view=0;
	doc=0;
};

spcCMacro::~spcCMacro()
{	
};
	
// [EDENFELD] 1.33 neu aus ModSource
void spcCMacro::Run(CSpacerDoc* _doc, CSpacerView* _view)
{
	doc		=	_doc;
	view	=	_view;
	CString macroprops = props;
	zSTRING commandline;
	zSTRING answer;
	bool result;	
	zERR_MESSAGE(1,0,"B: SPC MACRO: Running macro \""+zSTRING(name.GetBuffer(0))+"\"");
	
	bool workingDlgOpened = false;	
	if (!workingDlg)
	{
		workingDlgOpened = true;
		workingDlg = new spcCWorkInfoDlg();
		workingDlg->Init();
	}
	
	bool winDisabled = true;
	if (CMainFrame::mainframe) 
	{		
		winDisabled = CMainFrame::mainframe->DeactivateApplicationWindows();		
	}

	if (workingDlg) workingDlg->AddMessage("Running macro \""+name+"\"");

	int index = 0;
	do 
	{
		index = macroprops.Find('\n',0);
		if (index<0) index = macroprops.GetLength();
		
		commandline = macroprops.GetBuffer(0);
		commandline.Delete(index);
		commandline.Delete("\r");
		commandline.Delete("\n");
		macroprops.Delete(0,index+1);		

		
		if (!commandline.IsEmpty() && (commandline[0] != '/')) 		
		{
			if (workingDlg) workingDlg->AddMessage("Command \""+CString(commandline.ToChar())+"\"");

			result = RunCommand(commandline, answer);

			if (!answer.IsEmpty())
				if (result)		{ if (workingDlg) workingDlg->AddMessage(": "+CString(answer.ToChar()));			}
				else 			{ if (workingDlg) workingDlg->AddMessage(": Error? "+CString(answer.ToChar()));		}
		};

		if (CMainFrame::mainframe) 
		{		
			if (CMainFrame::mainframe->DeactivateApplicationWindows()) winDisabled = true;
		}

	} while (macroprops.GetLength()>0);
	
	if (CMainFrame::mainframe && winDisabled) 
	{		
		CMainFrame::mainframe->ReactivateApplicationWindows();		
	}

	if (workingDlgOpened)
	{
		workingDlg->CloseWindow();
		workingDlg->DestroyWindow();
		//delete workingDlg;
		workingDlg = 0;
	};

	if (doc->GetWorld())
	{
		zCWayNet* waynet = doc->GetWorld()->GetWayNet();
		if (waynet)
		{
			zSTRING result = waynet->MergeWaypoints();
			if (!result.IsEmpty())
			{
				AfxMessageBox(zSTRING(zSTRING("Merged the following waypoints:\r\n")+result).ToChar());
			};
		};
	};

	result = doc->VobDetectCollision();
	//if (!result) AfxMessageBox("Macro \""+name+"\" finished\r\n\r\n... but there are colliding vobs.\r\nHave a look at the list of vobs in the vobtree.");
	//else AfxMessageBox("Macro \""+name+"\" finished");	

}

bool spcCMacro::RunCommand(zSTRING commandline, zSTRING answer)
{	
	answer.Clear();
	commandline.Upper();
	zSTRING wort[20];
	for (int i=0;i<20;i++) 
	{
		wort[i] = commandline.PickWord(i+1," ,\r\n\0"," ,\r\n\0");	
		if (wort[i]=="/P") AfxMessageBox("Pause (Macro-Intermission)\r\n\r\ncommand:\r\n"+CString(commandline.ToChar()));
	}

	if (wort[0] == ">")
	{				
		zerr.Separator();
		zERR_MESSAGE(1,0,"B: SPCMAC: "+commandline.PickWord(2,">\r\n\0","\r\n\0"));
		zerr.Separator();
		return true;
	}

	else
	if (wort[0] == "RESET")
	{				
		doc->Reset();
		return true;
	}

	else
	if (wort[0] == "LOAD")
	{
		if (wort[1]=="WORLD") McLoadWorldFile(wort[2]);
		else if (wort[1]=="MESH") McLoadMeshFile(wort[2]);
		return true;
	}
	
	else		
	if (wort[0] == "SAVE")
	{
		zBOOL compiled	= (wort[3]=="COMPILED"	|| wort[4]=="COMPILED");
		zBOOL binary	= !(wort[3]=="ASCII"	|| wort[4]=="ASCII");
		if (wort[1]=="WORLD")		McSaveWorldFile	(wort[2], compiled, binary);
		else if (wort[1]=="MESH")	McSaveMeshFile	(wort[2]);
		return true;
	}

	else
	if (wort[0] == "COMPILE")
	{
		answer = "macro-command "+wort[0]+" not implemented.";

		if		(wort[1] == "WORLD") McCompileWorld(commandline);
		else if (wort[1] == "LIGHT") McCompileLight(commandline);
		
		return false;
	}		
	else
	if (wort[0] == "SET")
	{
		if (wort[1]=="ERROR")
		{
			int errprio = wort[2].ToInt();
			if (errprio>=2)	{ zerr.SetFilterLevel(errprio);return true; }
			else			{ answer="Unknown or too low error-level: "+wort[2]; return false; }
		};
	}
	else
	if (wort[0] == "RENDER")
	{
		int num = wort[1].ToInt();
		for (int i=0;i<num;i++) 
		{
			CSpacerView::view->RedrawWindow(0,0,RDW_INVALIDATE);
		};
	}
	
	else if (!wort[0].IsEmpty())
	{		
		answer = "Unknown macro-command "+wort[0]+".";
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCMacroDlg 


spcCMacroDlg::spcCMacroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(spcCMacroDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCMacroDlg)
	m_edit = _T("");
	m_list_entry = _T("");
	executeMacro = 0;
	//}}AFX_DATA_INIT	
}


void spcCMacroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCMacroDlg)	
	DDX_Control(pDX, IDC_NEW, ctrl_new);
	DDX_Control(pDX, IDC_RENAME, ctrl_rename);
	DDX_Control(pDX, IDC_DELETE, ctrl_delete);
	DDX_Control(pDX, IDC_LIST, ctrl_list);
	DDX_Control(pDX, IDC_EDIT, ctrl_edit);
	DDX_Text(pDX, IDC_EDIT, m_edit);
	DDX_LBString(pDX, IDC_LIST, m_list_entry);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCMacroDlg, CDialog)
	//{{AFX_MSG_MAP(spcCMacroDlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_EN_CHANGE(IDC_EDIT, OnChangeEdit)
	ON_EN_KILLFOCUS(IDC_EDIT, OnKillfocusEdit)
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_NEW, OnNew)	
	ON_BN_CLICKED(IDC_RENAME, OnRename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten spcCMacroDlg 

spcCMacro* spcCMacroDlg::GetExecuteMacro()
{
	return executeMacro;
}

void spcCMacroDlg::OnChangeEdit() 
{
	// TODO: Wenn dies ein RICHEDIT-Steuerelement ist, sendet das Steuerelement diese

	// Benachrichtigung nicht, bevor Sie nicht die Funktion CDialog::OnInitDialog()

	// überschreiben und CRichEditCrtl().SetEventMask() aufrufen, wobei

	// eine ODER-Operation mit dem Attribut ENM_CHANGE und der Maske erfolgt.

	

	// TODO: Fügen Sie hier Ihren Code für die Benachrichtigungsbehandlungsroutine des Steuerelements hinzu

	
}

void spcCMacroDlg::OnKillfocusEdit() 
{
	POSITION pos;
	spcCMacro* macro = SearchMacro(m_list_entry,pos);
	if (macro)
	{
		UpdateData(TRUE);	
		macro->SetMacroProperties(m_edit);
		UpdateData(FALSE);
	}
	else zERR_WARNING("B: SPC MACRO: Could not find macro "+zSTRING(m_list_entry.GetBuffer(0)));
}

void spcCMacroDlg::OnDblclkList() 
{
	UpdateData(TRUE);
	POSITION pos;
	executeMacro = SearchMacro(m_list_entry,pos);

	if (executeMacro) OnOK();
}

void spcCMacroDlg::OnSelchangeList() 
{
	UpdateData(TRUE);
	POSITION pos;
	spcCMacro* macro = SearchMacro(m_list_entry,pos);
	if (macro)
	{
		m_edit = macro->GetMacroProperties();
		ctrl_edit.SetFocus();
	}
	else 
	{
		zERR_WARNING("B: SPC MACRO: Could not find macro "+zSTRING(m_list_entry.GetBuffer(0)));
		m_edit = "";
	}
	UpdateData(FALSE);
}

void spcCMacroDlg::OnNew() 
{
	spcCInputDialog dlg;	
	spcCMacro* newmacro=0;
	bool finished = false;
	int result;
	do
	{		
		result = dlg.DoModal();
		if (result == IDOK)
		{
			POSITION pos;
			newmacro = SearchMacro(dlg.GetInput(),pos);
			finished = (newmacro==0);
			if (!finished) AfxMessageBox("A macro with the name\r\n\""+dlg.GetInput()+"\"\r\nalready exists!");
		}

	} while ( (result==IDOK) && (!finished));

	if (finished)
	{
		newmacro = new spcCMacro;
		newmacro->SetMacroName(dlg.GetInput());
		newmacro->SetMacroProperties("// spacer macro \""+newmacro->GetMacroName()+"\"\r\n");
		macroList.AddTail(newmacro);
		ctrl_list.AddString(newmacro->GetMacroName());
	}

	UpdateData(FALSE);
}

void spcCMacroDlg::OnDelete() 
{
	UpdateData(TRUE);
	POSITION pos;
	spcCMacro* macro = SearchMacro(m_list_entry, pos);
	if (!macro) return;
	if (!pos)	return;

	ctrl_list.DeleteString(ctrl_list.FindString(0,m_list_entry));
	macroList.RemoveAt(pos);
	delete macro;macro=0;
	
	UpdateData(FALSE);
}

void spcCMacroDlg::OnRename() 
{
	UpdateData(TRUE);
	POSITION pos;
	spcCMacro* macro = SearchMacro(m_list_entry, pos);
	if (!macro) return;
	
	spcCInputDialog dlg;	
	dlg.SetInput(macro->GetMacroName());
	spcCMacro* foundmacro=0;
	bool finished = false;
	int result;
	do
	{				
		result = dlg.DoModal();
		if (result == IDOK)
		{
			POSITION pos;
			foundmacro = SearchMacro(dlg.GetInput(),pos);
			finished = (foundmacro==0);
			if (!finished) AfxMessageBox("A macro with the name\r\n\""+dlg.GetInput()+"\"\r\nalready exists!");
		}

	} while ( (result==IDOK) && (!finished));
	
	macro->SetMacroName(dlg.GetInput());

	ctrl_list.DeleteString(ctrl_list.FindString(0,m_list_entry));	
	ctrl_list.AddString(dlg.GetInput());	
	
	UpdateData(FALSE);
}

void spcCMacroDlg::OnOK() 
{	
	SaveMacroFile("macros.zmf");
	CDialog::OnOK();
}

void spcCMacroDlg::OnCancel() 
{
	SaveMacroFile("macros.zmf");
	executeMacro = 0;	
	CDialog::OnCancel();
}

spcCMacro* spcCMacroDlg::SearchMacro(CString name, POSITION& pos)
{
	CString name2;
	name.MakeUpper();
	spcCMacro* macro = 0;
	POSITION curpos = macroList.GetHeadPosition();	
	while (curpos)
	{
		pos = curpos;
		macro = macroList.GetNext(curpos);
		name2 = macro->GetMacroName();
		name2.MakeUpper();			
		if (macro && (name == name2))
		{		
			return macro;
		};		
	};
	return 0;
}

void spcCMacroDlg::SaveMacroFile(CString filename)
{
	// Macro-Datei laden
	zSTRING line;
	zSTRING macrofilename=zSTRING(filename.GetBuffer(0));
	POSITION pos;

	spcCMacro* macro;
	CString macroname;	

	zFILE* file = new zFILE_FILE;
	zoptions->ChangeDir(DIR_TOOLS_CONFIG);
	if (file->Exists(macrofilename))
	{
		zFILE_FILE backupfile(macrofilename+".bak");
		file->FileCopy(&backupfile);
	};
	
	if (file->Create(macrofilename) == zERR_NONE)
	{
		for (int i=0;i<ctrl_list.GetCount();i++)
		{
			ctrl_list.GetText(i,macroname);			
			macro = SearchMacro(macroname, pos);
			if (macro)
			{
				file->Write("["+macro->GetMacroName()+"]\r\n");
				file->Write(macro->GetMacroProperties()+"\r\n");
			}
			else zERR_WARNING("B: SPC MACRO: Could not find macro "+zSTRING(macroname.GetBuffer(0)));
		}
		file->Close();
	}
	else
	{
		zERR_WARNING("B: SPC MACRO: Could not create file "+macrofilename);
	};

}

void spcCMacroDlg::LoadMacroFile(CString filename)
{
	// Macro-Datei laden
	zSTRING line;
	zSTRING macrofilename=zSTRING(filename.GetBuffer(0));

	spcCMacro* macro = 0;
	zSTRING name;
	zSTRING props;

	zFILE* file = new zFILE_FILE;
	zoptions->ChangeDir(DIR_TOOLS_CONFIG);
	if (!file->Exists(macrofilename))
	{
		file->Create(macrofilename);
	};

	if (file->Open(macrofilename) == zERR_NONE)
	{
		while (!file->Eof())
		{
			file->Read(line);
			if (line.Length()>0)
				if (line[0]=='[')
				{					
					// Neues Macro beginnen
					line.Delete("[",zSTR_TO);
					line.Delete("]",zSTR_FROM);
					macro = new spcCMacro;					
					macro->SetMacroName(line.ToChar());
					props.Clear();

					// Macro in die Liste eintragen
					macroList.AddTail(macro);					
					ctrl_list.AddString(macro->GetMacroName());
				}

				else if (macro)
				{
					// Zeile dem aktuellen Macro hinzufügen
					props = props+line+"\r\n";
					macro->SetMacroProperties(props.ToChar());
				};

		}
		file->Close();
	}
	else
	{
		zERR_WARNING("B: SPC MACRO: Could not read/create file "+macrofilename);
	};

}

BOOL spcCMacroDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadMacroFile("macros.zmf");	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void spcCMacro::McLoadWorldFile(zSTRING filename)
{	
	zoptions->ChangeDir(DIR_WORLD);
	
	if (!doc->IsAWorldLoaded())
	{
		zERR_MESSAGE(2,0,"B: SPC MACRO: Loading first world: \""+filename+"\" ...");
		doc->LoadFile(filename.ToChar(), LOAD_ZEN_UC);
	}
	else
	{		
	
		if (filename.Search("ZEN")>0)
		{
			zERR_MESSAGE(2,0,"B: SPC MACRO: Merging file \""+filename+"\" ... ");
			
			spcCViewProgressBar* progressBar = new spcCViewProgressBar(0,0,0,0);
			progressBar->Init(AfxGetMainWnd());
			doc->GetWorld()->SetProgressBar(progressBar);
	
			doc->GetWorld()->MergeVobSubtree(filename);

			doc->GetWorld()->SetProgressBar(0);
			delete progressBar;progressBar=0;
		}
		else zERR_WARNING("B: SPC MACRO: Unknown filetype. File \""+filename+"\"!");
	
	};
	
}

void spcCMacro::McLoadMeshFile(zSTRING filename)
{	
	zoptions->ChangeDir(DIR_MESHES);
	
	if (!doc->IsAWorldLoaded())
	{
		zERR_MESSAGE(2,0,"B: SPC MACRO: Loading first mesh: \""+filename+"\" ...");
		doc->LoadFile(filename.ToChar(), LOAD_3DS);
	}
	else
	{		
	
		if (filename.Search("3DS")>0)
		{
			zERR_MESSAGE(2,0,"B: SPC MACRO: Merging mesh \""+filename+"\" ... ");
			doc->GetWorld()->LoadWorld(filename, zCWorld::zWLD_LOAD_EDITOR_UNCOMPILED);
		}
		else zERR_WARNING("B: SPC MACRO: Unknown filetype. File \""+filename+"\"!");
	
	};
	
}

void spcCMacro::McCompileWorld(const zSTRING& parm)
{
	if (!CSpacerDoc::doc->IsAWorldLoaded()) return;

	spcCCompileWorldAction mode;
	mode.detectLeaks = (parm.Search("LEAKCHECK")>0);
	mode.editormode  = (parm.Search("EDIT")>0);	
	mode.polycheck	 = (parm.Search("POLYCHECK")>0);	
	mode.quick		 = (parm.Search("QUICK")>0);
	mode.inout       = zBSP_MODE_INDOOR;
	if (parm.Search("OUTDOOR")>0) mode.inout = zBSP_MODE_OUTDOOR;
	
	view->Do_CompileWorld(mode);
}

void spcCMacro::McCompileLight(const zSTRING& parm)
{
	if (!CSpacerDoc::doc->IsAWorldLoaded()) return;

	spcCCompileLightAction mode;
	mode.vertex_only = (parm.Search("VERTEX")>0);	
	if (parm.Search("LOW")>0) mode.lightmap_level = 1;
	else if (parm.Search("MID")>0) mode.lightmap_level = 2;
	else mode.lightmap_level = 3;

	view->Do_CompileLight(mode);
}

void spcCMacro::McSaveWorldFile(zSTRING filename, zBOOL compiled, zBOOL binary)
{	
	if (!CSpacerDoc::doc->IsAWorldLoaded()) return;

	zoptions->ChangeDir(DIR_WORLD);
	
	if (filename.Search("ZEN")>0)
	{
		zERR_MESSAGE(2,0,"B: SPC MACRO: Saving file \""+filename+"\" ... ");
			
		// Savetype ermitteln
		zSAVE_TYPE type;
		if (binary)			type = SAVE_ZEN_BIN;
		else if (compiled)	type = SAVE_ZEN;
			 else			type = SAVE_ZEN_UC;								

		doc->SaveFile(filename.ToChar(), type);		
	}
	else zERR_WARNING("B: SPC MACRO: Unknown filetype. File \""+filename+"\"!");	
}

void spcCMacro::McSaveMeshFile(zSTRING filename)
{	
	if (!CSpacerDoc::doc->IsAWorldLoaded()) return;

	zoptions->ChangeDir(DIR_WORLD);
	
	if (filename.Search("3DS")>0)
	{
		zERR_MESSAGE(2,0,"B: SPC MACRO: Saving mesh \""+filename+"\" ... ");		
		zCVob* camvob = 0;
		if (zCCamera::activeCam)
		{
			camvob = zCCamera::activeCam->GetVob();				
			zCCamera::activeCam->SetVob(0);
		}
		// save only mesh
		CSpacerDoc::doc->GetWorld()->SaveBspTreeMesh3DS(filename);
		if (camvob) 
		{
			zCCamera::activeCam->SetVob(camvob);				
		}
	}
	else zERR_WARNING("B: SPC MACRO: Unknown filetype. File \""+filename+"\"!");	
}


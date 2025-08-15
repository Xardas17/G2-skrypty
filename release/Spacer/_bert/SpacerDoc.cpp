// SpacerDoc.cpp : implementation of the CSpacerDoc class
//

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"

// Spacer-Files
#include "MainFrm.h"
#include "SpacerDoc.h"
#include "SpacerView.h"
#include "spc_ParseTools.h"
#include "spcCWorkInfoDlg.h"
#include "spcCHelpDlg.h"
#include "spcMatCalc.inc"
#include "spcCObjectSheet.h"
#include "spcCList_Vobs.h"
#include "spcCTextInfoDlg.h"
#include "spcCInfoBar.h"
#include "spcCObjPreset.h"
#include "spcCWorldAnalyseDlg.h"
#include "spcCViewProgressBar.h"
#include "spcCObjectSoundDialog.h"

// z-Files
#include "zoption.h"
#include "z3d.h"
#include "zWorld.h"
#include "zWaynet.h"
#include "zfile3d.h"
#include "zrenderer.h"
#include "zArchiver.h"
#include "zoption.h"
#include "zsndmss.h"
#include "zbuffer.h"
#include "zvobmisc.h"
#include "zcscamera.h"
#include "zexceptionhandler.h"
#include "zlensflare.h"

// o-Files (evil)
#ifdef COMPILING_GOTHIC
	#include "onpc.h"
	#include "ogamemanager.h"
	#include "ospawn.h"
	#include "oaihuman.h"
	#include "oGame.h"
	#include "oworld.h"
#endif

#include "direct.h"

#pragma warning ( disable:4244 )

/////////////////////////////////////////////////////////////////////////////
// CSpacerDoc

IMPLEMENT_DYNCREATE(CSpacerDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpacerDoc, CDocument)
	//{{AFX_MSG_MAP(CSpacerDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_VIEW_HELPERVOBS, OnViewInvisibleVobs)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HELPERVOBS, OnUpdateViewInvisibleVobs)	
	ON_COMMAND(ID_FILE_MERGE, OnFileMerge)
	ON_UPDATE_COMMAND_UI(ID_FILE_MERGE, OnUpdateFileMerge)	
	ON_COMMAND(ID_WORLD_DIFSCRIPT, OnWorldDifscript)
	ON_COMMAND(ID_FILE_OPENMAKEFILE, OnFileOpenmakefile)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPENMAKEFILE, OnUpdateFileOpenmakefile)
	ON_COMMAND(ID_FILE_OPENMESH, OnFileOpenmesh)
	ON_COMMAND(ID_FILE_MERGEMESH, OnFileMergemesh)
	ON_UPDATE_COMMAND_UI(ID_FILE_MERGEMESH, OnUpdateFileMergemesh)	
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_SAVE_ZEN, OnFileSaveZen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_ZEN, OnUpdateFileSaveZen)
	ON_COMMAND(ID_FILE_SAVE_MESH, OnFileSaveMesh)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_MESH, OnUpdateFileSaveMesh)
	ON_COMMAND(ID_TOOLS_INFORMATIONS, OnToolsInformations)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_INFORMATIONS, OnUpdateToolsInformations)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEWEDIT_TOGGLEVOBBOXES, OnViewTogglevobboxes)
	ON_UPDATE_COMMAND_UI(ID_VIEWEDIT_TOGGLEVOBBOXES, OnUpdateVieweditTogglevobboxes)
	ON_COMMAND(ID_WORLD_ANALYSE, OnWorldAnalyse)
	ON_UPDATE_COMMAND_UI(ID_WORLD_ANALYSE, OnUpdateWorldAnalyse)
	ON_COMMAND(ID_WORLD_RELOADPARTICLEFX, OnWorldReloadparticlefx)
	ON_COMMAND(ID_WORLD_ANALYSEWAYNET, OnWorldAnalysewaynet)
	ON_UPDATE_COMMAND_UI(ID_WORLD_ANALYSEWAYNET, OnUpdateWorldAnalysewaynet)
	ON_COMMAND(ID_WORLD_CALLSTARTUPSCRIPT, OnWorldCallstartupscript)
	ON_UPDATE_COMMAND_UI(ID_WORLD_CALLSTARTUPSCRIPT, OnUpdateWorldCallstartupscript)
	ON_COMMAND(ID_QUICK_SAVE, OnQuickSave)
	ON_COMMAND(ID_QUICK_OPEN, OnQuickOpen)
	ON_COMMAND(ID_WORLD_MANIPULATESOUNDS, OnWorldManipulatesounds)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSpacerDoc* CSpacerDoc::doc		= 0;
zCSession*	CSpacerDoc::session	= 0;

//#define ASSIGN_HELPER_VISUALS
static const zSTRING INVISIBLE_FILEPREFIX = "INVISIBLE_";

zSTRING			g_strWorldFileName;

/////////////////////////////////////////////////////////////////////////////
// CSpacerDoc construction/destruction

CSpacerDoc::CSpacerDoc()
	: spcVERSION(""), spcCMVOBNAME("SPACER_LCMOVE_VOB"), addToRecent(true)
{			
	doc = this;

	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	modeViewHelperVobs	= true;	
	isDirty				= false;		
}

CSpacerDoc::~CSpacerDoc()
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Destructing CSpacerDoc-Instance ...");
	Reset();
	camera_vob	= 0;
	session		= 0;
	doc			= 0;
	zERR_MESSAGE(7,zERR_END,"");		
}

static void Handle_UnhandledException_Doc()
{
	if (CSpacerDoc::doc)
	{		
		zCWorld* world=CSpacerDoc::doc->GetWorld();
		if (!world) return;

		if (CSpacerDoc::doc->IsAWorldLoaded())
		{									
			if (world->IsCompiledEditorMode())
			{
				if (AfxMessageBox("An error occured.\r\nShould I save the mesh to as tmp.3ds?",MB_YESNO) == IDYES)
				{
					CSpacerDoc::doc->SaveFile("tmp.3ds", SAVE_3DS);
				}				
			}
			else if (world->IsCompiled())
			{
				if (AfxMessageBox("An error occured.\r\nShould I save the level to as tmp.zen?",MB_YESNO) == IDYES)
				{
					CSpacerDoc::doc->SaveFile("tmp.zen",SAVE_ZEN);
				}				
			}						
		}
	};
}

extern CGameManager* gameMan;

void CSpacerDoc::Init()
{		
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Initializing instance of CSpacerDoc...");

	if (zoptions->Parm("CRASHHANDLER")) zexhnd.AddUnhandledExceptionReleaseCallback ( Handle_UnhandledException_Doc ); 	
	
	session = gameMan->GetGame();			

	if (zrenderer) zrenderer->Vid_SetScreenMode(zRND_SCRMODE_HIDE);		
	
	//////////////////////////////////////////////
	// PARSE
	//////////////////////////////////////////////	
	
	UpdateWindowTitle();
	
	zERR_MESSAGE(7,zERR_END,"");
}

void CSpacerDoc::PresetSyncX(zCTree<zCVob>* node, zCObjPresetLib& pLib, int method , zBOOL warn)
{
	zCVob* thisVob = dynamic_cast<zCVob*>(node->GetData());
	if (!thisVob) return;
		
	zSTRING lpn = thisVob->GetVobPresetName();
	if (!lpn.IsEmpty()) 
	{
		// find preset
		zCObject* prob = pLib.GetObjectByName(lpn);
		if (prob && prob->GetClassName_()==thisVob->GetClassName_()) {
			// this->getPosition
			zPOINT3 vobPosition = thisVob->GetPositionWorld();
			//ArchiveBuffer/BufferArchive			
			zCBuffer*	buffer	= 0;
			zCArchiver* arcWrite	= zarcFactory.CreateArchiverWrite(zARC_MODE_BINARY);
			zCArchiver*	arcRead		= zarcFactory.CreateArchiverRead(buffer);			
			arcWrite->WriteObject(prob);
			buffer = arcWrite->GetBuffer();
			if (buffer)
			{				
				arcRead->ReadObject(thisVob);				
				buffer->SetMode(WRITE);
			}

			arcRead->Close();
			zRELEASE(arcRead);

			arcWrite->Close();
			zRELEASE(arcWrite);			

			//this->RestorePosition
			thisVob->SetPositionWorld(vobPosition);
		} else
		{
			//TODO: spezielle methode
			if (warn)
					zERR_WARNING("B: SPC: Preset not found or invalid class : "+lpn);
		}
	}
	
	zCTree<zCVob>* tree = node->GetFirstChild();	
	while (tree)
	{		
		PresetSyncX(tree, pLib, method, warn);
		tree = tree->GetNextChild();
	}	
}


void CSpacerDoc::PresetSynchronisation(zCObjPresetLib& pLib,int method , zBOOL warn)
{
	if (!GetWorld()) return;

	zCTree<zCVob>* tree = GetWorld()->globalVobTree.GetFirstChild();	
	while (tree)
	{		
		PresetSyncX(tree, pLib, method, warn);
		tree = tree->GetNextChild();
	}
}
void CSpacerDoc::VobTreeCorrX(zCTree<zCVob>* node, zCArray<TFlagMem>& flagMem)
{
	flagMem.Insert(TFlagMem(node->GetData()));
	zCTree<zCVob>* tree = node->GetFirstChild();
	while(tree)
	{
		VobTreeCorrX(tree, flagMem);
		tree = tree->GetNextChild();
	}
}
void CSpacerDoc::VobTreeCorrection(CString& matName)
{
	if (!GetWorld()) return;

	zCVob* transVob = GetWorld()->SearchVobByName(spcCMVOBNAME);
	
	zCTree<zCVob>* tree = GetWorld()->globalVobTree.GetFirstChild();
	// für jeder Levelcomponente
	while (tree)
	{
		zCVobLevelCompo* lev = dynamic_cast<zCVobLevelCompo*>(tree->GetData());
		if (lev) {

			// * finde Poly über matNomenklatur und zugehörige Weltdaten
			zCMesh* levMesh = dynamic_cast<zCMesh*>(lev->GetVisual());
			if (levMesh==0) { tree = tree->GetNextChild(); continue; }

			int z=0;
			BOOL found = FALSE;
			zCPolygon* lpoly = 0;
			while (z<levMesh->numPoly && !found)
			{
				lpoly = levMesh->Poly(z);
				found = (lpoly->GetMaterial()->GetName()==zSTRING(matName.GetBuffer(0)));
				z++;
			}
			// berechne T-Matrix für Level,Poly
			zMAT4 polyMat, vobMat;
			if (found) {
			// berechne Matrix(PolyPos)
				polyMat = CalcMatrixFromPoly(lpoly);
			// berechne Matrix(VobPos)
				vobMat = CalcMatrixFromVob(transVob);
			}
			// wenn jetzt kein transvob für  das poly existiert, erzeugen und raus
			if (found && !transVob)
			{
				transVob = new zCVob();
				transVob->SetVobName(spcCMVOBNAME);
				GetWorld()->AddVob(transVob);				
				transVob->SetTrafoObjToWorld(polyMat);
				zRELEASE(transVob);
				found=false;
			}
			// hat sich die LevelCompo verschoben?
			zMAT4 transMat;
			if (found && CalcMatrixDifference(vobMat,polyMat,transMat))
			{
				zERR_MESSAGE(3,0,"B: SPC: LevelCompo was moved...");
				zCArray<TFlagMem> flagMem;
				// Iteriere den Vobtree und merke alle Flag-Zustände, lösche alle Flags 
				zCTree<zCVob>* vobTree = tree->GetFirstChild();
				while (vobTree)
				{
					VobTreeCorrX(vobTree,flagMem);
					//	verschiebe den VobTree
					zCVob* vobi=vobTree->GetData();
					vobi->SetTrafoObjToWorld(transMat*vobi->trafoObjToWorld);
					vobTree = vobTree->GetNextChild();
				}
				// restauriere die Flaggs
				for (int c=0; c<flagMem.GetNumInList(); c++) flagMem[c].Put();
				// verschiebe transVob dahin
				transVob->SetTrafoObjToWorld(polyMat);
			} // if
		} // if
		tree = tree->GetNextChild();
	} // while
} // method end

BOOL CSpacerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CSpacerDoc diagnostics

#ifdef _DEBUG
void CSpacerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpacerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// SAVING ///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

BOOL CSpacerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::OnSaveDocument(lpszPathName);
}


bool CSpacerDoc::ParseScript(CString scriptname)
{	
	if (scriptname.IsEmpty()) return false;
	
	delete parseinfo;
	parseinfo = new spcCParseInfo();
	parseinfo->PrepareParseInfo();
	
	parser.SetEnableParsing(TRUE);
	zBOOL result = dynamic_cast<oCGame*>(session)->LoadParserFile(scriptname.GetBuffer(0));	

	parseinfo->UpdateParseInfo();
	
	return bool(result==TRUE);
}



/////////////////////////////////////////////////////////////////////////////
// OPEN /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

BOOL CSpacerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{	
	zSTRING filename(lpszPathName);
	filename.Lower();

	bool workingDlgOpened = false;
	if (!workingDlg)
	{
		workingDlg = new spcCWorkInfoDlg();
		workingDlg->Init();
		workingDlgOpened = true;
	}	

	if (filename.Search(".3ds")>0)
	{
		workingDlg->AddMessage("Loading 3DS-File "+CString(lpszPathName));
		LoadFile(lpszPathName,LOAD_3DS);
	}
	else if (filename.Search(".zen")>0)
	{
		workingDlg->AddMessage("Loading ZEN-File "+CString(lpszPathName));
		LoadFile(lpszPathName,LOAD_ZEN);

		zCWorld* world = GetWorld();
		
		if ( NULL == world ) return FALSE;

		if ( !world->IsCompiled() )
		{
			CSpacerView::view->OnWorldCompile();		
		}
	}

	::g_strWorldFileName = lpszPathName;
	
	// [EDENFELD] ausgeklammert Spacer 1.33 aus ModSource
	/*
	if (workingDlgOpened)
	{
		workingDlg->CloseWindow();
		workingDlg->DestroyWindow();
		workingDlg = 0;		
		AfxGetMainWnd()->SetFocus();
	};*/

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLOSING //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CSpacerDoc::OnCloseDocument() 
{
//	Reset();
	
	CDocument::OnCloseDocument();
}

static bool CB_DetectCollision(zCVob* vob, CSpacerDoc* pDoc)
{	

	if (vob->GetCollDetStat() &&
		vob->DetectCollision()) 
	{
		if (CMainFrame::mainframe) CMainFrame::mainframe->GetVobListWindow()->CDaddVob(vob);
		return false;
	}
	return true;
}
static bool CB_ViewInvisibleVobs(zCVob* vob, CSpacerDoc* pDoc)
{		
	if (!vob->GetVisual())
		return true;				
	if (!vob->GetShowVisual() && !pDoc->modeViewHelperVobs)
		return true;
	if (vob->GetShowVisual() && pDoc->modeViewHelperVobs)
		return true;

	zSTRING visualName = vob->GetVisual()->GetVisualName();
	visualName.Upper();
	if ( 
			dynamic_cast<zCVobLight*>			(vob)	||
			dynamic_cast<zCZone*>				(vob)	||
			dynamic_cast<zCVobSpot*>			(vob)	||
			dynamic_cast<zCVobStartpoint*>		(vob)	||
			dynamic_cast<zCVobWaypoint*>		(vob)	||
			dynamic_cast<zCCSCamera*>			(vob)	||
			dynamic_cast<zCCamTrj_KeyFrame*>	(vob)	||
			dynamic_cast<zCVobScreenFX*>		(vob)	||		
			(visualName.Search(INVISIBLE_FILEPREFIX)>=0)||
			(visualName.Search("VOBBOX")>=0)			
		)
		{			
			vob->SetShowVisual(pDoc->modeViewHelperVobs);
		};

	return true;
}


static bool CB_HandleVobsAfterLoad(zCVob* vob, CSpacerDoc* pDoc)
{		
	if (!vob) return true;

	//
	// Check auf gueltigen Visualnamen
	//

	// Levelkomponente
	if (dynamic_cast<zCVobLevelCompo*>(vob))
	{
		zSTRING visualName;
		if (vob->GetVisual()) visualName = vob->GetVisual()->GetVisualName();	
		
		if (visualName.IsEmpty() || visualName[0]=='#')
		{						
			AfxMessageBox("The level-component has no visual. Choose one ...");
			zoptions->ChangeDir(DIR_MESHES);				
			zFILE::DirectFileAccess(true);
				CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"All Files (*.*)|*.*||");						
				dlg.m_ofn.lpstrInitialDir = zoptions->GetDirString(DIR_MESHES).ToChar();
				int result = dlg.DoModal();
			zFILE::DirectFileAccess(false);
			if (result == IDOK)	
			{
				CString visualName = dlg.GetFileName();				
				vob->SetVisual(zSTRING(visualName.GetBuffer(0)));								
			}
		}				
	}

	if (dynamic_cast<zCVobWaypoint*>(vob))
	{
		zTBBox3D BBox;
		BBox.mins = zVEC3(-100,-100,-100);
		BBox.maxs = zVEC3(+100,+100,+100);
		BBox.Translate(vob->GetPositionWorld());
		vob->SetBBox3DWorld(BBox);
	}

	//
	// NPC auf simple AI schalten
	//
	
	#ifdef COMPILING_GOTHIC		
		if (dynamic_cast<oCNpc*>(vob)) 
		{
			dynamic_cast<oCNpc*>(vob)->UseStandAI();	
			dynamic_cast<oCNpc*>(vob)->SetPhysicsEnabled(TRUE);
		}
	#endif
	
	//
	// Weiter spezielle Vobs bearbeiten
	//
	
	if (dynamic_cast<zCCSCamera*>		(vob))	dynamic_cast<zCCSCamera*>(vob)->SetDrawEnabled(TRUE);
	if (dynamic_cast<zCPFXControler*>	(vob))	vob->SetVisual(0);
	

	//
	// Trigger (ausser Mover) und Zones duerfen kein Visual haben 
	// -> die Boundingbox ist sonst nicht editierbar
	//
	
	if (
			(
				dynamic_cast<zCMover*>			(vob) 
			)
			||
			(
				!dynamic_cast<zCTrigger*>		(vob) &&	// Boundingbox eines Triggers muss bearbeitet werden
				!dynamic_cast<zCZone*>			(vob) &&	// Boundingbox einer Zone muss bearbeitet werden				
				!dynamic_cast<zCTouchDamage*>	(vob) &&	// Boundingbox einer TouchDamage muss bearbeitet werden				
				// !dynamic_cast<zCMessageFilter*>	(vob) &&
				!dynamic_cast<zCVobLensFlare*>	(vob) 
			)
		)
	{
		// Checke, ob ein Mesh existiert
		if (!vob->GetVisual())
		{			
			zERR_MESSAGE(9,0,"B: SPCDOC: Assigning visual to a "+vob->GetClassDef()->GetClassName_());
			vob->zCVob::SetVisual(INVISIBLE_FILEPREFIX+vob->GetClassDef()->GetClassName_()+".3ds" );							
		}
		// Vergebe Standard-Mesh "_intern/invsible_vobbox.3ds"
		if (!vob->GetVisual()) 
		{
			zERR_MESSAGE(9,0,"B: SPCDOC: Assigning default-visual to a "+vob->GetClassDef()->GetClassName_());
			vob->zCVob::SetVisual( INVISIBLE_FILEPREFIX+"vobbox.3ds" );
		}
	}
	else
	{
		vob->SetVisual(0);
	};
	
	//
	// Entscheide, ob das Hilfsmesh auch sichtbar sein soll
	//
	
	CB_ViewInvisibleVobs(vob,pDoc);

	return true;
}


static bool CB_HandleVobsBeforeSave(zCVob* vob, CSpacerDoc* pDoc)
{		
	if (!vob)				return true;		
	if (!vob->GetVisual()) return true;

	zERR_MESSAGE(9,0,"B: SPC: Handle Vob before Save: "+vob->GetClassName_()+":"+vob->GetVobName());

	zSTRING visualName = vob->GetVisual()->GetVisualName();
	visualName.Upper();
	if ( 
			dynamic_cast< zCVobLight*		>	(vob)		||
			dynamic_cast< zCZone*			>	(vob)		||
			dynamic_cast< zCVobSpot*		>	(vob)		||
			dynamic_cast< zCVobStartpoint*	>	(vob)		||
			dynamic_cast< zCVobWaypoint*	>	(vob)		||
			dynamic_cast< zCCSCamera*		>	(vob)		||
			dynamic_cast< zCCamTrj_KeyFrame*>	(vob)		||
			dynamic_cast< zCVobScreenFX*	>	(vob)		||	
			dynamic_cast< zCPFXControler*	>	(vob)		||
			(visualName.Search(INVISIBLE_FILEPREFIX)>=0)	||
			(visualName.Search("VOBBOX")>=0)				
		)
	{
		zERR_MESSAGE		(9,0,"B: SPCDOC: Removing visual of a "+vob->GetClassDef()->GetClassName_());
		vob->SetVisual		(0);
		vob->SetShowVisual	(FALSE);
	};

	// 
	// Goldmaster?
	//

	if (spcConfig.goldmastering)
	{
		if (vob->GetClassDef()==zCVob::GetStaticClassDef())
		{
			vob->SetObjectName("");
		};
	};
	
	return true;
}

bool CSpacerDoc::VobDetectCollision(zCVob * vob)
{		
	if (CMainFrame::mainframe) CMainFrame::mainframe->GetVobListWindow()->CDremoveTree();	
	
	return HandleVob(T_HANDLEVOB_CALLBACK(CB_DetectCollision));		
}
bool CSpacerDoc::HandleVob (T_HANDLEVOB_CALLBACK callback, zCTree<zCVob>* vobNode)
{
	if (!GetWorld()) return false;
	
	// gesamten vobtree?
	if (!vobNode) vobNode = &(GetWorld()->globalVobTree);

	// callback aufrufen
	zCVob* vob	= vobNode->GetData();
	if (vob) callback(vob, this);
		
	// childs bearbeiten
	zCTree<zCVob>* child = vobNode->GetFirstChild();
	while (child) 
	{
		HandleVob (callback, child);		
		child	= child->GetNextChild();
	};
	return true;
};


void CSpacerDoc::OnViewInvisibleVobs() 
{
	modeViewHelperVobs = !modeViewHelperVobs;
	VobViewInvisible();
}

void CSpacerDoc::OnUpdateViewInvisibleVobs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable		(IsAWorldLoaded());
	pCmdUI->SetCheck	(IsAWorldLoaded() && modeViewHelperVobs);		
}

void CSpacerDoc::LoadFile(CString filename, zLOAD_TYPE load_type)
{	
	if (filename == "")		return;		
	if (!GetWorld(TRUE))	return;

	//::SetCursor(spcConfig.MouseWait);

	Reset();

	// Kompletten Pfad der Datei ermitteln
	zSTRING		zfilename(filename);
	{
		zFILE*		file = zfactory->CreateZFile(zfilename);	
		zfilename = file->GetFullPath();
		zfilename.Upper();
		delete file;file = 0;
	}

	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Loading ZEN: "+zSTRING(filename.GetBuffer(0)));
	
	// [EDENFELD] 1.33 Änderungen aus ModSource
	spcCViewProgressBar* progressBar = 0;
	if (load_type != LOAD_3DS)
	{
		progressBar = new spcCViewProgressBar(0,0,0,0);
		progressBar->Init(AfxGetMainWnd());
		GetWorld(TRUE)->SetProgressBar(progressBar);
	}
	
	bool winDisabled = true;
	if (CMainFrame::mainframe) 
	{		
		winDisabled = CMainFrame::mainframe->DeactivateApplicationWindows();		
	}
	// [EDENFELD] 1.33 bis hier
	
	zERR_MESSAGE(4,0,"B: SPC: Start loading from file ...");
	switch (load_type)
	{
		case LOAD_3DS:
			zoptions->ChangeDir(DIR_MESHES);
			GetWorld(TRUE)->LoadWorld(zfilename, zCWorld::zWLD_LOAD_EDITOR_UNCOMPILED);
			break;
		case LOAD_ZEN:
			zoptions->ChangeDir(DIR_WORLD);
			GetWorld(TRUE)->LoadWorld(zfilename, zCWorld::zWLD_LOAD_EDITOR_COMPILED);			
			break;
		case LOAD_ZEN_UC:
			zoptions->ChangeDir(DIR_WORLD);
			GetWorld(TRUE)->LoadWorld(zfilename, zCWorld::zWLD_LOAD_EDITOR_UNCOMPILED);
			// Sofort compilieren:			
			break;
	}	
	zERR_MESSAGE(4,0,"B: SPC: ... finished");
	
	if (CMainFrame::mainframe) CMainFrame::mainframe->GetInfoBar()->SetActiveWorld(GetWorld(TRUE));
	
	zERR_MESSAGE(4,0,"B: SPC: Handling all vobs after load.");
	HandleWorldAfterLoad();
	zERR_MESSAGE(4,0,"B: SPC: ... finished");	
	
	GetWorld(TRUE)->SetProgressBar(0);
	delete progressBar;progressBar=0;
	
	UpdateWindowTitle();
	AfxGetApp()->AddToRecentFileList(filename);
				
	SetDirty(false);	

	zERR_MESSAGE(4,0,"B: SPC: Updating window-contents");

	// [EDENFELD] 1.33 aus ModSource: Reaktiviere das Window
	if (CMainFrame::mainframe && winDisabled) 
	{
		CMainFrame::mainframe->ReactivateApplicationWindows();		
	}	
		
	CSpacerView::view->InitViewport(TRUE);	

	if (CMainFrame::mainframe) 
	{		
		CMainFrame::mainframe->UpdateWindowContents( GetWorld(TRUE) );
	}

	::SetCursor(spcConfig.MouseArrow);
	
	zERR_MESSAGE(4,zERR_END,"B: SPC: Load-File finished");		
};


// [EDENFELD] 1.33 neu aus ModSource: Details... aber unkritisch 
void CSpacerDoc::SaveFile(CString filename, zSAVE_TYPE save_type)
{				
	// Plausibilitaets-Checks
	if (!GetWorld()) return;
	if (filename=="" || !IsAWorldLoaded()) return;	

	if (!GetWorld()->IsCompiled())
	{
		if ( (save_type == SAVE_ZEN) || (save_type == SAVE_ZEN_BIN))
		{
			zERR_WARNING("B: SPC: You can't save the file with compiled data: It is not compiled!");			
			return;
		}
	}
	if (GetWorld()->IsCompiledEditorMode())
	{
		if ( (save_type != SAVE_3DS))
		{
			zERR_WARNING("B: SPC: You can't save a ZEN-file if the level is compiled in editor-mode!");
			return;
		}
	};		


	zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Saving ZEN: "+zSTRING(filename.GetBuffer(0)));

	// Warte-Mauscursor
	::SetCursor(spcConfig.MouseWait);	

	// 
	// Vor dem Speichern
	//
	bool winDisabled = true;
	if (CMainFrame::mainframe) 
	{		
		CMainFrame::mainframe->GetObjectWindow()->StopEditBoundingBox();			
		winDisabled = CMainFrame::mainframe->DeactivateApplicationWindows();
	}

	zERR_MESSAGE(4,0,"B: SPC: Handle all vobs before saving the level");
	HandleWorldBeforeSave();
	zERR_MESSAGE(4,0,"B: SPC: ... finished");		
	
	//
	// goldmastering?
	//
	zSTRING s = zSTRING(filename.GetBuffer(0));
	zFILE_FILE filepath(s);	
	if (spcConfig.goldmastering) 
	{
		zERR_MESSAGE(4,0,"B: SPC: GOLDMASTERING!!!");
		if (filepath.GetFilename().Search("GM_")<0)	filepath.SetFilename("gm_"+filepath.GetFilename()); 
	}	

	bool workingDlgOpened = false;
	if (!workingDlg)
	{
		workingDlg = new spcCWorkInfoDlg();
		workingDlg->Init();
		workingDlgOpened = true;
	}		

	/*
	spcCViewProgressBar* progressBar = 0;
	if (save_type != SAVE_3DS)
	{
		progressBar = new spcCViewProgressBar(0,0,0,0);
		progressBar->Init(AfxGetMainWnd());
		GetWorld(TRUE)->SetProgressBar(progressBar);
	}
	*/

	//
	// Saving
	//
	if (workingDlg) 
	{
		workingDlg->AddMessage(" Saving world");
		workingDlg->AddMessage(" -> "+filename);
	}
	zERR_MESSAGE(4,0,"B: SPC: Start saving to file, savetype = "+zSTRING(save_type));
	switch (save_type)
	{
		case SAVE_3DS:	
			if (workingDlg) workingDlg->AddMessage(" - mesh only");
			if (workingDlg) workingDlg->AddMessage(" saving ...");
			GetWorld()->SaveBspTreeMesh3DS(filepath.GetFullPath());
			break;		
		case SAVE_ZEN:
			if (workingDlg) workingDlg->AddMessage(" - compiled zen (ascii) ...");
			if (workingDlg) workingDlg->AddMessage(" saving ...");

			// [EDENFELD] 1.33c: Kein Mesh hier mit abspeichern
			session->SaveWorld(filepath.GetFullPath(), zCWorld::zWLD_SAVE_EDITOR_COMPILED,false,false); // mesh, ascii
			SetDirty(false);
			break;
		case SAVE_ZEN_UC:		
			if (workingDlg) workingDlg->AddMessage(" - uncompiled zen (ascii)");
			if (workingDlg) workingDlg->AddMessage(" saving ...");
			// [EDENFELD] 1.33c: Kein Mesh hier mit abspeichern
			session->SaveWorld(filepath.GetFullPath(), zCWorld::zWLD_SAVE_EDITOR_UNCOMPILED,false,false); // mesh, ascii
			SetDirty(false);
			break;		
		case SAVE_ZEN_BIN :					
			if (workingDlg) workingDlg->AddMessage(" - compiled zen (binary save)");
			if (workingDlg) workingDlg->AddMessage(" saving ...");
			session->SaveWorld(filepath.GetFullPath(),zCWorld::zWLD_SAVE_EDITOR_COMPILED,false,true); // noMesh, Binary
			SetDirty(false);
			break;
	}			

	/*
	GetWorld(TRUE)->SetProgressBar(0);
	delete progressBar;progressBar=0;
	*/

	if (workingDlgOpened)
	{
		workingDlg->CloseWindow();
		workingDlg->DestroyWindow();
		workingDlg = 0;		
		AfxGetMainWnd()->SetFocus();
	};	

	zERR_MESSAGE(4,0,"B: SPC: ... finished");

	// Alle Vobs nach dem Speichern bearbeiten
	zERR_MESSAGE(4,0,"B: SPC: Handle all vobs after saving the level");
	HandleWorldAfterSave();
	zERR_MESSAGE(4,0,"B: SPC: ... finished");
	
	zERR_MESSAGE(4,zERR_END,"B: SPC: Saving finished");

	// Setze Fenstertitel und fuege Dateiname in RecentFilelist ein
	UpdateWindowTitle();
	AfxGetApp()->AddToRecentFileList(filename);
	
	// WorkingDialog schliessen
	if (CMainFrame::mainframe && winDisabled)
	{		
		CMainFrame::mainframe->ReactivateApplicationWindows();		
	};

	// normaler Mauscursor
	::SetCursor(spcConfig.MouseArrow);
}


void CSpacerDoc::OnWorldDifscript() 
{
	zoptions->ChangeDir(DIR_SCRIPTS);	
	zFILE::DirectFileAccess(true);
		CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"Parser-Files (*.src, *.dat)|*.src;*.dat|All Files (*.*)|*.*||");	
		zSTRING s = zoptions->GetDirString(DIR_SCRIPTS);
		dlg.m_ofn.lpstrInitialDir = s.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)	
	{
		CString name = dlg.GetPathName();
		ParseScript(name);
		// CMainFrame::mainframe->UpdateOUList();
		if (CMainFrame::mainframe) CMainFrame::mainframe->UpdateWindowContents(GetWorld());
	}
}

void CSpacerDoc::OnUpdateFileOpenmakefile(CCmdUI* pCmdUI) 
{
	// TODO: Code 
	
}

bool CSpacerDoc::IsAWorldLoaded()
{
	zCWorld* world = GetWorld(TRUE);	
	return (world && world->globalVobTree.GetFirstChild()!=0);
}

zCWorld* CSpacerDoc::GetWorld(zBOOL getEmptyWorldToo)
{
	if (!session)				return 0;	
	if (!CMainFrame::mainframe) return 0;
	if (!CSpacerView::view)		return 0;	
	
	zCWorld* world = (zCWorld*)(session->GetWorld());	

	if (getEmptyWorldToo || world->globalVobTree.GetFirstChild()!=0) return world;	

	return 0;
}

void CSpacerDoc::Reset()
{			
	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/	

	if (IsAWorldLoaded())
	{
		if (CMainFrame::mainframe) CMainFrame::mainframe->GetObjectWindow()->StopEditBoundingBox();

		zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Reset");				
		
		zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Reset. Mainframe ...");		
		if (CMainFrame::mainframe) CMainFrame::mainframe->Reset();
		zERR_MESSAGE(4,zERR_END,"");

		zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Reset. View ...");		
		if (CSpacerView::view) CSpacerView::view->Reset();	
		zERR_MESSAGE(4,zERR_END,"");

		zERR_MESSAGE(4,zERR_BEGIN,"B: SPC: Reset. Deselecting vobs ...");		
		if (GetWorld()) GetWorld()->DisposeWorld();		
		SetDirty(false);		
		zERR_MESSAGE(4,zERR_END,"");
		
		zERR_MESSAGE(4,zERR_END,"B: SPC: Reset finished");

	};
	/**** CHECK MEMORY *****/
	ASSERT(AfxCheckMemory());
	/**** CHECK MEMORY *****/

	if (CSpacerView::view) CSpacerView::view->RedrawWindow(0,0,RDW_INVALIDATE);

	// [EDENFELD] 1.33: Nullptr Crash abgefangen
	if (CMainFrame::mainframe && CMainFrame::mainframe->GetInfoBar())
	{
		CMainFrame::mainframe->GetInfoBar()->SetActiveWorld(0);
		CMainFrame::mainframe->GetInfoBar()->SetSelectedObject(0);
		//CMainFrame::mainframe->ObjectSelection(0,0,true);
	};
	
};

void CSpacerDoc::OnFileOpenmakefile() 
{
	/*
	zoptions->ChangeDir(DIR_WORLD);

	CString filter = "ZenGinMakeFile (*.zmf)|*.zmf|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE,"zmf","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);
	
	zFILE::DirectFileAccess(true);
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{			
		CString filepath;
		CString filename = dlg.GetPathName();		
		filename.MakeLower();
		
		zSTRING mergeFile;
		zFILE* makefile = zfactory->CreateZFile(zSTRING(filename.GetBuffer(0)));		
		makefile->Open();

		if (makefile->Eof())
		{
			zERR_WARNING("A: No entry in makefile!");			
			makefile->Close();
			delete makefile;
			return;
		}			

		// merge next files		
		while (!makefile->Eof()) 
		{						
			makefile->Read(mergeFile);
			mergeFile.Upper();
			if ((mergeFile.Search("ZEN")>0) || (mergeFile.Search("3DS")>0))
			{
				if (!IsAWorldLoaded())
				{
					zERR_MESSAGE(3,0,"B: SPC: Open file \""+mergeFile+"\"");					
					LoadFile(mergeFile.ToChar(), LOAD_ZEN_UC);
				}
				else if (mergeFile.Search("ZEN")>0)
				{
					zERR_MESSAGE(3,0,"B: SPC: Merging file \""+mergeFile+"\"");		
					GetWorld()->MergeVobSubtree(mergeFile);
					SetDirty();
				}
				else if (mergeFile.Search("3DS")>0)
				{
					zERR_MESSAGE(3,0,"B: SPC: Merging file \""+mergeFile+"\"");		
					GetWorld()->LoadWorld(mergeFile, zCWorld::zWLD_LOAD_EDITOR_UNCOMPILED);
					SetDirty();
				}
			}
		}
		makefile->Close();
		delete makefile;
		zERR_MESSAGE(3,0,"B: SPC: Ready");

		CString WinText(filename);
		WinText = WinText + " - " + CString(SPC_APPLICATION_NAME) + " " + CString(SPC_VERSION);
		AfxGetMainWnd()->SetWindowText(WinText);		
		
		VobHandleAfterLoad();		
		
		CMainFrame::mainframe->UpdateWindowContents(GetWorld());		

		current_filename = "";

		zERR_MESSAGE(3,0,"B: SPC: Ready loading file");
	};	
	*/
}

// [EDENFELD] 1.33 neu aus ModSource
void CSpacerDoc::OnFileOpen() 
{	
	zoptions->ChangeDir(DIR_WORLD);		
	
	if (IsDirty())
	{		
		int answer = AfxMessageBox("The World has changed.\r\nDo you want to save it?",MB_ICONQUESTION | MB_YESNOCANCEL | MB_TOPMOST);		
		switch (answer)
		{
		case IDYES:		OnFileSaveZen();	break;
		case IDCANCEL:	return;			break;
		};
	};
		

	CString filter = 
		"World compiled (*.zen)|*.zen|"
		"World uncompiled (*.zen)|*.zen||";

	
	zFILE::DirectFileAccess(true);
		zSTRING filepathStr;
		filepathStr = zoptions->ReadString("spacer","spcZenFilePath");
		CFileDialog dlg(TRUE,"zen","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);	
		dlg.m_ofn.lpstrInitialDir = filepathStr.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);	
	
	if (result == IDOK)	
	{			
		CString filepath = dlg.GetPathName();
		filepath.MakeLower();		
		zFILE_FILE path(filepath.GetBuffer(0));
		
		current_filename = path.GetFile().ToChar();
		::g_strWorldFileName = current_filename;

		path.SetFile("");
		zoptions->WriteString("spacer","spcZenFilePath",path.GetFullPath());
		zERR_MESSAGE(6,0,"B: SPC: default-zenpath is "+path.GetFullPath());
		// zoptions->Save("spcOptions.ini");

		/*
		bool workingDlgOpened = false;
		if (!workingDlg)
		{
			workingDlg = new spcCWorkInfoDlg();
			workingDlg->Init();
			workingDlgOpened = true;
		}
		*/

		filepath.MakeLower();

		if (workingDlg) workingDlg->AddMessage(" Loading ZEN-File");

		// if the 2. filter is selected the user wants to load uncompiled
		switch (dlg.m_ofn.nFilterIndex)
		{
			case 1 : LoadFile(filepath, LOAD_ZEN);break;				
			case 2 : LoadFile(filepath, LOAD_ZEN_UC);break;
			default: AfxMessageBox("Selected format is unknown.");break;
			
		};			

		/*
		if (workingDlgOpened)
		{
			workingDlg->CloseWindow();
			workingDlg->DestroyWindow();
			workingDlg = 0;			
			AfxGetMainWnd()->SetFocus();			
		};
		*/

		zCWorld* world = GetWorld();
		if (world && !world->IsCompiled() )
		{
			CSpacerView::view->OnWorldCompile();		
		}
	};	
}



void CSpacerDoc::OnFileOpenmesh() 
{
	zoptions->ChangeDir(DIR_MESHES);
			
	CString filter = "Mesh-File (*.3ds)|*.3ds|All Files(*.*)|*.*||";

	zFILE::DirectFileAccess(true);
		CFileDialog dlg(TRUE,"3ds","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);	
		zSTRING filepathStr;
		filepathStr = zoptions->ReadString("spacer","spcMeshFilePath");
		dlg.m_ofn.lpstrInitialDir=filepathStr.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);	
	
	if (result == IDOK)	
	{
		CString filepath = dlg.GetPathName();
		filepath.MakeLower();		
		zFILE_FILE path(filepath.GetBuffer(0));

		current_filename = path.GetFile().ToChar();

		path.SetFile("");
		zoptions->WriteString("spacer","spcMeshFilePath",path.GetFullPath());
		zERR_MESSAGE(6,0,"B: SPC: default-meshpath is "+path.GetFullPath());
		// zoptions->Save("spcOptions.ini");

		bool workingDlgOpened = false;
		if (!workingDlg)
		{
			workingDlg = new spcCWorkInfoDlg();
			workingDlg->Init();
			workingDlgOpened = true;
		}
		workingDlg->AddMessage("Loading Mesh "+filepath);


		// if the 2. filter is selected the user wants to load uncompiled
		if (dlg.m_ofn.nFilterIndex==1) loadCompiled=true; else loadCompiled=false;		
		
		filepath.MakeLower();
		LoadFile(filepath,LOAD_3DS);	

		if (workingDlgOpened)
		{
			workingDlg->CloseWindow();
			workingDlg->DestroyWindow();
			workingDlg = 0;			
			AfxGetMainWnd()->SetFocus();
		};		
	};	
}

// [EDENFELD] 1.33 neu aus ModSource.
void CSpacerDoc::OnFileMerge() 
{
	if (!IsAWorldLoaded()) return;

	zoptions->ChangeDir(DIR_WORLD);

	CString filter = "World (*.Zen)|*.zen|All Files(*.*)|*.*||";

	zFILE::DirectFileAccess(true);
		zSTRING filepathStr;
		filepathStr = zoptions->ReadString("spacer","spcMeshFilePath");		
		CFileDialog dlg(TRUE,"zen","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);	
		dlg.m_ofn.lpstrInitialDir=filepathStr.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{		
		CString filepath = dlg.GetPathName();
		filepath.MakeLower();		
		zFILE_FILE path(filepath.GetBuffer(0));
		path.SetFile("");
		zoptions->WriteString("spacer","spcZenFilePath",path.GetFullPath());
		zERR_MESSAGE(6,0,"B: SPC: default-zenpath is "+path.GetFullPath());
		// zoptions->Save("spcOptions.ini");

		CString filename = dlg.GetFileName();		
		CString fileExt = dlg.GetFileExt();
		
		filepath.MakeLower();
		filename.MakeLower();
		fileExt.MakeLower();

		if (fileExt!="zen") { AfxMessageBox("Wrong file-type: "+fileExt); return; }

		bool workingDlgOpened = false;
		if (!workingDlg)
		{
			workingDlg = new spcCWorkInfoDlg();
			workingDlg->Init();
			workingDlgOpened = true;
		}
		workingDlg->AddMessage(" Merging ZEN-File "+filename);

		bool winDisabled = true;
		if (CMainFrame::mainframe) 
		{		
			winDisabled = CMainFrame::mainframe->DeactivateApplicationWindows();		
		}

		// merge file
		zERR_MESSAGE(2,0,"B: SPC: Merging file \""+zSTRING(filename.GetBuffer(0))+"\"");
				
		GetWorld()->MergeVobSubtree(zSTRING(filepath.GetBuffer(0)));
		SetDirty();
		
		zERR_MESSAGE(3,0,"B: SPC: Ready");
		
		VobHandleAfterLoad();		

		if (CMainFrame::mainframe && winDisabled) 
		{		
			CMainFrame::mainframe->ReactivateApplicationWindows();		
		}

		if (workingDlgOpened)
		{
			workingDlg->CloseWindow();
			workingDlg->DestroyWindow();
			workingDlg = 0;			
			AfxGetMainWnd()->SetFocus();
		};
		
		CMainFrame::mainframe->UpdateWindowContents(GetWorld());		

		if (GetWorld())
		{
			zCWayNet* waynet = GetWorld()->GetWayNet();
			if (waynet)
			{
				zSTRING result = waynet->MergeWaypoints();
				if (!result.IsEmpty())
				{
					AfxMessageBox(zSTRING(zSTRING("Merged the following waypoints: \r\n")+result).ToChar(),MB_OK |  MB_TOPMOST);
				};
			};
		}

	};		
}


void CSpacerDoc::OnFileMergemesh() 
{
	if (!IsAWorldLoaded()) return;

	zoptions->ChangeDir(DIR_MESHES);

	CString filter = "Mesh-File (*.3ds)|*.3ds|All Files(*.*)|*.*||";
	zFILE::DirectFileAccess(true);
		zSTRING filepathStr;
		filepathStr = zoptions->ReadString("spacer","spcMeshFilePath");
		CFileDialog dlg(TRUE,"3ds","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);	
		dlg.m_ofn.lpstrInitialDir=filepathStr.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{		
		CString filepath = dlg.GetPathName();
		filepath.MakeLower();		
		zFILE_FILE path(filepath.GetBuffer(0));
		path.SetFile("");
		zoptions->WriteString("spacer","spcMeshFilePath",path.GetFullPath());
		zERR_MESSAGE(6,0,"B: SPC: default-meshpath is "+path.GetFullPath());
		// zoptions->Save("spcOptions.ini");

		CString filename = dlg.GetFileName();		
		CString fileExt = dlg.GetFileExt();
		
		filepath.MakeLower();
		filename.MakeLower();
		fileExt.MakeLower();

		if (fileExt!="3ds") { AfxMessageBox("Wrong file-type: "+fileExt); return; }

		// merge file
		zERR_MESSAGE(2,0,"B: SPC: Merging file \""+zSTRING(filename.GetBuffer(0))+"\"");

		bool workingDlgOpened = false;
		if (!workingDlg)
		{
			workingDlg = new spcCWorkInfoDlg();
			workingDlg->Init();
			workingDlgOpened = true;
		}
		workingDlg->AddMessage("Merging mesh "+filepath);

		// GetWorld()->MergeVobSubtree(zSTRING(filepath.GetBuffer(0)));
		GetWorld()->LoadWorld(zSTRING(filepath.GetBuffer(0)), zCWorld::zWLD_LOAD_EDITOR_UNCOMPILED);
		
		zERR_MESSAGE(3,0,"B: SPC: Ready");		

		VobHandleAfterLoad();
		
		CMainFrame::mainframe->UpdateWindowContents(GetWorld());		

		if (workingDlgOpened)
		{
			workingDlg->CloseWindow();
			workingDlg->DestroyWindow();
			workingDlg = 0;
			AfxGetMainWnd()->SetFocus();
		};
	};	
}

void CSpacerDoc::OnUpdateFileMergemesh(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsAWorldLoaded() && GetWorld() && !GetWorld()->IsCompiled());
}

void CSpacerDoc::OnUpdateFileMerge(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsAWorldLoaded() && GetWorld() && !GetWorld()->IsCompiled());	
}

void CSpacerDoc::OnFileNew() 
{
	if (IsDirty())
	{		
		int answer = AfxMessageBox("The World has changed.\r\nDo you want to save it?",MB_ICONQUESTION | MB_YESNOCANCEL);
		if (answer == IDYES) OnFileSaveZen();		
		if (answer == IDCANCEL) return;
	};

	Reset();	
}

// [EDENFELD] neu 1.33 aus ModSource
CString CSpacerDoc::UpdateWindowTitle()
{
	CString s;	
	if (spcConfig.goldmastering) s+=" [GM] ";	
	s += CString(SPC_APPLICATION_NAME) + " - " + CString(SPC_VERSION);
	s += " : ";
	s += current_filename;	
	if (IsDirty()) s += "*";
	
	AfxGetMainWnd()->SetWindowText(s);
	return s;
};

void CSpacerDoc::OnFileSaveZen() 
{
	if (!IsAWorldLoaded()) return;
	/*
	if (GetWorld()->IsCompiledEditorMode())
	{
		AfxMessageBox("The World is compiled in editor mode.\r\nYou can only save the mesh!");
		return;
	};
	*/

	zoptions->ChangeDir(DIR_WORLD);	

	// Lege verfuegbare Formate fest:	
	static int	lastFilterIndex = 3;		// standard ist "compiled zen (ascii)"
	int			maxFilterIndex = 1;
	
	CString filter = "Uncompiled ZEN (ascii)|*.zen|";	
	if (GetWorld()->IsCompiled() && !GetWorld()->IsCompiledEditorMode())
	{
		filter = filter + "Compiled ZEN (binary safe)|*.zen|";
		filter = filter + "Compiled ZEN (ascii)|*.zen|";		
		maxFilterIndex = 3;
	};
	filter = filter + "|";
	
	//
	// Verzeichnis und Flags festlegen
	//	
	zSTRING filepathStr;
	int flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN;

	if (spcConfig.goldmastering) 
	{
		zFILE_FILE gmFile(zoptions->GetDirString(DIR_WORLD)+"goldmaster\\");
		gmFile.DirCreate();
		gmFile.ChangeDir();
		flags = flags | OFN_NOCHANGEDIR;
		filepathStr = gmFile.GetFullPath();
	}
	else
	{		
		filepathStr = zoptions->ReadString("spacer","spcZenFilePath");		
	};

	// 
	// Save-Dialog
	//
	zFILE::DirectFileAccess(true);		
		CFileDialog dlg(FALSE,"",GetNextFilename(current_filename,"zen") ,flags,filter);
		if (lastFilterIndex>maxFilterIndex) lastFilterIndex=1;
		dlg.m_ofn.nFilterIndex = lastFilterIndex;	
		dlg.m_ofn.lpstrInitialDir=filepathStr.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	//
	// Speichern starten
	//
	if (result == IDOK)
	{					
		lastFilterIndex = dlg.m_ofn.nFilterIndex;

		CString filepath = dlg.GetPathName();
		filepath.MakeLower();		
		zFILE_FILE path(filepath.GetBuffer(0));
	
		current_filename = path.GetFile().ToChar();

		path.SetFile("");
		if (!spcConfig.goldmastering)
		{
			zoptions->WriteString("spacer","spcZenFilePath",path.GetFullPath());
			zERR_MESSAGE(6,0,"B: SPC: default-zenpath is "+path.GetFullPath());
		}
		
		UpdateWindowTitle();
		AfxGetApp()->AddToRecentFileList(filepath);
	
		if (filepath.Find(".zen")<0) filepath = filepath + ".zen";				

		zERR_MESSAGE(3,0,"B: SPC: Saving file '"+filepath+"' with filterIndex "+zSTRING(lastFilterIndex));
		switch(lastFilterIndex)
		{
			case 1 : SaveFile(filepath, SAVE_ZEN_UC);				break;
			case 2 : SaveFile(filepath, SAVE_ZEN_BIN);				break;
			case 3 : SaveFile(filepath, SAVE_ZEN);					break;
			default: AfxMessageBox("Selected format is unknown.");	break;
		}							
	}		
}

void CSpacerDoc::OnUpdateFileSaveZen(CCmdUI* pCmdUI) 
{
	zCWorld* world = GetWorld();
	pCmdUI->Enable(IsAWorldLoaded() && world && world->IsCompiled() && !world->IsCompiledEditorMode());
}

// [EDENFELD] 1.33 neu aus ModSource
void CSpacerDoc::OnFileSaveMesh() 
{
	if (!IsAWorldLoaded()) return;
	if (!GetWorld()->IsCompiledEditorMode())
	{
		AfxMessageBox("That works only in EditorCompiledMode");
		return;
	}

	zoptions->ChangeDir(DIR_MESHES);
			
	CString filter = "Mesh 3DS|*.3DS||";		
	
	zFILE::DirectFileAccess(true);
		zSTRING filepathStr;
		filepathStr = zoptions->ReadString("spacer","spcMeshFilePath");
		CFileDialog dlg(FALSE,NULL,GetNextFilename(current_filename,"3ds"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,filter);			
		dlg.m_ofn.lpstrInitialDir=filepathStr.ToChar();
		int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)
	{							
		CString filepath = dlg.GetPathName();
		filepath.MakeLower();		
		zFILE_FILE path(filepath.GetBuffer(0));

		current_filename = path.GetFile().ToChar();

		path.SetFile("");
		zoptions->WriteString("spacer","spcMeshFilePath",path.GetFullPath());
		zERR_MESSAGE(6,0,"B: SPC: default-meshpath is "+path.GetFullPath());
		// zoptions->Save("spcOptions.ini");
		
		UpdateWindowTitle();
		AfxGetApp()->AddToRecentFileList(filepath);
		
		if (filepath.Find(".3ds")<0) filepath = filepath + ".3ds";

		bool workingDlgOpened = false;
		if (!workingDlg)
		{
			workingDlg = new spcCWorkInfoDlg();
			workingDlg->Init();
			workingDlgOpened = true;
		}
		workingDlg->AddMessage(" Saving Mesh "+filepath);

		SaveFile(filepath, SAVE_3DS);

		if (workingDlgOpened)
		{
			workingDlg->CloseWindow();
			workingDlg->DestroyWindow();
			workingDlg = 0;			
			AfxGetMainWnd()->SetFocus();
		};		
	}			
}

void CSpacerDoc::OnUpdateFileSaveMesh(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsAWorldLoaded());
}


void CSpacerDoc::SetDirty(bool set) 
{
	if (isDirty!=set)
	{		
		isDirty = set;				
		UpdateWindowTitle();
	};	
}

bool CSpacerDoc::IsDirty() 
{
	return (isDirty == true);
}


void CSpacerDoc::OnToolsInformations() 
{
	zSTRING inhalt;
	if (!GetWorld())
	{
		inhalt = "No Level is loaded";
	}	
	else
	{
		zCWorld* world = GetWorld();

		// world-stats
		inhalt += "World-Stats:\r\n";
		inhalt += "- number of vobs: "+zSTRING(world->globalVobTree.CountNodes())+"\r\n";
		inhalt += "- bsp-tree: ";
		zCMesh* mesh = world->GetBspTree() ? world->GetBspTree()->mesh : 0;
		if (!mesh) inhalt+="no ";
		else inhalt += zSTRING(mesh->numVert) +" verts, "+zSTRING(mesh->numPoly) +" polys";
		inhalt += "\r\n";
		
		// Render-Stats
		inhalt += "Render-Stats: \r\n";
		inhalt += "- vobFarClipZ: " + zSTRING(world->GetVobFarClipZ()) + "\r\n";
		inhalt += "- compiled: ";if (world->IsCompiled()) inhalt+="yes\r\n"; else inhalt+="no\r\n";
		if (world->IsCompiledEditorMode()) inhalt+="- editormode\r\n";
				
		// last render-action
		/*
		inhalt += "Last Renderaction: \r\n";
		inhalt += "- mode: "+zSTRING(world->GetWorldRenderMode())+ "\r\n";
		inhalt += "- rendered: "+zSTRING(world->s_polysRendered)+" polys, "+zSTRING(world->s_trisRendered)+" tris\r\n";		
		inhalt += "- verts transformed: "+zSTRING(world->s_vertsTransformed)+"\r\n";		
		*/
		
		// waynet
		inhalt += "Waynet: \r\n";
		if (!world->GetWayNet()) inhalt+="- none\r\n";
		else 
		{
			inhalt += "- "+zSTRING(world->GetWayNet()->GetNumberOfWays())+" ways\r\n";
			inhalt += "- "+zSTRING(world->GetWayNet()->GetNumberOfWaypoints())+" waypoints\r\n";			
		}

		world->PrintStatus();
	};

	spcCTextInfoDlg dlg;
	dlg.m_contents = CString(inhalt.ToChar());
	dlg.DoModal();
}

void CSpacerDoc::OnUpdateToolsInformations(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(IsAWorldLoaded());
	pCmdUI->Enable(TRUE);
}

void CSpacerDoc::OnQuickSave() 
{
	if (!IsAWorldLoaded()) return;

	zoptions->ChangeDir(DIR_WORLD);

	CString filepath = CString("~tmp.zen");	
	addToRecent=false;
	SaveFile(filepath, SAVE_ZEN);
	addToRecent=true;
}

void CSpacerDoc::OnQuickOpen() 
{
	zoptions->ChangeDir(DIR_WORLD);
	zFILE* f = zoptions->GetDir(DIR_WORLD);
	zSTRING str = f->GetFullPath();
	str = str+zSTRING("~tmp.zen");
	// die Kamera merken
	zMAT4 cMat = camera_vob->trafoObjToWorld;
	addToRecent=false;
	LoadFile(str.ToChar(),LOAD_ZEN);
	// die Kamera zurücksetzen
	camera_vob->SetTrafoObjToWorld(cMat);
	addToRecent=true;	
}

void CSpacerDoc::OnClose() 
{
	Reset();	
}

void CSpacerDoc::OnViewTogglevobboxes() 
{
	zCWorld* world = GetWorld();
	if (!world) return;
	world->SetDrawVobBBox3D (!world->GetDrawVobBBox3D());	
}

void CSpacerDoc::OnUpdateVieweditTogglevobboxes(CCmdUI* pCmdUI) 
{
	zCWorld* world = GetWorld();
	pCmdUI->Enable		(world && IsAWorldLoaded());
	pCmdUI->SetCheck	(world && world->GetDrawVobBBox3D());
}


bool CSpacerDoc::InsertVob(zCVob* vob, zPOINT3* pos, zPOINT3* dir, zCVob* parent)
{	
	if (!IsAWorldLoaded()) return false;
	if (!GetWorld()) return false;	
	
	zBOOL				phys	= vob->GetPhysicsEnabled();
	zTVobSleepingMode	mode	= vob->GetSleepingMode();

	// CollisionDetection ausschalten		
	vob->SetCollDetDyn(FALSE);
	vob->SetCollDetStat(FALSE);			
	
	parent = GetParentVob(parent);
	GetWorld()->AddVobAsChild(vob,parent);	
		
	if (dynamic_cast<zCTrigger*>(vob) || !dynamic_cast<zCZone*>(vob))
	{
		// Bei Zones (Sounds) und Triggern soll die Ausrichtung beim Einfuegen ignoriert werden
		// Dies ist vor allem ein Hack fuer den BBox-Bug.
		// Ausser fuer spezielle Sounds ist die Ausrichtung allerdings wirklich irrelevant.
		dir=0;
	};
	
	if (pos)
	{
		zBOOL cdDyn		= vob->GetCollDetDyn();
		zBOOL cdStat	= vob->GetCollDetStat();		

		vob->SetCollDetDyn(FALSE);
		vob->SetCollDetStat(FALSE);		

		vob->SetPositionWorld(*pos);
		if (dir) vob->SetHeadingWorld((*pos) + (*dir) * 200);
		
		vob->SetCollDetDyn(cdDyn);
		vob->SetCollDetStat(cdStat);
	}	

	vob->ResetXZRotationsWorld();	

	if (
		(vob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_PC) &&
		(vob->GetCharacterClass()!=zCVob::zVOB_CHAR_CLASS_NPC)
		)
	{
		vob->SetPhysicsEnabled(phys);
		vob->SetSleepingMode(mode);
	};	

	VobHandleAfterLoad(vob); // Mesh testen und evtl. Hilfsmesh zuweisen

	if (dynamic_cast<zCVobWaypoint*>(vob)) 
	{
		zCWayNet* waynet = GetWorld()->GetWayNet();
		if (waynet)
		{
			zCWaypoint* wp = zfactory->CreateWaypoint();
			wp->Init(dynamic_cast<zCVobWaypoint*>(vob));
			waynet->InsertWaypoint(wp);		
			waynet->CorrectHeight();
		}
	}	

	CMainFrame::mainframe->HandleVobInsert(vob,parent);		

	SetDirty();		

	return true;
};


bool CSpacerDoc::RemoveVob(zCVob* vob, zBOOL secure_ask)
{
	if (!IsAWorldLoaded()) return false;
	if (!GetWorld()) return false;
	
	CString ask;

	int result;

	if (vob==camera_vob) return false;

	// Abfragetext ermitteln
	if (dynamic_cast<zCVobLevelCompo*>(vob))
	{		
		ask = "ATTENTION! This is a level-component!\r\nDo you really want to delete it?";
		result = AfxMessageBox(ask,MB_YESNO);
		if (result==IDYES)
		{
			ask = "Hey, really?\r\nTHIS IS A LEVEL-COMPONENT!\r\nDo you wanna delete it?\r\nAre you sure?";
			result = AfxMessageBox(ask,MB_YESNO);
		};
	}
	else if (secure_ask)
	{
		zSTRING vobName;
		vobName = vob->GetVobName();
		if (vobName.IsEmpty()) vobName = vob->GetClassName_();
		ask = CString("Do you really want to remove\r\nthe item ")+CString(vobName.ToChar())+CString(" ?");
		result = AfxMessageBox(ask,MB_YESNO);
	}
	else result = IDYES;
	
	// Antwort auf die Abfragebox auswerten

	if (result!=IDYES) return false;	
	
	CMainFrame::mainframe->HandleVobRemove(vob);

	if (vob) vob->AddRef();

	zCVobWaypoint* wpvob = dynamic_cast<zCVobWaypoint*>(vob);						
	// Wegpunkt
	if (wpvob)
	{						
		zCWayNet* waynet	= GetWorld()->GetWayNet();			
		zCWaypoint* wp		= waynet->SearchWaypoint(wpvob);
		if (!wp) return false;
		waynet->DeleteWaypoint(wp);
	} 	
	else
	{	
		GetWorld()->RemoveVobSubtree(vob);
	}
	// vob=0;	

	SetDirty();

	zRELEASE(vob);
	return true;

};



void CSpacerDoc::WayToggleWay(zCVob * vob1, zCVob * vob2)
{
	if (!IsAWorldLoaded()) return;
	if (!dynamic_cast<zCVobWaypoint*>(vob1)) return;
	if (!dynamic_cast<zCVobWaypoint*>(vob2)) return;
	
	zCWorld* world = GetWorld();if (!world) return;
	zCWayNet* waynet = world->GetWayNet();if (!waynet) return;

	zCWaypoint* wp1 = waynet->SearchWaypoint(static_cast<zCVobWaypoint*>(vob1));
	zCWaypoint* wp2 = waynet->SearchWaypoint(static_cast<zCVobWaypoint*>(vob2));
	if (!wp1 || !wp2) return;	
	if (wp1==wp2) return;

	if (!waynet->HasWay(wp1,wp2)) 
	{
		waynet->CreateWay(wp1,wp2);
	}
	else
	{
		waynet->DeleteWay(wp1,wp2);	
	}

}

void CSpacerDoc::WayRemovePoint(zCVob* wpvob)
{
	if (!IsAWorldLoaded()) return;
	if (!dynamic_cast<zCVobWaypoint*>(wpvob)) return;

	zCWorld*	world	= GetWorld();			if (!world)		return;
	zCWayNet*	waynet	= world->GetWayNet();	if (!waynet)	return;
		
	zCWaypoint* wp = waynet->SearchWaypoint( static_cast<zCVobWaypoint*>(wpvob));
	if (!wp) return;

	waynet->DeleteWaypoint(wp);
}

void CSpacerDoc::WayMovePoint(zCVob * wpvob)
{
	if (!IsAWorldLoaded()) return;
	if (!dynamic_cast<zCVobWaypoint*>(wpvob)) return;

	zCWorld* world = GetWorld();if (!world) return;
	zCWayNet* waynet = world->GetWayNet();if (!waynet) return;
	
	zCWaypoint* wp = waynet->SearchWaypoint( static_cast<zCVobWaypoint*>(wpvob));
	// neue koordinaten des Wp
	if (wp) wp->UpdatePositionWorld();
}


zCVob* CSpacerDoc::GetParentVob(zCVob* candidate)
{
	if (candidate) return candidate;
	
	zCTree<zCVob>* tree = CSpacerDoc::doc->GetWorld()->globalVobTree.GetFirstChild();
	while (tree)
	{		
		if (tree->GetData() && tree->GetData()->GetVobType()==zVOB_TYPE_LEVEL_COMPONENT) 
		{
			return tree->GetData();
		}
		tree = tree->GetNextChild();
	}	
	return 0;
}

void CSpacerDoc::HandleWorldAfterLoad()
{
	VobHandleAfterLoad();
	VobTreeCorrection(CString("TRA_HE_POLY"));	// TreeCorrection (LevelVob wurde verschoben)	
	oCNpc::SetNpcAIDisabled(TRUE);
	dynamic_cast<oCGame*>(session)->GetSpawnManager()->SetSpawningEnabled(FALSE);
}

void CSpacerDoc::HandleWorldBeforeSave()
{
	if (CMainFrame::mainframe)	CMainFrame::mainframe	->PrepareForSave();	
	if (CSpacerView::view)		CSpacerView::view		->PolyHideSelection(TRUE);
	if (camera_vob && camera_vob->GetHomeWorld()) camera_vob->GetHomeWorld()->RemoveVob(camera_vob);

	VobHandleBeforeSave();
}

void CSpacerDoc::HandleWorldAfterSave()
{	
	VobHandleAfterSave();

	if (camera_vob)				GetWorld()->AddVob(camera_vob);	
	if (CSpacerView::view)		CSpacerView::view->PolyHideSelection(FALSE);	
	if (CMainFrame::mainframe)	CMainFrame::mainframe->AfterSave();
}

void CSpacerDoc::UserSelectVisual(zCVob *vob)
{
	zoptions->ChangeDir(DIR_MESHES);				
	zFILE::DirectFileAccess(true);
		CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,"All Files (*.*)|*.*||");
		zSTRING s = zoptions->GetDirString(DIR_MESHES);
		dlg.m_ofn.lpstrInitialDir=s.ToChar();
	int result = dlg.DoModal();
	zFILE::DirectFileAccess(false);

	if (result == IDOK)	
	{
		zSTRING filename = dlg.GetFileName().GetBuffer(0);
		if (!filename.IsEmpty()) vob->SetVisual(filename);
	}
}


void CSpacerDoc::OnWorldAnalyse() 
{
	if (!IsAWorldLoaded())	return;
	if (!GetWorld())		return;

	spcCWorldAnalyseDlg dlg;
	dlg.AnalyseWorld(GetWorld());
	dlg.DoModal();
}

void CSpacerDoc::OnUpdateWorldAnalyse(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsAWorldLoaded() && GetWorld());	
}

zPOINT3 CSpacerDoc::CalcLocalPosition(zCVob* parent, zPOINT3 pos)
{	
	if (parent)
	{
		zPOINT3 parentPos = parent->GetPositionWorld();
		pos = pos - parentPos;
	}
	return pos;
}


CString CSpacerDoc::GetNextFilename(CString filename, CString ext)
{		
	if (ext.IsEmpty() || filename.IsEmpty()) return filename;	

	zFILE_FILE path(filename.GetBuffer(0));
	zSTRING name = path.GetFilename();

	if (spcConfig.interativeSave) 
	{

		int index = name.SearchRev("_");
		zSTRING numStr = name.Copied(index+1);	
		if (numStr.ToInt()>0) 
		{
			numStr = zSTRING(numStr.ToInt()+1);
			name.Delete(index);
		}
		else numStr = "1";
		numStr.Align(zSTR_RIGHT,2,'0');
		name = name + "_" + numStr;
	}

	return CString(name.ToChar()) + "." + ext;
}
 

void CSpacerDoc::OnWorldReloadparticlefx() 
{
	zCLensFlareFX::LoadLensFlareScript();
}


void CSpacerDoc::OnWorldAnalysewaynet() 
{
	zCWorld* world = GetWorld();
	if (world)
	{
		zCWayNet* waynet = world->GetWayNet();
		if (waynet) 
		{			
			zSTRING result = waynet->CheckConsistency();
			if (!result.IsEmpty())
			{
				result = "Errors found: "+result;
				AfxMessageBox(result.ToChar());
			}
			else
			{
				AfxMessageBox("No errors found.");
			}			
		}
	};
}

void CSpacerDoc::OnUpdateWorldAnalysewaynet(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsAWorldLoaded() && GetWorld());	
}


void CSpacerDoc::OnWorldCallstartupscript() 
{
	#ifdef COMPILING_GOTHIC
	if (dynamic_cast<oCGame*>(session)) 
	{	
		//dynamic_cast<oCGame*>(session)->EnableScriptStartup(TRUE);
		//dynamic_cast<oCGame*>(session)->CallScriptStartup();		
	}
	#endif
}

void CSpacerDoc::OnUpdateWorldCallstartupscript(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);

#if defined COMPILING_GOTHIC && defined DEBUG_SPECKELS
	pCmdUI->Enable(TRUE);
#endif

}


bool CSpacerDoc::VobHandleBeforeSave(zCVob* vob)
{
	#ifndef ASSIGN_HELPER_VISUALS
		return true;
	#else
		if (!vob) // alle Vobs im Level
		{
			HandleVob(T_HANDLEVOB_CALLBACK(CB_HandleVobsBeforeSave));	
		}
		else // ein einzelner Vobtree
		{
			HandleVob(T_HANDLEVOB_CALLBACK(CB_HandleVobsBeforeSave), vob->globalVobTreeNode);	
		}	
		return true;
	#endif
}

bool CSpacerDoc::VobHandleAfterSave(zCVob* vob)
{	
	#ifndef ASSIGN_HELPER_VISUALS
		return true;
	#else	
		VobHandleAfterLoad(vob);
		return true;
	#endif
}

bool CSpacerDoc::VobHandleAfterLoad(zCVob* vob)
{
	#ifndef ASSIGN_HELPER_VISUALS	
		
		VobViewInvisible();

		#ifdef COMPILING_GOTHIC			

			// 
			// Npc(s) auf StandAI umschalten
			//
			if (!vob)
			{				
				oCWorld* world = dynamic_cast<oCWorld*>(GetWorld());
				oTVobListNpcs* npclist = (world?world->GetVobListNpcs():0);
				if (npclist)
				{
					for (int i=0;i<npclist->GetNumInList();i++)
					{
						if (npclist->Get(i))
							npclist->Get(i)->UseStandAI();
					};
				};		
			}
			else if (dynamic_cast<oCNpc*>(vob)) dynamic_cast<oCNpc*>(vob)->UseStandAI();

		#endif
		return true;
	#else
		zERROR_TYPE ackType = zerr.GetAck();
		zerr.SetAck((zERROR_TYPE)zERR_FATAL);
		
		// alle Vobs im Level bearbeiten (uff, das dauert ...)
		if (!vob) 
		{		
			HandleVob(T_HANDLEVOB_CALLBACK(CB_HandleVobsAfterLoad));	
		}
		// einen einzelnen VobTree bearbeiten
		else 
		{
			HandleVob(T_HANDLEVOB_CALLBACK(CB_HandleVobsAfterLoad), vob->globalVobTreeNode);	
		}

		zerr.SetAck(ackType);	
		return true;
	#endif
}

bool CSpacerDoc::VobViewInvisible()
{
	#ifdef ASSIGN_HELPER_VISUALS	
		HandleVob(T_HANDLEVOB_CALLBACK(CB_ViewInvisibleVobs));		
		return true;
	#else				
		zCVob::SetShowHelperVisuals(modeViewHelperVobs);
		return true;
	#endif
}

static double s_mult_ranges=1.0f;
static double s_mult_volumes=1.0f;

static bool CB_ManipulateSounds(zCVob* vob, CSpacerDoc* pDoc)
{	
	zCVobSound* soundVob = dynamic_cast<zCVobSound*>(vob);
	if (soundVob)
	{		
		soundVob->SetSoundVolume(soundVob->GetSoundVolume()*s_mult_volumes);
		if (soundVob->GetSoundVolType() == zCVobSound::zTSoundVolType::SV_SPHERE)
		{
			soundVob->SetSoundRadius(soundVob->GetSoundRadius()*s_mult_ranges);		
		}
		else if (soundVob->GetSoundVolType() == zCVobSound::zTSoundVolType::SV_ELLIPSOID)
		{
			zTBBox3D bbox = soundVob->GetBBox3DWorld();
			bbox.Scale(zVEC3(s_mult_ranges,1,s_mult_ranges));
			soundVob->SetBBox3DWorld(bbox);
		}
	};

	return true;
}

void CSpacerDoc::OnWorldManipulatesounds() 
{
	spcCObjectSoundDialog dialog;
	dialog.m_mult_ranges	= 1.0f;	
	dialog.m_mult_volumes	= 1.0f;
	if (dialog.DoModal()==IDOK)
	{
		if ((dialog.m_mult_volumes<=0.0f) || (dialog.m_mult_ranges<=0.0f))
		{
			AfxMessageBox("Error: Factors can't be zero or negative!!",IDOK);
		}
		else if ((dialog.m_mult_volumes==1.0f) && (dialog.m_mult_ranges==1.0f))
		{
			AfxMessageBox("Nothing to do. Factors are 1.",IDOK);
		}
		else
		{
			s_mult_volumes  = dialog.m_mult_volumes; 
			s_mult_ranges	= dialog.m_mult_ranges;
			HandleVob(T_HANDLEVOB_CALLBACK(CB_ManipulateSounds));
		}
	};
}

#pragma warning ( default:4244 )
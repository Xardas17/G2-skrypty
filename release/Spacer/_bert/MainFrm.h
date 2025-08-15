// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__64FA800A_27E8_11D2_88A8_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__64FA800A_27E8_11D2_88A8_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "z3d.h"
#ifndef __ZTYPES3D_H__
#include "zTypes3D.h"
#endif

#ifndef AFX_SPCCCONFIGURATION_H__F7F40944_2D1E_11D2_88A8_0080AD209698__INCLUDED_
#include "spcCConfiguration.h"
#endif

#ifndef AFX_SPCCWINDOWRESIZESTYLE_H__1814FCE9_E851_11D3_BA4F_0050DA339C1B__INCLUDED_
#include "spcCWindowResizeStyle.h"
#endif

#ifndef _ZOBJPRESET_H_
#include "spcCObjPreset.h"
#endif


class spcCListVobDlg;
class spcCListMaterialDlg;
class spcCListCutsceneDlg;
class spcCHelpDlg;
class spcCObjectSheet;

class spcCObjectBar;
class spcCInfoBar;
class spcCInfoBar_Specials;
class spcCInfoBar_Vobs;
class spcCInfoBar_Lights;
class spcCInfoBar_Sounds;
class spcCInfoBar_Materials;
class spcCInfoBar_Camera;
class spcCInfoBar_Events;
class spcCInfoBar_VobsPlus;
class spcCVobLogicalDialog;
class spcCInfoBar_Vertex;
class spcCVobContainer;

class spcCVobPropertyDialog;
class spcCVobCreationDialog;
class spcCVobListDialog;;

class spcCCSSequencer;
class zCCSBlockBase;

const int UPDATE_OBJECT_SHEET	= 1 << 0;
const int UPDATE_FOCUS			= 1 << 1;

enum TWorkMode
{
	MODE_NONE, MODE_UNKNOWN, 
	MODE_MOB, MODE_LIGHT, MODE_SOUND, MODE_ZONE,
	MODE_SPECIAL, MODE_VOBS, MODE_MATERIAL, MODE_EVENT, MODE_CUTSCENE, 
	MODE_CAMERA, MODE_PROPS, MODE_LOGICAL, MODE_VERTEX
};


enum TLibFLags
{
	MATLIB_VISIBLE, MATLIB_INVISIBLE
};

class zCVob;
class zCMaterial;

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	bool windowsAreOnTop;

// Attributes
public:
	static CMainFrame* mainframe;

	// Statusbar
	CStatusBar  m_wndStatusBar;

	TWorkMode workmode;			// mein mode (MODE_VOB, MODE_POLY
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:			
	void Reset();

	spcCListVobDlg*			GetVobListWindow()			{ return winVobList; };
	spcCListMaterialDlg*	GetMaterialListWindow()		{ return winMaterialList; };
	spcCListCutsceneDlg*	GetCutsceneListWindow()		{ return winCutsceneList; };
	spcCCSSequencer*		GetCutsceneSeqWindow()		{ return winCutsceneSequencer; };
	spcCHelpDlg*			GetHelpWindow()				{ return winHelp; };
	spcCObjectSheet*		GetObjectWindow()			{ return winObjectDlg; };
	spcCVobContainer*		GetVobContainer()			{ return winVobContainer; }

	bool	AreToolWindowsOnTop() { return windowsAreOnTop; };
	void	HideToolWindow(CWnd* wnd);
	void	ShowToolWindow(CWnd* wnd);

	// [EDENFELD] neu 1.33 aus ModSource
	bool	DeactivateApplicationWindows();
	bool	ReactivateApplicationWindows();


	virtual void HandleVobInsert(zCVob *vob, zCVob* parentVob=0);
	virtual void HandleVobRemove(zCVob *vob);
	virtual void HandleVobSelect(zCVob *vob);
	virtual void HandleObjChange(zCObject *obj, int flag=0);
	
	void UpdateWindowContents(zCWorld* world);
	void UpdateMaterialList(const zSTRING& filterName="");
	void UpdateVobList(zCWorld* world);	
	void PrepareForSave();
	void AfterSave();
	
	zCMaterial*		GetMaterial();	
	CString			GetVobTypeName();
	int				GetVertexMoveSpeed();

	// zCVob* InsertVobInTree(zCVob* vob, zCVob* parent);
	zCVob* CreateNewVob();
	zCVob* InsertVob(const zPOINT3& pos, const zPOINT3& dir, zCVob* vob);
	// zCVob* InsertMarker(const zPOINT3& pos, zCVob* vob);
	
	void GetMaterialMapping(float& x, float& y);
	void UpdateMatFilterList(); // if the config.matfilterlist possily changed, use this
	void VobCopy(zCVob* vob);	
		
	void ToggleWindowZOrder(CWnd* win);

	bool ActivateCutsceneSeq();   // is true if the CutsSeq was not running
	
	void DeactivateCS();
	bool CSActive() { return winCutsceneSequencer!=0; };
	void CSSetOU(zCCSBlockBase* ou);
	void CSUpdate();
	void CSAssignParameter(zSTRING & p);
	void	CSAssignIntegratedRole(zCVob* irole);
	zCVob*	CSRegetIntegratedRole();

	zCObjPresetLib presetLib;

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members	

	void UpdateChildWindows(zCObject* obj, bool show = true);

	void CloseChildWindow(CWnd* wnd);	

	void SetWorkMode(TWorkMode mode);

	// Toolbars	
	CToolBar			m_wndObjectToolbar;
	CToolBar			m_wndActionToolbar;	
	
	// BrowseBar: List of Vobs/Materials
	spcCListVobDlg*			winVobList;
	spcCListMaterialDlg*	winMaterialList;
	spcCListCutsceneDlg*	winCutsceneList;	
	spcCHelpDlg*			winHelp;
	spcCObjectSheet*		winObjectDlg;
	spcCCSSequencer*		winCutsceneSequencer;
	
	// InfoBar
	spcCObjectBar*			winBar;
	spcCInfoBar*			winInfoBar;
	spcCInfoBar_Specials*	winInfoBar_Specials;
	spcCInfoBar_Vobs*		winInfoBar_Vobs;
	spcCInfoBar_Lights*		winInfoBar_Lights;
	spcCInfoBar_Sounds*		winInfoBar_Sounds;
	spcCInfoBar_Materials*	winInfoBar_Materials;
	spcCInfoBar_Camera*		winInfoBar_Camera;
	spcCInfoBar_Events*		winInfoBar_Events;	
	spcCInfoBar_VobsPlus*	winInfoBar_Zones;	
	spcCInfoBar_Vertex*		winInfoBar_Vertex;
	spcCVobLogicalDialog*	winInfoBar_Logical;

	spcCVobContainer*		winVobContainer;

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;
	POSITION winID;
	// Generated message map functions
public:		
	void				OnMoveChild();		
	void				ResizeToView(CView* view, int x, int y);
	void				ObjectModified(zCObject* obj);
	CString				GetModeInformationString(zCObject* selectedObject);

	spcCInfoBar_Events*	GetInfoBarEvents();
	spcCInfoBar*		GetInfoBar();	
	spcCInfoBar_Lights* GetLightInfoBar()															{ return winInfoBar_Lights; };
	
	void				ObjectSelection(zCObject* obj, CWnd* wnd, BOOL show = TRUE);
	void				UpdateFixedWindows();
	void				UpdateWorkMode();
	void				HandleKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	

	void				InitWindows();

	void				OnObjStandardMode();

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnSettingsView();	
	afx_msg void OnSettingsGeneral();
	afx_msg void OnSaveSettings();
	afx_msg void OnLoadSettings();
	afx_msg void OnSaveMatfilter();
	afx_msg void OnLoadMatfilter();	
	afx_msg void OnExtracttext();
	afx_msg void OnUpdateExtracttext(CCmdUI* pCmdUI);
	afx_msg void OnImporttext();
	afx_msg void OnUpdateImporttext(CCmdUI* pCmdUI);
	afx_msg void OnCutsceneseq();
	afx_msg void OnUpdateCutsceneseq(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDoAI(CCmdUI* pCmdUI);
	afx_msg void OnPresetsave();
	afx_msg void OnUpdateViewConsole(CCmdUI* pCmdUI);
	afx_msg void OnWindowsFix();
	afx_msg void OnUpdateWindowsFix(CCmdUI* pCmdUI);
	afx_msg void OnMove(int x, int y);	
	afx_msg void OnWindowsAlignright();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnViewvobVobInitevents();
	afx_msg void OnUpdateViewvobVobInitevents(CCmdUI* pCmdUI);		
	afx_msg void OnObjTexture();
	afx_msg void OnObjCutscenes();
	afx_msg void OnObjLight();	
	afx_msg void OnObjSound();
	afx_msg void OnObjSpecial();
	afx_msg void OnObjEvent();	
	afx_msg void OnObjVobs();
	afx_msg void OnObjZone();
	afx_msg void OnObjCameras();
	afx_msg void OnObjLogical();
	afx_msg void OnObjVertex();
	afx_msg void OnViewConsole();
	afx_msg void OnUpdateObjCutscenes(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjLight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjSound(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjSpecial(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjTexture(CCmdUI* pCmdUI);	
	afx_msg void OnUpdateObjEvent(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjVobs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjZone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjCameras(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjVertex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjLogical(CCmdUI* pCmdUI);	
	afx_msg void OnWorldStoreVobstates();
	afx_msg void OnWorldRestoreVobstates();	
	afx_msg void OnUpdateCsReget(CCmdUI* pCmdUI);
	afx_msg void OnVieweditToggletools();
	afx_msg void OnUpdateVieweditToggletools(CCmdUI* pCmdUI);
	afx_msg void OnWindowsAlignwindowsoutside();
	afx_msg void OnUpdateWindowsAlignwindowsoutside(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnWindowsVobcontainer();
	afx_msg void OnUpdateWindowsVobcontainer(CCmdUI* pCmdUI);
	afx_msg void OnViewvobVobInserttocontainer();
	afx_msg void OnPlayGame();
	afx_msg void OnUpdatePlayGame(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__64FA800A_27E8_11D2_88A8_444553540000__INCLUDED_)

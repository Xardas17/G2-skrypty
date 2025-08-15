// SpacerView.h : interface of the CSpacerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPACERVIEW_H__64FA800E_27E8_11D2_88A8_444553540000__INCLUDED_)
#define AFX_SPACERVIEW_H__64FA800E_27E8_11D2_88A8_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ztypes3d.h"
#include "zAlgebra.h"	// Added by ClassView
#include "zstring.h"

#include "spcCCompileAction.h"
#include "spcCParticleControl.h"

class CMainFrame;
class CSpacerDoc;

class zCVob;
class zCPolygon;
class zCCamera;
class zCView;
class zCCSBlockBase;
class zCVobWaypoint;
class zCMaterial;
class spcCInfoBar;
class spcCDibSection;

class spcCMovement;

enum zTModeMove  { MV_NORMAL, MV_VOB_MOVE, MV_VOB_CONTROL, MV_VOB_OVERTAKEN };
enum zTModeView  { VIEW_PERSON, VIEW_TOP, VIEW_BOTTOM, VIEW_SPLIT2 };

const zSTRING VOBNAME_SPACER_CAMERA = "SPACER_CAMERA_VOB";
const int     SPC_NUM_VIEWS = 2;

class zCSelPoly
{		
public:
	zCSelPoly(zCPolygon* _poly);
	virtual ~zCSelPoly();

	void			SetMaterial(zCMaterial* _mat);
	zCMaterial*		GetMaterial();	
	zCPolygon*		GetPolygon();

protected:
	zCSelPoly() {};
	zCPolygon*  poly;
	zCMaterial* mat;	
};


class CSpacerView : public CView
{
// Attributes
public:

	virtual ~CSpacerView();

	virtual void HandleVobInsert(zCVob *vob, zCVob* parentVob=0);
	virtual void HandleVobRemove(zCVob *vob);
	virtual void HandleVobSelect(zCVob *vob);

	CSpacerDoc* GetDocument();
	
	zCCamera*	GetCamera()	{ return camera[0]; }; 
	void		ResetCameraAfterPlay();

	static CSpacerView* view;

	spcCParticleControl particleControl;
	void UpdateParticleControl(bool onoff);	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpacerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//}}AFX_VIRTUAL

	bool LastDrawSuccess() { return drawSuccess; };

	void PlayAs(zCVob* vob);	
	void AddVobToWorld	 (zCVob* childVob, zCVob* parentVob);
	void SetViewMode(zTModeView mode);
	// zCObject* GetPickedObject();
	bool view_sound;
	bool view_waynet;
	void SetCamInFrontOfVob(zCVob* vob, int distance);
	void ShowPopupMenue(CPoint point);
	void Do_CompileWorld(const spcCCompileWorldAction& action);
	void Do_CompileLight(const spcCCompileLightAction& action);

	bool modeFullscreen;
	void AutomapMovement();	
	
	/*
	void WayRemovePoint	(zCVobWaypoint* wpvob);
	void WayToggleWay	(zCVob* vob1, zCVob* vob2);
	void WayRemoveWay	(zCVob* vob1, zCVob* vob2);
	void WayMovePoint	(zCVobWaypoint * wpvob);
	void WayCreateWay	(zCVob* vob1, zCVob* vob2);
	*/
	
	void RememberCamPos	(bool remember=true);
	void ResetCamPos	();

	void VobApplyPhysics(zCVob* _vob, zVEC3 vec);	
	void VobGoto		(zCVob* vob);
	void VobSelect		(zCVob* vob, bool show=true);

	void SetMoveMode	(zTModeMove newmode);	
	
	void RepeatLastCompileAction(bool emode=true);
	void InvalidateLastCompileAction() { lastCompileWorldAction.valid=false; };
	
	void RenderInfo(CDC* dc);	
	void Reset();	
	void InitVideo();
	void InitSettings();
	
	void PositionShortcut(int nr, bool jump);
	
	void WorldPolyApplyMapping(zVALUE su, zVALUE sv, zCMaterial* mat);
	
	//AFX_MSG
	afx_msg void OnWorldCompile();
	//AFX_MSG (End)

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
	bool		camLastRemembered;
	bool		camLastAutoRemembered;
	zPOINT3		camLastPos;
	zPOINT3		camLastDir;
	

	void PrepareInsertedWaypoint(zCVob* vob);

	CSpacerView();
	DECLARE_DYNCREATE(CSpacerView)

	void Init();
	void InitNull();
	void Deinit();
	void ResizeViewport();
	void InitViewport(BOOL newworld=FALSE);	

	void EnableDrawing(BOOL draw=TRUE);

	void OnDrawExtView(CDC* pDC, int nr);
	void OnDrawInitialize(CDC* pDC);
	void OnDrawStartScreen(CDC* pDC);
	void OnDrawAfterRender(CDC* pDC);
	void OnDrawBeforeRender(CDC* pDC);
	void OnDrawUpdate(CDC* pDC, int left = 0, int top = 0, int right=8192, int bottom=8192);

	void DrawLine ( zCCamera *camera, zCVob* v1, zCVob* v2, zCOLOR col );

	void OnKey_TextureManipulate(UINT nChar); 
	void OnKey_VertexManipulate(UINT nChar);	
	void OnKey_VobManipulate(UINT nChar);

	void PolyApplyMapping();	
	void PolyHideSelection(bool hide);
	void PolyClearSelection	();
	void PolyMouseClick		(zCPolygon* xPoly);
	bool PolySelect			(bool select, zCSelPoly* selPoly);			
	void PolyMouseOver		(UINT nFlags, CPoint point);
	void PolyFloatSelect	(zCPolygon* xPoly);
	zCSelPoly* PolyIsSelected(zCPolygon* xPoly);

	void TextureShear(zVALUE x, zVALUE y);
	void TextureMove(zREAL x, zREAL y);
	void TextureRotate(zVALUE value);
	void TextureRotateByAngle(zVALUE angle);
	void TextureScale(zVALUE x, zVALUE y);
	void TextureMirror(zVALUE u, zVALUE v);	
	void TextureCalcCenter(zPOINT2& center);

	void VertMouseClick		(zCVertex* v);
	void VertClearSelection	();
	bool VertSelect			(bool select, zCVertex* v);
	bool VertIsSelected		(zCVertex* v) { return selVertex.Search(v)>=0; };
	void VertMove			(zVALUE x, zVALUE y, zVALUE z);
	void CollectVobsInContainer(zCWorld* world);		// [EDENFELD] neu 1.33

	zCVob* GetParentVob(zCVob* candidate);	
	
	//{{AFX_MSG(CSpacerView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVobInsert();	
	afx_msg void OnVobRemove();
	afx_msg void OnUpdateVobRemove(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWorldCompile(CCmdUI* pCmdUI);	
	afx_msg void OnVobMove();
	afx_msg void OnUpdateVobMove(CCmdUI* pCmdUI);
	afx_msg void OnVobTakeover();
	afx_msg void OnUpdateVobTakeover(CCmdUI* pCmdUI);
	afx_msg void OnVobControl();
	afx_msg void OnUpdateVobControl(CCmdUI* pCmdUI);	
	afx_msg void OnVobCollisionDetection();
	afx_msg void OnUpdateVobCollisionDetection(CCmdUI* pCmdUI);
	afx_msg void OnVobColldet();
	afx_msg void OnWayCreate();
	afx_msg void OnUpdateWayCreate(CCmdUI* pCmdUI);
	afx_msg void OnPolyPickmaterial();
	afx_msg void OnPolyApplyTexWithMapping();
	afx_msg void OnUpdatePolyApplyM(CCmdUI* pCmdUI);
	afx_msg void OnPolyApplyTexture();
	afx_msg void OnUpdatePolyApplyTexture(CCmdUI* pCmdUI);
	afx_msg void OnViewFogging();
	afx_msg void OnUpdateViewFogging(CCmdUI* pCmdUI);
	afx_msg void OnWorldCompilelight();
	afx_msg void OnUpdateWorldCompilelight(CCmdUI* pCmdUI);
	afx_msg void OnPolyToggleSelection();
	afx_msg void OnUpdatePolyPickmaterial(CCmdUI* pCmdUI);
	afx_msg void OnVobSaveTree();
	afx_msg void OnVobInsertTree();
	afx_msg void OnViewWire();
	afx_msg void OnUpdateViewWire(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVobInsertTree(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVobInsertmeshVob(CCmdUI* pCmdUI);
	afx_msg void OnVobPhysics();
	afx_msg void OnUpdateVobPhysics(CCmdUI* pCmdUI);	
	afx_msg void OnDeselect();
	afx_msg void OnPolyApplyDes();
	afx_msg void OnCSIntegrate();
	afx_msg void OnPolyPlanar();
	afx_msg void OnCsDeclarePc();
	afx_msg void OnUpdateCsDeclarePc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCsIntegrate(CCmdUI* pCmdUI);
	afx_msg void OnToolsMacros();
	afx_msg void OnViewFullscreen();
	afx_msg void OnUpdateViewFullscreen(CCmdUI* pCmdUI);
	afx_msg void OnToolsGotoposition();
	afx_msg void OnToolsGotoOrigin();
	afx_msg void OnToolsSpecialSavetmpdoc();
	afx_msg void OnToolsSpecialLoadtmpdoc();
	afx_msg void OnViewvobCopy();
	afx_msg void OnViewvobPaste();
	afx_msg void OnViewvobPlay();
	afx_msg void OnUpdateViewvobPlay(CCmdUI* pCmdUI);
	afx_msg void OnKeyPopup();
	afx_msg void OnUpdateViewvobPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewvobCopy(CCmdUI* pCmdUI);
	afx_msg void OnViewvobGoto5meters();
	afx_msg void OnViewvobGoto2meters();
	afx_msg void OnViewvobGoto1meter();
	afx_msg void OnViewvobGotoHalfmeter();
	afx_msg void OnShortcut1Def();
	afx_msg void OnShortcut1();
	afx_msg void OnShortcut2();
	afx_msg void OnShortcut2Def();
	afx_msg void OnShortcut3();
	afx_msg void OnShortcut3Def();
	afx_msg void OnShortcut4();
	afx_msg void OnShortcut4Def();	
	afx_msg void OnViewvobVobLetfalldown();	
	afx_msg void OnVobCreatePreset();
	afx_msg void OnUpdateViewvobVobCreatepreset(CCmdUI* pCmdUI);
	afx_msg void OnViewTogglesound();
	afx_msg void OnViewWaynet();
	afx_msg void OnUpdateViewWaynet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTogglesound(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePolyToggleSel(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePolyPlanar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeselect(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePolyApplyDes(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVobColldet(CCmdUI* pCmdUI);	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnToggleBilinearFiltering();
	afx_msg void OnUpdateToggleBilinearFiltering(CCmdUI* pCmdUI);	
	afx_msg void OnVobInsertByKey();
	afx_msg void OnCsReget();		
	afx_msg void OnViewvobVobSizedownbbox();		
	afx_msg void OnVieweditTogglecamsplines();
	afx_msg void OnUpdateVieweditTogglecamsplines(CCmdUI* pCmdUI);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnVobTest();
	afx_msg void OnUpdateVobTest(CCmdUI* pCmdUI);
	afx_msg void OnVieweditTextoutput();
	afx_msg void OnUpdateVieweditTextoutput(CCmdUI* pCmdUI);
	afx_msg void OnVieweditToggleinfotext();
	afx_msg void OnUpdateVieweditToggleinfotext(CCmdUI* pCmdUI);
	afx_msg void OnViewVob();
	afx_msg void OnUpdateViewVob(CCmdUI* pCmdUI);
	afx_msg void OnVobVobname();
	afx_msg void OnUpdateVobVobname(CCmdUI* pCmdUI);
	afx_msg void OnUpdateVobProperties(CCmdUI* pCmdUI);
	afx_msg void OnVobProperties();
	afx_msg void OnViewvobVobMovehere();
	afx_msg void OnToggleCamPos();
	afx_msg void OnUpdateToggleCamPos(CCmdUI* pCmdUI);
	afx_msg void OnRememberCamPos();
	afx_msg void OnUpdateRememberCamPos(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	zCVob* playAsVob;	

	// static BOOL draw_enabled;	
	zCPolygon*	pickedPoly;	
	zCVertex*	pickedVertex;
	zCVob*		pickedWaypoint2nd;
	zCVob*		pickedWaypoint;

	zTModeView modeView;
	zTModeMove modeMove;

	bool drawSuccess;
	bool viewInfoText;
	bool viewTextOut;
	bool modeSelectPolygons;
	bool modePickMaterial;
	bool modeTexManip;
	bool modeVertManip;

	zCArray<zMATRIX4> rememberedPositions;

	zCMaterial*				SelectMaterial;
	zCArray<zCPolygon*>*	leakPolyList;
	int leakPolyCurrent;
	
	// last compile-options
	spcCCompileWorldAction lastCompileWorldAction;

	zPOINT2 poly_center;

	// time values
	LARGE_INTEGER	counter;
	LARGE_INTEGER	counterfrequency;
	BOOL			counter_enabled;	

	// world:	
	bool			view_show[SPC_NUM_VIEWS];
	zCCamera*		camera[SPC_NUM_VIEWS];
	zCVob*			camera_vob[SPC_NUM_VIEWS];	
	zCView*			viewport[SPC_NUM_VIEWS];		
	spcCDibSection*	dib[SPC_NUM_VIEWS];
	
	//zPOINT3			camera_pos;
	//zPOINT3			camera_heading;
	zVALUE			camera_farclipz;
	BOOL			fog;
	BOOL			wire;
	BOOL			big;
			
	spcCInfoBar*	infoBar;

	// view-modes
	// zRENDERER renderer_type;
	int drawMode, drawShadeMode;
	int drawWire, drawSmoothMesh;	

	// popups

	// selected polygones
	zCList<zCSelPoly>* selPolyList;
	zCList<zCSelPoly>* selPolyList2;
	zCArray<zCVertex*> selVertex;

	CString vobCopyName;
	zCBuffer* vobCopyBuffer;
};

#ifndef _DEBUG  // debug version in SpacerView.cpp
inline CSpacerDoc* CSpacerView::GetDocument()
   { return (CSpacerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPACERVIEW_H__64FA800E_27E8_11D2_88A8_444553540000__INCLUDED_)

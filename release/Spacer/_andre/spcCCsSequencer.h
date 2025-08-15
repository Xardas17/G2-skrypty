#if !defined(AFX_spcCCSSequencerS_H__43DE44E1_B5D4_11D2_A902_DD27DBE4DE08__INCLUDED_)
#define AFX_spcCCSSequencerS_H__43DE44E1_B5D4_11D2_A902_DD27DBE4DE08__INCLUDED_


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCCSSequencers.h : header file
//

#include <resource.h> 
#include "afxtempl.h"

#include "spcCTrackCtrl.h"
#include "spcCWindowResizeStyle.h"

class spcCDiagramVP;

// engine
#include "zString.h"
#include "zbuffer.h"
#include "zCCSPlayer.h"


class zCCSCutsceneContext;

class spcCCSViewportScrollbar : public CScrollBar
{
public:
	spcCCSViewportScrollbar();
	virtual ~spcCCSViewportScrollbar();

	void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
};

/////////////////////////////////////////////////////////////////////////////
// spcCCSSequencers dialog

class spcCCSSequencer : public CDialog, public zCCSDebugger
{
// Construction
public:
	spcCCSSequencer(CWnd* pParent = NULL);   // standard constructor
	virtual ~spcCCSSequencer();

	HTREEITEM FindTreeItem(const zSTRING& name, HTREEITEM item=0);

	virtual void HandleObjChange(zCObject* obj);

	void	BlockPositionCheck(zCCSBlockBase* blockToCheck, bool setToZero);

	virtual void Reset();

// Dialog Data
	//{{AFX_DATA(spcCCSSequencer)
	enum { IDD = IDD_CS_SEQUENCER };
	CButton	ctrl_grid;
	spcCCSViewportScrollbar ctrl_viewport_scrollbar;	
	CButton	ctrl_role_del;
	CButton	ctrl_role_add;
	CEdit	ctrl_time_value;
	CButton	ctrl_sync_ins;
	CButton	ctrl_sync_del;
	CButton	ctrl_sync_add;
	CButton	ctrl_simulate;
	CButton	ctrl_button_sync_inc;	
	CButton	ctrl_button_sync_dec;
	CButton	ctrl_button_timeinc;
	CButton	ctrl_button_timedec;
	CButton	ctrl_button_start;	
	CEdit	ctrl_edit_syncblock;	
	CStatic	ctrl_viewport_placeholder;	
	spcCTrackCtrl	ctrl_tracktree;
	CEdit	ctrl_seltext;
	CString	m_seltext;
	int		m_syncBlock;
	BOOL	m_simulate;
	int		m_viewport_scrollpos;	
	BOOL	m_grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCCSSequencer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation 
protected:
	zSTRING csName;
	zSTRING oldBaseClass;
	
	zCVob*	InitCutsceneBeforeRunning	(zCCutscene* cs);
	zCVob*	DeinitCutsceneAfterRunning	(zCCutscene* cs);
	zBOOL	InitRoleVob					(zCVob* vob);
	zBOOL	DeinitRoleVob				(zCVob *vob);
	void	StopRunningCutscene			();	
	void	OnUpdate					();	

	POSITION winID;

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;		

	spcCDiagramVP* viewPort;
	
	int selectedSubType;
	
	void StartTimer	();
	void StopTimer	();

	// Generated message map functions
	//{{AFX_MSG(spcCCSSequencer)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnItemexpandedTracktree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTracktree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimedec();
 	afx_msg void OnTimeinc();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChangeText();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCsopen();
	afx_msg void OnAddtrackAni();
	afx_msg void OnAddtracksnd();
	afx_msg void OnAddtrackturn();
	afx_msg void OnTimescrollL();
	afx_msg void OnTimescrollR();
	afx_msg void OnCSnew();
	afx_msg void OnCSsaveAs();
	afx_msg void OnAddTrack_00();
	afx_msg void OnAddTrack_01();
	afx_msg void OnAddTrack_02();
	afx_msg void OnAddTrack_03();
	afx_msg void OnAddTrack_04();
	afx_msg void OnAddTrack_05();
	afx_msg void OnAddTrack_06();
	afx_msg void OnAddTrack_07();
	afx_msg void OnAddTrack_08();
	afx_msg void OnAddTrack_09();
	afx_msg void OnAddTrack_0A();
	afx_msg void OnAddTrack_0B();
	afx_msg void OnAddTrack_0C();
	afx_msg void OnAddTrack_0D();
	afx_msg void OnAddTrack_0E();
	afx_msg void OnAddTrack_0F();
	afx_msg void OnAddTrack_10();
	afx_msg void OnAddTrack_11();
	afx_msg void OnAddTrack_12();
	afx_msg void OnAddTrack_13();	
	afx_msg void OnAddTrack_14();	
	afx_msg void OnAddTrack_15();
	afx_msg void OnAddTrack_16();
	afx_msg void OnAddTrack_17();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRemoveblock();
	afx_msg void OnEndlabeleditTracktree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddrole();
	afx_msg void OnAddsyncblock();
	afx_msg void OnRemoveRole();
	afx_msg void OnUpdateEdit(CCmdUI* pCmdUI);
	afx_msg void OnInsertsyncblock();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowProp();
	afx_msg void OnAddgentrack();
	afx_msg void OnCsprops();
	afx_msg void OnRemovesync();
	afx_msg void OnRoleprops();	
	afx_msg void OnCsStart();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);	
	afx_msg void OnEditAddroleMain();
	afx_msg void OnUpdateEditAddroleMain(CCmdUI* pCmdUI);
	afx_msg void OnEditAddspecialroleTheplayer();
	afx_msg void OnUpdateEditAddspecialroleTheplayer(CCmdUI* pCmdUI);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeydownTracktree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateInsertsyncblock(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRemoverole(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRemoveblock(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRemovesync(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddsyncblock(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddgentrack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRoleprops(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCssave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCssaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCsprops(CCmdUI* pCmdUI);
	afx_msg void OnSelchangedTracktree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCssave();
	afx_msg void OnSyncblockDelByButton();
	afx_msg void OnSyncblockAddByButton();
	afx_msg void OnSyncblockInsByButton();	
	afx_msg void OnRoleAddByButton();
	afx_msg void OnRoleDelByButton();				
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCutscenesMovetobegin();	
	afx_msg void OnCutscenesSynchronous();
	afx_msg void OnUpdateCutscenesSynchronous(CCmdUI* pCmdUI);
	afx_msg void OnCutscenesRemove();
	afx_msg void OnGrid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int message_mapper[24];

private:
	zCArray<zCCSBlockBase*> flatData;
	zCArray<CString>		roleNameList;
	HTREEITEM				lastFirstItem;

	enum TCSWorkMode { workOU, workCS };
	TCSWorkMode				workMode;
	int						selected;
	int						dataState;		
	bool					stepPlay;	
	CString					lastFileName;

	void BuildAfterBlockCorrection	();
	zCCutscene* GetCutsceneFromFlatData();

	void DrawIt				();
	void FlatnBlock			(zCCSBlockBase* bl, HTREEITEM parent);
	void FlatnCutscene		(zCCutscene* cs);
	void BuildData			(zCCutscene* cs);
	int  FindFocus			(int n);
	void AddTrack			(int nr);
	
	int m_timepos;
	void OnChangeTimePos	();
	void ChangeDataState	(int newState);
	void BuildMenu			();

	// besondere flatn operationen für Cutscenes
	void createTrack_Roles	();
	void createTrack_AICom	(HTREEITEM roleITEM, int roleNumber);
	void createTrackBlockRef(int num);

	bool propmode;

public:	
	void AssignCutscene		(zCCutscene* cs);
	void AssignOutputUnit	(zCCutscene* cs);
	void AssignParameter	(zSTRING & p);
	bool	AssignIntegratedRole	(zCVob* irole);
	zCVob*	RegetIntegratedRole		();


	void ViewDrawIfNessesary();
	void ViewRefresh		();
	zCCSBlockBase* GetCutsceneForDebug();

	// spcDebugger
	virtual void CSDB_BeginSyncBlock(zCCSSyncBlock* b);
	virtual void CSDB_BeginAtomBlock(zCCSBlockBase* b);
	virtual void CSDB_EndAtomBlock	(zCCSBlockBase* b);
	virtual void CSDB_Error			(zCCSBlockBase* b, zSTRING & text);
	virtual void CSDB_Warning		(zCCSBlockBase* b, zSTRING & text);

	virtual void CSDB_StartPlaying(zCCutscene* b);
	virtual void CSDB_Stop(zCCutscene* b);

	void OnOK();
private:
	zCBuffer DB_RoleBuffer;
	zCCSCutsceneContext* current_context;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_spcCCSSequencerS_H__43DE44E1_B5D4_11D2_A902_DD27DBE4DE08__INCLUDED_)

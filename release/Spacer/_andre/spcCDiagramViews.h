#if !defined(AFX_SPCCDIAGRAMVIEWS_H__43DE44E1_B5D4_11D2_A902_DD27DBE4DE08__INCLUDED_)
#define AFX_SPCCDIAGRAMVIEWS_H__43DE44E1_B5D4_11D2_A902_DD27DBE4DE08__INCLUDED_


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spcCDiagramViews.h : header file
//
#include <resource.h> 

#include "spcCDiagramVP.h"
#include "spcCInfoPropDlg2.h"
#include "spcCTrackCtrl.h"


#include "zCCSPlayer.h"

/////////////////////////////////////////////////////////////////////////////
// spcCDiagramViews dialog

class spcCDiagramView : public CDialog, public zCCSDebugger
{
// Construction
public:
	spcCDiagramView(CWnd* pParent = NULL);   // standard constructor
	virtual ~spcCDiagramView();
// Dialog Data
	//{{AFX_DATA(spcCDiagramView)
	enum { IDD = IDD_DIAGRAMVIEW };
	CButton	ctrl_cs_start;
	spcCTrackCtrl	ctrl_tracktree;
	CEdit	ctrl_seltext;
	CString	m_seltext;
	int		m_syncBlock;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spcCDiagramView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	spcCDiagramVP viewPort;
	spcCInfoPropDlg2 blockEdit;

	// Generated message map functions
	//{{AFX_MSG(spcCDiagramView)
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
	afx_msg void OnCSSave();
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
	afx_msg void OnCsRepeat();
	afx_msg void OnCsStart();
	afx_msg void OnCsStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int message_mapper[16];

private:
	zCArray<zCCSBlockBase*> flatData;
	zCArray<CString> roleNames;
	HTREEITEM lastFirstItem;

	int selected;
	int dataState;
	enum TCSWorkMode { workOU, workCS };
	TCSWorkMode workMode;

	bool stepPlay;

	CString lastFileName;

	void drawIt		();
	void flatn		(zCCSBlockBase* bl, HTREEITEM parent);
	void buildData	(zCCSBlockBase* cs);
	int  findFocus	(int n);
	void addTrack	(int nr);

	void buildAfterBlockCorrection();

	zCCSBlockBase* GetFlatData0();

	int m_timepos;
	void OnChangeTimePos();
	void ChangeDataState(int newState);
	void BuildMenu();

	// besondere flatn operationen für Cutscenes
	void createTrack_Roles	();
	void createTrack_AICom	(HTREEITEM roleITEM, int roleNumber);
	void createTrackBlockRef(int num);

	bool propmode;

public:
	void AssignCutscene		(zCCSBlockBase* cs);
	void AssignOutputUnit	(zCCSBlockBase* cs);
	void AssignParameter	(zSTRING & p);
	void AssignIntegratedRole(zCVob* irole);

	void ViewDrawIfNessesary();
	void ViewRefresh();
	zCCSBlockBase* GetCutsceneForDebug();

	// spcDebugger
	virtual void CSDB_BeginSyncBlock(zCCSSyncBlock* b);
	virtual void CSDB_BeginAtomBlock(zCCSBlockBase* b);
	virtual void CSDB_EndAtomBlock	(zCCSBlockBase* b);
	virtual void CSDB_Error			(zCCSBlockBase* b, zSTRING & text);
	virtual void CSDB_Warning		(zCCSBlockBase* b, zSTRING & text);

	virtual void CSDB_Start(zCCutscene* b);
	virtual void CSDB_Stop(zCCutscene* b);

	void OnOK();
private:
	zCBuffer DB_RoleBuffer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPCCDIAGRAMVIEWS_H__43DE44E1_B5D4_11D2_A902_DD27DBE4DE08__INCLUDED_)

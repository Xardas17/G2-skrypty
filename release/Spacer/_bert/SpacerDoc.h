// SpacerDoc.h : interface of the CSpacerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPACERDOC_H__64FA800C_27E8_11D2_88A8_444553540000__INCLUDED_)
#define AFX_SPACERDOC_H__64FA800C_27E8_11D2_88A8_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <zVob.h>

class CSpacerDoc;

class zCWorld;
class zCObjPresetLib;

class oCGame;

enum zSAVE_TYPE { SAVE_ZEN, SAVE_ZEN_UC, SAVE_ZEN_BIN, SAVE_3DS };
enum zLOAD_TYPE { LOAD_ZEN, LOAD_ZEN_UC, LOAD_3DS };
 
#define GET_DOC() 

typedef bool* (*T_HANDLEVOB_CALLBACK)   (zCVob* vob, CSpacerDoc* pDoc);

class CSpacerDoc : public CDocument
{
public:			
	virtual ~CSpacerDoc();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpacerDoc)
	public:
	virtual BOOL OnNewDocument();	
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL
	
	void	SaveFile			(CString filename, zSAVE_TYPE save_type);
	void	LoadFile			(CString filename, zLOAD_TYPE load_type);
	
	void	UserSelectVisual	(zCVob* vob);

	void	SetDirty			(bool set = TRUE);
	bool	IsDirty				();	

	void	Init				();
	void	Reset				();	

	zCVob*	GetParentVob		(zCVob* candidate=0);
	bool	InsertVob			(zCVob* vob, zPOINT3* pos=0, zPOINT3* dir=0, zCVob* parent = 0);
	bool	RemoveVob			(zCVob* vob,  zBOOL secure_ask = TRUE);

	zPOINT3 CalcLocalPosition	(zCVob* parent, zPOINT3 pos);
	
	bool	VobHandleBeforeSave	(zCVob* vob=0);
	bool	VobHandleAfterSave	(zCVob* vob=0);
	bool	VobHandleAfterLoad	(zCVob* vob=0);
	bool	VobViewInvisible	();
	bool	VobDetectCollision	(zCVob* vob=NULL);	
	
	bool	HandleVob			(T_HANDLEVOB_CALLBACK callback, zCTree<zCVob>* vobNode = NULL);	

	CString	UpdateWindowTitle	();

	bool	ParseScript			(CString scriptname);		

	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif

	afx_msg void OnQuickSave	();
	afx_msg void OnQuickOpen	();	

	void WayRemovePoint			(zCVob* wpvob);
	void WayToggleWay			(zCVob* vob1, zCVob* vob2);
	void WayMovePoint			(zCVob* wpvob);
	
	void HandleWorldAfterSave	();
	void HandleWorldBeforeSave	();
	void HandleWorldAfterLoad	();

	zCWorld*	GetWorld		(zBOOL getEmptyWorldToo = FALSE);
	bool		IsAWorldLoaded	();

public:
	static CSpacerDoc*	doc;
	static zCSession*	session;	
	
	zCVob*				camera_vob;
	bool				modeViewHelperVobs;	

protected:	
	CString GetNextFilename		(CString filename, CString ext);

	CSpacerDoc();

	DECLARE_DYNCREATE(CSpacerDoc)

	//{{AFX_MSG(CSpacerDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnViewInvisibleVobs();
	afx_msg void OnUpdateViewInvisibleVobs(CCmdUI* pCmdUI);		
	afx_msg void OnFileMerge();
	afx_msg void OnUpdateFileMerge(CCmdUI* pCmdUI);	
	afx_msg void OnWorldDifscript();
	afx_msg void OnFileOpenmakefile();
	afx_msg void OnUpdateFileOpenmakefile(CCmdUI* pCmdUI);
	afx_msg void OnFileOpenmesh();
	afx_msg void OnFileMergemesh();
	afx_msg void OnUpdateFileMergemesh(CCmdUI* pCmdUI);		
	afx_msg void OnFileNew();
	afx_msg void OnFileSaveZen();
	afx_msg void OnUpdateFileSaveZen(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveMesh();
	afx_msg void OnUpdateFileSaveMesh(CCmdUI* pCmdUI);
	afx_msg void OnToolsInformations();
	afx_msg void OnUpdateToolsInformations(CCmdUI* pCmdUI);	
	afx_msg void OnClose();
	afx_msg void OnViewTogglevobboxes();
	afx_msg void OnUpdateVieweditTogglevobboxes(CCmdUI* pCmdUI);
	afx_msg void OnWorldAnalyse();
	afx_msg void OnUpdateWorldAnalyse(CCmdUI* pCmdUI);
	afx_msg void OnWorldReloadparticlefx();
	afx_msg void OnWorldAnalysewaynet();
	afx_msg void OnUpdateWorldAnalysewaynet(CCmdUI* pCmdUI);
	afx_msg void OnWorldCallstartupscript();
	afx_msg void OnUpdateWorldCallstartupscript(CCmdUI* pCmdUI);
	afx_msg void OnWorldManipulatesounds();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:

	void PresetSyncX			(zCTree<zCVob>* node, zCObjPresetLib& pLib,int method , zBOOL warn);
	void PresetSynchronisation	(zCObjPresetLib& pLib,int method=0, zBOOL warn=FALSE);

	CString	spcVERSION;
	zSTRING	spcCMVOBNAME;

	CString	current_filename;
	
	bool	addToRecent;
	bool	loadCompiled;
	bool	firstVobFound;
	bool	isDirty;
	
	struct TFlagMem 
	{
		zBOOL dynCol;
		zBOOL statCol;
		zCVob* vob;
		
		TFlagMem() : vob(0), dynCol(FALSE), statCol(FALSE) {};
		TFlagMem(zCVob* _vob) { Set(_vob); };
		void Set(zCVob* _vob) 
		{
			vob = _vob;
			dynCol = vob->GetCollDetDyn();
			statCol = vob->GetCollDetStat();
			vob->SetCollDet(FALSE);
		};
		void Put() 
		{
			vob->SetCollDetDyn(dynCol);
			vob->SetCollDetStat(statCol);
			vob=0;
		};
	};

	void VobTreeCorrX		(zCTree<zCVob>* node, zCArray<TFlagMem>& flagMem);
	void VobTreeCorrection	(CString& matName);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPACERDOC_H__64FA800C_27E8_11D2_88A8_444553540000__INCLUDED_)

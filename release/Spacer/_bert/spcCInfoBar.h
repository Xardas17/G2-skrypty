#if !defined(AFX_spcCInfoBar_H__1D413AE1_FA9D_11D3_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_spcCInfoBar_H__1D413AE1_FA9D_11D3_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCInfoBar.h : Header-Datei
//

#include <afxdtctl.h>
#include "zTypes3D.h"
#include "zcontainer.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCInfoBar 

class zCBuffer;
class zCWorld;
class zCVob;
class zCArchiver;
class zCObject;
class zCCSPlayer;
class zCCSManager;

class spcCVobItem
{
public:
	zCVob* vob;
	zCVob* parent;

	spcCVobItem(zCVob* vob);
};

typedef zCList<spcCVobItem> spcCVobList;

class spcCInfo
{
public:	
	spcCInfo();
	virtual ~spcCInfo();
	virtual void		SetActiveWorld(zCWorld* world);
	virtual void		SetSelectedObject(zCObject* obj);
	virtual void		SetPositionVob(zCVob* vob);
	virtual	void		SetSession(zCSession* _session);
	
	virtual zCWorld*	GetActiveWorld();	
	virtual zCVob*		GetSelectedVob();
	virtual zCObject*	GetSelectedObject();	
	virtual zBOOL		GetCurrentPosVector(zPOINT3& pos);
	virtual zBOOL		GetCurrentAtVector(zPOINT3& dir);	

	zCCSManager*		GetCurrentCutsceneManager();
	zCCSPlayer*			GetCurrentCutscenePlayer();

	virtual void		StoreVobStates();
	virtual void		RestoreVobStates();
	virtual void		ClearVobStates();	

	virtual void		StoreVob(zCArchiver* arc, zCVob* vob);
	virtual void		RestoreVob(zCArchiver* arc, zCVob* vob, zCVob* parent);

protected:

	void				Store(zCArchiver* archiver, zCTree<zCVob>* vobNode);

protected:

	zCSession*	session;
	zCWorld*	activeWorld;
	zCObject*	selectedObject;	
	zCVob*		positionVob;

	spcCVobList		storedVobList;
	spcCVobList*	curStoredVobList;
	zCBuffer*		storedVobBuffer;	
};

class spcCInfoBar : public CDialog, public spcCInfo
{
// Konstruktion
public:
	virtual void RestoreVobStates();
	virtual void StoreVobStates();

	virtual void UpdateInfo();
	virtual void SetSelectedObject(zCObject *obj);
	virtual void SetActiveWorld(zCWorld *world);

	virtual void StoreVob(zCArchiver* arc, zCVob* vob);
	virtual void RestoreVob(zCArchiver* arc, zCVob* vob, zCVob* parent);

	spcCInfoBar(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~spcCInfoBar();

	bool UpdateTime(int &_hour, int &_min);

// Dialogfelddaten
	//{{AFX_DATA(spcCInfoBar)
	enum { IDD = IDD_INFO_DEFAULT };
	CProgressCtrl	ctrl_progress;
	CButton	ctrl_store;
	CButton	ctrl_restore;
	CDateTimeCtrl	ctrl_daytime;
	CTime	m_daytime;	
	BOOL	m_holdtime;
	CString	m_info;
	CString	m_state;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCInfoBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnCancel();	
	//}}AFX_VIRTUAL

// Implementierung
protected:
	
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCInfoBar)
	virtual BOOL OnInitDialog();
	afx_msg void OnWorldStoreVobstates();
	afx_msg void OnWorldRestoreVobstates();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_spcCInfoBar_H__1D413AE1_FA9D_11D3_BA4F_0050DA339C1B__INCLUDED_

#if !defined(AFX_SPCCWORLDANALYSEDLG_H__2A8ABF01_032B_11D4_BA4F_0050DA339C1B__INCLUDED_)
#define AFX_SPCCWORLDANALYSEDLG_H__2A8ABF01_032B_11D4_BA4F_0050DA339C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCWorldAnalyseDlg.h : Header-Datei
//

#include "zworld.h"

class zCWorld;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCWorldAnalyseDlg 


struct spcTAnalysedVob
{
	zCVob*	vob;
	enum {	INFO,
			NO_VISUAL, 
			BAD_VISUAL, 
			NO_DISTINCT_VOBNAME, 
			HAS_VOBNAME, 
			NO_VOBNAME,
			NO_WAYPOINT_CONNECTED,
			MORE_THAN_ONE_INSTANCE,
			MAX 
		} type;
	zSTRING info;

	spcTAnalysedVob(zCVob* v) { vob =v; };
};

class spcCVobAnalyseCallback : public zCVobCallback
{
protected:		
	zCWorld*				world;
	zCList<spcTAnalysedVob>	vobList;
	CProgressCtrl*			ctrl_progress;	
public:
	zDWORD					num_vobs;				// vob-counter
	zDWORD					num_vobs_with_names;	// vobs with unexpected names
	zDWORD					size_of_vob;			// size of all vobs
	zDWORD					size_of_vobnames;		// size of all vobnames
	zDWORD					length_of_vobnames;		// length of all vobnames
public:
	spcCVobAnalyseCallback();
	~spcCVobAnalyseCallback();

	spcTAnalysedVob*	GetResult(int i);
	int					GetNumResults();
	void				RemoveResult(spcTAnalysedVob* item);

	void				InsertInfo(zSTRING msg);
	void				InsertWarning(zSTRING msg);

	virtual void Init(zCWorld* w, CProgressCtrl* progress=0);
	virtual void HandleVob(zCVob* vob, void *callbackData);
};

class spcCVobTidyCallback : public zCVobCallback
{
protected:		
	zCWorld*				world;	
	CProgressCtrl*			ctrl_progress;
public:
	spcCVobTidyCallback();
	~spcCVobTidyCallback();
	
	virtual void Init(zCWorld* w, CProgressCtrl* progress=0);
	virtual void HandleVob(zCVob* vob, void *callbackData);
};

class spcCWorldAnalyseDlg : public CDialog
{
	zCWorld* world;
	spcCVobAnalyseCallback	callback;
	spcCVobTidyCallback		tidyCallback;

// Konstruktion
public:
	void AnalyseWorld(zCWorld* w);
	spcCWorldAnalyseDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCWorldAnalyseDlg)
	enum { IDD = IDD_WORLD_ANALYSE };
	CProgressCtrl	ctrl_progress;
	CListBox	ctrl_list;	
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCWorldAnalyseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCWorldAnalyseDlg)
	afx_msg void OnSelchangeList();
	afx_msg void OnDblclkList();
	virtual BOOL OnInitDialog();
	afx_msg void OnFix();
	afx_msg void OnGotoVob();
	afx_msg void OnAnalyse();
	afx_msg void OnTidyVobs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCWORLDANALYSEDLG_H__2A8ABF01_032B_11D4_BA4F_0050DA339C1B__INCLUDED_

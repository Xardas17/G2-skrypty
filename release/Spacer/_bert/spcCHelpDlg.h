#if !defined(AFX_spcCHelpDlg_H__1E60AEC1_ED22_11D3_A405_0080AD209698__INCLUDED_)
#define AFX_spcCHelpDlg_H__1E60AEC1_ED22_11D3_A405_0080AD209698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCHelpDlg.h : Header-Datei
//

#include <afxdtctl.h>
#include <afxtempl.h>
#include "zstring.h"

#include "spcCWindowResizeStyle.h"

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCHelpDlg 


enum spcTHelpTopicType
{
	HELP_TOPIC_CLASS,
	HELP_TOPIC_MEMBER,
	HELP_TOPIC_MENU,
	HELP_TOPIC_WINDOW,
	HELP_TOPIC_TYPE_MAX
};

const zSTRING HELP_TOPIC_TYPE_STRING[HELP_TOPIC_TYPE_MAX] = 
{
	"CLASS","MEMBER","MENU","WINDOW"
};

const zSTRING HELP_CLASS_DELIMITER = "@";

class spcCHelpDlg : public CDialog
{
// Konstruktion
public:
	spcCHelpDlg(CWnd* pParent = NULL);   // Standardkonstruktor

	void ClearTopics();
	void SetHelpTopic(spcTHelpTopicType type, const zSTRING& topic);	

// Dialogfelddaten
	//{{AFX_DATA(spcCHelpDlg)
	enum { IDD = IDD_HELP_DLG };
	CEdit	ctrl_helptext;
	CString	m_helptext;
	//}}AFX_DATA

	CList<CString,CString&> topicList;


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	zSTRING help_pool;

	POSITION winID;

	CList<spcCWindowResizeStyle*,spcCWindowResizeStyle*> childResizeList;


	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCHelpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual void OnCancel();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_spcCHelpDlg_H__1E60AEC1_ED22_11D3_A405_0080AD209698__INCLUDED_

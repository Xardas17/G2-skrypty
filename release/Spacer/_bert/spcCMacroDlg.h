#if !defined(AFX_SPCCMACRODLG_H__2E5696E0_B254_11D3_B00B_0080AD209698__INCLUDED_)
#define AFX_SPCCMACRODLG_H__2E5696E0_B254_11D3_B00B_0080AD209698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spcCMacroDlg.h : Header-Datei
//


#include "zstring.h"
#include <afxtempl.h>

class CSpacerView;
class CSpacerDoc;

class spcCMacro
{
public:	
	void McCompileLight		(const zSTRING& parm);
	void McCompileWorld		(const zSTRING& parm);
	void McLoadWorldFile	(zSTRING filename);
	void McLoadMeshFile		(zSTRING filename);
	void McSaveWorldFile	(zSTRING filename, zBOOL compiled, zBOOL binary);
	void McSaveMeshFile		(zSTRING filename);
	
	spcCMacro();
	virtual ~spcCMacro();
	
	void Run(CSpacerDoc* _doc, CSpacerView* _view);

	CString		GetMacroProperties()				{ return props; }
	void		SetMacroProperties(CString _props)	{ props = _props; };

	CString		GetMacroName()						{ return name; }
	void		SetMacroName(CString _name)			{ name = _name; };

protected:

	bool RunCommand(zSTRING commandline, zSTRING answer);

	CString		props;
	CString		name;
private:	
	bool mcLoadFirstWorld;
	CSpacerView* view;
	CSpacerDoc* doc;
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld spcCMacroDlg 

class spcCMacroDlg : public CDialog
{
// Konstruktion
public:
	void LoadMacroFile(CString filename);
	void SaveMacroFile(CString filename);
	spcCMacro* SearchMacro(CString name, POSITION& pos);

	CList<spcCMacro*,spcCMacro*> macroList;

	spcCMacro* GetExecuteMacro();
	spcCMacroDlg(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(spcCMacroDlg)
	enum { IDD = IDD_MAKRODIALOG };	
	CButton	ctrl_new;
	CButton	ctrl_rename;
	CButton	ctrl_delete;
	CListBox	ctrl_list;
	CEdit	ctrl_edit;
	CString	m_edit;
	CString	m_list_entry;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(spcCMacroDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(spcCMacroDlg)
	afx_msg void OnDelete();
	afx_msg void OnChangeEdit();
	afx_msg void OnKillfocusEdit();
	afx_msg void OnDblclkList();
	afx_msg void OnSelchangeList();
	afx_msg void OnNew();
	virtual void OnOK();
	virtual void OnCancel();	
	virtual BOOL OnInitDialog();
	afx_msg void OnRename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	spcCMacro* executeMacro;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPCCMACRODLG_H__2E5696E0_B254_11D3_B00B_0080AD209698__INCLUDED_

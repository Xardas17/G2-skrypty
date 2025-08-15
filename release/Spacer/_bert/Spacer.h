// Spacer.h : main header file for the SPACER application
//

#if !defined(AFX_SPACER_H__64FA8006_27E8_11D2_88A8_444553540000__INCLUDED_)
#define AFX_SPACER_H__64FA8006_27E8_11D2_88A8_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "zcore.h"

/////////////////////////////////////////////////////////////////////////////
// CSpacerApp:
// See Spacer.cpp for the implementation of this class
//

class spcCWorkInfoDlg;
class zCOption;
class zFILE;

extern const char* SPC_APPLICATION_NAME;
extern const char* SPC_APPLICATION_DESCRIPTION;
extern const char* SPC_COMPANY_NAME;
extern const char* SPC_AUTHOR_NAMES;
extern const char* SPC_VERSION;
extern const char* SPC_YEAR_START;
extern const char* SPC_YEAR_END;
extern const char* SPC_COMPILE_DATE;
extern const char* SPC_COMPILE_TIME;

extern zFILE*			mainpath;
extern spcCWorkInfoDlg*	workingDlg;

const char INI_SECTION_SPACER[] = "spacer";



// Vob-Description: "zCVobTrigger(&345)" or "netCNpc(Born&82732)"
#define zVOB_DESCRIPTION(vob) \
	( (vob) ? (vob)->GetClassDef()->GetClassName_()+"("+(vob)->GetVobName()+"&"+zSTRING((vob)->GetVobID())+")" : "NULL")

class CSpacerApp : public CWinApp
{
public:
	void EnableDrawing(bool enable = true);
	CSpacerApp();
	virtual ~CSpacerApp();

	void Initialize(zTSystemContextHandle& handle);
	void Deinitialize();	

	virtual int Run( );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpacerApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpacerApp)
	afx_msg void OnAppAbout();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	bool enable_drawing;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPACER_H__64FA8006_27E8_11D2_88A8_444553540000__INCLUDED_)

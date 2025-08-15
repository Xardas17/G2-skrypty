// spcCSetGeneral.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCSetGeneral.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCSetGeneral dialog


spcCSetGeneral::spcCSetGeneral(CWnd* pParent /*=NULL*/)
	: CDialog(spcCSetGeneral::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCSetGeneral)
	m_use_grid = FALSE;
	m_rot_grid = 0.0f;
	m_move_grid = 0;
	m_tex_move_grid = 0;
	m_tex_use_grid = FALSE;
	m_tex_rot_grid = 0.0f;
	m_interative_save = FALSE;
	m_goldmaster = FALSE;
	//}}AFX_DATA_INIT
}


void spcCSetGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCSetGeneral)
	DDX_Control(pDX, IDC_USE_TEX_GRID, ctrl_use_tex_grid);
	DDX_Control(pDX, IDC_MOVE_SPEED, ctrl_movespeed);
	DDX_Check(pDX, IDC_USE_GRID, m_use_grid);
	DDX_Text(pDX, IDC_ROTGRID, m_rot_grid);
	DDX_Text(pDX, IDC_MOVEGRID, m_move_grid);
	DDX_Text(pDX, IDC_TEX_MOVEGRID, m_tex_move_grid);
	DDX_Check(pDX, IDC_USE_TEX_GRID, m_tex_use_grid);
	DDX_Text(pDX, IDC_TEX_ROTGRID, m_tex_rot_grid);
	DDX_Check(pDX, IDC_SAVE_INTERATIVE, m_interative_save);
	DDX_Check(pDX, IDC_GOLDMASTER, m_goldmaster);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCSetGeneral, CDialog)
	//{{AFX_MSG_MAP(spcCSetGeneral)
	ON_BN_CLICKED(IDC_USE_TEX_GRID, OnUseTexGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCSetGeneral message handlers

BOOL spcCSetGeneral::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ctrl_movespeed.SetRangeMax(100);
	ctrl_movespeed.SetRangeMin(1);
	ctrl_movespeed.SetLineSize(5);
	ctrl_movespeed.SetPageSize(10);
	ctrl_movespeed.SetPos((long)m_movespeed);
	ctrl_movespeed.SetTicFreq(10);
	
	OnUseTexGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void spcCSetGeneral::OnOK() 
{
	m_movespeed = ctrl_movespeed.GetPos();
	CDialog::OnOK();
}


void spcCSetGeneral::SetMovespeed(int value)
{
	m_movespeed = value;
}


int spcCSetGeneral::GetMovespeed()
{
	return m_movespeed;
}

void spcCSetGeneral::OnUseTexGrid() 
{
	UpdateData(TRUE);	
	if (m_tex_use_grid) ctrl_use_tex_grid.SetWindowText("move-grid ON, rot-grid OFF");
	else ctrl_use_tex_grid.SetWindowText("move-grid OFF, rot-grid ON");
	UpdateData(FALSE);
}

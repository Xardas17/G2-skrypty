// spcCSetView.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "spcCSetView.h"

#include "zrenderer.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spcCSetView dialog


spcCSetView::spcCSetView(CWnd* pParent /*=NULL*/)
	: CDialog(spcCSetView::IDD, pParent)
{
	//{{AFX_DATA_INIT(spcCSetView)		
	//}}AFX_DATA_INIT
}


void spcCSetView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCSetView)
	DDX_Control(pDX, IDC_VIDEO_RESOLUTION, ctrl_video_resolution);
	DDX_Control(pDX, IDC_VIDEO_DEVICE, ctrl_video_device);		
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCSetView, CDialog)
	//{{AFX_MSG_MAP(spcCSetView)
	ON_CBN_SELCHANGE(IDC_VIDEO_DEVICE, OnSelchangeVideoDevice)
	ON_CBN_SELCHANGE(IDC_VIDEO_RESOLUTION, OnSelchangeVideoResolution)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spcCSetView message handlers

BOOL spcCSetView::OnInitDialog() 
{
	CDialog::OnInitDialog();			

	zTRnd_DeviceInfo info;
	zBOOL result;
	int count = zrenderer->Vid_GetNumDevices();
	for (int nr=0;nr<count;nr++)
	{
		result = zrenderer->Vid_GetDeviceInfo(info,nr);		
		if (result) ctrl_video_device.AddString(info.deviceName.ToChar());		
	}

	ctrl_video_resolution.EnableWindow(TRUE);

	int devNr = zrenderer->Vid_GetActiveDeviceNr();
	ctrl_video_device.SetCurSel(devNr);
	OnSelchangeVideoDevice();

	ctrl_video_device.EnableWindow(FALSE);
	// ctrl_video_device.EnableWindow(TRUE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void spcCSetView::OnOK() 
{	
	CDialog::OnOK();
}

void spcCSetView::OnSelchangeVideoDevice() 
{
	ctrl_video_resolution.ResetContent();
	zTRnd_VidModeInfo info;
	zBOOL result;

	int currentModeNr=-1;

	int count = zrenderer->Vid_GetNumModes();
	for (int nr=0;nr<count;nr++)
	{
		result = zrenderer->Vid_GetModeInfo(info,nr);
		if (result)
		{
			CString s;
			s.Format("%i:%i (%i bit)",info.xdim,info.ydim,info.bpp);						
			if (info.xdim == m_view_x && info.ydim == m_view_y && info.bpp == m_view_bpp)
			{
				currentModeNr = nr;
				s = s + " *";
			};
			ctrl_video_resolution.AddString(s);
		}		
	}	

	ctrl_video_resolution.EnableWindow();	
	if (currentModeNr>=0) ctrl_video_resolution.SetCurSel(currentModeNr);
}

void spcCSetView::SetVideo(int device, int resolution)
{
	ctrl_video_device.SetCurSel(device);
	OnSelchangeVideoDevice();
	ctrl_video_resolution.SetCurSel(resolution);
}

void spcCSetView::GetVideo(int &device, int &resolution)
{
}

void spcCSetView::OnSelchangeVideoResolution() 
{	
	int modeNr = ctrl_video_resolution.GetCurSel();
	zTRnd_VidModeInfo info;
	zrenderer->Vid_GetModeInfo(info,modeNr);
	m_view_x = info.xdim;
	m_view_y = info.ydim;
	m_view_bpp = info.bpp;
	UpdateData(false);
}

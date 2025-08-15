// spcCInfoBar_Lights.cpp : implementation file
//

#include "stdafx.h"

#include "zengine.h"

#include "Spacer.h"
#include "mainfrm.h"
#include "SpacerDoc.h"
#include "SpacerView.h"
#include "spcCInfoBar_Lights.h"
#include "spcCInputDialog.h"
#include "spcCInfoBar.h"

#include "zarchiver.h"


// z-files
#include "z3d.h"
#include "zoption.h"
#include "zworld.h"


#ifdef _DEBUG
////#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// spcCInfoBar_Lights dialog


spcCInfoBar_Lights::spcCInfoBar_Lights(CWnd* pParent /*=NULL*/)
	: CDialog(spcCInfoBar_Lights::IDD, pParent), selPreset(NULL), vobPreset(NULL)
{
	zERR_MESSAGE(7,zERR_BEGIN,"B: SPC: Constructing Instance of LightsPage...");

	//{{AFX_DATA_INIT(spcCInfoBar_Lights)
	m_color_chps = 0;
	m_color_smooth = FALSE;
	m_light_dyn = FALSE;
	m_range_smooth = FALSE;
	m_light_static = FALSE;
	m_range_chps = 0;
	m_name = _T("");
	text_tovob = _T("");
	text_label = _T("");
	m_curvob_preset_name = _T("");
	//}}AFX_DATA_INIT
	cur_vob = NULL;
	text_tovob = "";
	text_label = "";
	m_pLastVobLight = NULL;
	m_bShowWireFrame	= FALSE;
	m_bLightDynCompile	= FALSE;

	zERR_MESSAGE(7,zERR_END,"");
}

spcCInfoBar_Lights::~spcCInfoBar_Lights()
{
	zRELEASE(this->m_pLastVobLight);
};


void spcCInfoBar_Lights::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spcCInfoBar_Lights)
	DDX_Control(pDX, IDC_PRESET_REAPPLY, ctrl_reapply);
	DDX_Control(pDX, IDC_APPLY, ctrl_button_apply);
	DDX_Control(pDX, IDC_STATIC_LIGHT, ctrl_select_static);
	DDX_Control(pDX, IDC_DYNAMIC_LIGHT, ctrl_select_dynamic);
	DDX_Control(pDX, IDC_NAME, ctrl_name);
	DDX_Control(pDX, IDC_COLOR_SMOOTH, ctrl_color_smooth);
	DDX_Control(pDX, IDC_RANGE_SMOOTH, ctrl_range_smooth);
	DDX_Control(pDX, IDC_RANGE_DEL, ctrl_range_del);
	DDX_Control(pDX, IDC_RANGE_CHPS, ctrl_range_chps);
	DDX_Control(pDX, IDC_RANGE_ADD, ctrl_range_add);
	DDX_Control(pDX, IDC_COLOR_DEL, ctrl_color_del);
	DDX_Control(pDX, IDC_COLOR_CHPS, ctrl_color_chps);
	DDX_Control(pDX, IDC_COLOR_ADD, ctrl_color_add);
	DDX_Control(pDX, IDC_PRESET_UPDATE_FROM_CURRENT, ctrl_button_update_preset);
	DDX_Control(pDX, IDC_PRESET_ASSIGN_TO_CURRENT, ctrl_button_update_light);
	DDX_Control(pDX, IDC_COLOR_DOWN, ctrl_color_down);
	DDX_Control(pDX, IDC_COLOR_UP, ctrl_color_up);	
	DDX_Control(pDX, IDC_PROP_GROUP, ctrl_prop_group);
	DDX_Control(pDX, IDC_COLOR_LIST, ctrl_color_list);
	DDX_Control(pDX, IDC_RANGE_LIST, ctrl_range_list);
	DDX_Control(pDX, IDC_PRESET_LIST, ctrl_preset_list);
	DDX_Control(pDX, IDC_LIGHT_DYN_QUALITY, ctrl_light_dyn_quality);
	DDX_Text(pDX, IDC_COLOR_CHPS, m_color_chps);
	DDX_Check(pDX, IDC_COLOR_SMOOTH, m_color_smooth);
	DDX_Check(pDX, IDC_DYNAMIC_LIGHT, m_light_dyn);
	DDX_Check(pDX, IDC_RANGE_SMOOTH, m_range_smooth);
	DDX_Check(pDX, IDC_STATIC_LIGHT, m_light_static);
	DDX_Text(pDX, IDC_RANGE_CHPS, m_range_chps);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_TOVOB, text_tovob);
	DDX_Text(pDX, IDC_TOVOB_LABEL, text_label);
	DDX_Text(pDX, IDC_VOB_PRESET_NAME, m_curvob_preset_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spcCInfoBar_Lights, CDialog)
	//{{AFX_MSG_MAP(spcCInfoBar_Lights)
	ON_BN_CLICKED(IDC_FILTER_BUTTON, OnFilterButton)
	ON_BN_CLICKED(IDC_COLOR_ADD, OnColorAdd)
	ON_BN_CLICKED(IDC_COLOR_DEL, OnColorDel)
	ON_LBN_SELCHANGE(IDC_COLOR_LIST, OnSelchangeColorList)
	ON_BN_CLICKED(IDC_RANGE_ADD, OnRangeAdd)
	ON_BN_CLICKED(IDC_RANGE_DEL, OnRangeDel)
	ON_LBN_SELCHANGE(IDC_RANGE_LIST, OnSelchangeRangeList)
	ON_BN_CLICKED(IDC_PRESET_NEW, OnPresetNew)	
	ON_LBN_DBLCLK(IDC_COLOR_LIST, OnDblclkColorList)
	ON_LBN_DBLCLK(IDC_RANGE_LIST, OnDblclkRangeList)
	ON_BN_CLICKED(IDC_DYNAMIC_LIGHT, OnDynamicLight)
	ON_BN_CLICKED(IDC_STATIC_LIGHT, OnStaticLight)
	ON_LBN_SELCHANGE(IDC_PRESET_LIST, OnSelchangePresetList)
	ON_LBN_DBLCLK(IDC_PRESET_LIST, OnDblclkPresetList)
	ON_BN_CLICKED(IDC_PRESET_REMOVE, OnPresetRemove)
	ON_EN_CHANGE(IDC_COLOR_CHPS, OnChangeColorChps)
	ON_BN_CLICKED(IDC_COLOR_SMOOTH, OnColorSmooth)
	ON_CBN_SELCHANGE(IDC_LIGHT_DYN_QUALITY, OnSelchangeLightDynQuality)
	ON_EN_CHANGE(IDC_RANGE_CHPS, OnChangeRangeChps)
	ON_BN_CLICKED(IDC_RANGE_SMOOTH, OnRangeSmooth)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)	
	ON_BN_CLICKED(IDC_COLOR_DOWN, OnColorDown)
	ON_BN_CLICKED(IDC_COLOR_UP, OnColorUp)	
	ON_BN_CLICKED(IDC_PRESET_UPDATE_FROM_CURRENT, OnUpdatePresetByVob)
	ON_BN_CLICKED(IDC_PRESET_ASSIGN_TO_CURRENT, OnUpdateVobByPreset)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_PRESET_REAPPLY, OnPresetReapply)
	ON_BN_CLICKED(IDC_LIGHT_SHOWRANGES, OnLightShowranges)
	ON_BN_CLICKED(IDC_LIGHT_DYNAMIC_COMPILE, OnLightDynamicCompile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




void spcCInfoBar_Lights::OnFilterButton() 
{
	// TODO: Add your control notification handler code here
	
}

void spcCInfoBar_Lights::OnColorAdd() 
{
	UpdateData(true);
	int index = ctrl_color_list.GetCurSel();
	COLORREF color = RGB(255,0,0);
	CColorDialog dlg(color);
	if (dlg.DoModal()==IDOK)
	{
		color = dlg.GetColor();
		if ((index==LB_ERR) || (index<0)) 
		{
			ctrl_color_list.AddColor(GetRValue(color),GetGValue(color),GetBValue(color));
		}
		else 
		{
			ctrl_color_list.InsertColor(index+1,GetRValue(color),GetGValue(color),GetBValue(color));
		}
		ctrl_color_list.SetCurSel(index+1);
	};
	

	// UpdateLightData();

	UpdateData(false);		
}

void spcCInfoBar_Lights::OnColorDel() 
{	
	int index = ctrl_color_list.GetCurSel();
	if ((index>=0) && (index!=LB_ERR) && (ctrl_color_list.GetCount()>1))
	{
		ctrl_color_list.DeleteString(index);
		if (index>1) index--;
		ctrl_color_list.SetCurSel(index);
		
		// UpdateLightData();

	}
}


void spcCInfoBar_Lights::OnColorDown() 
{
	int index = ctrl_color_list.GetCurSel();
	if ((index>=0) && (index!=LB_ERR) && index<ctrl_color_list.GetCount())
	{
		int r,g,b;
		ctrl_color_list.GetColor(index, r,g,b);
		ctrl_color_list.DeleteString(index);
		ctrl_color_list.InsertColor(index+1,r,g,b);
		ctrl_color_list.SetCurSel(index+1);	

		// UpdateLightData();

	}
}

void spcCInfoBar_Lights::OnColorUp() 
{
	int index = ctrl_color_list.GetCurSel();
	if ((index>0) && (index!=LB_ERR))
	{
		int r,g,b;
		ctrl_color_list.GetColor(index, r,g,b);
		ctrl_color_list.DeleteString(index);
		ctrl_color_list.InsertColor(index-1,r,g,b);
		ctrl_color_list.SetCurSel(index-1);
		
		// UpdateLightData();
	}
}

void spcCInfoBar_Lights::OnSelchangeColorList() 
{
	//CSpacerView::view->SetActiveWindow();
	//CSpacerView::view->SetFocus();
}

void spcCInfoBar_Lights::OnRangeAdd() 
{
	int index = ctrl_range_list.GetCurSel();
	spcCInputDialog dlg;
	if (dlg.DoModal()==IDOK)
	{						
		float valueInt = (float)atof(dlg.GetUpperInput().GetBuffer(0));
		CString valueStr;
		valueStr.Format("%.4f",valueInt);

		if ((index==LB_ERR) || (index<0)) 
			ctrl_range_list.AddString(valueStr);
		else 
			ctrl_range_list.InsertString(index+1,valueStr);

		ctrl_range_list.SetCurSel(index+1);
	}	

	// UpdateLightData();
}

void spcCInfoBar_Lights::OnRangeDel() 
{
	int index = ctrl_range_list.GetCurSel();
	if ((index>=0) && (index!=LB_ERR) && (ctrl_range_list.GetCount()>1))
	{
		ctrl_range_list.DeleteString(index);			
		if (index>1) index--;
		ctrl_range_list.SetCurSel(index);
	}

	// UpdateLightData();
}

void spcCInfoBar_Lights::OnSelchangeRangeList() 
{
	//CSpacerView::view->SetActiveWindow();
	//CSpacerView::view->SetFocus();
}

void spcCInfoBar_Lights::OnPresetRemove() 
{
	int index = ctrl_preset_list.GetCurSel();
	if (index==LB_ERR) return;
	ctrl_preset_list.DeleteString(index);
	ctrl_preset_list.SetCurSel(-1);
	zCVobLight::lightPresetList.RemoveIndex(index);
}

void spcCInfoBar_Lights::OnPresetNew() 
{
	UpdateData(true);	
	spcCInputDialog namedlg;
	namedlg.SetInput("new");
	bool repeat;	
	zSTRING name;
	zCArchiver* arch = zarcFactory.CreateArchiverWrite(zARC_MODE_ASCII_PROPS);
	do
	{
		repeat = false;
		if (namedlg.DoModal()==IDOK)	
		{
			name = zSTRING(namedlg.GetUpperInput().GetBuffer(0));
			if ( (name=="") || (!arch->IsStringValid(name.ToChar()))) repeat=true;
			else for (int i=0; i<zCVobLight::lightPresetList.GetNumInList(); i++) 	
					if (zCVobLight::lightPresetList[i]->GetName() == name) repeat=true;						
		}
	} while (repeat);	

	arch->Close();
	zRELEASE(arch);
		
	// Preset erzeugen					
	zCVobLight* light =  new zCVobLight;
	
	if (cur_vob)
	{
		spcCInfoBar_Lights::UpdateVobByData(light);
	};

	UpdateVobByData(light);
	light->AddThisToPresetList(name);
	zRELEASE(light);			
	
	CreatePresetList();

	ctrl_preset_list.SelectString(0,name.ToChar());
	OnSelchangePresetList();	

	UpdateData(false);
	UpdateWindow();	

}


void spcCInfoBar_Lights::OnUpdatePresetByVob() 
{
	UpdateData(true);

	if (!cur_vob) return;

	// Ein Vob wurde angewaehlt und dessen Daten liegen
	// nun im Dialog vor. Ein zuvor ausgewaehltes 
	// Preset soll dessen Daten erhalten		
	
	UpdatePresetByData(selPreset);

	UpdateData(false);	
}

void spcCInfoBar_Lights::UpdateVobByPreset(zCVobLight* vob)
{
	UpdateData(true);
	if (!selPreset || !vob) return;

	if (m_preset_name=="") return;
	
	// Ein Vob wurde angewaehlt und dessen Daten liegen
	// nun im Dialog vor. Von einem zuvor ausgewaehltem
	// Preset sollen nun aber die Eigenschaften des
	// Vobs uebernommen werden.

	SetDataByPreset(selPreset);
	
	vob->SetByPreset(selPreset->GetName());
	vob->SetVobPresetName(selPreset->GetName());		
	m_curvob_preset_name=CString(selPreset->GetName().ToChar());

	ResetVobLighting(vob);
	UpdateData(false);
};

void spcCInfoBar_Lights::OnUpdateVobByPreset()
{
	UpdateVobByPreset(cur_vob);
	if (cur_vob == this->m_pLastVobLight) CheckWireFrameLight(cur_vob);
}

zCVob* spcCInfoBar_Lights::CreateNewVob()
{		
	UpdateData(true);	
	
	zCVobLight* new_vob = new zCVobLight;		

	new_vob->SetCollDet(FALSE);
	new_vob->SetSleeping(TRUE);
	new_vob->SetPhysicsEnabled(FALSE);
	new_vob->SetPositionWorld(0,0,0);
	
	if (selPreset)
	{
		UpdateVobByPreset(new_vob);	
	}
	else
	{
		UpdateVobByData(new_vob);
	};
	
	UpdateData(false);
	return (zCVob*)new_vob;
}

void spcCInfoBar_Lights::SelectVob(zCVob * pickedVob)
{	
	zCVob* avob = pickedVob;

	pickedVob = dynamic_cast<zCVobLight*>(avob);
	
	UpdateData(true);

	if (pickedVob)
	{								
		cur_vob=(zCVobLight*)pickedVob;

		m_curvob_preset_name = CString(cur_vob->GetVobPresetName().ToChar());

		ctrl_prop_group.SetWindowText("Selected Lightvob");
		ctrl_prop_group.ShowWindow(TRUE);

		ctrl_name.EnableWindow(TRUE);
		
		SetDataByVob(cur_vob);			
	}
	else
	{		
		UpdateData(true);		
		
		if (selPreset) 
		{
			ctrl_prop_group.SetWindowText("Selected Preset");
			ctrl_prop_group.ShowWindow(FALSE);
		}
		else 
		{
			ctrl_prop_group.SetWindowText("No Preset of Vob selected");
			ctrl_prop_group.ShowWindow(FALSE);
		}

		cur_vob = 0;		

		ctrl_name.EnableWindow(FALSE);				
	}

	ctrl_button_apply.EnableWindow(cur_vob!=NULL);

	// Daten setzen
	vobPreset = 0;
	selPreset = 0;
	zSTRING lightPresetName;
	if (m_preset_name.GetLength()>0)
	{
		for (int i=0; i<zCVobLight::lightPresetList.GetNumInList(); i++)
		{
			lightPresetName = zCVobLight::lightPresetList[i]->GetName();
			// Lightpreset des ausgewaehlten Presets waehlen
			if (CString(lightPresetName.ToChar())==m_preset_name )
			{					
				selPreset = zCVobLight::lightPresetList[i];
				if (!cur_vob) SetDataByPreset(selPreset);
			}
			// Lightpreset des Vobs waehlen
			if (cur_vob && (lightPresetName==cur_vob->GetVobPresetName()))
			{					
				vobPreset = zCVobLight::lightPresetList[i];
			}
		}
	}		

	m_preset_name="";	
	if (selPreset) m_preset_name = selPreset->GetName().ToChar(); 

	m_curvob_preset_name="";
	if (vobPreset) m_curvob_preset_name = vobPreset->GetName().ToChar();

	ctrl_button_update_preset.EnableWindow(cur_vob && m_preset_name.GetLength()>0);
	ctrl_button_update_light.EnableWindow(cur_vob && m_preset_name.GetLength()>0);

	UpdateData(false);		

	ctrl_reapply.EnableWindow(!m_preset_name.IsEmpty());

	UpdateWindow();

	CheckWireFrameLight(pickedVob);
}

void spcCInfoBar_Lights::ConnectionTo(zCVob* vob)
{
	if (vob && !dynamic_cast<zCVobLight*>(vob))
	{
		text_label = "connect light to vob:";
	
		if (vob->GetVobName()!="") 
			text_tovob = vob->GetVobName().ToChar();
		else 	
			text_tovob = vob->GetClassName_().ToChar();	
	}
	else
	{
		text_label = "";
		text_tovob = "";
	}
	UpdateData(false);
}

void spcCInfoBar_Lights::OnDblclkColorList() 
{
	// UpdateLightData();
}

void spcCInfoBar_Lights::OnDblclkRangeList() 
{
	int index = ctrl_range_list.GetCurSel();
	if (index==LB_ERR) return;
	
	CString s;
	ctrl_range_list.GetText(index,s);

	spcCInputDialog dlg;
	dlg.SetInput(s);
	if (dlg.DoModal()==IDOK)
	{
		float valueInt = (float)atof(dlg.GetInput().GetBuffer(0));
		CString valueStr;
		if (index>0) valueStr.Format("%.4f",valueInt);
		else valueStr.Format("%i",(int)valueInt);

		ctrl_range_list.DeleteString(index);
		ctrl_range_list.InsertString(index,valueStr);
	}
	// UpdateLightData();
}

void spcCInfoBar_Lights::OnDynamicLight() 
{
	UpdateData(true);	
	m_light_static = !m_light_dyn;
	UpdateData(false);
	ctrl_light_dyn_quality.EnableWindow(m_light_dyn);

	// UpdateLightData();
}

void spcCInfoBar_Lights::OnStaticLight() 
{
	UpdateData(true);	
	m_light_dyn = !m_light_static;
	UpdateData(false);
	ctrl_light_dyn_quality.EnableWindow(m_light_dyn);

	// UpdateLightData();
}

BOOL spcCInfoBar_Lights::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ctrl_range_list.ResetContent();
	ctrl_range_list.AddString("10000");	
	ctrl_range_list.SetCurSel(0);
	ctrl_color_list.ResetContent();
	ctrl_color_list.AddColor(255,0,0);
	ctrl_color_list.SetCurSel(0);
	{
		zCVobLightPreset* preset = new zCVobLightPreset();
		UpdatePresetByData(preset);
		SetDataByPreset(preset);		
		zRELEASE(preset);
	}

	CreatePresetList();	
	
	ctrl_reapply.EnableWindow(FALSE);

	SelectVob(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void spcCInfoBar_Lights::SetDataByPreset(zCVobLightPreset * preset)
{
	zCVobLightData * data = &(preset->lightData);

	///
	// Rangelist erzeugen
	///
	ctrl_range_list.ResetContent();

	// zuerst dem Startwert
	CString s;s.Format("%i",(int)data->GetRangeFixed());	
	ctrl_range_list.AddString(s);
	
	// Nun die Animationliste
	int num = data->rangeAniScaleList.GetNumInList();
	for (int i=0;i<num;i++)
	{		
		s.Format("%.4f",data->rangeAniScaleList[i]);
		ctrl_range_list.AddString(s);		
	}
	
	///
	// Colorliste erzeugen
	///
	ctrl_color_list.ResetContent();	
	zCOLOR col;

	// Entweder die Animationsliste
	if (data->colorAniList.GetNumInList()>1)
	{
		num = data->colorAniList.GetNumInList();
		for (i=0;i<num;i++)
		{		
			col = data->colorAniList[i];		
			ctrl_color_list.AddColor(col.r,col.g,col.b);
		}
	}
	// oder den einen Wert
	else
	{
		col = data->GetColor();
		ctrl_color_list.AddColor(col.r,col.g,col.b);
	}
	
	///
	// weitere Daten
	///
	m_name = "";
	m_color_chps	= data->GetColorAniFPS();
	m_range_chps	= data->GetRangeAniFPS();
	m_color_smooth	= (data->GetColorAniSmooth()==TRUE);
	m_range_smooth	= (data->GetRangeAniSmooth()==TRUE);
	m_light_static	= (data->GetIsStatic()==TRUE);
	m_light_dyn		= !m_light_static;

	switch (data->GetLightQuality())
	{
	case zVOBLIGHT_QUAL_HI		: ctrl_light_dyn_quality.SetCurSel(0); break;
	case zVOBLIGHT_QUAL_MID		: ctrl_light_dyn_quality.SetCurSel(1); break;
	case zVOBLIGHT_QUAL_FASTEST	: ctrl_light_dyn_quality.SetCurSel(2); break;
	}	

	ctrl_light_dyn_quality.EnableWindow(m_light_dyn);

	UpdateData(false);
}

void spcCInfoBar_Lights::SetDataByVob(zCVob * vob)
{
	m_name="";
	zCVobLight* lightVob = dynamic_cast<zCVobLight*>(vob);
	if (lightVob) 
	{		
		m_name = CString(lightVob->GetVobName().ToChar());
		SetDataByLightData(&lightVob->lightData);
	}
	UpdateData(false);
}

void spcCInfoBar_Lights::SetDataByLightData(zCVobLightData* data)
{
	if (!data) 
	{
		zERR_WARNING("B: SPC: SetDataByLightData was called with NULL-Pointer");
		return;
	}	

	///
	// Rangelist erzeugen
	///

	ctrl_range_list.ResetContent();

	// den Startewert...
	CString s;s.Format("%i",(int)data->GetRangeFixed());
	ctrl_range_list.AddString(s);
	
	// Die Multiplikatoren ...
	int num = data->rangeAniScaleList.GetNumInList();
	for (int i=0;i<num;i++)
	{		
		s.Format("%.4f",data->rangeAniScaleList[i]);
		ctrl_range_list.AddString(s);
	}
	
	///
	// Colorliste erzeugen
	///

	ctrl_color_list.ResetContent();
	
	zCOLOR col;
	// Entweder die Animationsliste
	if (data->colorAniList.GetNumInList()>1)
	{
		num = data->colorAniList.GetNumInList();
		for (i=0;i<num;i++)
		{		
			col = data->colorAniList[i];		
			ctrl_color_list.AddColor(col.r,col.g,col.b);
		}
	}
	// oder den einen Wert
	else
	{
		col = data->GetColor();
		ctrl_color_list.AddColor(col.r,col.g,col.b);
	}

	///
	// Weitere Werte
	///
	m_color_chps	= data->GetColorAniFPS();
	m_range_chps	= data->GetRangeAniFPS();
	m_color_smooth	= (data->GetColorAniSmooth()==TRUE);
	m_range_smooth	= (data->GetRangeAniSmooth()==TRUE);
	m_light_static	= (data->GetIsStatic()==TRUE);
	m_light_dyn		= !m_light_static;

	switch (data->GetLightQuality())
	{
	case zVOBLIGHT_QUAL_HI		: ctrl_light_dyn_quality.SetCurSel(0); break;
	case zVOBLIGHT_QUAL_MID		: ctrl_light_dyn_quality.SetCurSel(1); break;
	case zVOBLIGHT_QUAL_FASTEST	: ctrl_light_dyn_quality.SetCurSel(2); break;
	}	
	
	// CreatePresetList();

	ctrl_light_dyn_quality.EnableWindow(m_light_dyn);

	UpdateData(false);
}

void spcCInfoBar_Lights::UpdatePresetByData(zCVobLightPreset * preset)
{
	UpdateData(true);

	CString s;
	int index;
	
	preset->lightData.SetIsStatic(m_light_static);	
	
	index = ctrl_light_dyn_quality.GetCurSel();
	switch (index)
	{
	case 0: preset->lightData.SetLightQuality(zVOBLIGHT_QUAL_HI);break;
	case 1: preset->lightData.SetLightQuality(zVOBLIGHT_QUAL_MID);break;
	case 2: preset->lightData.SetLightQuality(zVOBLIGHT_QUAL_FASTEST);break;
	default:preset->lightData.SetLightQuality(zVOBLIGHT_QUAL_MID);break;
	}
		
	// Range-Settings
	ctrl_range_list.GetText(0,s);
	preset->lightData.SetRange(zSTRING(s.GetBuffer(0)).ToFloat());	
	preset->lightData.SetRangeAniLoop(ctrl_range_list.GetCount()>1);
	preset->lightData.SetRangeAniFPS(float(m_range_chps));
	preset->lightData.SetRangeAniSmooth(m_range_smooth);
	
	// Range-Ani
	preset->lightData.rangeAniScaleList.DeleteList();
	int num = ctrl_range_list.GetCount();
	if (num>1)
	{
		for (int i=1;i<num;i++)
		{
			ctrl_range_list.GetText(i,s);
			preset->lightData.rangeAniScaleList.InsertEnd(zSTRING(s.GetBuffer(0)).ToFloat());			
		}
	}

	// color settings	
	int r,g,b;	
	if (ctrl_color_list.GetCount()<=0) ctrl_color_list.AddColor(255,0,0);
	bool isColorAnimated = ctrl_color_list.GetCount()>1;
	
	ctrl_color_list.GetColor(0, r,g,b);
	preset->lightData.SetColor(r,g,b);
	preset->lightData.SetColorAniLoop(isColorAnimated);
	preset->lightData.SetColorAniFPS(float(m_color_chps));
	preset->lightData.SetColorAniSmooth(m_color_smooth);
	
	// set loop-array
	preset->lightData.colorAniList.DeleteList();	
	if (isColorAnimated)
	{		
		for (int i=0;i<ctrl_color_list.GetCount();i++)
		{
			ctrl_color_list.GetColor(i,r,g,b);
			preset->lightData.colorAniList.InsertEnd(zCOLOR(r,g,b,0));
		}		
	}

	UpdateData(false);
}

void spcCInfoBar_Lights::OnSelchangePresetList() 
{
	m_preset_name="";

	int index = ctrl_preset_list.GetCurSel();
	if (index!=LB_ERR) 
	{
		ctrl_preset_list.GetText(index,m_preset_name);
	}

	ctrl_reapply.EnableWindow(!m_preset_name.IsEmpty());

	UpdateData(false);

	// CSpacerView::view->VobSelect(0,false);
	SelectVob(0);
}

void spcCInfoBar_Lights::OnDblclkPresetList() 
{
	
}

void spcCInfoBar_Lights::UpdateVobByData(zCVobLight* vob)
{	
	if (!vob) return;
	UpdateData(true);
	
	zCVobLightPreset* preset = new zCVobLightPreset();				
	UpdatePresetByData(preset);
	vob->lightData = preset->lightData;		
	zRELEASE(preset);

	if (m_name!="") vob->SetVobName(zSTRING(m_name.GetBuffer(0)));

	ResetVobLighting(vob);

	UpdateData(false);		
}

void spcCInfoBar_Lights::OnChangeColorChps() 
{	
	// UpdateLightData();
}

void spcCInfoBar_Lights::OnColorSmooth() 
{	
	// UpdateLightData();
}

void spcCInfoBar_Lights::OnSelchangeLightDynQuality() 
{
	// UpdateLightData();
	// CSpacerView::view->SetActiveWindow();
	// CSpacerView::view->SetFocus();
}

void spcCInfoBar_Lights::OnChangeRangeChps() 
{
	// UpdateLightData();
}

void spcCInfoBar_Lights::OnRangeSmooth() 
{
	// UpdateLightData();
}

void spcCInfoBar_Lights::OnChangeName() 
{	
		
}

void spcCInfoBar_Lights::OnOK() 
{
	// prevent that ENTER will close the dialog
	// CDialog::OnOK();
}


void spcCInfoBar_Lights::CreatePresetList()
{
	UpdateData(true);
	
	CString selected_item = m_preset_name;
	
	ctrl_preset_list.ResetContent();
	ctrl_preset_list.SetCurSel(-1);
	for (int i=0; i<zCVobLight::lightPresetList.GetNumInList(); i++) 
	{
		ctrl_preset_list.AddString(CString(zCVobLight::lightPresetList[i]->GetName().ToChar()));
	};

	ctrl_preset_list.SelectString(0,m_preset_name);
	
	UpdateData(false);
}


void spcCInfoBar_Lights::UpdateLightData()
{
	if (selPreset) 
	{
		UpdatePresetByData(selPreset);
	}
	else if (cur_vob)
	{
		UpdateVobByData(cur_vob);
	}
}

void spcCInfoBar_Lights::OnApply() 
{
	if (!cur_vob) return;

	UpdateVobByData(cur_vob);			

	if (CMainFrame::mainframe) 
	{
		CMainFrame::mainframe->HandleObjChange(cur_vob,UPDATE_OBJECT_SHEET | UPDATE_FOCUS);
	}
}



void spcCInfoBar_Lights::HandleVobSelect(zCVob* vob)
{
	SelectVob(vob);
};

void spcCInfoBar_Lights::CheckWireFrameLight(zCVob *a_pVobLight)
{
	zCVobLight *light = zDYNAMIC_CAST<zCVobLight>(a_pVobLight);

	if ( light )
	{
//		if (m_pLastVobLight == light)  return;

		if (m_pLastVobLight) 
		{
			m_pLastVobLight->SetShowLightSphere(FALSE);
			zRELEASE(m_pLastVobLight);
		}

		if ( GetShowLightsWireFramed() )
		{
			light->SetShowLightSphere(TRUE);
		}

		m_pLastVobLight = light;
		m_pLastVobLight->AddRef();
	}
	else if (m_pLastVobLight) // ein anderes Vob wurde selektiert/eingefügt
	{
		m_pLastVobLight->SetShowLightSphere(FALSE);
		zRELEASE(m_pLastVobLight)
	}
	
};


void spcCInfoBar_Lights::HandleVobInsert(zCVob* vob, zCVob* parentVob)
{	
	CheckWireFrameLight(vob);
};

void spcCInfoBar_Lights::HandleVobRemove(zCVob* vob)
{
	if (vob == cur_vob) HandleVobSelect(0);
	if (m_pLastVobLight && vob==m_pLastVobLight)
	{
		m_pLastVobLight->SetShowLightSphere(FALSE);
		zRELEASE(m_pLastVobLight);
	}
};


void spcCInfoBar_Lights::OnPresetReapply() 
{	
	if (!CMainFrame::mainframe) return;
	if (!CMainFrame::mainframe->GetInfoBar()) return;
	zCWorld* world = CMainFrame::mainframe->GetInfoBar()->GetActiveWorld();
	if (!world) return;
	if (m_preset_name.IsEmpty()) return;

	zSTRING presetName(m_preset_name.GetBuffer(0));
	presetName.Upper();
	zSTRING presetInUse;

	zCClassDef* lightClassdef = zCVobLight::GetStaticClassDef();
	zCVobLight* vob;
	
	zCArray<zCVob*> result;
		
	world->SearchVobListByClass(lightClassdef,result);		

	int num = result.GetNumInList();

	zERR_MESSAGE(6,zERR_BEGIN,"B: SPC: Updating lights with preset "+presetName);

	int count = 0;
	for (int i=0;i<num;i++)
	{
		vob = dynamic_cast<zCVobLight*>(result.GetSafe(i));
		if (vob)
		{
			presetInUse = vob->GetPresetInUseName();
			if (presetInUse.IsEmpty()) presetInUse = vob->GetVobPresetName();
			presetInUse.Upper();			
			if (presetInUse == presetName)
			{
				zERR_MESSAGE(7,0,"B: SPC: Updating light "+vob->GetVobName());
				vob->SetByPreset(presetName);				
				ResetVobLighting(vob);
				count++;
			};
		};
	};	

	CString text;text.Format("Reapplied %i lights with preset %s",count, presetName.ToChar());
	MessageBox(text,"Result");	

	zERR_MESSAGE(6,zERR_END,"");
}

void spcCInfoBar_Lights::ResetVobLighting(zCVob* vob)
{
	if (!vob) vob = cur_vob;
	if (vob)
	{
		vob->BeginMovement();
		vob->TouchMovement();
		vob->EndMovement();
	}
};

void spcCInfoBar_Lights::OnLightShowranges() 
{
	SetShowLightsWireFramed(!GetShowLightsWireFramed());

	if (this->GetShowLightsWireFramed()) 
	{
		CheckWireFrameLight(this->cur_vob);
	}
	else if (zCVobLight *light = zDYNAMIC_CAST<zCVobLight>(cur_vob))
	{
		light->SetShowLightSphere(FALSE);
		if ( light == this->m_pLastVobLight ) zRELEASE(m_pLastVobLight);
	}
}

void spcCInfoBar_Lights::OnLightDynamicCompile() 
{
	m_bLightDynCompile = !m_bLightDynCompile;
}



#include "stdafx.h"
#include "zengine.h"
#include "spcCCSSequencer.h"


void spcCCSSequencer :: CSDB_BeginSyncBlock(zCCSSyncBlock* b)
{
	if (flatData.GetNumInList()==0) return;
	if (m_timepos>=0 && 
		m_timepos<flatData[0]->GetNumOfChilds()-1 && 
		workMode==workCS)
	{ 
		int z=0; 
		while (	z<flatData[0]->GetNumOfChilds() &&
				flatData[0]->GetChild(z)!=b) z++;
		if (b==flatData[0]->GetChild(z))
		{
			m_timepos=z;
			OnChangeTimePos();
		}
	}
}
void spcCCSSequencer :: CSDB_BeginAtomBlock(zCCSBlockBase* b)
{
	if (flatData.GetNumInList()==0 || b==0) return;

	b->SetDBFlag(true);
	DrawIt();
//	spcCCSDebugger :: CSDB_BeginAtomBlock(b);
}
void spcCCSSequencer :: CSDB_EndAtomBlock(zCCSBlockBase* b)
{
	if (flatData.GetNumInList()==0) return;

	b->SetDBFlag(false);
	DrawIt();
//	spcCCSDebugger :: CSDB_EndAtomBlock(b);
}
void spcCCSSequencer :: CSDB_Error(zCCSBlockBase* b, zSTRING & text)
{
	if (flatData.GetNumInList()==0) return;

	DrawIt();
	zERR_WARNING("A: CutsceneDebugger: "+text);//AfxMessageBox(text.ToChar());
}
void spcCCSSequencer :: CSDB_Warning(zCCSBlockBase* b, zSTRING & text)
{
	if (flatData.GetNumInList()==0) return;

	zSTRING mess ("A: CSBD: WARNING: ");
	if (b) mess += b->GetCommand()->MD_GetSubTypeString(b->GetCommand()->GetSubType());
	else mess += zSTRING("- ");
	mess += zSTRING(": ")+text;
	zerr.Warning(mess);
}
zCCSBlockBase* spcCCSSequencer :: GetCutsceneForDebug()
{
	if (workMode==workCS) return flatData[0];
	else return 0;
}
void spcCCSSequencer :: CSDB_StartPlaying(zCCutscene* b)
{
//	b->SaveRolesVobs(DB_RoleBuffer);
}
void spcCCSSequencer :: CSDB_Stop(zCCutscene* b)
{
//	b->RestoreRoleVobs(DB_RoleBuffer);
}
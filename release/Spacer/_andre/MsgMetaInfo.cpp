// MetaDaten, die nur im Spacer interessant sind



#ifdef COMPILING_SPACER // für den Cutscene sequenzer: ein string, der die Parameter enthält ( in gekürzter aussagekräftiger Form )

#include "zengine.h"

#include "oNPCMessages.h"

zSTRING	oCMsgMovement :: MD_GetInfo()
{
	if (subType==oCMsgMovement::EV_SETWALKMODE)	return zSTRING(targetMode);
	if (!targetName.IsEmpty())					return targetName;
	else return targetVobName;
//	return zCEventMessage::MD_GetInfo();
}
void oCMsgMovement :: MD_SetInfo(const zSTRING & str)
{
	if (subType==oCMsgMovement::EV_SETWALKMODE) targetMode=str.ToInt();
	else { 
		targetName = str; 
		targetVobName = str;
	}
};

zSTRING	oCMsgDamage::MD_GetInfo	()
{
	return "";
};

void oCMsgDamage::MD_SetInfo(const zSTRING & strInfo)
{
};

zSTRING	oCMsgConversation :: MD_GetInfo()
{
	switch (subType) {
	case EV_PLAYANISOUND	:	return text;
	case EV_PLAYANI			:	return name;
	case EV_PLAYSOUND		:	return text;
	case EV_LOOKAT			:	return targetVobName;	
	default					:	return zCEventMessage::MD_GetInfo();
	}
}
void oCMsgConversation :: MD_SetInfo(const zSTRING & str)
{
	zSTRING s = str;

	// Nachfolgende Sonderzeichen (ASCII<32 und SPACE) entfernen
	int i = s.Length();
	while ((i>=0) && (s[i]<=32)) i--;	
	s.Delete(i+1); // Alles ab i+1;

	switch (subType) {
	case EV_PLAYANISOUND	: 
		if (s.Search("#")>=0)
		{
			name = s.PickWord(1,"#","#") + ".WAV";
			text = s.PickWord(2,"#","#");
		}
		else text=s;
		break;
	case EV_PLAYANI			: name=s; break;
	case EV_PLAYSOUND		: text=s; break;
	case EV_LOOKAT			: targetVobName=s; break;
/*	case EV_OUTPUT			:
	case EV_OUTPUTSVM		:
	case EV_CUTSCENE		:
	case EV_WAITTILLEND		:
	case EV_ASK				:
	case EV_WAITFORQUESTION	:
	case EV_STOPLOOKAT		:
	case EV_STOPPOINTAT		:
		
	case EV_POINTAT			:
	case EV_QUICKLOOK		:
	case EV_PLAYANI_NOOVERLAY :*/
	}
};

zSTRING	oCMsgManipulate :: MD_GetInfo()
{
	return zCEventMessage::MD_GetInfo();
}
void oCMsgManipulate :: MD_SetInfo(const zSTRING & str){};

zSTRING	oCMsgMagic :: MD_GetInfo()
{
	return zCEventMessage::MD_GetInfo();
}
void oCMsgMagic :: MD_SetInfo(const zSTRING & str){};

zSTRING	oCMsgWeapon::MD_GetInfo()
{
	return zCEventMessage::MD_GetInfo();
}
void oCMsgWeapon :: MD_SetInfo(const zSTRING & str){};

zSTRING	oCMsgAttack::MD_GetInfo()
{
	return zCEventMessage::MD_GetInfo();
}
void oCMsgAttack :: MD_SetInfo(const zSTRING & str){};

zSTRING	oCMsgUseItem::MD_GetInfo()
{
	return zCEventMessage::MD_GetInfo();
}
void oCMsgUseItem :: MD_SetInfo(const zSTRING & str){};

zSTRING	oCMsgState::MD_GetInfo()
{
	return zCEventMessage::MD_GetInfo();
}
void oCMsgState :: MD_SetInfo(const zSTRING & str){};


#include "zCSCamera.h"

zSTRING	zCCSCamera_EventMsgActivate :: MD_GetInfo()
{
	return referenceName;
}
void	zCCSCamera_EventMsgActivate :: MD_SetInfo(const zSTRING & str)
{
	referenceName = str;
}

zSTRING	zCCSCamera_EventMsg :: MD_GetInfo()
{
	return MD_GetSubTypeString(GetSubType());
}
void	zCCSCamera_EventMsg :: MD_SetInfo(const zSTRING & str)
{

}

#endif
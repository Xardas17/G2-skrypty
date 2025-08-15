#include "zcore.h"
#include "zoption.h"
#include "zrenderer.h"

#include "osysinfo.h"

oCSystemInfo::oCSystemInfo()
{		
	scored		= FALSE;
	
	scoreCpu	= 1;
	scoreMem	= 1;
	scoreGra	= 1;
	scoreSnd	= 1;
	score		= 1;

	SetCpuSpecs			(700,1200);
	SetMemorySpecs		(256,512);
	SetGraphicsSpecs	(16,64);
};

oCSystemInfo::~oCSystemInfo()
{
};


void oCSystemInfo::AnalyseNow()
{
	zCSystemInfo::AnalyseNow();
};

void oCSystemInfo::ResetSettings(zREAL score)
{
	zSTRING settingsName = "???";
	
	zREAL gameTextureDetail		= 1.0f;	// Wert von 0.0 bis 1.0 (wird auf Texturgroessen umgerechnet)
	zREAL gameModelDetail		= 0.5f;	// Wert von 0.0 bis 1.0 (evtl. nur TRUE [>=0.5] und FALSE [<0.5])	
	bool  musicEnabled			= true;	
	int	  gameSight				= 4;	// Wert von 0 bis 14 (20% bis 300%)	
		
	// high
	if (score>=0.66)
	{
		settingsName = "high Quality / high Speed";

		gameTextureDetail	= 1.00f;
		gameModelDetail		= 0.8f;
		gameSight			= 4;				
	}
	// mid
	else if (score>=0.33)
	{
		settingsName = "mid Quality / mid Speed";
		gameTextureDetail	= 0.70f;
		gameModelDetail		= 0.5f;
		gameSight			= 3;		
	}
	// low
	else if (score>=0.00)
	{
		settingsName = "low Quality / high Speed";
		gameTextureDetail	= 0.40f;
		gameModelDetail		= 0.2f;
		gameSight			= 2;		
		musicEnabled		= false;
	}
	// calculated
	else 
	{
		settingsName = "calculated";

		if		(scoreCpu>0.80f)	{ gameSight+=1; }
		else if (scoreCpu>0.40f)	{ gameSight+=0; }
		else if (scoreCpu>0.20f)	{ gameSight-=1; gameModelDetail-=0.1f; }
		else						{ gameSight-=2; gameModelDetail-=0.2f; }

		if		(scoreMem>0.80f)	{ gameSight+=1; gameTextureDetail+=0.0f; }
		else if (scoreMem>0.40f)	{ gameSight+=0; gameTextureDetail-=0.2f; }
		else if (scoreMem>0.20f)	{ gameSight-=1; gameTextureDetail-=0.4f; }
		else						{ gameSight-=2; gameTextureDetail-=0.6f; musicEnabled = false;}

		if		(scoreGraMem>0.60f)	{ gameTextureDetail+=0.0f; }
		else if (scoreGraMem>0.35f)	{ gameSight-=1; gameTextureDetail-=0.2f; }
		else						{ gameSight-=2; gameTextureDetail-=0.4f; }		
	}

	// Grenzen einhalten (siehe obene)
	zClamp(gameTextureDetail,	0.0f,1.0f);
	zClamp(gameModelDetail,		0.0f,1.0f);	

	// Werte schreiben (evtl. auf Wertebereich 0.0 bis 1.0 konvertieren)	
	zoptions->WriteInt (zOPT_SEC_PERFORMANCE,	"sightValue",		gameSight);
	zoptions->WriteReal(zOPT_SEC_INTERNAL,		"texDetailIndex",	gameTextureDetail);	
	zoptions->WriteReal(zOPT_SEC_PERFORMANCE,	"modelDetail",		gameModelDetail);	
	zoptions->WriteBool(zOPT_SEC_SOUND,			"musicEnabled",		musicEnabled);	
		
	// Werte ausgeben
	zERR_MESSAGE(3,zERR_BEGIN,"B: SYS: Resulting settings: "+settingsName);		
		zERR_MESSAGE(3,0,"B: SYS: gameSight: "			+ zSTRING(gameSight));
		zERR_MESSAGE(3,0,"B: SYS: gameModelDetail: "	+ zSTRING(gameModelDetail,		2));
		zERR_MESSAGE(3,0,"B: SYS: gameTextureDetail: "	+ zSTRING(gameTextureDetail,	2));
		if (musicEnabled)	zERR_MESSAGE(3,0,"B: SYS: Music enabled");
		else				zERR_MESSAGE(3,0,"B: SYS: Music disabled");
	zERR_MESSAGE(3,zERR_END,"");
};


void oCSystemInfo::ScoreNow()
{
	zERR_MESSAGE(3,zERR_BEGIN,"B: SYS: Scoring your system ...");
	
	scoreCpu	= ( (cpuSpeed)				- cpuLow	) / ( cpuHigh		- cpuLow	);	
	scoreMem	= ( (memSize/1024/1024)		- memLow	) / ( memHigh		- memLow	);
	scoreGraMem	= ( (graMemSize/1024/1024)	- graMemLow	) / ( graMemHigh	- graMemLow	);
	scoreGra	= 0.50f + GetGraphicsBonus();
	scoreSnd	= 0.50f + GetSoundBonus();
	score		= ( scoreCpu*2 + scoreMem*2 + scoreGra*1 ) / 5.0f;
	
	zERR_MESSAGE(3,0,"B: SYS: Score CPU: "		+zSTRING(scoreCpu,2)+" ["+GetScoreDescr(scoreCpu)+"]");
	zERR_MESSAGE(3,0,"B: SYS: Score Memory: "	+zSTRING(scoreMem,2)+" ["+GetScoreDescr(scoreMem)+"]");					
	zERR_MESSAGE(3,0,"B: SYS: Score Graphics: "	+zSTRING(scoreGra,2)+" ["+GetScoreDescr(scoreGra)+"]");	
	zERR_MESSAGE(3,0,"B: SYS: Score Sound: "	+zSTRING(scoreSnd,2)+" ["+GetScoreDescr(scoreSnd)+"]");	
	zERR_MESSAGE(3,0,"B: SYS: Resulting Score: "+zSTRING(score,2)	+" ["+GetScoreDescr(score)+"]");	

	zERR_MESSAGE(3,zERR_END,"");	

	scored = TRUE;
};

zREAL oCSystemInfo::GetGraphicsBonus()
{
	zERR_ASSERT(zrenderer);

	bool	tnl			= zrenderer->HasCapability(zRND_CAP_TNL_HARDWARE) != 0;
	int		numStages	= zrenderer->HasCapability(zRND_CAP_MAX_BLEND_STAGES);

	zREAL value = 0.0f;
	if (tnl) value += 0.2f;					// max. 0.2
	if (numStages==2)	value += 0.1f;
	if (numStages>=3)	value += 0.2f;		// max. 0.2

	if (!tnl) 
	{
		zoptions->WriteBool("RENDERER_D3D", "zFogRadial", FALSE);
		if (zrenderer) zrenderer->SetRadialFog(FALSE);
	}

	return value;							// => max 0.4
};

zREAL oCSystemInfo::GetSoundBonus()
{
	return 0.25f;
};

zSTRING	oCSystemInfo::GetScoreDescr(zREAL value)
{
	if		(value>=1.00)	return "UNBELIEVABLE";
	else if (value>=0.80)	return "GREAT";
	else if (value>=0.60)	return "GOOD";
	else if (value>=0.40)	return "OK";
	else if (value>=0.20)	return "POOR";
	else if (value>=0.00)	return "BAD";
	else					return "NO WAY";
};

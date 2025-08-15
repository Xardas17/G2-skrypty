#ifndef _OSYSINFO_H_
#define _OSYSINFO_H_

#include "zsysinfo.h"

class oCSystemInfo : public zCSystemInfo
{	
public:
	oCSystemInfo();
	virtual ~oCSystemInfo();

	// do the bart-man
	virtual void AnalyseNow		();
	virtual void ScoreNow		();	
	virtual void ResetSettings	(zREAL score = -1.0f);	

	// set specificcations (minimum and optimum)
	void	SetCpuSpecs		(int _low, int _high)	{ cpuLow = zREAL(_low); cpuHigh=zREAL(_high); };
	void	SetMemorySpecs	(int _low, int _high)	{ memLow = zREAL(_low); memHigh=zREAL(_high); };
	void	SetGraphicsSpecs(int _low, int _high)	{ graMemLow = zREAL(_low); graMemHigh=zREAL(_high); };

	// get scores
	zREAL	GetScore			()					{ return score;    };
	zREAL	GetScoreCpu			()					{ return scoreCpu; };
	zREAL	GetScoreMemory		()					{ return scoreMem; };
	zREAL	GetScoreGraphics	()					{ return scoreGra; };
	zREAL	GetScoreSound		()					{ return scoreSnd; };	

	// get comment on given score
	zSTRING	GetScoreDescr		(zREAL value);	

protected:

	// axtra-bonus for specific hardware
	zREAL	GetGraphicsBonus	();
	zREAL	GetSoundBonus		();

protected:

	zBOOL	scored;

	// specifications (minimum and optimum)
	zREAL	cpuLow, cpuHigh;
	zREAL	memLow, memHigh;
	zREAL	graMemLow, graMemHigh;

	// score-values
	zREAL	scoreCpu;
	zREAL	scoreMem;
	zREAL	scoreGraMem;
	zREAL	scoreGra;
	zREAL	scoreSnd;
	zREAL	score;
};

#endif
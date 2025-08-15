#include "zcore.h"
#include "oVisFX_MultiTarget.h"


static zBOOL ArraysEqual(zCArray<zCVob*>&a1, zCArray<zCVob*>&a2)
{
	if (a1.GetNumInList()!=a2.GetNumInList()) return FALSE;
	for (int i=0; i<a1.GetNumInList(); i++) if (a1[i]!=a2[i]) return FALSE;
	return TRUE;
}

oCVisFX_MultiTarget::oCVisFX_MultiTarget()
{
	this->SetDontWriteIntoArchive(TRUE);
};

oCVisFX_MultiTarget::~oCVisFX_MultiTarget()
{
	zCVob *delVob;
	for (int i=vobList.GetNum()-1; i>=0; i--)
	{
		delVob = vobList[i];
		vobList.RemoveIndex(i);
		zRELEASE(delVob);
	};

	oCVisualFX* delVis;
	for (i=visList.GetNum()-1; i>=0; i--)
	{
		delVis = visList[i];
		visList.RemoveIndex(i);
		delVis -> Stop();
		zRELEASE(delVis);
	};
};

void oCVisFX_MultiTarget::Open()
{
	for (int i=0; i<visList.GetNum(); i++)
	{
		visList[i]->Open();
	};
	oCVisualFX::Open();
};

void oCVisFX_MultiTarget::SetLevel		( int level )							 
{
	for (int i=0; i<visList.GetNum(); i++)
	{
		visList[i]->SetLevel(level);
	};
	oCVisualFX::SetLevel(level);
};


void oCVisFX_MultiTarget::Init( zCArray <zCVob *> trajectoryVobs		)
{

	if (ArraysEqual(trajectoryVobs,vobList)) return;

	zCVob *delVob;
	for (int i=vobList.GetNum()-1; i>=0; i--)
	{
		delVob = vobList[i];
		vobList.RemoveIndex(i);
		zRELEASE(delVob);
	};
		
	vobList = trajectoryVobs;

	for (i=0; i<vobList.GetNum(); i++) vobList[i]->AddRef();
	
	// gibbet neue targets, alte effekte löschen

	oCVisualFX* delVis;
	for (i=visList.GetNum()-1; i>=0; i--)
	{
		delVis = visList[i];
		visList.RemoveIndex(i);
		delVis -> Stop();
		zRELEASE(delVis);
	};

	if (trajectoryVobs.GetNum() == 0)
	{
		// gibt kein origin, und kein target, safe methode der basisklasse aufrufen
		oCVisualFX::Init(0,0);
		return;
	}
	else if (trajectoryVobs.GetNum() == 1)
	{
		// gibt ein origin, und kein target, methode der basisklasse aufrufen
		oCVisualFX::Init(trajectoryVobs[0],0);
		return;
	}
	else
	{
		// gibt ein origin, und targets, doh!
		int numEffects = trajectoryVobs.GetNum()-1;
		oCVisualFX *newFX;

		for (int i=0; i<numEffects; i++)
		{
			newFX = zNEW(oCVisualFX());
			// ein wenig kompliziert: hier wird die hierachie festgelegt
			// da es ein einfacher solo effekt ist, ist root == parent == der erzeugte fx
			newFX->root		= newFX;
			newFX->parent	= newFX;

			zSTRING levelID = fxName + "_SUB" + "_L" + zSTRING(level);
			if (fxParser->GetSymbol(levelID)) 	newFX->SetByScript	( levelID );
			else								newFX->SetByScript	( fxName + "_SUB" );

			newFX->Init			( trajectoryVobs[0], trajectoryVobs[i+1]);		// FIXME: wo wird der effekt erstmalig in die welt eingefügt ?

			if (level != 0) newFX->SetLevel(level);
			
			visList.InsertEnd(newFX);
			newFX->AddRef();
		};

	};

	oCVisualFX::Init(trajectoryVobs);
};

void oCVisFX_MultiTarget::InvestNext		()										 
{
	for (int i=0; i<visList.GetNum(); i++)
	{
		visList[i]->InvestNext();
	};
	oCVisualFX::InvestNext();
};

void oCVisFX_MultiTarget::Cast			( const zBOOL killAfterDone )
{

	oCVisualFX* castVis;
	for (int i=visList.GetNum()-1; i>=0; i--)
	{
		castVis = visList[i];
		visList.RemoveIndex(i);
		castVis -> Cast();
		zRELEASE(castVis);
	};

	oCVisualFX::Cast();
};

void oCVisFX_MultiTarget::Stop			( const zBOOL killAfterDone )
{
	oCVisualFX* stopVis;
	for (int i=visList.GetNum()-1; i>=0; i--)
	{
		stopVis = visList[i];
		visList.RemoveIndex(i);
		stopVis -> Stop();
		zRELEASE(stopVis);
	};
	oCVisualFX::Stop();
};

void oCVisFX_MultiTarget::SetByScript	( const zSTRING &id )
{
	zSTRING ID(id);
	ID.Upper();

	// das dumme ist, das hier noch nicht bekannt ist, wieviele targets wir später wirklich haben,
	// darum wird hier nur der Name initialisiert, die seperaten effekte müssen später in ::Init() erzeugt werden
	// -> performance

	oCVisualFX::SetByScript(id);

};

void oCVisFX_MultiTarget::Reset			()
{
	for (int i=0; i<visList.GetNum(); i++)
	{
		visList[i]->Reset();
	};
	oCVisualFX::Reset();
};

zBOOL oCVisFX_MultiTarget::IsFinished		()
{
	for (int i=0; i<visList.GetNum(); i++)
	{
		if (!visList[i]->IsFinished()) return FALSE;
	};
	if (!oCVisualFX::IsFinished()) return FALSE;

	return TRUE;
};

void oCVisFX_MultiTarget::SetDamage		( const float dam     )
{
	for (int i=0; i<visList.GetNum(); i++)
	{
		visList[i]->SetDamage(dam);
	};
	oCVisualFX::SetDamage(dam);
};

void oCVisFX_MultiTarget::SetDamageType	( const int   damType )
{
	for (int i=0; i<visList.GetNum(); i++)
	{
		visList[i]->SetDamageType(damType);
	};
	oCVisualFX::SetDamageType(damType);
};


void oCVisFX_MultiTarget::Archive			(zCArchiver &)
{
};

void oCVisFX_MultiTarget::Unarchive		(zCArchiver &)
{
};


zCLASS_DEFINITION			(oCVisFX_MultiTarget, oCVisualFX,	0,	0)

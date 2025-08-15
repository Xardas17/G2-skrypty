/******************************************************************************** 
 
     $Workfile:: oNews.cpp            $                $Date:: 24.04.01 17:33   $
     $Revision:: 35                   $             $Modtime:: 21.04.01 15:46   $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oNews.cpp $
 * 
 * 35    24.04.01 17:33 Edenfeld
 * Patch 1.08a
 * 
 * 34    9.02.01 20:49 Wohlers
 * 
 * 33    31.01.01 2:07 Wohlers
 * 
 * 32    30.01.01 14:28 Wohlers
 * 
 * 31    27.01.01 22:51 Wohlers
 * 
 * 30    27.01.01 20:55 Wohlers
 * 
 * 29    27.01.01 20:21 Wohlers
 * 
 * 28    22.01.01 21:36 Speckels
 * 
 * 27    22.01.01 19:13 Speckels
 * 
 * 26    22.01.01 18:11 Speckels
 * 
 * 32    19.01.01 18:30 Speckels
 * 
 * 31    19.01.01 16:01 Speckels
 * 
 * 30    16.01.01 20:08 Admin
 * 
 * 25    9.11.00 16:43 Wohlers
 * 
 * 24    8.11.00 19:28 Wohlers 
 * 
 * 23    8.11.00 17:53 Wohlers
 * 
 * 22    8.11.00 16:46 Wohlers
 * 
 * 21    8.11.00 13:24 Wohlers
 * 
 * 20    7.11.00 18:53 Wohlers
 * 
 * 19    24.10.00 11:00 Moos
 * 
 * 18    19.10.00 21:49 Wohlers
 * 
 * 17    17.10.00 15:21 Wohlers
 * 
 * 16    16.10.00 18:43 Moos
 * 
 * 15    5/10/00 19:01 Luesebrink
 * 
 * 14    5.10.00 13:57 Keskenti
 * 
 * 13    5.10.00 13:32 Keskenti
 * 
 * 12    5.10.00 13:28 Keskenti
 * 
 * 11    5/10/00 13:22 Luesebrink
 * 
 * 10    28.09.00 17:27 Wohlers
 * 
 * 9     27.09.00 17:25 Wohlers
 * 
 * 8     11.09.00 20:10 Rueve
 * 
 * 7     7.09.00 16:06 Wohlers
 * 
 * 6     2.08.00 14:25 Wohlers
 * 
 * 5     21.07.00 15:34 Wohlers
 * 
 * 4     22.05.00 18:42 Wohlers
 * Gothic 0.82
 * 
 * 4     8.05.00 23:08 Edenfeld
 * 
 * 3     28.04.00 15:56 Wohlers
 * Gothic 0.79
 * Nahkampf AI Phase 2
 * 
 * 2     19.04.00 19:10 Wohlers
 * 
 * 5     9.03.00 15:50 Wohlers
 * Sourcen 0.74 (Levelwechsel, Änderung oCGame)
 * 
 * 4     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 3     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/
 
#include "zCore.h"

#include "oNews.h"
#include "oNpc.h"
#include "oGame.h"
#include "oWorld.h"

#include "zAccount.h"

const int	NEWS_MAX_ENTRY		= 200;						// Maximal 20 Eintraege
const zREAL NEWS_SPREAD_TIME	= 60 * 1000;				

// Unterschiedliche Spreadmodi der News.
// Wird aus den Skripten per "C_CANNEWSBESPREAD" als Returnwert uebergeben.

// **************************************************************************************
// NEWS - Manager
// **************************************************************************************

oCNewsManager::oCNewsManager ()
{
	sentry = 0;
	for (int i=0; i<MAX_ENTRY; i++) spreadList[i] = 0;
	called_BAssessAndMem = 0;
}

oCNewsManager::~oCNewsManager ()
{
}

void oCNewsManager::CreateNews ( int newsid, zBOOL gossip, oCNpc* witness, oCNpc* offender, oCNpc* victim, zBOOL guildvictim )
// Beachte : andere Parameterreihenfolge als der Skriptbefehl ( Übersicht ! )
// Npc_MemoryEntry_(Guild)
// Guild = Bezieht sich News auf gesamte Gilde ?
{
	// This is for Debugging only.....
/*	if (!gossip && (called_BAssessAndMem>1)) {
		zERR_FAULT("B_AssessAndMem called, but theres a missing C_CanNewsBeSpread call.... This is a strange news-bug -> call one of the programmers.... This is an emergency !!!!");
	}
*/
	if (!witness || !witness->GetNewsMemory()) return;

	// Gibt es News dieser Konstellation schon ?	
	oCNews* news = witness -> GetNewsMemory() -> GetNews(newsid,offender,victim);
	// Ja, und ist neue Info Gossip = dann überschreiben
	if (news && gossip) {
		news -> SetGossip(TRUE);
	
	} else if (!news && witness && !witness->IsSelfPlayer()) {
		
		// Wenn es die News noch nicht gibt, diese erzeugen
		news  = zNEW( oCNews ( newsid, gossip, witness, offender, victim, guildvictim ) );
		news -> SetSpreadTime(0);

		// Und ins Gedächtnis des Zeugen einfügen
		witness -> GetNewsMemory() -> Insert (news);
		
		// Kann News weitererzaehlt werden ?
		// Wenn InfoQuelle = witness, dann
		if (!gossip) {
			
			// C_CanNewsBeSpread aufrufen
			int index = parser.GetIndex("C_CANNEWSBESPREAD");
			if (index<=0) {
				zERR_MESSAGE(5,0,"U:NEWS:Script-Function C_CANNEWSBESPREAD not found. News cant be spreaded !!!");
				return;
			}
			// Init Parser
			parser.SetInstance("SELF"	,witness);
			parser.SetInstance("OTHER"	,offender);
			parser.SetInstance("VICTIM"	,victim);		
			int iSpreadType = *(int*)parser.CallFunc(index);
			oTNewsSpreadType spreadType = oTNewsSpreadType(iSpreadType);
	
//			called_BAssessAndMem--;

			if (spreadType!=NEWS_DONT_SPREAD) {			
				// Timecounter starten.
				news->SetSpreadTime(NEWS_SPREAD_TIME);
				news->SetSpreadType(spreadType);
				return;
			}
		}
	}
}

void oCNewsManager::SpreadToGuild (int guildnr)
{
	if (sentry < MAX_ENTRY) {
		spreadList[sentry] = guildnr;
		sentry ++;
	};
};

zBOOL oCNewsManager::IsInSpreadList (int guildnr)
{
	for (int i=0; i<sentry; i++) {
		if (spreadList[i] == guildnr) return TRUE;
	}
	return FALSE;
}

void oCNewsManager::SpreadNews (oCNews* news)
{	
	// News soll in der Welt verteilt werden
	// an befreundete Gilden
	// FIXME : Sollte nie Gossip sein, but Safety first...
	if (!news->IsGossip()) {
		int index = parser.GetIndex("B_SPREADANDMEMORIZE");
		if (index<0) {
			zERR_MESSAGE(5,0,"U:NEWS:Script-Function B_SPREADANDMEMORIZE not found. News cannot be spread !!!");
			return;
		}

		// Nur Zeugen erzählen es weiter
		int	newsid;
		zBOOL gossip;
		oCNpc *witness;
		oCNpc *offender;
		oCNpc *victim;
		news -> GetNewsData (newsid, gossip, witness, offender, victim);

		// Durchlaufe NSC Liste
		zBOOL spreadIt	= FALSE;
		oCNpc* npc		= NULL;
		zCListSort<oCNpc>* node = ogame->GetGameWorld()->GetVobListNpcs()->GetNextInList();
		while (node) {
			npc		= node->GetData();
			node	= node->GetNextInList();
			
			if (!npc->IsDead())				// Er sollte leben
			if ( npc!=witness )				// und nicht der Zeuge sein
			if ( !npc->IsSelfPlayer() )		// und auch nicht der Spieler.
			{
				// je nach NewsSpreadType jetzt verteilen
				spreadIt = FALSE;
				switch (news->GetSpreadType()) {
					
					case NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_VICTIM	:	
						spreadIt = (victim && victim->IsGuildFriendly(npc->GetTrueGuild()) );
						break;
					case NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_WITNESS	:	
						spreadIt = (witness && witness->IsGuildFriendly(npc->GetTrueGuild()) );
						break;
					case NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_OFFENDER	:	
						spreadIt = (offender && offender->IsGuildFriendly(npc->GetTrueGuild()) );
						break;
					case NEWS_SPREAD_NPC_SAME_GUILD_VICTIM			:	
						spreadIt = (victim && (victim->GetTrueGuild()==npc->GetTrueGuild()) );
						break;
					default :	// oops, this should never happen.
						zERR_WARNING("U: NEWS: Unknown News-spreadType used.");
						break;
				}
				if (spreadIt) {
					// Init Parser
					// Set all, cos during script, they may be changed.
					parser.SetInstance	("OTHER"	,offender);
					parser.SetInstance	("VICTIM"	,victim);		
					parser.SetInstance	("SELF"		,npc);
					parser.CallFunc		(index,newsid,1);
				}
			}
		}
		zERR_MESSAGE(5,0,"U:NEWS: News spreaded : "+zSTRING(newsid));
	}
};

// **************************************************************************************
// NEWS - Memory
// **************************************************************************************

oCNewsMemory::oCNewsMemory()
{
}

oCNewsMemory::~oCNewsMemory()
{
	ClearNews();	
}

void oCNewsMemory::Insert( oCNews* news )
{	
	if (!news) return;	

	// Nicht mehr als 20 Eintraege zulassen....
	if (iknow.GetNumInList()>=NEWS_MAX_ENTRY) {
		Remove (iknow.Get(NEWS_MAX_ENTRY-1));
	}
	iknow.Insert(news);
}

void oCNewsMemory::Remove( oCNews* news )
{
	if (!news) return;
	iknow.Remove(news);
	delete(news);
}

oCNews* oCNewsMemory::GetNews(int news_id, oCNpc* offender, oCNpc* victim)
// TRUE, if news is already in List
// Zeuge ist hier nicht mehr wichtig, es geht allein um die Tatsache
{
	zCList <oCNews> *node = iknow.GetNextInList();
	oCNews*			 news = NULL;
	while (node) {
		news = node -> GetData();
		node = node -> GetNextInList();
		if (news -> IsIdentical(news_id, offender, victim)) return news;
	}
	return NULL;
}

void oCNewsMemory::CheckSpreadNews ()
{
	// FIXME : Besser kein Counter, sondern an Weltzeit festmachen ????
	// Nix da zum erzaehlen
	if (iknow.GetNumInList()<=0) return;
	
	zREAL dtime = ztimer.GetFrameTimeF();
	zCList <oCNews> *node = iknow.GetNextInList();
	oCNews*			 news = NULL;
	while (node) {
		news = node -> GetData();
		node = node -> GetNextInList();
		zREAL counter = news -> GetSpreadTime();
		if (counter>0) {
			news -> SetSpreadTime (counter -= dtime);
			if (news -> GetSpreadTime() <=0 ) {
				// Aktivate News global
				ogame -> GetNewsManager() -> SpreadNews ( news );
			}
		}	
	}
}

int oCNewsMemory::SearchNews(int _newsID, oCNpc* _offender, oCNpc* _victim)
// Suche passende News
// 0  - keine News
// >0 - entsprechende News Nummer
{
	zCList <oCNews> *node = iknow.GetNextInList();
	oCNews*			 news = NULL;
	oCNpc *witness,*victim,*offender;
	zBOOL			gossip;
	int				newsID;
	int				number = 0;
	while (node) {
		number++;
		news = node -> GetData();
		node = node -> GetNextInList();
		
		news -> GetNewsData(newsID, gossip, witness, offender, victim);
		
		if (newsID == _newsID) {
			if (_offender	&& (_offender != offender)) continue;
			if (_victim		&& (_victim	  != victim))	continue;
			return number;
		}
	}
	return 0;
}

void oCNewsMemory::ShowDebugInfos()
{
	zCList <oCNews> *	node	= iknow.GetNextInList();
	oCNews*				news	= NULL;
	int					newsID	= 0;
	zBOOL				gossip	= FALSE;
	zSTRING				s;
	
	int y = 0;
	screen->Print(   0,y,"ID");
	screen->Print( 500,y,"Witness");
	screen->Print(2000,y,"Offender");
	screen->Print(3500,y,"Victim");
	screen->Print(5000,y,"Type");
	screen->Print(7500,y,"Time");

	y += screen->FontY()*2;

	oCNpc *witness,*victim,*offender;
	while (node) {
		news =  node->GetData();
		news -> GetNewsData(newsID, gossip, witness, offender, victim);
		
		screen->Print(0,y,zSTRING(newsID));
		
		if (witness)	screen->Print( 500,y,witness->GetName());
		if (offender)	screen->Print(2000,y,offender->GetName());
		if (victim)		screen->Print(3500,y,victim->GetName());
		
		if (news->GetSpreadType()==NEWS_DONT_SPREAD)							s = "DONT SPREAD";		else
		if (news->GetSpreadType()==NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_VICTIM)		s = "FR-VICTIM";		else
		if (news->GetSpreadType()==NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_WITNESS)	s = "FR-WITNESS";		else
		if (news->GetSpreadType()==NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_OFFENDER)	s = "FR-OFFENDER";		else
		if (news->GetSpreadType()==NEWS_SPREAD_NPC_SAME_GUILD_VICTIM)			s = "GUILD-VICTIM";

		if (gossip) s+="  (G)";
		screen->Print(5000,y,s);

		screen->Print(7500,y,zSTRING(int(news->GetSpreadTime())));

		y += screen->FontY();
		node = node->GetNextInList();
	}
};

oCNews* oCNewsMemory::GetNewsByNumber(int newsNumber)
// 0 - keine News
// 1 - erste News
{
	zCList <oCNews> *node = iknow.GetNextInList();
	int			   number = 1;
	while (node) {
		if (number == newsNumber) return node->GetData();
		node = node -> GetNextInList();
		number++;
	}
	return NULL;	
}

void oCNewsMemory::ClearNews()
{
	oCNews* news;
	for( int i = iknow.GetNumInList()-1; i >=0; i-- )
	{		
		news = iknow[i];		
		iknow.Remove(news);
		delete news;
	}
	iknow.DeleteListDatas();
};

zBOOL oCNewsMemory::DeleteNewsByNumber(int newsNumber)
{
	zCList <oCNews> *node = iknow.GetNextInList();
	int			   number = 1;
	while (node) {
		if (number == newsNumber) break;
		node = node -> GetNextInList();
		number++;
	}
	if (node) {
		oCNews* news = node->GetData();
		iknow.Remove(news);
		news = NULL;
	}
	return (node!=NULL);		
}

void oCNewsMemory::Archive(zCArchiver &arc)
{
	if(!arc.InSaveGame())return;

	arc.WriteInt("NumOfEntries", iknow.GetNumInList() );
	for( int i = 0; i < iknow.GetNumInList(); i++ )
	{
		iknow[i]->Archive(arc);
	}
}

void oCNewsMemory::Unarchive(zCArchiver &arc)
{
	if(!arc.InSaveGame())return;

	ClearNews();	

	oCNews* news;
	int NumOfEntries;
	arc.ReadInt("NumOfEntries", NumOfEntries );	
	for(int i=0; i < NumOfEntries; i++ )
	{		
		news = zNEW( oCNews );
		news->Unarchive(arc);
		iknow.Insert( news );
	}
}
// **************************************************************************************
// Single NEWS
// **************************************************************************************

int oCNews::news_counter = 0;	// How many News.... ?

static zCArray<oCNews*>newsList;

int oCNews :: GetRemainingNews()
{
	return news_counter;
};

void oCNews :: CheckRemainingNews()
{
	int		newsID;
	zBOOL	gossip;
	oCNpc *witness,*offender,*victim;

	for (int i=0; i<newsList.GetNumInList(); i++) {
		oCNews* news = newsList[i];
		if (news) {

			news->GetNewsData(newsID,gossip,witness,offender,victim);

			zSTRING s = "U: NEWS: Found illegal news : ";
			
			s += "ID:"+zSTRING(newsID)+"/Gossip:"+zSTRING(gossip)+"/";
			if (witness)	s+="Witness:"	+witness	->GetInstanceName()+"/";
			if (offender)	s+="Offender:"	+offender	->GetInstanceName()+"/";
			if (victim)		s+="Victim:"	+victim		->GetInstanceName();

			zERR_WARNING(s);
		}
	}
};

oCNews::oCNews()
{
	news_counter ++;

	news_id		= -1;
	gossip		= FALSE;
	
	mNpcWitness	= 0;
	mNpcOffender= 0;
	mNpcVictim	= 0;

	guildvictim = FALSE;

	spread_time	= 0;
	spreadType	= NEWS_DONT_SPREAD;
	told		= FALSE;

	newsList.Insert(this);
};

oCNews::oCNews (int nid, zBOOL g, oCNpc* w, oCNpc* o, oCNpc* v, zBOOL gv)
{
	news_counter ++;

	news_id		= nid;
	gossip		= g;
	
	mNpcWitness	= w;	if (mNpcWitness)	zADDREF_ACCT(mNpcWitness);
	mNpcOffender= o;	if (mNpcOffender)	zADDREF_ACCT(mNpcOffender);
	mNpcVictim	= v;	if (mNpcVictim)		zADDREF_ACCT(mNpcVictim);

	guildvictim = gv;

	spread_time	= 0;
	spreadType	= NEWS_DONT_SPREAD;
	told		= FALSE;

	newsList.Insert(this);
	zERR_MESSAGE(4,0,"U: NEWS: News created: "+zSTRING(nid));
};

oCNews::~oCNews()
{
	newsList.Remove(this);
	
	zRELEASE_ACCT(mNpcWitness);
	zRELEASE_ACCT(mNpcOffender);
	zRELEASE_ACCT(mNpcVictim);
	news_counter--;
};

int oCNews::GetID()
{
	return news_id;
}

zBOOL oCNews::IsIdentical (int nid, oCNpc* o, oCNpc* v)
{
	return ( (nid==news_id) && (o==mNpcOffender) && (v==mNpcVictim) );
}

void oCNews::SetSpreadTime (zREAL counter)
{
	spread_time = counter;
	if (spread_time<0) spread_time = 0;
}

zREAL oCNews::GetSpreadTime ()
{
	return spread_time;
}

void oCNews::SetGossip(zBOOL g)
{
	gossip = g;
	if (gossip) {
		// Wenn es gossip ist, dann kein weiteres Spreading
		SetSpreadTime(0);
	}
}

zBOOL oCNews::IsGossip ()
{
	return gossip;
}

zBOOL oCNews::IsGuildVictim()
{
	return guildvictim;
}

void oCNews::GetNewsData (int &n, zBOOL &g, oCNpc* &w, oCNpc* &o, oCNpc* &v)
{
	n = news_id;
	g = gossip;

	if (!mNpcWitness && !witnessName.IsEmpty()) {
		mNpcWitness = dynamic_cast<oCNpc*>(ogame->GetGameWorld()->SearchVobByName(witnessName));
		if (mNpcWitness) zADDREF_ACCT(mNpcWitness);
	};
	if (!mNpcOffender && !offenderName.IsEmpty()) {
		mNpcOffender = dynamic_cast<oCNpc*>(ogame->GetGameWorld()->SearchVobByName(offenderName));
		if (mNpcOffender) zADDREF_ACCT(mNpcOffender);
	};
	if (!mNpcVictim && !victimName.IsEmpty()) {
		mNpcVictim = dynamic_cast<oCNpc*>(ogame->GetGameWorld()->SearchVobByName(victimName));
		if (mNpcVictim) zADDREF_ACCT(mNpcVictim);
	};	

	w = mNpcWitness;
	o = mNpcOffender;
	v = mNpcVictim;
};

void oCNews::Archive(zCArchiver &arc)
{
	arc.WriteBool	("told",		told);
	arc.WriteFloat	("spread_time",	spread_time);
	arc.WriteInt	("spreadType",	(int)spreadType);
	arc.WriteInt	("news_id",		news_id);
	arc.WriteBool	("gossip",		gossip);
	arc.WriteBool	("guildvictim",	guildvictim);

	// Npcs
	if (mNpcWitness) {
		witnessName = mNpcWitness->GetInstanceName();
		if (mNpcWitness==oCNpc::dontArchiveThisNpc)	zRELEASE(mNpcWitness);
	}
	arc.WriteString	("witnessName",		witnessName);

	if (mNpcOffender) {
		offenderName = mNpcOffender->GetInstanceName();
		if (mNpcOffender==oCNpc::dontArchiveThisNpc) zRELEASE(mNpcOffender);
	}
	arc.WriteString	("offenderName",	offenderName);
	
	if (mNpcVictim) {
		victimName = mNpcVictim->GetInstanceName();
		if (mNpcVictim==oCNpc::dontArchiveThisNpc)	zRELEASE(mNpcVictim);
	}
	arc.WriteString	("victimName",		victimName);
	
/*	arc.WriteObject	("witness",		mNpcWitness);
	arc.WriteObject	("offender",	mNpcOffender);
	arc.WriteObject	("victim",		mNpcVictim);
*/	
}


void oCNews::Unarchive(zCArchiver &arc)
{
	arc.ReadBool	("told",		told);
	arc.ReadFloat	("spread_time",	spread_time);
	arc.ReadInt		("spreadType",	(int&)spreadType);
	arc.ReadInt		("news_id",		news_id);
	arc.ReadBool	("gossip",		gossip);
	arc.ReadBool	("guildvictim",	guildvictim);

	// Npcs
	zRELEASE(mNpcWitness);
	zRELEASE(mNpcOffender);
	zRELEASE(mNpcVictim);

	witnessName		= arc.ReadString("witnessName");
	offenderName	= arc.ReadString("offenderName");
	victimName		= arc.ReadString("victimName");

/*	mNpcWitness		= static_cast<oCNpc*>	(arc.ReadObject("witness")	);
	mNpcOffender	= static_cast<oCNpc*>	(arc.ReadObject("offender")	);
	mNpcVictim		= static_cast<oCNpc*>	(arc.ReadObject("victim")	);*/
}

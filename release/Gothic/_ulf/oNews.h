 /******************************************************************************** 
 
     $Workfile:: oNews.h              $                $Date:: 9.02.01 20:49    $
     $Revision:: 14                   $             $Modtime:: 9.02.01 18:31    $
       $Author:: Wohlers                                                        $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oNews.h $
 * 
 * 14    9.02.01 20:49 Wohlers
 * 
 * 13    27.01.01 20:21 Wohlers
 * 
 * 12    22.01.01 19:13 Speckels
 * 
 * 11    22.01.01 18:11 Speckels
 * 
 * 29    19.01.01 18:30 Speckels
 * 
 * 28    19.01.01 16:01 Speckels 
 * 
 * 27    16.01.01 20:08 Admin
 * 
 * 10    8.11.00 17:53 Wohlers
 * 
 * 9     7.11.00 18:53 Wohlers
 * 
 * 8     5/10/00 19:01 Luesebrink
 * 
 * 7     5/10/00 13:22 Luesebrink
 * 
 * 6     28.09.00 17:27 Wohlers
 * 
 * 5     27.09.00 17:25 Wohlers
 * 
 * 4     22.05.00 18:43 Wohlers
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
 * 3     10.01.00 15:18 Wohlers
 * Angepasst an ZenGin 0.85
 * 
 * 2     23.11.99 18:49 Wohlers
 * SourceSafe Header eingefügt
 * Mobsi-Erweiterungen
 * 
 *********************************************************************************/

#ifndef __ONEWS_H__
#define __ONEWS_H__

class oCNpc;

#include "zTypes.h"
#include "zContainer.h"

// Enum for different spreadmodes.
typedef enum oENewsSpreadType
{
	NEWS_DONT_SPREAD							= 0,
	NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_VICTIM		= 1,
	NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_WITNESS	= 2,
	NEWS_SPREAD_NPC_FRIENDLY_TOWARDS_OFFENDER	= 3,		
	NEWS_SPREAD_NPC_SAME_GUILD_VICTIM			= 4		
}
oTNewsSpreadType;

class oCNews {
public:
	oCNews									();
	oCNews									(int nid, zBOOL gossip, oCNpc* w, oCNpc* o, oCNpc* v, zBOOL guildvictim);
	~oCNews									();

	int					GetID				();
	zBOOL				IsIdentical			(int nid, oCNpc* o, oCNpc* v);

	void				SetSpreadTime		(zREAL count);
	zREAL				GetSpreadTime		();

	void				SetGossip			(zBOOL g);
	zBOOL				IsGossip			();
	zBOOL				IsGuildVictim		();

	void				SetSpreadType		(oTNewsSpreadType spType)	{ spreadType = spType;	};
	oTNewsSpreadType	GetSpreadType		()							{ return spreadType;	};
	
	void				GetNewsData			(int &newsid, zBOOL &gossip, oCNpc* &witness, oCNpc* &offender, oCNpc* &victim);

	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);

	// Statics
	static int			GetRemainingNews	();
	static void			CheckRemainingNews	(); 

private:			
	zBOOL				told;				// already told ?
	zREAL				spread_time;		// Should News be spreaded ?
	oTNewsSpreadType	spreadType;

	int					news_id;			// whats this news about ?
	zBOOL				gossip;				// Is it gossip ?

	oCNpc*				mNpcWitness;		// Who has seen the News-Event ? Who has spread it into the world ?
	oCNpc*				mNpcOffender;		// Who has done the action, which caused the news ?
	oCNpc*				mNpcVictim;			// who was the victim of this terrible Event ?	
	
	zSTRING				witnessName;
	zSTRING				offenderName;
	zSTRING				victimName;

	zBOOL				guildvictim;		
	
	static	int			news_counter;		// How many News.... ?

};
	
class oCNewsMemory {
public :
	oCNewsMemory				( );
	~oCNewsMemory				( );

	void	Insert				( oCNews* news );
	void	Remove				( oCNews* news );
	oCNews*	GetNews				( int news_id, oCNpc* offender, oCNpc* victim );
	int		SearchNews			( int _newsID, oCNpc* _offender, oCNpc* _victim );
	oCNews* GetNewsByNumber		( int newsNumber );
	zBOOL	DeleteNewsByNumber	( int newsNumber );
	void	ClearNews			();
	void	CheckSpreadNews		( );

	void	ShowDebugInfos		( );

	virtual void		Archive				(zCArchiver &arc);
	virtual void		Unarchive			(zCArchiver &arc);
private:
	// Hier steht drin, was der NSC weiss.....
	// a) SC1 hat einen Söldner umgebracht
	// b) SC1 hat mich bestohlen
	// c) SC1 hat jemand aus meiner Gilde (Schatten) angegriffen... etc.
	zCList <oCNews>		iknow;

};

const int MAX_ENTRY = 20;

class oCNewsManager {
public :

	oCNewsManager				();
	~oCNewsManager				();
	
	//	void	CreatePersonalNews	( int news_id, oCNpc* witness, oCNpc* offender, oCNpc* victim, zBOOL allowSpread = FALSE);
	void	CreateNews			( int newsid, zBOOL gossip, oCNpc* witness, oCNpc* offender, oCNpc* victim, zBOOL guildvictim );
	void	SpreadNews			( oCNews* news );
	void	SpreadToGuild		( int guildnr );
	zBOOL	IsInSpreadList		( int guildnr );

	int		called_BAssessAndMem;

private :
	int		sentry;
	int		spreadList			[MAX_ENTRY];
};

#endif 
 /******************************************************************************** 
 
     $Workfile:: oGameExternal.cpp    $                $Date:: 19.03.01 6:36    $
     $Revision:: 195                  $             $Modtime:: 19.03.01 6:17    $
       $Author:: Edenfeld                                                       $
    Subproject:: Gothic
     Copyright:: 1998-2000, Piranha Bytes GmbH
 
   Description:
   

 * $Log: /current_work/Gothic/_Ulf/oGameExternal.cpp $
 * 
 * 195   19.03.01 6:36 Edenfeld
 * Wld_PlayEffect()
 * 
 * 194   16.02.01 18:31 Wohlers
 * 
 * 193   14.02.01 21:00 Wohlers
 * 
 * 192   14.02.01 19:13 Wohlers
 * 
 * 191   13.02.01 20:36 Speckels
 * 
 * 190   13.02.01 20:28 Speckels
 * 
 * 189   13.02.01 19:11 Wohlers
 * 
 * 188   13.02.01 18:15 Speckels
 * 
 * 187   8.02.01 14:53 Moos
 * 
 * 186   7.02.01 12:53 Moos
 * 
 * 185   30.01.01 23:38 Keskenti
 * 
 * 184   29.01.01 14:28 Keskenti
 * 
 * 183   28.01.01 19:08 Wohlers
 * 
 * 182   27.01.01 16:06 Wohlers
 * 
 * 181   26.01.01 21:55 Speckels
 * 
 * 180   25.01.01 20:09 Wohlers
 * 
 * 179   25.01.01 15:59 Wohlers
 * 
 * 178   23.01.01 16:25 Wohlers
 * 
 * 177   23.01.01 12:04 Moos
 * 
 * 176   22.01.01 22:38 Wohlers
 * 
 * 175   22.01.01 20:21 Moos
 * 
 * 174   22.01.01 20:16 Keskenti
 * 
 * 173   22.01.01 18:59 Wohlers
 * 
 * 172   18.01.01 14:48 Keskenti
 * 
 * 171   18.01.01 2:00 Wohlers
 * 
 * 170   17.01.01 16:57 Keskenti
 * 
 * 169   16.01.01 17:27 Keskenti
 * 
 * 168   16.01.01 17:25 Keskenti
 * 
 * 167   16.01.01 16:42 Speckels
 * 
 * 166   15.01.01 20:19 Wohlers
 * 
 * 165   15.01.01 18:23 Speckels
 * 
 * 164   12.01.01 21:01 Edenfeld
 * 
 * 163   12.01.01 16:36 Wohlers
 * 
 * 162   11.01.01 18:29 Wohlers
 * 
 * 161   11.01.01 15:32 Wohlers
 * 
 * 160   11.01.01 1:08 Keskenti
 * 
 * 159   8.01.01 21:16 Wohlers
 * 
 * 158   8.01.01 14:55 Wohlers
 * 
 * 157   20.12.00 21:01 Keskenti
 * 
 * 156   19.12.00 17:38 Wohlers
 * 
 * 155   19.12.00 13:40 Wohlers
 * 
 * 154   19.12.00 12:58 Keskenti
 * 
 * 153   19.12.00 12:06 Keskenti
 * 
 * 152   15.12.00 17:21 Keskenti
 * 
 * 151   12.12.00 20:34 Keskenti
 * 
 * 150   12.12.00 13:32 Keskenti
 * 
 * 149   7.12.00 22:14 Keskenti
 * 
 * 148   5.12.00 21:57 Speckels
 * 
 * 147   5.12.00 18:56 Speckels
 * 
 * 146   1.12.00 16:58 Speckels
 * 
 * 145   1.12.00 3:07 Speckels
 * 
 * 143   29.11.00 12:52 Speckels
 * 
 * 142   27.11.00 14:08 Keskenti
 * 
 * 141   27.11.00 11:31 Keskenti
 * 
 * 140   24.11.00 15:45 Wohlers
 * 
 * 139   17.11.00 16:07 Keskenti
 * 
 * 138   15.11.00 13:12 Wohlers
 * 
 * 137   14.11.00 14:30 Wohlers
 * 
 * 136   8.11.00 19:21 Speckels
 * 
 * 135   8.11.00 17:47 Speckels
 * 
 * 134   8.11.00 13:24 Wohlers
 * 
 * 133   6.11.00 18:17 Wohlers
 * 
 * 132   2.11.00 16:13 Speckels
 * 
 * 131   27.10.00 11:52 Keskenti
 * 
 * 130   26.10.00 21:49 Keskenti
 * 
 * 129   26.10.00 17:54 Keskenti
 * 
 * 128   26.10.00 17:03 Keskenti
 * 
 * 127   25.10.00 17:57 Wohlers
 * 
 * 126   25.10.00 17:44 Keskenti
 * 
 * 125   24.10.00 20:54 Keskenti
 * 
 * 124   23.10.00 23:27 Keskenti
 * 
 * 123   21.10.00 1:19 Keskenti
 * 
 * 122   20.10.00 22:46 Keskenti
 * 
 * 121   20.10.00 19:08 Keskenti
 * 
 * 120   20.10.00 18:54 Keskenti
 * 
 * 119   18.10.00 17:15 Keskenti
 * 
 * 118   13.10.00 14:32 Speckels
 * 
 * 117   9.10.00 14:14 Keskenti
 * 
 * 116   6.10.00 17:02 Keskenti
 * 
 * 115   6.10.00 13:45 Keskenti
 * 
 * 114   6.10.00 13:38 Keskenti
 * 
 * 113   6.10.00 13:04 Keskenti
 * 
 * 112   6.10.00 12:44 Keskenti
 * 
 *********************************************************************************/

#ifndef _GAMEEXTERNALS_H_
#define _GAMEEXTERNALS_H_

#include "zCore.h"

#include "z3d.h"
#include "zModel.h"
#include "zMorphMesh.h"
#include "zSound.h"
#include "zSky.h"
#include "zSndMSS.h"
#include "zWayNet.h"
#include "zEventMan.h"
#include "zCCSManager.h"
#include "zmenu.h"
#include "zccspool.h"
#include "zPhysics.h"
#include "zParser.h"
#include "zParser_Const.h"
#include "zFonts.h"
#include "oDialog.h"
#include "oItem.h"
#include "oInfo.h"
#include "oWorld.h"
#include "oNpc.h"
#include "oMagic.h"
#include "oMission.h"
#include "oAIHuman.h"
#include "oAniCtrl.h"
#include "oWorld.h"
#include "oGame.h"
#include "oMobInter.h"
#include "oDoc.h"
#include "oGuilds.h"
#include "oPortals.h"
#include "oSpawn.h"
#include "ogamemanager.h"
#include "oNpcMessages.h"
#include "zCCSPlayer.h"
#include "oIncDialogs.h"
#include "oDocumentManager.h"
#include "oInformationManager.h"
#include "oLogManager.h"
#include "oVisFX.h"

#include "zAccount.h"

#pragma warning ( disable:4244 )

//#define GOLDMASTER

#ifndef GOLDMASTER
	//#define CHECK_SCRIPT_VERY_PARANOID
	#define CHECK_SCRIPT_PARANOID
	#pragma warning ( disable:4189 )

	static int s_dbgLevel = 1;

	static inline void DebugOut(const zSTRING &debugString, const zBOOL showCallstack )
	{

	#ifdef CHECK_SCRIPT_PARANOID

		if (s_dbgLevel == 0)
		{
			return;
		}
		else if (s_dbgLevel == 1)
		{
			zERR_WARNING("C: SCRIPT: " + debugString);
		}
		else
		{
			zERR_FAULT_ONCE("C: SCRIPT: " + debugString);
			zERR_WARNING   ("C: SCRIPT: " + debugString);
		}

		if (!showCallstack) return;
		zCPar_Symbol *funcSym = parser.GetSymbol(parser.GetCurrentFunc());
		if (funcSym) zERR_WARNING("C: SCRIPT: last parser func-name: " + funcSym->name);
	#endif


	};

	static oCNpc* PopAndCheckValidNPC(const zSTRING &funcName, const zBOOL showCallstack )
	{
		zCParser *p = zCParser::GetParser();
		oCNpc *npc;

		if (s_dbgLevel==0)
		{
		   return dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance());
		}

		int index;
		npc = dynamic_cast<oCNpc*>((zCVob*)p -> GetInstanceAndIndex(index));

		zCPar_Symbol *testSym = p->GetSymbol(index);

		if (!dynamic_cast<oCNpc*>((zCVob*)testSym->GetOffset()))
		{
			// unbekanntes symbol: a) fehlerhaft initialisiert (z.B. C_NPC.self==0)
			if (testSym->GetOffset()==0) 
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is NULL.", showCallstack); 
			}
			else if (dynamic_cast<oCItem*>((zCVob*)testSym->GetOffset()))
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is an item and not a npc. ", showCallstack); 
			}
			else if (dynamic_cast<oCMOB*>((zCVob*)testSym->GetOffset()),showCallstack)
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is a mob and not a npc. ",showCallstack); 
			}
			else if (dynamic_cast<zCVob*>((zCVob*)testSym->GetOffset()),showCallstack)
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is a vob and not a npc. ",showCallstack); 
			}
			else
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is invalid (bug? -> contact me!). ",showCallstack); 
			};
		}
		return npc;
	};
	static oCItem* PopAndCheckValidItem(const zSTRING &funcName, const zBOOL showCallstack )
	{
		zCParser *p = zCParser::GetParser();
		oCItem *item;

		if (s_dbgLevel==0)
		{
		   return dynamic_cast<oCItem*>((zCVob*)p -> GetInstance());
		}

		int index;
		item = dynamic_cast<oCItem*>((zCVob*)p -> GetInstanceAndIndex(index));

		zCPar_Symbol *testSym = p->GetSymbol(index);

		if (!dynamic_cast<oCItem*>((zCVob*)testSym->GetOffset()))
		{
			// unbekanntes symbol: a) fehlerhaft initialisiert (z.B. C_NPC.self==0)
			if (testSym->GetOffset()==0) 
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is NULL.", showCallstack); 
			}
			else if (dynamic_cast<oCMOB*>((zCVob*)testSym->GetOffset()),showCallstack)
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is a mob and not an item. ",showCallstack); 
			}
			else if (dynamic_cast<zCVob*>((zCVob*)testSym->GetOffset()),showCallstack)
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is a vob and not an item. ",showCallstack); 
			}
			else
			{
				DebugOut(funcName + "(): illegal param: \"" + testSym->name + "\" is invalid (bug? -> contact me!). ",showCallstack); 
			};
		}
		return item;
	};



#else
	#define DebugOut(in,flag) 
	#define PopAndCheckValidNPC(str,flag) dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());
	#define PopAndCheckValidItem(str,flag) dynamic_cast<oCItem*>((zCVob*)p -> GetInstance ());
#endif



// ****************************************************************************************
// Save & Restore Parser Vars
// ****************************************************************************************

oCNpc* oldSelfNpc	= NULL;
oCNpc* oldOtherNpc	= NULL;
oCNpc* oldVictimNpc	= NULL;

static void SaveParserVars()
{
	oldSelfNpc		= NULL;
	oldOtherNpc		= NULL;
	oldVictimNpc	= NULL;

	// Save self & other
	zCPar_Symbol* sym		= parser.GetSymbol("SELF");
	if (sym) oldSelfNpc		= dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
	sym						= parser.GetSymbol("OTHER");
	if (sym) oldOtherNpc	= dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
	sym						= parser.GetSymbol("VICTIM");
	if (sym) oldVictimNpc	= dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
}

static void RestoreParserVars()
{
	parser.SetInstance("SELF"	,oldSelfNpc);
	parser.SetInstance("OTHER"	,oldOtherNpc);
	parser.SetInstance("VICTIM"	,oldVictimNpc);
}

// ****************************************************************************************
// Documents
// ****************************************************************************************

/* ----------------------------------------------------------------------
	
	Doc_Create()


	20-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_CreateMap()
{
	int nDocID = -1;

	//
	//	GET DOC MANAGER
	//
	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	nDocID = mgrDoc.CreateMap();

	//
	//	RETURN DOCUMENT HANDLE
	//
	::parser.SetReturn( nDocID );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_Create()


	20-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_Create()
{
	int nDocID = -1;

	//
	//	GET DOC MANAGER
	//
	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	nDocID = mgrDoc.CreateDocument();

	//
	//	RETURN DOCUMENT HANDLE
	//
	::parser.SetReturn( nDocID );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_SetPages()


	20-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_SetPages()
{
	int nPages = -1;
	int nDocID = -1;

	zCParser *p = zCParser::GetParser();
	p->GetParameter( nPages );
	p->GetParameter( nDocID );

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.SetPages( nDocID, nPages );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_SetPage()


	20-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_SetPage()
{
	int		nPage		= -1;
	int		nDocID		= -1;
	zBOOL	bScale		= FALSE;
	zSTRING	strTexture	= "";

	zCParser *p = zCParser::GetParser();

	p->GetParameter( bScale		);
	p->GetParameter( strTexture	);
	p->GetParameter( nPage		);
	p->GetParameter( nDocID		);

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.SetPage( nDocID, nPage, strTexture, bScale );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_SetMargins()


	20-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_SetMargins()
{
	int		nPage	= -1;
	int		nDocID	= -1;
	int		nLeft	= -1;
	int		nTop	= -1;
	int		nRight	= -1;
	int		nBottom	= -1;
	int		bPixels	= TRUE;

	zCParser *p = zCParser::GetParser();

	p->GetParameter( bPixels	);
	p->GetParameter( nBottom	);
	p->GetParameter( nRight	);
	p->GetParameter( nTop		);
	p->GetParameter( nLeft	);
	p->GetParameter( nPage	);
	p->GetParameter( nDocID	);

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.SetMargins( nDocID, nPage, zPOS( nLeft, nTop ), zPOS( nRight, nBottom ), bPixels );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_SetFont()


	20-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_SetFont()
{
	int		nPage	= -1;
	int		nDocID	= -1;
	zSTRING	strFont	= "";

	zCParser *p = zCParser::GetParser();

	p->GetParameter( strFont	);
	p->GetParameter( nPage	);
	p->GetParameter( nDocID	);

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.SetFont( nDocID, nPage, strFont );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_SetLevel()


	16-Jan-2001	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_SetLevel()
{
	int		nDocID		= -1;
	zSTRING	strLevel		;

	zCParser *p = zCParser::GetParser();

	p->GetParameter( strLevel );
	p->GetParameter( nDocID	);

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.SetLevel( nDocID, strLevel );

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////
//	
//	Doc_SetLevelCoords()
//
//	2002-08-19	[Bendlin]
//
//				Initial implementation
//
//////////////////////////////////////////////////////////////////////////////

static zBOOL Doc_SetLevelCoords()
{
	int		doc		= -1;
	int		left	= 0;
	int		top		= 0;
	int		right	= 0;
	int		bottom	= 0;

	zCParser *p = zCParser::GetParser();

	p->GetParameter( bottom );
	p->GetParameter( right );
	p->GetParameter( top );
	p->GetParameter( left );
	p->GetParameter( doc );

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.SetLevelCoords( doc, left, top, right, bottom );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_PrintLine()


	20-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_PrintLine()
{
	int		nPage	= -1;
	int		nDocID	= -1;
	zSTRING	strText	= "";

	zCParser *p = zCParser::GetParser();

	p->GetParameter( strText	);
	p->GetParameter( nPage	);
	p->GetParameter( nDocID	);

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.PrintLine( nDocID, nPage, strText );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_PrintLines()


	20-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_PrintLines()
{
	int		nPage	= -1;
	int		nDocID	= -1;
	zSTRING	strText	= "";

	zCParser *p = zCParser::GetParser();

	p->GetParameter( strText	);
	p->GetParameter( nPage	);
	p->GetParameter( nDocID	);

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.PrintLines( nDocID, nPage, strText );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Doc_Show()


	24-Oct-2000	[Roman Keskenti]
					
					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Doc_Show()
{
	int		nDocID	= -1;

	zCParser *p = zCParser::GetParser();

	p->GetParameter( nDocID	);

	static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
	mgrDoc.Show( nDocID );

	return FALSE;
}


static zBOOL Doc_Open()
{
	zSTRING name;
	zCParser *p	= zCParser::GetParser();
	p->GetParameter( name );

	if (!name.IsEmpty()) 
	{
		if (document) delete(document);
		document = zNEW(oCDoc(name));
		document -> Show();
	}
	else DebugOut("Dop_Open(): invalid param!", TRUE);

	return FALSE;
}

static zBOOL Doc_Print()
{
	zSTRING name;
	zCParser *p	= zCParser::GetParser();
	p->GetParameter(name);

	if (document) {
		document->Printwin(name+"\n");
	}
	else DebugOut("Doc_Print(): no document to print text: " + name, TRUE);

	return FALSE;
}
 
static zBOOL Doc_Font()
{
	zSTRING name;
	zCParser *p	= zCParser::GetParser();
	p->GetParameter(name);

	if (document) {
		document->SetFont(name);
	}
	else DebugOut("Doc_Font(): no document to set font: " + name, TRUE);

	return FALSE;
}

static zBOOL Doc_MapCoordinates()
{
	zSTRING name;
	zREAL gcx1, gcy1, gcx2, gcy2;
	zREAL px1, py1, px2, py2;
	zCParser *p	= zCParser::GetParser();
	
	p->GetParameter(py2);
	p->GetParameter(px2);
	p->GetParameter(gcy2);
	p->GetParameter(gcx2);
	p->GetParameter(py1);
	p->GetParameter(px1);
	p->GetParameter(gcy1);
	p->GetParameter(gcx1);
	p->GetParameter(name);

	if (document) 
	{
		oCNpc* npc;
		document->MapInitCoordinates(gcx1,gcy1,px1,py1,gcx2,gcy2,px2,py2);
		document->SetLevelName		(name);
		npc = ogame->GetSelfPlayerVob();
		if (npc) {
			zVEC3 pos = npc->GetPositionWorld();			
			document->MapDrawCoordinates(pos[VX],pos[VZ]);
		}
	}
	else DebugOut("Doc_Mapcoordinates(): no document to set coords. levelname: " + name, TRUE);

	return FALSE;
}

// ****************************************************************************************
// News
// ****************************************************************************************

static zBOOL Npc_MemoryEntry	()
// (VAR C_NPC self, VAR INT source, VAR C_NPC offender, VAR INT newsid, VAR C_NPC victim);
{
	int source;
	int newsid;	
	zCParser *p		= zCParser::GetParser();

	oCNpc* victim   = PopAndCheckValidNPC("Npc_MemoryEntry", TRUE);
	p -> GetParameter (newsid);
	oCNpc* offender = PopAndCheckValidNPC("Npc_MemoryEntry", TRUE);
	p -> GetParameter (source);
	oCNpc* witness	= PopAndCheckValidNPC("Npc_MemoryEntry", TRUE);

// Checks, ob Werte valid sollten im Create-News passieren
	ogame -> GetNewsManager()->CreateNews(newsid,source,witness,offender,victim,FALSE);

	return FALSE;
};

static zBOOL Npc_MemoryEntryGuild ()
// Gilde wird als Opfer betrachtet
// (VAR C_NPC self, VAR INT source, VAR C_NPC offender, VAR INT newsid, VAR C_NPC victim);
{
	int source;
	int newsid;
	zCParser *p		= zCParser::GetParser();
	oCNpc* victim	= PopAndCheckValidNPC("Npc_MemoryEntryGuild", TRUE);
	p -> GetParameter (newsid);
	oCNpc* offender = PopAndCheckValidNPC("Npc_MemoryEntryGuild", TRUE);
	p -> GetParameter (source);
	oCNpc* witness	= PopAndCheckValidNPC("Npc_MemoryEntryGuild", TRUE);

	// Checks, ob Werte valid sollten im Create-News passieren
	ogame -> GetNewsManager()->CreateNews(newsid,source,witness,offender,victim,TRUE);
	return FALSE;
};

// ****************************************************************************************
// Information
// ****************************************************************************************

/*--------------------------------------------------------------------------

    NotifyInfoToSpy()			[static]

    20-Nov-00       [Roman Keskenti]

					  Initial implementation

--------------------------------------------------------------------------*/ 
void NotifyInfoToSpy( zSTRING& str )	
{ 
	//
	//	OUTPUT DEBUG MESSAGE
	//
	zERR_MESSAGE( 8, 0, "R: INF: " + str );  // [SPECKELS] von 6 auf 8 gesetzt
}

/*--------------------------------------------------------------------------

    NotifyInfoToSpy()			[static]

    20-Nov-00       [Roman Keskenti]

					  Initial implementation

--------------------------------------------------------------------------*/ 
void NotifyInfoToSpy( char* pszMethod, char* pszOutput, char* pszStatus )	
{ 
	//
	//	OUTPUT DEBUG MESSAGE
	//
	zSTRING strMethod( pszMethod );
	zSTRING strOutput( pszOutput );
	zSTRING strStatus( pszStatus );	strStatus = "[" + strStatus + "]";
	zSTRING strMessage;

	strMethod.Align( zSTR_LEFT, 30 );
	strOutput.Align( zSTR_LEFT, 30 );
	strStatus.Align( zSTR_LEFT, 30 );

	strMessage = strMethod + "->" + strOutput + strStatus;
}

/*--------------------------------------------------------------------------

    AI_StopProcessInfos()

 

    19-Oct-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
static zBOOL AI_StopProcessInfos()
{

	zCParser *p			= zCParser::GetParser();
	oCNpc	 *pPlayer	= dynamic_cast< oCNpc* >  ( ::ogame->GetSelfPlayerVob() );

	oCNpc	 *pSelf		= PopAndCheckValidNPC("AI_StopProcessInfos", TRUE);

	if ( pSelf )																								
	{																											
		oCMsgConversation* pMsg = zNEW( oCMsgConversation ) ( oCMsgConversation::EV_STOPPROCESSINFOS, pSelf );	
		pSelf->GetEM()->OnMessage( pMsg, pPlayer );
	}

	return FALSE;
}

/*--------------------------------------------------------------------------

    AI_ProcessInfos()

 

    19-Oct-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
static zBOOL AI_ProcessInfos()
{

	zCParser *p			= zCParser::GetParser();
	oCNpc	 *pPlayer	= dynamic_cast< oCNpc* >  ( ::ogame->GetSelfPlayerVob() );
	oCNpc	 *pSelf		= PopAndCheckValidNPC("AI_ProcessInfos", TRUE);

	//
	//	DO NOT START TWICE 
	//
	oCInformationManager&	mgrInfos	= oCInformationManager::GetInformationManager();						
	zBOOL					bFinished	= mgrInfos.HasFinished();												

	if ( bFinished )																							
	{																											
		if ( pSelf )																							
		{
			oCMsgConversation* pMsg = zNEW( oCMsgConversation ) ( oCMsgConversation::EV_PROCESSINFOS, pSelf );	
			pSelf->GetEM()->OnMessage( pMsg, pPlayer );														
		}
	}

	return FALSE;
}

/*--------------------------------------------------------------------------

    InfoManager_HasFinished()

 

    23-Oct-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
static zBOOL InfoManager_HasFinished()
{
	oCInformationManager&	mgrInfos	= oCInformationManager::GetInformationManager();						
	zBOOL					bFinished	= mgrInfos.HasFinished();												

	zCParser::GetParser()->SetReturn( bFinished );

	return FALSE;
}

/*--------------------------------------------------------------------------

    Info_AddChoice()

 

    23-Oct-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
static zBOOL Info_AddChoice()
{
	int		nInfoInstance, nFunc;
	zSTRING strText;

	zCParser *p = zCParser::GetParser();

	p->GetParameter	( nFunc			);
	p->GetParameter	( strText		);
	p->GetParameter	( nInfoInstance );

	oCInfo* pInfo = NULL;
	pInfo = ::ogame->GetInfoManager()->GetInformation( nInfoInstance );

	if ( pInfo )
	{
		pInfo->AddChoice( strText, nFunc );
	}
#ifdef CHECK_SCRIPT_PARANOID
	else 
	{
		zCPar_Symbol *sym = parser.GetSymbol(nInfoInstance);
		zSTRING infoString = sym ? sym->name : zSTRING(nInfoInstance);
		DebugOut("Info_AddChoice(): wrong or non-existant info with instance-id: " + infoString + ", with text: " + strText, TRUE);
	}
#endif

	return FALSE;
}

/*--------------------------------------------------------------------------

    Info_ClearChoices()

 

    23-Oct-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
static zBOOL Info_ClearChoices()
{
	int		nInfoInstance;

	zCParser *p = zCParser::GetParser();

	p->GetParameter	( nInfoInstance );

	oCInfo* pInfo = NULL;
	pInfo = ::ogame->GetInfoManager()->GetInformation( nInfoInstance );

	if ( pInfo )
	{
		pInfo->RemoveAllChoices();
	}
#ifdef CHECK_SCRIPT_PARANOID
	else 
	{
		zCPar_Symbol *sym = parser.GetSymbol(nInfoInstance);
		zSTRING infoString = sym ? sym->name : zSTRING(nInfoInstance);
		DebugOut("Info_ClearChoices(): wrong or non-existant info with instance-id: " + infoString, TRUE);
	}
#endif

	return FALSE;
}

static zBOOL Npc_KnowsInfo()
{
	zBOOL flag = FALSE;
	int instance;
	zCParser *p	= zCParser::GetParser();
	p -> GetParameter(instance);

#ifdef CHECK_SCRIPT_PARANOID
	oCNpc* self = PopAndCheckValidNPC("Npc_KnowsInfo", FALSE);
	if (!self) 
	{
		zCPar_Symbol *sym = parser.GetSymbol(instance);
		zSTRING instanceString = sym ? sym->name : "[UNKNOWN]";
		DebugOut("... infoinstance: " + instanceString, TRUE);
	}
#else
	oCNpc* self = dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());
#endif
	if (self) flag = ogame->GetInfoManager()->InformationTold(instance);

	p -> SetReturn(flag);
	return FALSE;
}

static zBOOL Npc_CheckInfo()
{
	zBOOL		important	= FALSE;
	oCInfo*		info		= NULL;
	zCParser*	p			= zCParser::GetParser();
	p->GetParameter	(important);
	oCNpc*		self		= PopAndCheckValidNPC("Npc_CheckInfo", TRUE);

	if (self) 
	{		
		info = ogame->GetInfoManager()->GetInformation(ogame->GetSelfPlayerVob(),self,important);
	}
	
	p -> SetReturn(info!=NULL);
	return FALSE;
}

static zBOOL Npc_GiveInfo()
{
	zBOOL		important	= FALSE;
	zBOOL		flag		= FALSE;
	oCInfo*		info		= NULL;
	zCParser*	p			= zCParser::GetParser();
	p->GetParameter	(important);
	oCNpc*		self		= PopAndCheckValidNPC("Npc_GiveInfo", TRUE);

	if (self) 
	{		
		info = ogame->GetInfoManager()->GetInformation(ogame->GetSelfPlayerVob(),self,important);
		if (info) 
		{
			info -> Info();
			flag  = TRUE;
		}
	}	
	p -> SetReturn(flag);
	return FALSE;
};

// ****************************************************************************************
// Tagesablauf
// ****************************************************************************************

static zBOOL TA()
{
	int func,hour1,hour2;
	zSTRING wp;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(wp);
	p -> GetParameter(func);
	p -> GetParameter(hour2);
	p -> GetParameter(hour1);

#ifdef CHECK_SCRIPT_PARANOID
	oCNpc* self		= PopAndCheckValidNPC("TA", FALSE);
	if (!self) 
	{
		DebugOut("... wp-name: " + wp, TRUE);
	}
#else
	oCNpc* self		= dynamic_cast<oCNpc*>((zCVob*)p->GetInstance());
#endif

	if (self) 
	{	
		self -> state.InsertRoutine(hour1,0,hour2,0,func,wp);
	}
	return FALSE;
}

static zBOOL TA_Min()
{
	int func,hour1,min1,hour2,min2;
	zSTRING wp;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(wp	);
	p -> GetParameter(func	);
	p -> GetParameter(min2	);
	p -> GetParameter(hour2	);
	p -> GetParameter(min1	);
	p -> GetParameter(hour1	);

#ifdef CHECK_SCRIPT_PARANOID
	oCNpc* self		= PopAndCheckValidNPC("TA_Min", FALSE);
	if (!self) 
	{
		DebugOut("... wp-name: " + wp , TRUE);
	}
#else
	oCNpc* self		= dynamic_cast<oCNpc*>((zCVob*)p->GetInstance());
#endif

	if (self) {	
		self -> state.InsertRoutine(hour1,min1,hour2,min2,func,wp);
	}
	return FALSE;
}

static zBOOL TA_CS()
{
	zSTRING csName, roleName;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(roleName);
	p -> GetParameter(csName);

#ifdef CHECK_SCRIPT_PARANOID

	oCNpc* self		= PopAndCheckValidNPC("TA_Min", FALSE);
	if (!self) 
	{
		DebugOut("... cs-name: " + csName + ", role-name: " + roleName, TRUE);
	}
#else
	oCNpc* self	= dynamic_cast<oCNpc*>((zCVob*)p->GetInstance());
#endif

	if (self) 
	{
		self -> state.InsertRoutineCS(csName,roleName);
	}
	return FALSE;
}

static zBOOL TA_BeginOverlay()
{

	zCParser *p = zCParser::GetParser();
	oCNpc* self	= PopAndCheckValidNPC("TA_BeginOverlay", TRUE);

	if (self) {
		self -> state.BeginInsertOverlayRoutine();
	}
	return FALSE;
}

static zBOOL TA_EndOverlay()
{
	zCParser *p = zCParser::GetParser();
	oCNpc* self	= PopAndCheckValidNPC("TA_EndOverlay", TRUE);

	if (self) 
	{
		self -> state.StopInsertOverlayRoutine();
	}
	return FALSE;
}

static zBOOL TA_RemoveOverlay()
{
	zCParser *p = zCParser::GetParser();
	oCNpc* self	= PopAndCheckValidNPC("TA_RemoveOverlay", TRUE);

	if (self) {
		self -> state.RemoveOverlay();
	}
	return FALSE;
}

static zBOOL Rtn_Exchange()
{
	// Tagesablauf aller NSCs mit angegebenen Namen �ndern
	zBOOL	anyRoutineFound = FALSE;
	zSTRING rtnName,oldRoutine,newRoutine;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(newRoutine);
	p -> GetParameter(oldRoutine);
	oldRoutine.Upper(); newRoutine.Upper();
	
	zCListSort<oCNpc>*	npcNode = ogame->GetGameWorld()->GetVobListNpcs()->GetNextInList();
	oCNpc*				npc		= NULL;
	while (npcNode) {
		npc		= npcNode->GetData();
		npcNode = npcNode->GetNextInList();
		if (npc && !npc->IsSelfPlayer() && npc->state.HasRoutine()) {
			rtnName = npc->state.GetRoutineName();
			if (rtnName.Search(oldRoutine)>=0) 
			{
				SaveParserVars();
				npc->state.ChangeRoutine(newRoutine);
				RestoreParserVars();
				anyRoutineFound = TRUE;
			}
		}
	}

#ifdef CHECK_SCRIPT_PARANOID
	if (!anyRoutineFound) DebugOut("Rtn_Exchange(): no npc found with routine: " + oldRoutine, TRUE);
#endif

	return FALSE;
}


static zBOOL Npc_ExchangeRoutine()
{
	zSTRING routineName;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(routineName);
#ifdef CHECK_SCRIPT_PARANOID
	oCNpc* self		= PopAndCheckValidNPC("Npc_ExchangeRoutine", FALSE);
	if (!self) 
	{
		DebugOut("... routineName: " + routineName, TRUE);
	}

#else
	oCNpc* self		= dynamic_cast<oCNpc*>((zCVob*)p->GetInstance());
#endif

	if (self) 
	{
		SaveParserVars();
		self -> state.ChangeRoutine(routineName);
		RestoreParserVars();
	}
	return FALSE;
}

static zBOOL Wld_SetTime()
{
	zSTRING wp;
	int day,hour,min;
	ogame->GetTime(day,hour,min);
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(min);
	p -> GetParameter(hour);
	ogame->SetTime(day,hour,min);
	return FALSE;
}

static zBOOL Wld_SendTrigger()
{
	zSTRING vobName;
	zCParser *p = zCParser::GetParser();
	p->GetParameter(vobName);
	zCVob* vob = ogame->GetWorld()->SearchVobByName(vobName);
	if (vob) {
		vob->GetEM()->OnTrigger(vob,vob);
	} else {
		DebugOut("Script tries to send trigger to "+vobName+". Failure : vob not found.", TRUE);
	}
	return FALSE;
};

static zBOOL Wld_SendUntrigger()
{
	zSTRING vobName;
	zCParser *p = zCParser::GetParser();
	p->GetParameter(vobName);
	zCVob* vob = ogame->GetWorld()->SearchVobByName(vobName);
	if (vob) {
		vob->GetEM()->OnUntrigger(vob,vob);
	} else {
		DebugOut("Script tries to send untrigger to "+vobName+". Failure : vob not found.", TRUE);
	}
	return FALSE;
};

/* ----------------------------------------------------------------------
	
	AI_Teleport()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_Teleport()
{
	zSTRING name;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(name);
	oCNpc* self		= PopAndCheckValidNPC("AI_Teleport", TRUE);

	if (self)
	{
		// [BENDLIN] Addon Patch - Update Position if NPC is not in World! (>40m)
		if (!self->IsSelfPlayer() && !self->GetHomeWorld() && !self->GetEM()->GetCutscene())
			self->BeamTo(name);
		else
			self->GetEM()->OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_BEAMTO, name), self);
	}
	return TRUE;
}

// ****************************************************************************************
// Perception
// ****************************************************************************************

static zBOOL Perc_SetRange ()
{
	int percID,percRange;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter			(percRange);
	p -> GetParameter			(percID);
	oCNpc :: SetPerceptionRange	(percID,percRange);
	return FALSE;
}

static zBOOL Npc_SetPercTime ()
{
	zREAL deltaSeconds;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(deltaSeconds);
	oCNpc* self	= PopAndCheckValidNPC("Npc_SetPercTime", TRUE);

	if (self) {
		self -> SetPerceptionTime(deltaSeconds * 1000);
	}
	return FALSE;
};

static zBOOL Npc_PercEnable ()
{
	int percID,func;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(func);
	p -> GetParameter(percID);
	oCNpc* self		= PopAndCheckValidNPC("Npc_SetPercTime", TRUE);

	if (self) {
		self -> EnablePerception(percID,func);
	}
	return FALSE;
};

static zBOOL Npc_PercDisable ()
{
	int percID;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(percID);
	oCNpc* self	 = PopAndCheckValidNPC("Npc_PercDisable", TRUE);
	if (self) {
		self -> DisablePerception(percID);
	}
	return FALSE;
};

static zBOOL Npc_IsInCutscene ()
{
	zBOOL flag	= FALSE;
	zCParser *p = zCParser::GetParser();
	oCNpc* self		= PopAndCheckValidNPC("Npc_IsInCutscene", TRUE);
	if (self) flag = self->GetEM()->GetCutsceneMode();
	p->SetReturn(flag);
	return FALSE;	
}

static zBOOL Npc_IsVoiceActive()
{
	zBOOL flag	= FALSE;
	zCParser *p = zCParser::GetParser();
	oCNpc* self	= PopAndCheckValidNPC("Npc_IsVoiceActive", TRUE);
	if (self) {
		flag =	self->GetEM()->GetCutsceneMode() ||
				self->IsVoiceActive();
	}	
	p->SetReturn(flag);
	return FALSE;	
}


static zBOOL Npc_StopAni()
{
	zCParser *p = zCParser::GetParser();
	zSTRING ani;
	p -> GetParameter(ani);
	oCNpc* self	= PopAndCheckValidNPC("Npc_StopAni", TRUE);
	if (self) 
	{
		self->GetModel()->StopAni(self->GetModel()->GetAniFromAniName(ani));

		//
		//	DELETE ANIMATION MESSAGES
		//
		oCMsgConversation *	pMsg		= NULL;
		int					nMessages	= self->GetEM()->GetNumMessages();
		int					nMessage	= 0;

		for (	; nMessage < nMessages; nMessage++ ) 
		{
			pMsg = zDYNAMIC_CAST< oCMsgConversation > ( self->GetEM()->GetEventMessage( nMessage ) );

			if ( pMsg )
			if ( pMsg->GetSubType() == oCMsgConversation::EV_PLAYANI_NOOVERLAY	) 
			if ( pMsg->name			== ani							)
			{
				pMsg->Delete();
			}
		}
	}
	return FALSE;
}



// ****************************************************************************************
// Welt - Funktionen um auf aktuell gefundene Objekte zu reagieren 
// ****************************************************************************************

static zBOOL Wld_SetObjectRoutine()
{
	zSTRING name;
	int state,hour1,min1;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(state);
	p -> GetParameter(name);
	p -> GetParameter(min1);
	p -> GetParameter(hour1);

#ifdef CHECK_SCRIPT_PARANOID
	zCVob* vob = ogame->GetGameWorld()->SearchVobByName(name);
	if (!vob) DebugOut("Wld_SetObjectRoutine(): could not find a vob with name: " + name, TRUE);
#endif

	ogame->InsertObjectRoutine(1,name,hour1,min1,state);
	return FALSE;
}

static zBOOL Wld_SetMobRoutine()
{
	zSTRING name;
	int state,hour1,min1;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(state);
	p -> GetParameter(name);
	p -> GetParameter(min1);
	p -> GetParameter(hour1);

#ifdef CHECK_SCRIPT_PARANOID
	zCVob* vob = ogame->GetGameWorld()->SearchVobByName(name);
	if (!vob) DebugOut("Wld_SetMobRoutine(): could not find a vob with name: " + name, TRUE);
#endif

	ogame->InsertObjectRoutine(0,name,hour1,min1,state);
	return FALSE;
}

static zBOOL Wld_InsertNpc()
{
	int index;
	zSTRING posPoint;
	
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(posPoint);
	p -> GetParameter(index);
	oCNpc* npc	= ogame -> GetSpawnManager()->SpawnNpc(index,posPoint,0.0f);
	
	// Respawning off !!!!!!!!!!!
	if (npc) 
	{
		npc->SetCanRespawn(FALSE);	
		if (ogame && !ogame->IsInScriptStartup() && npc->state.HasRoutine()) {
			// zur Laufzeit eingefuegt.
			rtnMan.UpdateSingleRoutine(npc);
		}
	}
#ifdef CHECK_SCRIPT_PARANOID
	else 
	{
		zCPar_Symbol *sym = parser.GetSymbol(index);
		zSTRING infoString = sym ? sym->name : "[UNKNOWN]";
		DebugOut("Wld_InsertNpc(): called with illegal index. instance: " + infoString + ", position: " + posPoint, TRUE);
	}
#endif
/*	
	oCNpc* npc = (oCNpc*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_NSC,index);
	if (npc) {
	
		// Looking for posPoint
		zVEC3 pos		(100,100,100);
		zCVob* posVob	= ogame->GetGameWorld()->SearchVobByName(posPoint);
		if (posVob) {
	        pos		= posVob->GetPositionWorld();
			found	= TRUE;
		} else {
			zCWaypoint* wp	= ogame->GetGameWorld()->GetWayNet()->GetWaypoint(posPoint);
			if (wp)		pos	= wp->GetPositionWorld();
			found	= (wp!=NULL);
		}
		if (!found) zERR_WARNING("U:WLD: Position-Vob "+posPoint+" not found.");

		npc		-> SetCollDet		(FALSE);
		npc		-> SetPositionWorld	(pos);
		ogame	-> GetWorld			() -> AddVob(npc);
		npc		-> GetRigidBody() -> SetVelocity(zVEC3(0,1,0));
		npc		-> GetFloorPosition	(pos);
		npc		-> SearchNpcPosition(pos);
		npc		-> SetPositionWorld	(pos);
		npc		-> Release			();
		npc		-> SetCollDet		(TRUE);
		ogame	-> GetGameWorld() -> DisableVob(npc);

		// Zustandsgesteuert, PositionPoint speichern
		if (npc->state.IsAIStateDriven()) {
			npc->state.InitAIStateDriven(pos);
		}
	}*/
	return FALSE;
}

static zBOOL Wld_RemoveNpc()
{
	int				index;
	zCParser*		p			= zCParser::GetParser();
	oCSpawnManager* pSpawnManager	= ::ogame->GetSpawnManager();

	p -> GetParameter(index);
	zCPar_Symbol* sym = p->GetSymbol(index);
	if (sym && (sym->type==zPAR_TYPE_INSTANCE)) {
		
		zCVob* pVob = ogame->GetWorld()->SearchVobByName(sym->name);
		oCNpc* pNpc = dynamic_cast<oCNpc*>(pVob);
		if (pNpc && pSpawnManager) {
			
			// Und NSC komplett removen.			
			pSpawnManager->DeleteNpc(pNpc);			
		}
#ifdef CHECK_SCRIPT_PARANOID
		else 
		{
			DebugOut("Wld_RemoveNpc(): npc could not be removed, no spawnmanager or instance is not an npc (name:" + sym->name + ")", TRUE);
		}
#endif
	}
	else DebugOut("Wld_RemoveNpc(): npc could not be removed (illegal nsc ?)", TRUE);

	return FALSE;
};

// codechange [CARSTEN]
static zBOOL Wld_SpawnNpcRange()
{
	int		nIndex;
	int		nCount;
	float	fRange;
	
	zCParser*		p				= zCParser::GetParser();
	oCSpawnManager* pSpawnManager	= ::ogame->GetSpawnManager();

	p	-> GetParameter( fRange );
	p	-> GetParameter( nCount );
	p	-> GetParameter( nIndex );

	oCNpc* self = PopAndCheckValidNPC("Wld_SpawnNpcRange", TRUE);

	if (!self) return FALSE;

	static const int ANGLE_STEP = 18;

	oCNpc*	pMonster	; 
	zVEC3	vecPosition ; 
	zMAT4	newMat		; 
	zPOINT3	selfPos		; 
	float   angle		; 
	float	sign		; 
	int		tries		; 

	//
	//	FOR EACH MONSTER TO BE SPAWNED
	//
	for ( int i = 0; i < nCount; i++ )
	{
		pMonster	= NULL;
		selfPos		= self->GetPositionWorld();
		vecPosition = selfPos + 150 * self->GetAtVectorWorld();
		newMat		= self->trafoObjToWorld;
		angle		= 0;
		sign		= 1;
		tries		= (360/ANGLE_STEP) -1;		

		do
		{
			//
			//	TRY TO SPAWN IT AT CURRENT LOCATION
			//
			pMonster = pSpawnManager->SummonNpc( nIndex, vecPosition, 0.0f );

			//
			//	START SPAWN ANIMATION
			//
			if ( pMonster )
			{
				 pMonster->GetModel()->StartAni( "T_SPAWN" );
				 tries = 0;
			}
			else
			//
			//	SEEK FREE SPACE AROUND SPAWN POSITION
			//
			{
				//
				//	TRANSLATE MATRIX RANDOMLY WITHIN RANGE
				//
				vecPosition = selfPos + ( zRandF( fRange ) + 100 ) * newMat.GetAtVector();
				newMat.SetTranslation( vecPosition );

				//
				//	ROTATE MATRIX OSCILATING CLOCKWISE 
				//
				float advanceRot = sign * ANGLE_STEP;
				newMat.PostRotateY(advanceRot);
				angle += advanceRot;

				if (angle>=90) 
				{	
					newMat = self->trafoObjToWorld;
					newMat.PostRotateY(-ANGLE_STEP);
					angle  = -ANGLE_STEP;
					sign   = -1;
				}

				//
				//	RE-GET NEW ROTATED TRANSLATION
				//
				vecPosition = newMat.GetTranslation();
			}
		}
		while( --tries>=0 );
	}
	
	return FALSE;
};

static zBOOL Wld_PlayEffect()
{
	zCVob*			originVob		= 0;
	zCVob*			targetVob		= 0;
	int				effectLevel		= 1;
	int				damage			= 0;
	int				damageType		= 0;
	int				bIsProjectile	= FALSE;
	oCVisualFX*		newFX			= 0;
	zCParser*		p			= zCParser::GetParser();
	zSTRING			effectInstance;

	p -> GetParameter(bIsProjectile);
	p -> GetParameter(damageType	);
	p -> GetParameter(damage		);
	p -> GetParameter(effectLevel	);

	targetVob = dynamic_cast<zCVob*>((zCVob*)p->GetInstance());
	originVob = dynamic_cast<zCVob*>((zCVob*)p->GetInstance());

	if (originVob == NULL) 
	{
		zERR_WARNING("C: Wld_PlayEffect: Origin Script Instance is NULL!");
		return FALSE;
	}

	p -> GetParameter(effectInstance);

	newFX = oCVisualFX::CreateAndPlay(effectInstance,originVob, targetVob, effectLevel, damage, damageType, bIsProjectile );
	zRELEASE(newFX);

	return FALSE;
};


static zBOOL AI_PlayFX()
{
	oCNpc*			originNpc		= 0;
	zCVob*			targetVob		= 0;
	zCParser*		p				= zCParser::GetParser();
	zSTRING			effectInstance;

	p	-> GetParameter(effectInstance);
	targetVob = zDYNAMIC_CAST<zCVob >((zCVob*)p->GetInstance());
	originNpc = PopAndCheckValidNPC("AI_PlayFX", TRUE);

	if (originNpc == NULL) 
	{
		zERR_WARNING("C: Wld_PlayEffect: Origin Script NPC Instance is unknown!");
		return FALSE;
	}

	oCMsgConversation *msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_STARTFX);
	msg->name = effectInstance;

	originNpc -> GetEM() -> OnMessage(msg, targetVob);

	return FALSE;
};

static zBOOL AI_StopFX()
{
	oCNpc*			originNpc		= 0;
	zCParser*		p			= zCParser::GetParser();
	zSTRING			effectInstance;

	p -> GetParameter(effectInstance);
	originNpc = PopAndCheckValidNPC("AI_StopFX", TRUE);

	if (originNpc == NULL) 	return FALSE;

	oCMsgConversation *msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_STOPFX);
	msg->name = effectInstance;

	originNpc -> GetEM() -> OnMessage(msg, originNpc);

	return FALSE;
};


// codechange [CARSTEN] END

static zBOOL Wld_InsertNpcAndRespawn()
{
	int		index;
	zSTRING posPoint;
	int		sDelay;
	
	zCParser *p = zCParser::GetParser();
	
	p -> GetParameter(sDelay);
	p -> GetParameter(posPoint);
	p -> GetParameter(index);
	oCNpc* npc	= ogame -> GetSpawnManager()->SpawnNpc(index,posPoint,0.0f);
	
	// Respawning on !!!!!!!!!!!
	if (npc) {
		// Spawnpoint wurde von SpawnNpc bereits initialisiert
		// jetzt nur noch spawnDelay setzen.
		npc->spawnDelay = sDelay;	
		npc->SetCanRespawn(TRUE);
		if (ogame && !ogame->IsInScriptStartup() && npc->state.HasRoutine()) {
			// zur Laufzeit eingefuegt.
			rtnMan.UpdateSingleRoutine(npc);
		}
	}
#ifdef CHECK_SCRIPT_PARANOID
	else 
	{
		zCPar_Symbol*sym = parser.GetSymbol(index);
		zSTRING npcName = sym ? sym->name : "[UNKNOWN]";
		DebugOut("Wld_InsertNpcAndRespawn(): npc could not be spawned (illegal nsc ? not enough place ?): spawnpoint: " + posPoint + ", npcName: " + npcName, TRUE);
	}
#endif

	
	return FALSE;
}

static zBOOL Wld_InsertItem()
{
	int		index;
	zSTRING posPoint;
	zBOOL	found		= FALSE;

	zCParser *p = zCParser::GetParser();
	p -> GetParameter(posPoint);
	p -> GetParameter(index);
	oCItem* item = (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,index);
	if (item) 
	{
		// Looking for posPoint
		zVEC3 pos		(0,0,0);
		// a) Waynet
		zCWaypoint* wp	= ogame->GetWorld()->GetWayNet()->GetWaypoint(posPoint);
		if (wp) {
			pos			= wp->GetPositionWorld();
			found		= TRUE;
		} else {
			zCVob* posVob	= ogame->GetGameWorld()->SearchVobByName(posPoint);
			if (posVob) {
				pos		= posVob->GetPositionWorld();
				found	= TRUE;
			}
		} 
		if (!found) zERR_WARNING("U:WLD: Position-Vob "+posPoint+" not found.");
		
		item ->SetPositionWorld(pos);
		ogame->GetGameWorld()->AddVob(item);
		item ->Release();
	}
#ifdef CHECK_SCRIPT_PARANOID
	else
	{
		zCPar_Symbol*sym = parser.GetSymbol(index);
		zSTRING itemName = sym ? sym->name : "[UNKNOWN]";
		DebugOut("Wld_InsertItem(): item could not be inserted (illegal item ? not enough place ?): itemname: " + itemName + " ,position: " + posPoint, TRUE);
	};
#endif
	return FALSE;
}

//
//	CODECHANGE [ROMAN]
//

/* ----------------------------------------------------------------------
	
	Wld_InsertObject()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL Wld_InsertObject()
{
	zSTRING strVisual;
	zSTRING strWaypoint;

	zCParser*	p		= zCParser :: GetParser();									// get the current global parser

	p -> GetParameter( strWaypoint	);											// Waypoint
	p -> GetParameter( strVisual		);											// MDS

	//
	//	CALCULATE WORLD/FLOOR POSITION
	//

	// SpawnPosition ermitteln
	// a) Waypoint
	// b) Freepoint (nur falls nicht mehr als Objekte im Spiel)
	// c) anderes Vob
	zVEC3		ptFloor (0,0,0);
	zCVob*		vob = NULL;
	zCWaypoint* wp	= ogame	-> GetWorld()->GetWayNet()->GetWaypoint( strWaypoint );

	if (wp) {
		ptFloor	= wp  -> GetPositionWorld();
	} else if ( (vob  =  ogame -> GetWorld()->SearchVobByName( strWaypoint )) != NULL ) {
		ptFloor = vob -> GetPositionWorld();
	} else {
		DebugOut("Wld_InsertObject(): Spawnpoint "+ strWaypoint +" not found. Object "+ strVisual +" cannot be spawned.", TRUE);
		return FALSE;
	}

	//
	//	CREATE MOB
	//
	oCMOB* mob = zNEW(oCMOB)();
	mob->zCVob::SetVisual	( strVisual );
	
	mob->SetTakeable		( FALSE	);
	mob->SetCollDet			( FALSE	);

	oCNpc::player->GetHomeWorld()->AddVob( mob );
	mob->SetOnFloor			( ptFloor	);

	mob->SetCollDet			( TRUE	);
	mob->SetPhysicsEnabled	( TRUE	);
	mob->SetSleeping		( TRUE	);

	mob->Release();	// [Ulf] : Leakfix.

	return FALSE;
}
//
//	CODECHANGE [ROMAN] END
//

//
//	CODECHANGE [ROMAN]
//
static zBOOL Wld_RemoveItem()
{
	zCParser*	p		= zCParser :: GetParser();									// get the current global parser
	oCItem*		pItem		= dynamic_cast<oCItem*>((zCVob*)p->GetInstance ());	// get item instance from script
	zBOOL		wasRemoved	= FALSE;													// assume failure
	if ( pItem )																		// is the instance valid?
		if ( ::ogame->GetGameWorld()->GetVobListItems()->InList( pItem ) )				// is the chosen vob contained in the world?
		{																				
			::ogame->GetGameWorld()->RemoveVob( pItem );								// remove the vob
			wasRemoved = TRUE;															// return success
		}																				
																						
	p -> SetReturn( wasRemoved );													// tell the script whether removal succeeded 

	return FALSE;
}
//
//	CODECHANGE [ROMAN] END
//

static zBOOL Wld_ExchangeGuildAttitudes()
{
	zSTRING tableName;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(tableName);
	ogame->GetGuilds()->InitGuildTable(tableName);
	ogame->InitNpcAttitudes();
	return FALSE;
}

static zBOOL Wld_DetectItem()
{
	int w;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(w);
	oCNpc* self = PopAndCheckValidNPC("Wld_DetectItem", TRUE);

	if (self) 
	{
		oCItem* item = self	-> DetectItem (w);
		parser.SetInstance("ITEM",item);
		p->SetReturn(item!=NULL);
	};
	return FALSE;
}

static zBOOL Wld_DetectPlayer()
{
	oCNpc* npc	= NULL;
	zCParser *p = zCParser::GetParser();
	oCNpc* self = PopAndCheckValidNPC("Wld_DetectPlayer", TRUE);

	if (self) 
	{
		npc = self	-> DetectPlayer();
		parser.SetInstance("OTHER",npc);
	};
	p->SetReturn(npc!=NULL);
	return FALSE;
}

static zBOOL Wld_DetectNpc()
{
	int instance, guild, aiState;
	oCNpc* npc	= NULL;
	zCParser *p = zCParser::GetParser();
	p->GetParameter(guild);
	p->GetParameter(aiState);
	p->GetParameter(instance);
	oCNpc* self = PopAndCheckValidNPC("Wld_DetectNpc", FALSE);
	
#ifdef CHECK_SCRIPT_PARANOID
	if (!self)
	{
		zCPar_Symbol *sym = parser.GetSymbol(aiState);
		zSTRING stateString= sym ? sym->name : "[UNKNOWN]";
		sym = parser.GetSymbol(instance);
		zSTRING instanceString= sym ? sym->name : "[UNKNOWN]";

		DebugOut("... aiState: " + stateString + ", npc-name: " + instanceString, TRUE);
	}
#endif
	
	if (self)
	{
		// Initialisiere other mit gefundenen NSC
		npc = self -> FindNpc(instance,guild,aiState,TRUE);
		if (npc) p->SetInstance("OTHER",npc);
	};
	p->SetReturn(npc!=NULL);
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Wld_DetectNpcEx()

	29.08.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */

static zBOOL Wld_DetectNpcEx()
{
	int instance, guild, aiState, detectPlayer;
	oCNpc* npc	= NULL;
	zCParser *p = zCParser::GetParser();
	
	p->GetParameter(detectPlayer);
	p->GetParameter(guild);
	p->GetParameter(aiState);
	p->GetParameter(instance);
	oCNpc* self = PopAndCheckValidNPC("Wld_DetectNpcEx", FALSE);

#ifdef CHECK_SCRIPT_PARANOID
	if (!self)
	{
		zCPar_Symbol* sym = parser.GetSymbol(aiState);
		zSTRING stateString= sym ? sym->name : "[UNKNOWN]";
		sym = parser.GetSymbol(instance);
		zSTRING instanceString= sym ? sym->name : "[UNKNOWN]";

		DebugOut("... aiState: " + stateString + ", npc-name: " + instanceString, TRUE);
	}
#endif
	
	if (self) {
		// Initialisiere other mit gefundenen NSC
		npc = self -> FindNpcEx(instance,guild,aiState,TRUE, (detectPlayer == 0), TRUE /*ignoreDead*/ );
		if (npc) p->SetInstance("OTHER",npc);
	};
	p->SetReturn(npc!=NULL);
	return FALSE;
}

static zBOOL Wld_DetectNpcExAtt()
{
	int instance, guild, aiState, detectPlayer, att;
	oCNpc* npc	= NULL;
	zCParser *p = zCParser::GetParser();
	
	p->GetParameter(att);
	p->GetParameter(detectPlayer);
	p->GetParameter(guild);
	p->GetParameter(aiState);
	p->GetParameter(instance);

	oCNpc* self = PopAndCheckValidNPC("Wld_DetectNpcExAtt", FALSE);
	
#ifdef CHECK_SCRIPT_PARANOID
	if (!self)
	{
		zCPar_Symbol *sym = parser.GetSymbol(aiState);
		zSTRING stateString= sym ? sym->name : "[UNKNOWN]";
		sym = parser.GetSymbol(instance);
		zSTRING instanceString= sym ? sym->name : "[UNKNOWN]";

		DebugOut("... aiState: " + stateString + ", npc-name: " + instanceString, TRUE);
	}
#endif

	if (self) {
		// Initialisiere other mit gefundenen NSC
		npc = self -> FindNpcExAtt(instance,guild,aiState,TRUE, (detectPlayer == 0), TRUE, att );
		if (npc) p->SetInstance("OTHER",npc);
	};
	p->SetReturn(npc!=NULL);
	return FALSE;
}


static zBOOL Wld_SetGuildAttitude()
{
	int guild1, attitude, guild2;
	zCParser *p = zCParser::GetParser();
	
	p->GetParameter(guild2);
	p->GetParameter(attitude);
	p->GetParameter(guild1);
	
	ogame->GetGuilds()->SetAttitude(guild1,guild2,attitude);
	return FALSE;
}

static zBOOL Wld_GetGuildAttitude()
{
	int guild1, guild2;
	zCParser *p = zCParser::GetParser();
	
	p->GetParameter(guild2);
	p->GetParameter(guild1);
	
	p->SetReturn( ogame->GetGuilds()->GetAttitude(guild1,guild2));
	return FALSE;
}

// ****************************************************************************************
// Skript Zustand-�berwachung
// ****************************************************************************************

/* ----------------------------------------------------------------------
	
	AI_ContinueRoutine()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_ContinueRoutine()
{
	zCParser *p = zCParser::GetParser();
	oCNpc* self = PopAndCheckValidNPC("AI_ContinueRoutine", TRUE);

	if (self) {
		self -> GetEM() -> OnMessage(zNEW(oCMsgMovement)	(oCMsgMovement	  ::EV_STANDUP,NULL)			, self);
		self -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_STOPLOOKAT)		, self);
		self -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_STOPPOINTAT)		, self);
		self -> GetEM() -> OnMessage(zNEW(oCMsgWeapon)		(oCMsgWeapon	  ::EV_REMOVEWEAPON)	, self);
		self -> GetEM() -> OnMessage(zNEW(oCMsgState)		(oCMsgState		  ::EV_STARTSTATE,0)	, self);
	}
	return FALSE;
}

static zBOOL AI_StartState()
{
	zSTRING wp;
	int param,stateID;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(wp);
	p -> GetParameter(param);
	p -> GetParameter(stateID);
	oCNpc* self = PopAndCheckValidNPC("AI_StartState", FALSE);

#ifdef CHECK_SCRIPT_PARANOID
	if (!self)
	{
		zCPar_Symbol* sym = parser.GetSymbol(stateID);
		zSTRING stateString= sym ? sym->name : "[UNKNOWN]";
		DebugOut("... aiState: " + stateString + ", wp-name: " + wp, TRUE);
	}; 
#endif

	if (self) {
		oCMsgState* msg = zNEW(oCMsgState)(oCMsgState::EV_STARTSTATE,stateID,param,wp);
		
/*		zSTRING stateName;
		zCPar_Symbol* sym1 = parser.GetSymbol(stateID);
		if (sym1) stateName = sym1->name;		
*/		
		// Save Globals needed for further execution
		zCPar_Symbol* sym	= parser.GetSymbol("OTHER");
		if (sym) msg->other	= dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
		sym					= parser.GetSymbol("VICTIM");
		if (sym) msg->victim= dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
		// [Wohlers] - (AtHome) inRoutine beachten
		msg  -> inRoutine	= self->state.IsInRoutine();
		self -> GetEM() -> OnMessage(msg,self);
	};
	return TRUE;
}

static zBOOL Npc_GetStateTime()
{
	int seconds = 0;
	zCParser *p = zCParser::GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_GetStateTime", TRUE);
	if (self) {
		seconds = self -> GetAIStateTime();
	};
	p->SetReturn(seconds);
	return FALSE;
}

static zBOOL Npc_SetStateTime()
{
	int seconds = 0;
	zCParser *p = zCParser::GetParser();
	p -> GetParameter(seconds);
	oCNpc* self = PopAndCheckValidNPC("Npc_SetStateTime", TRUE);
	if (self) {
		self->state.SetStateTime(seconds);
	};
	return FALSE;
}

// ****************************************************************************************
// Sonstiges 
// ****************************************************************************************

// CODECHANGE [STEFAN]

static zBOOL IntToString()
{
	int val;
	static zSTRING s;
	
	char buf[100];
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(val);
	itoa(val, buf, 10);
	s = buf;
	p->SetReturn(s);
	return FALSE;
}

static zBOOL FloatToString()
{
	float val;
	static zSTRING s;

	char buf[100];
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(val);
	sprintf(buf, "%f", val);
	s = buf;
	p->SetReturn(s);
	return FALSE;
}

static zBOOL IntToFloat()
{
	int val;
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(val);
	p->SetReturn((float)val);
	return FALSE;
}

static zBOOL FloatToInt()
{
	float val;
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(val);
	p->SetReturn((int)val);
	return FALSE;
}

static zBOOL ConcatStrings()
{
	static zSTRING s1;
	zSTRING s2;
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(s2);
	p->GetParameter(s1);
	s1 += s2;
	p->SetReturn(s1);
	return FALSE;
}

// CODECHANGE [STEFAN] END

static zBOOL Print()
{
	zSTRING s;
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(s);
	ogame->GetTextView()->Printwin(s+"\n");
	return FALSE;
}

static zBOOL PrintDebug()
{
	// FIXME : Bugfix fuers einf�gen von NSCs im Spacer,
	// sonst hier Absturz... Aber warum ? Und wieso hier ?
#ifndef COMPILING_SPACER
	zSTRING s;
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(s);
	if (ogame->GetShowDebug()) zerr.Message("U:Skript: "+s);
#endif
	return FALSE;
}

// CODECHANGE [STEFAN]

//
//	CODECHANGE [ROMAN]
//
static zBOOL PrintScreen()																					//	USAGE: PrintScreen ("Blablabla", -1, 90, "FONTNAME", SEKUNDEN )
{																											
	//																										
	//	DECLARE LOCAL VARIABLES																				
	//																										
																											
	zSTRING strMessage,																						//	the actual message to be displayed
			strFont		;																					//	name of the font to be used
	int		nPosX,																							//	x-position in percent of screen's size	(negative values indicate alignment: -1 == centered )
			nPosY		;																					//	y-position in percent of screen's size	(negative values indicate alignment: -1 == centered )
	int		nTimeSeconds;																					//	# of seconds to display the message		(in real-time) 		
	int		nDialog		;
	zBOOL	bSuccess	= TRUE;																				//	assume success
																											
	//																										
	//	RETRIVE PARAMETERS																					
	//																										
																											
	zCParser* p = zCParser :: GetParser();															//	retrieve current global parser
	p -> GetParameter( nTimeSeconds	);																//	get duration
	p -> GetParameter( strFont		);																//	get the font's name
	p -> GetParameter( nPosY		);																//	get vertical   placement
	p -> GetParameter( nPosX		);																//	get horizontal placement
	p -> GetParameter( strMessage	);																//	get the actual message
	p -> GetParameter( nDialog		);																//	get duration
			
	//
	//	CHECK IF DESIRED VIEW IS AVAILABLE
	//

	if (strMessage.IsEmpty())
	{

#if defined(SECUROM) && !defined(COMPILING_SPACER)
			oCNpc* player = dynamic_cast<oCNpc*>(::ogame->GetSelfPlayerVob());
			if (player)
			{
				oCMsgRequest* msg = zNEW(oCMsgRequest)();
				player->GetEM()->OnMessage(msg, player);
			}
#endif

		bSuccess = TRUE;
		p->SetReturn(bSuccess);
	}

	if ( ! ::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN ) )
	{
		bSuccess = FALSE;
		p -> SetReturn( bSuccess );
		return FALSE;
	}

	//
	//	OPEN THE DIALOG IF IT'S BEEN CLOSED
	//

//	::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->Open();

	//																										
	//	TRY TO RETRIEVE THE DESIRED FONT																	
	//																										
																											
	if ( ! strFont.IsEmpty() )																				
	{																										
			 ::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->SetFont( strFont );
		if ( ::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->GetFont()->GetFontName() != strFont )	//	check for success
			 bSuccess &= FALSE;
		else bSuccess &= TRUE ;
	}

	//															
	//	CALCULATE EFFECTIVE PLACEMENT							
	//															
																
	int		nWidth	,																						//	view's with as specified in virtual coords 
			nHeight		;																					//	view's height as specified in virtual coords 
	float	fWidth	,																						//	percentage-applied view's width 
			fHeight		;																					//	percentage-applied view's height 
	
	nWidth	= VIEW_VXMAX		;
	nHeight = VIEW_VYMAX		;

	fWidth	= (float) nWidth	;									
	fHeight	= (float) nHeight	;
							
	fWidth	*= 0.01f			;										
	fHeight *= 0.01f			;										
							
	fWidth	*= (float) nPosX	;										
	fHeight *= (float) nPosY	;										
							
	nWidth	= (int) fWidth		;
	nHeight	= (int) fHeight		;

	//
	//	ACTUALLY OUTPUT THE MESSAGE
	//

	if		( ( nPosX == - 1 ) && ( nPosY == - 1 ) )	::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->PrintTimedCXY(				    strMessage, nTimeSeconds * 1000, NULL );
	else if   ( nPosY == - 1 )							::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->PrintTimedCY ( nWidth,		    strMessage, nTimeSeconds * 1000, NULL );
	else if   ( nPosX == - 1 )							::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->PrintTimedCX (	       nHeight, strMessage, nTimeSeconds * 1000, NULL );
	else												::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN )->PrintTimed	 ( nWidth, nHeight, strMessage, nTimeSeconds * 1000, NULL );

	//
	//	GIVE SOME FEEDBACK
	//

	p -> SetReturn( bSuccess );

	return FALSE;
}

static zBOOL AI_PrintScreen()																					//	USAGE: PrintScreen ("Blablabla", -1, 90, "FONTNAME", SEKUNDEN )
{																											
	//																										
	//	DECLARE LOCAL VARIABLES																				
	//																										
																											
	zSTRING strMessage,																						//	the actual message to be displayed
			strFont		;																					//	name of the font to be used
	int		nPosX,																							//	x-position in percent of screen's size	(negative values indicate alignment: -1 == centered )
			nPosY		;																					//	y-position in percent of screen's size	(negative values indicate alignment: -1 == centered )
	int		nTimeSeconds;																					//	# of seconds to display the message		(in real-time) 		
	int		nDialog		;
	zBOOL	bSuccess	= TRUE;																				//	assume success
																											
	//																										
	//	RETRIVE PARAMETERS																					
	//																										
																											
	zCParser* p = zCParser :: GetParser();															//	retrieve current global parser
	p -> GetParameter( nTimeSeconds	);																//	get duration
	p	-> GetParameter( strFont		);																//	get the font's name
	p -> GetParameter( nPosY			);																//	get vertical   placement
	p -> GetParameter( nPosX			);																//	get horizontal placement
	p -> GetParameter( strMessage		);																//	get the actual message
	p -> GetParameter( nDialog		);																//	get duration
			
	//
	//	CHECK IF DESIRED VIEW IS AVAILABLE
	//

	if ( ! ::ogame->GetView( oCGame::oEGameDialogView::GAME_VIEW_SCREEN ) )
	{
		bSuccess = FALSE;
		p -> SetReturn( bSuccess );
		return FALSE;
	}


	if ( oCNpc::player )																								
	{																											
		oCMsgConversation* pMsg = zNEW( oCMsgConversation ) ( oCMsgConversation::EV_PRINTSCREEN, oCNpc::player );	
		pMsg->f_no				= nPosX;
		pMsg->f_yes				= nPosY;
		pMsg->timer				= (zREAL)nTimeSeconds;
		pMsg->number			= nDialog;
		pMsg->name				= strFont;
		pMsg->text				= strMessage;

		oCNpc::player->GetEM()->OnMessage( pMsg, oCNpc::player );
	}

	//
	//	GIVE SOME FEEDBACK
	//

	p -> SetReturn( bSuccess );

	return FALSE;
}



static zBOOL Wld_StopEffect()
{
	zSTRING visFXName;
	zCParser :: GetParser() -> GetParameter( visFXName );														

	//	get the actual fx
	zCArray<zCVob*>vobList;
	if (oCNpc::player)
	{
		oCNpc::player->GetHomeWorld()->SearchVobListByClass(oCVisualFX::GetStaticClassDef(),vobList);
		for (int i=0; i<vobList.GetNum(); i++)
		{
			oCVisualFX *visFX = zDYNAMIC_CAST<oCVisualFX>(vobList[i]);
			if (visFX->GetName() == visFXName)
			{
				visFX->Stop();
				return FALSE;
			}
		}
	}
	return FALSE;
}




static zBOOL PrintDialog()																					//	USAGE: PrintDialog ( DIALOG_TYP, "Blablabla", -1, 90, "FONTNAME", SEKUNDEN )
{																											
	//																										
	//	DECLARE LOCAL VARIABLES																				
	//																										
																											
	zSTRING strMessage,																						//	the actual message to be displayed
			strFont		;																					//	name of the font to be used
	int		nPosX,																							//	x-position in percent of screen's size	(negative values indicate alignment: -1 == centered )
			nPosY		;																					//	y-position in percent of screen's size	(negative values indicate alignment: -1 == centered )
	int		nTimeSeconds;																					//	# of seconds to display the message		(in real-time) 		
	int		nDialog		;
	zBOOL	bSuccess	= TRUE;																				//	assume success
																											
	//																										
	//	RETRIVE PARAMETERS																					
	//																										
																											
	zCParser* p = zCParser :: GetParser();															//	retrieve current global parser
	p -> GetParameter( nTimeSeconds	);																//	get duration
	p	-> GetParameter( strFont		);																//	get the font's name
	p -> GetParameter( nPosY			);																//	get vertical   placement
	p -> GetParameter( nPosX			);																//	get horizontal placement
	p -> GetParameter( strMessage		);																//	get the actual message
	p -> GetParameter( nDialog		);																//	get duration
			
	//
	//	CHECK IF DESIRED VIEW IS AVAILABLE
	//

	if ( ! ::ogame->GetView( (oCGame::oTGameDialogView) nDialog ) )
	{
		bSuccess = FALSE;
		p -> SetReturn( bSuccess );
		return FALSE;
	}

	//
	//	OPEN THE DIALOG IF IT'S BEEN CLOSED
	//

	::ogame->OpenView( (oCGame::oTGameDialogView) nDialog );

	//																										
	//	TRY TO RETRIEVE THE DESIRED FONT																	
	//																										
																											
	if ( ! strFont.IsEmpty() )																				
	{																										
			 ::ogame->GetView( (oCGame::oTGameDialogView) nDialog )->SetFont( strFont );
		if ( ::ogame->GetView( (oCGame::oTGameDialogView) nDialog )->GetFont()->GetFontName() != strFont )	//	check for success
			 bSuccess &= FALSE;
		else bSuccess &= TRUE ;
	}

	//															
	//	CALCULATE EFFECTIVE PLACEMENT							
	//															
																
	int		nWidth	,																						//	view's with as specified in virtual coords 
			nHeight		;																					//	view's height as specified in virtual coords 
	float	fWidth	,																						//	percentage-applied view's width 
			fHeight		;																					//	percentage-applied view's height 
	
	nWidth	= VIEW_VXMAX		;
	nHeight = VIEW_VYMAX		;

	fWidth	= (float) nWidth	;									
	fHeight	= (float) nHeight	;
							
	fWidth	*= 0.01f			;										
	fHeight *= 0.01f			;										
							
	fWidth	*= (float) nPosX	;										
	fHeight *= (float) nPosY	;										
							
	nWidth	= (int) fWidth		;
	nHeight	= (int) fHeight		;

	//
	//	ACTUALLY OUTPUT THE MESSAGE
	//

	zCOLOR col = zCOLOR( 0xff, 0xff, 0xff, 0xff );

	if		( ( nPosX == - 1 ) && ( nPosX == - 1 ) )	::ogame->GetView( (oCGame::oTGameDialogView) nDialog )->DialogCXY(				    strMessage, nTimeSeconds * 1000, &col );
	else if   ( nPosY == - 1 )							::ogame->GetView( (oCGame::oTGameDialogView) nDialog )->DialogCY ( nWidth,		    strMessage, nTimeSeconds * 1000, &col );
	else if   ( nPosX == - 1 )							::ogame->GetView( (oCGame::oTGameDialogView) nDialog )->DialogCX (	       nHeight, strMessage, nTimeSeconds * 1000, &col );
	else												::ogame->GetView( (oCGame::oTGameDialogView) nDialog )->Dialog	 ( nWidth, nHeight, strMessage, nTimeSeconds * 1000, &col );

	//
	//	GIVE SOME FEEDBACK
	//

	p -> SetReturn( bSuccess );

	return FALSE;
}
//
//	CODECHANGE [ROMAN] END
//

static zBOOL PrintDebugInst()
{
	zCVob *self;
	zCParser *p			= zCParser :: GetParser();
	zCPar_Symbol* sym	= p->GetSymbol("SELF");
	if (sym) self = (zCVob*)sym->GetInstanceAdr();
	zSTRING s;
	p->GetParameter(s);

	if (ogame->IsDebuggingAllInstances() || ogame->IsDebuggingInstance(self))
		if (ogame->GetShowDebug()) zerr.Message("U:Skript: "+s);
	return FALSE;
}

static zBOOL PrintDebugInstCh()
{
	zCVob *self;
	zCParser *p			= zCParser :: GetParser();
	zCPar_Symbol* sym	= p->GetSymbol("SELF");
	if (sym) self = (zCVob*)sym->GetInstanceAdr();
	zSTRING s;
	int ch;
	p->GetParameter(s);
	p->GetParameter(ch);

	if (ogame->IsDebuggingAllInstances() || ogame->IsDebuggingInstance(self))
		if (ogame->IsDebuggingChannel(ch))
			if (ogame->GetShowDebug()) zerr.Message("U:Skript: "+s);
	return FALSE;
}

static zBOOL PrintDebugCh()
{
	zCParser *p = zCParser :: GetParser();

	zSTRING s;
	int ch;
	p->GetParameter(s);
	p->GetParameter(ch);
	if (ogame->IsDebuggingChannel(ch))
		if (ogame->GetShowDebug()) zerr.Message("U:Skript: "+s);
	return FALSE;
}

// CODECHANGE [STEFAN] END

static zBOOL PrintMulti()
{
	int anz = 0;
	zSTRING s[5];
	zCParser *p = zCParser :: GetParser();
	for (int i=4; i>=0; i--) p->GetParameter(s[i]);

	for (i=0; i<5; i++) {
		if (s[i].Length()>0) anz++;
		else break;
	}
	i = zRand() % anz;
	ogame->GetTextView()->Printwin(s[i]);
	return FALSE;
}

// CODECHANGE [STEFAN]

// ****************************************************************************************
// MissionLog
// ****************************************************************************************

static zBOOL Log_CreateTopic()
{
	zCParser*		p =	zCParser	::GetParser		();	
	oCLogManager&	mgrLogs	=	oCLogManager::GetLogManager	();

	int						nSection;	p->GetParameter( nSection );	zELogSection enuSection = (zELogSection) nSection;
	zSTRING					strTopic;	p->GetParameter( strTopic );

	mgrLogs.AddTopic( strTopic, enuSection );

	return FALSE;
}

static zBOOL Log_AddEntry()
{
	zCParser*		p =	zCParser	::GetParser		();	
	oCLogManager&	mgrLogs	=	oCLogManager::GetLogManager	();

	zSTRING					strEntry;	p->GetParameter( strEntry );	
	zSTRING					strTopic;	p->GetParameter( strTopic );

	mgrLogs.AddEntry( strTopic, strEntry );

	return FALSE;
}

static zBOOL Log_SetTopicStatus()
{
	zCParser*		p =	zCParser	::GetParser		();	
	oCLogManager&	mgrLogs	=	oCLogManager::GetLogManager	();

	int						nStatus;	p->GetParameter( nStatus  );	zELogTopicStatus enuStatus = (zELogTopicStatus) nStatus;
	zSTRING					strTopic;	p->GetParameter( strTopic );

	mgrLogs.SetStatus( strTopic, enuStatus );

	return FALSE;
}

static zBOOL Mis_AddMissionEntry()
{
	zCParser *p = zCParser :: GetParser();	

	zSTRING		text;		p->GetParameter		(text);	
	int			instance;	p->GetParameter		(instance);	
	oCMission*	mission		= misMan.GetMission	(instance);
	if (mission)	mission->AddEntry(text);
	else			
	{
#ifdef CHECK_SCRIPT_PARANOID
		zCPar_Symbol *sym = p->GetSymbol(instance);
		zSTRING misText = sym ? sym->name : "[UNKNOWN]";
		DebugOut("S: Mission " + misText + " not found !", TRUE); 
#endif
		return FALSE; 
	}
	
	mission->AddEntry(text);

	return FALSE;
}

static zBOOL Mis_RemoveMission()
{
	zCParser *p = zCParser :: GetParser();
	
	int			instance;	p->GetParameter		(instance);
	oCMission*	mission		= misMan.GetMission	(instance);	
	if (mission)	mission->SetDeleted();
	else			
	{
#ifdef CHECK_SCRIPT_PARANOID
		zCPar_Symbol *sym = p->GetSymbol(instance);
		zSTRING misText = sym ? sym->name : "[UNKNOWN]";
		DebugOut("S: Mission " + misText + " not found !", TRUE); 
#endif		
	};
	
	return FALSE;
}

// CODECHANGE [STEFAN] END

// ****************************************************************************************
// PortalRa�me
// ****************************************************************************************

static zBOOL Wld_GetPlayerPortalOwner()
{
	oCNpc*		owner			= NULL;
	zCParser*	p				= zCParser :: GetParser();
	oCPortalRoomManager* rooms	= ogame->GetPortalRoomManager();
	if (rooms)  owner			= rooms->GetCurPlayerPortalRoomOwner();
	// Check, if physically available ?
	if (owner && !ogame->GetGameWorld()->GetVobListNpcs()->IsInList(owner)) owner = NULL;
	p->SetReturn(owner);
	return FALSE;
}

static zBOOL Wld_GetFormerPlayerPortalOwner()
{
	oCNpc*		owner			= NULL;
	zCParser*	p				= zCParser :: GetParser();
	oCPortalRoomManager* rooms	= ogame->GetPortalRoomManager();
	if (rooms)  owner			= rooms->GetFormerPlayerPortalRoomOwner();
	// Check, if physically available ?
	if (owner && !ogame->GetGameWorld()->GetVobListNpcs()->IsInList(owner)) owner = NULL;
	p->SetReturn(owner);
	return FALSE;
}

static zBOOL Wld_GetPlayerPortalGuild()
{
	int			guildNr			= -1;
	zCParser*	p				= zCParser :: GetParser();
	oCPortalRoomManager* rooms	= ogame->GetPortalRoomManager();
	if (rooms)  guildNr			= rooms->GetCurPlayerPortalRoomGuild();
	p->SetReturn(guildNr);
	return FALSE;
}

static zBOOL Wld_GetFormerPlayerPortalGuild()
{
	int			guildNr			= -1;
	zCParser*	p				= zCParser :: GetParser();
	oCPortalRoomManager* rooms	= ogame->GetPortalRoomManager();
	if (rooms)  guildNr			= rooms->GetFormerPlayerPortalRoomGuild();
	p->SetReturn(guildNr);
	return FALSE;
}

static zBOOL Wld_AssignRoomToNpc()
{
	zSTRING		name;
	zCParser*	p			= zCParser :: GetParser();
	oCNpc*		self		= PopAndCheckValidNPC("Wld_AssignRoomToNpc", FALSE);
	p -> GetParameter		(name);

#ifdef CHECK_SCRIPT_PARANOID
	if (!self)
	{
		DebugOut("... roomName: " + name, TRUE);
	};
#endif
	if (self) {
		oCPortalRoomManager* rooms = ogame->GetPortalRoomManager();
		if (rooms) rooms->AssignPortalToNpc(name,self->GetInstanceName());
	}
	return FALSE;
}

static zBOOL Wld_AssignRoomToGuild()
{
	int			guildNr;
	zSTRING		name;
	zCParser*	p			= zCParser :: GetParser();
	p -> GetParameter		(guildNr);
	p -> GetParameter		(name);

	oCPortalRoomManager* rooms = ogame->GetPortalRoomManager();
	if (rooms) rooms->AssignPortalToGuild(name,guildNr);
	
	return FALSE;
}

static zBOOL Npc_IsPlayerInMyRoom()
{
	zBOOL		playerIsIn	= FALSE;
	zCParser*	p			= zCParser :: GetParser();
	oCNpc*		self		= PopAndCheckValidNPC("Npc_IsPlayerInMyRoom", TRUE);
	if (self) {
		oCPortalRoomManager* rooms = ogame->GetPortalRoomManager();
		if (rooms) playerIsIn = rooms->IsPlayerInMyRoom(self);
	}
	p->SetReturn(playerIsIn);
	return FALSE;
}

static zBOOL Npc_IsInPlayersRoom()
{
	zBOOL  playerIsIn = FALSE;
	zCParser* p   = zCParser :: GetParser();
	oCNpc*  self  = PopAndCheckValidNPC("Npc_IsInPlayersRoom", TRUE);
	if (self) {
		oCPortalRoomManager* rooms = ogame->GetPortalRoomManager();
		if (rooms) playerIsIn = rooms->IsNSCInPlayerRoom(self);
	}
	p->SetReturn(playerIsIn);
	return FALSE;
}

static zBOOL Npc_WasPlayerInMyRoom()
{
	zBOOL		playerIsIn	= FALSE;
	zCParser*	p			= zCParser :: GetParser();
	oCNpc*		self		= PopAndCheckValidNPC("Npc_WasPlayerInMyRoom", TRUE);
	if (self) {
		oCPortalRoomManager* rooms = ogame->GetPortalRoomManager();
		if (rooms) playerIsIn = rooms->WasPlayerInMyRoom(self);
	}
	p->SetReturn(playerIsIn);
	return FALSE;
}

static zBOOL Npc_GetPortalOwner()
{
	oCNpc*  owner = NULL;
	zCParser* p  = zCParser::GetParser();
	oCNpc*  npc  = PopAndCheckValidNPC("Npc_GetPortalOwner", TRUE);
	if (npc)
	{
		oCPortalRoomManager* rooms = ogame->GetPortalRoomManager();
		if (rooms)
		owner = rooms->GetCurNpcPortalRoomOwner(npc);
		// Check, if physically available ?
		if (owner && !ogame->GetGameWorld()->GetVobListNpcs()->IsInList(owner))
			owner = NULL;
	}
	p->SetReturn(owner);
	return FALSE;
}
 
static zBOOL Npc_GetPortalGuild()
{
	int guild	= -1;
	zCParser* p	= zCParser::GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_GetPortalGuild", TRUE);
	if (npc)
	{
		oCPortalRoomManager* rooms = ogame->GetPortalRoomManager();
		if (rooms)
			guild = rooms->GetCurNpcPortalRoomGuild(npc);
	}
	p->SetReturn(guild);
	return FALSE;
}

// ****************************************************************************************
// NPCS 
// ****************************************************************************************

static zBOOL Npc_IsInState()
{
	int statenr;
	zCParser *p	 = zCParser :: GetParser();
	p -> GetParameter (statenr);
	oCNpc* self = PopAndCheckValidNPC("Npc_IsInState", TRUE);
	if (self) 
		p->SetReturn (self->IsAIState(statenr));		
	else
		p->SetReturn (FALSE);

	return FALSE;
};

static zBOOL Npc_WasInState()
{
	int statenr;
	zCParser *p	 = zCParser :: GetParser();
	p -> GetParameter (statenr);
	oCNpc* self = PopAndCheckValidNPC("Npc_WasInState", TRUE);
	if (self) 
		p->SetReturn (self->state.GetLastState()==statenr);		
	else
		p->SetReturn (FALSE);

	return FALSE;
};

static zBOOL Npc_IsInRoutine()
{
	int statenr;
	zCParser *p	 = zCParser :: GetParser();
	p -> GetParameter (statenr);
	oCNpc* self = PopAndCheckValidNPC("Npc_IsInRoutine", TRUE);
	if (self) 
		p->SetReturn (self->state.GetLastRoutineState()==statenr);
	else
		p->SetReturn (FALSE);

	return FALSE;
};

/* ----------------------------------------------------------------------
	
	Npc_PlayAni()

	14.09.00 [Edenfeld]	

			  BuildIn zum Abspielen von Anis ausserhalb der AI Pipeline
   ---------------------------------------------------------------------- */


static zBOOL Npc_PlayAni()
{
	zSTRING s;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter(s);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_PlayAni", TRUE);
	if (npc) {
		npc->GetModel()->StartAni(s);
	}
	return TRUE;
};

/* ----------------------------------------------------------------------
	
	AI_SetNpcsToState()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_SetNpcsToState()
// setze alle NSCs im Radius xx aus ZS_Yy
{
	zCParser *p	 = zCParser :: GetParser();
	int func,radius;
	p->GetParameter(radius);	
	p->GetParameter(func);
	oCNpc* self = PopAndCheckValidNPC("AI_SetNpcsToState", TRUE);
	if (self) {
		oCMsgState* msg = zNEW(oCMsgState)(oCMsgState::EV_SETNPCSTOSTATE,func);
		msg ->minutes	= radius;
		self->GetEM()->OnMessage(msg,self);
	};
	return FALSE;
}

static zBOOL Npc_GetActiveSpell ()
{
	zCParser *p	 = zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_GetActiveSpell", TRUE);
	if (self) p->SetReturn (self->GetActiveSpellNr());
	return FALSE;
};

static zBOOL Npc_GetLastHitSpellID()
{
	zCParser *p	 = zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_GetLastHitSpellID", TRUE);
	if (self) p->SetReturn (self->GetLastHitSpellID());
	return FALSE;
};

static zBOOL Npc_GetLastHitSpellCat()
{
	zCParser *p	 = zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_GetLastHitSpellCat", TRUE);
	if (self) p->SetReturn (self->GetLastHitSpellCat());
	return FALSE;
};


static zBOOL Npc_SetActiveSpellInfo ()
{
	int value;
	zCParser *p	 = zCParser :: GetParser();
	p->GetParameter(value);
	oCNpc* self = PopAndCheckValidNPC("Npc_SetActiveSpellInfo", TRUE);
	if (self) {
		self->SetActiveSpellInfo(value);
	}
	return FALSE;
};

static zBOOL Npc_GetActiveSpellCat ()
{
	zCParser *p	 = zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_GetActiveSpellCat", TRUE);
	if (self) p->SetReturn (self->GetActiveSpellCategory());
	return FALSE;
};

static zBOOL Npc_GetActiveSpellLevel ()
{
	zCParser *p	 = zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_GetActiveSpellLevel", TRUE);
	if (self) p->SetReturn (self->GetActiveSpellLevel());
	return FALSE;
};

static zBOOL Npc_GetActiveSpellIsScroll ()
{
	zCParser *p	 = zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_GetActiveSpellIsScroll", TRUE);
	if (self) p->SetReturn (self->GetActiveSpellIsScroll());
	return FALSE;
}



static zBOOL Npc_GetGuildAttitude()
{
	zCParser *p	 = zCParser :: GetParser();
	oCNpc* other = PopAndCheckValidNPC("Npc_GetGuildAttitude", TRUE);
	oCNpc* self  = PopAndCheckValidNPC("Npc_GetGuildAttitude", TRUE);
	if (self && other) {
		p -> SetReturn( self -> GetGuildAttitude ( other->GetTrueGuild() ) );
	}
	return FALSE;
}

static zBOOL Npc_IsInFightMode()
{
	int w;
	zCParser *p	= zCParser :: GetParser();
	p -> GetParameter(w);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_IsInFightMode", TRUE);
	if (npc)
		p -> SetReturn ( npc->IsInFightMode_S(w) );
	else
		p -> SetReturn(0);

	return FALSE;
};

static zBOOL Npc_IsAiming()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* other= PopAndCheckValidNPC("Npc_IsAiming", TRUE);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_IsAiming", TRUE);
	if (npc && other) 
		p -> SetReturn( npc -> IsAiming_S(other) );
	else
		p -> SetReturn(0);

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	Npc_HasRangedWeaponWithAmmo()

	26.10.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Npc_HasRangedWeaponWithAmmo()
{
	zCParser*	p						= zCParser :: GetParser();
	oCNpc*		pNpc						= PopAndCheckValidNPC("Npc_HasRangedWeaponWithAmmo", TRUE);
	zBOOL		bHasRangedWeaponWithAmmo	= FALSE;

	if ( pNpc )
	{
		bHasRangedWeaponWithAmmo = pNpc->HasRangedWeaponAndAmmo();
	}

	p->SetReturn( bHasRangedWeaponWithAmmo );

	return FALSE;
}

static zBOOL Npc_HasEquippedWeapon()
{
	zCParser*	p		= zCParser :: GetParser();
	oCNpc*		npc		= PopAndCheckValidNPC("Npc_HasEquippedWeapon", TRUE);
	oCItem*		item	= NULL;
	if (npc) {
		item			= npc -> GetEquippedMeleeWeapon();
		if (!item) item	= npc -> GetEquippedRangedWeapon();
	}
	p->SetReturn(item!=NULL);
	return FALSE;
}

static zBOOL Npc_HasReadiedWeapon()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_HasReadiedWeapon", TRUE);
	oCItem*item	= NULL;
	if (npc) item	= npc -> GetWeapon();
	p->SetReturn(item!=NULL);	
	return FALSE;
}

static zBOOL Npc_HasEquippedMeleeWeapon()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_HasEquippedMeleeWeapon", TRUE);
	oCItem *item	= NULL;
	if (npc) item	= npc -> GetEquippedMeleeWeapon();
	p->SetReturn(item!=NULL);	
	return FALSE;
}

static zBOOL Npc_HasReadiedMeleeWeapon()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_HasReadiedMeleeWeapon", TRUE);
	oCItem *item	= NULL;
	if (npc) item	= npc -> GetWeapon();
	p->SetReturn( (item) && (item->HasFlag(ITM_CAT_NF)) );
	return FALSE;
}

static zBOOL Npc_HasEquippedRangedWeapon()
{
	oCItem* item = NULL;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_HasEquippedRangedWeapon", TRUE);
	if (npc) item	= npc -> GetEquippedRangedWeapon();
	p->SetReturn( item!=NULL );
	return FALSE;
}

static zBOOL Npc_HasReadiedRangedWeapon()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_HasReadiedRangedWeapon", TRUE);
	oCItem *item	= NULL;
	if (npc) item	= npc -> GetWeapon();
	p->SetReturn( (item) && (item->HasFlag(ITM_CAT_FF)) );
	return FALSE;
}

// CODECHANGE [MICHAEL]
// diese Funktionen sind offenbar �berreste vergangener Zeiten
/* static zBOOL Npc_HasEquippedSpell()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());
	p->SetReturn( 0 );
	return FALSE;
}

static zBOOL Npc_HasReadiedSpell()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());
	p->SetReturn( 0 );
	return FALSE;
} */

static zBOOL Npc_HasEquippedArmor()
{
	zCParser* p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_HasEquippedArmor", TRUE);
	oCItem*item  = NULL;
	if (npc) item	= npc->GetEquippedArmor();
	p->SetReturn( item!=NULL );
	return FALSE;
}

static zBOOL Npc_GetTalentSkill()
{
	int value = 0;
	int talent= 0;
	zCParser* p		= zCParser :: GetParser();
	p -> GetParameter (talent);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_GetTalentSkill", TRUE);
	if (npc) value = npc->GetTalentSkill(talent);
	p -> SetReturn(value);
	return FALSE;
};

static zBOOL Npc_SetTalentSkill()
{
	int		value = 0;
	int		talent= 0;
	zCParser* p	= zCParser :: GetParser();
	p -> GetParameter (value);
	p -> GetParameter (talent);	
	oCNpc* npc	= PopAndCheckValidNPC("Npc_SetTalentSkill", TRUE);
	if (npc) npc->SetTalentSkill(talent, value);	
	p -> SetReturn(npc!=0);
	return FALSE;
};

static zBOOL Npc_GetTalentValue()
{
	int value = 0;
	int talent= 0;
	zCParser* p		= zCParser :: GetParser();
	p -> GetParameter (talent);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_GetTalentValue", TRUE);
	if (npc) value = npc->GetTalentValue(talent);
	p -> SetReturn(value);
	return FALSE;
};

static zBOOL Npc_SetTalentValue()
{
	int		value = 0;
	int		talent= 0;
	zCParser* p	= zCParser :: GetParser();
	p -> GetParameter (value);
	p -> GetParameter (talent);	
	oCNpc* npc	= PopAndCheckValidNPC("Npc_SetTalentValue", TRUE);
	if (npc) npc->SetTalentValue(talent, value);	
	p -> SetReturn(npc!=0);
	return FALSE;
};

static zBOOL Tal_Configure()
{
	int		valueRelevant	= 0;
	int		talent			= 0;
	zCParser* p	= zCParser :: GetParser();
	p -> GetParameter (valueRelevant);
	p -> GetParameter (talent);	
	oCNpc* npc	= PopAndCheckValidNPC("Tal_Configure", TRUE);
	// TODO: Relevanz des Values setzen
	p -> SetReturn(npc!=0);
	return FALSE;
};




static zBOOL Npc_LearnSpell()
{
	int nr;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(nr);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_LearnSpell", TRUE);
	if (npc) npc->LearnSpell(nr);
	return FALSE;
}

static zBOOL Npc_SetToFistMode()
{
	zCParser *p = zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_SetToFistMode", TRUE);
	if (self) 
	{
		self -> SetWeaponMode( NPC_WEAPON_FIST );

		//
		//	REMOVE ITEM FROM HAND, INVENTORY AND WORLD
		//
		oCItem* pItem = dynamic_cast< oCItem*> ( self->GetRightHand() );
		if ( pItem )
		{
			self -> RemoveFromSlot	( NPC_NODE_RIGHTHAND, TRUE );
			self -> RemoveFromInv	( pItem );

			::ogame->GetGameWorld()->RemoveVob( pItem );
		}
	}
	return FALSE;
}

static zBOOL Npc_SetToFightMode()
{
	int nr;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(nr);
	oCNpc*	self = PopAndCheckValidNPC("Npc_SetToFightMode", TRUE);

	if (self)
	{
		//
		//	DO NOT INSERT TWICE
		//
		oCItem* pItem = dynamic_cast< oCItem*> ( self->GetRightHand() );	
		if ( pItem ) return FALSE;

		pItem = (oCItem*) ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,nr);
		//
		//	PLACE ITEM AT HAND AND INVENTORY
		//
		if (pItem) {
		//	pItem->SetFlag( ITM_FLAG_ACTIVE );
			self -> PutInInv		(pItem);
			self -> PutInSlot		( "ZS_RIGHTHAND", pItem, TRUE );
		//	self -> SetRightHand	(pItem);

			// [BENDLIN] Addon
			// JUUUUNGEEEEE!!!
			// Wird zum Finishen benutzt - ABER auch bei Gobbos
			// (Warum es bisher funktionierte? Gute Frage! Spontane Selbstheilung?)
			int guild = self->GetTrueGuild();
			if (guild == NPC_GIL_NONE)
				guild = self->GetGuild();
			
			if (guild < NPC_GIL_HUMANS)
				self->SetWeaponMode(NPC_WEAPON_1HS);  // FIXME: passend zur Waffe
			else
				self->SetWeaponMode(NPC_WEAPON_FIST);
		}
#ifdef CHECK_SCRIPT_PARANOID
		else
		{
			zCPar_Symbol *sym = p->GetSymbol(nr);
			zSTRING itemName  = sym ? sym->name : "[UNKNOWN]";
			DebugOut("Npc_SetToFightMode(): item could not be created for fight mode. illegal item: " + itemName, TRUE);
		};
#endif
		zRELEASE(pItem);
	}

	return FALSE;
}

static zBOOL Npc_HasItems()
{
	int index;
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(index);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_HasItems", TRUE);
	if (npc) {
		int amount = npc->inventory2.GetAmount(index);
		p->SetReturn(amount);
	} 
	else	 
		p->SetReturn (0);
	return FALSE;
}

static zBOOL Npc_GiveItem()
//EXTERN FUNC VOID GiveItem			(VAR C_NPC _npc, VAR FUNCREF id, VAR C_NPC target8);
// Ein NPC gibt ein Item an einen anderen !
{
	int instance		= 0;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc*		target	= PopAndCheckValidNPC("Npc_GiveItem", TRUE);
	p->GetParameter	(instance);
	oCNpc*	npc			= PopAndCheckValidNPC("Npc_GiveItem", TRUE);
	if (npc && target) {
		
		zCPar_Symbol*	sym		= p		-> GetSymbol(instance);
		if (sym && sym->name=="ITEM") {
			// Verweis auf variable Item-Instanz 
			oCItem* item		= dynamic_cast<oCItem*>((zCVob*)sym->GetInstanceAdr());
			if (item) instance	= item -> GetInstance();
		}

		if (instance>=0) {

			// Ist das Item im TradeContainer gemeint ?
			oCItem* tradeItem = npc->GetTradeItem();
			if (tradeItem && (tradeItem->GetInstance() == instance)) {
				npc		-> CloseTradeContainer();
				target	-> CloseTradeContainer();
			}

			oCItem* item = npc -> RemoveFromInv(instance);
			target -> PutInInv(item);
		}
	}
	return FALSE;
}

//
//	CODECHANGE [ROMAN]
//
static zBOOL Npc_CreateInvItem()
//EXTERN FUNC VOID Npc_CreateInvItem		(VAR C_NPC _npc, VAR FUNCREF item1);
// Create this Item into Inventory of NPC
// Get Pointer to NPC
{
	int index;
	oCItem* item;
	zCParser *p = zCParser :: GetParser();
	
	p   -> GetParameter(index);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_CreateInvItem", TRUE);
	
	// Nix erzeugen, falls gerade Savegame geladen wird (nicht noetig -> optimierung)
	if (npc && ogame && !ogame->IsInLoadSaveGame())
	{
		// [BENDLIN]
		SaveParserVars();  // save SELF, OTHER, ...

		item		= (oCItem*)ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,index);
		// FIXME : Hier ein zRELEASE -> weil RefCtr auf "3"
		// 1	 - new
		// 2 + 3 - InsertInLists
		// aber noch nicht in Welt !
		if (item) 
		{
			oCItem* item2 = npc -> PutInInv( item );
			parser.SetInstance("ITEM", item2);
		}
#ifdef CHECK_SCRIPT_PARANOID
		else
		{
			zCPar_Symbol *sym = p->GetSymbol(index);
			zSTRING itemName  = sym ? sym->name : "[UNKNOWN]";
			DebugOut("Npc_CreateInvItem(): item could not be created. illegal item: " + itemName, TRUE);
		}
#endif
		zRELEASE(item);

		RestoreParserVars();  // restore SELF, OTHER, ...
	}
	return FALSE;
}

static zBOOL Npc_CreateInvItems()
//EXTERN FUNC VOID Npc_CreateInvItems		(VAR C_NPC _npc, VAR FUNCREF item1, VAR INT anz);
{
	int index,anz;
	zCParser *p = zCParser :: GetParser();
	
	p->GetParameter(anz);
	p->GetParameter(index);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_CreateInvItems", TRUE);
	// Nix erzeugen, falls gerade Savegame geladen wird (nicht noetig -> optimierung)
	if (npc && ogame && !ogame->IsInLoadSaveGame())
	{
		// [BENDLIN]
		SaveParserVars();  // save SELF, OTHER, ...

		npc -> CreateItems(index,anz);

		RestoreParserVars();  // restore SELF, OTHER, ...
	}
	return FALSE;
}

static zBOOL Npc_RemoveInvItem()
//EXTERN FUNC INT Npc_RemoveInvItem		(VAR C_NPC npc, VAR INT item);
// Removes the desired amount of specified items of type item
{
	int nIndex;																			// item's index in npc's inventory
	
	zCParser*	p		= zCParser :: GetParser();									// get current global parser
				p -> GetParameter( nIndex  );										// get item's index in npc's inventory
	oCNpc*		pNpc		= PopAndCheckValidNPC("Npc_RemoveInvItem", TRUE);	// retrieve the npc
	oCItem*		pItem		= NULL;
	if (pNpc)   pItem		= pNpc->IsInInv( nIndex, 1 );								// check inventory for desired amount of chosen item
	zBOOL		wasRemoved	= FALSE;													// assume failure

	if ( pItem != NULL )																// is desired amount available?
	{
		// [BENDLIN]
		SaveParserVars();  // save SELF, OTHER, ...
		
		pNpc->RemoveFromInv( nIndex, 1 );												// actually remove the amount of chosen item
		wasRemoved = TRUE;																// tell the script that removal succeeded

		RestoreParserVars();  // restore SELF, OTHER, ...
	}

	p->SetReturn( wasRemoved );													// pass result on to script

	return FALSE;
}


// [EDENFELD] neu 1.09
// Remove all Inventory Items, except Mission-Items
static zBOOL Npc_ClearInventory()
{
	zCParser*	p		= zCParser::GetParser();
	oCNpc*		pNpc	= PopAndCheckValidNPC("Npc_ClearInventory", TRUE);

	// Wenn das Inventory nicht leer ist
	if ( (NULL != pNpc) && !pNpc->inventory2.IsEmpty() )
	{
		// Alle Inventory-Kategorien durchgehen

		// [BENDLIN]
		SaveParserVars();  // save SELF, OTHER, ...

		// Davon ausgehen, dass ALLE items gel�scht werden m�ssen
		int itemsToBeLeft = 0;
		// Durchlaufen bis Schwellenwert erreicht wurde
		while (pNpc->inventory2.GetNumItemsInCategory() > itemsToBeLeft)
		{
			oCItem* pItem = pNpc->inventory2.GetItem(itemsToBeLeft);
			if (pItem)
			{
				int anz = pNpc->inventory2.GetAmount(pItem->GetInstance());
				// Wenn Items vorhanden 
				if ( anz > 0 )
				{
					// Checken ob Item evtl. ein Missions-Item ist oder angelegt wurde
					if ( pItem->HasFlag(ITM_FLAG_MI) || pItem->HasFlag(ITM_FLAG_ACTIVE) )
					{	// dann die Abbruchbedingung �ndern
						itemsToBeLeft++;
					}
					else // dann schmeiss es raus !
					{
						pNpc->RemoveFromInv(pItem, anz);
					}
				}
			}
		}

		RestoreParserVars();  // restore SELF, OTHER, ...
	}	
	return FALSE;
}
// ---- [KARK]


static zBOOL Npc_RemoveInvItems()
//EXTERN FUNC INT Npc_RemoveInvItems	(VAR C_NPC npc, VAR INT item, VAR INT count);
// Removes the desired amount of specified items of type item
{
	int nIndex,																			// item's index in npc's inventory
		nAmount;																		// amount of chosen item to be removed
	
	zCParser*	p = zCParser :: GetParser();									// get current global parser
				p -> GetParameter( nAmount );										// get amount 
				p -> GetParameter( nIndex  );										// get item's index in npc's inventory
	oCNpc*		pNpc		= PopAndCheckValidNPC("Npc_RemoveInvItems", TRUE);			// retrieve the npc

	oCItem*		pItem		= NULL;
	if (pNpc)   pItem		= pNpc->IsInInv(nIndex);									// check inventory for desired item
	zBOOL		wasRemoved	= FALSE;													// assume failure

	if ( pItem != NULL )																// is desired amount available?
	{
		// [BENDLIN]
		SaveParserVars();  // save SELF, OTHER, ...
		
		if (pItem->MultiSlot() && pNpc->IsInInv(nIndex, nAmount))
			pNpc->RemoveFromInv(nIndex, nAmount);
		else
			for (int i=0; i<nAmount; i++)
				if (!pNpc->RemoveFromInv(nIndex, 1))
					break;
		wasRemoved = TRUE;

		RestoreParserVars();  // restore SELF, OTHER, ...
	}

	p->SetReturn( wasRemoved );													// pass result on to script

	return FALSE;
}
//
//	CODECHANGE [ROMAN] END
//

static zBOOL EquipItem()
{
	int index;
	oCItem *item;
	zCParser *p = zCParser :: GetParser();

	p->GetParameter(index);
	oCNpc* npc	= PopAndCheckValidNPC("EquipItem", TRUE);
	if (npc && ogame && !ogame->IsInLoadSaveGame()) {
		// Item erschaffen
		item =  (oCItem*) ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,index);

		if (item)
		{
			item -> SetFlag (ITM_FLAG_ACTIVE);
			// Als erstes ins Inventory packen
			npc  -> PutInInv(item);

			// [EDENFELD] 1.09 auch besondere Qualit�ten des (magischen) Items mit aktivieren (mehr Health z.B.)
			npc  ->AddItemEffects (item);
			// und releasen
			zRELEASE(item);
		}
#ifdef CHECK_SCRIPT_PARANOID
		else
		{
			zCPar_Symbol *sym = p->GetSymbol(index);
			zSTRING itemName  = sym ? sym->name : "[UNKNOWN]";
			DebugOut("EquipItem(): item could not be created. illegal item: " + itemName, TRUE);
		};
#endif
	}
	return FALSE;
}

static zBOOL Npc_HasDetectedNpc()
{
	zCParser* p		= zCParser :: GetParser();
	oCNpc* other	= PopAndCheckValidNPC("Npc_HasDetectedNpc", TRUE);
	oCNpc* self		= PopAndCheckValidNPC("Npc_HasDetectedNpc", TRUE);
	if (self && other) {
		p->SetReturn(self->HasVobDetected(other));
	}
	return FALSE;
}

static zBOOL Npc_IsDead()
{
	zCParser* p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_IsDead", TRUE);
	if (npc) {
		p->SetReturn(npc->IsDead());
	} else {
		// Not found. Whatever was asked -> its gone and dead....
		p->SetReturn(TRUE);
	}
	return FALSE;
}

static zBOOL Npc_ChangeAttribute()
{
	int value,atr;
	zCParser* p	= zCParser :: GetParser();
	p -> GetParameter (value);
	p -> GetParameter (atr);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_ChangeAttribute", TRUE);
	if (npc) npc -> ChangeAttribute (atr,value);
	return FALSE;
}

static zBOOL Npc_SetAttitude()
{
	int att;
	zCParser* p	= zCParser :: GetParser();
	p	-> GetParameter		(att);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_SetAttitude", TRUE);
	if (npc) npc -> SetAttitude (att);
	return FALSE;
}

static zBOOL Npc_SetTempAttitude()
{
	int att;
	zCParser* p	= zCParser :: GetParser();
	p	-> GetParameter		(att);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_SetTempAttitude", TRUE);
	if (npc) npc -> SetTmpAttitude (att);
	return FALSE;
}

static zBOOL Npc_GetAttitude()
{
	zCParser* p	 = zCParser :: GetParser();
	oCNpc* other = PopAndCheckValidNPC("Npc_GetAttitude", TRUE);
	oCNpc* npc	 = PopAndCheckValidNPC("Npc_GetAttitude", TRUE);
	if (npc && other) p -> SetReturn (npc -> GetAttitude(other));
	return FALSE;
}

static zBOOL Npc_GetPermAttitude()
{
	zCParser* p	 = zCParser :: GetParser();
	oCNpc* other = PopAndCheckValidNPC("Npc_GetPermAttitude", TRUE);
	oCNpc* npc	 = PopAndCheckValidNPC("Npc_GetPermAttitude", TRUE);
	if (npc && other) p -> SetReturn (npc -> GetPermAttitude(other));
	return FALSE;
}

static zBOOL Npc_PerceiveAll()
{
	zCParser* p	 = zCParser :: GetParser();
	oCNpc* npc	 = PopAndCheckValidNPC("Npc_PerceiveAll", TRUE);
	if (npc) npc -> PerceiveAll();
	return FALSE;
}

static zBOOL Npc_StartItemReactModules ()
{
	zBOOL success = FALSE;
	oCNpc*	self, *other;
	oCItem* item;
	
//	SaveParserGlobals();

	zCParser* p	= zCParser :: GetParser();
	item	= PopAndCheckValidItem("Npc_StartItemReactModules", TRUE);
	other	= PopAndCheckValidNPC ("Npc_StartItemReactModules", TRUE);
	self	= PopAndCheckValidNPC ("Npc_StartItemReactModules", TRUE);

	if (self && other && item) {
		if (self->IsAPlayer())	success = self->CheckItemReactModule	(other,item);
		else					success = other->CheckItemReactModule	(self,item);
	}

//	RestoreParserGlobals()

	p->SetReturn(success);
	return FALSE;
}

static zBOOL Npc_HasOffered ()
{
	zBOOL success = FALSE;
	oCNpc*	self, *other;
	int instance;
	
	zCParser* p	= zCParser :: GetParser();
	p -> GetParameter(instance);
	other	= PopAndCheckValidNPC("Npc_HasOffered", TRUE);
	self	= PopAndCheckValidNPC("Npc_HasOffered", TRUE);

	if (self && other) {	
		oCItem* item = other->GetTradeItem();
		if (item && other->IsSelfPlayer())	{
			// FIXME : Wirklich diesem NSC ( self ) angeboten ?
			success = (item->GetInstance() == instance);
		}
	}
	p->SetReturn(success);
	return FALSE;
}

static zBOOL Npc_OwnedByNpc ()
{
	zBOOL owned		= FALSE;
	zCParser* p		= zCParser :: GetParser();
	oCNpc*	self	= PopAndCheckValidNPC("Npc_OwnedByNpc", TRUE);
	oCItem* item	= PopAndCheckValidItem("Npc_OwnedByNpc", TRUE);
	if (self && item) {
		owned = item->IsOwnedByNpc(self->GetInstance());	
	}
	p->SetReturn (owned);
	return FALSE;
}

static zBOOL Npc_OwnedByGuild ()
{
	int guild;
	zBOOL owned		= FALSE;
	zCParser* p		= zCParser :: GetParser();
	p -> GetParameter (guild);
	oCItem* item	= PopAndCheckValidItem("Npc_OwnedByGuild", TRUE);
	if (item) {
		owned = item->IsOwnedByGuild(guild);	
	}
	p->SetReturn (owned);
	return FALSE;
}

static zBOOL Npc_IsWayBlocked()
{
	zBOOL blocked	= FALSE;
	zCParser* p		= zCParser :: GetParser();
	oCNpc* self		= PopAndCheckValidNPC("Npc_IsWayBlocked", TRUE);
	if (self) {
		// Blocked by obstacle
		zCVob*		vobObstacle;
		zVEC3		vecNormal;
		zTBBox3D bbox	= self->GetModel()->GetBBox3D();
		zREAL dist		= 100 + (bbox.maxs[VZ] - bbox.mins[VZ]) / 2;	
		blocked			= self->RbtGetObstacle	 ( self->GetPositionWorld(),
												   self->GetAtVectorWorld() * dist,
												   vobObstacle, vecNormal   );
		zBOOL		isObstacleNpc = ( dynamic_cast<oCNpc*>(vobObstacle) != NULL );
		if (!blocked && isObstacleNpc) blocked = TRUE;
		if (!blocked)
		{
			oCAIHuman* ai	= dynamic_cast<oCAIHuman*>(self->GetAI());
			if (ai) blocked = !ai->CheckEnoughSpaceMoveForward();
		}
	} 	
	p->SetReturn(blocked);
	return FALSE;
}

// *************************************************************************************
// Artificial Intelligence
// *************************************************************************************

/* ----------------------------------------------------------------------
	
	AI_Output()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_Output()
{
	zCEventMessage* oldMsg	= NULL;
	zCParser* p	= zCParser :: GetParser();
	zSTRING name;
	p -> GetParameter (name);
	oCNpc* target	= PopAndCheckValidNPC("AI_Output", TRUE);
	oCNpc* npc		= PopAndCheckValidNPC("AI_Output", TRUE);
	if (npc) {
		if (target) {
			// Gucke ob "target" einen Eintrag mit "npc" als Ziel hat. 
			// Dann auf Beendigung dieser Msg warten
			zCEventMessage* evMsg = target->GetTalkingWithMessage(npc);
			oldMsg = evMsg;
			if (evMsg) {
				oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_WAITTILLEND,target);
				msg->watchMsg = evMsg;
				npc->GetEM()->OnMessage(msg,npc);
			}
		}
		oCMsgConversation* convMsg = zNEW(oCMsgConversation)(oCMsgConversation::EV_OUTPUT,name);
		convMsg->target = target;
		npc -> GetEM() -> OnMessage(convMsg,npc);

		if (oldMsg) {
			// Target soll auch warten, bis diese Message durch ist.
			oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_WAITTILLEND,npc);
			msg->watchMsg = convMsg;
			target->GetEM()->OnMessage(msg,npc);
		}
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_OutputSVM()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_OutputSVM()
{
	zSTRING name;
	zCParser* p		= zCParser :: GetParser();
	p -> GetParameter (name);
	oCNpc* target	= PopAndCheckValidNPC("AI_OutputSVM", TRUE);
	oCNpc* npc		= PopAndCheckValidNPC("AI_OutputSVM", TRUE);
	if (npc) {
		if (target) {
			// Gucke ob "target" einen Eintrag mit "npc" als Ziel hat. 
			// Dann auf Beendigung dieser Msg warten
			zCEventMessage* evMsg = target->GetTalkingWithMessage(npc);
			if (evMsg) {
				oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_WAITTILLEND,target);
				msg->watchMsg = evMsg;
				npc->GetEM()->OnMessage(msg,npc);
			}
		}
		oCMsgConversation* convMsg = zNEW(oCMsgConversation)(oCMsgConversation::EV_OUTPUTSVM,name);
		convMsg->target = target;
		npc -> GetEM() -> OnMessage(convMsg,npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_OutputSVM_Overlay()

	24.11.2000	[Wohlers]	
				erstellt.

   ---------------------------------------------------------------------- */

static zBOOL AI_OutputSVM_Overlay()
{
	zSTRING name;
	zCParser* p		= zCParser :: GetParser();
	p -> GetParameter (name);
	oCNpc* target	= PopAndCheckValidNPC("AI_OutputSVM_Overlay", TRUE);
	oCNpc* npc		= PopAndCheckValidNPC("AI_OutputSVM_Overlay", TRUE);
	if (npc) {
		if (target) {
			// Gucke ob "target" einen Eintrag mit "npc" als Ziel hat. 
			// Dann auf Beendigung dieser Msg warten
			zCEventMessage* evMsg = target->GetTalkingWithMessage(npc);
			if (evMsg) {
				oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_WAITTILLEND,target);
				msg->watchMsg = evMsg;
				npc->GetEM()->OnMessage(msg,npc);
			}
		}
		oCMsgConversation* convMsg = zNEW(oCMsgConversation)(oCMsgConversation::EV_OUTPUTSVM_OVERLAY,name);
		convMsg->target = target;
		npc -> GetEM() -> OnMessage(convMsg,npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_PlayCutscene()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_PlayCutscene()
{
	zSTRING csName;
	zCParser* p		= zCParser :: GetParser();
	p -> GetParameter (csName);
	oCNpc* npc	= PopAndCheckValidNPC("AI_PlayCutscene", TRUE);
	if (npc) {
		npc -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_CUTSCENE,csName,npc->GetVobName()),npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_PlayAni()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_PlayAni()
{
	zSTRING s;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter(s);
	oCNpc* npc	= PopAndCheckValidNPC("AI_PlayAni", TRUE);
	if (npc) {
		oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_PLAYANI_NOOVERLAY,s);
		msg -> number   = BS_STAND;	// Bodystate nicht aendern
		npc -> GetEM() -> OnMessage(msg,npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_PlayAniBS()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_PlayAniBS()
// PlayAni mit BodyState
{
	zSTRING s;
	int nextBodyState = BS_STAND;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter(nextBodyState);
	p->GetParameter(s);
	oCNpc* npc		= PopAndCheckValidNPC("AI_PlayAniBS", TRUE);
	if (npc) {
		oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_PLAYANI_NOOVERLAY,s);
		msg -> number   = nextBodyState;
		npc -> GetEM() -> OnMessage(msg,npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_Wait()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_Wait()
// Sekunden
{
	zREAL delay;
	zCParser *p		= zCParser :: GetParser();
	p -> GetParameter(delay);
	oCNpc* npc	= PopAndCheckValidNPC("AI_Wait", TRUE);
	if (npc) npc -> GetEM() -> OnMessage(zNEW(oCMsgState)(oCMsgState::EV_WAIT,delay*1000),npc);	
	return TRUE;
}

static zBOOL AI_Waitms()
// Sekunden
{
	int delay;
	zCParser *p		= zCParser :: GetParser();
	p -> GetParameter(delay);
	oCNpc* npc	= PopAndCheckValidNPC("AI_WaitMS", TRUE);
	if (npc) npc -> GetEM() -> OnMessage(zNEW(oCMsgState)(oCMsgState::EV_WAIT,delay),npc);	
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_WaitTilEnd()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_WaitTillEnd()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* other= PopAndCheckValidNPC("AI_WaitTillEnd", TRUE);
	oCNpc* self = PopAndCheckValidNPC("AI_WaitTillEnd", TRUE);
	if (self && other) {
		oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_WAITTILLEND,other);
		int nr = other -> GetEM()->GetNumMessages();
		zCEventMessage* watch = NULL;
		for (int i=nr-1; i>=0; i--) {
			watch = other->GetEM()->GetEventMessage(i);
			if (!watch->IsOverlay()) {
				msg->watchMsg = watch;
				break;
			}		
		}
		self -> GetEM() -> OnMessage(msg ,self);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_GotoWP()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_GotoWP()
{
	zSTRING s;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter(s);
	oCNpc* npc	= PopAndCheckValidNPC("AI_GotoWP", TRUE);
	if (npc) {
			
		if (s.IsEmpty()) {
			zERR_WARNING("U:NPC:AI_GotoWP Waypoint is empty ! Ignored.message : "+npc->GetInstanceName());
			return TRUE;
		}
		npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_GOROUTE,s), npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_GotoNpc

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_GotoNpc()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* other	= PopAndCheckValidNPC("AI_GotoNpc", TRUE);
	oCNpc* npc		= PopAndCheckValidNPC("AI_GotoNpc", TRUE);

	if (npc && other) {
		npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_GOTOVOB,other), npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_GotoItem()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_GotoItem()
{
	zCParser *p		= zCParser :: GetParser();
	oCItem* item	= PopAndCheckValidItem("AI_GotoItem", TRUE);
	oCNpc* npc		= PopAndCheckValidNPC("AI_GotoItem", TRUE);;
	if (npc && item) {
		npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_GOTOVOB,item), npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_GotoSount()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_GotoSound()
{
	zCParser* p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_GotoSound", TRUE);
	if (npc) {
		npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_GOTOPOS, npc->GetSoundPosition()),npc);		
	}
	return TRUE;
}

// *************************************************************************************
// Freepoints 
// *************************************************************************************

static zBOOL Wld_IsFPAvailable()
{
	zSTRING fpName;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter	(fpName); fpName.Upper();
	oCNpc*		npc	= PopAndCheckValidNPC("Wld_IsFPAvailable", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... fpName: " + fpName, TRUE);
	};
#endif
	zCVobSpot*	spot= NULL;
	if (npc)    spot= npc ->FindSpot(fpName,1);	// Den naechsten waehlen
	p->SetReturn(spot!=NULL);
	return TRUE;
}

static zBOOL Wld_IsNextFPAvailable()
{
	zSTRING fpName;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter	(fpName); fpName.Upper();
	oCNpc*		npc	= PopAndCheckValidNPC("Wld_IsNextFPAvailable", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... fpName: " + fpName, TRUE);
	};
#endif
	zCVobSpot*	spot= NULL;
	if (npc)    spot= npc ->FindSpot(fpName,0); // den erstbesten benutzen
	p->SetReturn(spot!=NULL);
	return TRUE;
}

static zBOOL Npc_IsOnFP()
{
	zBOOL isonwp = FALSE;
	zSTRING s;
	zCParser *p	= zCParser :: GetParser();
	p->GetParameter(s);
	oCNpc*		npc	= PopAndCheckValidNPC("Npc_IsOnFP", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... fpName: " + s, TRUE);
	};
#endif
	if (npc) {
		zCVobSpot* spot = npc -> FindSpot	(s,TRUE, 100);
		isonwp = (spot && spot-> IsOnFP		(npc));
	}
	p->SetReturn(isonwp);
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_AlignToFP()

	06.10.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */

static zBOOL AI_AlignToFP()
{
	zCParser *p		= zCParser :: GetParser();

	oCNpc*	 pSelf = PopAndCheckValidNPC("AI_AlignToFP", TRUE);
	
	if ( pSelf ) 
	{
		oCMsgMovement* pMsg = zNEW(oCMsgMovement)(oCMsgMovement::EV_ALIGNTOFP, "" );
		pSelf->GetEM()->OnMessage( pMsg, pSelf );
	}

	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_GotoFP()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_GotoFP()
{
	zSTRING fpName;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter	(fpName); fpName.Upper();
	oCNpc*		npc	= PopAndCheckValidNPC("AI_GotoFP", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... fpName: " + fpName, TRUE);
	};
#endif
 
	if (npc) {
		oCMsgMovement* msg = zNEW(oCMsgMovement)	(oCMsgMovement::EV_GOTOFP,fpName);
		msg -> targetMode = 1;	// CheckDistance an. Immer den nahesten nehmen.
		npc -> GetEM() -> OnMessage(msg,npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_GotoNextPF()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_GotoNextFP()
{
	zSTRING fpName;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter	(fpName); fpName.Upper();
	oCNpc*		npc	= PopAndCheckValidNPC("AI_GotoNextFP", FALSE);;
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... fpName: " + fpName, TRUE);
	};
#endif
	if (npc) {
		oCMsgMovement* msg = zNEW(oCMsgMovement)	(oCMsgMovement::EV_GOTOFP,fpName);
		msg -> targetMode = 0;	// Suche zufaellig einen aus, kein CheckDistance.
		npc -> GetEM() -> OnMessage(msg,npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_DrawWeapon()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_DrawWeapon()
{
	zCParser* p	= zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("AI_DrawWeapon", TRUE);;
	if (self) self -> GetEM() -> OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON), self);
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_RemoveWeapon()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_RemoveWeapon()
{
	zCParser* p		= zCParser :: GetParser();
	oCNpc* self		= PopAndCheckValidNPC("AI_RemoveWeapon", TRUE);;
	// [EDENFELD] 1.09: NPC mit gezogener Fernkampfwaffe h�rt bei AI_RemoveWeapon automatisch
	// auf zu zielen
	if (self)
	{
		oCItem *item = self -> GetWeapon();
		if ( (item) && (item->HasFlag(ITM_CAT_FF)) )
		{
			// npc hat fernkampfwaffe gezogen. H�r doch mal auf zu zielen
			oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_STOPAIM, NULL );
			self->GetEM()->OnMessage( pMsg , self );
		}
		self -> GetEM() -> OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON), self);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_SetWalkMode

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_SetWalkMode()
{
	int modenr;
	zCParser *p		= zCParser :: GetParser();
	p  -> GetParameter(modenr);
	oCNpc* self = PopAndCheckValidNPC("AI_SetWalkMode", TRUE);
	if (self) self -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_SETWALKMODE, modenr),self);
	return TRUE;
}

// ************************ Weapon Info V1.42 **************************

static zBOOL Npc_AreWeStronger()
{
	zBOOL stronger	= FALSE;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* self		= PopAndCheckValidNPC("Npc_AreWeStronger", TRUE);	// man selber
	oCNpc* other	= PopAndCheckValidNPC("Npc_AreWeStronger", TRUE);	// einer der Feinde
	if (self && other) {
		stronger = self->AreWeStronger(other);
	}
	p -> SetReturn (stronger);
	return FALSE;
}

static zBOOL Npc_SetTarget()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* enemy	= PopAndCheckValidNPC("Npc_SetTarget", TRUE);	// der feind
	oCNpc* self		= PopAndCheckValidNPC("Npc_SetTarget", TRUE);	// man selber
	if (self) {
		if (!enemy) 
		{			
			zERR_WARNING("C: skript: Npc_SetTarget(): target is not valid. self is:"  + self->GetInstanceName());
		}
		self->SetEnemy(enemy);
	};
	return FALSE;	
}

static zBOOL Npc_GetTarget()
{
	oCNpc* target	= NULL;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* self		= PopAndCheckValidNPC("Npc_GetTarget", TRUE);	// man selber
	if (self) {
		target = self->GetEnemy();
		p->SetInstance("OTHER",target);
	};
	p -> SetReturn (target!=NULL);
	return FALSE;
}

static zBOOL Npc_GetNextTarget()
{
	oCNpc*		enemy	= NULL;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc*		npc		= PopAndCheckValidNPC("Npc_GetNextTarget", TRUE);
	if (npc)	enemy	= npc->GetNextEnemy();
	parser.SetInstance	("OTHER",enemy);
	p->SetReturn		(enemy!=NULL);
	return FALSE;
};

static zBOOL Npc_IsNextTargetAvailable()
{
	oCNpc*		enemy	= NULL;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc*		npc		= PopAndCheckValidNPC("Npc_IsNextTargetAvailable", TRUE);
	if (npc)	enemy	= npc->GetNextEnemy();
	p->SetReturn		(enemy!=NULL);
	return FALSE;
};


static zBOOL Npc_GetLookAtTarget()
{
	oCNpc*		enemy	= NULL;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc*		npc		= PopAndCheckValidNPC("Npc_GetLookAtTarget", TRUE);
	if (npc)	enemy	= zDYNAMIC_CAST<oCNpc>(npc->GetAnictrl()->targetVob);
	p->SetReturn		(enemy);
	return FALSE;
};


static zBOOL Npc_GetDetectedMob()
{
	static zSTRING		mobScheme;
	oCMobInter* mob		= NULL;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc*		npc		= PopAndCheckValidNPC("Npc_GetDetectedMob", TRUE);
	if (npc) 
	{
		mob = npc->GetInteractMob();
		if ( ! mob )
			mob = dynamic_cast<oCMobInter*>(npc->GetRbtObstacleVob());

		if (mob) 
			mobScheme = mob->GetScemeName().PickWord( 1, "_", "_" );
	}
	p->SetReturn (mobScheme);
	return FALSE;
}

static zBOOL Npc_IsDetectedMobOwnedByNpc()
{
	oCMobInter* mob		= NULL;
	zBOOL		owned	= FALSE;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc*		owner	= PopAndCheckValidNPC("Npc_IsDetectedMobOwnedByNpc", TRUE);
	oCNpc*		user	= PopAndCheckValidNPC("Npc_IsDetectedMobOwnedByNpc", TRUE);
	if (user && owner) {
		mob = user->GetInteractMob();
		if ( ! mob )
			mob		= dynamic_cast<oCMobInter*>(user ->GetRbtObstacleVob());

		owned	= (mob && mob->IsOwnedByNpc(owner->GetInstance()));
	}
	p->SetReturn (owned);
	return FALSE;
}

static zBOOL Npc_IsDetectedMobOwnedByGuild()
{
	int guild;
	oCMobInter* mob		= NULL;
	zBOOL		owned	= FALSE;
	zCParser*	p		= zCParser :: GetParser();
	p->GetParameter (guild);
	oCNpc*		user	= PopAndCheckValidNPC("Npc_IsDetectedMobOwnedByGuild", TRUE);
	if (user) {
		mob = user->GetInteractMob();
		if ( ! mob )
			mob		= dynamic_cast<oCMobInter*>	 (user->GetRbtObstacleVob());

		owned	= (mob && mob->IsOwnedByGuild(guild));
	};
	p->SetReturn (owned);
	return FALSE;
}

/*--------------------------------------------------------------------------

    Wld_GetMobState()

    06-Oct-00       [Roman Keskenti]
						
						Initial implementation
	25-Oct-00		[Ulf Wohlers]
						Zusaetzliche Abfrage, ob NSC bereits in MobInteraktion

--------------------------------------------------------------------------*/ 

static zBOOL Wld_GetMobState()
{
	zCParser*	p = zCParser :: GetParser();
	zSTRING		strScheme; p->GetParameter( strScheme );
	oCNpc*		user	= PopAndCheckValidNPC("Wld_GetMobState", TRUE);
	oCMobInter* mob		= NULL;
	int			nState	= -1;

	if ( user )
	{
		// Bereits in MobInteraktion ?
		if (user->GetInteractMob()) mob		= user->GetInteractMob();
		else						mob		= user->FindMobInter( strScheme );
		if ( mob )					nState	= mob->GetState();
	}
	p->SetReturn( nState );

	return FALSE;
}

/*--------------------------------------------------------------------------
    Npc_IsEnemyBehindFriend()()

    25-Aug-00       [Roman Keskenti]

						By Design-Change of Aug, 24th 2000, this
						function has become obsolete!
	22-Sep-00		[RUEVE]
						Darum jetzt ganz weg damit!
--------------------------------------------------------------------------*/ 
/*static zBOOL Npc_IsEnemyBehindFriend()
{
	oCNpc* friend1	= NULL;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* other	= dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());	// einer der Feinde
	oCNpc* self		= dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());	// man selber
	if (self && other) {
		friend1		= other->IsEnemyBehindFriend(self);
		p->SetInstance("VICTIM",friend1);
	}
	p -> SetReturn (friend1!=NULL);
	
	return FALSE;
} */

static zBOOL Npc_GetReadiedWeapon()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc		= PopAndCheckValidNPC("Npc_GetReadiedWeapon", TRUE);
	oCItem *item	= (npc) ? npc -> GetWeapon() : NULL;
	p -> SetReturn ( item );
	return FALSE;
}

static zBOOL Npc_GetEquippedMeleeWeapon()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc		= PopAndCheckValidNPC("Npc_GetEquippedMeleeWeapon", TRUE);
	oCItem *item	= (npc) ? npc -> GetEquippedMeleeWeapon() : NULL;
	p -> SetReturn ( item );
	return FALSE;
}

static zBOOL Npc_GetEquippedRangedWeapon()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc		= PopAndCheckValidNPC("Npc_GetEquippedRangedWeapon", TRUE);
	oCItem *item	= (npc) ? npc -> GetEquippedRangedWeapon() : NULL;
	p -> SetReturn ( item );
	return FALSE;
}

static zBOOL Npc_GetEquippedArmor()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc		= PopAndCheckValidNPC("Npc_GetEquippedArmor", TRUE);
	oCItem *item	= (npc) ? npc -> GetEquippedArmor() : NULL;
	p -> SetReturn ( item );
	return FALSE;
}

static zBOOL Npc_GetNearestWP()
{
	static zSTRING name;
	name.Clear();
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_GetNearestWP", TRUE);
	if (npc && npc->GetHomeWorld()) {
		zCWaypoint* wp = npc -> GetHomeWorld() -> GetWayNet() -> GetNearestWaypoint(npc->GetPositionWorld());
		if (wp)	name = wp -> GetName();
	}
	p -> SetReturn(name);

	return FALSE;
}

static zBOOL Npc_GetNextWP()
{
	static zSTRING name;
	name = "";
	zCParser *p		= zCParser :: GetParser();
	oCNpc *npc	= PopAndCheckValidNPC("Npc_GetNextWP", TRUE);
	if (npc && npc->GetHomeWorld()) {
		zCWaypoint* wp = npc -> GetHomeWorld() -> GetWayNet() -> GetSecNearestWaypoint(npc->GetPositionWorld());
		if (wp)	name = wp -> GetName();
	}
	p -> SetReturn(name);

	return FALSE;
}

static zBOOL Npc_ClearAIQueue()
{
	zCParser*			p			= zCParser :: GetParser();
	oCNpc*				npc			= PopAndCheckValidNPC("Npc_ClearAIQueue", TRUE);
//	oCAniCtrl_Human*	pAniCtrl	= npc->GetAnictrl();
	if (npc) {
		npc->ClearEM();
		//if (! pAniCtrl )
		//pAniCtrl->StopTurnAnis();
		//npc->StandUp();
	}	
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_AlignToWP()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_AlignToWP()
// NSC blickt in dieselbe Richtung, wie der WP
{
	static zSTRING name;
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_AlignToWP", TRUE);
	if (npc && npc->GetHomeWorld()) {
		zCWaypoint* wp = npc -> GetHomeWorld() -> GetWayNet() -> GetNearestWaypoint(npc->GetPositionWorld());
		if (wp) npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_TURNTOPOS, npc->GetPositionWorld() + wp -> GetAtVectorWorld() * 200), npc);		
	}
	return TRUE;
}

static zBOOL Npc_GetTrueGuild()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_GetTrueGuild", TRUE);
	if (npc) p -> SetReturn(npc->GetTrueGuild());
	else	 p -> SetReturn(0);
	return FALSE;
}

static zBOOL Npc_SetTrueGuild()
{
	int guild;
	zCParser *p	= zCParser :: GetParser();
	p		   -> GetParameter(guild);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_SetTrueGuild", TRUE);
	if (npc)	
	{
		npc->SetTrueGuild(guild);

		if ( npc->IsAPlayer() ) ::ogame->InitNpcAttitudes();
	}
	else		zERR_WARNING("U:NPC: SetTrueGuild failed.");
	return FALSE;
}

static zBOOL Npc_KnowsPlayer()
{
	zBOOL known		= FALSE;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* player	= PopAndCheckValidNPC("Npc_KnowsPlayer", TRUE);
	oCNpc* npc		= PopAndCheckValidNPC("Npc_KnowsPlayer", TRUE);
	if (npc && player) {
		known = npc->KnowsPlayer( player->GetPlayerNumber() );
	}
	p->SetReturn(known);
	return FALSE;
}

static zBOOL Npc_SetKnowsPlayer()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* player	= PopAndCheckValidNPC("Npc_SetKnowsPlayer", TRUE);
	oCNpc* npc		= PopAndCheckValidNPC("Npc_SetKnowsPlayer", TRUE);
	if (npc && player)	npc->SetKnowsPlayer( player->GetPlayerNumber() );	
	return FALSE;
}

static zBOOL Hlp_StrCmp()
{
	zSTRING s1,s2;
	zCParser *p	= zCParser :: GetParser();
	p -> GetParameter(s2);
	p -> GetParameter(s1);
	s1.Upper(); s2.Upper();
	p -> SetReturn	 (s1==s2);
	return FALSE;
}

static zBOOL Hlp_CutscenePlayed() 
{
	zSTRING csName;
	zCParser *p	= zCParser :: GetParser();
	p -> GetParameter	(csName);
 	p->SetReturn(ogame->GetCutsceneManager()->PoolNumPlayed(csName));	
	return FALSE;
}

static zBOOL Hlp_GetNpc()
{	
	oCNpc* npc = NULL;
	int instance;
	zCParser *p	= zCParser :: GetParser();
	p -> GetParameter	(instance);
	zCPar_Symbol* sym = p->GetSymbol(instance);
	if (sym) {
		if (sym->type==zPAR_TYPE_INSTANCE) {
			npc = dynamic_cast<oCNpc*>((zCVob*)sym->GetInstanceAdr());
#ifdef CHECK_SCRIPT_VERY_PARANOID
			if (!npc && (sym->GetOffset()>0))
			{
				DebugOut("Hlp_GetNpc(): given instance is not an npc! instance name: " + sym->name, TRUE);
			};
#endif
		}
		if (!npc) {
			npc = zDYNAMIC_CAST<oCNpc>(ogame->GetGameWorld()->SearchVobByName(sym->name));
#ifdef CHECK_SCRIPT_VERY_PARANOID
			if (!npc) 
			{
				DebugOut("Hlp_GetNpc(): given instance is not in world: " + sym->name, TRUE);
			};
#endif

		}
	}
	p->SetReturn(npc);
	return FALSE;
}

static zBOOL Hlp_IsValidNpc()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc	= dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance());
	p->SetReturn(npc!=NULL);
	return FALSE;
};

static zBOOL Npc_GetInvItem()
{
	oCItem* item = NULL;
	int itemInstance;
	zCParser*	p		= zCParser :: GetParser();
	p -> GetParameter (itemInstance);
	oCNpc*		npc		= dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());
	if (npc)	item	= npc->IsInInv(itemInstance);
	parser.SetInstance("ITEM",item);

	p->SetReturn(item!=NULL);
	return FALSE;
}

//
//	CODECHANGE [ROMAN]
//
static zBOOL Npc_GetInvItemBySlot()
{
	int nCategory, 
		nSlot;

	zCParser*	p	=  zCParser :: GetParser();
				p	-> GetParameter ( nSlot		);
				p	-> GetParameter ( nCategory );
	oCNpc*		pNPC	=  PopAndCheckValidNPC("Npc_GetInvItemBySlot", TRUE);

	oCItem* pItem = (pNPC) ? pNPC->GetItem( nCategory, nSlot ) : NULL;

	parser.SetInstance( "ITEM", pItem );
	p->SetReturn( pItem ? pItem->GetAmount() : 0 );

	return FALSE;
}
//
//	CODECHANGE [ROMAN] END
//

static zBOOL Hlp_IsValidItem()
{
	zCParser *p		= zCParser :: GetParser();
	oCItem* item	= dynamic_cast<oCItem*>((zCVob*)p -> GetInstance());
	p->SetReturn(item!=NULL);
	return FALSE;
};

// ************************ Laut Konzept V1.41 **************************

/* ----------------------------------------------------------------------
	
	AI_EquipBestMeleeWeapon()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_EquipBestMeleeWeapon()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_EquipBestMeleeWeapon", TRUE);
	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_EQUIPBESTWEAPON,ITM_CAT_NF),npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_EquipBestRangedWeapon()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_EquipBestRangedWeapon()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_EquipBestRangedWeapon", TRUE);
	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_EQUIPBESTWEAPON,ITM_CAT_FF),npc);
	}	
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_EquipBestArmor()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_EquipBestArmor()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_EquipBestArmor", TRUE);
	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_EQUIPBESTARMOR),npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_UnequipWeapons()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_UnequipWeapons()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_UnequipWeapons", TRUE);
	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_UNEQUIPWEAPONS),npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_UnequipArmor()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_UnequipArmor()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_UnequipArmor", TRUE);
	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_UNEQUIPARMOR),npc);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_EquipArmor()

	25.08.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */

static zBOOL AI_EquipArmor()
{
	zCParser *p	= zCParser :: GetParser();

	int index;
	p->GetParameter (index);
	oCNpc* npc	= PopAndCheckValidNPC("AI_EquipArmor", TRUE);
	if (npc) {
		zCPar_Symbol*	sym		= p		-> GetSymbol(index);
		zSTRING			name	= sym	-> name;
		if (name=="ITEM") {
			// Verweis auf variable Item-Instanz 
			oCItem* item		= dynamic_cast<oCItem*>((zCVob*)sym->GetInstanceAdr());
			if (item) name		= item -> GetInstanceName();
		}
		if (!name.IsEmpty()) {
			oCMsgWeapon* msg = zNEW(oCMsgWeapon)(oCMsgWeapon::EV_EQUIPARMOR);
			msg->SetObjectName( name );
			npc -> GetEM() -> OnMessage(msg,npc);
		}
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_ReadyMeleeWeapon()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_ReadyMeleeWeapon()
{
	int res = 0;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_ReadyMeleeWeapon", TRUE);
	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON,NPC_WEAPON_FIST),npc);
	}	
	p -> SetReturn( res );
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_ReadyRangedWeapon()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_ReadyRangedWeapon()
{
	int res = 0;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("AI_ReadyRangedWeapon", TRUE);
	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_DRAWWEAPON,NPC_WEAPON_BOW),npc);
	}	
	p -> SetReturn( res );
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_TurnAway()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_TurnAway()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc2	= PopAndCheckValidNPC("AI_TurnAway", TRUE);
	oCNpc* npc1	= PopAndCheckValidNPC("AI_TurnAway", TRUE);
	if (npc1 && npc2) npc1 -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_TURNAWAY, npc2), npc1);		
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_TurnToNPC()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_TurnToNPC()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc2	= PopAndCheckValidNPC("AI_TurnToNPC", TRUE);
	oCNpc* npc1	= PopAndCheckValidNPC("AI_TurnToNPC", TRUE);
	if (npc1 && npc2) 
	{
		// [BENDLIN] wieder raus, weil hier definitiv nicht richtig
		// npc1->GetEM()->OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_STOPLOOKAT), npc1);
		npc1 -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_TURNTOVOB, npc2), npc1   );		
	};
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_WhirlAround()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_WhirlAround()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc2	= PopAndCheckValidNPC("AI_WhirlAround", TRUE);
	oCNpc* npc1	= PopAndCheckValidNPC("AI_WhirlAround", TRUE);
	if (npc1 && npc2) npc1 -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_WHIRLAROUND, npc2), npc1);		
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_WhirlArountToSource()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_WhirlAroundToSource()
{
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc1	= PopAndCheckValidNPC("AI_WhirlAroundToSource", TRUE);
	if (npc1) {
		npc1 -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_WHIRLAROUND, npc1->GetSoundPosition()), npc1);	
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_CanSeeNpc()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_CanSeeNpc()
{
	int funcNr;
	zCParser *p	= zCParser :: GetParser();
	p->GetParameter(funcNr);
	oCNpc* npc2	= PopAndCheckValidNPC("AI_CanSeeNpc", TRUE);
	oCNpc* npc1	= PopAndCheckValidNPC("AI_CanSeeNpc", TRUE);
	if (npc1 && npc2) {
		oCMsgMovement* msg	= zNEW(oCMsgMovement)(oCMsgMovement::EV_CANSEENPC,npc2);
		msg  -> targetMode	= funcNr;
		npc1 -> GetEM() -> OnMessage(msg,npc1);
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_TurnToSound()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_TurnToSound()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc		= PopAndCheckValidNPC("AI_TurnToSound", TRUE);
	if (npc) npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_TURNTOPOS, npc->GetSoundPosition()), npc);
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_QuickLook()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_QuickLook()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc2		= PopAndCheckValidNPC("AI_QuickLook", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC("AI_QuickLook", TRUE);
	if (npc1 && npc2) {
		npc1 -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_QUICKLOOK, npc2), npc1);		
	}
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_LookAtNpc()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_LookAtNpc()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc2		= PopAndCheckValidNPC("AI_LookAtNpc", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC("AI_LookAtNpc", TRUE);
	if (npc1 && npc2) {
		npc1 -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_LOOKAT, npc2), npc1);		
	}
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_LookAt()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_LookAt()
{
	zSTRING name;
	zCParser *p	= zCParser :: GetParser();
	p -> GetParameter (name);
	oCNpc* npc1	= PopAndCheckValidNPC("AI_LookAt", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc1)
	{
		DebugOut("... name: " + name, TRUE);
	};
#endif
	
	if (npc1) {
		npc1 -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_LOOKAT, name), npc1);		
	}
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_StopLookAt()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_StopLookAt()
{
	zCParser*	p	= zCParser :: GetParser();
	oCNpc* npc		= PopAndCheckValidNPC("AI_StopLookAt", TRUE);
	if (npc) {
		npc -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_STOPLOOKAT), npc);		
	}
	return FALSE;
}	

/* ----------------------------------------------------------------------
	
	AI_PointAtNpc()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_PointAtNpc()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc2		= PopAndCheckValidNPC("AI_PointAtNpc", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC("AI_PointAtNpc", TRUE);
	if (npc1 && npc2) {
		npc1 -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_POINTAT, npc2), npc1);		
	}
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_PointAt()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_PointAt()
{
	zSTRING name;
	zCParser *p	= zCParser :: GetParser();
	p -> GetParameter (name);
	oCNpc* npc1	= PopAndCheckValidNPC("AI_PointAtNpc", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc1)
	{
		DebugOut("... name: " + name, TRUE);
	};
#endif
	
	if (npc1) {
		npc1 -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_POINTAT, name), npc1);		
	}
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_StopPointAt()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_StopPointAt()
{
	zCParser*	p	= zCParser :: GetParser();
	oCNpc*		npc	= PopAndCheckValidNPC("AI_StopPointAt", TRUE);
	if (npc) {
		npc -> GetEM() -> OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_STOPPOINTAT), npc);		
	}
	return FALSE;
}	



// *************************** Ende Konzept V1.41 ********************************

/* ----------------------------------------------------------------------
	
	AI_TakeItem()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_TakeItem()
{
	zCParser *p		= zCParser :: GetParser();

	oCItem* item	= PopAndCheckValidItem("AI_TakeItem", TRUE);
	oCNpc*	npc		= PopAndCheckValidNPC("AI_TakeItem", TRUE);
	if (npc && item) {
		npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)	 (oCMsgMovement  ::EV_GOTOVOB,item),npc);
		npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)	 (oCMsgMovement  ::EV_TURNTOVOB,item),npc);
		npc -> GetEM() -> OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_TAKEVOB,item),npc);
	}
	return TRUE;
}

/*
/* ----------------------------------------------------------------------
	
	AI_TakeVob()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- /

static zBOOL AI_TakeItem()
{
	zCParser *p		= zCParser :: GetParser();

	oCItem* item	= dynamic_cast<oCItem*>((zCVob*)p -> GetInstance ());
	oCNpc*	npc		= dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());
	if (npc && item) {
		npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)	 (oCMsgMovement  ::EV_GOTOVOB,item),npc);
		npc -> GetEM() -> OnMessage(zNEW(oCMsgMovement)	 (oCMsgMovement  ::EV_TURNTOVOB,item),npc);
		npc -> GetEM() -> OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_TAKEVOB,item),npc);
	}
	return TRUE;
}
*/

/* ----------------------------------------------------------------------
	
	AI_DropItem()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_DropItem()
{
	zCParser *p	= zCParser :: GetParser();

	int item_id;
	p->GetParameter (item_id);
	oCNpc*  npc	= PopAndCheckValidNPC("AI_DropItem", TRUE);
	
	if (npc) 
	{
		// Verweis auf variable Item-Instanz ?
		int index = p -> GetIndex("ITEM");
		if (index == item_id) {
			// Variabler Item - Verweise
			zCPar_Symbol* sym	= p -> GetSymbol(index);
			oCItem* item		= (oCItem*)sym->GetInstanceAdr();
			if (item) item_id	= item -> GetInstance();
		}
		oCItem* what = npc -> RemoveFromInv(item_id);
		if (what) 
		{
			if (	what->HasFlag( ITM_FLAG_ACTIVE	) )				// item is equipped
			if (	what->HasFlag( ITM_CAT_NF		)				
				||	what->HasFlag( ITM_CAT_FF		) 
				||	what->HasFlag( ITM_CAT_MUN		)
				||	what->HasFlag( ITM_CAT_RUNE		) )				// item is a weapon
			{
				npc -> GetEM() -> OnMessage(zNEW(oCMsgWeapon)(oCMsgWeapon::EV_REMOVEWEAPON),npc);
			}

			npc -> GetEM() -> OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_DROPVOB,what),npc);
		}
	}
	return TRUE;
}


/* ----------------------------------------------------------------------
	
	AI_UseItem()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_UseItem()
{
	zCParser *p	= zCParser :: GetParser();

	int index;
	p->GetParameter (index);
	oCNpc*  npc	= PopAndCheckValidNPC("AI_UseItem", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		zCPar_Symbol* sym	= p->GetSymbol(index);
		zSTRING			itemName= sym ? sym	-> name : "[UNKNOWN]";
		DebugOut("... item-name: " + itemName, TRUE);
	}
#endif
	if (npc) {
		zCPar_Symbol*	sym		= p		-> GetSymbol(index);
		zSTRING			name	= sym	-> name;
		if (name=="ITEM") {
			// Verweis auf variable Item-Instanz 
			oCItem* item		= dynamic_cast<oCItem*>((zCVob*)sym->GetInstanceAdr());
			if (item) name		= item -> GetInstanceName();
		}
		if (!name.IsEmpty()) {
			oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_USEITEM,name,-1);
			npc -> GetEM() -> OnMessage(msg,npc);
		}
	}
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_UseItemToState()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_UseItemToState()
{
	zCParser *p	= zCParser :: GetParser();

	int index,state;
	p->GetParameter (state);
	p->GetParameter (index);

	oCNpc*  npc	= PopAndCheckValidNPC("AI_UseItemToState", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		zCPar_Symbol *sym	= p-> GetSymbol(index);
		zSTRING			itemName= sym ? sym	-> name : "[UNKNOWN]";
		DebugOut("... item-name: " + itemName, TRUE);
	}
#endif

	if (npc) {
		zCPar_Symbol*	sym		= p		-> GetSymbol(index);
		zSTRING			name	= sym	-> name;
		if (name=="ITEM") {
			// Verweis auf variable Item-Instanz 
			oCItem* item		= dynamic_cast<oCItem*>((zCVob*)sym->GetInstanceAdr());
			if (item) name		= item -> GetInstanceName();
		}
		if (!name.IsEmpty()) {
			oCMsgManipulate* msg = zNEW(oCMsgManipulate)(oCMsgManipulate::EV_USEITEMTOSTATE,name,state);
			npc -> GetEM() -> OnMessage(msg,npc);
		}
	}
	return TRUE;
}

static zBOOL Npc_IsNear()
{
	zBOOL flag = FALSE;
	zCParser *p	= zCParser :: GetParser();
	oCNpc* npc2		= PopAndCheckValidNPC("Npc_IsNear", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC("Npc_IsNear", TRUE);
	
	if ((npc1) && (npc2)) 
	{
		flag = npc1 -> IsNear (npc2);
	}	
	p -> SetReturn  ( flag );
	return FALSE;
}

static zBOOL Npc_IsPlayer()
{
	zCParser *p		= zCParser :: GetParser();
	oCNpc*  npc	= PopAndCheckValidNPC("Npc_IsPlayer", TRUE);
	p -> SetReturn ( npc && npc->IsAPlayer() );
	return FALSE;
}

static zBOOL Npc_CanSeeNpc()
// CanISee ( mit Winkelcheck )
{
	zBOOL canSee	= FALSE;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc2		= PopAndCheckValidNPC("Npc_CanSeeNpc", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC("Npc_CanSeeNpc", TRUE);
	if (npc1 && npc2) canSee = npc1->CanSee(npc2);
	p -> SetReturn ( canSee );
	return FALSE;
}

static zBOOL Npc_CanSeeNpcFreeLOS()
// Nur Free Line of Sight / ohne Winkelcheck
{
	zBOOL canSee	= FALSE;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc2		= PopAndCheckValidNPC("Npc_CanSeeNpcFreeLOS", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC("Npc_CanSeeNpcFreeLOS", TRUE);
	if (npc1 && npc2) canSee = npc1->CanSee(npc2,TRUE);
	p -> SetReturn ( canSee );
	return FALSE;
}

static zBOOL Npc_CanSeeItem()
{
	zBOOL canSee	= FALSE;
	zCParser *p		= zCParser :: GetParser();
	oCItem* item	= PopAndCheckValidItem("Npc_CanSeeItem", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC ("Npc_CanSeeItem", TRUE);
	if (npc1 && item) canSee = npc1->CanSee(item);
	p -> SetReturn ( canSee );
	return FALSE;
}


static zBOOL Npc_GetDistToNpc()
{
	int dist		= INT_MAX;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc2		= PopAndCheckValidNPC("Npc_GetDistToNpc", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC("Npc_GetDistToNpc", TRUE);
//	if (npc1 && npc2) dist = (int) npc1->GetDistanceToVobApprox(*npc2);
	if (npc1 && npc2) dist = (int) npc1->GetDistanceToVob(*npc2);

	p -> SetReturn ( dist );
	return FALSE;	
}

static zBOOL Npc_GetHeightToNpc()
{
	int dist		= INT_MAX;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc2		= PopAndCheckValidNPC("Npc_GetHeightToNpc", TRUE);
	oCNpc* npc1		= PopAndCheckValidNPC("Npc_GetHeightToNpc", TRUE);
	if (npc1 && npc2) dist = (int) zAbs(npc1->GetPositionWorld()[VY]-npc2->GetPositionWorld()[VY]);

	p -> SetReturn ( dist );
	return FALSE;	
}

static zBOOL Npc_GetHeightToItem()
{
	int dist		= INT_MAX;
	zCParser *p		= zCParser :: GetParser();

	oCItem* item	= PopAndCheckValidItem("Npc_GetHeightToItem", TRUE);
	oCNpc*  npc		= PopAndCheckValidNPC("Npc_GetHeightToItem", TRUE);

	if (npc && item) dist = (int) zAbs(npc->GetPositionWorld()[VY]-item->GetPositionWorld()[VY]);

	p -> SetReturn ( dist );
	return FALSE;	
}



static zBOOL Npc_GetDistToWP()
{
	zSTRING wpName;
	int dist		= INT_MAX;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter (wpName);
	oCNpc*  npc1	= PopAndCheckValidNPC("Npc_GetDistToWP", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc1)
	{
		DebugOut("... wp-name: " + wpName, TRUE);
	}
#endif
	if (npc1 && npc1->GetHomeWorld()) {
		zCWaypoint* wp = ogame->GetWorld()->GetWayNet()->GetWaypoint(wpName);
		if (wp) {
			dist	= (int) (npc1->GetPositionWorld()-wp->GetPositionWorld()).LengthApprox();
		} else {
			DebugOut("Npc_GetDistToWP(): Waypoint "+wpName+" not found.", TRUE);
		}
	}
	p -> SetReturn ( dist );
	return FALSE;	
}

static zBOOL Npc_GetDistToItem()
{
	int dist		= INT_MAX;
	zCParser *p		= zCParser :: GetParser();
	oCItem* item	= PopAndCheckValidItem("Npc_GetDistToItem", TRUE);
	oCNpc*  npc1	= PopAndCheckValidNPC("Npc_GetDistToItem", TRUE);
	if (npc1 && item) dist = (int) npc1->GetDistanceToVob(*item);
	p -> SetReturn ( dist );
	return FALSE;	
}

static zBOOL Npc_GetDistToPlayer()
{
	int dist		= INT_MAX;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc1 = PopAndCheckValidNPC("Npc_GetDistToPlayer", TRUE);
	oCNpc* npc2 = ogame->GetSelfPlayerVob();
	if (npc1 && npc2) dist = (int) npc1->GetDistanceToVobApprox(*npc2);
	p -> SetReturn ( dist );
	return FALSE;	
}

static zBOOL Npc_SendPassivePerc()
{
	int percType	= 0;
	zCParser *p		= zCParser :: GetParser();

	oCNpc* other	= PopAndCheckValidNPC("Npc_SendPassivePerc", TRUE);
	oCNpc* victim	= PopAndCheckValidNPC("Npc_SendPassivePerc", TRUE);
	p->GetParameter (percType);
	oCNpc* npc		= PopAndCheckValidNPC("Npc_SendPassivePerc", TRUE);

	if (npc) 
	{
		// SELF		= jeweiliger NPC
		// OTHER	= B�sewicht
		// VICTIM	= Opfer
		SaveParserVars		();
		npc->CreatePassivePerception(percType,other,victim);
		RestoreParserVars	();		
	}
	return FALSE;	
}

static zBOOL Npc_SendSinglePerc()
{
	int percType	= 0;
	zCParser *p		= zCParser :: GetParser();
	p -> GetParameter(percType);
	oCNpc* other = PopAndCheckValidNPC("Npc_SendSinglePerc", TRUE);
	oCNpc* npc	 = PopAndCheckValidNPC("Npc_SendSinglePerc", TRUE);
	
	if (npc && other) 
	{
		
		SaveParserVars();
		parser.SetInstance("SELF"	,other);
		parser.SetInstance("OTHER"	,npc);
		int func =		other -> GetPerceptionFunc	 (percType);	// b) Wahrnehmung relevant ?
		if (func>=0)	other -> state .StartAIState (func,FALSE,AITIME_NO,0.0f);	
		RestoreParserVars();

	}
	return FALSE;	
}

static zBOOL Npc_GetBodyState()
{
	int bodyState	= 0;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* npc = PopAndCheckValidNPC("Npc_GetBodyState", TRUE);
	if (npc) 
	{
		bodyState = npc->GetFullBodyState();
	}
	p->SetReturn(bodyState);
	return FALSE;
}

static zBOOL Npc_HasBodyFlag()
{
	zBOOL	flag	= FALSE;
	int		bodyFlag= 0;
	zCParser *p		= zCParser :: GetParser();
	p -> GetParameter(bodyFlag);
	oCNpc* npc = PopAndCheckValidNPC("Npc_HasBodyFlag", TRUE);
	if (npc) 
	{
		flag = ((npc->GetFullBodyState() & bodyFlag)>0);
	}
	p->SetReturn(flag);
	return FALSE;
}

static zBOOL Npc_GetComrades()
{
	zCParser*	p		= zCParser :: GetParser();
	oCNpc* npc = PopAndCheckValidNPC("Npc_GetComrades", TRUE);
	int			count	= 0;
	if (npc) {
		count = npc->GetComrades();
	}
	p->SetReturn(count);
	return FALSE;
}

// ************************************************************************************
//  News 
// ************************************************************************************

static zBOOL Npc_HasNews()
{
	int newsID, newsNumber = 0;
	zCParser*	p	= zCParser :: GetParser();

	oCNpc* victim	= PopAndCheckValidNPC("Npc_HasNews", FALSE);
	oCNpc* offender = PopAndCheckValidNPC("Npc_HasNews", FALSE);
	p->GetParameter (newsID);
	oCNpc* npc		= PopAndCheckValidNPC("Npc_HasNews", FALSE);

#ifdef CHECK_SCRIPT_PARANOID
	if (!victim || !offender || !npc)
	{
		DebugOut("... newsID: " +zSTRING(newsID), TRUE);
	}
#endif

	if (npc) {
		newsNumber	= npc->GetNewsMemory()->SearchNews(newsID,offender,victim);
	}
	p->SetReturn(newsNumber);
	return FALSE;
};

static zBOOL Npc_GetNewsWitness()
{
	int newsNumber, newsID;
	oCNpc*	witness		= NULL;
	oCNpc*	offender	= NULL;
	oCNpc*	victim		= NULL;
	zBOOL	gossip		= FALSE;

	zCParser* p		= zCParser :: GetParser();
	p->GetParameter (newsNumber);
	oCNpc* npc = PopAndCheckValidNPC("Npc_GetNewsWitness", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... newsnumber: " + zSTRING(newsNumber), TRUE);
	}
#endif

	if (npc) {
		oCNews* news = npc->GetNewsMemory()->GetNewsByNumber(newsNumber);
	if (news) news->GetNewsData(newsID,gossip,witness,offender,victim);
	}
	p->SetReturn(witness);
	return FALSE;
};

static zBOOL Npc_GetNewsOffender()
{
	int newsNumber, newsID;
	oCNpc*	witness		= NULL;
	oCNpc*	offender	= NULL;
	oCNpc*	victim		= NULL;
	zBOOL	gossip		= FALSE;

	zCParser* p		= zCParser :: GetParser();
	p->GetParameter (newsNumber);
	oCNpc* npc = PopAndCheckValidNPC("Npc_GetNewsOffender", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... newsnumber: " + zSTRING(newsNumber), TRUE);
	}
#endif
	if (npc) {
		oCNews* news = npc->GetNewsMemory()->GetNewsByNumber(newsNumber);
		if (news) news->GetNewsData(newsID,gossip,witness,offender,victim);
	}
	p->SetReturn(offender);
	return FALSE;
};

static zBOOL Npc_GetNewsVictim()
{
	int newsNumber, newsID;
	oCNpc*	witness		= NULL;
	oCNpc*	offender	= NULL;
	oCNpc*	victim		= NULL;
	zBOOL	gossip		= FALSE;

	zCParser* p		= zCParser :: GetParser();
	p->GetParameter (newsNumber);

	oCNpc* npc = PopAndCheckValidNPC("Npc_GetNewsVictim", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... newsnumber: " + zSTRING(newsNumber), TRUE);
	}
#endif

	if (npc) {
		oCNews* news = npc->GetNewsMemory()->GetNewsByNumber(newsNumber);
		if (news) news->GetNewsData(newsID,gossip,witness,offender,victim);
	}
	p->SetReturn(victim);
	return FALSE;
};

static zBOOL Npc_IsNewsGossip()
{
	int newsNumber, newsID;
	oCNpc*	witness		= NULL;
	oCNpc*	offender	= NULL;
	oCNpc*	victim		= NULL;
	zBOOL	gossip		= FALSE;

	zCParser* p		= zCParser :: GetParser();
	p->GetParameter (newsNumber);
	oCNpc* npc = PopAndCheckValidNPC("Npc_IsNewsGossip", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... newsnumber: " + zSTRING(newsNumber), TRUE);
	}
#endif
	if (npc) {
		oCNews* news = npc->GetNewsMemory()->GetNewsByNumber(newsNumber);
		if (news) news->GetNewsData(newsID,gossip,witness,offender,victim);
	}
	p->SetReturn(gossip);
	return FALSE;
};

static zBOOL Npc_DeleteNews()
{
	int		newsNumber = 0;
	zBOOL	success	= FALSE;
	
	zCParser* p		= zCParser :: GetParser();
	p->GetParameter (newsNumber);
	oCNpc* npc = PopAndCheckValidNPC("Npc_DeleteNews", TRUE);
	if (npc) {
		success		= npc->GetNewsMemory()->DeleteNewsByNumber(newsNumber);
	}
	p->SetReturn(success);
	return FALSE;
};

/* ----------------------------------------------------------------------
	
	AI_StandUp()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_StandUp()
{
	zCParser*	p	= zCParser :: GetParser();
	oCNpc* npc = PopAndCheckValidNPC("AI_StandUp", TRUE);
	if (npc) {
		oCMsgMovement* msg	= zNEW(oCMsgMovement)(oCMsgMovement::EV_STANDUP,0);
		msg->targetMode		= 1;	// StartAniTransition on
		npc->GetEM()->OnMessage(msg,npc);
	}	
	return TRUE;
}

static zBOOL AI_StandUpQuick()
{
	zCParser*	p	= zCParser :: GetParser();
	oCNpc* npc = PopAndCheckValidNPC("AI_StandUpQuick", TRUE);
	
	if (npc) 
	{
		oCMsgMovement* msg	= zNEW(oCMsgMovement)(oCMsgMovement::EV_STANDUP,0);
		msg->targetMode		= 0;	// StartAniTransition off
		npc->GetEM()->OnMessage(msg,npc);
	}	
	return TRUE;
}

//
//	CODECHANGE [ROMAN]
//

/* ----------------------------------------------------------------------
	
	AI_Defend()

	07.09.2000	[Keskenti]

					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL AI_Defend()
{
	zCParser*	p = zCParser :: GetParser();

	oCNpc* defender = PopAndCheckValidNPC("AI_Defenc", TRUE);
	//
	//	MUTUAL EXCLUSION FOR DEFEND-MESSAGES
	//
	oCMsgAttack* pMsgAttack	= NULL;

	for ( int nMessage = 0; nMessage < defender->GetEM()->GetNumMessages(); nMessage++ ) 
	{
		pMsgAttack = dynamic_cast<oCMsgAttack*> (defender->GetEM()->GetEventMessage( nMessage ));
		if ( pMsgAttack ) 
		{
			if ( pMsgAttack->GetSubType() == oCMsgAttack::EV_DEFEND ) 
			{
				return FALSE;
			}
		}
	}

	//
	//	SEND MESSAGE
	//
	oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_DEFEND, NULL );
	defender->GetEM()->OnMessage( pMsg , defender );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_Flee()

	07.09.2000	[Keskenti]

					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL AI_Flee()
{
	zCParser*	p= zCParser :: GetParser();

	oCNpc* npcSelf = PopAndCheckValidNPC("AI_Flee", TRUE);
	if (npcSelf) {
		if (npcSelf->GetEM()->IsEmpty(TRUE)) npcSelf->Fleeing();
	}	
	return TRUE;	
}

/* ----------------------------------------------------------------------
	
	AI_AimAt()

	25.08.2000	[Moos]	

				auf zNEW umgestellt

				[Keskenti]

					ANNOTATION:	By now, only aiming at NPCs is possible.
					ANNOTATION:	NPC has got to be in its standing state.

   ---------------------------------------------------------------------- */

static zBOOL AI_AimAt()
{
	zCParser*	p = zCParser :: GetParser();

	oCNpc* target	= PopAndCheckValidNPC("AI_AimAt", TRUE);
	oCNpc* attacker = PopAndCheckValidNPC("AI_AimAt", TRUE);

	oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_AIMAT, target );
	attacker->GetEM()->OnMessage( pMsg , attacker );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_StopAim()

	25.08.2000	[Keskenti]

					Initial implementation

   ---------------------------------------------------------------------- */

static zBOOL AI_StopAim()
{
	zCParser*	p = zCParser :: GetParser();
	oCNpc* attacker = PopAndCheckValidNPC("AI_StopAim", TRUE);
	oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_STOPAIM, NULL );
	attacker->GetEM()->OnMessage( pMsg , attacker );

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_ShootAt()

	25.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_ShootAt()
{
	zCParser*	p = zCParser :: GetParser();


	oCNpc* target	= PopAndCheckValidNPC("AI_ShootAt", TRUE);
	oCNpc* attacker = PopAndCheckValidNPC("AI_ShootAt", TRUE);

	oCMsgAttack* pMsg = zNEW(oCMsgAttack)( oCMsgAttack::EV_SHOOTAT, target );
	attacker->GetEM()->OnMessage( pMsg , attacker );

	return FALSE;
}
//
//	CODECHANGE [ROMAN]
//

static zBOOL AI_Attack()
{
	zCParser*	p	= zCParser :: GetParser();

	oCNpc* npc = PopAndCheckValidNPC("AI_Attack", TRUE);
	if (npc) 
	{
		if ( npc->GetEM()->IsEmpty(TRUE) ) 
		{
			npc->Fighting();
		}
		//else zERR_WARNING("C: could not execute AI_Attack for npc: " + npc->GetName() + ", because there is still a command waiting in his AI-Queue");
		//oCMsgWeapon* msg = new oCMsgWeapon(oCMsgWeapon::EV_ATTACK,0);
		//npc->GetEM()->OnMessage(msg,npc);
	}	
	return TRUE;	
};

/* ----------------------------------------------------------------------
	
	AI_CombatReactToDamage()

	13.09.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL AI_CombatReactToDamage()
{
	return TRUE;	
}

/* ----------------------------------------------------------------------
	
	AI_ReadySpell()

	28.09.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL AI_ReadySpell()
{
	zCParser*	p	= zCParser :: GetParser();

	int			nMana	; p->GetParameter( nMana  );
	int			nSpell	; p->GetParameter( nSpell );
	oCNpc* npcSelf = PopAndCheckValidNPC("AI_ReadySpell", TRUE);
	if ( npcSelf ) 
	{
		oCMsgMagic* pMsg = zNEW(oCMsgMagic)(oCMsgMagic::EV_READY );
		pMsg->activeSpell  = nSpell;
		pMsg->manaInvested = nMana ;
		npcSelf->GetEM()->OnMessage( pMsg, npcSelf );
	}	

	return TRUE;	
}

/* ----------------------------------------------------------------------
	
	AI_UnreadySpell()

	28.09.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL AI_UnreadySpell()
{
	zCParser*	p= zCParser :: GetParser();

	oCNpc* npcSelf = PopAndCheckValidNPC("AI_UnreadySpell", TRUE);

	if ( npcSelf ) {
		oCMsgMagic* pMsg = zNEW(oCMsgMagic)(oCMsgMagic::EV_UNREADY );
		npcSelf->GetEM()->OnMessage( pMsg, npcSelf );
	}	

	return TRUE;	
}

/* ----------------------------------------------------------------------
	
	Npc_HasSpell()

	13.09.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */
static zBOOL Npc_HasSpell()
{
	zCParser*	p	= zCParser :: GetParser();

	int			nSpell	; p->GetParameter( nSpell );
	oCNpc* npcSelf = PopAndCheckValidNPC("Npc_HasSpell", TRUE);

	if ( npcSelf ) 
	{
		zBOOL bHasSpell = ( npcSelf->GetSpellItem( nSpell ) != NULL );
		p->SetReturn( bHasSpell );
	}	

	return TRUE;	
}

/* ----------------------------------------------------------------------
	
	AI_FinishingMove()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_FinishingMove()
{
	zCParser*	p		= zCParser :: GetParser();

	oCNpc* other	= PopAndCheckValidNPC("AI_FinishingMove", TRUE);
	oCNpc* npc		= PopAndCheckValidNPC("AI_FinishingMove", TRUE);
	
	if (npc && other && npc->GetAnictrl() && npc->GetModel()) 
	{
		zSTRING	s			= npc->GetAnictrl()->GetWeaponHitString(npc->GetWeaponMode());
		zTModelAniID ani	= npc->GetModel()  ->GetAniIDFromAniName("T_"+s+"FINISH");
		oCMsgAttack* msg	= zNEW(oCMsgAttack)(oCMsgAttack::EV_ATTACKFINISH,ani);
		msg->target			= other;
		npc->GetEM()->OnMessage(msg,npc);
	}
	return TRUE;
};

/* ----------------------------------------------------------------------
	
	AI_Dodge()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_Dodge()
{
	zCParser*	p		= zCParser :: GetParser();
	oCNpc* npc = PopAndCheckValidNPC("AI_Dodge", TRUE);

	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_DODGE,0),npc);
	}
	return TRUE;
};

// ****************************************************************************************
// Mobsis
// ****************************************************************************************

/* ----------------------------------------------------------------------
	
	Wld_IsMobAvailable()

	02.10.2000	[Roman Keskenti]	

					Added the actual availablity check 

   ---------------------------------------------------------------------- */

static zBOOL Wld_IsMobAvailable()
{
	zSTRING mobName;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter	(mobName); mobName.Upper();
	oCNpc* npc = PopAndCheckValidNPC("Wld_IsMobAvailable", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... mobName: " + mobName, TRUE);
	}
#endif

	//
	//	CODECHANGE [ROMAN]
	//
	zBOOL bIsAvailable = FALSE;

	if ( npc )												// gibt es den NPC ?
	{
		oCMobInter*	mob = npc ->FindMobInter(mobName);		
		if ( mob )											// ist der NPC in der Naehe des Mobs ?
		{
			if ( mob->IsAvailable( npc ) )					// kann er NPC das Mob verwenden ?
				bIsAvailable = TRUE;
		}
	}
	p->SetReturn( bIsAvailable );
	//
	//	CODECHANGE [ROMAN] END
	//

	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_MobInteract()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_MobInteract()
{
	zVEC3 targetPos;
	oCMobInter* mob = NULL;
	zSTRING mobSchemeName;
	int targetState;
	
	zCParser *p = zCParser::GetParser();
	p -> GetParameter (targetState);
	p -> GetParameter (mobSchemeName);
	oCNpc* npc = PopAndCheckValidNPC("AI_MobInteract", FALSE);

#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... mobSchemeName: " + mobSchemeName, TRUE);
	}
#endif

	if (npc) {
		// Benutzen
		npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_USEMOB,mobSchemeName, targetState),NULL);
	}
	p -> SetReturn(mob!=NULL);
	return TRUE;
}

/* ----------------------------------------------------------------------
	
	AI_TakeMob()

	20.09.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */

static zBOOL AI_TakeMob()
{
	zSTRING mobSchemeName;

	zCParser *p = zCParser::GetParser();
	p -> GetParameter (mobSchemeName);
	oCNpc* npc = PopAndCheckValidNPC("AI_TakeMob", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... mobSchemeName: " + mobSchemeName, TRUE);
	}
#endif
	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_TAKEMOB, mobSchemeName, 0),NULL);
	}

	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_DropMob()

	06.10.2000	[Roman Keskenti]	

					Initial implementation

   ---------------------------------------------------------------------- */

static zBOOL AI_DropMob()
{
	zSTRING mobSchemeName;

	zCParser *p = zCParser::GetParser();
	oCNpc* npc = PopAndCheckValidNPC("AI_DropMob", TRUE);

	if (npc) {
		npc->GetEM()->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_DROPMOB, "", 0),NULL);
	}

	return FALSE;
}

static zBOOL Mob_CreateItems()
{
	zSTRING vobName;
	int instance,amount;
	
	zCParser *p = zCParser::GetParser();
	p -> GetParameter (amount	);
	p -> GetParameter (instance	);
	p -> GetParameter (vobName	);
	oCMobContainer* mob = dynamic_cast<oCMobContainer*>(ogame -> GetWorld() ->SearchVobByName(vobName));
	if (mob) {
		oCItem* item;
		for (int i=0; i<amount; i++) {
			item	= dynamic_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM,instance));
			if (item) 
			{
				mob	-> Insert(item);
				if (item -> MultiSlot()) {
					item -> SetAmount ( amount );
					break;
				}
				zRELEASE(item);
			}
#ifdef CHECK_SCRIPT_PARANOID
			else 
			{
				zCPar_Symbol* sym = p->GetSymbol(instance);
				if (!sym) 	DebugOut("Mob_CreateItems() : No instance found, mobName: "+vobName + ", illegal instance" , TRUE);
				else		DebugOut("Mob_CreateItems() : No instance found, mobName: "+vobName + ", instance-name:" + sym->name, TRUE );
			}
#endif
		}

	} else 
		DebugOut("Mob_CreateItems() : No Mob found with specified Vobname : "+vobName, TRUE);
	
	return FALSE;
}

static zBOOL Mob_HasItems()
{
	zSTRING vobName;
	int instance,amount = 0;
	
	zCParser *p = zCParser::GetParser();
	p -> GetParameter (instance	);
	p -> GetParameter (vobName	);
	oCMobInter* mob = dynamic_cast<oCMobInter*>(ogame -> GetWorld() ->SearchVobByName(vobName));
	if (mob) {
		amount = mob->IsIn(instance);
	} else 
		DebugOut("Mob_HasItems() : No Mob found with specified Vobname : "+vobName, TRUE);

	p->SetReturn(amount);
	return FALSE;
}

// ****************************************************************************************
// Dialog 
// ****************************************************************************************

static zBOOL Npc_CanTalk()
{
	zBOOL refuse	= FALSE;
	zCParser *p		= zCParser :: GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_CanTalk", TRUE);
	if (self) refuse= !self->CanTalk();
	p -> SetReturn(refuse);
	return FALSE;
}

static zBOOL Npc_SetCanTalk()
{
	int timeSec		= 0;
	zCParser *p		= zCParser :: GetParser();
	p->GetParameter (timeSec);
	oCNpc* self = PopAndCheckValidNPC("Npc_SetCanTalk", TRUE);
	if (self) self -> SetCanTalk(timeSec);
	return FALSE;
}

/* ----------------------------------------------------------------------
	
	AI_Ask()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_Ask()
{
	int f_no, f_yes;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter (f_no);
	p -> GetParameter (f_yes);
	oCNpc* self = PopAndCheckValidNPC("AI_Ask", TRUE);
	// Schnackt immer den Spieler an.
	if (self) {
		oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_ASK,f_yes,f_no,20*1000);
		msg->name="Nein";
		msg->text="Ja";
		self -> GetEM() ->OnMessage(msg,self);
	}
	return TRUE;
}

//
//	CODECHANGE [ROMAN]
//

/* ----------------------------------------------------------------------
	
	AI_AskText()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_AskText()
{
	int f_no, f_yes;
	zSTRING s, strYes, strNo;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter (strNo);
	p -> GetParameter (strYes);
	p -> GetParameter (f_no);
	p -> GetParameter (f_yes);
	oCNpc* self = PopAndCheckValidNPC("AI_AskText", TRUE);
	// Schnackt immer den Spieler an.
	if (self) {
		oCMsgConversation* msg = zNEW(oCMsgConversation)(oCMsgConversation::EV_ASK,f_yes,f_no,20*1000);
		msg->name=strNo;
		msg->text=strYes;
		self -> GetEM() ->OnMessage(msg,self);
	}
	return TRUE;
}
//
//	CODECHANGE [ROMAN] END
//

/* ----------------------------------------------------------------------
	
	AI_WaitForQuestion()

	24.08.2000	[Moos]	

				auf zNEW umgestellt

   ---------------------------------------------------------------------- */

static zBOOL AI_WaitForQuestion()
{
	int f_yes;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter (f_yes);

	oCNpc* self = PopAndCheckValidNPC("AI_WaitForQuestion", TRUE);
	// Schnackt immer den Spieler an.
	if (self) {
		self -> GetEM() ->OnMessage(zNEW(oCMsgConversation)(oCMsgConversation::EV_WAITFORQUESTION,f_yes,f_yes,20*1000),self);
	}
	return TRUE;
}

// ****************************************************************************************
// Items 
// ****************************************************************************************

static zBOOL Hlp_IsItem()
{
	zBOOL	identical = FALSE;
	int		index;
	oCItem*	item;
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(index);
	item = PopAndCheckValidItem("Hlp_IsItem", TRUE);
	if (item) identical = (item->GetInstance()==index);
	p->SetReturn(identical);
	return FALSE;
}

static zBOOL Hlp_GetInstanceID()
{
	zCParser*	p		= zCParser :: GetParser	();
#ifdef CHECK_SCRIPT_VERY_PARANOID
	int selfIndex;
	zCVob* vob = (zCVob*)p -> GetInstanceAndIndex (selfIndex);
	if (!vob)
	{
		zCPar_Symbol*sym = p->GetSymbol(selfIndex);
		zSTRING npcName			= sym ? sym->name : "[UNKNOWN]";
		DebugOut("Hlp_GetInstanceID(): illegal id:" + npcName, TRUE);
	}
#else
	zCVob*		vob		= (zCVob*)p->GetInstance();
#endif
	zSTRING*	insName	= NULL;
	int		insNr		= -1;
	if (vob) vob->GetScriptInstance	(insName,insNr);

	p->SetReturn (insNr);
	return FALSE;
}

static zBOOL Hlp_Random()
{
	int value;
	int rnd;
	zCParser *p = zCParser :: GetParser();
	p->GetParameter(value);
	rnd = zRand() % value;
	// zERR_MESSAGE(1,0,"S: Random " + zSTRING(rnd));
	p->SetReturn(rnd);
	return FALSE;
}

// ****************************************************************************************
// Magic 
// ****************************************************************************************

static zBOOL Npc_CreateSpell()
//EXTERN FUNC VOID CreateSpell		(VAR INT id, VAR INT level, VAR INT mana, VAR INT invest, VAR FUNCREF func );
{
	int nr;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(nr);
	oCNpc* npc = PopAndCheckValidNPC("Npc_CreateSpell", TRUE);
	if (npc) npc -> CreateSpell (nr);
	return FALSE;
}

// ****************************************************************************************
// Missions 
// ****************************************************************************************

static zBOOL Npc_CheckAvailableMission()
// IsAvailableMission ( self, state )
{
	zBOOL important = FALSE;
	int state;
	oCMission* mission = NULL;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(important);
	p -> GetParameter(state);
	oCNpc* npc = PopAndCheckValidNPC("Npc_CheckAvailableMissions", TRUE);
	if (npc) 
	{
		// Missionsstatus kann sein
		// a) MIS_NOTINVOLVED, aber Kriterien erf�llt
		// b) MIS_RUNNING, Mission l�uft
		// c) MIS_OFFERED, Mission wurde angeboten
		mission = misMan.GetAvailableMission(npc,ogame->GetSelfPlayerVob(),important);
#ifdef CHECK_SCRIPT_PARANOID
		if (!mission)
		{
			DebugOut("Npc_CheckAvailableMission(): illegal mission: nsc-name: " + npc->GetName(), TRUE);
		};
#endif
	}
	p->SetReturn (mission && (mission->GetStatus() == state));
	return FALSE;
}

static zBOOL Npc_IsDrawingWeapon()
{

	zBOOL		weaponSelect		= FALSE;
	zCParser *p = zCParser::GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_IsDrawingWeapon", TRUE);

	oCMsgWeapon *pMsgWeaponCurrent	= NULL;
	oCMsgMagic*  pMsgMagic			= NULL;

	int		 	 nMessages			= self->GetEM()->GetNumMessages();
	int		 	 nMessage			= 0;

	for ( ; nMessage < nMessages; nMessage ++ ) 
	{
		pMsgWeaponCurrent = zDYNAMIC_CAST< oCMsgWeapon > ( self->GetEM()->GetEventMessage( nMessage ) );
		pMsgMagic		  = zDYNAMIC_CAST< oCMsgMagic  > ( self->GetEM()->GetEventMessage( nMessage ) );

		if ( pMsgWeaponCurrent )														
		{
			if ( pMsgWeaponCurrent->GetSubType() < oCMsgWeapon::EV_REMOVEWEAPON)		
			{
				weaponSelect = TRUE;
				break;
			}
		}
		else if (pMsgMagic)
		{
			if ( pMsgMagic->GetSubType() == oCMsgMagic::EV_READY )		
			{
				weaponSelect = TRUE;
				break;
			}
		};
	};
	p->SetReturn(weaponSelect);
	return FALSE;

};


static zBOOL Npc_IsDrawingSpell()
{

	int spellDrawn	= -1;

	zCParser *p = zCParser::GetParser();
	oCNpc* self = PopAndCheckValidNPC("Npc_IsDrawingSpell", TRUE);
	if (self)
	{
//		oCMsgWeapon *pMsgWeaponCurrent	= NULL;
		oCMsgMagic*  pMsgMagic			= NULL;

		int		 	 nMessages			= self->GetEM()->GetNumMessages();
		int		 	 nMessage			= 0;

		for ( ; nMessage < nMessages; nMessage ++ ) 
		{
			pMsgMagic		  = zDYNAMIC_CAST< oCMsgMagic  > ( self->GetEM()->GetEventMessage( nMessage ) );

			if (pMsgMagic)
			{
				if ( pMsgMagic->GetSubType() == oCMsgMagic::EV_READY )		
				{
					spellDrawn = pMsgMagic->activeSpell;
					break;
				}
			};
		};
	};
	p->SetReturn(spellDrawn);
	return FALSE;

};


static zBOOL Npc_CheckRunningMission()
{
	zBOOL important		= FALSE;
	zBOOL exec			= FALSE;
	oCMission* mission	= NULL;
	zCParser *	p		= zCParser :: GetParser();
	p->GetParameter		(important);
	oCNpc* npc = PopAndCheckValidNPC("Npc_CheckRunningMission", TRUE);
	if (npc) 
	{
		mission = misMan.GetAvailableMission(npc,ogame->GetSelfPlayerVob(),important);
		if (mission && mission->GetStatus()!=MIS_NOTINVOLVED) {
			exec = mission->CheckMission();
		}
#ifdef CHECK_SCRIPT_PARANOID
		else if (!mission)
		{
			DebugOut("Npc_CheckRunningMission(): illegal mission: nsc-name: " + npc->GetName(), TRUE);
		};
#endif

	}
	p->SetReturn(exec);
	return FALSE;
}

static zBOOL Npc_CheckOfferMission()
{
	zBOOL important		= FALSE;
	zBOOL exec			= FALSE;
	oCMission* mission	= NULL;
	zCParser *p			= zCParser :: GetParser();
	p -> GetParameter(important);
	oCNpc* npc = PopAndCheckValidNPC("Npc_CheckOfferMission", TRUE);
	if (npc) 
	{
		mission = misMan.GetAvailableMission(npc,ogame->GetSelfPlayerVob(),important);
		if (mission && mission->GetStatus()==MIS_NOTINVOLVED) 
		{
			// Bedingungen hier bereits gecheckt.
			mission->Offer();
			exec = TRUE;
		}
#ifdef CHECK_SCRIPT_PARANOID
		else if (!mission)
		{
			DebugOut("Npc_CheckOfferMission(): illegal mission: nsc-name: " + npc->GetName(), TRUE);
		};
#endif
	}
	p->SetReturn(exec);
	return FALSE;
}

static zBOOL Mis_GetStatus()
{
	int nr;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(nr);
	int status = misMan.GetStatus(oCNpc::player,nr);
#ifdef CHECK_SCRIPT_PARANOID
	if (status == MIS_NOMISSION) DebugOut("Mis_GetStatus() failed for nr: " + zSTRING(nr), TRUE);
#endif
	p -> SetReturn (status);
	return FALSE;
}

static zBOOL Mis_SetStatus()
{
	int instance,status;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter	(status);
	p -> GetParameter	(instance);
	misMan.SetStatus	(oCNpc::player,instance,status);
	return FALSE;
}

static zBOOL Mis_OnTime()
{
	int instance;
	zBOOL ontime = FALSE;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter (instance);
	oCMission* mission = misMan.GetMission(instance);
	if (mission) 
	{
		// FIXME : Ist das ok so ?
		mission->SetCurrentUser(NULL,oCNpc::player);
		ontime = mission->OnTime();
	}
#ifdef CHECK_SCRIPT_PARANOID
	else
	{
		zCPar_Symbol *sym = p->GetSymbol(instance);
		if (!sym) DebugOut("Mis_OnTime(): illegal mission instance!", TRUE);
		else	  DebugOut("Mis_OnTime(): could not get mission for instance: " + sym->name, TRUE);
	};
#endif
	p->SetReturn(ontime);
	return FALSE;
}

// ****************************************************************************************
// Sound
// ****************************************************************************************

static zBOOL Ext_SndPlay()
{
	zSTRING s;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(s);
	Game_PlaySound(s);
	return FALSE;
}

static zBOOL Ext_SndPlay3d()
{
	zSTRING s;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(s);
#ifdef CHECK_SCRIPT_PARANOID
	int selfIndex;
	zCVob *v = (zCVob*)p -> GetInstanceAndIndex(selfIndex);
	if (!v)
	{
		zCPar_Symbol*sym = p->GetSymbol(selfIndex);
		zSTRING npcName			= sym ? sym->name : "[UNKNOWN]";
		DebugOut("Snd_Play(): illegal params: vob-name: " + npcName + ", sndName: " + s, TRUE);
	}
#else
	zCVob *v = (zCVob*)p -> GetInstance();
#endif

	zCSoundFX* snd = zsound->LoadSoundFXScript(s);
	if (snd!=NULL) zsound->PlaySound3D(snd,v);
	zRELEASE(snd);
	return FALSE;
}

// [EDENFELD] neu 1.09
static zBOOL AI_Snd_Play()	// AI_SndPlay(self, "sound.wav")
{
	zCParser *p  = zCParser::GetParser();
	
	zSTRING		s;
	oCNpc		*npc = NULL;

	p->GetParameter(s);

	npc = PopAndCheckValidNPC("AI_Snd_Play", FALSE);

#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... sndName: " + s, TRUE);
	}
#endif
	
	if (npc)
	{
		oCMsgConversation* pMsg = zNEW( oCMsgConversation ) ( oCMsgConversation::EV_SNDPLAY, s);	
		pMsg->f_yes = FALSE;	// FLag as no 3D
		npc->GetEM()->OnMessage( pMsg, npc);
	}
	return FALSE;
}

static zBOOL AI_Snd_Play3D()	// AI_SndPlay3D(self, emitter, "sound.wav")
{
	zCParser	*p = zCParser::GetParser();

	zSTRING		s;	
	zCVob		*emitter	= NULL;
	oCNpc		*npc		= NULL;
	
	p->GetParameter(s);
#ifdef CHECK_SCRIPT_PARANOID
	int emitterIndex;
	emitter = (zCVob*)p->GetInstanceAndIndex(emitterIndex);	
	npc		= PopAndCheckValidNPC("AI_Snd_Play3D", FALSE);

	if (!npc || !emitter)
	{
		zCPar_Symbol*sym = p->GetSymbol(emitterIndex);
		zSTRING emitterName		= sym ? sym->name : "[UNKNOWN]";
		DebugOut(" ...emitterName: " + emitterName, TRUE);
	}
#else
	emitter = (zCVob*)p->GetInstance();	
	npc = dynamic_cast<oCNpc*>((zCVob*)p -> GetInstance ());
#endif
	if (npc && emitter)
	{
		oCMsgConversation* pMsg = zNEW( oCMsgConversation ) ( oCMsgConversation::EV_SNDPLAY, s);	
		pMsg->f_yes		= TRUE;		// FLag as 3D-Sound
		pMsg->target	= emitter;
		npc->GetEM()->OnMessage( pMsg, npc);
	}
	return FALSE;
}


// ****************************************************************************
// Logical Sound
// ****************************************************************************

static zBOOL Snd_GetDistToSource()
{
	int dist	= INT_MAX;
	zCParser *p = zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Snd_GetDistToSource", TRUE);
	if (npc) dist = (int)npc->GetDistToSound();
	p -> SetReturn(dist);
	return FALSE;
};

static zBOOL Snd_IsSourceNpc()
{
	oCNpc*		other	= NULL;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Snd_IsSourceNpc", TRUE);
	if (npc)	other	= dynamic_cast<oCNpc*>(npc->GetSoundSource());
	p->SetInstance	("OTHER",other);
	p->SetReturn	(other!=NULL);
	return FALSE;
};

static zBOOL Snd_IsSourceItem()
{
	oCItem*		item	= NULL;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Snd_IsSourceItem", TRUE);
	if (npc)	item	= dynamic_cast<oCItem*>(npc->GetSoundSource());
	p->SetInstance	("ITEM",item);
	p->SetReturn	(item!=NULL);
	return FALSE;
};

static zBOOL Npc_CanSeeSource()
{
	zBOOL		see		= FALSE;
	zCParser*	p		= zCParser :: GetParser();
	oCNpc* npc	= PopAndCheckValidNPC("Npc_CanSeeSource", TRUE);
	if (npc) {
		if (npc->GetSoundSource()) see = npc->CanSee(npc->GetSoundSource());
		// FIXME : Hier noch Check, falls nur Position bekannt
		// else					see = npc->CanS
	}
	p -> SetReturn(see);
	return FALSE;
}


// ****************************************************************************************
// Models
// ****************************************************************************************

static zBOOL Mdl_SetVisual()
{
	zSTRING s;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(s);
	oCNpc* npc	= PopAndCheckValidNPC("Npc_CanSeeSource", FALSE);

#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... visual: " + s, TRUE);
	};
#endif
	if (npc) {
//		npc -> zCVob::SetVisual(s);
		npc -> SetMdsName(s);
	}
	return FALSE;
}

static zBOOL Mdl_SetVisualBody()
{
	zSTRING body,head;
	int		bodyTexNr,bodyTexColor,headTexNr,teethTexNr,armorInstance;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(armorInstance);
	p -> GetParameter(teethTexNr);
	p -> GetParameter(headTexNr);
	p -> GetParameter(head);
	p -> GetParameter(bodyTexColor);
	p -> GetParameter(bodyTexNr);
	p -> GetParameter(body);
	oCNpc* npc	= PopAndCheckValidNPC("Mdl_SetVisualBody", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		zCPar_Symbol* sym = parser.GetSymbol(armorInstance);
		if (sym) DebugOut("... armor: " + sym->name , TRUE);
		else	 DebugOut("... armor: [UNKNOWN]" , TRUE);
	};
#endif
	if (npc) {
		// Set Visuals -> Formerly set by Scriptvars
		npc -> SetAdditionalVisuals(body,bodyTexNr,bodyTexColor,head,headTexNr,teethTexNr,armorInstance);
	}
	return FALSE;
}

static zBOOL Mdl_ApplyOverlayMds()
{
	zSTRING s;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(s);

	oCNpc* npc	= PopAndCheckValidNPC("Mdl_ApplyOverlayMds", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... ani: " + s, TRUE);
	};
#endif

	if (npc) 
	{
		                            npc -> ApplyOverlay(s);
		if (npc -> GetAnictrl())	npc -> GetAnictrl() -> InitAnimations();
	}
	return FALSE;
}

/*--------------------------------------------------------------------------

    Mdl_ApplyOverlayMdsTimed()

 

    03-Oct-00       [Roman Keskenti]

                      Initial implementation


--------------------------------------------------------------------------*/ 
static zBOOL Mdl_ApplyOverlayMdsTimed()
{
	zSTRING			strOverlay	;
	int				nTicks		;
	oCNpc*			npcSelf		;
	zCParser*		p		= zCParser :: GetParser();

	p -> GetParameter( nTicks		);
	p -> GetParameter( strOverlay );

	npcSelf	= PopAndCheckValidNPC("Mdl_ApplyOverlayMdsTimed", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npcSelf)
	{
		DebugOut("... overlay: " + strOverlay, TRUE);
	};
#endif

	if ( npcSelf ) 
	{
		npcSelf->ApplyTimedOverlayMds(strOverlay,nTicks);
	}

	return FALSE;
}

static zBOOL Mdl_RemoveOverlayMds()
{
	zSTRING s;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(s);
	oCNpc* npc	= PopAndCheckValidNPC("Mdl_RemoveOverlayMds", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... overlay: " + s, TRUE);
	};
#endif

	if (npc) 
	{
		npc -> RemoveOverlay(s);
		if (npc -> GetAnictrl()) npc -> GetAnictrl() -> InitAnimations();
	}
	return FALSE;
}

static zBOOL Mdl_ApplyRandomAni()
{
	zSTRING sani,sran;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(sran); sran.Upper();
	p -> GetParameter(sani); sani.Upper();
	oCNpc* npc	= PopAndCheckValidNPC("Mdl_ApplyRandomAni", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... ani: "+ sani + ", ani2: " + sran, TRUE);
	};
#endif

	if (npc) 
	{
		zCModel* model = npc->GetModel();
		if (model) 
		{
			zTModelAniID ani = npc -> GetModel() -> GetAniIDFromAniName(sani);
			zTModelAniID ran = npc -> GetModel() -> GetAniIDFromAniName(sran);
			if ((ani) && (ran)) model -> InsertRandAni (ani, ran);
			else zERR_WARNING("C: Mdl_ApplyRandomAni(): could not apply random ani with name " + sani + ". name2: " + sran);
		}
	}
	return FALSE;
}

static zBOOL Mdl_ApplyRandomAniFreq()
{
	zREAL freq;
	zSTRING sani;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(freq);
	p -> GetParameter(sani); sani.Upper();
	oCNpc* npc	= PopAndCheckValidNPC("Mdl_ApplyRandomAniFreq", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... ani: " + sani, TRUE);
	};
#endif
	if (npc && npc->GetModel()) 
	{
		zCModel* model = npc->GetModel();
		if (model) 
		{
			zTModelAniID ani = npc -> GetModel() -> GetAniIDFromAniName(sani);
			if (ani != zMDL_ANI_ID_ILLEGAL) model -> SetRandAniFreq(ani, freq);
			else zERR_WARNING("C: Mdl_ApplyRandomAniFreq(): could not apply random ani with name " + sani);
		}
	}
	return FALSE;
}

static zBOOL Mdl_SetModelScale()
{
	zREAL x,y,z;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(z);
	p -> GetParameter(y);
	p -> GetParameter(x);

	oCNpc* npc	= PopAndCheckValidNPC("Mdl_SetModelScale", TRUE);

	if (npc) 
	{
		zVEC3 scale(x,y,z);
		npc->SetModelScale(scale);
		if (npc->GetAnictrl()) npc->GetAnictrl()->SetVob(npc);
	}
	return FALSE;
}

static zBOOL Mdl_SetModelFatness()
{
	zREAL fatness;
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(fatness);

	oCNpc* npc	= PopAndCheckValidNPC("Mdl_SetModelFatness", TRUE);
	if (npc) {
		npc->SetFatness(fatness);
	};
	return FALSE;
}


static zBOOL Mdl_StartFaceAni()
{
	zSTRING name;
	zREAL holdtime,intensity;
	
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(holdtime);
	p -> GetParameter(intensity);
	p -> GetParameter(name);
	oCNpc* npc	= PopAndCheckValidNPC("Mdl_StartFaceAni", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... face Ani: " + name, TRUE);
	};
#endif
	if (npc) {
		npc -> StartFaceAni (name,intensity,holdtime);
	}
	return FALSE;
}

static zBOOL Mdl_ApplyRandomFaceAni()
{
	zSTRING name;
	zREAL timeMin,timeMinVar,timeMax,timeMaxVar,probMin;
	
	zCParser *p = zCParser :: GetParser();
	p -> GetParameter(probMin);
	p -> GetParameter(timeMaxVar);
	p -> GetParameter(timeMax);
	p -> GetParameter(timeMinVar);
	p -> GetParameter(timeMin);
	p -> GetParameter(name);

	oCNpc* npc	= PopAndCheckValidNPC("Mdl_ApplyRandomFaceAni", FALSE);
#ifdef CHECK_SCRIPT_PARANOID
	if (!npc)
	{
		DebugOut("... face Ani: " + name, TRUE);
	};
#endif
	if (npc) 
	{
		// NOTE start morph ani at any node
		// Search HeadNode
		zCModelNodeInst* head = npc->GetModel()->SearchNode(zMDL_NODE_NAME_HEAD);
		if (!head) return FALSE;
		// Getting the Visual
		zCMorphMesh* mm = dynamic_cast<zCMorphMesh*> (head->GetNodeVisual());
		if (mm) {
			zCMorphMeshAni* ani = mm -> SearchAni(name);
			if (ani) mm -> AddRandAni (ani,timeMin,timeMinVar,timeMax,timeMaxVar,probMin);
		}
	}
	return FALSE;
}

// ****************************************************************************************
// World
// ****************************************************************************************

static zBOOL Wld_IsTime()
{
	zCParser *p = zCParser :: GetParser();
	int hour1,min1,hour2,min2;
	p -> GetParameter(min2);
	p -> GetParameter(hour2);
	p -> GetParameter(min1);
	p -> GetParameter(hour1);
	p -> SetReturn (ogame -> GetWorldTimer() -> IsTimeBetween(hour1,min1,hour2,min2));
	return FALSE;
}

static zBOOL Wld_GetDay()
{
	zCParser *p = zCParser :: GetParser();
	p -> SetReturn (ogame -> GetWorldTimer() -> GetDay());
	return FALSE;
}


static zBOOL Wld_IsRaining()
{
	zCParser *p = zCParser :: GetParser();
	zCSkyControler_Outdoor* sky = dynamic_cast<zCSkyControler_Outdoor*>(zCSkyControler::GetActiveSkyControler());
	
	p -> SetReturn ( (sky && sky->GetRainFXWeight()>0.3f) );
	return FALSE;
}


// CODECHANGE [SPECKELS]

#if defined(SECUROM) && !defined(COMPILING_SPACER)
#include <tchar.h>
#include "special.h"
#endif

static zBOOL IntroduceChapter()
{
	zCParser *p = zCParser :: GetParser();
	zSTRING		texName;
	zSTRING		sndName;
	zSTRING		text1,text2;
	int			milliseconds;
	zBOOL		result = FALSE;	

	p->GetParameter(milliseconds);
	p->GetParameter(sndName);	
	p->GetParameter(texName);
	p->GetParameter(text2);
	p->GetParameter(text1);	
	
	zERR_MESSAGE(1,0,"B: Introducing chapter: "+text1+" ("+zSTRING(milliseconds)+"ms)");
	
	gameMan->IntroduceChapter(text1,text2,texName,sndName,milliseconds);
	
	zERR_MESSAGE(1,0,"B: Introducing chapter ended.");

	p -> SetReturn (result);
	
#if defined(SECUROM) && !defined(COMPILING_SPACER)
	#include "evt_1.inl"
		::ogame->GetSpawnManager()->SetSpawnFlags(NPC_FLAG_IMMORTAL | NPC_FLAG_PROTECTED);
	#include "evt_2.inl"
#endif

	return TRUE;
};

static zBOOL ExitGame()
{
	if (gameMan)
		gameMan->ExitGame();
	return TRUE;
};
 
static zBOOL ExitSession()
{
	if (gameMan)
		gameMan->ExitSession();
	return TRUE;
};
 
zBOOL PlayVideo()
{
	zCParser *p = zCParser :: GetParser();
	
	zSTRING	s;
	p->GetParameter(s);

	zBOOL result = gameMan->PlayVideo(s);
	p->SetReturn(result);
	
	return TRUE;
};

zBOOL PlayVideoEx()
{
	zCParser *p = zCParser :: GetParser();
	
	int sessionExit = FALSE;
	p->GetParameter(sessionExit);
	int screenBlend = 0;
	p->GetParameter(screenBlend);
	zSTRING	s;
	p->GetParameter(s);

	zBOOL result = gameMan->PlayVideoEx(s, screenBlend, sessionExit);
	p->SetReturn(result);

	return TRUE;
};

static zBOOL SetPercentDone()
{
	zCParser *p = zCParser :: GetParser();
	int percent;	
	p->GetParameter(percent);
	p->SetPercentDone(percent);
	return TRUE;
};

////////////////////////////////////////////////////////////////////////////////
//
//	Currently Dummy (for protection reasons)
//

static zBOOL Game_InitLanguage(int lang)
{
	zCParser *p = zCParser::GetParser();
	// dummy
	zBOOL result = TRUE;
	p->SetReturn(result);
	return TRUE;
}

#ifndef GOLDMASTER
	static zBOOL Game_InitGerman()	{ return Game_InitLanguage(0x0407); };
	static zBOOL Game_InitEnglish() { return Game_InitLanguage(0x0409); };
	static zBOOL Game_InitEngIntl() { return Game_InitLanguage(0x0409); };
#else
	#ifdef	LANG_DEU
		static zBOOL Game_InitGerman()	{ return Game_InitLanguage(0x0407); };
	#elif	LANG_ENU
		static zBOOL Game_InitEnglish() { return Game_InitLanguage(0x0409); };
		static zBOOL Game_InitEngIntl() { return Game_InitLanguage(0x0409); };
	#else
	#error	--- You have to specify the language for goldmasters! ---
	#endif
#endif

/* ----------------------------------------------------------------------
	
	DefineExternals_Ulfi()

	25.08.2000	[Roman Keskenti]	Added EquipArmor() skript function

	13.10.2000	[SPECKELS]			Added function "PlayVideo(s)"					

	08.11.2000	[SPECKELS]			Added function "SetPercentDone(i)"					

   ---------------------------------------------------------------------- */

void oCGame :: DefineExternals_Ulfi(zCParser* parser)
{	
	//
	// Game-Parser
	//


	// HELPERS
	parser->DefineExternal("IntToString",IntToString,
		zPAR_TYPE_STRING,	zPAR_TYPE_INT,							zPAR_TYPE_VOID);
	parser->DefineExternal("FloatToString",FloatToString,
		zPAR_TYPE_STRING,	zPAR_TYPE_FLOAT,							zPAR_TYPE_VOID);
	parser->DefineExternal("FloatToInt",FloatToInt,
		zPAR_TYPE_INT,	zPAR_TYPE_FLOAT,							zPAR_TYPE_VOID);
	parser->DefineExternal("IntToFloat",IntToFloat,
		zPAR_TYPE_FLOAT,	zPAR_TYPE_INT,							zPAR_TYPE_VOID);
	parser->DefineExternal("ConcatStrings",ConcatStrings,
		zPAR_TYPE_STRING,	zPAR_TYPE_STRING,	zPAR_TYPE_STRING,							zPAR_TYPE_VOID);
		// CODECHANGE [STEFAN] END
	parser->DefineExternal("Print",Print,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING,							zPAR_TYPE_VOID);
	parser->DefineExternal("PrintDebug",PrintDebug,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING,							zPAR_TYPE_VOID);
	// CODECHANGE [STEFAN]
	// CODECHANGE [ROMAN]
	parser->DefineExternal("PrintScreen",PrintScreen,
		zPAR_TYPE_INT,	zPAR_TYPE_STRING,zPAR_TYPE_INT,zPAR_TYPE_INT,zPAR_TYPE_STRING,zPAR_TYPE_INT,zPAR_TYPE_VOID);
	parser->DefineExternal("AI_PrintScreen",AI_PrintScreen,
		zPAR_TYPE_INT,	zPAR_TYPE_STRING,zPAR_TYPE_INT,zPAR_TYPE_INT,zPAR_TYPE_STRING,zPAR_TYPE_INT,zPAR_TYPE_VOID);
	parser->DefineExternal("PrintDialog",PrintDialog,
		zPAR_TYPE_INT,	zPAR_TYPE_INT,zPAR_TYPE_STRING,zPAR_TYPE_INT,zPAR_TYPE_INT,zPAR_TYPE_STRING,zPAR_TYPE_INT,zPAR_TYPE_VOID);
	// CODECHANGE [ROMAN] END
	parser->DefineExternal("PrintDebugInst",PrintDebugInst,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING,							zPAR_TYPE_VOID);
	parser->DefineExternal("PrintDebugInstCh",PrintDebugInstCh,
		zPAR_TYPE_VOID,	zPAR_TYPE_INT,	zPAR_TYPE_STRING,							zPAR_TYPE_VOID);
	parser->DefineExternal("PrintDebugCh",PrintDebugCh,
		zPAR_TYPE_VOID,	zPAR_TYPE_INT,	zPAR_TYPE_STRING,							zPAR_TYPE_VOID);
	// CODECHANGE [STEFAN] END
	parser->DefineExternal("PrintMulti",PrintMulti,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING,zPAR_TYPE_STRING,zPAR_TYPE_STRING,zPAR_TYPE_STRING,zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	

	// CODECHANGE [SPECKELS] BEGIN
	parser->DefineExternal("ExitGame", ExitGame,
		zPAR_TYPE_VOID,	 zPAR_TYPE_VOID);
	parser->DefineExternal("ExitSession", ExitSession,
		zPAR_TYPE_VOID,	 zPAR_TYPE_VOID);
	parser->DefineExternal("PlayVideo", PlayVideo,
		zPAR_TYPE_INT,	 zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("PlayVideoEx", PlayVideoEx,
		zPAR_TYPE_INT,	 zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_INT,	zPAR_TYPE_VOID);
	parser->DefineExternal("SetPercentDone",SetPercentDone,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INT, zPAR_TYPE_VOID);

	parser->DefineExternal("IntroduceChapter",IntroduceChapter,
		zPAR_TYPE_VOID,	 zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	// CODECHANGE [SPECKELS] END


	// *** NEWS ***
	parser->DefineExternal("Npc_MemoryEntry",Npc_MemoryEntry,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_MemoryEntryGuild",Npc_MemoryEntryGuild,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_HasNews",Npc_HasNews,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetNewsWitness",Npc_GetNewsWitness,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetNewsOffender",Npc_GetNewsOffender,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetNewsVictim",Npc_GetNewsVictim,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_IsNewsGossip",Npc_IsNewsGossip,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_DeleteNews",Npc_DeleteNews,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	
	parser->DefineExternal("Npc_GetGuildAttitude", Npc_GetGuildAttitude,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);

	// Spells & Magic
	parser->DefineExternal("Npc_GetActiveSpell", Npc_GetActiveSpell,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetLastHitSpellID", Npc_GetLastHitSpellID,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetLastHitSpellCat", Npc_GetLastHitSpellCat,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_GetActiveSpellCat", Npc_GetActiveSpellCat,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_GetActiveSpellLevel", Npc_GetActiveSpellLevel,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_GetActiveSpellIsScroll", Npc_GetActiveSpellIsScroll,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_SetActiveSpellInfo", Npc_SetActiveSpellInfo,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	

	// WORLD
	parser->DefineExternal("Wld_DetectItem",Wld_DetectItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);		
	parser->DefineExternal("Wld_DetectPlayer",Wld_DetectPlayer,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);		
	parser->DefineExternal("Wld_DetectNpc",Wld_DetectNpc,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_FUNC, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_DetectNpcEx",Wld_DetectNpcEx,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_FUNC, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_DetectNpcExAtt",Wld_DetectNpcExAtt,		// [BENDLIN] 2002-05-12, fixed swapped params
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_FUNC, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_SetGuildAttitude",Wld_SetGuildAttitude,
		zPAR_TYPE_VOID,	zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_GetGuildAttitude",Wld_GetGuildAttitude,
		zPAR_TYPE_INT,	zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_IsMobAvailable",Wld_IsMobAvailable,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_IsFPAvailable",Wld_IsFPAvailable,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_IsNextFPAvailable",Wld_IsNextFPAvailable,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);

	// NSCS
	parser->DefineExternal("Npc_CreateSpell",Npc_CreateSpell,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,			zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_LearnSpell", Npc_LearnSpell,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,			zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasItems", Npc_HasItems,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,			zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GiveItem", Npc_GiveItem,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	//	CODECHANGE [ROMAN]
	parser->DefineExternal("CreateInvItem", Npc_CreateInvItem,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,			zPAR_TYPE_VOID);	
	parser->DefineExternal("CreateInvItems", Npc_CreateInvItems,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,			zPAR_TYPE_INT,	zPAR_TYPE_VOID);	
	//	CODECHANGE [ROMAN] END
	parser->DefineExternal("Npc_GetInvItem", Npc_GetInvItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,			zPAR_TYPE_VOID);	
	//	CODECHANGE [ROMAN]
	parser->DefineExternal("Npc_GetInvItemBySlot", Npc_GetInvItemBySlot,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,zPAR_TYPE_INT,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_RemoveInvItem", Npc_RemoveInvItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT, zPAR_TYPE_VOID );	
	parser->DefineExternal("Npc_RemoveInvItems", Npc_RemoveInvItems,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,zPAR_TYPE_INT, zPAR_TYPE_VOID );	
	//	CODECHANGE [ROMAN] END

	// [EDENFELD] neu 1.09
	parser->DefineExternal("Npc_ClearInventory", Npc_ClearInventory,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);


	parser->DefineExternal("Npc_IsInState", Npc_IsInState,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FUNC, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_WasInState", Npc_WasInState,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FUNC, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_IsInRoutine", Npc_IsInRoutine,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FUNC, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_SetNpcsToState", AI_SetNpcsToState,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FUNC, zPAR_TYPE_INT, zPAR_TYPE_VOID);	


	parser->DefineExternal("Npc_HasDetectedNpc", Npc_HasDetectedNpc,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID );	

	// ********************************************************************************
	// Attitude
	// ********************************************************************************
	parser->DefineExternal("Npc_SetAttitude",		Npc_SetAttitude,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,			zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_SetTempAttitude",	Npc_SetTempAttitude,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,			zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetAttitude",		Npc_GetAttitude,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetPermAttitude",	Npc_GetPermAttitude,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_ChangeAttribute",		Npc_ChangeAttribute,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT,	zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_GetComrades", Npc_GetComrades,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_IsNear", Npc_IsNear,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetDistToNpc", Npc_GetDistToNpc,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetHeightToNpc", Npc_GetHeightToNpc,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetHeightToItem", Npc_GetHeightToItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_GetDistToPlayer", Npc_GetDistToPlayer,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetDistToItem", Npc_GetDistToItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetDistToWP", Npc_GetDistToWP,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);	
	
	parser->DefineExternal("Npc_CanSeeNpc", Npc_CanSeeNpc,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_CanSeeNpcFreeLOS", Npc_CanSeeNpcFreeLOS,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_CanSeeItem", Npc_CanSeeItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	
	parser->DefineExternal("Npc_IsPlayer", Npc_IsPlayer,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	
	parser->DefineExternal("Npc_KnowsPlayer", Npc_KnowsPlayer,
		zPAR_TYPE_INT,  zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID );
	parser->DefineExternal("Npc_SetKnowsPlayer", Npc_SetKnowsPlayer,
		zPAR_TYPE_VOID,  zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID );

	parser->DefineExternal("Npc_IsInFightMode", Npc_IsInFightMode,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_IsAiming",	Npc_IsAiming,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);

	parser->DefineExternal("Npc_StartItemReactModules", Npc_StartItemReactModules,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasOffered", Npc_HasOffered,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	

	// NSC AI
	parser->DefineExternal("EquipItem", EquipItem,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_SetToFistMode", Npc_SetToFistMode,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_SetToFightMode", Npc_SetToFightMode,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	
	parser->DefineExternal("Npc_IsDead", Npc_IsDead,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	// ***************************************************************************************
	// Zust�nde
	// ***************************************************************************************
	
	parser->DefineExternal("AI_StartState", AI_StartState,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_FUNC, zPAR_TYPE_INT, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_ContinueRoutine", AI_ContinueRoutine,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetStateTime", Npc_GetStateTime,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_SetStateTime", Npc_SetStateTime,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INT, zPAR_TYPE_VOID);	

	parser->DefineExternal("AI_Output", AI_Output,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,		zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_OutputSVM",	AI_OutputSVM,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,		zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_OutputSVM_Overlay",	AI_OutputSVM_Overlay,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,		zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_PlayCutscene", AI_PlayCutscene,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_CanSeeNpc",	AI_CanSeeNpc,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE,	zPAR_TYPE_FUNC,	zPAR_TYPE_VOID);	

	parser->DefineExternal("AI_Wait", AI_Wait,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_FLOAT,	zPAR_TYPE_VOID);		
	parser->DefineExternal("AI_Waitms", AI_Waitms,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INT,		zPAR_TYPE_VOID);		
	parser->DefineExternal("AI_WaitTillEnd", AI_WaitTillEnd,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);		
	parser->DefineExternal("AI_AlignToWP",	AI_AlignToWP,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);		

	parser->DefineExternal("AI_SetWalkMode", AI_SetWalkMode,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INT,		zPAR_TYPE_VOID);		

	parser->DefineExternal("AI_PlayAni",	AI_PlayAni,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_PlayAniBS",	AI_PlayAniBS,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,	zPAR_TYPE_INT,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_GotoWP",		AI_GotoWP,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_Teleport",	AI_Teleport,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	
	parser->DefineExternal("AI_GotoItem",	AI_GotoItem,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_GotoNpc",	AI_GotoNpc,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	

	parser->DefineExternal("AI_AlignToFP",	AI_AlignToFP,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_GotoFP",		AI_GotoFP,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_IsOnFP",	Npc_IsOnFP,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_GotoNextFP", AI_GotoNextFP,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_GotoSound",	AI_GotoSound,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);		
	parser->DefineExternal("AI_TakeItem",	AI_TakeItem,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_DropItem",	AI_DropItem,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_DrawWeapon", AI_DrawWeapon,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_RemoveWeapon", AI_RemoveWeapon,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	// Konzept V1.41
	parser->DefineExternal("Npc_HasRangedWeaponWithAmmo",	Npc_HasRangedWeaponWithAmmo,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasEquippedWeapon",			Npc_HasEquippedWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasEquippedMeleeWeapon",	Npc_HasEquippedMeleeWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasEquippedRangedWeapon",	Npc_HasEquippedRangedWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasEquippedArmor",			Npc_HasEquippedArmor,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_HasReadiedWeapon",			Npc_HasReadiedWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasReadiedMeleeWeapon",		Npc_HasReadiedMeleeWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasReadiedRangedWeapon",	Npc_HasReadiedRangedWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetTrueGuild",				Npc_GetTrueGuild,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_SetTrueGuild",				Npc_SetTrueGuild,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_AreWeStronger",				Npc_AreWeStronger,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetTarget",					Npc_GetTarget,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetNextTarget",				Npc_GetNextTarget,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetLookAtTarget",				Npc_GetLookAtTarget,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_IsNextTargetAvailable",		Npc_IsNextTargetAvailable,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_SetTarget",					Npc_SetTarget,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	// wird nicht mehr gebarucht:  parser->DefineExternal("Npc_IsEnemybehindFriend",		Npc_IsEnemyBehindFriend,
	//	zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetBodyState",				Npc_GetBodyState,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasBodyFlag",				Npc_HasBodyFlag,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_IsInCutscene",				Npc_IsInCutscene,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_IsVoiceActive",				Npc_IsVoiceActive,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_StopAni",	Npc_StopAni,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_GetDetectedMob",			Npc_GetDetectedMob,
		zPAR_TYPE_STRING, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_PlayAni",	Npc_PlayAni,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_IsDetectedMobOwnedByNpc",	Npc_IsDetectedMobOwnedByNpc,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_IsDetectedMobOwnedByGuild",	Npc_IsDetectedMobOwnedByGuild,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_INT,		zPAR_TYPE_VOID);	
	parser->DefineExternal("Wld_GetMobState",	Wld_GetMobState	,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	

	parser->DefineExternal("Npc_ClearAIQueue",				Npc_ClearAIQueue,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	
	// ****************************************************************************
	// Infos
	// ****************************************************************************
	
	parser->DefineExternal("InfoManager_HasFinished", InfoManager_HasFinished,
		zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_StopProcessInfos",		AI_StopProcessInfos,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_ProcessInfos",			AI_ProcessInfos,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Info_AddChoice",			Info_AddChoice,
		zPAR_TYPE_VOID,	zPAR_TYPE_INT,	zPAR_TYPE_STRING, zPAR_TYPE_FUNC, zPAR_TYPE_VOID);	
	parser->DefineExternal("Info_ClearChoices",			Info_ClearChoices,
		zPAR_TYPE_VOID,	zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_KnowsInfo",				Npc_KnowsInfo,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_CheckInfo",				Npc_CheckInfo,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GiveInfo",				Npc_GiveInfo,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	

	// ****************************************************************************
	// Talents
	// ****************************************************************************

	parser->DefineExternal("Npc_GetTalentSkill",	Npc_GetTalentSkill,	// (npc, talentConstant)
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);			
	parser->DefineExternal("Npc_GetTalentValue",	Npc_GetTalentValue,	// (npc, talentConstant)
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);			
	
	parser->DefineExternal("Npc_SetTalentSkill",	Npc_SetTalentSkill, // (npc, talentConstant, talentSkill)
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);				
	parser->DefineExternal("Npc_SetTalentValue",	Npc_SetTalentValue, // (npc, talentConstant, talentValue)
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);				
							
	parser->DefineExternal("Tal_Configure",			Tal_Configure,		// (talentConstant, valueRelevant)
		zPAR_TYPE_VOID,	zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);		
	

	// ****************************************************************************
	// Waypoints
	// ****************************************************************************

	parser->DefineExternal("Npc_GetNearestWP",				Npc_GetNearestWP,
		zPAR_TYPE_STRING, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_GetNextWP",					Npc_GetNextWP,
		zPAR_TYPE_STRING, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_IsWayBlocked",				Npc_IsWayBlocked,
		zPAR_TYPE_INT,  zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);

	// ****************************************************************************
	// Weapons
	// ****************************************************************************

	parser->DefineExternal("Npc_GetReadiedWeapon",			Npc_GetReadiedWeapon,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetEquippedMeleeWeapon",	Npc_GetEquippedMeleeWeapon,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetEquippedRangedWeapon",	Npc_GetEquippedRangedWeapon,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_GetEquippedArmor",			Npc_GetEquippedArmor,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	
	parser->DefineExternal("AI_EquipBestMeleeWeapon", AI_EquipBestMeleeWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_EquipBestRangedWeapon", AI_EquipBestRangedWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_EquipBestArmor", AI_EquipBestArmor,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_UnequipWeapons", AI_UnequipWeapons,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_UnequipArmor", AI_UnequipArmor,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_EquipArmor", AI_EquipArmor,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_ReadyMeleeWeapon", AI_ReadyMeleeWeapon,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_ReadyRangedWeapon", AI_ReadyRangedWeapon,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	
	// ****************************************************************************
	// Turn To
	// ****************************************************************************

	parser->DefineExternal("AI_TurnAway", AI_TurnAway,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_TurnToNPC", AI_TurnToNPC,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_WhirlAround", AI_WhirlAround,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_WhirlAroundToSource", AI_WhirlAroundToSource,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_TurnToSound", AI_TurnToSound,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	// ****************************************************************************
	// Look
	// ****************************************************************************

	parser->DefineExternal("AI_QuickLook", AI_QuickLook,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);

	parser->DefineExternal("AI_LookAt",		AI_LookAt,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_LookAtNpc",	AI_LookAtNpc,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);		
	parser->DefineExternal("AI_StopLookAt", AI_StopLookAt,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	parser->DefineExternal("AI_PointAt",	AI_PointAt,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_PointAtNpc", AI_PointAtNpc,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);		
	parser->DefineExternal("AI_StopPointAt", AI_StopPointAt,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	parser->DefineExternal("AI_Standup",	AI_StandUp,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_StandupQuick",	AI_StandUpQuick,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	

	//
	//	CODECHANGE [ROMAN]
	//
	parser->DefineExternal("AI_Flee",		AI_Flee,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_AimAt",	AI_AimAt, 
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_StopAim",	AI_StopAim, 
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_ShootAt", AI_ShootAt, 
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_Defend",		AI_Defend,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_CombatReactToDamage", AI_CombatReactToDamage,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_ReadySpell",	AI_ReadySpell,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_UnreadySpell", AI_UnreadySpell,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_HasSpell", Npc_HasSpell,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	//
	//	CODECHANGE [ROMAN] END
	//
	parser->DefineExternal("AI_Attack",		AI_Attack,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_FinishingMove",		AI_FinishingMove,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_Dodge",		AI_Dodge,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("AI_UseItem",	AI_UseItem, 
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_UseItemToState",	AI_UseItemToState, 
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);

	// DIALOG	
	parser->DefineExternal("Npc_RefuseTalk", Npc_CanTalk,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_SetRefuseTalk", Npc_SetCanTalk,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	
	parser->DefineExternal("AI_Ask", AI_Ask,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FUNC, zPAR_TYPE_FUNC,	zPAR_TYPE_VOID);
	//
	//	CODECHANGE [ROMAN]
	//
	parser->DefineExternal("AI_AskText", AI_AskText,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FUNC, zPAR_TYPE_FUNC,	zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	//
	//	CODECHANGE [ROMAN] END
	//
	parser->DefineExternal("AI_WaitForQuestion", AI_WaitForQuestion,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FUNC, zPAR_TYPE_VOID);

	// HELPERS
	parser->DefineExternal("Hlp_IsItem", Hlp_IsItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Hlp_GetInstanceID", Hlp_GetInstanceID,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);	
	parser->DefineExternal("Hlp_Random", Hlp_Random,
		zPAR_TYPE_INT,	zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Hlp_StrCmp", Hlp_StrCmp,
		zPAR_TYPE_INT,	zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_VOID);	
	parser->DefineExternal("Hlp_GetNpc", Hlp_GetNpc,
		zPAR_TYPE_INSTANCE,	zPAR_TYPE_INT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Hlp_IsValidNpc", Hlp_IsValidNpc,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Hlp_IsValidItem", Hlp_IsValidItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);

	// SOUND
	// [EDENFELD] 1.09 neu
	parser->DefineExternal("AI_Snd_Play", AI_Snd_Play, 
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_Snd_Play3D", AI_Snd_Play3D,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);

	parser->DefineExternal("Snd_Play", Ext_SndPlay,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING, zPAR_TYPE_VOID);	
	parser->DefineExternal("Snd_Play3d", Ext_SndPlay3d,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);	

	// ****************************************************************************
	// Logical Sound
	// ****************************************************************************

	parser->DefineExternal("Snd_GetDistToSource",	Snd_GetDistToSource,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Snd_IsSourceNpc",		Snd_IsSourceNpc,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Snd_IsSourceItem",		Snd_IsSourceItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_CanSeeSource",		Npc_CanSeeSource,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);

	// ****************************************************************************
	// Missions
	// ****************************************************************************
	parser->DefineExternal("Mis_GetStatus",		Mis_GetStatus,
		zPAR_TYPE_INT,	zPAR_TYPE_INT,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Mis_SetStatus",		Mis_SetStatus,
		zPAR_TYPE_VOID,	zPAR_TYPE_INT,	zPAR_TYPE_INT,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Mis_OnTime",		Mis_SetStatus,
		zPAR_TYPE_INT,	zPAR_TYPE_INT,	zPAR_TYPE_VOID);	

	// CODECHANGE [STEFAN]
	
	parser->DefineExternal("Log_CreateTopic",Log_CreateTopic,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING,	zPAR_TYPE_INT,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Log_AddEntry",Log_AddEntry,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);
	parser->DefineExternal("Log_SetTopicStatus",Log_SetTopicStatus,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING,	zPAR_TYPE_INT,	zPAR_TYPE_VOID);
	
	parser->DefineExternal("Mis_AddMissionEntry",	Mis_AddMissionEntry,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_STRING,	zPAR_TYPE_VOID);
	parser->DefineExternal("Mis_RemoveMission",	 Mis_RemoveMission,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE,	zPAR_TYPE_VOID);
	// CODECHANGE [STEFAN] END

	parser->DefineExternal("Npc_CheckAvailableMission",	Npc_CheckAvailableMission,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_CheckRunningMission",	Npc_CheckRunningMission,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);

	parser->DefineExternal("Npc_IsDrawingWeapon",	Npc_IsDrawingWeapon,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);


	parser->DefineExternal("Npc_IsDrawingSpell",	Npc_IsDrawingSpell,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);

	parser->DefineExternal("Npc_CheckOfferMission",		Npc_CheckOfferMission,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);


	// Models & other lustige Thingies
	parser->DefineExternal("Mdl_SetVisual",	Mdl_SetVisual,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Mdl_SetVisualBody",	Mdl_SetVisualBody,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Mdl_ApplyOverlayMds",	Mdl_ApplyOverlayMds,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Mdl_ApplyOverlayMdsTimed",	Mdl_ApplyOverlayMdsTimed,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Mdl_RemoveOverlayMds",	Mdl_RemoveOverlayMds,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Mdl_ApplyRandomAni",	Mdl_ApplyRandomAni,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Mdl_ApplyRandomAniFreq",Mdl_ApplyRandomAniFreq,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_FLOAT, zPAR_TYPE_VOID);
	parser->DefineExternal("Mdl_SetModelScale",	Mdl_SetModelScale,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Mdl_SetModelFatness",	Mdl_SetModelFatness,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_FLOAT, zPAR_TYPE_VOID);	

	parser->DefineExternal("Mdl_StartFaceAni",	Mdl_StartFaceAni,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_VOID);	
	parser->DefineExternal("Mdl_ApplyRandomFaceAni",	Mdl_ApplyRandomFaceAni,
		zPAR_TYPE_VOID,	zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_VOID);	
	// **************************
	// Welt
	// **************************
	parser->DefineExternal("Wld_IsTime",	Wld_IsTime,
		zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_GetDay",	Wld_GetDay,
		zPAR_TYPE_INT, zPAR_TYPE_VOID);

	parser->DefineExternal("Wld_IsRaining",	Wld_IsRaining,	zPAR_TYPE_INT, zPAR_TYPE_VOID);

	parser->DefineExternal("Wld_SetTime",	Wld_SetTime,
		zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_InsertNpc",	Wld_InsertNpc,
		zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	// Codechange [CARSTEN]
	parser->DefineExternal("Wld_SpawnNpcRange",	Wld_SpawnNpcRange,
		zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE,zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_FLOAT,zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_PlayEffect",	Wld_PlayEffect,
		zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_StopEffect",	Wld_StopEffect,	zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);

	// npc effect related
	parser->DefineExternal("AI_PlayFX",	AI_PlayFX,  zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_StopFX",	AI_StopFX,	zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,   zPAR_TYPE_VOID);

	// Codechange [CARSTEN] END
	parser->DefineExternal("Wld_RemoveNpc",	Wld_RemoveNpc,
		zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_VOID);

	parser->DefineExternal("Wld_InsertNpcAndRespawn",	Wld_InsertNpcAndRespawn,
		zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_InsertItem",Wld_InsertItem,
		zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_STRING, zPAR_TYPE_VOID);	
	// CODECHANGE [ROMAN]
	parser->DefineExternal("Wld_InsertObject",Wld_InsertObject,
		zPAR_TYPE_VOID,	zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_VOID);		
	// CODECHANGE [ROMAN] END
	// CODECHANGE [ROMAN]
	parser->DefineExternal("Wld_RemoveItem",Wld_RemoveItem,
		zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);		
	// CODECHANGE [ROMAN] END
	parser->DefineExternal("Wld_ExchangeGuildAttitudes",Wld_ExchangeGuildAttitudes,
		zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID );
	parser->DefineExternal("Wld_SetObjectRoutine", Wld_SetObjectRoutine,
		zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_VOID );
	parser->DefineExternal("Wld_SetMobRoutine", Wld_SetMobRoutine,
		zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_VOID );

	parser->DefineExternal("Wld_SendTrigger", Wld_SendTrigger,
		zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID );
	parser->DefineExternal("Wld_SendUntrigger", Wld_SendUntrigger,
		zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID );

	// **************************
	// Owners
	// **************************
	parser->DefineExternal("Npc_OwnedByNpc",	Npc_OwnedByNpc,
		zPAR_TYPE_INT, zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_OwnedByGuild",	Npc_OwnedByGuild,
		zPAR_TYPE_INT, zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_VOID);

	// **************************
	// Mob-Interact
	// **************************
	parser->DefineExternal("AI_TakeMob",		AI_TakeMob,			zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_DropMob",		AI_DropMob,			zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("AI_UseMob",			AI_MobInteract,		zPAR_TYPE_INT, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Mob_CreateItems",	Mob_CreateItems,	zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Mob_HasItems",		Mob_HasItems,		zPAR_TYPE_INT,	zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_VOID);

	// **************************
	// Documents
	// **************************
	parser->DefineExternal( "Doc_Create"		,	Doc_Create			, zPAR_TYPE_INT ,																											zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_CreateMap"		,	Doc_CreateMap		, zPAR_TYPE_INT ,																											zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_SetPages"		,	Doc_SetPages		, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT,																				zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_SetPage"		,	Doc_SetPage			, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_STRING, zPAR_TYPE_INT,											zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_SetFont"		,	Doc_SetFont			, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_STRING,															zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_SetLevel"		,	Doc_SetLevel		, zPAR_TYPE_VOID, zPAR_TYPE_INT,				zPAR_TYPE_STRING,															zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_SetLevelCoords",	Doc_SetLevelCoords	, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT,								zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_SetMargins"	,	Doc_SetMargins		, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT,	zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_PrintLine"		,	Doc_PrintLine		, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_STRING,															zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_PrintLines"	,	Doc_PrintLines		, zPAR_TYPE_VOID, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_STRING,															zPAR_TYPE_VOID );
	parser->DefineExternal( "Doc_Show"			,	Doc_Show			, zPAR_TYPE_VOID, zPAR_TYPE_INT,																							zPAR_TYPE_VOID );

	// obsolete
	parser->DefineExternal("Doc_Open",			Doc_Open			, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Doc_Font",			Doc_Font			, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Doc_Print",			Doc_Print			, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Doc_MapCoordinates",Doc_MapCoordinates	, zPAR_TYPE_VOID, zPAR_TYPE_STRING, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_FLOAT, zPAR_TYPE_VOID);
	
	// **************************
	// Tagesablauf
	// **************************
	parser->DefineExternal("TA",TA,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,zPAR_TYPE_INT,zPAR_TYPE_FUNC,zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("TA_Min",TA_Min,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE,zPAR_TYPE_INT,zPAR_TYPE_INT,zPAR_TYPE_INT,zPAR_TYPE_INT,zPAR_TYPE_FUNC,zPAR_TYPE_STRING,	zPAR_TYPE_VOID);	
	parser->DefineExternal("TA_CS",		TA_CS,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE,zPAR_TYPE_STRING,zPAR_TYPE_STRING,	zPAR_TYPE_VOID);
	parser->DefineExternal("TA_BeginOverlay",	TA_BeginOverlay,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("TA_EndOverlay",		TA_EndOverlay,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("TA_RemoveOverlay",	TA_RemoveOverlay,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	
	parser->DefineExternal("Npc_ExchangeRoutine", Npc_ExchangeRoutine,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_VOID);
	parser->DefineExternal("Rtn_Exchange", Rtn_Exchange,
		zPAR_TYPE_VOID,	 zPAR_TYPE_STRING, zPAR_TYPE_STRING, zPAR_TYPE_VOID);

	// **************************
	// Perception
	// **************************

	parser->DefineExternal("Perc_SetRange",Perc_SetRange,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INT, zPAR_TYPE_INT,	zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_SetPercTime",Npc_SetPercTime,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_FLOAT,	zPAR_TYPE_VOID);	
	parser->DefineExternal("Npc_PercEnable", Npc_PercEnable,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,	zPAR_TYPE_FUNC,	zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_PercDisable", Npc_PercDisable,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,	zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_SendPassivePerc", Npc_SendPassivePerc,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,	zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_SendSinglePerc", Npc_SendSinglePerc,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,	zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_PerceiveAll", Npc_PerceiveAll,
		zPAR_TYPE_VOID,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);

	// **************************
	// Portal - R�ume
	// **************************
	parser->DefineExternal("Wld_AssignRoomToGuild", Wld_AssignRoomToGuild,
		zPAR_TYPE_VOID,	 zPAR_TYPE_STRING, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_AssignRoomToNpc", Wld_AssignRoomToNpc,
		zPAR_TYPE_VOID,	 zPAR_TYPE_STRING, zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	
	parser->DefineExternal("Wld_GetPlayerPortalOwner", Wld_GetPlayerPortalOwner,
		zPAR_TYPE_INSTANCE,		zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_GetPlayerPortalGuild", Wld_GetPlayerPortalGuild,
		zPAR_TYPE_INT,			zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_GetFormerPlayerPortalOwner", Wld_GetFormerPlayerPortalOwner,
		zPAR_TYPE_INSTANCE,		zPAR_TYPE_VOID);
	parser->DefineExternal("Wld_GetFormerPlayerPortalGuild", Wld_GetFormerPlayerPortalGuild,
		zPAR_TYPE_INT,			zPAR_TYPE_VOID);

	parser->DefineExternal("Npc_IsPlayerInMyRoom", Npc_IsPlayerInMyRoom,
		zPAR_TYPE_INT,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);

	parser->DefineExternal("Npc_IsInPlayersRoom", Npc_IsInPlayersRoom,
		zPAR_TYPE_INT,  zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
 
	parser->DefineExternal("Npc_WasPlayerInMyRoom", Npc_WasPlayerInMyRoom,
		zPAR_TYPE_INT,	 zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);

	parser->DefineExternal("Npc_GetPortalOwner", Npc_GetPortalOwner,
		zPAR_TYPE_INSTANCE,  zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	parser->DefineExternal("Npc_GetPortalGuild", Npc_GetPortalGuild,
		zPAR_TYPE_INT,  zPAR_TYPE_INSTANCE, zPAR_TYPE_VOID);
	
	// **************************
	// Cutscenes
	// **************************
	parser->DefineExternal("Hlp_CutscenePlayed", Hlp_CutscenePlayed,
		zPAR_TYPE_INT,	 zPAR_TYPE_STRING,	zPAR_TYPE_VOID);

	// [BENDLIN] 1.30
	// Language (currently dummy - protection)
#ifndef GOLDMASTER
	parser->DefineExternal("Game_InitGerman",	Game_InitGerman,	zPAR_TYPE_INT,  zPAR_TYPE_VOID);
	parser->DefineExternal("Game_InitEnglish",	Game_InitEnglish,	zPAR_TYPE_INT,  zPAR_TYPE_VOID);
	parser->DefineExternal("Game_InitEngIntl",	Game_InitEngIntl,	zPAR_TYPE_INT,  zPAR_TYPE_VOID);
#else
	#ifdef	LANG_DEU
	parser->DefineExternal("Game_InitGerman",	Game_InitGerman,	zPAR_TYPE_INT,  zPAR_TYPE_VOID);
	#elif	LANG_ENU
	parser->DefineExternal("Game_InitEnglish",	Game_InitEnglish,	zPAR_TYPE_INT,  zPAR_TYPE_VOID);
	parser->DefineExternal("Game_InitEngIntl",	Game_InitEngIntl,	zPAR_TYPE_INT,  zPAR_TYPE_VOID);
	#else
	#error	--- You have to specify the language for goldmasters! ---
	#endif
#endif

}

#pragma warning ( default:4244 )
#ifndef GOLDMASTER
#pragma warning ( default:4189 )
#endif

#endif


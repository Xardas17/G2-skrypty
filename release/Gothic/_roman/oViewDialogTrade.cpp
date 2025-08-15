
#include <zIncDialogs.h>
#include "zoption.h"
#include <oItem.h>
#include <oViewDialogItem.h>
#include <oInventory.h>
#include <oViewDialogItemContainer.h>
#include <oViewDialogStealContainer.h>
#include <oViewDialogInventory.h>
#include <oNpc.h>
#include <oNpcMessages.h>
#include <oGame.h>
#include <oWorld.h>
#include <oViewDialogTrade.h>
#include <zInput_Win32.h>


zCLASS_DEFINITION(oCViewDialogTrade, zCViewDialog, 0 ,0)


////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: UpdateViewSettings
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::UpdateViewSettings(void)
{
	int animateFade = zCViewFX::zEViewFX::VIEW_FX_FADE;
	int animateZoom = zCViewFX::zEViewFX::VIEW_FX_ZOOM;	
	int animateNone = zCViewFX::zEViewFX::VIEW_FX_NONE;	
	float durationFade = 500.0f;
	float durationZoom = 500.0f;
	float durationNone = 0.0f;
	if (!zoptions->ReadBool(zOPT_SEC_GAME, "animatedWindows", TRUE))
	{
		animateFade		= animateZoom	= animateNone;
		durationFade	= durationZoom	= durationNone;		
	};

	this->DlgInventoryNpc->SetFXOpen			(animateFade);
	this->DlgInventoryNpc->SetFXClose			(animateFade);	
	this->DlgInventoryNpc->SetDurationOpen		(durationFade);
	this->DlgInventoryNpc->SetDurationClose		(durationFade);

	this->DlgInventoryPlayer->SetFXOpen			(animateFade);
	this->DlgInventoryPlayer->SetFXClose		(animateFade);	
	this->DlgInventoryPlayer->SetDurationOpen	(durationFade);
	this->DlgInventoryPlayer->SetDurationClose	(durationFade);
};

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade (CONSTRUCTOR)
//
////////////////////////////////////////////////////////////////////////////////

oCViewDialogTrade::oCViewDialogTrade()
{
	// Deaktivieren
	this->Activate( FALSE );

	// Initialisieren
	this->SectionTrade	= TRADE_SECTION_LEFT_INVENTORY;
	this->NpcLeft		= NULL;
	this->NpcRight		= NULL;

	// Dialoge erzeugen
	this->DlgInventoryNpc		= zNEW(oCViewDialogStealContainer);
	this->DlgInventoryPlayer	= zNEW(oCViewDialogInventory);
	
	// Händler Inventar inititalisieren
	this->DlgInventoryNpc->Init			(this, FALSE, 0, 0, 0, 0, zSTRING("DEFAULT.TGA"));
	this->DlgInventoryNpc->SetPosition	(zPOS(0, 0));
	this->DlgInventoryNpc->SetSize		(zPOS(8192 / 8, 8192));
	this->DlgInventoryNpc->SetAlignment	(oCViewDialogStealContainer::oEStealContainerAlignment_Left);

	// Spieler Inventar initialisieren
	this->DlgInventoryPlayer->Init			(this, FALSE, 0, 0, 0, 0, zSTRING("DEFAULT.TGA"));
	this->DlgInventoryPlayer->SetPosition	(zPOS( 8192 - 8192 / 8, 0));
	this->DlgInventoryPlayer->SetSize		(zPOS( 8192 / 8	, 8192));
	this->DlgInventoryPlayer->SetAlignment	(oCViewDialogInventory::oEInventoryAlignment_Right);

	// Handelsfaktor holen (Standard ist 0.3f)
	this->DlgInventoryNpc->SetValueMultiplier( oCItemContainer::GetValueMultiplier() );

	// Einstellungen aktualisieren
	UpdateViewSettings();
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade (DESTRUCTOR)
//
////////////////////////////////////////////////////////////////////////////////

oCViewDialogTrade::~oCViewDialogTrade()
{
	// Dialoge freigeben
	zRELEASE(this->DlgInventoryNpc);
	zRELEASE(this->DlgInventoryPlayer);

	// Member zurücksetzen
	this->SetNpcLeft (NULL);
	this->SetNpcRight(NULL);
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: AllDialogsStop
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::AllDialogsStop(void)
{
	// Dialoge deselektieren
	this->DlgInventoryNpc->StopSelection();
	this->DlgInventoryPlayer->StopSelection();	
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: AllDialogsDisable
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::AllDialogsDisable(void)
{
	// Dialoge deaktivieren
	this->DlgInventoryNpc->Activate(FALSE);
	this->DlgInventoryPlayer->Activate(FALSE);
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: SetNpcLeft
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::SetNpcLeft(oCNpc* pNpc)
{
	this->NpcLeft = pNpc;

	if (this->NpcLeft)
	{
		// Vorherigen Handels-Container löschen
		if (this->NpcLeft->trader) 
		{ 
			delete this->NpcLeft->trader;
			this->NpcLeft->trader = NULL; 
		}
		// Handels-Container erzeugen
		this->NpcLeft->trader = zNEW(oCItemContainer);

		// Vorherigen Händler-Container löschen
		if (oCNpc::stealcontainer) 
		{
			delete (oCNpc::stealcontainer);
			oCNpc::stealcontainer = NULL;
		}
		// Handles-Container erzeugen
		oCNpc::stealcontainer = zNEW(oCStealContainer);
		oCNpc::stealcontainer->SetOwner(this->NpcLeft);

		// Member setzen
		this->DlgInventoryNpc->SetStealContainer(oCNpc::stealcontainer);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: SetNpcRight
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::SetNpcRight(oCNpc* pNpc)
{
	this->NpcRight = pNpc;

	if (this->NpcRight)
	{
		// Vorherigen Handles-Container freigeben
		if (this->NpcRight->trader) 
		{ 
			delete this->NpcRight->trader;
			this->NpcRight->trader = NULL; 
		}
		// Handels-Container erzeugen
		this->NpcRight->trader = zNEW(oCItemContainer);

		// Member setzen
		this->DlgInventoryPlayer->SetInventory(&this->NpcRight->inventory2);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: StartSelection
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::StartSelection(void)
{
	// Aktivieren
	this->Activate(TRUE);

	// Initialisieren
	this->IsDone = FALSE;

	// Dialoge starten
	this->DlgInventoryNpc->StartSelection();
	this->DlgInventoryPlayer->StartSelection();

	// Eingabefokus holen
	this->SetHandleEventTop();

	// Selektion setzen
	this->OnSection(TRADE_SECTION_LEFT_INVENTORY);
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: HandleEvent
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::HandleEvent(int nKey)
{
	if (!this->IsActive())
		return FALSE;

	// Anderen Handlern keine Nachricht zukommen lassen
	zBOOL bMessageHandled = TRUE;

	// FIXME: ein Unter-Inventar und/oder ein Unter-DialogView
	// haben die Selektion/Aktivitaet selbststaendig veraendert
	if (this->DlgInventoryPlayer->GetInventory())
		if ((this->DlgInventoryPlayer->GetInventory()->IsActive()) &&
			(this->SectionTrade != TRADE_SECTION_RIGHT_INVENTORY))
		{
			this->OnSection(TRADE_SECTION_RIGHT_INVENTORY);
		}
	if (this->DlgInventoryNpc->GetStealContainer())
		if ((this->DlgInventoryNpc->GetStealContainer()->IsActive()) &&
			(this->SectionTrade != TRADE_SECTION_LEFT_INVENTORY))
		{
			this->OnSection(TRADE_SECTION_LEFT_INVENTORY);
		}
	
	// Transfer-Anzahl initialisieren
	if (zinput->IsBindedToggled(GAME_ACTION, nKey) ||
		((nKey == MOUSE_BUTTONLEFT) && zinput->KeyToggled(MOUSE_BUTTONLEFT)))
	{
		SetTransferCount(0);
	}
	zINT transferAmount = oCItemContainer::TransferCountToAmount(GetTransferCount());
	if (zinput->IsBinded(GAME_SMOVE, nKey))
	{
		SetTransferCount(0);
		switch (this->SectionTrade)
		{
			case TRADE_SECTION_LEFT_INVENTORY:
				transferAmount = zMax(transferAmount, this->DlgInventoryNpc->GetSelectedItemCount());
				break;
			case TRADE_SECTION_RIGHT_INVENTORY:
				transferAmount = zMax(transferAmount, this->DlgInventoryPlayer->GetSelectedItemCount());
				break;
		}
	}

	// [ESC]
	if (zinput->IsBindedToggled(GAME_END, nKey) || (nKey == MOUSE_BUTTONRIGHT))
	{
		bMessageHandled = this->OnKeyEsc();
	}
	// [ACTION]
	else if (zinput->IsBinded(GAME_ACTION, nKey) || zinput->IsBinded(GAME_SMOVE, nKey) || (nKey == MOUSE_BUTTONLEFT)) 
	{
		switch (this->SectionTrade)
		{
			case TRADE_SECTION_LEFT_INVENTORY:
				// Item vom Händler zum Spieler (Kaufen)
				bMessageHandled = this->OnTransferRight(transferAmount);
				break;
			case TRADE_SECTION_RIGHT_INVENTORY:
				// Item vom Spieler zum Händler (Verkaufen)
				bMessageHandled = this->OnTransferLeft(transferAmount);
				break;
		}
	}
	// [NEXT]
	else if ( zinput->IsBindedToggled(GAME_INVENTORY, nKey) ) 
	{
		if (oCItemContainer::GetInvSplitScreen())
		{
			bMessageHandled = this->OnKeyEsc();
		}
		else
		{
			bMessageHandled = this->OnSectionNext();
			if (!bMessageHandled)
				bMessageHandled = this->OnSectionPrevious();
		}
	}
	else if (zinput->IsBinded(GAME_UP, nKey) || (nKey == MOUSE_WHEELUP) || 
			zinput->IsBinded(GAME_DOWN, nKey) || (nKey == MOUSE_WHEELDOWN) ||
			zinput->IsBinded(GAME_LEFT, nKey) || zinput->IsBinded(GAME_STRAFELEFT, nKey) || 
			zinput->IsBinded(GAME_RIGHT, nKey) || zinput->IsBinded(GAME_STRAFERIGHT, nKey))
	{
		bMessageHandled	= FALSE;
	}

	// Situation überprüfen
	this->Update();

	return bMessageHandled; 
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: Update
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::Update(void)
{
	// Immer Eingabefokus
	this->SetHandleEventTop();

	// Spieler weiterhin blockieren
	this->NpcRight->SetMovLock(TRUE);
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnKeyEnter
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::OnKeyEnter(void)
{
	// obsolete
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnKeyEsc
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::OnKeyEsc(void)
{
	// Handel beenden
	this->OnExit();
	
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnMoveLeft
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::OnMoveLeft(void)
{
	// Überprüfen, ob die Dialoge die Eingabe behandeln
	switch (this->SectionTrade)
	{
		case TRADE_SECTION_LEFT_INVENTORY:
			if (this->DlgInventoryNpc->CanHandleLeft())
				return FALSE;
			else
				return this->OnSectionPrevious();
			break;
		case TRADE_SECTION_RIGHT_INVENTORY:
			if (this->DlgInventoryPlayer->CanHandleLeft())
				return FALSE;
			else
				return this->OnSectionPrevious();
			break;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnTransferLeft
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::OnTransferLeft(zINT amount)
{
	oCItem* pItemChosen = NULL;
	int i;	

	switch (this->SectionTrade)
	{
		// Selektiertes item vom Spieler zum Händler (Verkaufen)
		case TRADE_SECTION_RIGHT_INVENTORY:
			{
				// Transferanzahl initialisieren
				IncTransferCount(amount);
				oCItem* item = this->DlgInventoryPlayer->GetSelectedItem();
				if ( item ) if ( item->GetAmount() <= amount )
				{
					amount = item->GetAmount();
					SetTransferCount(0);
				}

				// Währung kann nicht verkauft werden
				if (item && item->GetInstanceName().CompareTo( oCItemContainer::GetCurrencyInstanceName() ) == 0)
					return TRUE;

				// Items einzeln transferieren
				for (i = 0; i < amount; i++)
				{	
					// Item beim Spieler entfernen
					pItemChosen = this->DlgInventoryPlayer->RemoveSelectedItem();
					if ( pItemChosen )
					{
						// Anzahl Währungseinheiten geben, die der Spieler bekommt
						// (wenn das Item überhaupt was kostet)
						int value = pItemChosen->GetValue();
						if (value > 0)
						{
							// (Value * Multiplier)
							value = zFloat2Int(zREAL(value) * this->DlgInventoryNpc->GetValueMultiplier());
							// Mindestens 1
							if (value <= 0)
								value = 1;
						}
						
						if (value <= 0)
						{
							// Das Item kostet nichts... gib dem Händler das Item
							this->DlgInventoryNpc->InsertItem(pItemChosen);
						}
						else
						{
							// Währung erzeugen
							oCItem* coin = oCItemContainer::CreateCurrencyItem(value);
							if (!coin)
							{
								// Währung konnte nicht erzeugt werden... dem Spieler das Item zurückgeben
								this->DlgInventoryPlayer->InsertItem(pItemChosen);
							}
							else
							{
								// Händler das Item geben
								this->DlgInventoryNpc->InsertItem(pItemChosen);
								// Spieler das Gold geben
								this->DlgInventoryPlayer->InsertItem(coin);
								zRELEASE(coin);
							}
						}
					}
				}
			}
			break;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnMoveRight
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::OnMoveRight(void)
{
	// Überprüfen, ob die Dialoge die Eingabe behandeln
	switch (this->SectionTrade)
	{
		case TRADE_SECTION_LEFT_INVENTORY:
			if	(this->DlgInventoryNpc->CanHandleRight())
				return FALSE;
			else
				return this->OnSectionNext();
			break;
		case TRADE_SECTION_RIGHT_INVENTORY:
			if (this->DlgInventoryPlayer->CanHandleRight())
				return FALSE;
			else
				return this->OnSectionNext();
			break;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnTransferRight
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::OnTransferRight(zINT amount)
{
	oCItem* pItemChosen = NULL;
	int i;	

	switch ( this->SectionTrade )
	{
		// Selektiertes item vom Händler zum Spieler (Kaufen)
		case TRADE_SECTION_LEFT_INVENTORY:
			{
				// Transferanzahl initialisieren
				IncTransferCount(amount);
				oCItem* item = this->DlgInventoryNpc->GetSelectedItem();
				if ( item ) if ( item->GetAmount() <= amount )
				{
					amount = item->GetAmount();
					SetTransferCount(0);
				}
				
				// Items einzeln transferieren
				for (i = 0; i < amount; i++)
				{
					// Item beim Händler entfernen
					pItemChosen = this->DlgInventoryNpc->RemoveSelectedItem();
					if ( pItemChosen )
					{
						// Anzahl Währungseinheiten ermitteln, die der Spieler bezahlt
						// (wenn das Item überhaupt was kostet)
						int itemValue = pItemChosen->GetValue();
						int coinsToRemove = itemValue;
						// Item kostet was?
						if (coinsToRemove > 0)
						{
							// Invetar des Spilers holen
							oCNpcInventory* playerInventory = this->DlgInventoryPlayer->GetInventory();
							if (playerInventory)
							{
								// Hat der Spieler soviele Währungseinheiten?
								oCItem* coinItems = playerInventory->IsIn(oCItemContainer::GetCurrencyInstanceName(), coinsToRemove);
								if (coinItems)
								{
									// Währungseinheiten beim Spieler entfernen
									coinItems = playerInventory->Remove(oCItemContainer::GetCurrencyInstanceName(), coinsToRemove);
									if (coinItems)
									{
										oCItemContainer::RemoveCurrencyItem(coinItems);
										// Bezahlt
										coinsToRemove = 0;
									}
								}
							}

						}
						
						if (coinsToRemove == 0)
							// Das Item wurde bezahlt oder war umsonst,
							// ...gibt es dem Spieler
							this->DlgInventoryPlayer->InsertItem(pItemChosen);
						else
						{
							// Der Spieler kann sich das Item nicht leisten,
							// ...gib es dem Händler zurück
							this->DlgInventoryNpc->InsertItem(pItemChosen);
							
							// Refuse Action
							int refuseActionFunc = -1;
							refuseActionFunc = parser.GetIndex("PLAYER_TRADE_NOT_ENOUGH_GOLD");
							if (refuseActionFunc != -1)
								oCNpc::player->GetEM(TRUE)->OnMessage(zNEW(oCMsgManipulate)(oCMsgManipulate::EV_CALLSCRIPT, refuseActionFunc), oCNpc::player);
							else
								ogame->GetTextView()->Printwin("Nicht genug Gold um den Gegenstand zu kaufen.");
						}
					}
				}
			}
			break;	
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnSectionPrevious
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::OnSectionPrevious(void)
{
	switch (this->SectionTrade)
	{
	case TRADE_SECTION_LEFT_INVENTORY:
		this->OnSection(TRADE_SECTION_RIGHT_INVENTORY);
		break;
	case TRADE_SECTION_RIGHT_INVENTORY:
		this->OnSection(TRADE_SECTION_LEFT_INVENTORY);
		break;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnSectionNext
//
////////////////////////////////////////////////////////////////////////////////

zBOOL oCViewDialogTrade::OnSectionNext(void)
{
	switch (this->SectionTrade)
	{
	case TRADE_SECTION_LEFT_INVENTORY:
		this->OnSection(TRADE_SECTION_RIGHT_INVENTORY);
		break;
	case TRADE_SECTION_RIGHT_INVENTORY:
		this->OnSection(TRADE_SECTION_LEFT_INVENTORY);
		break;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnSection
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::OnSection(zTTradeSection enuSection)
{
	// Sektion setzen
	this->SectionTrade = enuSection;

	// Dialoge deaktivieren
	this->AllDialogsDisable();

	// Selektierten Dialog aktivieren
	switch (this->SectionTrade)
	{
		case TRADE_SECTION_LEFT_INVENTORY:
			this->DlgInventoryNpc->Activate(TRUE);
			break;

		case TRADE_SECTION_RIGHT_INVENTORY:
			this->DlgInventoryPlayer->Activate(TRUE);
			break;
	}

	// Immer Eingabefokus holen
	this->SetHandleEventTop();
}

////////////////////////////////////////////////////////////////////////////////
//
//	oCViewDialogTrade :: OnExit
//
////////////////////////////////////////////////////////////////////////////////

void oCViewDialogTrade::OnExit(void)
{
	// Deaktivieren
	this->Activate(FALSE);

	// Dialoge deaktivieren
	this->AllDialogsDisable();
	this->AllDialogsStop();

	// Spieler blokieren
	if (this->NpcRight)
		 this->NpcRight->SetMovLock(TRUE);

	// Handels-Container freigeben
	if (this->NpcLeft->trader) 
	{ 
		delete this->NpcLeft->trader;
		this->NpcLeft->trader = NULL;
	}

	if (this->NpcRight->trader) 
	{ 
		delete this->NpcRight->trader;
		this->NpcRight->trader = NULL; 
	}
	
	this->IsDone = TRUE;
}

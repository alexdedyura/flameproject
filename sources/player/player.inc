#include <..\..\sources\player\playerdata.inc>
#include <..\..\sources\player\authorization.inc>
#include <..\..\sources\player\spawn.inc>
#include <..\..\sources\player\rp_rating.inc>
#include <..\..\sources\player\death.inc>
#include <..\..\sources\player\actors.inc>
#include <..\..\sources\player\loading_texture.inc>
#include <..\..\sources\player\inv\inv.inc>
#include <..\..\sources\player\documents.inc>
#include <..\..\sources\player\quests.inc>
#include <..\..\sources\player\id_card.inc>
#include <..\..\sources\player\driving_licenses.inc>
#include <..\..\sources\player\bank_system.inc>
#include <..\..\sources\player\gps.pwn>

UpdatePlayerMoney(playerid, amount)
{
	pData[playerid][pMoney] += amount;
	if(pData[playerid][pMoney] < 0) pData[playerid][pMoney] = 0;
	ReloadPlayerMoney(playerid);
	SyncPlayerMoneyInventory(playerid);
	if(InventoryShowed[playerid]) RefreshInventoryWeightText(playerid);
	UpdateBaseInt("accounts", "money", pData[playerid][pMoney], pData[playerid][pID]);
	return true;
}

UpdatePlayerBankMoney(playerid, amount, positive)
{
	if (positive)
	{
		pData[playerid][pBankMoney] += amount;
	}
	else
	{
		pData[playerid][pBankMoney] -= amount;
	}
	UpdateBaseInt("accounts", "bank_money", pData[playerid][pBankMoney], pData[playerid][pID]);
	return true;
}

ReloadPlayerMoney(playerid)
{
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, pData[playerid][pMoney]);
    return true;
}

Player_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	
    if(!Logged[playerid]) return true;
    SaveInventory(playerid);
    return true;
}

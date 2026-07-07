#include <YSI_Coding\y_hooks>

hook OnPlayerDeath(playerid, killerid, reason)
{

	pData[playerid][pDeaths] ++;
	if(killerid != INVALID_PLAYER_ID) pData[killerid][pKills]++;
}
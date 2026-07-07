#include <YSI_Coding\y_hooks>

#define SPAWN_X -1423.4968
#define SPAWN_Y -289.9872
#define SPAWN_Z 14.1484

GotoSpawn(playerid)
{
    PlayerPlaySound(playerid, 0, 0.0, 0.0, 0.0);
	SetSpawnInfo(playerid, 0, pData[playerid][pDefault_Skin], SPAWN_X+random(3), SPAWN_Y+random(3), SPAWN_Z, random(3), 0, 0, 0, 0, 0, 0);
	SetPlayerSkin(playerid, pData[playerid][pDefault_Skin]);
	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) SpawnPlayer(playerid);
	else TogglePlayerSpectating(playerid, false);
	SendClientMessage(playerid, COLOR_FLAME, !"[SERVER]:"COLOR_WHITE" ¬ведите /help дл€ получени€ помощи по игровому моду и командам сервера.");
	SendClientMessage(playerid, COLOR_FLAME, !"[SERVER]:"COLOR_WHITE" ќткрыть инвентарь - Y | ќткрыть игровое меню - N");
	SendClientMessage(playerid, COLOR_FLAME, !"[SERVER]:"COLOR_WHITE" ќфициальный сайт сервера "WEBSITE"");
    UpdatePlayerWeapons(playerid);
	return true;
}

hook OnPlayerSpawn(playerid)
{
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);

    UpdatePlayerWeapons(playerid);
}

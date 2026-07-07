#include <YSI_Coding\y_hooks>

#define PAME_TIMEOUT_TIME 6 * 60 * 60 // 6 часов


hook OnPlayerSpawn(playerid)
{
    UpdatePlayerDescription(playerid);
}

CMD:pame_off(playerid, params[])
{
    pData[playerid][pDescText] = EOS;
    UpdatePlayerDescription(playerid);
    SendClientMessage(playerid, COLOR_GREY, "* ¬ы удалили описание персонажа!");
    return true;
}

CMD:pame(playerid, params[])
{
    if(gettime() - pData[playerid][pDescTime] < PAME_TIMEOUT_TIME)
        return SendClientMessage(playerid, COLOR_ERROR, "¬ы недавно использовали эту команду!");
    if(sscanf(params, "s[128]", params[0]))
        return SendClientMessage(playerid, COLOR_GREY,!"[SYNTAX]:"COLOR_WHITE" /pame [описание персонажа]");
    format(pData[playerid][pDescText], 128, "%s", params[0]);
    pData[playerid][pDescTime] = gettime();
    SaveAccount(playerid);
    SendClientMessage(playerid, -1, "¬ы установили "FLAME_COLOR"описание персонажа"COLOR_WHITE", дл€ его удалени€ введите команду "FLAME_COLOR"/pame_off"COLOR_WHITE"!");
    UpdatePlayerDescription(playerid);
    IncreasePlayerRPExp(playerid, 15);
    return true;
}


UpdatePlayerDescription(playerid)
{
    if(IsValidDynamic3DTextLabel(pData[playerid][pDescLabel]))
        DestroyDynamic3DTextLabel(pData[playerid][pDescLabel]);
    if(strlen(pData[playerid][pDescText]))
        pData[playerid][pDescLabel] = CreateDynamic3DTextLabel(pData[playerid][pDescText], COLOR_GREY, 0.0, 0.0, -1.0, 5.0, playerid, _, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    return true;
}

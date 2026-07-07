#include <YSI_Coding\y_hooks>

ShowPlayerGunLic(playerid, targetid)
{
    new string[64];
    format(string, sizeof(string), "Тут должна быть лицензия на оружие %s", pData[playerid][pName]);
    ShowPlayerDialog(targetid, 0, DIALOG_STYLE_MSGBOX, "Лицензия на оружие", string, !"OK", !"");
    return true;
}

ShowPlayerBizLic(playerid, targetid)
{
    new string[64];
    format(string, sizeof(string), "Тут должна быть лицензия на бизнес %s", pData[playerid][pName]);
    ShowPlayerDialog(targetid, 0, DIALOG_STYLE_MSGBOX, "Лицензия на бизнес", string, !"OK", !"");
    return true;
}

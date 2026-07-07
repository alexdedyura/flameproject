#include <YSI_Coding\y_hooks>

IncreasePlayerRPExp(playerid, amount)
{
    pData[playerid][pRPExp] += amount;
    new nextamount = 50 + 25 * pData[playerid][pRPLevel];
    while(pData[playerid][pRPExp] >= nextamount)
    {
        pData[playerid][pRPExp] -= nextamount;
        pData[playerid][pRPLevel] ++;
        SetPlayerScore(playerid, pData[playerid][pRPLevel]);
        SendClientMessage(playerid, -1, !"Ваш "FLAME_COLOR"РП рейтинг"COLOR_WHITE" повышен!");
        nextamount = 50 + 25 * pData[playerid][pRPLevel];
    }
    return true;
}

CMD:give_rating(playerid, params[])
{
	// Проверка на админа
	if(sscanf(params, "ii", params[0], params[1])) 
		return SendClientMessage(playerid, -1, !"/give_rating [id] [amount]");
	if(!IsPlayerConnected(params[0])) 
		return SendClientMessage(playerid, -1, !"Данный игрок не подключен!");
	if(!Logged[params[0]])
		return SendClientMessage(playerid, -1, !"Данный игрок не авторизован!");
	IncreasePlayerRPExp(params[0], params[1]);
	UpdateBaseInt("accounts", "rp_exp", pData[params[0]][pRPExp], pData[params[0]][pID]);
	UpdateBaseInt("accounts", "rp_level", pData[params[0]][pRPLevel], pData[params[0]][pID]);
	SendClientMessageEx(params[0], -1, "Администратор %s выдал Вам %i очков РП рейтинга.", pData[playerid][pName], params[1]);
	SendClientMessageEx(playerid, -1, "Вы выдали %s %i очков РП рейтинга.", pData[params[0]][pName], params[1]);
	return true;
}

CMD:rating(playerid)
{
	new string[512];
	format(string, sizeof(string), ""COLOR_WHITE"Уровень: "FLAME_COLOR"%i\n"COLOR_WHITE"EXP: "FLAME_COLOR"%i/%i\n"COLOR_WHITE"Чтобы повысить "FLAME_COLOR"RolePlay рейтинг"COLOR_WHITE" вам необходимо отыгрывать различные ситуации используя RP команды\n"FLAME_COLOR"(/me, /ame, /do, /todo, /action, /pame)"COLOR_WHITE"\nТакже вы можете оставить на форуме свои "FLAME_COLOR"случайные ситуации"COLOR_WHITE" за которые получите RP рейтинг.", pData[playerid][pRPLevel], pData[playerid][pRPExp],
		50 + 25*pData[playerid][pRPLevel]);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Role Play рейтинг", string, !"Закрыть", !"");
	return true;
}
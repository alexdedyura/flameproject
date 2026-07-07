#include <YSI_Coding\y_hooks>

#define RP_COMMANDS_TIMEOUT_TIME 15 // 15 секунд


CMD:me(playerid, params[])
{
    if(gettime() - pData[playerid][pRPAntiFloodTime] < 30)
        return SendClientMessage(playerid, -1, "Не флудите!");
    if(sscanf(params, "s[144]", params[0])) return SendClientMessage(playerid, COLOR_GREY,!"[SYNTAX]:"COLOR_WHITE" /me [действие]");
    if(!strcmp(LastCommandText[playerid], params, true) && strlen(params) && strlen(LastCommandText[playerid]))
    {
        if(GetPVarInt(playerid, "RPCommandsAntiFlood") >= 2)
        {
            pData[playerid][pRPAntiFloodTime] = gettime();
            SendClientMessageEx(playerid, -1, "РП команды заблокированы на "FLAME_COLOR"%i"COLOR_WHITE" секунд!", RP_COMMANDS_TIMEOUT_TIME);
            DeletePVar(playerid, "RPCommandsAntiFlood");
            return true;
        }
        SetPVarInt(playerid, "RPCommandsAntiFlood", GetPVarInt(playerid, "RPCommandsAntiFlood") + 1);
    }
    else DeletePVar(playerid, "RPCommandsAntiFlood");
    format(LastCommandText[playerid], 128, params[0]);
    MeAction(playerid, params[0]);
    IncreasePlayerRPExp(playerid, 3);
    return true;
}

MeAction(playerid,params[])
{
    if(strlen(params) > 64)
    {
        SendNearbyMessage(playerid, 20.0, 0xC2A2DAFF, "* %s %.64s...", pData[playerid][pName], params);
        SendNearbyMessage(playerid, 20.0, 0xC2A2DAFF, "...%s", params[64]);
    }
    else
        SendNearbyMessage(playerid, 20.0, 0xC2A2DAFF, "* %s %s", pData[playerid][pName], params);
    return true;
}

CMD:ame(playerid, params[])
{
    if(gettime() - pData[playerid][pRPAntiFloodTime] < 30)
        return SendClientMessage(playerid, -1, "Не флудите!");
    if(!strcmp(LastCommandText[playerid], params, true) && strlen(params) && strlen(LastCommandText[playerid]))
    {
        if(GetPVarInt(playerid, "RPCommandsAntiFlood") >= 2)
        {
            pData[playerid][pRPAntiFloodTime] = gettime();
            SendClientMessageEx(playerid, -1, "РП команды заблокированы на "FLAME_COLOR"%i"COLOR_WHITE" секунд!", RP_COMMANDS_TIMEOUT_TIME);
            DeletePVar(playerid, "RPCommandsAntiFlood");
            return true;
        }
        SetPVarInt(playerid, "RPCommandsAntiFlood", GetPVarInt(playerid, "RPCommandsAntiFlood") + 1);
    }
    else DeletePVar(playerid, "RPCommandsAntiFlood");
    format(LastCommandText[playerid], 128, params[0]);
    new string[144];
    if(sscanf(params, "s[144]", params[0])) return SendClientMessage(playerid, COLOR_GREY,!"[SYNTAX]:"COLOR_WHITE" /ame [действие]");
    format(string, sizeof(string), "%s %s",pData[playerid][pName], params[0]);
    SetPlayerChatBubble(playerid, string, 0xC2A2DAFF, 30.0, 10000);
    IncreasePlayerRPExp(playerid, 3);
    return true;
}
CMD:do(playerid, params[])
{
    if(gettime() - pData[playerid][pRPAntiFloodTime] < 30)
        return SendClientMessage(playerid, -1, "Не флудите!");
    if(!strcmp(LastCommandText[playerid], params, true) && strlen(params) && strlen(LastCommandText[playerid]))
    {
        if(GetPVarInt(playerid, "RPCommandsAntiFlood") >= 2)
        {
            pData[playerid][pRPAntiFloodTime] = gettime();
            SendClientMessageEx(playerid, -1, "РП команды заблокированы на "FLAME_COLOR"%i"COLOR_WHITE" секунд!", RP_COMMANDS_TIMEOUT_TIME);
            DeletePVar(playerid, "RPCommandsAntiFlood");
            return true;
        }
        SetPVarInt(playerid, "RPCommandsAntiFlood", GetPVarInt(playerid, "RPCommandsAntiFlood") + 1);
    }
    else DeletePVar(playerid, "RPCommandsAntiFlood");
    format(LastCommandText[playerid], 128, params[0]);
    if(sscanf(params, "s[144]", params)) return SendClientMessage(playerid, COLOR_GREY,!"[SYNTAX]:"COLOR_WHITE" /do [действие]");

    if (strlen(params) > 64)
    {
        SendNearbyMessage(playerid, 20.0, 0xC2A2DAFF, "* %.64s...", params);
        SendNearbyMessage(playerid, 20.0, 0xC2A2DAFF, "...%s (( %s ))", params[64], pData[playerid][pName]);
    }
    else SendNearbyMessage(playerid, 20.0, 0xC2A2DAFF, "* %s (( %s ))", params, pData[playerid][pName]);
    IncreasePlayerRPExp(playerid, 3);
    return true;
}

CMD:pm(playerid, params[])
{
    new PID, message[144], string[144];
    if(sscanf(params, "us[144]", PID, message)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /pm [ID] [Сообщение]");
    if(!pData[PID][pChatSettings][2]) return SendClientMessage(playerid, COLOR_GREY, !"* У данного игрока выключен приём сообщений!");
    if(playerid == PID) return SendClientMessage(playerid, COLOR_GREY,!"* Вы не можете писать сами себе");

    if(strlen(params) > 64)
    {
        new text1[65], text2[65];

        strmid(text2, params, 64, 128);
        strmid(text1, params, 0, 64);

        format(string, sizeof(string), "(( PM от %s(%d): %s ))", pData[PID][pName], PID, text1);
        SendClientMessage(playerid, 0xFFD700FF, string);
        format(string, sizeof(string), "... %s ))", text2);
        SendClientMessage(playerid, 0xFFD700FF, string);

        format(string, sizeof(string), "(( PM для %s(%d): %s ))", pData[playerid][pName], playerid, text1);
        SendClientMessage(PID, 0xFFD700FF, string);
        format(string, sizeof(string), "... %s ))", text2);
        SendClientMessage(PID, 0xFFD700FF, string);

    }
    else
    {
        format(string, sizeof(string), "(( PM от %s(%d): %s ))", pData[playerid][pName], playerid, message);
        SendClientMessage(PID, 0xFFD700FF, string);
        format(string, sizeof(string), "(( PM для %s(%d): %s ))", pData[PID][pName], PID, message);
        SendClientMessage(playerid, 0xFFD700FF, string);
    }
    return true;
}

hook OnPlayerText(playerid, text[])
{
	if(!Logged[playerid]) return false;
	if(text[0] == '!')
	{
		if(!pData[playerid][pChatSettings][0])
		{
			SendClientMessage(playerid, COLOR_GREY, !"* У Вас отключен этот чат!");
			return false;
		}
		foreach(new i : Player)
		{
			if(!pData[i][pChatSettings][0]) continue;
			SendClientMessageEx(i, -1, "%s(%i): {ffa500}%s", pData[playerid][pName], playerid, text[1]);
		}
	}
	else if(text[0] == '@')
	{
		if(!pData[playerid][pChatSettings][1])
		{
			SendClientMessage(playerid, COLOR_GREY, !"* У Вас отключен этот чат!");
			return false;
		}
		foreach(new i : Player)
		{
			if(!pData[i][pChatSettings][1]) continue;
			if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) SendClientMessageEx(i, -1, "%s(%i): {91ff00}%s", pData[playerid][pName], playerid, text[1]);
		}
	}
	else
	{
        if(GetPVarInt(playerid, !"ChatAnim"))
        {
            switch(GetPVarInt(playerid, !"ChatAnim"))
            {
                case 1: ApplyAnimation(playerid,"PED","IDLE_chat",4.1,false,true,true,true,1);
                case 2: ApplyAnimation(playerid,"GANGS","PRTIAL_GNGTLKA",4.1,false,true,true,true,1);
                case 3: ApplyAnimation(playerid,"GANGS","PRTIAL_GNGTLKB",4.1,false,true,true,true,1);
                case 4: ApplyAnimation(playerid,"GANGS","PRTIAL_GNGTLKD",4.1,false,true,true,true,1);
                case 5: ApplyAnimation(playerid,"GANGS","PRTIAL_GNGTLKE",4.1,false,true,true,true,1);
                case 6: ApplyAnimation(playerid,"GANGS","PRTIAL_GNGTLKF",4.1,false,true,true,true,1);
                case 7: ApplyAnimation(playerid,"GANGS","PRTIAL_GNGTLKG",4.1,false,true,true,true,1);
            }
            SetTimerEx("ResetAnims", 1400, false, "i", playerid);
        }
		if(strlen(text) > 64)
	    {
	        SendNearbyMessage(playerid, 20.0, -1, "%s "COLOR_WHITE"говорит:{B7AFAF} %.64s ...", pData[playerid][pName], text);
	        SendNearbyMessage(playerid, 20.0, 0xB7AFAFAA, "... %s", text[64]);
	    }
	    else SendNearbyMessage(playerid, 20.0, -1, "%s "COLOR_WHITE"говорит:{B7AFAF} %s", pData[playerid][pName], text);
	}
	return false;
}

CMD:m(playerid, params[])
{
    if(sscanf(params, "s[144]", params)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /m [текст]");
    SendNearbyMessage(playerid, 30.0, 0xFFFF00AA, ">> Мегафон %s: %s", pData[playerid][pName], params);
    return true;
}

CMD:r(playerid, params[])
{
	if(!GetPVarInt(playerid, !"RadioChannel")) return SendClientMessage(playerid, -1, !"Вы не настроили волну. Используйте /channel");
	if(sscanf(params, "s[144]", params)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]: "COLOR_WHITE"/r [текст]");
	foreach(new i : Player)
	{
		if(GetPVarInt(playerid, !"RadioChannel") == GetPVarInt(i, !"RadioChannel")) SendClientMessageEx(i, 0x0080bcFF, "** [Рация: %i] %s: %s **", GetPVarInt(playerid, !"RadioChannel"), pData[playerid][pName], params);
	}
	return true;
}

CMD:channel(playerid, params[])
{
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]: "COLOR_WHITE"/channel [номер]");
	if(params[0] < 0 || params[0] > 100000) return SendClientMessage(playerid, COLOR_GREY, !"* Номер канала от 0 до 100.000!");
	SetPVarInt(playerid, !"RadioChannel", params[0]);
	SendClientMessageEx(playerid, 0xff6600FF, "[SERVER]: "COLOR_WHITE"Вы установили радиоканал %i (\"/r [текст]\").", params[0]);
	return true;
}
/*
CMD:mute(playerid, params[])
{
	new string[128];
	format(string, sizeof(string), "1. Test\t[ %s ]\n2. Test\t[ %s ]\n3. Test\t[ %s ]\n4. Test\t[ %s ]\n5. Сохранять при выходе\t[ %s ]",
		(pData[playerid][pChatSettings][0]) ? ("ON") : ("OFF"), (pData[playerid][pChatSettings][1]) ? ("ON") : ("OFF"), (pData[playerid][pChatSettings][2]) ? ("ON") : ("OFF"),
		(pData[playerid][pChatSettings][3]) ? ("ON") : ("OFF"), (pData[playerid][pChatSettings][4]) ? ("ON") : ("OFF"));
	ShowPlayerDialog(playerid, D_MUTE, DIALOG_STYLE_TABLIST, !"Настройки чата", string, !"Изменить", !"Отмена");
}*/

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_MUTE)
	{
		if(!response) return true;
		pData[playerid][pChatSettings][listitem] = !pData[playerid][pChatSettings][listitem];
		new string[128];
		format(string, sizeof(string), "%i %i %i %i %i", pData[playerid][pChatSettings][0], pData[playerid][pChatSettings][1], pData[playerid][pChatSettings][2], pData[playerid][pChatSettings][3], pData[playerid][pChatSettings][4]);
		UpdateBaseStr("accounts", "ChatSettings", string, pData[playerid][pID]);
		format(string, sizeof(string), "1. Test\t[ %s ]\n2. Test\t[ %s ]\n3. Test\t[ %s ]\n4. Test\t[ %s ]\n5. Сохранять при выходе\t[ %s ]",
			(pData[playerid][pChatSettings][0]) ? ("ON") : ("OFF"), (pData[playerid][pChatSettings][1]) ? ("ON") : ("OFF"), (pData[playerid][pChatSettings][2]) ? ("ON") : ("OFF"),
			(pData[playerid][pChatSettings][3]) ? ("ON") : ("OFF"), (pData[playerid][pChatSettings][4]) ? ("ON") : ("OFF"));
		ShowPlayerDialog(playerid, D_MUTE, DIALOG_STYLE_TABLIST, !"Настройки чата", string, !"Изменить", !"Отмена");
	}
	return true;
}

CMD:b(playerid, params[])
{
    if(sscanf(params, "s[144]", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /b [текст]");

    if(strlen(params) > 64)
    {
        SendNearbyMessage(playerid, 20.0, -1, "(( %s: %.64s...", pData[playerid][pName], params);
        SendNearbyMessage(playerid, 20.0, -1, "...%s ))", params[64]);
    }
    else SendNearbyMessage(playerid, 20.0, -1, "(( %s: %s ))", pData[playerid][pName], params);
    return true;
}

CMD:l(playerid, params[]) return cmd_low(playerid, params);
CMD:low(playerid, params[])
{
    if(sscanf(params, "s[144]", params)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /(l)ow [текст]");
    if (strlen(params) > 64)
    {
        SendNearbyMessage(playerid, 2.0, 0x65969AAA, "%s говорит[тихо]: %.64s...", pData[playerid][pName], params);
        SendNearbyMessage(playerid, 2.0, 0x65969AAA, "...%s", params[64]);
    }
    else SendNearbyMessage(playerid, 2.0, 0x65969AAA, "%s говорит[тихо]: %s", pData[playerid][pName], params);
    return true;
}
  
CMD:w(playerid, params[]) return cmd_whisper(playerid, params);
CMD:whisper(playerid, params[])
{
    new PID, message[144], string[144];
    if(sscanf(params, "us[144]", PID, message)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /(w)hsiper [ID] [Сообщение]");
    if(playerid == PID) return SendClientMessage(playerid, COLOR_GREY,!"* Вы не можете шептать сами себе");
    if(!DistancePlayer(5.0, playerid, PID)) return SendClientMessage(playerid, COLOR_GREY, !"* Вы слишком далеко от игрока.");
    if(strlen(params) > 64)
    {
        new text1[65], text2[65];

        strmid(text2, params, 64, 128);
        strmid(text1, params, 0, 64);

        format(string, sizeof(string), "%s(%d) прошептал Вам: %s", pData[PID][pName], PID, text1);
        SendClientMessage(playerid, 0xFFD700FF, string);
        format(string, sizeof(string), "... %s", text2);
        SendClientMessage(playerid, 0xFFD700FF, string);

        format(string, sizeof(string), "Вы прошептали %s(%d): %s", pData[playerid][pName], playerid, text1);
        SendClientMessage(PID, 0xFFD700FF, string);
        format(string, sizeof(string), "... %s", text2);
        SendClientMessage(PID, 0xFFD700FF, string);

    }
    else
    {
        format(string, sizeof(string), "%s(%d) прошептал Вам: %s", pData[playerid][pName], playerid, message);
        SendClientMessage(PID, 0xFFD700FF, string);
        format(string, sizeof(string), "Вы прошептали %s(%d): %s", pData[PID][pName], PID, message);
        SendClientMessage(playerid, 0xFFD700FF, string);
    }
    return true;
}

CMD:s(playerid, params[]) return cmd_shout(playerid, params);
CMD:shout(playerid, params[])
{
    if(sscanf(params, "s[144]", params)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /(s)hout [текст]");
    if (strlen(params) > 64)
    {
        SendNearbyMessage(playerid, 30.0, -1, "%s кричит: %.64s...", pData[playerid][pName], params);
        SendNearbyMessage(playerid, 30.0, -1, "...%s!", params[64]);
    }
    else SendNearbyMessage(playerid, 30.0, -1, "%s кричит: %s!", pData[playerid][pName], params);
    return true;
}

forward ResetAnims(playerid);
public ResetAnims(playerid)
{
    ApplyAnimation(playerid,"CARRY","crry_prtial",4.0,false,false,false,false,0,0);
    return 1;
}

CMD:action(playerid, params[])
{
    if(sscanf(params, "s[144]", params[0])) return SendClientMessage(playerid, COLOR_GREY,!"[SYNTAX]:"COLOR_WHITE" /action [действие]");
    if(!strlen(params))
    {
        if(IsValidDynamic3DTextLabel(pData[playerid][pActionLabel]))
        {
            DestroyDynamic3DTextLabel(pData[playerid][pActionLabel]);
            SendClientMessage(playerid, -1, !"Вы удалили действие!");
        }
        return true;
    }
    if(gettime() - pData[playerid][pRPAntiFloodTime] < 30)
        return SendClientMessage(playerid, -1, "Не флудите!");    
    if(!strcmp(LastCommandText[playerid], params, true) && strlen(params) && strlen(LastCommandText[playerid]))
    {
        if(GetPVarInt(playerid, "RPCommandsAntiFlood") >= 2)
        {
            pData[playerid][pRPAntiFloodTime] = gettime();
            SendClientMessageEx(playerid, -1, "РП команды заблокированы на "FLAME_COLOR"%i"COLOR_WHITE" секунд!", RP_COMMANDS_TIMEOUT_TIME);
            DeletePVar(playerid, "RPCommandsAntiFlood");
            return true;
        }
        SetPVarInt(playerid, "RPCommandsAntiFlood", GetPVarInt(playerid, "RPCommandsAntiFlood") + 1);
    }
    else DeletePVar(playerid, "RPCommandsAntiFlood");
    format(LastCommandText[playerid], 128, params[0]);
    if(IsValidDynamic3DTextLabel(pData[playerid][pActionLabel]))
        DestroyDynamic3DTextLabel(pData[playerid][pActionLabel]);
    new text[144];
    format(text, sizeof(text), "%s\n(( %s[%i] ))", params, pData[playerid][pName], playerid);
    new Float:posX, Float:posY, Float:posZ;
    GetPlayerPos(playerid, posX, posY, posZ);
    pData[playerid][pActionLabel] = 
        CreateDynamic3DTextLabel(text, 0xC2A2DAFF, posX, posY, posZ - 0.5, 7.5, _, _, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    Streamer_Update(playerid);
    IncreasePlayerRPExp(playerid, 5);
    return true;
}

CMD:caraction(playerid, params[])
{
    if(!IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, -1, !"Вы не в транспорте!");
    new vehid = GetPlayerVehicleID(playerid);
    if(!strlen(params))
    {
        if(IsValidDynamic3DTextLabel(CarActionLabel[vehid]))
        {
            DestroyDynamic3DTextLabel(CarActionLabel[vehid]);
            SendClientMessage(playerid, -1, !"Вы удалили действие!");
        }
        return true;
    }
    if(!strcmp(LastCommandText[playerid], params, true) && strlen(params) && strlen(LastCommandText[playerid]))
    {
        if(GetPVarInt(playerid, "RPCommandsAntiFlood") >= 2)
        {
            pData[playerid][pRPAntiFloodTime] = gettime();
            SendClientMessageEx(playerid, -1, "РП команды заблокированы на "FLAME_COLOR"%i"COLOR_WHITE" секунд!", RP_COMMANDS_TIMEOUT_TIME);
            DeletePVar(playerid, "RPCommandsAntiFlood");
            return true;
        }
        SetPVarInt(playerid, "RPCommandsAntiFlood", GetPVarInt(playerid, "RPCommandsAntiFlood") + 1);
    }
    else DeletePVar(playerid, "RPCommandsAntiFlood");
    format(LastCommandText[playerid], 128, params[0]);
    if(gettime() - pData[playerid][pRPAntiFloodTime] < 30)
        return SendClientMessage(playerid, -1, "Не флудите!");    

    if(IsValidDynamic3DTextLabel(CarActionLabel[vehid]))
        DestroyDynamic3DTextLabel(CarActionLabel[vehid]);
    new text[144];
    format(text, sizeof(text), "%s\n(( %s[%i] ))", params, pData[playerid][pName], playerid);
    CarActionLabel[vehid] = 
        CreateDynamic3DTextLabel(text, 0xC2A2DAFF, 0.0, 0.0, 0.0, 7.5, _, vehid, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    Streamer_Update(playerid);
    IncreasePlayerRPExp(playerid, 5);
    return true;
}


hook OnVehicleSpawn(vehicleid)
{
    if(IsValidDynamic3DTextLabel(CarActionLabel[vehicleid]))
        DestroyDynamic3DTextLabel(CarActionLabel[vehicleid]);
}
#include <YSI_Coding\y_hooks>

#define _MAX_ACTORS 150

enum actorinfo
{
	aID,
	aSkin,
    aInv,
	aName[32],
    Float:aPosX,
    Float:aPosY,
    Float:aPosZ,
    Float:aPosFA,
    aInt,
    aVW,
	Text3D:aText,
    aActorID
}
new ActorsInfo[_MAX_ACTORS+1][actorinfo];

CMD:actor(playerid, params[])
{
	if(strlen(params) && !strcmp(params, "create", true))
	{
		for(new i = 1; i <= _MAX_ACTORS; i++)
		{
			if(ActorsInfo[i][aID] == 0)
			{
				ClearActorInfo(i);
				ActorsInfo[i][aSkin] = 1 + random(310);
				GetPlayerPos(playerid, ActorsInfo[i][aPosX], ActorsInfo[i][aPosY], ActorsInfo[i][aPosZ]);
				GetPlayerFacingAngle(playerid, ActorsInfo[i][aPosFA]);
				SendClientMessageEx(playerid, -1, "Вы создали актёра №%i.", i);
                new ms_string[256];
                new __ms15[] = "INSERT INTO `actors` (`skin`) VALUES ('%i')";
                mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms15, ActorsInfo[i][aSkin]);
                new __ms13[] = "ReturnActorID";
                new __ms14[] = "i";
                mysql_tquery(ConnectMySQL, ms_string, __ms13, __ms14, i);
                SaveActor(i);
                UpdateActor(i);
				return true;
			}
		}
		SendClientMessage(playerid, COLOR_GREY, !"* Превышен лимит актёров!");
		return true;
	}
	new actorid = strval(params);
	if(!actorid)
		return SendClientMessage(playerid, -1, "/actor [id]");
	if(actorid <= 0 || params[0] > _MAX_ACTORS) return SendClientMessage(playerid, COLOR_GREY, !"* Неверный номер актёра!");
	if(!ActorsInfo[actorid-1][aID]) return SendClientMessage(playerid, COLOR_GREY, !"* Неверный номер актёра!");
	ShowPlayerActorSettings(playerid, actorid-1);
	return true;
}

forward ReturnActorID(aid);
public ReturnActorID(aid)
{
    ActorsInfo[aid][aID] = cache_insert_id();
}

ClearActorInfo(aid)
{
	ActorsInfo[aid][aID] = 0;
    ActorsInfo[aid][aSkin] = 0;
    ActorsInfo[aid][aInv] = 0;
    ActorsInfo[aid][aName] = EOS;
    ActorsInfo[aid][aPosX] = 0.0;
    ActorsInfo[aid][aPosY] = 0.0;
    ActorsInfo[aid][aPosZ] = 0.0;
    ActorsInfo[aid][aPosFA] = 0.0;
    ActorsInfo[aid][aInt] = 0;
    ActorsInfo[aid][aVW] = 0;
	return true;
}

ShowPlayerActorSettings(playerid, actorid)
{
	new string[128];
	format(string, sizeof(string), "Статус\t[%s]\n\
		Телепортировать к себе\n\
		Установить скин\t[%i]\n\
		Установить имя\n\
		Удалить актёра",
		(ActorsInfo[actorid][aInv]) ? ("Неуязвим") : ("Уязвим"),
		ActorsInfo[actorid][aSkin]);
	new sstring[20];
	format(sstring, sizeof(sstring), "Меню актёра №%i", ActorsInfo[actorid][aID]);
	SetPVarInt(playerid, !"ActorSettingsID", actorid);
	ShowPlayerDialog(playerid, D_ACTORS_MENU, DIALOG_STYLE_TABLIST, sstring, string, !"Далее", !"Закрыть");
	return true;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_ACTORS_MENU)
	{
		if(!response) return true;
		new aid = GetPVarInt(playerid, !"ActorSettingsID");
		switch(listitem)
		{
			case 0: // Статус
			{
                ActorsInfo[aid][aInv] = !ActorsInfo[aid][aInv];
				SetDynamicActorInvulnerable(ActorsInfo[aid][aActorID], ActorsInfo[aid][aInv]);
                SaveActor(aid);
				ShowPlayerActorSettings(playerid, aid);
			}
			case 1: // ТП к себе
			{
				GetPlayerPos(playerid, ActorsInfo[aid][aPosX], ActorsInfo[aid][aPosY], ActorsInfo[aid][aPosZ]);
				GetPlayerFacingAngle(playerid, ActorsInfo[aid][aPosFA]);
				UpdateActor(aid);
                SaveActor(aid);
			}
			case 2: // Установить скин
			{
				ShowPlayerDialog(playerid, D_ACTORS_SKIN, DIALOG_STYLE_INPUT, !"Изменение скина актёра", !""COLOR_WHITE"Введите номер желаемого скина", !"Далее", !"Отмена");
			}
			case 3: // Установить имя
			{
				ShowPlayerDialog(playerid, D_ACTORS_NAME, DIALOG_STYLE_INPUT, !"Изменение имени актёра", !""COLOR_WHITE"Введите желаемое имя\n", !"Далее", !"Отмена");
			}
			case 4: // Удалить актёра
			{
                new ms_string[128];
                new __ms12[] = "DELETE FROM `actors` WHERE `id` = '%i'";
                mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms12, ActorsInfo[aid][aID]);
                mysql_tquery(ConnectMySQL, ms_string);
				ClearActorInfo(aid);
                UpdateActor(aid);
				SendClientMessageEx(playerid, -1, "Вы удалили актёра №%i", aid+1);
			}
		}
	}
	else if(dialogid == D_ACTORS_SKIN)
	{
		if(!response) return ShowPlayerActorSettings(playerid, GetPVarInt(playerid, !"ActorSettingsID"));
		if(strval(inputtext) < 1 || strval(inputtext) > 311)
		{
			ShowPlayerDialog(playerid, D_ACTORS_SKIN, DIALOG_STYLE_INPUT, !"Изменение скина актёра", !""COLOR_WHITE"Введите номер желаемого скина", !"Далее", !"Отмена");
			return true;
		}
        new aid = GetPVarInt(playerid, !"ActorSettingsID");
		ActorsInfo[aid][aSkin] = strval(inputtext);
		UpdateActor(aid);
        SaveActor(aid);
		ShowPlayerActorSettings(playerid, aid);
	}
	else if(dialogid == D_ACTORS_NAME)
	{
		if(!response) return ShowPlayerActorSettings(playerid, GetPVarInt(playerid, !"ActorSettingsID"));
        new aid = GetPVarInt(playerid, !"ActorSettingsID");
		if(!strlen(inputtext))
		{
			ActorsInfo[aid][aName] = EOS;
            UpdateActor(aid);
            SaveActor(aid);
			SendClientMessage(playerid, -1, !"Вы удалили имя актёра!");
		}
		else
		{
			format(ActorsInfo[aid][aName], 32, "%s", inputtext);
            UpdateActor(aid);
            SaveActor(aid);
		}
	}
	return true;
}

UpdateActor(aid)
{
    if(IsValidDynamicActor(ActorsInfo[aid][aActorID])) DestroyDynamicActor(ActorsInfo[aid][aActorID]);
    if(IsValidDynamic3DTextLabel(ActorsInfo[aid][aText])) DestroyDynamic3DTextLabel(ActorsInfo[aid][aText]);
    if(!ActorsInfo[aid][aID]) return true;
    ActorsInfo[aid][aActorID] = CreateDynamicActor(ActorsInfo[aid][aSkin], ActorsInfo[aid][aPosX], ActorsInfo[aid][aPosY], ActorsInfo[aid][aPosZ], ActorsInfo[aid][aPosFA], ActorsInfo[aid][aInv], 100.0,
        ActorsInfo[aid][aVW], ActorsInfo[aid][aInt]);
    ActorsInfo[aid][aText] = CreateDynamic3DTextLabel(ActorsInfo[aid][aName], 0xFFFFFFFF, ActorsInfo[aid][aPosX], ActorsInfo[aid][aPosY], ActorsInfo[aid][aPosZ]+0.5, 3.0, _, _, 1, ActorsInfo[aid][aVW], ActorsInfo[aid][aInt]);
    return true;
}

SaveActor(aid)
{
    new ms_string[512] = "UPDATE `actors` SET";
    new __ms11[] = "%s `skin` = '%i'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms11, ms_string, ActorsInfo[aid][aSkin]);
    new __ms10[] = "%s, `name` = '%s'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms10, ms_string, ActorsInfo[aid][aName]);
    new __ms9[] = "%s, `inv` = '%i'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms9, ms_string, ActorsInfo[aid][aInv]);
    new __ms8[] = "%s, `posX` = '%f'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms8, ms_string, ActorsInfo[aid][aPosX]);
    new __ms7[] = "%s, `posY` = '%f'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms7, ms_string, ActorsInfo[aid][aPosY]);
    new __ms6[] = "%s, `posZ` = '%f'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms6, ms_string, ActorsInfo[aid][aPosZ]);
    new __ms5[] = "%s, `posFA` = '%f'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms5, ms_string, ActorsInfo[aid][aPosFA]);
    new __ms4[] = "%s, `vw` = '%i'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms4, ms_string, ActorsInfo[aid][aVW]);
    new __ms3[] = "%s, `int` = '%i'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms3, ms_string, ActorsInfo[aid][aInt]);

    new __ms2[] = "%s WHERE `id` = '%i'";
    mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms2, ms_string, ActorsInfo[aid][aID]);
    mysql_tquery(ConnectMySQL, ms_string);
    return true;
}


hook OnGameModeInit()
{
	new __ms0[] = "SELECT * FROM `actors`";
	new __ms1[] = "LoadActors";
	mysql_tquery(ConnectMySQL, __ms0, __ms1);
}


forward LoadActors();
public LoadActors()
{
	new rows = cache_get_row_count();
	for(new i = 0; i < rows; i++)
	{
		ActorsInfo[i][aID] = cache_get_field_content_int(i, "id");
		ActorsInfo[i][aSkin] = cache_get_field_content_int(i, "skin");
		cache_get_field_content(i, "name", ActorsInfo[i][aName], ConnectMySQL, 32);
		ActorsInfo[i][aInv] = cache_get_field_content_int(i, "inv");
		ActorsInfo[i][aPosX] = cache_get_field_content_float(i, "posX");
		ActorsInfo[i][aPosY] = cache_get_field_content_float(i, "posY");
		ActorsInfo[i][aPosZ] = cache_get_field_content_float(i, "posZ");
		ActorsInfo[i][aPosFA] = cache_get_field_content_float(i, "posFA");
		ActorsInfo[i][aVW] = cache_get_field_content_int(i, "vw");
		ActorsInfo[i][aInt] = cache_get_field_content_int(i, "int");

		UpdateActor(i);
	}
	return true;
}

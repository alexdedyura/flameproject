#include <YSI_Coding\y_hooks>

#define CHOOSE_SKIN_POS 2068.7715, 1235.3546, 1019.0800
#define CHOOSE_SKIN_FA 229.4997

#define CHOOSE_SKIN_CAM_POS 2071.4302, 1233.3101, 1020.0800
#define CHOOSE_SKIN_CAM_LOOK 2068.7715, 1235.3546, 1019.0800

#define REG_START_MONEY 200
#define MAX_AUTH_TRIES 3

enum E_REG_DATA
{
	bool:regChoosingSkin,
	regSkinIndex,
	regConnectCamera,
	regAuthTries
}
new RegData[MAX_PLAYERS][E_REG_DATA];

static const reg_skins[][] =
{
	{1, 2, 3, 8, 15, 20, 23, 26, 29, 30, 32, 33, 34, 37, 43, 44, 45, 46, 47, 48, 50, 57, 58, 59, 60, 61, 62, 68, 72, 73, 78, 79, 81, 82, 94, 95, 96, 97, 98, 100,
	 101, 108, 109, 110, 114, 115, 116, 128, 132, 133, 135, 137, 146, 147, 153, 154, 158, 159, 160, 161, 162, 170, 171, 177, 181, 184, 185, 186, 187, 188, 189, 200,
	  202, 203, 204, 206, 208, 209, 210, 212, 213, 217, 223, 227, 228, 229, 230, 234, 235, 236, 239, 340, 241, 242, 247, 248, 249, 250, 252, 254, 255, 258, 259, 261, 272, 273, 289, 290, 291, 292, 294, 295, 299,
	   303, 304, 305, 4, 5, 6, 7, 14, 17, 18, 19, 21, 22, 24, 25, 28, 35, 36, 66, 67, 80, 83, 84, 86, 102, 103, 104, 105, 106, 107, 134, 136, 142, 143, 144, 149,
	 156, 168, 178, 180, 182, 220, 221, 222, 253, 262, 269, 270, 271, 293, 296, 297, -1},
	{11, 12, 31, 38, 39, 40, 41, 53, 54, 55, 56, 63, 64, 75, 77, 85, 88, 89, 90, 91, 93, 129, 130, 131, 138, 140, 141, 145, 148, 150,
	 151, 152, 157, 169, 172, 192, 193, 194, 196, 197, 198, 199, 201, 211, 214, 216, 224, 225,
	  226, 231, 232, 233, 237, 251, 263, 298, 9, 10, 13, 65, 69, 139, 190, 195, 207, 215, 218, 219, 238, 243, 244, 245, 256, -1}
};

// ===== UI helpers ===========================================================

ShowSkinSelectionTextDraws(playerid)
{
	for(new i; i < sizeof(ChooseSkinTD); i++) TextDrawShowForPlayer(playerid, ChooseSkinTD[i]);
}

HideSkinSelectionTextDraws(playerid)
{
	for(new i; i < sizeof(ChooseSkinTD); i++) TextDrawHideForPlayer(playerid, ChooseSkinTD[i]);
}

ApplySkinSelectionView(playerid)
{
	RegData[playerid][regSkinIndex] = 0;
	SetPlayerSkin(playerid, reg_skins[pData[playerid][pGender]-1][0]);
	TogglePlayerControllable(playerid, false);
	SetPlayerPos(playerid, CHOOSE_SKIN_POS);
	SetPlayerFacingAngle(playerid, CHOOSE_SKIN_FA);
	SetPlayerCameraPos(playerid, CHOOSE_SKIN_CAM_POS);
	SetPlayerCameraLookAt(playerid, CHOOSE_SKIN_CAM_LOOK);
	ShowSkinSelectionTextDraws(playerid);
	SelectTextDraw(playerid, 0xFFFFFFAA);
}

ShowRegisterPasswordDialog(playerid)
{
	new string[512];
	strcat(string, ""COLOR_WHITE"Вы подключились к ролевому серверу "FLAME_COLOR"Flame Project\n\n");
	strcat(string, ""COLOR_WHITE"Данный аккаунт "FLAME_COLOR"не зарегистрирован\n");
	strcat(string, ""COLOR_WHITE"Регистрируясь, Вы автоматически соглашаетесь с правилами сервера "FLAME_COLOR""WEBSITE"/rules\n");
	strcat(string, ""COLOR_WHITE"Для продолжения регистрации, придумайте пароль:\n\n");
	strcat(string, ""COLOR_WHITE"Пароль может содержать цифры и латинские буквы разного регистра от 8 до 20 символов.\n");
	strcat(string, ""COLOR_WHITE"Для Вашей безопасности мы рекомендуем использовать сложные пароли.\n");
	ShowPlayerDialog(playerid, D_REG_PASS, DIALOG_STYLE_INPUT, !"Регистрация", string, !"Далее", !"");
}

ShowAuthDialog(playerid)
{
	new string[256];
	strcat(string, ""COLOR_WHITE"Вы подключились к ролевому серверу "FLAME_COLOR"Flame Project\n\n");
	strcat(string, ""COLOR_WHITE"Данный аккаунт "FLAME_COLOR"зарегистрирован\n");
	strcat(string, ""COLOR_WHITE"Для продолжения авторизации, введите пароль:\n");
	ShowPlayerDialog(playerid, D_AUTH_PASS, DIALOG_STYLE_INPUT, !"Авторизация", string, !"Далее", !"");
}

ShowRegMailDialog(playerid)
{
	ShowPlayerDialog(playerid, D_REG_MAIL, DIALOG_STYLE_INPUT, !"Регистрация: Электронная почта.", !""COLOR_WHITE"Укажите вашу основную "FLAME_COLOR"электронную почту\n"COLOR_WHITE"В дальнейшем с помощью почтового ящика Вы сможете восстановить утерянный пароль или изменить текущий.\n\n"COLOR_WHITE"Рекомендуем использовать почтовые ящики сервисов "FLAME_COLOR"Yandex.com, Mail.com, Gmail.com", !"Далее", !"Отмена");
}

ShowRegGenderDialog(playerid)
{
	ShowPlayerDialog(playerid, D_REG_GENDER, DIALOG_STYLE_LIST, !"Регистрация: Выбор пола", !""FLAME_COLOR"1. "COLOR_WHITE"Мужской\n"FLAME_COLOR"2. "COLOR_WHITE"Женский", !"Далее", !"Отмена");
}

ShowRegAgeDialog(playerid)
{
	ShowPlayerDialog(playerid, D_REG_AGE, DIALOG_STYLE_INPUT, !"Регистрация: Выбор возраста", !""COLOR_WHITE"Введите желаемый возраст персонажа "FLAME_COLOR"(от 16 до 90 лет)", !"Далее", !"Отмена");
}

// ===== registration / load flow =============================================

static StartRegistrationSkinSelection(playerid)
{
	RegData[playerid][regChoosingSkin] = true;
	TogglePlayerSpectating(playerid, false);
	ApplySkinSelectionView(playerid);
	SetPlayerVirtualWorld(playerid, playerid + 1000);
	return true;
}

RegisterAccount(playerid)
{
	new ms_string[256];
	new query[] = "INSERT INTO `accounts` (`name`, `password`, `mail`, `gender`, \
		`default_skin`, `age`, `reg_ip`, `money`, `bank_money`, `bank_last_use`) VALUES ('%s', '%s', '%s', '%i', '%i', '%i', '%e', '%i', '0', '0')";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), query, pData[playerid][pName], pData[playerid][pPassword], pData[playerid][pEmail], pData[playerid][pGender], pData[playerid][pDefault_Skin], pData[playerid][pAge], pData[playerid][pRegIP], REG_START_MONEY);
	new cb[] = "ReturnRegisteredID", spec[] = "i";
	mysql_tquery(ConnectMySQL, ms_string, cb, spec, playerid);
}

LoadAccountById(playerid)
{
	new ms_string[96];
	new query[] = "SELECT * FROM `accounts` WHERE `id` = '%i' LIMIT 1";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), query, pData[playerid][pID]);
	new cb[] = "LoadAccount", spec[] = "i";
	mysql_tquery(ConnectMySQL, ms_string, cb, spec, playerid);
}

LoadInventoryColumn(playerid, const field[], inventory_info:col)
{
	new temp[128], array[15];
	cache_get_field_content(0, field, temp);
	sscanf(temp, "a<i>[15]", array);
	for(new i; i < 15; i++) PlayerInventory[playerid][i][col] = array[i];
}

// ===== callbacks ============================================================

hook OnPlayerConnect(playerid)
{
	//PlayerPlaySound(playerid, 1187, 0, 0, 0); // необходимо исправить, звук остается после авторизации
	RegData[playerid][regChoosingSkin] = false;
	RegData[playerid][regSkinIndex] = 0;
	RegData[playerid][regConnectCamera] = -1;
	RegData[playerid][regAuthTries] = 0;

	SetSpawnInfo(playerid, 0, 2, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(playerid, true);
	ClearPlayerData(playerid);
	SetTimerEx("ConnectCamera", 200, false, "i", playerid);
	GetPlayerName(playerid, pData[playerid][pName], 24);
	SetTimerEx("AuthCheck", 648000, false, "i", playerid);

	new ms_string[128];
	new query[] = "SELECT * FROM `accounts` WHERE `name` = '%s'";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), query, pData[playerid][pName]);
	new cb[] = "CheckAccountReg", spec[] = "i";
	mysql_tquery(ConnectMySQL, ms_string, cb, spec, playerid);
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_REG_PASS)
	{
		if(!response)
		{
			ShowRegisterPasswordDialog(playerid);
			return true;
		}
		new len = strlen(inputtext);
		if(len < 8 || len > 20)
		{
			SendClientMessage(playerid, COLOR_ERROR, !"* Длина пароля от 8 до 20 символов!");
			ShowRegisterPasswordDialog(playerid);
			return true;
		}
		for(new i; i < len; i++)
		{
			switch(inputtext[i])
			{
				case 'a'..'z', 'A'..'Z', '0'..'9': continue;
				default:
				{
					SendClientMessage(playerid, COLOR_ERROR, !"* Пароль содержит недопустимые символы!");
					ShowRegisterPasswordDialog(playerid);
					return true;
				}
			}
		}
		format(pData[playerid][pPassword], 32, "%s", inputtext);
		ShowRegMailDialog(playerid);
	}
	else if(dialogid == D_REG_MAIL)
	{
		if(!response || !strlen(inputtext) || strlen(inputtext) > 32)
		{
			ShowRegMailDialog(playerid);
			return true;
		}
		new symb1 = 0, symb2 = 0;
		for(new i, len = strlen(inputtext); i < len; i++)
		{
			switch(inputtext[i])
			{
				case 'A'..'Z', 'a'..'z', '0'..'9': continue;
				case '.': symb1++;
				case '@': symb2++;
				default:
				{
					SendClientMessage(playerid, COLOR_GREY, !"* Почта содержит недопустимые символы!");
					ShowRegMailDialog(playerid);
					return true;
				}
			}
		}
		if(symb1 != 1 || symb2 != 1)
		{
			ShowRegMailDialog(playerid);
			return true;
		}

		new ms_string[256];
		new query[] = "SELECT id FROM accounts WHERE mail = '%e'";
		mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), query, inputtext);
		new cb[] = "CheckPlayerMail", spec[] = "is";
		mysql_tquery(ConnectMySQL, ms_string, cb, spec, playerid, inputtext);
	}
	else if(dialogid == D_REG_GENDER)
	{
		if(!response)
		{
			ShowRegGenderDialog(playerid);
			return true;
		}
		pData[playerid][pGender] = listitem+1;
		ShowRegAgeDialog(playerid);
	}
	else if(dialogid == D_REG_AGE)
	{
		if(!response || strval(inputtext) < 16 || strval(inputtext) > 90)
		{
			ShowRegAgeDialog(playerid);
			return true;
		}
		pData[playerid][pAge] = strval(inputtext);
		StartRegistrationSkinSelection(playerid);
	}
	else if(dialogid == D_AUTH_PASS)
	{
		if(!response || !strlen(inputtext))
		{
			ShowAuthDialog(playerid);
			return true;
		}
		if(strcmp(inputtext, pData[playerid][pPassword]) != 0)
		{
			RegData[playerid][regAuthTries]++;
			if(RegData[playerid][regAuthTries] >= MAX_AUTH_TRIES)
			{
				SendClientMessage(playerid, COLOR_ERROR, !"* Вы превысили количество попыток авторизации!");
				KickEx(playerid);
				return true;
			}
			SendClientMessageEx(playerid, COLOR_ERROR, "* Вы ввели неверный пароль! Осталось %i попыток.", MAX_AUTH_TRIES - RegData[playerid][regAuthTries]);
			ShowAuthDialog(playerid);
			return true;
		}
		new ms_string[128];
		new query[] = "SELECT * FROM `accounts` WHERE `name` = '%s' LIMIT 1";
		mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), query, pData[playerid][pName]);
		new cb[] = "LoadAccount", spec[] = "i";
		mysql_tquery(ConnectMySQL, ms_string, cb, spec, playerid);
	}
	return true;
}

hook OnPlayerSpawn(playerid)
{
	if(RegData[playerid][regChoosingSkin])
	{
		ApplySkinSelectionView(playerid);
		SetPlayerVirtualWorld(playerid, 0); // fix
	}
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == INVALID_TEXT_DRAW)
	{
		if(RegData[playerid][regChoosingSkin]) return SelectTextDraw(playerid, 0xFFFFFFAA);
	}
	if(clickedid >= ChooseSkinTD[0] && clickedid <= ChooseSkinTD[sizeof(ChooseSkinTD)-1])
	{
		if(clickedid == ChooseSkinTD[11])
		{
			if(RegData[playerid][regSkinIndex] > 0)
			{
				RegData[playerid][regSkinIndex]--;
				SetPlayerSkin(playerid, reg_skins[pData[playerid][pGender]-1][RegData[playerid][regSkinIndex]]);
			}
		}
		else if(clickedid == ChooseSkinTD[10])
		{
			if(reg_skins[pData[playerid][pGender]-1][RegData[playerid][regSkinIndex]+1] != -1)
			{
				RegData[playerid][regSkinIndex]++;
				SetPlayerSkin(playerid, reg_skins[pData[playerid][pGender]-1][RegData[playerid][regSkinIndex]]);
			}
		}
		else if(clickedid == ChooseSkinTD[3])
		{
			HideSkinSelectionTextDraws(playerid);
			RegData[playerid][regChoosingSkin] = false;
			CancelSelectTextDraw(playerid);
			pData[playerid][pDefault_Skin] = reg_skins[pData[playerid][pGender]-1][RegData[playerid][regSkinIndex]];
			GetPlayerIp(playerid, pData[playerid][pRegIP], 16);
			RegisterAccount(playerid);
		}
	}
	return true;
}

forward CheckPlayerMail(playerid, mail[]);
public CheckPlayerMail(playerid, mail[])
{
	if(cache_num_rows())
	{
		SendClientMessage(playerid, COLOR_GREY, !"* Данная почта уже используется!");
		ShowRegMailDialog(playerid);
		return true;
	}

	strmid(pData[playerid][pEmail], mail, 0, strlen(mail), 32);
	ShowRegGenderDialog(playerid);
	return true;
}

forward ReturnRegisteredID(playerid);
public ReturnRegisteredID(playerid)
{
	pData[playerid][pID] = cache_insert_id();
	SendClientMessage(playerid, 0x50a532FF, !"Аккаунт успешно зарегистрирован!");
	PlayerInventory[playerid][10][invID] = 2;
	PlayerInventory[playerid][10][invParam] = pData[playerid][pDefault_Skin];
	PlayerInventory[playerid][10][invAmount] = 1;

	LoadAccountById(playerid);
}

forward LoadAccount(playerid);
public LoadAccount(playerid)
{
	pData[playerid][pID] = cache_get_field_content_int(0, "id");
	cache_get_field_content(0, "password", pData[playerid][pPassword], ConnectMySQL, 32);
	cache_get_field_content(0, "mail", pData[playerid][pEmail], ConnectMySQL, 32);
	pData[playerid][pGender] = cache_get_field_content_int(0, "gender");
	pData[playerid][pDefault_Skin] = cache_get_field_content_int(0, "default_skin");
	pData[playerid][pMoney] = cache_get_field_content_int(0, "money");
	pData[playerid][pBankMoney] = cache_get_field_content_int(0, "bank_money");
	pData[playerid][pBankLastUse] = cache_get_field_content_int(0, "bank_last_use");
	pData[playerid][pAge] = cache_get_field_content_int(0, "age");
	cache_get_field_content(0, "reg_ip", pData[playerid][pRegIP], ConnectMySQL, 16);
	GetPlayerIp(playerid, pData[playerid][pLastIP], 16);
	pData[playerid][pAdmin] = cache_get_field_content_int(0, "admin");
	new temp[32*3+2];
	cache_get_field_content(0, "ChatSettings", temp);
	sscanf(temp, "a<i>[5]", pData[playerid][pChatSettings]);
	if(!pData[playerid][pChatSettings][4])
	{
		for(new i; i < 3; i++) pData[playerid][pChatSettings][i] = 1;
	}
	cache_get_field_content(0, "MappingSlotsNames", temp);
	sscanf(temp, "p<|>s[32]s[32]s[32]", PlayerMapSlotsNames[playerid][0], PlayerMapSlotsNames[playerid][1], PlayerMapSlotsNames[playerid][2]);
	pData[playerid][pKills] = cache_get_field_content_int(0, "Kills");
	pData[playerid][pDeaths] = cache_get_field_content_int(0, "Deaths");
	pData[playerid][pWarns] = cache_get_field_content_int(0, "Warns");
	cache_get_field_content(0, "Comment", pData[playerid][pComment], ConnectMySQL, 32);
	cache_get_field_content(0, "desc_text", pData[playerid][pDescText], ConnectMySQL, 128);
	pData[playerid][pDescTime] = cache_get_field_content_int(0, "desc_time");
	pData[playerid][pRPExp] = cache_get_field_content_int(0, "rp_exp");
	pData[playerid][pRPLevel] = cache_get_field_content_int(0, "rp_level");
	pData[playerid][pQuestProgress] = cache_get_field_content_int(0, "quest_progress");

	new ms_string[128];
	new query[] = "SELECT * FROM `inventory` WHERE `id` = '%i' LIMIT 1";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), query, pData[playerid][pID]);
	new cb[] = "LoadInventory", spec[] = "i";
	mysql_tquery(ConnectMySQL, ms_string, cb, spec, playerid);

	ReloadPlayerMoney(playerid);
	SetPlayerScore(playerid, pData[playerid][pRPLevel]);
	Logged[playerid] = true;
	GotoSpawn(playerid);
	StartPlayerTextureLoading(playerid, 3); // 3 секунды
}

forward LoadInventory(playerid);
public LoadInventory(playerid)
{
	if(!cache_get_row_count())
	{
		new ms_string[128];
		new query[] = "INSERT INTO `inventory` (`id`) VALUES ('%i')";
		mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), query, pData[playerid][pID]);
		mysql_tquery(ConnectMySQL, ms_string);
		SyncPlayerMoneyInventory(playerid);
		SaveInventory(playerid);
	}
	else
	{
		LoadInventoryColumn(playerid, "item_ids", invID);
		LoadInventoryColumn(playerid, "item_nums", invParam);
		LoadInventoryColumn(playerid, "item_amount", invAmount);
		LoadInventoryColumn(playerid, "item_info", invInfo);

		SyncPlayerMoneyInventory(playerid);
		LoadVehiclesForPlayer(playerid);
	}
	return true;
}

hook OnPlayerRequestClass(playerid, classid)
{
	if(RegData[playerid][regChoosingSkin]) return SpawnPlayer(playerid);
	if(Logged[playerid]) return GotoSpawn(playerid);
	TogglePlayerSpectating(playerid, true);
	SetTimerEx("ConnectCamera", 200, false, "i", playerid);
	return false;
}

hook OnPlayerRequestSpawn(playerid)
{
	if(RegData[playerid][regChoosingSkin]) return true;
	if(Logged[playerid]) return true;
	return false;
}

forward ConnectCamera(playerid);
public ConnectCamera(playerid)
{
	if(RegData[playerid][regConnectCamera] == -1) RegData[playerid][regConnectCamera] = random(6);
	switch(RegData[playerid][regConnectCamera])
	{
		case 0:
		{
			SetPlayerCameraPos(playerid, -1711.9561, -2074.6953, 408.1536);
			SetPlayerCameraLookAt(playerid, -1712.8030, -2074.1675, 407.9286);
		}
		case 1:
		{
			SetPlayerCameraPos(playerid, -2416.0820, -354.7854, 124.8495);
			SetPlayerCameraLookAt(playerid, -2416.2168, -355.7750, 124.9945);
		}
		case 2:
		{
			SetPlayerCameraPos(playerid, -2152.2585, 916.8090, 83.2089);
			SetPlayerCameraLookAt(playerid, -2151.2595, 916.8685, 83.3593);
		}
		case 3:
		{
			SetPlayerCameraPos(playerid, -2267.4417, 730.4053, 57.5308);
			SetPlayerCameraLookAt(playerid, -2266.4399, 730.4265, 57.4313);
		}
		case 4:
		{
			SetPlayerCameraPos(playerid, -2864.2195, -148.3117, 89.6961);
			SetPlayerCameraLookAt(playerid, -2863.4841, -148.9906, 89.3015);
		}
		case 5:
		{
			SetPlayerCameraPos(playerid, -1620.6416, -502.4918, 43.0430);
			SetPlayerCameraLookAt(playerid, -1619.9277, -501.7901, 42.9084);
		}
	}
}

forward AuthCheck(playerid);
public AuthCheck(playerid)
{
	if(Logged[playerid]) return true;
	SendClientMessage(playerid, COLOR_GREY, !"* Время на авторизацию вышло!");
	KickEx(playerid);
	return true;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(!Logged[playerid])
		return true;

	SavePlayer(playerid);
	return true;
}

forward CheckAccountReg(playerid);
public CheckAccountReg(playerid)
{
	if(!cache_get_row_count())
	{
		ShowRegisterPasswordDialog(playerid);
	}
	else
	{
		cache_get_field_content(0, "password", pData[playerid][pPassword], ConnectMySQL, 32);
		ShowAuthDialog(playerid);
	}
	return true;
}

SaveAccount(playerid)
{
	if(!Logged[playerid])
		return true;

	new ms_string[1024];
	new query[] = "UPDATE `accounts` SET \
		gender=%i,\
		default_skin=%i,\
		money=%i,\
		bank_money=%i,\
		admin=%i,\
		rp_exp=%i,\
		rp_level=%i,\
		desc_text='%e',\
		desc_time=%i,\
		last_ip='%e' \
		WHERE id = %i";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), query, pData[playerid][pGender], pData[playerid][pDefault_Skin], pData[playerid][pMoney], pData[playerid][pBankMoney], pData[playerid][pAdmin], pData[playerid][pRPExp], pData[playerid][pRPLevel], pData[playerid][pDescText], pData[playerid][pDescTime], pData[playerid][pLastIP], pData[playerid][pID]);

	mysql_tquery(ConnectMySQL, ms_string);
	return true;
}

SavePlayer(playerid)
{
	SaveAccount(playerid);
	SaveInventory(playerid);
	SavePlayerVehicles(playerid);

	return true;
}
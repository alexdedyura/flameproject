#if defined PHONE_SYSTEM_INCLUDED
	#endinput
#endif
#define PHONE_SYSTEM_INCLUDED

#include <YSI_Coding\y_hooks>
#include <..\..\sources\player\phone_clock.inc>

#define PHONE_SMS_LIMIT 100
#define PHONE_SMS_PAGE_SIZE 10
#define PHONE_SMS_MAX_TEXT 144
// Wallpaper is drawn with the global iPhone[6..11] textdraws (the screen
// background pieces). They must stay global so they keep the correct z-order
// below the status bar/app icons (12+) - per-player textdraws always render on
// top of global ones, which previously made the wallpaper cover the whole UI.
#define PHONE_WALLPAPER_FIRST 6
#define PHONE_WALLPAPER_LAST 11

new PhoneDialogMessageIDs[MAX_PLAYERS][PHONE_SMS_PAGE_SIZE];
new PhoneVehicleDialogIDs[MAX_PLAYERS][MAX_PLAYER_VEHICLES];

static const PhoneWallpaperColors[] =
{
	-235802113,
	623192063,
	8388863,
	1605024511,
	303174399
};

Phone_OnGameModeInit()
{
	PhoneCreateTables();
	return true;
}

Phone_OnPlayerDisconnect(playerid)
{
	if(GetPVarInt(playerid, "PhoneShowed"))
		PhoneHide(playerid, false);
	return true;
}

Phone_PlayerSecTimer(playerid)
{
	if(GetPVarInt(playerid, "PhoneShowed"))
		PhoneUpdateClock();
	return true;
}

stock PhoneCreateTables()
{
	new Cache:result;
	new __ms6[] = "CREATE TABLE IF NOT EXISTS `phone_messages` (\
		`ID` int(11) NOT NULL AUTO_INCREMENT,\
		`SenderID` int(11) NOT NULL,\
		`ReceiverID` int(11) NOT NULL,\
		`DialogLowID` int(11) NOT NULL,\
		`DialogHighID` int(11) NOT NULL,\
		`Message` varchar(144) NOT NULL DEFAULT '',\
		`Date` int(11) NOT NULL,\
		PRIMARY KEY (`ID`),\
		KEY `dialog_id` (`DialogLowID`,`DialogHighID`,`ID`),\
		KEY `receiver_date` (`ReceiverID`,`Date`)\
	) ENGINE=MyISAM DEFAULT CHARSET=utf8;";
	result = mysql_query(ConnectMySQL, __ms6);
	cache_delete(result);
	return true;
}

stock PhoneGetWallpaperColor(wallpaper)
{
	if(wallpaper < 0 || wallpaper >= sizeof(PhoneWallpaperColors))
		wallpaper = 0;
	return PhoneWallpaperColors[wallpaper];
}

stock PhoneGetActiveSlot(playerid)
{
	new slot = GetPVarInt(playerid, "PhoneSlot");
	if(slot < 0 || slot >= sizeof(PlayerInventory[]))
		return -1;
	if(!IsPhoneInventoryItem(PlayerInventory[playerid][slot][invID], PlayerInventory[playerid][slot][invParam]))
		return -1;
	return slot;
}

stock PhoneApplyWallpaper(playerid, wallpaper)
{
	// Color is captured by the client at show time, so each viewer keeps their
	// own wallpaper color even though these textdraws are shared (global).
	new color = PhoneGetWallpaperColor(wallpaper);
	for(new i = PHONE_WALLPAPER_FIRST; i <= PHONE_WALLPAPER_LAST; i++)
	{
		TextDrawColor(iPhone[i], color);
		TextDrawShowForPlayer(playerid, iPhone[i]);
	}
	return true;
}

ShowPlayerPhone(playerid, slot)
{
	if(slot < 0 || slot >= sizeof(PlayerInventory[]))
		return true;
	if(!IsPhoneInventoryItem(PlayerInventory[playerid][slot][invID], PlayerInventory[playerid][slot][invParam]))
		return true;

	if(InventoryShowed[playerid])
		HidePlayerInventory(playerid, false);

	SetPVarInt(playerid, "PhoneShowed", 1);
	SetPVarInt(playerid, "PhoneSlot", slot);

	ShowIPhoneTD(playerid);
	PhoneUpdateClock();
	PhoneApplyWallpaper(playerid, PlayerInventory[playerid][slot][invInfo]);
	SelectTextDraw(playerid, 0xAAAAAAFF);
	return true;
}

PhoneHide(playerid, bool:cancel = true)
{
	DeletePVar(playerid, "PhoneShowed");
	DeletePVar(playerid, "PhoneSlot");
	DeletePVar(playerid, "PhoneSmsTargetID");
	DeletePVar(playerid, "PhoneSmsPage");
	DeletePVar(playerid, "PhoneSmsHasPrev");
	DeletePVar(playerid, "PhoneSmsHasNext");
	DeletePVar(playerid, "PhoneSmsFirstRow");
	DeletePVar(playerid, "PhoneSmsMessageID");
	DeletePVar(playerid, "PhoneVehicleCount");
	DeletePVar(playerid, "PhoneSmsTargetName");

	HideIPhoneTD(playerid);
	if(cancel)
		CancelSelectTextDraw(playerid);
	return true;
}

Phone_OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(!GetPVarInt(playerid, "PhoneShowed"))
		return true;

	if(clickedid == INVALID_TEXT_DRAW)
		return PhoneHide(playerid, false);

	if(clickedid == iPhone[30] || clickedid == iPhone[63] || clickedid == iPhone[71])
		return PhoneShowMessengerTarget(playerid);

	if(clickedid == iPhone[28] || clickedid == iPhone[61] || clickedid == iPhone[69])
		return PhoneShowVehicleCall(playerid);

	if(clickedid == iPhone[54])
		return SendClientMessage(playerid, COLOR_GREY, !"* GPS-навигатор пока находится в разработке.");

	if(clickedid == iPhone[31] || clickedid == iPhone[56] || clickedid == iPhone[64] || clickedid == iPhone[72])
		return PhoneShowSettings(playerid);

	if((clickedid >= iPhone[53] && clickedid <= iPhone[56]) || (clickedid >= iPhone[61] && clickedid <= iPhone[64]) ||
		(clickedid >= iPhone[69] && clickedid <= iPhone[72]) || (clickedid >= iPhone[28] && clickedid <= iPhone[31]))
	{
		SendClientMessage(playerid, COLOR_GREY, !"* Раздел пока недоступен.");
	}

	return true;
}

Phone_OnDialogResponse(playerid, dialogid, response, listitem, const inputtext[])
{
	switch(dialogid)
	{
		case D_PHONE_SMS_TARGET:
		{
			if(!response) return true;
			return PhoneOpenMessengerTarget(playerid, inputtext);
		}
		case D_PHONE_SMS_THREAD:
		{
			if(!response) return PhoneShowMessengerTarget(playerid);
			return PhoneHandleSmsThread(playerid, listitem);
		}
		case D_PHONE_SMS_TEXT:
		{
			if(!response) return PhoneShowSmsThread(playerid);
			return PhoneSendSms(playerid, inputtext);
		}
		case D_PHONE_SMS_FULL:
		{
			return PhoneShowSmsThread(playerid);
		}
		case D_PHONE_VEHICLES:
		{
			if(!response) return true;
			return PhoneCallVehicle(playerid, listitem);
		}
		case D_PHONE_SETTINGS:
		{
			if(!response) return true;
			return PhoneApplySettings(playerid, listitem);
		}
	}
	return true;
}

PhoneShowMessengerTarget(playerid)
{
	ShowPlayerDialog(playerid, D_PHONE_SMS_TARGET, DIALOG_STYLE_INPUT, !"Мессенджер", !""COLOR_WHITE"Введите никнейм игрока для открытия диалога.", !"Далее", !"Назад");
	return true;
}

stock PhoneFindAccountByName(const target_name[], &account_id, account_name[], account_name_size = sizeof account_name)
{
	new query[128], Cache:result;
	new __ms5[] = "SELECT id, name FROM accounts WHERE name = '%e' LIMIT 1";
	mysql_format(ConnectMySQL, query, sizeof(query), __ms5, target_name);
	result = mysql_query(ConnectMySQL, query);

	if(!cache_num_rows())
	{
		cache_delete(result);
		return false;
	}

	account_id = cache_get_field_content_int(0, "id");
	cache_get_field_content(0, "name", account_name, ConnectMySQL, account_name_size);
	cache_delete(result);
	return true;
}

PhoneOpenMessengerTarget(playerid, const target_name[])
{
	new targetID, targetName[MAX_PLAYER_NAME];
	if(!strlen(target_name))
		return PhoneShowMessengerTarget(playerid);
	if(!PhoneFindAccountByName(target_name, targetID, targetName))
	{
		SendClientMessage(playerid, COLOR_ERROR, !"* Аккаунт с таким никнеймом не найден.");
		return PhoneShowMessengerTarget(playerid);
	}
	if(targetID == pData[playerid][pID])
	{
		SendClientMessage(playerid, COLOR_ERROR, !"* Нельзя отправлять SMS самому себе.");
		return PhoneShowMessengerTarget(playerid);
	}

	SetPVarInt(playerid, "PhoneSmsTargetID", targetID);
	SetPVarInt(playerid, "PhoneSmsPage", 0);
	SetPVarString(playerid, "PhoneSmsTargetName", targetName);
	return PhoneShowSmsThread(playerid);
}

stock PhoneGetDialogBounds(playerid, targetID, &lowID, &highID)
{
	lowID = pData[playerid][pID];
	highID = targetID;
	if(lowID > highID)
	{
		lowID = targetID;
		highID = pData[playerid][pID];
	}
	return true;
}

stock PhoneGetSmsCount(lowID, highID)
{
	new query[160], Cache:result, count;
	new __ms4[] = "SELECT COUNT(*) AS total FROM phone_messages WHERE DialogLowID = %i AND DialogHighID = %i";
	mysql_format(ConnectMySQL, query, sizeof(query), __ms4, lowID, highID);
	result = mysql_query(ConnectMySQL, query);
	if(cache_num_rows())
		count = cache_get_field_content_int(0, "total");
	cache_delete(result);
	return count;
}

PhoneShowSmsThread(playerid)
{
	new targetID = GetPVarInt(playerid, "PhoneSmsTargetID");
	if(!targetID)
		return PhoneShowMessengerTarget(playerid);

	new targetName[MAX_PLAYER_NAME];
	GetPVarString(playerid, "PhoneSmsTargetName", targetName, sizeof(targetName));

	new lowID, highID;
	PhoneGetDialogBounds(playerid, targetID, lowID, highID);

	new total = PhoneGetSmsCount(lowID, highID);
	new page = GetPVarInt(playerid, "PhoneSmsPage");
	new maxPage = (total > 0) ? ((total - 1) / PHONE_SMS_PAGE_SIZE) : 0;
	if(page < 0) page = 0;
	if(page > maxPage) page = maxPage;
	SetPVarInt(playerid, "PhoneSmsPage", page);

	new offset = page * PHONE_SMS_PAGE_SIZE;
	new query[256], Cache:result;
	new __ms3[] = "SELECT ID, SenderID, Message, FROM_UNIXTIME(Date, '%%d.%%m %%H:%%i') AS MessageDate \
		FROM phone_messages WHERE DialogLowID = %i AND DialogHighID = %i ORDER BY ID DESC LIMIT %i, %i";
	mysql_format(ConnectMySQL, query, sizeof(query), __ms3, lowID, highID, offset, PHONE_SMS_PAGE_SIZE);
	result = mysql_query(ConnectMySQL, query);

	new bool:hasPrev = page > 0;
	new bool:hasNext = ((page + 1) * PHONE_SMS_PAGE_SIZE) < total;
	new firstMessageRow = 1;
	new list[2048], rowText[96], author[32], message[PHONE_SMS_MAX_TEXT + 1], shortMessage[72], date[20];
	format(list, sizeof(list), "Действие\tАвтор\tСообщение\nНаписать\t\tНовое SMS\n");

	if(hasPrev)
	{
		strcat(list, "Назад\t\tНовые сообщения\n");
		firstMessageRow++;
	}
	if(hasNext)
	{
		strcat(list, "Далее\t\tСтарые сообщения\n");
		firstMessageRow++;
	}

	for(new i = 0; i < PHONE_SMS_PAGE_SIZE; i++)
		PhoneDialogMessageIDs[playerid][i] = 0;

	new rows = cache_num_rows();
	for(new i = 0; i < rows; i++)
	{
		PhoneDialogMessageIDs[playerid][i] = cache_get_field_content_int(i, "ID");
		cache_get_field_content(i, "Message", message, ConnectMySQL, sizeof(message));
		cache_get_field_content(i, "MessageDate", date, ConnectMySQL, sizeof(date));

		if(cache_get_field_content_int(i, "SenderID") == pData[playerid][pID])
			format(author, sizeof(author), "Вы");
		else
			format(author, sizeof(author), "%s", targetName);

		strmid(shortMessage, message, 0, 64, sizeof(shortMessage));
		strreplace(shortMessage, "\n", " ");
		strreplace(shortMessage, "\t", " ");
		if(strlen(message) > 64)
			format(shortMessage, sizeof(shortMessage), "%s...", shortMessage);

		format(rowText, sizeof(rowText), "%s\t%s\t%s\n", date, author, shortMessage);
		strcat(list, rowText);
	}
	cache_delete(result);

	SetPVarInt(playerid, "PhoneSmsHasPrev", hasPrev);
	SetPVarInt(playerid, "PhoneSmsHasNext", hasNext);
	SetPVarInt(playerid, "PhoneSmsFirstRow", firstMessageRow);

	new caption[64];
	format(caption, sizeof(caption), "SMS: %s", targetName);
	ShowPlayerDialog(playerid, D_PHONE_SMS_THREAD, DIALOG_STYLE_TABLIST_HEADERS, caption, list, !"Выбрать", !"Назад");
	return true;
}

PhoneHandleSmsThread(playerid, listitem)
{
	if(listitem == 0)
	{
		ShowPlayerDialog(playerid, D_PHONE_SMS_TEXT, DIALOG_STYLE_INPUT, !"Новое SMS", !""COLOR_WHITE"Введите текст сообщения. Максимум 144 символа.", !"Отправить", !"Назад");
		return true;
	}

	new row = 1;
	if(GetPVarInt(playerid, "PhoneSmsHasPrev"))
	{
		if(listitem == row)
		{
			SetPVarInt(playerid, "PhoneSmsPage", GetPVarInt(playerid, "PhoneSmsPage") - 1);
			return PhoneShowSmsThread(playerid);
		}
		row++;
	}

	if(GetPVarInt(playerid, "PhoneSmsHasNext"))
	{
		if(listitem == row)
		{
			SetPVarInt(playerid, "PhoneSmsPage", GetPVarInt(playerid, "PhoneSmsPage") + 1);
			return PhoneShowSmsThread(playerid);
		}
	}

	new messageIndex = listitem - GetPVarInt(playerid, "PhoneSmsFirstRow");
	if(messageIndex < 0 || messageIndex >= PHONE_SMS_PAGE_SIZE || !PhoneDialogMessageIDs[playerid][messageIndex])
		return true;

	SetPVarInt(playerid, "PhoneSmsMessageID", PhoneDialogMessageIDs[playerid][messageIndex]);
	return PhoneShowFullSms(playerid);
}

PhoneShowFullSms(playerid)
{
	new messageID = GetPVarInt(playerid, "PhoneSmsMessageID");
	new targetID = GetPVarInt(playerid, "PhoneSmsTargetID");
	new lowID, highID;
	PhoneGetDialogBounds(playerid, targetID, lowID, highID);

	new query[256], Cache:result;
	new __ms2[] = "SELECT SenderID, Message, FROM_UNIXTIME(Date, '%%d.%%m.%%Y %%H:%%i') AS MessageDate \
		FROM phone_messages WHERE ID = %i AND DialogLowID = %i AND DialogHighID = %i LIMIT 1";
	mysql_format(ConnectMySQL, query, sizeof(query), __ms2, messageID, lowID, highID);
	result = mysql_query(ConnectMySQL, query);

	if(!cache_num_rows())
	{
		cache_delete(result);
		return PhoneShowSmsThread(playerid);
	}

	new targetName[MAX_PLAYER_NAME], author[32], message[PHONE_SMS_MAX_TEXT + 1], date[20], info[256];
	GetPVarString(playerid, "PhoneSmsTargetName", targetName, sizeof(targetName));
	cache_get_field_content(0, "Message", message, ConnectMySQL, sizeof(message));
	cache_get_field_content(0, "MessageDate", date, ConnectMySQL, sizeof(date));

	if(cache_get_field_content_int(0, "SenderID") == pData[playerid][pID])
		format(author, sizeof(author), "Вы");
	else
		format(author, sizeof(author), "%s", targetName);

	format(info, sizeof(info), ""COLOR_WHITE"Дата: "FLAME_COLOR"%s\n"COLOR_WHITE"Автор: "FLAME_COLOR"%s\n\n"COLOR_WHITE"%s", date, author, message);
	cache_delete(result);
	ShowPlayerDialog(playerid, D_PHONE_SMS_FULL, DIALOG_STYLE_MSGBOX, !"SMS", info, !"Назад", !"");
	return true;
}

stock PhoneFindOnlinePlayerByAccount(accountID)
{
	foreach(new i : Player)
	{
		if(Logged[i] && pData[i][pID] == accountID)
			return i;
	}
	return INVALID_PLAYER_ID;
}

PhoneSendSms(playerid, const inputtext[])
{
	new targetID = GetPVarInt(playerid, "PhoneSmsTargetID");
	if(!targetID)
		return PhoneShowMessengerTarget(playerid);
	if(!strlen(inputtext))
	{
		SendClientMessage(playerid, COLOR_ERROR, !"* Сообщение не может быть пустым.");
		return PhoneShowSmsThread(playerid);
	}
	if(strlen(inputtext) > PHONE_SMS_MAX_TEXT)
	{
		SendClientMessage(playerid, COLOR_ERROR, !"* Сообщение слишком длинное.");
		return PhoneShowSmsThread(playerid);
	}

	new lowID, highID;
	PhoneGetDialogBounds(playerid, targetID, lowID, highID);

	new query[512], Cache:result;
	new __ms1[] = "INSERT INTO phone_messages SET SenderID = %i, ReceiverID = %i, DialogLowID = %i, DialogHighID = %i, Message = '%e', Date = UNIX_TIMESTAMP()";
	mysql_format(ConnectMySQL, query, sizeof(query), __ms1, pData[playerid][pID], targetID, lowID, highID, inputtext);
	result = mysql_query(ConnectMySQL, query);
	cache_delete(result);

	new total = PhoneGetSmsCount(lowID, highID);
	if(total > PHONE_SMS_LIMIT)
	{
		new __ms0[] = "DELETE FROM phone_messages WHERE DialogLowID = %i AND DialogHighID = %i ORDER BY ID ASC LIMIT %i";
		mysql_format(ConnectMySQL, query, sizeof(query), __ms0, lowID, highID, total - PHONE_SMS_LIMIT);
		result = mysql_query(ConnectMySQL, query);
		cache_delete(result);
	}

	new targetOnline = PhoneFindOnlinePlayerByAccount(targetID);
	if(targetOnline != INVALID_PLAYER_ID)
		SendClientMessageEx(targetOnline, -1, "Новое SMS от "FLAME_COLOR"%s"COLOR_WHITE".", pData[playerid][pName]);

	SendClientMessage(playerid, -1, !"SMS отправлено.");
	SetPVarInt(playerid, "PhoneSmsPage", 0);
	return PhoneShowSmsThread(playerid);
}

PhoneShowVehicleCall(playerid)
{
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
		PhoneVehicleDialogIDs[playerid][i] = -1;

	new string[512], count;
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
	{
		if(!IsGarageSlotUsed(playerid, i))
			break;
		if(PlayerGarage[playerid][i][vType] != VEHICLE_TYPE_PERSONAL)
			continue;

		new vehName[64];
		GetGarageDisplayName(playerid, i, vehName);
		PhoneVehicleDialogIDs[playerid][count] = i;
		format(string, sizeof(string), "%s"FLAME_COLOR"%i."COLOR_WHITE" %s\n", string, count + 1, vehName);
		count++;
	}

	if(!count)
		return SendClientMessage(playerid, COLOR_GREY, !"* У Вас нет личного транспорта для вызова.");

	SetPVarInt(playerid, "PhoneVehicleCount", count);
	ShowPlayerDialog(playerid, D_PHONE_VEHICLES, DIALOG_STYLE_LIST, !"Вызов автомобиля", string, !"Вызвать", !"Назад");
	return true;
}

PhoneCallVehicle(playerid, listitem)
{
	new count = GetPVarInt(playerid, "PhoneVehicleCount");
	if(listitem < 0 || listitem >= count)
		return true;

	new slot = PhoneVehicleDialogIDs[playerid][listitem];
	if(!IsGarageSlotUsed(playerid, slot) || PlayerGarage[playerid][slot][vType] != VEHICLE_TYPE_PERSONAL)
		return SendClientMessage(playerid, COLOR_ERROR, !"* Этот транспорт больше недоступен.");
	if(IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_ERROR, !"* Вызов автомобиля недоступен из транспорта.");
	if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0)
		return SendClientMessage(playerid, COLOR_ERROR, !"* Автомобиль можно вызвать только на улице в основном мире.");
	if(IsGarageHaveTaxes(playerid, slot))
		return SendClientMessage(playerid, COLOR_ERROR, !"* Автомобиль недоступен из-за неоплаченного налога.");

	new Float:x, Float:y, Float:z, Float:angle;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);
	x += (5.0 * floatsin(-angle, degrees));
	y += (5.0 * floatcos(-angle, degrees));

	new newvehid = SpawnGarageVehicleAt(playerid, slot, x, y, z, angle);
	SetVehicleVirtualWorld(newvehid, 0);
	LinkVehicleToInterior(newvehid, 0);
	SetVehicleZAngle(newvehid, angle);
	VehicleInfo[newvehid][vEngine] = 0;
	VehicleInfo[newvehid][vLights] = 0;
	UpdateVehicleParamsEx(newvehid);
	SaveVehicle(newvehid);

	SendClientMessage(playerid, -1, !"Автомобиль доставлен рядом с Вами.");
	return true;
}

PhoneShowSettings(playerid)
{
	ShowPlayerDialog(playerid, D_PHONE_SETTINGS, DIALOG_STYLE_LIST, !"Настройки смартфона", !""FLAME_COLOR"1."COLOR_WHITE" Обои: стандартные\n"FLAME_COLOR"2."COLOR_WHITE" Обои: синие\n"FLAME_COLOR"3."COLOR_WHITE" Обои: зеленые\n"FLAME_COLOR"4."COLOR_WHITE" Обои: фиолетовые\n"FLAME_COLOR"5."COLOR_WHITE" Обои: светлые\nЗвук уведомлений - скоро\nЯркость - скоро", !"Выбрать", !"Назад");
	return true;
}

PhoneApplySettings(playerid, listitem)
{
	if(listitem < 0)
		return true;

	if(listitem < sizeof(PhoneWallpaperColors))
	{
		new slot = PhoneGetActiveSlot(playerid);
		if(slot == -1)
			return SendClientMessage(playerid, COLOR_ERROR, !"* Смартфон не найден в инвентаре.");

		PlayerInventory[playerid][slot][invInfo] = listitem;
		PhoneApplyWallpaper(playerid, listitem);
		if(InventoryShowed[playerid])
			UpdateInventoryCell(playerid, slot);
		SendClientMessage(playerid, -1, !"Обои смартфона изменены.");
		return PhoneShowSettings(playerid);
	}

	SendClientMessage(playerid, COLOR_GREY, !"* Эта настройка пока недоступна.");
	return PhoneShowSettings(playerid);
}


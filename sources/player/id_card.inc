#include <YSI_Coding\y_hooks>

#define ID_CARD_GAIN_POS 1484.9985,-1744.3380,3910.0859
#define ID_CARD_GAIN_VW 9
#define ID_CARD_GAIN_INT 3

hook OnGameModeInit()
{
	CreateDynamicPickup(1239, 1, ID_CARD_GAIN_POS, ID_CARD_GAIN_VW, ID_CARD_GAIN_INT);
	CreateDynamic3DTextLabel("Получение ID-карты\nНажмите "FLAME_COLOR"ALT"COLOR_WHITE" для взаимодействия", -1, ID_CARD_GAIN_POS, 5.0, _, _, 1, ID_CARD_GAIN_VW, ID_CARD_GAIN_INT);
}


hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_WALK && !(oldkeys & KEY_WALK) && !IsPlayerInAnyVehicle(playerid) && IsPlayerInRangeOfPoint(playerid, 2.0, ID_CARD_GAIN_POS) 
		&& GetPlayerVirtualWorld(playerid) == ID_CARD_GAIN_VW && GetPlayerInterior(playerid) == ID_CARD_GAIN_INT)
	{
		ShowPlayerDialog(playerid, D_ID_CARD_GAIN, DIALOG_STYLE_MSGBOX, "Получение ID карты", ""COLOR_WHITE"Вы действительно хотите получить "FLAME_COLOR"ID карту"COLOR_WHITE"?", "Да", "Нет");
	}
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_ID_CARD_GAIN)
	{
		if(!response)
			return true;

		for(new i = 0; i < 10; i++)
			if(PlayerInventory[playerid][i][invID] == 1 && PlayerInventory[playerid][i][invParam] == 1)
				ClearPlayerInventorySlot(playerid, i, true);

		if(AddItemInInventory(playerid, 1, 1, 1) == -1)
			return SendClientMessage(playerid, -1, !"Инвентарь заполнен, освободите слот чтобы получить "FLAME_COLOR"ID карту"COLOR_WHITE"!");
		SaveInventory(playerid);
		new ms_string[128];
		new __ms2[] = "DELETE FROM `documents` WHERE `acc_id` = '%i' and `type` = '1'";
		mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms2, pData[playerid][pID]);
		mysql_tquery(ConnectMySQL, ms_string);

		new __ms1[] = "INSERT INTO `documents` (`acc_id`, `type`, `issued`, `expired`) VALUES ('%i', '1', NOW(), DATE_ADD(NOW(), INTERVAL 3 MONTH))";
		mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms1, pData[playerid][pID], gettime(), gettime() + 30 * 24 * 60 * 60);
		mysql_tquery(ConnectMySQL, ms_string);
		SendClientMessage(playerid, -1, !"Вам была выдана "FLAME_COLOR"ID-карта"COLOR_WHITE", теперь вы являетесь гражданином США и можете устраиваться на официальные работы!");
		SendClientMessage(playerid, -1, !"ID карта действительна "FLAME_COLOR"3 месяца"COLOR_WHITE" со дня выдачи, после срока действия вам необходимо перевыпустить её.");
		Quest_OnPlayerGetIDCard(playerid);
		return true;
	}
	return true;
}

ShowPlayerIDCard(playerid, targetid)
{
	new ms_string[256];
	new __ms0[] = "SELECT DATE_FORMAT(`issued`, '%%d.%%m.%%Y') as `issued`, DATE_FORMAT(`expired`, '%%d.%%m.%%Y') as `expired` FROM `documents` WHERE\
		`acc_id` = '%i' and `type` = '1'";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms0, pData[playerid][pID]);
	mysql_query(ConnectMySQL, ms_string);
	new issued[32], expired[32];
	cache_get_field_content(0, "issued", issued);
	cache_get_field_content(0, "expired", expired);
    new string[512];
    format(string, sizeof(string), ""COLOR_WHITE"ID: "FLAME_COLOR"C%02i\n"COLOR_WHITE"Имя Фамилия: "FLAME_COLOR"%s\n"COLOR_WHITE"Возраст: "FLAME_COLOR"%i лет\n"COLOR_WHITE"Пол: "FLAME_COLOR"%s\n"COLOR_WHITE"Место проживания: "FLAME_COLOR"%s\n"COLOR_WHITE"Выдано: "FLAME_COLOR"%s\n"COLOR_WHITE"Действительно до "FLAME_COLOR"%s",
    pData[playerid][pID], pData[playerid][pName], pData[playerid][pAge], (pData[playerid][pGender]) ? ("Мужской") : ("Женский"),
    "Неизвестно", issued, expired);
    ShowPlayerDialog(targetid, 0, DIALOG_STYLE_MSGBOX, "ID карта", string, !"OK", !"");
    return true;
}



#define KEY_DUPLICATE_PRICE 300
static const KEY_DUPLICATE_POS[pos_info] = {-1416.0410, -303.7149, 14.0000, 0.0, 0, 0};

VKeys_OnGameModeInit()
{
	CreateDynamicPickup(1239, 1, KEY_DUPLICATE_POS[pX], KEY_DUPLICATE_POS[pY], KEY_DUPLICATE_POS[pZ], KEY_DUPLICATE_POS[pVW], KEY_DUPLICATE_POS[pInt]);
	CreateDynamic3DTextLabel("Сделать дубликат ключа", -1, KEY_DUPLICATE_POS[pX], KEY_DUPLICATE_POS[pY], KEY_DUPLICATE_POS[pZ], 
		5.0, .testlos = 1, .worldid = KEY_DUPLICATE_POS[pVW], .interiorid = KEY_DUPLICATE_POS[pInt]);

	return true;
}

VKeys_ButtonAltFoot(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 2.5, KEY_DUPLICATE_POS[pX], KEY_DUPLICATE_POS[pY], KEY_DUPLICATE_POS[pZ]) 
		&& GetPlayerInterior(playerid) == KEY_DUPLICATE_POS[pInt] && GetPlayerVirtualWorld(playerid) == KEY_DUPLICATE_POS[pVW])
		return ShowPlayerVehiclesShopDialog(playerid);

	return true;
}

VKeys_OnDialogResponse(playerid, dialogid, response, listitem, const inputtext[])
{
	switch(dialogid)
	{
		case D_VEHICLES_KEYS_LIST:
		{
			if(!response)
				return true;

			ShowPlayerVehicleKeysDupl(playerid, listitem);	
		}
		case D_VEHICLES_KEYS_ID:
		{
			if(!response)
				return ShowPlayerVehicleKeysList(playerid);

			new slot = GetPVarInt(playerid, "VKeysSlot");
			if(!IsGarageSlotUsed(playerid, slot))
				return true;

			if(pData[playerid][pMoney] < KEY_DUPLICATE_PRICE)
				return SendClientMessage(playerid, -1, !"У Вас недостаточно денег!");

			new targetid = strval(inputtext);
			if(playerid == targetid)
				return SendClientMessage(playerid, -1, !"Неприменимо к себе!");
			if(!DistancePlayer(5.0, playerid, targetid))
				return SendClientMessage(playerid, -1, !"Данный игрок не рядом с Вами!");

			new model = PlayerGarage[playerid][slot][vModel];
			new dbid = PlayerGarage[playerid][slot][vID];
			if(AddItemInInventory(targetid, 4, dbid, 1) == -1)
				return SendClientMessage(playerid, -1, !"У данного игрока нет места в инвентаре!");

			if(GetGarageSlotByDBID(targetid, dbid) == -1)
				AddPlayerGarageVehicle(targetid, PlayerGarage[playerid][slot], 0);

			UpdatePlayerMoney(playerid, -KEY_DUPLICATE_PRICE);
			SendClientMessageEx(playerid, -1, "Вы передали ключи от транспорта %s %s.", VehicleNames[model - 400], pData[targetid][pName]);
			SendClientMessageEx(targetid, -1, "%s передал Вам ключи от транспорта %s.", pData[playerid][pName], VehicleNames[model - 400]);
		}
	}

	return true;
}

ShowPlayerVehicleKeysList(playerid)
{
	new string[256];
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
	{
		if(!IsGarageSlotUsed(playerid, i))
			break;

		format(string, sizeof(string), "%s"FLAME_COLOR"%i."COLOR_WHITE" %s\n", string, i + 1, VehicleNames[PlayerGarage[playerid][i][vModel] - 400]);
	}

	if(!strlen(string))
		return SendClientMessage(playerid, -1, !"У Вас нет личного транспорта!");

	ShowPlayerDialog(playerid, D_VEHICLES_KEYS_LIST, DIALOG_STYLE_LIST, !"Дубликат ключей - "#KEY_DUPLICATE_PRICE"$", string, !"Далее", !"Назад");
	return true;
}

ShowPlayerVehicleKeysDupl(playerid, slot)
{
	SetPVarInt(playerid, "VKeysSlot", slot);
	ShowPlayerDialog(playerid, D_VEHICLES_KEYS_ID, DIALOG_STYLE_INPUT, !"Дубликат ключей - "#KEY_DUPLICATE_PRICE"$", "Введите id игрока", !"Далее", !"Назад");
	return true;
}
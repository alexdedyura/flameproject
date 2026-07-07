#define FIXCAR_PRICE 150
#define CALL_VEHICLE_PRICE 100

static const Float:PARKING_POS[][4] =
{
	{-1959.4386, 584.7615, 34.9651, 178.8785},
	{-2629.6831, 1368.6360, 7.1927, 190.9653},
	{-2123.8491, -876.6761, 31.7734, 337.3470}
};

CMD:vehicles(playerid)
{
	new string[512];
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
	{
		if(!IsGarageSlotUsed(playerid, i))
			break;

		new vehName[64];
		GetGarageDisplayName(playerid, i, vehName);
		format(string, sizeof(string), "%s"FLAME_COLOR"%i."COLOR_WHITE" %s\n", string, i + 1, vehName);
	}

	if(strlen(string))
		ShowPlayerDialog(playerid, D_VEHICLES_MENU, DIALOG_STYLE_LIST, !"Список транспорта", string, !"Далее", !"Выход");
	else
		SendClientMessage(playerid, -1, !"У вас нет транспорта!");

	return true;
}

VehiclesP_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext

	switch(dialogid)
	{
		case D_VEHICLES_MENU:
		{
			if(!response)
				return true;

			ShowPlayerVehicleMenu(playerid, listitem);
		}
		case D_VEHICLES_MENU_MAIN:
		{
			if(!response)
				return cmd_vehicles(playerid);

			new slot = GetPVarInt(playerid, "VMenuSlot");
			if(!IsGarageSlotUsed(playerid, slot))
				return true;

			switch(listitem)
			{
				case 0: // Информация
					return ShowPlayerVehicleInfo(playerid, slot);
				case 1: // Помощь
				{
					return ShowPlayerVehicleHelp(playerid, slot);
				}
				case 2: // Найти автомобиль по GPS
				{
					new vehid = pData[playerid][pVehicles][slot];
					if(!vehid || !IsValidVehicle(vehid))
					{
						SendClientMessage(playerid, -1, !"Транспорт на хранении. Сначала вызовите его.");
						ShowPlayerVehicleMenu(playerid, slot);
						return true;
					}

					new zoneName[64];
					new Float:x, Float:y, Float:z;
					GetVehiclePos(vehid, x, y, z);
					GetFullZoneName(x, y, zoneName);
					SendClientMessageEx(playerid, -1, "Ваш транспорт находится в %s.", zoneName);
					SetPlayerCustomGPSMarker(playerid, x, y, z);
				}
				case 3: // Вызвать транспорт
				{
					if(PlayerGarage[playerid][slot][vType] == VEHICLE_TYPE_SHARING && IsGarageSharingExpired(playerid, slot))
					{
						SendClientMessage(playerid, -1, !"Срок аренды этого транспорта истёк.");
						DeleteGarageVehicle(playerid, slot);
						return cmd_vehicles(playerid);
					}

					if(PlayerGarage[playerid][slot][vType] != VEHICLE_TYPE_SHARING && pData[playerid][pMoney] < CALL_VEHICLE_PRICE)
					{
						SendClientMessageEx(playerid, -1, "Вызов транспорта стоит %i$. У Вас недостаточно денег!", CALL_VEHICLE_PRICE);
						ShowPlayerVehicleMenu(playerid, slot);
						return true;
					}

					CallPlayerVehicle(playerid, slot);
				}
				case 4: // Налог
				{
					if(!IsGarageHaveTaxes(playerid, slot))
					{
						SendClientMessage(playerid, -1, !"Все налоги уплачены!");
						ShowPlayerVehicleMenu(playerid, slot);
						return true;
					}

					ShowPlayerVehicleTaxes(playerid, slot);
				}
			}
		}
		case D_VEHICLES_MENU_RETURN:
		{
			return ShowPlayerVehicleMenu(playerid, GetPVarInt(playerid, "VMenuSlot"));
		}
		case D_VEHICLES_MENU_FIXCAR:
		{
			if(!response)
				return true;
			if(pData[playerid][pMoney] < FIXCAR_PRICE)
				return SendClientMessage(playerid, -1, !"У Вас недостаточно денег!");
			if(!IsGarageSlotUsed(playerid, listitem))
				return true;

			new vehid = pData[playerid][pVehicles][listitem];
			if(!vehid || !IsValidVehicle(vehid))
				return SendClientMessage(playerid, -1, !"Сначала вызовите транспорт через /vehicles.");

			UpdatePlayerMoney(playerid, -FIXCAR_PRICE);
			SetVehicleToRespawn(vehid);
		}
		case D_SELLCAR:
		{
			if(!response)
				return true;

			new vehid = GetPlayerVehicleID(playerid);

			if(!IsPlayerVehicleOwner(playerid, vehid))
				return true;

			new price = GetVehicleSellCarPrice(GetVehicleModel(vehid));

			UpdatePlayerMoney(playerid, price);
			SendClientMessageEx(playerid, -1, "Вы продали транспорт за %i$.", price);

			DeleteVehicle(vehid);
		}
	}

	return true;
}

ShowPlayerVehicleMenu(playerid, slot)
{
	if(!IsGarageSlotUsed(playerid, slot))
		return true;

	new model = PlayerGarage[playerid][slot][vModel];

	new sstring[80];
	if(PlayerGarage[playerid][slot][vType] == VEHICLE_TYPE_SHARING)
		format(sstring, sizeof(sstring), "%s (арендный автомобиль)", VehicleNames[model - 400]);
	else
		format(sstring, sizeof(sstring), "%s %s", VehicleNames[model - 400], GetVehicleComplectationName(PlayerGarage[playerid][slot][vComp]));

	new string[512];
	if(PlayerGarage[playerid][slot][vType] == VEHICLE_TYPE_SHARING)
	{
		format(string, sizeof(string), ""FLAME_COLOR"1."COLOR_WHITE" Информация\n"FLAME_COLOR"2."COLOR_WHITE" Помощь\n"FLAME_COLOR"3."COLOR_WHITE" Найти автомобиль по GPS\n"FLAME_COLOR"4."COLOR_WHITE" Вызвать транспорт");
	}
	else
	{
		format(string, sizeof(string), ""FLAME_COLOR"1."COLOR_WHITE" Информация\n"FLAME_COLOR"2."COLOR_WHITE" Помощь\n"FLAME_COLOR"3."COLOR_WHITE" Найти автомобиль по GPS\n"FLAME_COLOR"4."COLOR_WHITE" Вызвать транспорт\n"FLAME_COLOR"5."COLOR_WHITE" Налог%s", (IsGarageHaveTaxes(playerid, slot)) ? (" | Накопился налог") : (""));
	}

	SetPVarInt(playerid, "VMenuSlot", slot);

	ShowPlayerDialog(playerid, D_VEHICLES_MENU_MAIN, DIALOG_STYLE_LIST, sstring, string, !"Далее", !"Назад");
	return true;
}

ShowPlayerVehicleInfo(playerid, slot)
{
	new model = PlayerGarage[playerid][slot][vModel];

	new string[512];
	if(PlayerGarage[playerid][slot][vType] == VEHICLE_TYPE_SHARING)
	{
		format(string, sizeof(string), ""COLOR_WHITE"Тип:"FLAME_COLOR" Арендный автомобиль\n"COLOR_WHITE"Модель:"FLAME_COLOR" %s\n"COLOR_WHITE"Цвет:"FLAME_COLOR" %s\n"COLOR_WHITE"Арендатор:"FLAME_COLOR" %s\n"COLOR_WHITE"Аренда до:"FLAME_COLOR" %s\n"COLOR_WHITE"Пробег:"FLAME_COLOR" %i км.\n"COLOR_WHITE"Номерной знак:"FLAME_COLOR" %s\n"COLOR_WHITE"Бак:"FLAME_COLOR" %i л.\n"COLOR_WHITE"Расход на 100 км:"FLAME_COLOR" %i л.",
			VehicleNames[model - 400],
			GetVehicleColorName(PlayerGarage[playerid][slot][vColor1]),
			PlayerGarage[playerid][slot][vOwnerName],
			dateMX("%dd.%mm.%yyyy", PlayerGarage[playerid][slot][vBuyTime]),
			GetGarageMileage(playerid, slot),
			PlayerGarage[playerid][slot][vNumbers],
			GetVehicleMaxFuel(model),
			GetVehicleFuelConsumption(model));
	}
	else
	{
		format(string, sizeof(string), ""COLOR_WHITE"Модель:"FLAME_COLOR" %s\n"COLOR_WHITE"Конфигурация:"FLAME_COLOR" %s\n"COLOR_WHITE"Стоимость:"FLAME_COLOR" %i$\n"COLOR_WHITE"Цвет:"FLAME_COLOR" %s\n"COLOR_WHITE"Владелец:"FLAME_COLOR" %s\n"COLOR_WHITE"Дата покупки:"FLAME_COLOR" %s\n"COLOR_WHITE"Пробег:"FLAME_COLOR" %i км.\n"COLOR_WHITE"Номерной знак:"FLAME_COLOR" %s\n"COLOR_WHITE"Бак:"FLAME_COLOR" %i л.\n"COLOR_WHITE"Расход на 100 км:"FLAME_COLOR" %i л.",
			VehicleNames[model - 400],
			GetVehicleComplectationName(PlayerGarage[playerid][slot][vComp]),
			GetVehiclePrice(model),
			GetVehicleColorName(PlayerGarage[playerid][slot][vColor1]),
			PlayerGarage[playerid][slot][vOwnerName],
			dateMX("%dd.%mm.%yyyy", PlayerGarage[playerid][slot][vBuyTime]),
			GetGarageMileage(playerid, slot),
			PlayerGarage[playerid][slot][vNumbers],
			GetVehicleMaxFuel(model),
			GetVehicleFuelConsumption(model));
	}

	ShowPlayerDialog(playerid, D_VEHICLES_MENU_RETURN, DIALOG_STYLE_MSGBOX, !"Информация о транспорте", string, !"Назад", !"");
	return true;
}

ShowPlayerVehicleHelp(playerid, slot)
{
	if(PlayerGarage[playerid][slot][vType] == VEHICLE_TYPE_SHARING)
	{
		ShowPlayerDialog(playerid, D_VEHICLES_MENU_RETURN, DIALOG_STYLE_MSGBOX, !"Помощь", ""FLAME_COLOR"/lock"COLOR_WHITE" - закрыть/открыть транспорт.\n"FLAME_COLOR"/fixcar"COLOR_WHITE" - отправить транспорт на место парковки.", !"Назад", !"");
	}
	else
	{
		ShowPlayerDialog(playerid, D_VEHICLES_MENU_RETURN, DIALOG_STYLE_MSGBOX, !"Помощь", ""FLAME_COLOR"/lock"COLOR_WHITE" - закрыть/открыть транспорт.\n"FLAME_COLOR"/fixcar"COLOR_WHITE" - отправить транспорт на место парковки.\n"FLAME_COLOR"/sellcar"COLOR_WHITE" - продать транспорт государству (50 процентов от цены)\n"FLAME_COLOR"/sellcarto"COLOR_WHITE" - продать транспорт игроку", !"Назад", !"");
	}

	return true;
}

GetPlayerVehicleSlot(playerid, vehid)
{
	new result = -1;
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
	{
		if(!pData[playerid][pVehicles][i])
			break;
		if(pData[playerid][pVehicles][i] == vehid)
		{
			result = i;
			break;
		}
	}
	return result;
}

SavePlayerVehicles(playerid)
{
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
	{
		if(!IsGarageSlotUsed(playerid, i))
			break;
		if(pData[playerid][pVehicles][i])
			SaveVehicle(pData[playerid][pVehicles][i]);
	}

	return true;
}

GetNearestParkingPos(playerid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	new result = 0;
	new Float:best = 999999.0;
	for(new i = 0; i < sizeof(PARKING_POS); i++)
	{
		new Float:dist = VectorSize(PARKING_POS[i][0] - x, PARKING_POS[i][1] - y, PARKING_POS[i][2] - z);
		if(dist < best)
		{
			best = dist;
			result = i;
		}
	}

	return result;
}

CallPlayerVehicle(playerid, slot)
{
	if(PlayerGarage[playerid][slot][vType] == VEHICLE_TYPE_SHARING)
		return CallSharingVehicle(playerid, slot);

	new pos = GetNearestParkingPos(playerid);
	SpawnGarageVehicleAt(playerid, slot, PARKING_POS[pos][0], PARKING_POS[pos][1], PARKING_POS[pos][2], PARKING_POS[pos][3]);

	UpdatePlayerMoney(playerid, -CALL_VEHICLE_PRICE);
	SetPlayerCustomGPSMarker(playerid, PARKING_POS[pos][0], PARKING_POS[pos][1], PARKING_POS[pos][2]);
	SendClientMessageEx(playerid, -1, "Транспорт подан на ближайшую парковку за %i$. Метка установлена на карте.", CALL_VEHICLE_PRICE);
	return true;
}

IsPlayerNearVehicle(playerid, vehid, Float:range = 2.5)
{
	new Float:x, Float:y, Float:z;
	GetVehiclePos(vehid, x, y, z);
	return IsPlayerInRangeOfPoint(playerid, range, x, y, z) && GetPlayerInterior(playerid) == VI_GetVehicleInterior(vehid) && GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehid);
}

CanPlayerUseVehicle(playerid, vehid)
{
	if(VehicleInfo[vehid][vType] == VEHICLE_TYPE_SHARING && IsSharingVehicleExpired(vehid))
	{
		DeleteExpiredSharingVehicle(vehid);
		return false;
	}

    // Пропускаем проверку ключей для транспорта автошколы
    if(vehid >= DrivingLessonVehicles[0] && vehid < DrivingLessonVehicles[3])
        return true;

    // Пропускаем проверку ключей для транспорта, не помеченного как личный или каршеринг
    if(VehicleInfo[vehid][vType] != VEHICLE_TYPE_PERSONAL && VehicleInfo[vehid][vType] != VEHICLE_TYPE_SHARING)
        return true;

	if((VehicleInfo[vehid][vType] == VEHICLE_TYPE_PERSONAL || VehicleInfo[vehid][vType] == VEHICLE_TYPE_SHARING) 
		&& IsItemInInventory(playerid, 4, VehicleInfo[vehid][vID]))
		return true;
	return false;

}

SetFuelSystemCars()
{
	// DMV (Moto, Cars, Trucks)
	for(new i = DrivingLessonVehicles[0]; i < DrivingLessonVehicles[3]; i++)
	{
		if(IsValidVehicle(i))
		{
			VehicleInfo[i][vFuel] = random(9) + 12;
		}
	}
}

hook OnVehicleSpawn(vehicleid)
{
    if(vehicleid >= DrivingLessonVehicles[0] && vehicleid < DrivingLessonVehicles[2])
    {
        if(IsValidVehicle(vehicleid))
        {
            VehicleInfo[vehicleid][vFuel] = random(9) + 12; // Устанавливаем топливо только для этой машины
        }
    }
    return 1;
}

CMD:lock(playerid)
{

	foreach(new i : Vehicle)
	{
		if(IsPlayerNearVehicle(playerid, i) && CanPlayerUseVehicle(playerid, i))
		{
			VehicleInfo[i][vLocked] = !VehicleInfo[i][vLocked];
			UpdateVehicleParamsEx(i);
			SendClientMessageEx(playerid, -1, "Вы %s транспорт.", VehicleInfo[i][vLocked] ? "закрыли" : "открыли");
			return true;
		}
	}

	SendClientMessage(playerid, -1, !"Поблизости нет транспорта, который Вы могли бы открыть.");
	return true;
}

CMD:fixcar(playerid)
{
	if(pData[playerid][pMoney] < FIXCAR_PRICE)
		return SendClientMessage(playerid, -1, !"У Вас недостаточно денег!");

	new string[256];
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
	{
		if(!IsGarageSlotUsed(playerid, i))
			break;
		new vehName[64];
		GetGarageDisplayName(playerid, i, vehName);
		format(string, sizeof(string), "%s"FLAME_COLOR"%i."COLOR_WHITE" %s\n", string, i + 1, vehName);
	}

	if(strlen(string))
		return ShowPlayerDialog(playerid, D_VEHICLES_MENU_FIXCAR, DIALOG_STYLE_LIST, !"Починка транспорта - "#FIXCAR_PRICE"$", string, !"Далее", !"Закрыть");
	SendClientMessage(playerid, -1, !"Вы не владеете транспортом!");
	return true;
}

CMD:sellcar(playerid)
{
	new vehid = GetPlayerVehicleID(playerid);
	if(!vehid || GetPlayerState(playerid) != PLAYER_STATE_DRIVER || !IsPlayerVehicleOwner(playerid, vehid))
		return SendClientMessage(playerid, -1, !"Необходимо находиться за рулём своего транспорта!");

	new model = GetVehicleModel(vehid);

	new string[256];
	format(string, sizeof(string), "Вы собираетесь продать свой транспорт\n\
		Модель: %s\n\
		Номера: %s\n\
		Гос. стоимость: %i$\n\
		Цена продажи: %i$",
		VehicleNames[model - 400],
		VehicleInfo[vehid][vNumbers],
		GetVehiclePrice(model),
		GetVehicleSellCarPrice(model));

	ShowPlayerDialog(playerid, D_SELLCAR, DIALOG_STYLE_MSGBOX, !"Продажа транспорта", string, !"Далее", !"Закрыть");
	return true;
}

GetVehicleSellCarPrice(model)
{
	return floatround(GetVehiclePrice(model) / 2);
}
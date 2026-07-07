static const SHARING_PRICE_PER_DAY = 200;
static const SHARING_MAX_DAYS = 7;
static const SHARING_MAX_PLAYER_VEHICLES = 3;
static const SHARING_COLOR = 1;
static const SHARING_COMP = 0;
static const SHARING_SECONDS_IN_DAY = 86400;

static const SHARING_POS[pos_info] = {-2520.6536, 2337.1821, 4.9835, 0.0, 0, 0};

static const SHARING_VEHICLES[] =
{
	600, // Picador
	410, // Manana
	422, // Bobcat
	436, // Previon
	439  // Stallion
};

static const Float:SHARING_SPAWN_POS[][] =
{
	{-2538.2830, 2366.8088, 4.6619, 180.9403},
	{-2534.4321, 2366.3428, 4.6619, 182.4169},
	{-2530.5037, 2366.3003, 4.6624, 180.8981},
	{-2526.6040, 2365.9846, 4.6631, 180.6119},
	{-2522.7373, 2366.5012, 4.6632, 181.4138},
	{-2519.2183, 2366.1367, 4.6632, 182.2487}
};

VSharing_OnGameModeInit()
{
	CreateDynamicPickup(1239, 1, SHARING_POS[pX], SHARING_POS[pY], SHARING_POS[pZ], SHARING_POS[pVW], SHARING_POS[pInt]);
	CreateDynamic3DTextLabel("Каршеринг\nДля взаимодействия нажмите - "FLAME_COLOR"ALT", -1, SHARING_POS[pX], SHARING_POS[pY], SHARING_POS[pZ],
		5.0, .testlos = 1, .worldid = SHARING_POS[pVW], .interiorid = SHARING_POS[pInt]);

	return true;
}

VSharing_ButtonAltFoot(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 2.5, SHARING_POS[pX], SHARING_POS[pY], SHARING_POS[pZ])
		&& GetPlayerInterior(playerid) == SHARING_POS[pInt] && GetPlayerVirtualWorld(playerid) == SHARING_POS[pVW])
		return ShowPlayerVehiclesSharingDialog(playerid);

	return true;
}

VSharing_OnDialogResponse(playerid, dialogid, response, listitem, const inputtext[])
{
	switch(dialogid)
	{
		case D_VEHICLES_SHARING_LIST:
		{
			if(!response)
				return true;
			if(listitem < 0 || listitem >= sizeof(SHARING_VEHICLES))
				return true;

			SetPVarInt(playerid, "VSharingCar", listitem);
			ShowPlayerVehiclesSharingDays(playerid);
		}
		case D_VEHICLES_SHARING_DAYS:
		{
			if(!response)
				return true;

			new days = strval(inputtext);
			if(days < 1 || days > SHARING_MAX_DAYS)
			{
				SendClientMessage(playerid, COLOR_GREY, !"* Срок аренды должен быть от 1 до 7 дней.");
				return ShowPlayerVehiclesSharingDays(playerid);
			}

			SetPVarInt(playerid, "VSharingDays", days);
			ShowVSharingConfirm(playerid);
		}
		case D_VEHICLES_SHARING_CONFIRM:
		{
			if(!response)
				return true;

			PlayerRentSharingVehicle(playerid);
		}
	}

	return true;
}

VSharing_OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	#pragma unused playerid
	#pragma unused clickedid
	return true;
}

VSharing_PlayerSecTimer(playerid)
{
	if(GetPVarInt(playerid, "VSharingExpireCheck") > gettime())
		return true;

	SetPVarInt(playerid, "VSharingExpireCheck", gettime() + 30);
	ClearExpiredSharingVehicles(playerid, true);
	return true;
}

ShowPlayerVehiclesSharingDialog(playerid)
{
	ClearExpiredSharingVehicles(playerid, false);

	new string[512];
	for(new i = 0; i < sizeof(SHARING_VEHICLES); i++)
		format(string, sizeof(string), "%s"FLAME_COLOR"%i."COLOR_WHITE" %s\n", string, i + 1, VehicleNames[SHARING_VEHICLES[i] - 400]);

	ShowPlayerDialog(playerid, D_VEHICLES_SHARING_LIST, DIALOG_STYLE_LIST, !"Каршеринг", string, !"Выбрать", !"Выход");
	return true;
}

ShowPlayerVehiclesSharingDays(playerid)
{
	new car = GetPVarInt(playerid, "VSharingCar");
	if(car < 0 || car >= sizeof(SHARING_VEHICLES))
		return true;

	new model = SHARING_VEHICLES[car];
	new string[256];
	format(string, sizeof(string), ""FLAME_COLOR"Вы выбрали %s\n\n"COLOR_WHITE"Введите срок аренды от 1 до %i дней.\nСтоимость: "FLAME_COLOR"%i$"COLOR_WHITE" за день.",
		VehicleNames[model - 400],
		SHARING_MAX_DAYS,
		SHARING_PRICE_PER_DAY);

	ShowPlayerDialog(playerid, D_VEHICLES_SHARING_DAYS, DIALOG_STYLE_INPUT, !"Срок аренды", string, !"Далее", !"Отмена");
	return true;
}

ShowVSharingConfirm(playerid)
{
	new car = GetPVarInt(playerid, "VSharingCar");
	new days = GetPVarInt(playerid, "VSharingDays");
	if(car < 0 || car >= sizeof(SHARING_VEHICLES) || days < 1 || days > SHARING_MAX_DAYS)
		return true;

	new model = SHARING_VEHICLES[car];
	new price = GetSharingVehicleRentPrice(days);

	new string[512];
	format(string, sizeof(string), ""FLAME_COLOR"Подтвердите аренду транспорта\n\n\
		"COLOR_WHITE"Модель:"FLAME_COLOR" %s\n\
		"COLOR_WHITE"Срок:"FLAME_COLOR" %i дн.\n\
		"COLOR_WHITE"Цвет:"FLAME_COLOR" Белый\n\
		"COLOR_WHITE"Комплектация:"FLAME_COLOR" Стандартная\n\
		"COLOR_WHITE"Цена:"FLAME_COLOR" %i$",
		VehicleNames[model - 400],
		days,
		price);

	ShowPlayerDialog(playerid, D_VEHICLES_SHARING_CONFIRM, DIALOG_STYLE_MSGBOX, !"Подтверждение аренды", string, !"Арендовать", !"Отмена");
	return true;
}

PlayerRentSharingVehicle(playerid)
{
	ClearExpiredSharingVehicles(playerid, false);

	new car = GetPVarInt(playerid, "VSharingCar");
	new days = GetPVarInt(playerid, "VSharingDays");
	if(car < 0 || car >= sizeof(SHARING_VEHICLES) || days < 1 || days > SHARING_MAX_DAYS)
		return true;

	if(GetPlayerSharingVehiclesAmount(playerid) >= SHARING_MAX_PLAYER_VEHICLES)
		return SendClientMessage(playerid, COLOR_GREY, !"* Вы уже арендовали максимальное количество машин каршеринга.");

	if(GetInventoryFreeSlot(playerid) == -1)
		return SendClientMessage(playerid, COLOR_GREY, !"* В инвентаре нет места для ключей от транспорта.");

	new spawn = GetFreeSharingSpawnPos();
	if(spawn == -1)
		return SendClientMessage(playerid, COLOR_GREY, !"* Сейчас нет свободных мест для выдачи автомобиля.");

	new price = GetSharingVehicleRentPrice(days);
	if(pData[playerid][pMoney] < price)
		return SendClientMessage(playerid, COLOR_GREY, !"* У вас недостаточно денег!");

	new model = SHARING_VEHICLES[car];
	new rentExpires = gettime() + days * SHARING_SECONDS_IN_DAY;

	new temp[vehicle_info];
	temp[vModel] = model;
	temp[vSpawnPosX] = SHARING_SPAWN_POS[spawn][0];
	temp[vSpawnPosY] = SHARING_SPAWN_POS[spawn][1];
	temp[vSpawnPosZ] = SHARING_SPAWN_POS[spawn][2];
	temp[vSpawnPosFA] = SHARING_SPAWN_POS[spawn][3];
	temp[vColor1] = SHARING_COLOR;
	temp[vColor2] = SHARING_COLOR;
	GenerateVehicleNumbers(temp[vNumbers]);

	new vehid = CreateVehicleEx(temp);
	if(!vehid)
		return SendClientMessage(playerid, COLOR_GREY, !"* Не удалось создать автомобиль. Попробуйте позже.");

	UpdatePlayerMoney(playerid, -price);
	DeletePVar(playerid, "VSharingCar");
	DeletePVar(playerid, "VSharingDays");

	new ownerName[32];
	strmid(ownerName, pData[playerid][pName], 0, strlen(pData[playerid][pName]));
	strreplace(ownerName, "_", " ");

	new ms_string[512];
	new __ms2[] = "INSERT INTO vehicles (model, type, owner_id, owner_name, color1, color2, complectation, \
		spawn_pos_x, spawn_pos_y, spawn_pos_z, spawn_pos_fa, spawn_pos_int, spawn_pos_vw, fuel, buy_time, numbers) VALUES \
		(%i, %i, %i, '%e', %i, %i, %i, %f, %f, %f, %f, %i, %i, %f, %i, '%e')";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms2, model, VEHICLE_TYPE_SHARING, pData[playerid][pID], ownerName, SHARING_COLOR, SHARING_COLOR, SHARING_COMP, SHARING_SPAWN_POS[spawn][0], SHARING_SPAWN_POS[spawn][1], SHARING_SPAWN_POS[spawn][2], SHARING_SPAWN_POS[spawn][3], 0, 0, float(GetVehicleMaxFuel(model)), rentExpires, temp[vNumbers]);
	new __ms0[] = "PlayerRentSharingVehicle_CALL";
	new __ms1[] = "ii";
	mysql_tquery(ConnectMySQL, ms_string, __ms0, __ms1, playerid, vehid);

	VehicleInfo[vehid][vModel] = model;
	VehicleInfo[vehid][vType] = VEHICLE_TYPE_SHARING;
	VehicleInfo[vehid][vOwnerID] = pData[playerid][pID];
	strmid(VehicleInfo[vehid][vOwnerName], ownerName, 0, strlen(ownerName), VEHICLE_INFO_OWNER_NAME_LENGTH);
	VehicleInfo[vehid][vSpawnPosX] = SHARING_SPAWN_POS[spawn][0];
	VehicleInfo[vehid][vSpawnPosY] = SHARING_SPAWN_POS[spawn][1];
	VehicleInfo[vehid][vSpawnPosZ] = SHARING_SPAWN_POS[spawn][2];
	VehicleInfo[vehid][vSpawnPosFA] = SHARING_SPAWN_POS[spawn][3];
	VehicleInfo[vehid][vSpawnPosInt] = 0;
	VehicleInfo[vehid][vSpawnPosVW] = 0;
	VehicleInfo[vehid][vBuyTime] = rentExpires;
	VehicleInfo[vehid][vFuel] = float(GetVehicleMaxFuel(model));
	VehicleInfo[vehid][vColor1] = SHARING_COLOR;
	VehicleInfo[vehid][vColor2] = SHARING_COLOR;
	VehicleInfo[vehid][vComp] = SHARING_COMP;
	strmid(VehicleInfo[vehid][vNumbers], temp[vNumbers], 0, strlen(temp[vNumbers]), VEHICLE_INFO_NUMBERS_LENGTH);
	AddPlayerGarageVehicle(playerid, VehicleInfo[vehid], vehid);

	PutPlayerInVehicle(playerid, vehid, 0);
	Quest_OnPlayerRentSharingVehicle(playerid, days);
	return true;
}

forward PlayerRentSharingVehicle_CALL(playerid, vehid);
public PlayerRentSharingVehicle_CALL(playerid, vehid)
{
	VehicleInfo[vehid][vID] = cache_insert_id();
	AddItemInInventory(playerid, 4, VehicleInfo[vehid][vID], 1);

	new slot = GetPlayerVehicleSlot(playerid, vehid);
	if(slot != -1)
		PlayerGarage[playerid][slot][vID] = VehicleInfo[vehid][vID];

	SaveInventory(playerid);
	SendClientMessage(playerid, COLOR_GREY, !"* Вы успешно арендовали автомобиль каршеринга. Ключи добавлены в инвентарь.");
	return true;
}

GetSharingVehicleRentPrice(days)
{
	return SHARING_PRICE_PER_DAY * days;
}

CallSharingVehicle(playerid, slot)
{
	new spawn = GetFreeSharingSpawnPos();
	if(spawn == -1)
		return SendClientMessage(playerid, COLOR_GREY, !"* На стоянке проката нет свободного места. Попробуйте позже.");

	SpawnGarageVehicleAt(playerid, slot, SHARING_SPAWN_POS[spawn][0], SHARING_SPAWN_POS[spawn][1], SHARING_SPAWN_POS[spawn][2], SHARING_SPAWN_POS[spawn][3]);
	SetPlayerCustomGPSMarker(playerid, SHARING_SPAWN_POS[spawn][0], SHARING_SPAWN_POS[spawn][1], SHARING_SPAWN_POS[spawn][2]);
	SendClientMessage(playerid, -1, !"Арендный транспорт подан на стоянку проката. Метка установлена на карте.");
	return true;
}

GetPlayerSharingVehiclesAmount(playerid)
{
	return GetPlayerGarageSharingCount(playerid);
}

GetSharingOwnerID(vehid)
{
	if(!VehicleInfo[vehid][vID] || VehicleInfo[vehid][vType] != VEHICLE_TYPE_SHARING)
		return -1;

	new result = -1;
	foreach(new i : Player)
	{
		if(pData[i][pID] == VehicleInfo[vehid][vOwnerID])
		{
			result = i;
			break;
		}
	}

	return result;
}

IsSharingVehicleExpired(vehid)
{
	return (VehicleInfo[vehid][vType] == VEHICLE_TYPE_SHARING && VehicleInfo[vehid][vBuyTime] <= gettime());
}

DeleteExpiredSharingVehicle(vehid, bool:notify = true)
{
	if(VehicleInfo[vehid][vType] != VEHICLE_TYPE_SHARING)
		return false;

	new owner = GetSharingOwnerID(vehid);
	if(owner != -1 && notify)
		SendClientMessage(owner, COLOR_GREY, !"* Срок аренды автомобиля каршеринга истёк. Автомобиль и ключи удалены.");

	DeleteVehicle(vehid);

	if(owner != -1)
		SaveInventory(owner);

	return true;
}

ClearExpiredSharingVehicles(playerid, bool:notify = true)
{
	for(new s = 0; s < MAX_PLAYER_VEHICLES; s++)
	{
		if(!IsGarageSlotUsed(playerid, s))
			break;
		if(PlayerGarage[playerid][s][vType] == VEHICLE_TYPE_SHARING && IsGarageSharingExpired(playerid, s))
		{
			if(notify)
				SendClientMessage(playerid, COLOR_GREY, !"* Срок аренды автомобиля каршеринга истёк. Автомобиль и ключи удалены.");
			DeleteGarageVehicle(playerid, s);
			s--;
		}
	}
	return true;
}

GetFreeSharingSpawnPos()
{
	for(new i = 0; i < sizeof(SHARING_SPAWN_POS); i++)
	{
		if(IsSharingSpawnPosFree(i))
			return i;
	}

	return -1;
}

IsSharingSpawnPosFree(pos)
{
	foreach(new i : Vehicle)
	{
		if(VehicleInfo[i][vType] != VEHICLE_TYPE_SHARING || IsSharingVehicleExpired(i))
			continue;

		if(floatabs(VehicleInfo[i][vSpawnPosX] - SHARING_SPAWN_POS[pos][0]) < 0.1
			&& floatabs(VehicleInfo[i][vSpawnPosY] - SHARING_SPAWN_POS[pos][1]) < 0.1
			&& floatabs(VehicleInfo[i][vSpawnPosZ] - SHARING_SPAWN_POS[pos][2]) < 0.1)
			return false;
	}

	return true;
}

VSharing_NewDay()
{
	foreach(new i : Vehicle)
	{
		if(VehicleInfo[i][vType] == VEHICLE_TYPE_SHARING && IsSharingVehicleExpired(i))
			DeleteExpiredSharingVehicle(i, true);
	}

	return true;
}

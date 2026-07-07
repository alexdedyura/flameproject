static const VEHICLES_SHOP_POS[pos_info] = {-2090.3708, 240.4008, 827.2234, 50.4084, 3, 44};

static const VEHICLE_SHOP_PREVIEW_VW_CONST = 45;
static const VEHICLES_SHOP_PREVIEW_INT = 3;
static const Float:VEHICLES_SHOP_PREVIEW_CAR_POS[] = {-2083.3660, 233.4852, 826.9634, 239.9787};
static const Float:VEHICLES_SHOP_PREVIEW_CAM_POS[] = {-2074.91, 233.61, 829.32, -2084.33, 233.63, 825.97};

//static const Float:VEHICLES_SHOP_PREVIEW_PED_POS[] = {-2090.3708, 240.4008, 827.2234, 50.4084};

static const Float:VEHICLES_SHOP_BUY_POSES[][] = 
{
	{-1987.5217, 272.2326, 34.8339, 269.9772},
	{-1987.6689, 268.5462, 34.8364, 269.8009},
	{-1986.7078, 264.7422, 34.8363, 270.5257},
	{-1987.3999, 257.0233, 34.8307, 269.1211},
	{-1987.2338, 260.9263, 34.8348, 269.3534},
	{-1987.0914, 253.1857, 34.8284, 271.5576},
	{-1986.9768, 249.2226, 34.8289, 270.4928},
	{-1987.6178, 245.0858, 34.8285, 269.9169}
};

static const VEHICLES_SHOP_CATEGORIES_NAMES[][] = 
{
	""FLAME_COLOR"1."COLOR_WHITE" Стритрейсерские авто",
	""FLAME_COLOR"2."COLOR_WHITE" Гоночные авто",
	""FLAME_COLOR"3."COLOR_WHITE" Лоурайдеры",
	""FLAME_COLOR"4."COLOR_WHITE" Двухдверные седаны",
	""FLAME_COLOR"5."COLOR_WHITE" Четырёхдверные седаны",
	""FLAME_COLOR"6."COLOR_WHITE" Джипы",
	""FLAME_COLOR"7."COLOR_WHITE" Мощные авто",
	""FLAME_COLOR"8."COLOR_WHITE" Лёгкие грузовики и фургоны",
	""FLAME_COLOR"9."COLOR_WHITE" Велосипеды и мотоциклы"
};

static const VEHICLES_SHOP_CATEGORIES_MODELS[][] = 
{
	{562, 565, 559, 561, 560, 558}, // Стритрейсерские авто
	{429, 541, 415, 480, 434, 494, 502, 503, 411, 506, 451, 555, 477, 0}, // Гоночные авто
	{536, 575, 534, 567, 535, 576, 412, 0}, // Лоурайдеры
	{602, 496, 401, 518, 527, 589, 419, 587, 533, 526, 474, 545, 517, 410, 600, 436, 439, 549, 491, 0}, // Двухдверные седаны
	{445, 507, 585, 466, 492, 546, 551, 516, 467, 426, 547, 405, 580, 409, 550, 566, 540, 421, 529, 0}, // Четырёхдверные седаны
	{579, 400, 404, 489, 479, 442, 458, 0}, // Джипы
	{402, 542, 603, 475, 0}, // Мощные авто
	{459, 422, 482, 530, 418, 572, 582, 413, 440, 543, 583, 478, 554, 0}, // Лёгкие грузовики и фургоны
	{481, 509, 510, 581, 462, 521, 463, 522, 461, 448, 468, 586, 0} // Велосипеды и мотоциклы
};

static const VEHICLES_SHOP_COLORS[] = {1, 0, 36, 3, 6, 86, 79};

VShop_OnGameModeInit()
{
	CreateDynamicPickup(1239, 1, VEHICLES_SHOP_POS[pX], VEHICLES_SHOP_POS[pY], VEHICLES_SHOP_POS[pZ], VEHICLES_SHOP_POS[pVW], VEHICLES_SHOP_POS[pInt]);
	CreateDynamic3DTextLabel("Покупка автомобиля\nДля взаимодействия нажмите - "FLAME_COLOR"ALT", -1, VEHICLES_SHOP_POS[pX], VEHICLES_SHOP_POS[pY], VEHICLES_SHOP_POS[pZ], 5.0, .testlos = 1, 
		.worldid = VEHICLES_SHOP_POS[pVW], .interiorid = VEHICLES_SHOP_POS[pInt]);

	return true;
}

VShop_ButtonAltFoot(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 2.5, VEHICLES_SHOP_POS[pX], VEHICLES_SHOP_POS[pY], VEHICLES_SHOP_POS[pZ]) 
		&& GetPlayerInterior(playerid) == VEHICLES_SHOP_POS[pInt] && GetPlayerVirtualWorld(playerid) == VEHICLES_SHOP_POS[pVW])
		return ShowPlayerVehiclesShopDialog(playerid);

	return true;
}

VShop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	switch(dialogid)
	{
		case D_VEHICLES_SHOP:
		{
			if(!response)
				return true;

			ShowPlayerVehiclesShopCategory(playerid, listitem);

			return true;
		}
		case D_VEHICLES_SHOP_LIST:
		{
			if(!response)
				return ShowPlayerVehiclesShopDialog(playerid);

			SetTimerEx("ShowPlayerVehiclesShop_CALL", 100, false, "iii", playerid, GetPVarInt(playerid, "VShopCat"), listitem);
		}
		case D_VEHICLES_SHOP_BUY:
		{
			if(!response)
				return true;
			if(!GetPVarInt(playerid, "VShopShowed"))
				return true;

			new cat = GetPVarInt(playerid, "VShopCat");
			new model = VEHICLES_SHOP_CATEGORIES_MODELS[cat][GetPVarInt(playerid, "VShopCar")];
			new comp = GetPVarInt(playerid, "VShopComp");
			new price = GetVehiclesShopCarPrice(model, comp);
			if(pData[playerid][pMoney] < price)
				return SendClientMessage(playerid, COLOR_GREY, !"У вас недостаточно денег!");
			if(GetPlayerVehiclesAmount(playerid) >= MAX_PLAYER_PERSONAL_VEHICLES)
				return SendClientMessage(playerid, COLOR_GREY, !"У вас максимальное количество личного транспорта!");

			PlayerBuyVehicle(playerid);
			SendClientMessage(playerid, COLOR_GREY, !"Поздравляем с покупкой нового транспорта, он ждет вас на парковке автосалона!");
		}
	}

	return true;
}

VShop_OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(GetPVarInt(playerid, "VShopShowed"))
	{
		if(clickedid == INVALID_TEXT_DRAW)
		{
			new cat = GetPVarInt(playerid, "VShopCat");
			HidePlayerVehiclesShop(playerid);
			ShowPlayerVehiclesShopCategory(playerid, cat);
			return true;
		}

		if(clickedid == VehiclesShopTD[18])
			SetPlayerVehiclesShopComp(playerid, 0);
		else if(clickedid == VehiclesShopTD[19])
			SetPlayerVehiclesShopComp(playerid, 1);
		else if(clickedid == VehiclesShopTD[20])
			SetPlayerVehiclesShopComp(playerid, 2);
		else if(clickedid == VehiclesShopTD[24])
			ShowPlayerVehiclesShopBuy(playerid);
		else if(clickedid >= VehiclesShopTD[3] && clickedid <= VehiclesShopTD[15])
		{
			for(new i = 3, j = 0; i < 16; i += 2, j++)
				if(clickedid == VehiclesShopTD[i])
					return SetPlayerVehiclesShopColor(playerid, j);
		}

	}
	
	return true;
}

forward ShowPlayerVehiclesShop_CALL(playerid, cat, car);
public ShowPlayerVehiclesShop_CALL(playerid, cat, car)
{
	ShowPlayerVehilcesShop(playerid);
	ShowPlayerVehiclesShopCar(playerid, cat, car);
	return true;
}

ShowPlayerVehiclesShopDialog(playerid)
{
	new string[512];
	for(new i = 0; i < sizeof(VEHICLES_SHOP_CATEGORIES_NAMES); i++)
	{
		strcat(string, VEHICLES_SHOP_CATEGORIES_NAMES[i]);
		strcat(string, "\n");
	}

	ShowPlayerDialog(playerid, D_VEHICLES_SHOP, DIALOG_STYLE_LIST, "Тип транспорта", string, !"Далее", !"Выход");
	return true;
}

ShowPlayerVehiclesShopCategory(playerid, cat)
{
	SetPVarInt(playerid, "VShopCat", cat);

	new string[1024];
	for(new i = 0; VEHICLES_SHOP_CATEGORIES_MODELS[cat][i]; i++)
		format(string, sizeof(string), "%s"FLAME_COLOR"%i."COLOR_WHITE" %s\n", string, i + 1, VehicleNames[VEHICLES_SHOP_CATEGORIES_MODELS[cat][i] - 400]);

	ShowPlayerDialog(playerid, D_VEHICLES_SHOP_LIST, DIALOG_STYLE_LIST, !"Список моделей", string, !"Выбрать", !"Назад");
	return true;
}

SetPlayerVehiclesShopComp(playerid, comp)
{
	new oldcomp = GetPVarInt(playerid, "VShopComp");
	SetPVarInt(playerid, "VShopComp", comp);

	if(oldcomp != comp)
	{
		TextDrawBoxColor(VehiclesShopTD[18 + oldcomp], 235802367);
		TextDrawShowForPlayer(playerid, VehiclesShopTD[18 + oldcomp]);
	}

	TextDrawBoxColor(VehiclesShopTD[18 + comp], 8388863);
	TextDrawShowForPlayer(playerid, VehiclesShopTD[18 + comp]);

	UpdatePlayerVehiclesShopPrice(playerid);
	return true;
}

SetPlayerVehiclesShopColor(playerid, color)
{
	ChangeVehicleColor(GetPVarInt(playerid, "VShopCarID"), VEHICLES_SHOP_COLORS[color], VEHICLES_SHOP_COLORS[color]);
	SetPVarInt(playerid, "VShopColor", color);

	return true;
}

ShowPlayerVehiclesShopCar(playerid, cat, car)
{
	SetPVarInt(playerid, "VShopCar", car);

	DestroyPlayerVehiclesShopCar(playerid);

	new model = VEHICLES_SHOP_CATEGORIES_MODELS[cat][car];
	new vehid = CreateVehicle(model, VEHICLES_SHOP_PREVIEW_CAR_POS[pX], VEHICLES_SHOP_PREVIEW_CAR_POS[pY], VEHICLES_SHOP_PREVIEW_CAR_POS[pZ], 
		VEHICLES_SHOP_PREVIEW_CAR_POS[pFA], 1, 1, 0);
	LinkVehicleToInterior(vehid, VEHICLES_SHOP_PREVIEW_INT);
	SetVehicleVirtualWorld(vehid, VEHICLE_SHOP_PREVIEW_VW_CONST + playerid);

	SetPVarInt(playerid, "VShopCarID", vehid);

	new str[32];
	format(str, sizeof(str), "%s", StringToUpper(VehicleNames[model - 400]));
	PlayerTextDrawSetString(playerid, VehiclesShopPTD[playerid][1], str);
	format(str, sizeof(str), "ЂAK:_%i_‡", GetVehicleMaxFuel(model));
	PlayerTextDrawSetString(playerid, VehiclesShopPTD[playerid][0], str);

	SetPlayerVehiclesShopComp(playerid, 0);
	return true;
}

DestroyPlayerVehiclesShopCar(playerid)
{
	new vehid = GetPVarInt(playerid, "VShopCarID");
	if(IsValidVehicle(vehid))
		DestroyVehicle(vehid);

	DeletePVar(playerid, "VShopCarID");

	return true;
}

HidePlayerVehiclesShop(playerid)
{
	DeletePVar(playerid, "VShopCat");
	DeletePVar(playerid, "VShopComp");
	DeletePVar(playerid, "VShopCar");
	DeletePVar(playerid, "VShopShowed");

	HidePlayerVehiclesShopTD(playerid);
	DestroyPlayerVehiclesShopCar(playerid);

	SetPlayerPos(playerid, VEHICLES_SHOP_POS[pX], VEHICLES_SHOP_POS[pY], VEHICLES_SHOP_POS[pZ]);
	SetPlayerInterior(playerid, VEHICLES_SHOP_POS[pInt]);
	SetPlayerVirtualWorld(playerid, VEHICLES_SHOP_POS[pVW]);
	SetPlayerFacingAngle(playerid, VEHICLES_SHOP_POS[pFA]);
	SetCameraBehindPlayer(playerid);
	CancelSelectTextDraw(playerid);

	return true;
}

ShowPlayerVehilcesShop(playerid)
{
	ShowPlayerVehiclesShopTD(playerid);
	
	SendClientMessage(playerid, COLOR_GREY, !"*Если вы передумаете покупать автомобиль нажмите клавишу 'ESC'!");
	SetPlayerCameraPos(playerid, VEHICLES_SHOP_PREVIEW_CAM_POS[0], VEHICLES_SHOP_PREVIEW_CAM_POS[1], VEHICLES_SHOP_PREVIEW_CAM_POS[2]);
	SetPlayerCameraLookAt(playerid, VEHICLES_SHOP_PREVIEW_CAM_POS[3], VEHICLES_SHOP_PREVIEW_CAM_POS[4], VEHICLES_SHOP_PREVIEW_CAM_POS[5]);
	//SetPlayerPos(playerid, VEHICLES_SHOP_PREVIEW_PED_POS[0], VEHICLES_SHOP_PREVIEW_PED_POS[1], VEHICLES_SHOP_PREVIEW_PED_POS[2]);
	SetPlayerInterior(playerid, VEHICLES_SHOP_PREVIEW_INT);
	SetPlayerVirtualWorld(playerid, VEHICLE_SHOP_PREVIEW_VW_CONST + playerid);

	SetPVarInt(playerid, "VShopShowed", 1);
	SelectTextDraw(playerid, 0xAAAAAAFF);
	return true;
}

UpdatePlayerVehiclesShopPrice(playerid)
{
	new str[16];
	format(str, sizeof(str), "$%i", GetVehiclesShopCarPrice(VEHICLES_SHOP_CATEGORIES_MODELS[GetPVarInt(playerid, "VShopCat")][GetPVarInt(playerid, "VShopCar")],
		GetPVarInt(playerid, "VShopComp")));
	PlayerTextDrawSetString(playerid, VehiclesShopPTD[playerid][2], str);

	return true;
}

GetVehiclesShopCarPrice(model, comp)
{
	new result = GetVehiclePrice(model);

	switch(comp)
	{
		case 1:
			result = floatround(float(result) * 1.15);
		case 2:
			result = floatround(float(result) * 1.30);
	}

	return result;
}

ShowPlayerVehiclesShopBuy(playerid)
{
	new cat = GetPVarInt(playerid, "VShopCat");
	new model = VEHICLES_SHOP_CATEGORIES_MODELS[cat][GetPVarInt(playerid, "VShopCar")];
	new comp = GetPVarInt(playerid, "VShopComp");
	new color = GetPVarInt(playerid, "VShopColor");
	new price = GetVehiclesShopCarPrice(model, comp);

	new string[512];
	format(string, sizeof(string), ""FLAME_COLOR"Подтвердите покупку транспорта\n\
		"COLOR_WHITE"Категория:"FLAME_COLOR" %s\n\
		"COLOR_WHITE"Модель:"FLAME_COLOR" %s\n\
		"COLOR_WHITE"Комплектация:"FLAME_COLOR" %s\n\
		"COLOR_WHITE"Цвет:"FLAME_COLOR" %s\n\
		"COLOR_WHITE"Цена:"FLAME_COLOR" %i$",
		VEHICLES_SHOP_CATEGORIES_NAMES[cat],
		VehicleNames[model - 400],
		GetVehicleComplectationName(comp),
		GetVehicleColorName(VEHICLES_SHOP_COLORS[color]),
		price);

	ShowPlayerDialog(playerid, D_VEHICLES_SHOP_BUY, DIALOG_STYLE_MSGBOX, !"Подтверждение покупки", string, !"Далее", !"Отмена");
	return true;
}

PlayerBuyVehicle(playerid)
{
	new cat = GetPVarInt(playerid, "VShopCat");
	new model = VEHICLES_SHOP_CATEGORIES_MODELS[cat][GetPVarInt(playerid, "VShopCar")];
	new comp = GetPVarInt(playerid, "VShopComp");
	new color = VEHICLES_SHOP_COLORS[GetPVarInt(playerid, "VShopColor")];
	new price = GetVehiclesShopCarPrice(model, comp);

	HidePlayerVehiclesShop(playerid);
	UpdatePlayerMoney(playerid, -price);

	new pos = random(sizeof(VEHICLES_SHOP_BUY_POSES));

	new temp[vehicle_info];
	temp[vModel] = model;
	temp[vSpawnPosX] = VEHICLES_SHOP_BUY_POSES[pos][0];
	temp[vSpawnPosY] = VEHICLES_SHOP_BUY_POSES[pos][1];
	temp[vSpawnPosZ] = VEHICLES_SHOP_BUY_POSES[pos][2];
	temp[vSpawnPosFA] = VEHICLES_SHOP_BUY_POSES[pos][3];
	temp[vColor1] = color;
	temp[vColor2] = color;
	GenerateVehicleNumbers(temp[vNumbers]);

	new vehid = CreateVehicleEx(temp);

	new ownerName[32];
	strmid(ownerName, pData[playerid][pName], 0, strlen(pData[playerid][pName]));
	strreplace(ownerName, "_", " ");

	new ms_string[512];
	new __ms2[] = "INSERT INTO vehicles (model, type, owner_id, owner_name, color1, color2, complectation, \
		spawn_pos_x, spawn_pos_y, spawn_pos_z, spawn_pos_fa, spawn_pos_int, spawn_pos_vw, fuel, buy_time, numbers) VALUES \
		(%i, %i, %i, '%e', %i, %i, %i, %f, %f, %f, %f, %i, %i, %f, %i, '%e')";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms2, model, VEHICLE_TYPE_PERSONAL, pData[playerid][pID], ownerName, color, color, comp, VEHICLES_SHOP_BUY_POSES[pos][0], VEHICLES_SHOP_BUY_POSES[pos][1], VEHICLES_SHOP_BUY_POSES[pos][2], VEHICLES_SHOP_BUY_POSES[pos][3], 0, 0, float(GetVehicleMaxFuel(model)), gettime(), temp[vNumbers]);
	new __ms0[] = "PlayerBuyVehicle_CALL";
	new __ms1[] = "ii";
	mysql_tquery(ConnectMySQL, ms_string, __ms0, __ms1, playerid, vehid);

	VehicleInfo[vehid][vModel] = model;
	VehicleInfo[vehid][vType] = VEHICLE_TYPE_PERSONAL;
	VehicleInfo[vehid][vOwnerID] = pData[playerid][pID];
	VehicleInfo[vehid][vSpawnPosX] = VEHICLES_SHOP_BUY_POSES[pos][0];
	VehicleInfo[vehid][vSpawnPosY] = VEHICLES_SHOP_BUY_POSES[pos][1];
	VehicleInfo[vehid][vSpawnPosZ] = VEHICLES_SHOP_BUY_POSES[pos][2];
	VehicleInfo[vehid][vSpawnPosFA] = VEHICLES_SHOP_BUY_POSES[pos][3];
	VehicleInfo[vehid][vSpawnPosInt] = 0;
	VehicleInfo[vehid][vSpawnPosVW] = 0;
	VehicleInfo[vehid][vBuyTime] = gettime();
	VehicleInfo[vehid][vFuel] = float(GetVehicleMaxFuel(model));
	VehicleInfo[vehid][vColor1] = color;
	VehicleInfo[vehid][vColor2] = color;
	VehicleInfo[vehid][vComp] = comp;
	strmid(VehicleInfo[vehid][vNumbers], temp[vNumbers], 0, strlen(temp[vNumbers]), VEHICLE_INFO_NUMBERS_LENGTH);

	AddPlayerGarageVehicle(playerid, VehicleInfo[vehid], vehid);

	PutPlayerInVehicle(playerid, vehid, 0);
	return true;
}

forward PlayerBuyVehicle_CALL(playerid, vehid);
public PlayerBuyVehicle_CALL(playerid, vehid)
{
	VehicleInfo[vehid][vID] = cache_insert_id();
	AddItemInInventory(playerid, 4, VehicleInfo[vehid][vID], 1);
	new gslot = GetPlayerVehicleSlot(playerid, vehid);
	if(gslot != -1)
		PlayerGarage[playerid][gslot][vID] = VehicleInfo[vehid][vID];
	SavePlayer(playerid);
	return true;
}
Vehicles_OnVehicleSpawn(vehicleid)
{
	if(VehicleInfo[vehicleid][vType] != VEHICLE_TYPE_NONE)
	{
		if(IsVehicleUnspawned(vehicleid))
			SetVehicleVirtualWorld(vehicleid, 1330);
		else
			SetVehicleVirtualWorld(vehicleid, VehicleInfo[vehicleid][vSpawnPosVW]);

		LinkVehicleToInterior(vehicleid, VehicleInfo[vehicleid][vSpawnPosInt]);
	}
}

ClearVehicleInfo(vehid)
{
	VehicleInfo[vehid][vID] = 0;
	VehicleInfo[vehid][vType] = VEHICLE_TYPE_NONE;
	VehicleInfo[vehid][vOwnerID] = 0;
	VehicleInfo[vehid][vOwnerName] = EOS;
	VehicleInfo[vehid][vSpawnPosX] = 0.0;
	VehicleInfo[vehid][vSpawnPosY] = 0.0;
	VehicleInfo[vehid][vSpawnPosZ] = 0.0;
	VehicleInfo[vehid][vSpawnPosFA] = 0.0;
	VehicleInfo[vehid][vSpawnPosInt] = 0;
	VehicleInfo[vehid][vSpawnPosVW] = 0;
	VehicleInfo[vehid][vNumbers] = EOS;
	VehicleInfo[vehid][vBuyTime] = 0;
	VehicleInfo[vehid][vMileage] = 0.0;
	VehicleInfo[vehid][vFuel] = 0.0;
	VehicleInfo[vehid][vColor1] = 0;
	VehicleInfo[vehid][vColor2] = 0;
	VehicleInfo[vehid][vComp] = 0;

	VehicleInfo[vehid][vLocked] = 0;
	VehicleInfo[vehid][vEngine] = 0;
	VehicleInfo[vehid][vLights] = 0;
	VehicleInfo[vehid][vBoot] = 0;
	VehicleInfo[vehid][vBonnet] = 0;

	return true;
}

SaveVehicle(vehid)
{
	if(!VehicleInfo[vehid][vID])
		return true;

	new ms_string[1024];
	new __ms3[] = "UPDATE vehicles SET \
		model=%i,\
		type=%i,\
		owner_id=%i,\
		owner_name='%e',\
		spawn_pos_x=%f,\
		spawn_pos_y=%f,\
		spawn_pos_z=%f,\
		spawn_pos_fa=%f,\
		spawn_pos_int=%i,\
		spawn_pos_vw=%i,\
		numbers='%e',\
		buy_time=%i,\
		mileage=%f,\
		color1=%i,\
		color2=%i,\
		complectation=%i,\
		tax_weeks=%i,\
		fuel=%f \
		WHERE id = %i";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms3, VehicleInfo[vehid][vModel], VehicleInfo[vehid][vType], VehicleInfo[vehid][vOwnerID], VehicleInfo[vehid][vOwnerName], VehicleInfo[vehid][vSpawnPosX], VehicleInfo[vehid][vSpawnPosY], VehicleInfo[vehid][vSpawnPosZ], VehicleInfo[vehid][vSpawnPosFA], VehicleInfo[vehid][vSpawnPosInt], VehicleInfo[vehid][vSpawnPosVW], VehicleInfo[vehid][vNumbers], VehicleInfo[vehid][vBuyTime], VehicleInfo[vehid][vMileage], VehicleInfo[vehid][vColor1], VehicleInfo[vehid][vColor2], VehicleInfo[vehid][vComp], VehicleInfo[vehid][vTaxWeeks], VehicleInfo[vehid][vFuel], VehicleInfo[vehid][vID]);

	mysql_tquery(ConnectMySQL, ms_string);

	return true;
}

forward LoadVehicles(playerid);
public LoadVehicles(playerid)
{
	new rows = cache_num_rows();

	for(new i = 0; i < rows; i++)
	{
		new temp[vehicle_info];
		temp[vID] = cache_get_field_content_int(i, "id");
		if(GetGarageSlotByDBID(playerid, temp[vID]) != -1)
			continue;

		temp[vModel] = cache_get_field_content_int(i, "model");
		temp[vType] = cache_get_field_content_int(i, "type");
		temp[vOwnerID] = cache_get_field_content_int(i, "owner_id");
		cache_get_field_content(i, "owner_name", temp[vOwnerName], ConnectMySQL, 32);
		temp[vSpawnPosX] = cache_get_field_content_float(i, "spawn_pos_x");
		temp[vSpawnPosY] = cache_get_field_content_float(i, "spawn_pos_y");
		temp[vSpawnPosZ] = cache_get_field_content_float(i, "spawn_pos_z");
		temp[vSpawnPosFA] = cache_get_field_content_float(i, "spawn_pos_fa");
		temp[vSpawnPosInt] = cache_get_field_content_int(i, "spawn_pos_int");
		temp[vSpawnPosVW] = cache_get_field_content_int(i, "spawn_pos_vw");
		cache_get_field_content(i, "numbers", temp[vNumbers], ConnectMySQL, 32);
		temp[vBuyTime] = cache_get_field_content_int(i, "buy_time");
		temp[vMileage] = cache_get_field_content_float(i, "mileage");
		temp[vFuel] = cache_get_field_content_float(i, "fuel");
		temp[vColor1] = cache_get_field_content_int(i, "color1");
		temp[vColor2] = cache_get_field_content_int(i, "color2");
		temp[vComp] = cache_get_field_content_int(i, "complectation");
		temp[vTaxWeeks] = cache_get_field_content_int(i, "tax_weeks");

		if(temp[vType] == VEHICLE_TYPE_SHARING && temp[vBuyTime] <= gettime())
		{
			DeleteVehicleDB(temp[vID]);
			SaveInventory(playerid);
			if(IsPlayerConnected(playerid))
				SendClientMessageEx(playerid, COLOR_GREY, "* јренда автомобил€ %s истекла. јрендуйте новый при необходимости.", VehicleNames[temp[vModel] - 400]);
			continue;
		}

		if(temp[vType] == VEHICLE_TYPE_PERSONAL && temp[vTaxWeeks] >= DELETE_TAX_WEEKS)
		{
			DeleteVehicleDB(temp[vID]);
			SaveInventory(playerid);
			if(IsPlayerConnected(playerid))
				SendClientMessageEx(playerid, COLOR_GREY, "* ¬аш автомобиль %s был изъ€т государством за долги по налогам.", VehicleNames[temp[vModel] - 400]);
			continue;
		}

		AddPlayerGarageVehicle(playerid, temp, 0);
	}

	return true;
}

DeleteVehicleDB(dbid)
{
	if(dbid <= 0)
		return false;

	new ms_string[128];
	new __q[] = "DELETE FROM vehicles WHERE id = %i";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __q, dbid);
	mysql_tquery(ConnectMySQL, ms_string);

	DeleteVehicleKeys(dbid);
	return true;
}

LoadVehiclesForPlayer(playerid)
{
	new vehicles[256];

	for(new i = 0; i < sizeof(PlayerInventory[]); i++)
	{
		if(PlayerInventory[playerid][i][invID] == 4)
		{
			if(!strlen(vehicles))
				format(vehicles, sizeof(vehicles), "id = %i", PlayerInventory[playerid][i][invParam]);
			else 
				format(vehicles, sizeof(vehicles), "%s OR id = %i", vehicles, PlayerInventory[playerid][i][invParam]);
		}
	}

	if(strlen(vehicles))
	{
		new ms_string[512];
		new __ms2[] = "SELECT * FROM vehicles WHERE %e";
		mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms2, vehicles);
		new __ms1[] = "LoadVehicles";
		new __ms0[] = "i";
		mysql_tquery(ConnectMySQL, ms_string, __ms1, __ms0, playerid);
	}

	return true;
}

CopyVehicleInfo(const from[vehicle_info], to[vehicle_info])
{
	to[vID] = from[vID];
	to[vModel] = from[vModel];
	to[vOwnerID] = from[vOwnerID];
	strmid(to[vOwnerName], from[vOwnerName], 0, strlen(from[vOwnerName]), VEHICLE_INFO_OWNER_NAME_LENGTH);
	to[vSpawnPosX] = from[vSpawnPosX];
	to[vSpawnPosY] = from[vSpawnPosY];
	to[vSpawnPosZ] = from[vSpawnPosZ];
	to[vSpawnPosFA] = from[vSpawnPosFA];
	to[vSpawnPosInt] = from[vSpawnPosInt];
	to[vSpawnPosVW] = from[vSpawnPosVW];
	strmid(to[vNumbers], from[vNumbers], 0, strlen(from[vNumbers]), VEHICLE_INFO_NUMBERS_LENGTH);
	to[vBuyTime] = from[vBuyTime];
	to[vMileage] = from[vMileage];
	to[vFuel] = from[vFuel];
	to[vColor1] = from[vColor1];
	to[vColor2] = from[vColor2];
	to[vComp] = from[vComp];
	to[vTaxWeeks] = from[vTaxWeeks];

	to[vLocked] = from[vLocked];
	to[vEngine] = from[vEngine];
	to[vLights] = from[vLights];
	to[vBoot] = from[vBoot];
	to[vBonnet] = from[vBonnet];

	return true;
}

RecreateVehicle(vehid)
{
	DestroyVehicle(vehid);

	new newvehid = CreateVehicleEx(VehicleInfo[vehid]);
	if(newvehid != vehid)
	{
		CopyVehicleInfo(VehicleInfo[vehid], VehicleInfo[newvehid]);
		new ownerID = GetVehiclePlayerID(vehid);
		if(ownerID != -1)
		{
			new slot = GetPlayerVehicleSlot(ownerID, vehid);
			if(slot != -1)
				pData[ownerID][pVehicles][slot] = newvehid;
		}
		ClearVehicleInfo(vehid);
	}

	return newvehid;
}

CreateVehicleEx(const info[vehicle_info])
{
	new vehid = CreateVehicle(info[vModel], info[vSpawnPosX], info[vSpawnPosY], info[vSpawnPosZ], info[vSpawnPosFA], info[vColor1], info[vColor2], -1);
	SetVehicleNumberPlate(vehid, info[vNumbers]);
	SetVehicleToRespawn(vehid);

	return vehid;
}

DeleteVehicle(vehid)
{
	if(VehicleInfo[vehid][vType] == VEHICLE_TYPE_NONE)
		return true;

	new dbid = VehicleInfo[vehid][vID];
	new ownerID = GetVehiclePlayerID(vehid);

	DestroyVehicle(vehid);

	DeleteVehicleDB(dbid);
	ClearVehicleInfo(vehid);

	if(ownerID != -1)
	{
		new slot = GetGarageSlotByDBID(ownerID, dbid);
		if(slot != -1)
			RemovePlayerGarageSlot(ownerID, slot);
	}
	return true;
}

DeleteVehicleKeys(vehID)
{
	foreach(new i : Player)
	{
		new slot = GetItemInInventorySlot(i, 4, vehID);
		if(slot != -1)
		{
			ClearPlayerInventorySlot(i, slot);
			if(InventoryShowed[i])
			{
				UpdateInventoryCell(i, slot);
				RefreshInventoryWeightText(i);
			}
		}
	}

	return true;
}

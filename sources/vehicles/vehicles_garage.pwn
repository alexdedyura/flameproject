// On-demand vehicle garage.
//
// Vehicles are NOT created in the world on login. Instead every owned/rented
// vehicle of an online player is loaded as metadata into PlayerGarage, and the
// physical vehicle is created only when the player calls it ("Vyzvat transport").
//
// Slot occupancy marker: PlayerGarage[pid][slot][vModel] != 0 (model is 400..611,
// never 0). The DB id (vID) may be 0 briefly for a just-bought vehicle until the
// INSERT callback returns, so it must NOT be used as the occupancy marker.
//
// pData[playerid][pVehicles][slot] = in-world vehicleid when this slot is spawned,
// or 0 when the vehicle is stored (not in the world).

new PlayerGarage[MAX_PLAYERS][MAX_PLAYER_VEHICLES][vehicle_info];

ClearGarageSlot(playerid, slot)
{
	PlayerGarage[playerid][slot][vID] = 0;
	PlayerGarage[playerid][slot][vModel] = 0;
	PlayerGarage[playerid][slot][vType] = VEHICLE_TYPE_NONE;
	PlayerGarage[playerid][slot][vOwnerID] = 0;
	PlayerGarage[playerid][slot][vOwnerName] = EOS;
	PlayerGarage[playerid][slot][vNumbers] = EOS;
	PlayerGarage[playerid][slot][vSpawnPosX] = 0.0;
	PlayerGarage[playerid][slot][vSpawnPosY] = 0.0;
	PlayerGarage[playerid][slot][vSpawnPosZ] = 0.0;
	PlayerGarage[playerid][slot][vSpawnPosFA] = 0.0;
	PlayerGarage[playerid][slot][vSpawnPosInt] = 0;
	PlayerGarage[playerid][slot][vSpawnPosVW] = 0;
	PlayerGarage[playerid][slot][vBuyTime] = 0;
	PlayerGarage[playerid][slot][vMileage] = 0.0;
	PlayerGarage[playerid][slot][vFuel] = 0.0;
	PlayerGarage[playerid][slot][vColor1] = 0;
	PlayerGarage[playerid][slot][vColor2] = 0;
	PlayerGarage[playerid][slot][vComp] = 0;
	PlayerGarage[playerid][slot][vTaxWeeks] = 0;
	return true;
}

ClearPlayerGarage(playerid)
{
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
	{
		ClearGarageSlot(playerid, i);
		pData[playerid][pVehicles][i] = 0;
	}
	return true;
}

IsGarageSlotUsed(playerid, slot)
{
	if(slot < 0 || slot >= MAX_PLAYER_VEHICLES)
		return false;
	return (PlayerGarage[playerid][slot][vModel] != 0);
}

GetFreeGarageSlot(playerid)
{
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
		if(!IsGarageSlotUsed(playerid, i))
			return i;
	return -1;
}

GetGarageSlotByDBID(playerid, dbid)
{
	if(dbid <= 0)
		return -1;
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
		if(IsGarageSlotUsed(playerid, i) && PlayerGarage[playerid][i][vID] == dbid)
			return i;
	return -1;
}

AddPlayerGarageVehicle(playerid, const info[vehicle_info], spawnedVehid = 0)
{
	new slot = GetFreeGarageSlot(playerid);
	if(slot == -1)
		return -1;

	CopyVehicleInfo(info, PlayerGarage[playerid][slot]);
	pData[playerid][pVehicles][slot] = spawnedVehid;
	return slot;
}

RemovePlayerGarageSlot(playerid, slot)
{
	if(slot < 0 || slot >= MAX_PLAYER_VEHICLES)
		return false;

	for(new i = slot; i < MAX_PLAYER_VEHICLES - 1; i++)
	{
		CopyVehicleInfo(PlayerGarage[playerid][i + 1], PlayerGarage[playerid][i]);
		pData[playerid][pVehicles][i] = pData[playerid][pVehicles][i + 1];
	}
	ClearGarageSlot(playerid, MAX_PLAYER_VEHICLES - 1);
	pData[playerid][pVehicles][MAX_PLAYER_VEHICLES - 1] = 0;
	return true;
}

IsGarageSharingExpired(playerid, slot)
{
	return (PlayerGarage[playerid][slot][vType] == VEHICLE_TYPE_SHARING
		&& PlayerGarage[playerid][slot][vBuyTime] <= gettime());
}

GetPlayerGaragePersonalCount(playerid)
{
	new c = 0;
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
		if(IsGarageSlotUsed(playerid, i) && PlayerGarage[playerid][i][vType] == VEHICLE_TYPE_PERSONAL)
			c++;
	return c;
}

GetPlayerGarageSharingCount(playerid)
{
	new c = 0;
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
		if(IsGarageSlotUsed(playerid, i) && PlayerGarage[playerid][i][vType] == VEHICLE_TYPE_SHARING && !IsGarageSharingExpired(playerid, i))
			c++;
	return c;
}

GetGarageDisplayName(playerid, slot, name[], maxname = sizeof name)
{
	new model = PlayerGarage[playerid][slot][vModel];
	if(model < 400 || model > 611)
		return false;

	if(PlayerGarage[playerid][slot][vType] == VEHICLE_TYPE_SHARING)
		format(name, maxname, "%s (аренда)", VehicleNames[model - 400]);
	else
		format(name, maxname, "%s", VehicleNames[model - 400]);
	return true;
}

// When a slot is currently spawned, its live state (mileage/fuel/tax) lives in
// VehicleInfo. Refresh the garage copy from it so menus/info show fresh data.
SyncGarageFromSpawn(playerid, slot)
{
	new vehid = pData[playerid][pVehicles][slot];
	if(vehid && IsValidVehicle(vehid) && VehicleInfo[vehid][vID] == PlayerGarage[playerid][slot][vID])
		CopyVehicleInfo(VehicleInfo[vehid], PlayerGarage[playerid][slot]);
	return true;
}

IsGarageHaveTaxes(playerid, slot)
{
	return (PlayerGarage[playerid][slot][vTaxWeeks] > 0);
}

GetGarageTaxAmount(playerid, slot)
{
	return GetVehicleTax(PlayerGarage[playerid][slot][vModel]) * PlayerGarage[playerid][slot][vTaxWeeks];
}

GetGarageMileage(playerid, slot)
{
	return floatround(PlayerGarage[playerid][slot][vMileage], floatround_floor);
}

// Remove a stored (not necessarily spawned) vehicle from DB + keys + garage.
DeleteGarageVehicle(playerid, slot)
{
	if(!IsGarageSlotUsed(playerid, slot))
		return false;

	new vehid = pData[playerid][pVehicles][slot];
	if(vehid && IsValidVehicle(vehid))
	{
		DeleteVehicle(vehid); // handles DB + keys + garage slot removal
		return true;
	}

	DeleteVehicleDB(PlayerGarage[playerid][slot][vID]);
	SaveInventory(playerid);
	RemovePlayerGarageSlot(playerid, slot);
	return true;
}

// Is the given in-world vehicle referenced as spawned by some OTHER online player
// (shared key scenario)? Used to avoid destroying it on disconnect.
IsVehicleReferencedByOther(playerid, vehid)
{
	if(!vehid)
		return false;
	foreach(new i : Player)
	{
		if(i == playerid)
			continue;
		for(new s = 0; s < MAX_PLAYER_VEHICLES; s++)
			if(IsGarageSlotUsed(i, s) && pData[i][pVehicles][s] == vehid)
				return true;
	}
	return false;
}

// Bring the stored vehicle in `slot` into the world (or reuse an already spawned
// instance from a shared key) and place it at x,y,z,a. Returns the in-world vehid.
SpawnGarageVehicleAt(playerid, slot, Float:x, Float:y, Float:z, Float:a)
{
	PlayerGarage[playerid][slot][vSpawnPosX] = x;
	PlayerGarage[playerid][slot][vSpawnPosY] = y;
	PlayerGarage[playerid][slot][vSpawnPosZ] = z;
	PlayerGarage[playerid][slot][vSpawnPosFA] = a;
	PlayerGarage[playerid][slot][vSpawnPosInt] = 0;
	PlayerGarage[playerid][slot][vSpawnPosVW] = 0;

	new vehid = pData[playerid][pVehicles][slot];
	if(!vehid)
		vehid = GetVehicleByID(PlayerGarage[playerid][slot][vID]);

	if(vehid && IsValidVehicle(vehid))
	{
		// Already in the world (called before, or spawned via shared key) - relocate it.
		VehicleInfo[vehid][vSpawnPosX] = x;
		VehicleInfo[vehid][vSpawnPosY] = y;
		VehicleInfo[vehid][vSpawnPosZ] = z;
		VehicleInfo[vehid][vSpawnPosFA] = a;
		VehicleInfo[vehid][vSpawnPosInt] = 0;
		VehicleInfo[vehid][vSpawnPosVW] = 0;

		new Float:health;
		GetVehicleHealth(vehid, health);
		new newvehid = RecreateVehicle(vehid);
		SetVehicleHealth(newvehid, health);
		pData[playerid][pVehicles][slot] = newvehid;
		return newvehid;
	}

	// Create a fresh instance from the stored metadata.
	new freshid = CreateVehicleEx(PlayerGarage[playerid][slot]);
	CopyVehicleInfo(PlayerGarage[playerid][slot], VehicleInfo[freshid]);
	pData[playerid][pVehicles][slot] = freshid;
	return freshid;
}

// On disconnect: persist any spawned vehicles, despawn them (unless a shared-key
// holder still references them) and wipe the garage. Called from OnPlayerDisconnect
// AFTER SavePlayer so DB state is already flushed.
Vehicles_OnPlayerDisconnect(playerid)
{
	for(new i = 0; i < MAX_PLAYER_VEHICLES; i++)
	{
		new vehid = pData[playerid][pVehicles][i];
		if(vehid && IsGarageSlotUsed(playerid, i))
		{
			SaveVehicle(vehid);
			if(!IsVehicleReferencedByOther(playerid, vehid))
			{
				DestroyVehicle(vehid);
				ClearVehicleInfo(vehid);
			}
		}
	}
	ClearPlayerGarage(playerid);
	return true;
}

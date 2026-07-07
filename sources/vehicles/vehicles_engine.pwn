#define MILEAGE_ENGINE_OFF 25_000
#define MILEAGE_ENGINE_BROKEN 30_000

VEngine_PlayerSecTimer(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehid = GetPlayerVehicleID(playerid);
		if(!VehicleInfo[vehid][vEngine])
			return true;
		
		new mileage = GetVehicleMileage(vehid);
		if(mileage >= MILEAGE_ENGINE_BROKEN)
		{
			SetVehicleEngine(vehid, false);
			SendClientMessage(playerid, -1, !"Двигатель сломан, необходима замена!");
		}
		else if(mileage >= MILEAGE_ENGINE_OFF)
		{
			if(!(random(10)))
			{
				SetVehicleEngine(vehid, false);
				SendClientMessage(playerid, -1, !"Двигатель неисправен!");
			}
		}
	}

	return true;
}

IsVehicleEngineBroken(vehid)
{
	return (GetVehicleMileage(vehid) >= MILEAGE_ENGINE_BROKEN);
}


// Test
CMD:setmileage(playerid, params[])
{
	extract params -> new vehid, mileage; else
		return SendClientMessage(playerid, -1, !"vehid mileage");

	VehicleInfo[vehid][vMileage] = mileage;
	return true;
}
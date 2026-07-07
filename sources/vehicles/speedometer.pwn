new SpeedometerTimer[MAX_PLAYERS];

Speed_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason

	KillTimer(SpeedometerTimer[playerid]);
	SpeedometerTimer[playerid] = 0;

	return true;
}

Speed_OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER && oldstate != PLAYER_STATE_DRIVER)
	{
		ShowPlayerSpeedometer(playerid);
		SpeedometerTimer[playerid] = SetTimerEx("UpdateSpeedometer", 100, true, "i", playerid);
	}
	else if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
	{
		HidePlayerSpeedometer(playerid);
		KillTimer(SpeedometerTimer[playerid]);
		SpeedometerTimer[playerid] = 0;
	}
}


ShowPlayerSpeedometer(playerid)
{
	for(new i = 0; i < sizeof(SpeedometerTD); i++)
		TextDrawShowForPlayer(playerid, SpeedometerTD[i]);

	for(new i = 0; i < sizeof(SpeedometerPTD[]); i++)
		PlayerTextDrawShow(playerid, SpeedometerPTD[playerid][i]);

	return true;
}

HidePlayerSpeedometer(playerid)
{
	for(new i = 0; i < sizeof(SpeedometerTD); i++)
		TextDrawHideForPlayer(playerid, SpeedometerTD[i]);

	for(new i = 0; i < sizeof(SpeedometerPTD[]); i++)
		PlayerTextDrawHide(playerid, SpeedometerPTD[playerid][i]);

	return true;
}

forward UpdateSpeedometer(playerid);
public UpdateSpeedometer(playerid)
{
	new vehid = GetPlayerVehicleID(playerid);

	new speed = GetVehicleSpeed(vehid);

	new str[32];
	valstr(str, speed);
	PlayerTextDrawSetString(playerid, SpeedometerPTD[playerid][2], str);

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehid, engine, lights, alarm, doors, bonnet, boot, objective);

	TextDrawColor(SpeedometerTD[11], !doors ? 8388863 : -347323649);
	TextDrawColor(SpeedometerTD[12], lights ? 8388863 : -347323649);

	TextDrawShowForPlayer(playerid, SpeedometerTD[11]);
	TextDrawShowForPlayer(playerid, SpeedometerTD[12]);

	new Float:dist = float(speed) / 36000.0; // подсчет пробега

	VehicleInfo[vehid][vMileage] += dist;

	format(str, sizeof(str), "МPOАEВ:_%i_KM", GetVehicleMileage(vehid));
	PlayerTextDrawSetString(playerid, SpeedometerPTD[playerid][1], str);


	if(VehicleInfo[vehid][vEngine])
	{
		VehicleInfo[vehid][vFuel] -= dist / 100.0 * GetVehicleFuelConsumption(GetVehicleModel(vehid));
		if(VehicleInfo[vehid][vFuel] <= 0.0)
		{
			VehicleInfo[vehid][vFuel] = 0.0;
			VehicleInfo[vehid][vEngine] = 0;
			UpdateVehicleParamsEx(vehid);
			SendClientMessage(playerid, -1, !"ƒвигатель заглох!");
		}
	}
	

	format(str, sizeof(str), "ПOМЗЕЛO:_%i_З", GetVehicleFuel(vehid));
	PlayerTextDrawSetString(playerid, SpeedometerPTD[playerid][0], str);

	BoostVehicle(playerid);
	return true;
}

GetVehicleSpeed(vehid)
{
	new Float:x, Float:y, Float:z;
	GetVehicleVelocity(vehid, x, y, z);
	return floatround(floatsqroot(x * x + y * y + z * z) * 180.0);
}
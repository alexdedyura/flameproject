UpdateVehicleParamsEx(vehid)
{
	SetVehicleParamsEx(vehid, VehicleInfo[vehid][vEngine], VehicleInfo[vehid][vLights], 0, VehicleInfo[vehid][vLocked], VehicleInfo[vehid][vBonnet], VehicleInfo[vehid][vBoot], 0);
	return true;
}

CMD:en(playerid) return cmd_engine(playerid);
CMD:engine(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))  
		return true;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) 
		return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");

	new vehid = GetPlayerVehicleID(playerid);
	if(!CanPlayerUseVehicle(playerid, vehid))
		return SendClientMessage(playerid, -1, !"У Вас нет ключей от этого транспорта!");
	if(IsVehicleEngineBroken(vehid))
		return SendClientMessage(playerid, -1, !"Двигатель транспорта неисправен!");
	if(!VehicleInfo[vehid][vFuel])
		return SendClientMessage(playerid, COLOR_GREY, !"* В транспорте нет топлива!");
	
	VehicleInfo[vehid][vEngine] = !VehicleInfo[vehid][vEngine];
	UpdateVehicleParamsEx(vehid);
	return true;
}

CMD:li(playerid) return cmd_lights(playerid);
CMD:lights(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))  
		return true;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) 
		return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	new vehid = GetPlayerVehicleID(playerid);
	if(!CanPlayerUseVehicle(playerid, vehid))
		return true;

	VehicleInfo[vehid][vLights] = !VehicleInfo[vehid][vLights];
	UpdateVehicleParamsEx(vehid);
	return true;
}

CMD:bonnet(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))  
		return true;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) 
		return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	new vehid = GetPlayerVehicleID(playerid);
	if(!CanPlayerUseVehicle(playerid, vehid))
		return true;
	
	VehicleInfo[vehid][vBonnet] = !VehicleInfo[vehid][vBonnet];
	UpdateVehicleParamsEx(vehid);
	return true;
}

CMD:boot(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))  
		return true;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) 
		return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	new vehid = GetPlayerVehicleID(playerid);
	if(!CanPlayerUseVehicle(playerid, vehid))
		return true;

	VehicleInfo[vehid][vBoot] = !VehicleInfo[vehid][vBoot];
	UpdateVehicleParamsEx(vehid);
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(GetPVarInt(playerid, !"VehicleNitro"))
		{
			if(newkeys & KEY_ACTION && !(oldkeys & KEY_ACTION) || newkeys & KEY_FIRE && !(oldkeys & KEY_FIRE)) return AddVehicleComponent(GetPlayerVehicleID(playerid), 1010);
		}
		if(newkeys & KEY_SUBMISSION && !(oldkeys & KEY_SUBMISSION)) return cmd_engine(playerid);
		else if(newkeys & KEY_FIRE && !(oldkeys & KEY_FIRE)) return cmd_lights(playerid);
	}
	return true;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER && GetPVarInt(playerid, !"VehicleNitro")) DeletePVar(playerid, !"VehicleNitro");
	return true;
}

SetVehicleEngine(vehid, status)
{
	VehicleInfo[vehid][vEngine] = status;
	UpdateVehicleParamsEx(vehid);
	return true;
}
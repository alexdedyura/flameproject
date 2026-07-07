#include <YSI_Coding\y_hooks>

CMD:setfuel(playerid, params[])
{
	extract params -> new vehid, Float:amount; else
		return SendClientMessage(playerid, -1, !"/setfuel [vehid] [amount]");

	if(!IsValidVehicle(vehid))
		return SendClientMessage(playerid, -1, !"Недействительный транспорт!");

	VehicleInfo[vehid][vFuel] = amount;
	SendClientMessage(playerid, -1, !"Success");

	return true;
}

CMD:getveh(playerid, params[])
{
	extract params -> new vehid; else
		return SendClientMessage(playerid, -1, !"/getveh [vehid]");

	if(!IsValidVehicle(vehid))
		return SendClientMessage(playerid, -1, !"Недействительный транспорт!");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetVehiclePos(vehid, x, y, z);
	return true;
}

CMD:spawncar(playerid, params[])
{
	extract params -> new vehid; else 
		return SendClientMessage(playerid, -1, !"/spawncar [vehid]");

	if(!IsValidVehicle(vehid))
		return SendClientMessage(playerid, -1, !"Недействительный транспорт!");

	SetVehicleToRespawn(vehid);
	return true;
}
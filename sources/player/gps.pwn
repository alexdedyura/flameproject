SetPlayerCustomGPSMarker(playerid, Float:x, Float:y, Float:z, Float:radius = 2.5)
{
	SetPVarInt(playerid, "GPS", 1);
	SetPlayerCheckpoint(playerid, x, y, z, radius);
	return true;
}

GPS_OnPlayerEnterCheckpoint(playerid)
{
	if(GetPVarInt(playerid, "GPS"))
	{
		DisablePlayerCheckpoint(playerid);
		DeletePVar(playerid, "GPS");
	}

	return true;
}
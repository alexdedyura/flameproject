BoostVehicle(playerid)
{
	new vehid = GetPlayerVehicleID(playerid);
	new keys, updown, leftright;
	GetPlayerKeys(playerid, keys, updown, leftright);
	//printf("%i", (keys & KEY_SPRINT)); // debug
	if(VehicleInfo[vehid][vComp] && (keys & KEY_SPRINT))
	{
		new speed = GetVehicleSpeed(vehid);
		new maxSpeed = GetVehicleMaxSpeed(GetVehicleModel(vehid)) + 15 * VehicleInfo[vehid][vComp];
		new Float:boostCoef = 0.05 * VehicleInfo[vehid][vComp];
		if(speed && !(speed % 5) && speed < maxSpeed)
		{
			new Float:x, Float:y, Float:z;
			GetVehicleVelocity(vehid, x, y, z);
			new Float:zAng;
			GetVehicleZAngle(vehid, zAng);

			if(floatround(speed * (1.0 + boostCoef)) >= maxSpeed)
				boostCoef = floatdiv(maxSpeed + 2.0, speed) - 1.0;

			SetVehicleVelocity(vehid, x + x * boostCoef * floatabs(floatsin(zAng, degrees)), y + y * boostCoef * floatabs(floatcos(zAng, degrees)), z);
		}	
	}

	return true;
}
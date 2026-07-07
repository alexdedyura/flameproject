new static VehicleInterior[MAX_VEHICLES];

VI_GetVehicleInterior(vehid)
{
	return VehicleInterior[vehid];
}

stock vi_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2)
{
	new vehid = AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2);
	VehicleInterior[vehid] = 0;
	return vehid;
}

#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle vi_AddStaticVehicle

stock vi_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, bool:addsiren=false)
{
	new vehid = AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren);
	VehicleInterior[vehid] = 0;
	return vehid;
}

#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx vi_AddStaticVehicleEx

stock vi_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, bool:addsiren=false)
{
	new vehid = CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren);
	VehicleInterior[vehid] = 0;
	return vehid;
}

#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle vi_CreateVehicle

stock vi_LinkVehicleToInterior(vehicleid, interiorid)
{
	VehicleInterior[vehicleid] = interiorid;
	return LinkVehicleToInterior(vehicleid, interiorid);
}
 
#if defined _ALS_LinkVehicleToInterior
	#undef LinkVehicleToInterior
#else
	#define _ALS_LinkVehicleToInterior
#endif
#define LinkVehicleToInterior vi_LinkVehicleToInterior

public OnVehicleSpawn(vehicleid)
{
    VehicleInterior[vehicleid] = 0;

    #if defined vi_OnVehicleSpawn
        return vi_OnVehicleSpawn(vehicleid);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnVehicleSpawn
    #undef OnVehicleSpawn
#else
    #define _ALS_OnVehicleSpawn
#endif
#define OnVehicleSpawn vi_OnVehicleSpawn
#if defined vi_OnVehicleSpawn
    forward vi_OnVehicleSpawn(vehicleid);
#endif
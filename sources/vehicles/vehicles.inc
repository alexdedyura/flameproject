#include <YSI_Coding\y_hooks>

enum
{
	VEHICLE_TYPE_NONE = 0,
	VEHICLE_TYPE_PERSONAL = 1,
	VEHICLE_TYPE_SHARING = 2
};

#define VEHICLE_INFO_OWNER_NAME_LENGTH 32
#define VEHICLE_INFO_NUMBERS_LENGTH 16

#define UNSPAWN_TAX_WEEKS 2
#define DELETE_TAX_WEEKS 4

enum vehicle_info 
{
	vID,
	vModel,
	vType,
	vOwnerID,
	vOwnerName[VEHICLE_INFO_OWNER_NAME_LENGTH],
	Float:vSpawnPosX,
	Float:vSpawnPosY,
	Float:vSpawnPosZ,
	Float:vSpawnPosFA,
	vSpawnPosInt,
	vSpawnPosVW,
	vNumbers[VEHICLE_INFO_NUMBERS_LENGTH],
	vBuyTime,
	Float:vMileage,
	Float:vFuel,
	vColor1,
	vColor2,
	vComp,
	vTaxWeeks,

	// temp
	vLocked,
	vEngine,
	vLights,
	vBoot,
	vBonnet
};

new VehicleInfo[MAX_VEHICLES + 1][vehicle_info];

new const VehicleNames[][] =
{
    "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel",
    "Dumper", "Firetruck", "Trashmaster", "Stretch", "Manana", "Infernus",
    "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
    "Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection",
    "Hunter", "Premier", "Enforcer", "Securicar", "Banshee", "Predator", "Bus",
    "Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach", "Cabbie",
    "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral",
    "Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder",
    "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair", "Berkley's RC Van",
    "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale",
    "Oceanic","Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy",
    "Hermes", "Sabre", "Rustler", "ZR-350", "Walton", "Regina", "Comet", "BMX",
    "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper",
    "Rancher", "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking",
    "Blista Compact", "Police Maverick", "Boxville", "Benson", "Mesa", "RC Goblin",
    "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher", "Super GT",
    "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stunt",
    "Tanker", "Roadtrain", "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra",
    "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck", "Fortune",
    "Cadrona", "FBI Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer",
    "Remington", "Slamvan", "Blade", "Freight", "Streak", "Vortex", "Vincent",
    "Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder", "Primo",
    "Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite",
    "Windsor", "Monster", "Monster", "Uranus", "Jester", "Sultan", "Stratium",
    "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
    "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper",
    "Broadway", "Tornado", "AT-400", "DFT-30", "Huntley", "Stafford", "BF-400",
    "News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
    "Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "Police Car",
    "Police Car", "Police Car", "Police Ranger", "Picador", "S.W.A.T", "Alpha",
    "Phoenix", "Glendale", "Sadler", "Luggage", "Luggage", "Stairs", "Boxville",
    "Tiller", "Utility Trailer"
};

#include <..\..\sources\vehicles\vehicles_core.pwn>
#include <..\..\sources\vehicles\vehicles_garage.pwn>
#include <..\..\sources\vehicles\speedometer.pwn>
#include <..\..\sources\vehicles\vehicles_params.pwn>
#include <..\..\sources\vehicles\vehicles_stats.pwn>
#include <..\..\sources\vehicles\vehicles_numbers.pwn>
#include <..\..\sources\vehicles\vehicles_shop.pwn>
#include <..\..\sources\vehicles\vehicles_sharing.pwn>
#include <..\..\sources\vehicles\vehicles_player.pwn>
#include <..\..\sources\vehicles\vehicles_comp.pwn>
#include <..\..\sources\vehicles\vehicles_tax.pwn>
#include <..\..\sources\vehicles\vehicles_engine.pwn>
#include <..\..\sources\vehicles\vehicles_keys.pwn>



Vehicles_OnPlayerStateChange(playerid, newstate, oldstate)
{
	#pragma unused oldstate
	if (newstate == PLAYER_STATE_DRIVER)
		SendClientMessage(playerid, -1, "- Чтобы завести двигатель нажмите "FLAME_COLOR"2"COLOR_WHITE" | Включить фары - "FLAME_COLOR"L.ALT"COLOR_WHITE"");
}

Vehicles_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	VehiclesP_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	VShop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	VSharing_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	VTax_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	return true;
}

GetVehicleByID(vehid)
{
	new result = 0;

	foreach(new i : Vehicle)
	{
		if(VehicleInfo[i][vID] == vehid)
		{
			result = i;
			break;
		}
	}

	return result;
}

IsPlayerVehicleOwner(playerid, vehid)
{
	return (VehicleInfo[vehid][vType] == VEHICLE_TYPE_PERSONAL && VehicleInfo[vehid][vOwnerID] == pData[playerid][pID]);
}

GetVehicleOwnerID(vehid)
{
	new result = -1;

	foreach(new i : Player)
	{
		if(IsPlayerVehicleOwner(i, vehid))
		{
			result = i;
			break;
		}
	}

	return result;
}


GetVehiclePlayerID(vehid)
{
	if(VehicleInfo[vehid][vType] == VEHICLE_TYPE_SHARING)
		return GetSharingOwnerID(vehid);

	return GetVehicleOwnerID(vehid);
}
GetVehicleMileage(vehid)
{
	return floatround(VehicleInfo[vehid][vMileage], floatround_floor);
}

GetVehicleFuel(vehid)
{
	return floatround(VehicleInfo[vehid][vFuel], floatround_ceil);
}

GetPlayerVehiclesAmount(playerid)
{
	return GetPlayerGaragePersonalCount(playerid);
}
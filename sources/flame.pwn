// Flame Project 2026

// SA-MP API compatibility layer for open.mp
#define SAMP_COMPAT

#include <open.mp>
#include <crashdetect>
#include <sscanf2>
#include <foreach>
#include <izcmd>
#include <streamer>
#include <a_mysql>
#include <rustext>
#include <mapfix>

#define MODE_VERSION "June 26 Build"
#define WEBSITE	"www.open.mp"

#if 1
#pragma option -r
#pragma option -d3
#endif

#include <..\..\sources\core\core.inc>
#include <..\..\sources\textdraws\textdraws.inc>
#include <..\..\sources\player\player.inc>
#include <..\..\sources\vehicles\vehicles.inc>
#include <..\..\sources\player\phone.inc>
#include <..\..\sources\player\admin\admin.inc>
#include <..\..\sources\objects\object.inc>
#include <..\..\sources\systems\systems.inc>
#include <..\..\sources\commands\commands.inc>


main()
{
    print("\n----------------------------------");
    printf("Flame Project %s loaded!\n", MODE_VERSION);
    print("----------------------------------\n");
}

public OnGameModeInit()
{
    SetDefaultRussifierType(RussifierType_SanLtd);

    Timers_OnGameModeInit();
    TextDraws_OnGameModeInit();
    VShop_OnGameModeInit();
    VSharing_OnGameModeInit();
    VKeys_OnGameModeInit();
    Phone_OnGameModeInit();
    SetFuelSystemCars();
    return true;
}

public OnPlayerCommandReceived(playerid, cmdtext[])
{
    if (!Logged[playerid])
    {
        SendClientMessage(playerid, COLOR_GREY, "* ��� ����� ������ ������� ���������� ��������������.");
        return false;
    }
    return true;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
    if (!success)
    {
        SendClientMessage(playerid, COLOR_GREY, "* ������ ������� �� ����������.");
    }
    return true;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	#if defined WEATHER_INCLUDED
		W_EnterDynamicArea(playerid, areaid);
	#endif
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    #if defined INVENTORY_INCLUDED
        INV_ClickPlayerTextDraw(playerid, playertextid);
    #endif
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	VShop_OnPlayerClickTextDraw(playerid, clickedid);
	VSharing_OnPlayerClickTextDraw(playerid, clickedid);
	Phone_OnPlayerClickTextDraw(playerid, clickedid);

	return true;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	Vehicles_OnPlayerStateChange(playerid, newstate, oldstate);
	Speed_OnPlayerStateChange(playerid, newstate, oldstate);
	return true;
}

public OnPlayerConnect(playerid)
{
    CreateSpeedometerPTD(playerid);
    Timers_OnPlayerConnect(playerid);
    return true;
}

public OnPlayerDisconnect(playerid, reason)
{
    Player_OnPlayerDisconnect(playerid, reason);
    Vehicles_OnPlayerDisconnect(playerid);
    Speed_OnPlayerDisconnect(playerid, reason);
    Phone_OnPlayerDisconnect(playerid);
    return true;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    HidePlayerSpeedometer(playerid);
    
    if (SpeedometerTimer[playerid] != 0)
    {
        KillTimer(SpeedometerTimer[playerid]);
        SpeedometerTimer[playerid] = 0;
    }

    return true;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_WALK) && !(oldkeys & KEY_WALK) && !IsPlayerInAnyVehicle(playerid)) // Alt key
	{
		VShop_ButtonAltFoot(playerid);
		VSharing_ButtonAltFoot(playerid);
		VKeys_ButtonAltFoot(playerid);
	}
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	Vehicles_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	VKeys_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Phone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
}

public OnPlayerEnterCheckpoint(playerid)
{
	GPS_OnPlayerEnterCheckpoint(playerid);
}

public OnVehicleSpawn(vehicleid)
{
	Vehicles_OnVehicleSpawn(vehicleid);
	return true;
}

Timers_OnGameModeInit()
{
	SetTimer("SecTimer", 1000, true);
	return true;
}

Timers_OnPlayerConnect(playerid)
{
	SetTimerEx("PlayerSecTimer", 1000, true, "i", playerid);
}

forward PlayerSecTimer(playerid);
public PlayerSecTimer(playerid)
{
	SecUpdate_BusStop(playerid);
	VSharing_PlayerSecTimer(playerid);
	VEngine_PlayerSecTimer(playerid);
	Phone_PlayerSecTimer(playerid);
	Horizon_PlayerSecTimer(playerid);
}

forward SecTimer();
public SecTimer()
{
	new hour, minute, second;
	gettime(hour, minute, second);

	if(!hour && !minute && !second)
		NewDay();

	return true;
}

NewDay()
{
	printf("Started new day!");
	new year, month, day;
    getdate(year, month, day);

    VSharing_NewDay(); // expire finished carsharing rentals

    if(GetWeekDayNum() == 2)
        NewWeek();

    return true;
}

NewWeek()
{
	printf("Started new week!");
	Vehicles_NewWeek();
	Bank_NewDay();
	return true;
}

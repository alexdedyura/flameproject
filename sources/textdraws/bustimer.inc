#include <YSI_Coding\y_hooks>

new PlayerText:BusTimerTD[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
	BusTimerTD[playerid] = CreatePlayerTextDraw(playerid, 237.999954, 395.733276, "TIME LEFT");
	PlayerTextDrawLetterSize(playerid, BusTimerTD[playerid], 0.396999, 1.367704);
	PlayerTextDrawTextSize(playerid, BusTimerTD[playerid], 492.666564, 32.355567);
	PlayerTextDrawAlignment(playerid, BusTimerTD[playerid], 1);
	PlayerTextDrawColor(playerid, BusTimerTD[playerid], -1);
	PlayerTextDrawUseBox(playerid, BusTimerTD[playerid], true);
	PlayerTextDrawBoxColor(playerid, BusTimerTD[playerid], 0);
	PlayerTextDrawSetShadow(playerid, BusTimerTD[playerid], 0);
	PlayerTextDrawSetOutline(playerid, BusTimerTD[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, BusTimerTD[playerid], 51);
	PlayerTextDrawFont(playerid, BusTimerTD[playerid], 1);
	PlayerTextDrawSetProportional(playerid, BusTimerTD[playerid], true);
}
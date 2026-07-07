#include <YSI_Coding\y_hooks>

new Text:info_TD[2];
new PlayerText:info_PTD[MAX_PLAYERS][2];

hook OnGameModeInit()
{

	info_TD[0] = TextDrawCreate(268.7481, 6.8333, "LD_SPAC:white"); // пусто
	TextDrawTextSize(info_TD[0], 112.0000, 40.0000);
	TextDrawAlignment(info_TD[0], 1);
	TextDrawColor(info_TD[0], 303174399);
	TextDrawBackgroundColor(info_TD[0], 255);
	TextDrawFont(info_TD[0], 4);
	TextDrawSetProportional(info_TD[0], false);
	TextDrawSetShadow(info_TD[0], 0);

	info_TD[1] = TextDrawCreate(256.5661, 25.8999, "LD_BEAT:CHIT"); // пусто
	TextDrawTextSize(info_TD[1], 138.0000, 2.0000);
	TextDrawAlignment(info_TD[1], 1);
	TextDrawColor(info_TD[1], -1);
	TextDrawBackgroundColor(info_TD[1], 255);
	TextDrawFont(info_TD[1], 4);
	TextDrawSetProportional(info_TD[1], false);
	TextDrawSetShadow(info_TD[1], 0);
}

hook OnPlayerConnect(playerid)
{
	info_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 324.2019, 12.9499, "WELCOME_TO_FLINT_COUNTY"); // пусто
	PlayerTextDrawLetterSize(playerid, info_PTD[playerid][0], 0.1788, 0.8883);
	PlayerTextDrawAlignment(playerid, info_PTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, info_PTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, info_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, info_PTD[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, info_PTD[playerid][0], true);
	PlayerTextDrawSetShadow(playerid, info_PTD[playerid][0], 0);

	info_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 323.2648, 32.7832, "15:46_I_12_C"); // пусто
	PlayerTextDrawLetterSize(playerid, info_PTD[playerid][1], 0.1788, 0.8883);
	PlayerTextDrawAlignment(playerid, info_PTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, info_PTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, info_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, info_PTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, info_PTD[playerid][1], true);
	PlayerTextDrawSetShadow(playerid, info_PTD[playerid][1], 0);
}


ShowWeatherTextDraw(playerid, const zonename[], temp)
{
	for(new i = 0; i < sizeof(info_TD); i++)
		TextDrawShowForPlayer(playerid, info_TD[i]);
	for(new i = 0; i < sizeof(info_PTD[]); i++)
		PlayerTextDrawShow(playerid, info_PTD[playerid][i]);

	new string[64];
	format(string, sizeof(string), "WELCOME TO %s", StringToUpper(zonename));
	strreplace(string, " ", "_");
	PlayerTextDrawSetString(playerid, info_PTD[playerid][0], string);
	new hour, minute, second;
	gettime(hour, minute, second);
	format(string, sizeof(string), "%02i:%02i I %i C", hour, minute, temp);
	strreplace(string, " ", "_");
	PlayerTextDrawSetString(playerid, info_PTD[playerid][1], string);
	SetTimerEx("HideWeatherTextDraw", 5000, false, "i", playerid);
	return true;
}

forward HideWeatherTextDraw(playerid);
public HideWeatherTextDraw(playerid)
{
	for(new i = 0; i < sizeof(info_TD); i++)
		TextDrawHideForPlayer(playerid, info_TD[i]);
	for(new i = 0; i < sizeof(info_PTD[]); i++)
		PlayerTextDrawHide(playerid, info_PTD[playerid][i]);
	return true;
}
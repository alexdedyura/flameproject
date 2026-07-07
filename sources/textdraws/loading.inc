#include <YSI_Coding\y_hooks>

new Text:LoadingTD[3];
new PlayerText:LoadingPTD[MAX_PLAYERS][2];

hook OnGameModeInit()
{

	LoadingTD[0] = TextDrawCreate(-2.5255, -1.9166, "LD_SPAC:white"); // пусто
	TextDrawTextSize(LoadingTD[0], 645.0000, 450.0000);
	TextDrawAlignment(LoadingTD[0], 1);
	TextDrawColor(LoadingTD[0], 303174399);
	TextDrawBackgroundColor(LoadingTD[0], 255);
	TextDrawFont(LoadingTD[0], 4);
	TextDrawSetProportional(LoadingTD[0], false);
	TextDrawSetShadow(LoadingTD[0], 0);

	LoadingTD[1] = TextDrawCreate(239.7276, 240.2675, "LD_SPAC:white"); // пусто
	TextDrawTextSize(LoadingTD[1], 162.0000, 19.0000);
	TextDrawAlignment(LoadingTD[1], 1);
	TextDrawColor(LoadingTD[1], 538976511);
	TextDrawBackgroundColor(LoadingTD[1], 255);
	TextDrawFont(LoadingTD[1], 4);
	TextDrawSetProportional(LoadingTD[1], false);
	TextDrawSetShadow(LoadingTD[1], 0);

	LoadingTD[2] = TextDrawCreate(258.0666, 220.9167, RusText("ЗАГРУЗКА ТЕКСТУР")); // пусто
	TextDrawLetterSize(LoadingTD[2], 0.4712, 1.9208);
	TextDrawAlignment(LoadingTD[2], 1);
	TextDrawColor(LoadingTD[2], -1);
	TextDrawBackgroundColor(LoadingTD[2], 255);
	TextDrawFont(LoadingTD[2], 1);
	TextDrawSetProportional(LoadingTD[2], true);
	TextDrawSetShadow(LoadingTD[2], 0);
}

hook OnPlayerConnect(playerid)
{

	LoadingPTD[playerid][0] = CreatePlayerTextDraw(playerid, 241.4277, 242.4677, "LD_SPAC:white"); // пусто
	PlayerTextDrawTextSize(playerid, LoadingPTD[playerid][0], 158.1993, 15.0000);
	PlayerTextDrawAlignment(playerid, LoadingPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, LoadingPTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, LoadingPTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, LoadingPTD[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, LoadingPTD[playerid][0], false);
	PlayerTextDrawSetShadow(playerid, LoadingPTD[playerid][0], 0);

	LoadingPTD[playerid][1] = CreatePlayerTextDraw(playerid, 319.9116, 245.0334, "100%"); // пусто
	PlayerTextDrawLetterSize(playerid, LoadingPTD[playerid][1], 0.2111, 0.8941);
	PlayerTextDrawAlignment(playerid, LoadingPTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, LoadingPTD[playerid][1], 303174399);
	PlayerTextDrawBackgroundColor(playerid, LoadingPTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, LoadingPTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, LoadingPTD[playerid][1], true);
	PlayerTextDrawSetShadow(playerid, LoadingPTD[playerid][1], 0);
}
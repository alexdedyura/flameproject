#include <YSI_Coding\y_hooks>

// Глобальные текстдравы
new Text:InventoryTD[12];


hook OnGameModeInit()
{
	InventoryTD[0] = TextDrawCreate(452.4085, 243.6670, "LD_SPAC:white"); // пусто
	TextDrawTextSize(InventoryTD[0], 179.0000, 84.1398);
	TextDrawAlignment(InventoryTD[0], 1);
	TextDrawColor(InventoryTD[0], 303174399);
	TextDrawBackgroundColor(InventoryTD[0], 255);
	TextDrawFont(InventoryTD[0], 4);
	TextDrawSetProportional(InventoryTD[0], false);
	TextDrawSetShadow(InventoryTD[0], 0);

	InventoryTD[1] = TextDrawCreate(452.4085, 214.5993, "LD_SPAC:white"); // пусто
	TextDrawTextSize(InventoryTD[1], 179.0000, 26.4099);
	TextDrawAlignment(InventoryTD[1], 1);
	TextDrawColor(InventoryTD[1], 303174399);
	TextDrawBackgroundColor(InventoryTD[1], 255);
	TextDrawFont(InventoryTD[1], 4);
	TextDrawSetProportional(InventoryTD[1], false);
	TextDrawSetShadow(InventoryTD[1], 0);

	InventoryTD[2] = TextDrawCreate(525.0449, 217.5332, RusText("ПЕРЕДАТЬ")); // пусто
	TextDrawLetterSize(InventoryTD[2], 0.1941, 0.9933);
	TextDrawTextSize(InventoryTD[2], 570.0000, 6.0000);
	TextDrawAlignment(InventoryTD[2], 1);
	TextDrawColor(InventoryTD[2], -1);
	TextDrawUseBox(InventoryTD[2], true);
	TextDrawBoxColor(InventoryTD[2], 303174144);
	TextDrawBackgroundColor(InventoryTD[2], 255);
	TextDrawFont(InventoryTD[2], 2);
	TextDrawSetProportional(InventoryTD[2], true);
	TextDrawSetShadow(InventoryTD[2], 0);
	TextDrawSetSelectable(InventoryTD[2], true);

	InventoryTD[3] = TextDrawCreate(525.0891, 229.7174, RusText("УДАЛИТЬ")); // пусто
	TextDrawLetterSize(InventoryTD[3], 0.1941, 0.9933);
	TextDrawTextSize(InventoryTD[3], 574.0000, 6.0000);
	TextDrawAlignment(InventoryTD[3], 1);
	TextDrawColor(InventoryTD[3], -1);
	TextDrawUseBox(InventoryTD[3], true);
	TextDrawBoxColor(InventoryTD[3], 303174144);
	TextDrawBackgroundColor(InventoryTD[3], 255);
	TextDrawFont(InventoryTD[3], 2);
	TextDrawSetProportional(InventoryTD[3], true);
	TextDrawSetShadow(InventoryTD[3], 0);
	TextDrawSetSelectable(InventoryTD[3], true);

	InventoryTD[4] = TextDrawCreate(456.1618, 217.6000, RusText("ИСПОЛЬЗОВАТЬ")); // пусто
	TextDrawLetterSize(InventoryTD[4], 0.1941, 0.9933);
	TextDrawTextSize(InventoryTD[4], 515.0000, 6.0000);
	TextDrawAlignment(InventoryTD[4], 1);
	TextDrawColor(InventoryTD[4], -1);
	TextDrawUseBox(InventoryTD[4], true);
	TextDrawBoxColor(InventoryTD[4], 303174144);
	TextDrawBackgroundColor(InventoryTD[4], 255);
	TextDrawFont(InventoryTD[4], 2);
	TextDrawSetProportional(InventoryTD[4], true);
	TextDrawSetShadow(InventoryTD[4], 0);
	TextDrawSetSelectable(InventoryTD[4], true);

	InventoryTD[5] = TextDrawCreate(456.2138, 229.7341, RusText("ВЫБРОСИТЬ")); // пусто
	TextDrawLetterSize(InventoryTD[5], 0.1941, 0.9933);
	TextDrawTextSize(InventoryTD[5], 499.0000, 6.0000);
	TextDrawAlignment(InventoryTD[5], 1);
	TextDrawColor(InventoryTD[5], -1);
	TextDrawUseBox(InventoryTD[5], true);
	TextDrawBoxColor(InventoryTD[5], 303174144);
	TextDrawBackgroundColor(InventoryTD[5], 255);
	TextDrawFont(InventoryTD[5], 2);
	TextDrawSetProportional(InventoryTD[5], true);
	TextDrawSetShadow(InventoryTD[5], 0);
	TextDrawSetSelectable(InventoryTD[5], true);

	InventoryTD[6] = TextDrawCreate(607.3521, 214.6665, "LD_SPAC:white"); // пусто
	TextDrawTextSize(InventoryTD[6], 24.0000, 12.0000);
	TextDrawAlignment(InventoryTD[6], 1);
	TextDrawColor(InventoryTD[6], -1523963137);
	TextDrawBackgroundColor(InventoryTD[6], 255);
	TextDrawFont(InventoryTD[6], 4);
	TextDrawSetProportional(InventoryTD[6], false);
	TextDrawSetShadow(InventoryTD[6], 0);

	InventoryTD[7] = TextDrawCreate(619.5178, 215.1165, "X"); // пусто
	TextDrawLetterSize(InventoryTD[7], 0.1941, 0.9933);
	TextDrawTextSize(InventoryTD[7], 6.0000, 20.0000);
	TextDrawAlignment(InventoryTD[7], 2);
	TextDrawColor(InventoryTD[7], -1);
	TextDrawUseBox(InventoryTD[7], true);
	TextDrawBoxColor(InventoryTD[7], 0);
	TextDrawBackgroundColor(InventoryTD[7], 255);
	TextDrawFont(InventoryTD[7], 2);
	TextDrawSetProportional(InventoryTD[7], true);
	TextDrawSetShadow(InventoryTD[7], 0);
	TextDrawSetSelectable(InventoryTD[7], true);

	InventoryTD[8] = TextDrawCreate(583.4572, 214.6665, "LD_SPAC:white"); // пусто
	TextDrawTextSize(InventoryTD[8], 24.0000, 12.0000);
	TextDrawAlignment(InventoryTD[8], 1);
	TextDrawColor(InventoryTD[8], 538976511);
	TextDrawBackgroundColor(InventoryTD[8], 255);
	TextDrawFont(InventoryTD[8], 4);
	TextDrawSetProportional(InventoryTD[8], false);
	TextDrawSetShadow(InventoryTD[8], 0);

	InventoryTD[9] = TextDrawCreate(588.0111, 215.0832, " "); // пусто
	TextDrawTextSize(InventoryTD[9], 13.0000, 11.0000);
	TextDrawAlignment(InventoryTD[9], 1);
	TextDrawColor(InventoryTD[9], -1);
	TextDrawBackgroundColor(InventoryTD[9], 303174144);
	TextDrawFont(InventoryTD[9], 5);
	TextDrawSetProportional(InventoryTD[9], false);
	TextDrawSetShadow(InventoryTD[9], 0);
	TextDrawSetSelectable(InventoryTD[9], true);
	TextDrawSetPreviewModel(InventoryTD[9], 1239);
	TextDrawSetPreviewRot(InventoryTD[9], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryTD[10] = TextDrawCreate(452.4085, 342.2503, "LD_SPAC:white"); // пусто
	TextDrawTextSize(InventoryTD[10], 179.0000, 43.2000);
	TextDrawAlignment(InventoryTD[10], 1);
	TextDrawColor(InventoryTD[10], 303174399);
	TextDrawBackgroundColor(InventoryTD[10], 255);
	TextDrawFont(InventoryTD[10], 4);
	TextDrawSetProportional(InventoryTD[10], false);
	TextDrawSetShadow(InventoryTD[10], 0);

	InventoryTD[11] = TextDrawCreate(452.4771, 333.4664, RusText("АКТИВНЫЕ СЛОТЫ")); // пусто
	TextDrawLetterSize(InventoryTD[11], 0.1782, 0.8532);
	TextDrawAlignment(InventoryTD[11], 1);
	TextDrawColor(InventoryTD[11], -1);
	TextDrawBackgroundColor(InventoryTD[11], 255);
	TextDrawFont(InventoryTD[11], 2);
	TextDrawSetProportional(InventoryTD[11], true);
	TextDrawSetShadow(InventoryTD[11], 0);
}


new PlayerText:InventoryPTD[MAX_PLAYERS][16];

hook OnPlayerConnect(playerid)
{
	InventoryPTD[playerid][0] = CreatePlayerTextDraw(playerid, 454.2821, 246.5668, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][0], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][0], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][0], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][0], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][0], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][0], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][1] = CreatePlayerTextDraw(playerid, 489.6773, 246.5502, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][1], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][1], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][1], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][1], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][1], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][1], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][2] = CreatePlayerTextDraw(playerid, 524.8167, 246.5500, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][2], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][2], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][2], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][2], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][2], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][2], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][3] = CreatePlayerTextDraw(playerid, 559.9558, 246.5500, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][3], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][3], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][3], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][3], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][3], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][3], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][4] = CreatePlayerTextDraw(playerid, 595.2949, 246.2666, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][4], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][4], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][4], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][4], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][4], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][4], 0.0000, 0.0000, 0.0000, 1.0000);

    InventoryPTD[playerid][5] = CreatePlayerTextDraw(playerid, 454.2821, 286.8168, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][5], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][5], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][5], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][5], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][5], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][5], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][6] = CreatePlayerTextDraw(playerid, 489.6773, 286.8001, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][6], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][6], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][6], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][6], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][6], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][6], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][7] = CreatePlayerTextDraw(playerid, 524.8167, 286.8001, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][7], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][7], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][7], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][7], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][7], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][7], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][8] = CreatePlayerTextDraw(playerid, 559.9558, 286.8001, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][8], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][8], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][8], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][8], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][8], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][8], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][8], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][8], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][9] = CreatePlayerTextDraw(playerid, 595.4575, 286.8168, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][9], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][9], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][9], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][9], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][9], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][9], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][9], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][9], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][10] = CreatePlayerTextDraw(playerid, 453.9328, 345.0180, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][10], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][10], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][10], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][10], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][10], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][10], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][10], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][10], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][10], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][11] = CreatePlayerTextDraw(playerid, 489.0722, 344.9346, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][11], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][11], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][11], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][11], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][11], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][11], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][11], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][11], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][11], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][11], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][12] = CreatePlayerTextDraw(playerid, 524.5797, 344.8680, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][12], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][12], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][12], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][12], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][12], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][12], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][12], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][12], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][12], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][12], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][13] = CreatePlayerTextDraw(playerid, 560.1875, 344.8681, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][13], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][13], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][13], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][13], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][13], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][13], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][13], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][13], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][13], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][13], 0.0000, 0.0000, 0.0000, 1.0000);

	InventoryPTD[playerid][14] = CreatePlayerTextDraw(playerid, 595.7952, 344.8847, " "); // пусто
	PlayerTextDrawTextSize(playerid, InventoryPTD[playerid][14], 34.0000, 38.0000);
	PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][14], 1);
	PlayerTextDrawColor(playerid, InventoryPTD[playerid][14], -1);
	PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][14], 538976511);
	PlayerTextDrawFont(playerid, InventoryPTD[playerid][14], 5);
	PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][14], false);
	PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][14], 0);
	PlayerTextDrawSetSelectable(playerid, InventoryPTD[playerid][14], true);
	PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][14], 46);
	PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][14], 0.0000, 0.0000, 0.0000, 1.0000);

    InventoryPTD[playerid][15] = CreatePlayerTextDraw(playerid, 630.8150, 327.3000, RusText("1.52/15.00KГ")); // пусто
    PlayerTextDrawLetterSize(playerid, InventoryPTD[playerid][15], 0.1746, 0.8532);
    PlayerTextDrawAlignment(playerid, InventoryPTD[playerid][15], 3);
    PlayerTextDrawColor(playerid, InventoryPTD[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][15], 255);
    PlayerTextDrawFont(playerid, InventoryPTD[playerid][15], 2);
    PlayerTextDrawSetProportional(playerid, InventoryPTD[playerid][15], true);
    PlayerTextDrawSetShadow(playerid, InventoryPTD[playerid][15], 0);
}

new Text:VehiclesShopTD[25];
new PlayerText:VehiclesShopPTD[MAX_PLAYERS][3];

CreateVehiclesShopTD()
{
	VehiclesShopTD[0] = TextDrawCreate(176.9999, 398.0814, "LD_SPAC:white"); // пусто
	TextDrawTextSize(VehiclesShopTD[0], 295.3994, 44.0000);
	TextDrawAlignment(VehiclesShopTD[0], 1);
	TextDrawColor(VehiclesShopTD[0], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[0], 255);
	TextDrawFont(VehiclesShopTD[0], 4);
	TextDrawSetProportional(VehiclesShopTD[0], false);
	TextDrawSetShadow(VehiclesShopTD[0], 0);

	VehiclesShopTD[1] = TextDrawCreate(178.3332, 399.6702, "LD_SPAC:white"); // пусто
	TextDrawTextSize(VehiclesShopTD[1], 293.0000, 41.0000);
	TextDrawAlignment(VehiclesShopTD[1], 1);
	TextDrawColor(VehiclesShopTD[1], 538976511);
	TextDrawBackgroundColor(VehiclesShopTD[1], 255);
	TextDrawFont(VehiclesShopTD[1], 4);
	TextDrawSetProportional(VehiclesShopTD[1], false);
	TextDrawSetShadow(VehiclesShopTD[1], 0);

	VehiclesShopTD[2] = TextDrawCreate(183.4667, 405.7037, "ЙЛEП"); // пусто
	TextDrawLetterSize(VehiclesShopTD[2], 0.1740, 1.1188);
	TextDrawAlignment(VehiclesShopTD[2], 1);
	TextDrawColor(VehiclesShopTD[2], -1);
	TextDrawBackgroundColor(VehiclesShopTD[2], 255);
	TextDrawFont(VehiclesShopTD[2], 2);
	TextDrawSetProportional(VehiclesShopTD[2], true);
	TextDrawSetShadow(VehiclesShopTD[2], 0);

	VehiclesShopTD[3] = TextDrawCreate(204.3332, 403.8889, "LD_SPAC:white"); // color 1
	TextDrawTextSize(VehiclesShopTD[3], 13.0000, 15.0000);
	TextDrawAlignment(VehiclesShopTD[3], 1);
	TextDrawColor(VehiclesShopTD[3], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[3], 255);
	TextDrawFont(VehiclesShopTD[3], 4);
	TextDrawSetProportional(VehiclesShopTD[3], false);
	TextDrawSetShadow(VehiclesShopTD[3], 0);
	TextDrawSetSelectable(VehiclesShopTD[3], true);

	VehiclesShopTD[4] = TextDrawCreate(205.3333, 404.8889, "LD_SPAC:white"); // color 1
	TextDrawTextSize(VehiclesShopTD[4], 10.9599, 12.4499);
	TextDrawAlignment(VehiclesShopTD[4], 1);
	TextDrawColor(VehiclesShopTD[4], -1);
	TextDrawBackgroundColor(VehiclesShopTD[4], 255);
	TextDrawFont(VehiclesShopTD[4], 4);
	TextDrawSetProportional(VehiclesShopTD[4], false);
	TextDrawSetShadow(VehiclesShopTD[4], 0);

	VehiclesShopTD[5] = TextDrawCreate(218.8332, 403.8889, "LD_SPAC:white"); // color 2
	TextDrawTextSize(VehiclesShopTD[5], 13.0000, 15.0000);
	TextDrawAlignment(VehiclesShopTD[5], 1);
	TextDrawColor(VehiclesShopTD[5], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[5], 255);
	TextDrawFont(VehiclesShopTD[5], 4);
	TextDrawSetProportional(VehiclesShopTD[5], false);
	TextDrawSetShadow(VehiclesShopTD[5], 0);
	TextDrawSetSelectable(VehiclesShopTD[5], true);

	VehiclesShopTD[6] = TextDrawCreate(219.8333, 404.8889, "LD_SPAC:white"); // color 2
	TextDrawTextSize(VehiclesShopTD[6], 10.9599, 12.4499);
	TextDrawAlignment(VehiclesShopTD[6], 1);
	TextDrawColor(VehiclesShopTD[6], 255);
	TextDrawBackgroundColor(VehiclesShopTD[6], 255);
	TextDrawFont(VehiclesShopTD[6], 4);
	TextDrawSetProportional(VehiclesShopTD[6], false);
	TextDrawSetShadow(VehiclesShopTD[6], 0);

	VehiclesShopTD[7] = TextDrawCreate(233.5341, 403.8889, "LD_SPAC:white"); // color 3
	TextDrawTextSize(VehiclesShopTD[7], 13.0000, 15.0000);
	TextDrawAlignment(VehiclesShopTD[7], 1);
	TextDrawColor(VehiclesShopTD[7], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[7], 255);
	TextDrawFont(VehiclesShopTD[7], 4);
	TextDrawSetProportional(VehiclesShopTD[7], false);
	TextDrawSetShadow(VehiclesShopTD[7], 0);
	TextDrawSetSelectable(VehiclesShopTD[7], true);

	VehiclesShopTD[8] = TextDrawCreate(234.5342, 404.8889, "LD_SPAC:white"); // color 3
	TextDrawTextSize(VehiclesShopTD[8], 10.9599, 12.4499);
	TextDrawAlignment(VehiclesShopTD[8], 1);
	TextDrawColor(VehiclesShopTD[8], 623192063);
	TextDrawBackgroundColor(VehiclesShopTD[8], 255);
	TextDrawFont(VehiclesShopTD[8], 4);
	TextDrawSetProportional(VehiclesShopTD[8], false);
	TextDrawSetShadow(VehiclesShopTD[8], 0);

	VehiclesShopTD[9] = TextDrawCreate(248.1351, 403.8889, "LD_SPAC:white"); // color 4
	TextDrawTextSize(VehiclesShopTD[9], 13.0000, 15.0000);
	TextDrawAlignment(VehiclesShopTD[9], 1);
	TextDrawColor(VehiclesShopTD[9], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[9], 255);
	TextDrawFont(VehiclesShopTD[9], 4);
	TextDrawSetProportional(VehiclesShopTD[9], false);
	TextDrawSetShadow(VehiclesShopTD[9], 0);
	TextDrawSetSelectable(VehiclesShopTD[9], true);

	VehiclesShopTD[10] = TextDrawCreate(249.1351, 404.8889, "LD_SPAC:white"); // color 4
	TextDrawTextSize(VehiclesShopTD[10], 10.9599, 12.4499);
	TextDrawAlignment(VehiclesShopTD[10], 1);
	TextDrawColor(VehiclesShopTD[10], -2113530625);
	TextDrawBackgroundColor(VehiclesShopTD[10], 255);
	TextDrawFont(VehiclesShopTD[10], 4);
	TextDrawSetProportional(VehiclesShopTD[10], false);
	TextDrawSetShadow(VehiclesShopTD[10], 0);

	VehiclesShopTD[11] = TextDrawCreate(262.8359, 403.8889, "LD_SPAC:white"); // color 5
	TextDrawTextSize(VehiclesShopTD[11], 13.0000, 15.0000);
	TextDrawAlignment(VehiclesShopTD[11], 1);
	TextDrawColor(VehiclesShopTD[11], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[11], 255);
	TextDrawFont(VehiclesShopTD[11], 4);
	TextDrawSetProportional(VehiclesShopTD[11], false);
	TextDrawSetShadow(VehiclesShopTD[11], 0);
	TextDrawSetSelectable(VehiclesShopTD[11], true);

	VehiclesShopTD[12] = TextDrawCreate(263.8360, 404.8889, "LD_SPAC:white"); // color 5
	TextDrawTextSize(VehiclesShopTD[12], 10.9599, 12.4499);
	TextDrawAlignment(VehiclesShopTD[12], 1);
	TextDrawColor(VehiclesShopTD[12], -728817153);
	TextDrawBackgroundColor(VehiclesShopTD[12], 255);
	TextDrawFont(VehiclesShopTD[12], 4);
	TextDrawSetProportional(VehiclesShopTD[12], false);
	TextDrawSetShadow(VehiclesShopTD[12], 0);

	VehiclesShopTD[13] = TextDrawCreate(277.5368, 403.8889, "LD_SPAC:white"); // color 6
	TextDrawTextSize(VehiclesShopTD[13], 13.0000, 15.0000);
	TextDrawAlignment(VehiclesShopTD[13], 1);
	TextDrawColor(VehiclesShopTD[13], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[13], 255);
	TextDrawFont(VehiclesShopTD[13], 4);
	TextDrawSetProportional(VehiclesShopTD[13], false);
	TextDrawSetShadow(VehiclesShopTD[13], 0);
	TextDrawSetSelectable(VehiclesShopTD[13], true);

	VehiclesShopTD[14] = TextDrawCreate(278.5369, 404.8889, "LD_SPAC:white"); // color 6
	TextDrawTextSize(VehiclesShopTD[14], 10.9599, 12.4499);
	TextDrawAlignment(VehiclesShopTD[14], 1);
	TextDrawColor(VehiclesShopTD[14], 777724671);
	TextDrawBackgroundColor(VehiclesShopTD[14], 255);
	TextDrawFont(VehiclesShopTD[14], 4);
	TextDrawSetProportional(VehiclesShopTD[14], false);
	TextDrawSetShadow(VehiclesShopTD[14], 0);

	VehiclesShopTD[15] = TextDrawCreate(291.8377, 403.8889, "LD_SPAC:white"); // color 7
	TextDrawTextSize(VehiclesShopTD[15], 13.0000, 15.0000);
	TextDrawAlignment(VehiclesShopTD[15], 1);
	TextDrawColor(VehiclesShopTD[15], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[15], 255);
	TextDrawFont(VehiclesShopTD[15], 4);
	TextDrawSetProportional(VehiclesShopTD[15], false);
	TextDrawSetShadow(VehiclesShopTD[15], 0);
	TextDrawSetSelectable(VehiclesShopTD[15], true);

	VehiclesShopTD[16] = TextDrawCreate(292.8378, 404.8889, "LD_SPAC:white"); // color 7
	TextDrawTextSize(VehiclesShopTD[16], 10.9599, 12.4499);
	TextDrawAlignment(VehiclesShopTD[16], 1);
	TextDrawColor(VehiclesShopTD[16], 405826815);
	TextDrawBackgroundColor(VehiclesShopTD[16], 255);
	TextDrawFont(VehiclesShopTD[16], 4);
	TextDrawSetProportional(VehiclesShopTD[16], false);
	TextDrawSetShadow(VehiclesShopTD[16], 0);

	VehiclesShopTD[17] = TextDrawCreate(183.4667, 423.4035, "KOMМЗEKПAЙЕХ"); // пусто
	TextDrawLetterSize(VehiclesShopTD[17], 0.1740, 1.1188);
	TextDrawAlignment(VehiclesShopTD[17], 1);
	TextDrawColor(VehiclesShopTD[17], -1);
	TextDrawBackgroundColor(VehiclesShopTD[17], 255);
	TextDrawFont(VehiclesShopTD[17], 2);
	TextDrawSetProportional(VehiclesShopTD[17], true);
	TextDrawSetShadow(VehiclesShopTD[17], 0);

	VehiclesShopTD[18] = TextDrawCreate(270.5335, 424.3852, "STANDART"); // пусто
	TextDrawLetterSize(VehiclesShopTD[18], 0.1656, 1.1188);
	TextDrawTextSize(VehiclesShopTD[18], 10.0000, 53.0000);
	TextDrawAlignment(VehiclesShopTD[18], 2);
	TextDrawColor(VehiclesShopTD[18], -1);
	TextDrawUseBox(VehiclesShopTD[18], true);
	TextDrawBoxColor(VehiclesShopTD[18], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[18], 255);
	TextDrawFont(VehiclesShopTD[18], 2);
	TextDrawSetProportional(VehiclesShopTD[18], true);
	TextDrawSetShadow(VehiclesShopTD[18], 0);
	TextDrawSetSelectable(VehiclesShopTD[18], true);	

	VehiclesShopTD[19] = TextDrawCreate(327.7335, 424.3852, "EXTENDED"); // пусто
	TextDrawLetterSize(VehiclesShopTD[19], 0.1656, 1.1188);
	TextDrawTextSize(VehiclesShopTD[19], 10.0000, 53.0000);
	TextDrawAlignment(VehiclesShopTD[19], 2);
	TextDrawColor(VehiclesShopTD[19], -1);
	TextDrawUseBox(VehiclesShopTD[19], true);
	TextDrawBoxColor(VehiclesShopTD[19], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[19], 255);
	TextDrawFont(VehiclesShopTD[19], 2);
	TextDrawSetProportional(VehiclesShopTD[19], true);
	TextDrawSetShadow(VehiclesShopTD[19], 0);
	TextDrawSetSelectable(VehiclesShopTD[19], true);

	VehiclesShopTD[20] = TextDrawCreate(384.6001, 424.3852, "PERFOMANCE"); // пусто
	TextDrawLetterSize(VehiclesShopTD[20], 0.1656, 1.1188);
	TextDrawTextSize(VehiclesShopTD[20], 10.0000, 53.0000);
	TextDrawAlignment(VehiclesShopTD[20], 2);
	TextDrawColor(VehiclesShopTD[20], -1);
	TextDrawUseBox(VehiclesShopTD[20], true);
	TextDrawBoxColor(VehiclesShopTD[20], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[20], 255);
	TextDrawFont(VehiclesShopTD[20], 2);
	TextDrawSetProportional(VehiclesShopTD[20], true);
	TextDrawSetShadow(VehiclesShopTD[20], 0);
	TextDrawSetSelectable(VehiclesShopTD[20], true);

	VehiclesShopTD[21] = TextDrawCreate(425.6005, 399.5816, "particle:lamp_shad_64"); // пусто
	TextDrawTextSize(VehiclesShopTD[21], 1.0000, 41.0000);
	TextDrawAlignment(VehiclesShopTD[21], 1);
	TextDrawColor(VehiclesShopTD[21], -1);
	TextDrawBackgroundColor(VehiclesShopTD[21], 255);
	TextDrawFont(VehiclesShopTD[21], 4);
	TextDrawSetProportional(VehiclesShopTD[21], false);
	TextDrawSetShadow(VehiclesShopTD[21], 0);

	VehiclesShopTD[22] = TextDrawCreate(440.1330, 400.7259, "ЙEHA"); // пусто
	TextDrawLetterSize(VehiclesShopTD[22], 0.1740, 1.1188);
	TextDrawAlignment(VehiclesShopTD[22], 1);
	TextDrawColor(VehiclesShopTD[22], -1);
	TextDrawBackgroundColor(VehiclesShopTD[22], 255);
	TextDrawFont(VehiclesShopTD[22], 2);
	TextDrawSetProportional(VehiclesShopTD[22], true);
	TextDrawSetShadow(VehiclesShopTD[22], 0);

	VehiclesShopTD[23] = TextDrawCreate(430.8345, 422.9702, "LD_SPAC:white"); // пусто
	TextDrawTextSize(VehiclesShopTD[23], 36.7800, 14.5699);
	TextDrawAlignment(VehiclesShopTD[23], 1);
	TextDrawColor(VehiclesShopTD[23], 235802367);
	TextDrawBackgroundColor(VehiclesShopTD[23], 255);
	TextDrawFont(VehiclesShopTD[23], 4);
	TextDrawSetProportional(VehiclesShopTD[23], false);
	TextDrawSetShadow(VehiclesShopTD[23], 0);

	VehiclesShopTD[24] = TextDrawCreate(449.1680, 425.7853, "KYМЕПТ"); // пусто
	TextDrawLetterSize(VehiclesShopTD[24], 0.1610, 0.9860);
	TextDrawTextSize(VehiclesShopTD[24], 9.0000, 32.0000);
	TextDrawAlignment(VehiclesShopTD[24], 2);
	TextDrawColor(VehiclesShopTD[24], -1);
	TextDrawUseBox(VehiclesShopTD[24], true);
	TextDrawBoxColor(VehiclesShopTD[24], 8388863);
	TextDrawBackgroundColor(VehiclesShopTD[24], 255);
	TextDrawFont(VehiclesShopTD[24], 2);
	TextDrawSetProportional(VehiclesShopTD[24], true);
	TextDrawSetShadow(VehiclesShopTD[24], 0);
	TextDrawSetSelectable(VehiclesShopTD[24], true);

	return true;
}

CreateVehiclesShopPTD(playerid)
{
	VehiclesShopPTD[playerid][0] = CreatePlayerTextDraw(playerid, 312.3997, 404.1551, "АAK:_100_З"); // пусто
	PlayerTextDrawLetterSize(playerid, VehiclesShopPTD[playerid][0], 0.1886, 1.3262);
	PlayerTextDrawAlignment(playerid, VehiclesShopPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, VehiclesShopPTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, VehiclesShopPTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, VehiclesShopPTD[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, VehiclesShopPTD[playerid][0], true);
	PlayerTextDrawSetShadow(playerid, VehiclesShopPTD[playerid][0], 0);

	VehiclesShopPTD[playerid][1] = CreatePlayerTextDraw(playerid, 412.7997, 404.1551, "LANDSTALKER"); // пусто
	PlayerTextDrawLetterSize(playerid, VehiclesShopPTD[playerid][1], 0.1886, 1.3262);
	PlayerTextDrawAlignment(playerid, VehiclesShopPTD[playerid][1], 3);
	PlayerTextDrawColor(playerid, VehiclesShopPTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, VehiclesShopPTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, VehiclesShopPTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, VehiclesShopPTD[playerid][1], true);
	PlayerTextDrawSetShadow(playerid, VehiclesShopPTD[playerid][1], 0);

	VehiclesShopPTD[playerid][2] = CreatePlayerTextDraw(playerid, 448.6996, 410.3997, "$100000"); // пусто
	PlayerTextDrawLetterSize(playerid, VehiclesShopPTD[playerid][2], 0.2140, 1.0026);
	PlayerTextDrawAlignment(playerid, VehiclesShopPTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, VehiclesShopPTD[playerid][2], 10551551);
	PlayerTextDrawBackgroundColor(playerid, VehiclesShopPTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, VehiclesShopPTD[playerid][2], 3);
	PlayerTextDrawSetProportional(playerid, VehiclesShopPTD[playerid][2], true);
	PlayerTextDrawSetShadow(playerid, VehiclesShopPTD[playerid][2], 0);

	return true;
}

ShowPlayerVehiclesShopTD(playerid)
{
	for(new i = 0; i < sizeof(VehiclesShopTD); i++)
		TextDrawShowForPlayer(playerid, VehiclesShopTD[i]);

	CreateVehiclesShopPTD(playerid);

	for(new i = 0; i < sizeof(VehiclesShopPTD[]); i++)
		PlayerTextDrawShow(playerid, VehiclesShopPTD[playerid][i]);

	return true;
}

HidePlayerVehiclesShopTD(playerid)
{
	for(new i = 0; i < sizeof(VehiclesShopTD); i++)
		TextDrawHideForPlayer(playerid, VehiclesShopTD[i]);

	for(new i = 0; i < sizeof(VehiclesShopPTD[]); i++)
		PlayerTextDrawDestroy(playerid, VehiclesShopPTD[playerid][i]);

	return true;
}
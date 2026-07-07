new Text:SpeedometerTD[13];
new PlayerText:SpeedometerPTD[MAX_PLAYERS][3];

CreateSpeedometerTD()
{
	SpeedometerTD[0] = TextDrawCreate(268.3333, 394.7627, "LD_SPAC:white"); // пусто
	TextDrawTextSize(SpeedometerTD[0], 102.0000, 45.0000);
	TextDrawAlignment(SpeedometerTD[0], 1);
	TextDrawColor(SpeedometerTD[0], 235802367);
	TextDrawBackgroundColor(SpeedometerTD[0], 255);
	TextDrawFont(SpeedometerTD[0], 4);
	TextDrawSetProportional(SpeedometerTD[0], false);
	TextDrawSetShadow(SpeedometerTD[0], 0);

	SpeedometerTD[1] = TextDrawCreate(269.6666, 396.4220, "LD_SPAC:white"); // пусто
	TextDrawTextSize(SpeedometerTD[1], 99.2000, 41.7298);
	TextDrawAlignment(SpeedometerTD[1], 1);
	TextDrawColor(SpeedometerTD[1], 538976511);
	TextDrawBackgroundColor(SpeedometerTD[1], 255);
	TextDrawFont(SpeedometerTD[1], 4);
	TextDrawSetProportional(SpeedometerTD[1], false);
	TextDrawSetShadow(SpeedometerTD[1], 0);

	SpeedometerTD[2] = TextDrawCreate(305.0998, 396.1036, "particle:lamp_shad_64"); // пусто
	TextDrawTextSize(SpeedometerTD[2], 1.7099, 41.8501);
	TextDrawAlignment(SpeedometerTD[2], 1);
	TextDrawColor(SpeedometerTD[2], -1);
	TextDrawBackgroundColor(SpeedometerTD[2], 255);
	TextDrawFont(SpeedometerTD[2], 4);
	TextDrawSetProportional(SpeedometerTD[2], false);
	TextDrawSetShadow(SpeedometerTD[2], 0);

	SpeedometerTD[3] = TextDrawCreate(315.0332, 429.6072, "LD_SPAC:white"); // пусто
	TextDrawTextSize(SpeedometerTD[3], 4.0000, 5.0000);
	TextDrawAlignment(SpeedometerTD[3], 1);
	TextDrawColor(SpeedometerTD[3], -2139062017);
	TextDrawBackgroundColor(SpeedometerTD[3], 255);
	TextDrawFont(SpeedometerTD[3], 4);
	TextDrawSetProportional(SpeedometerTD[3], false);
	TextDrawSetShadow(SpeedometerTD[3], 0);

	SpeedometerTD[4] = TextDrawCreate(315.4666, 433.0812, "u"); // пусто
	TextDrawLetterSize(SpeedometerTD[4], 0.1426, -0.7976);
	TextDrawAlignment(SpeedometerTD[4], 1);
	TextDrawColor(SpeedometerTD[4], -2139062017);
	TextDrawBackgroundColor(SpeedometerTD[4], 255);
	TextDrawFont(SpeedometerTD[4], 2);
	TextDrawSetProportional(SpeedometerTD[4], true);
	TextDrawSetShadow(SpeedometerTD[4], 0);

	SpeedometerTD[5] = TextDrawCreate(337.4667, 425.5850, "("); // пусто
	TextDrawLetterSize(SpeedometerTD[5], 0.2000, 0.9694);
	TextDrawAlignment(SpeedometerTD[5], 1);
	TextDrawColor(SpeedometerTD[5], -2139062017);
	TextDrawBackgroundColor(SpeedometerTD[5], 255);
	TextDrawFont(SpeedometerTD[5], 1);
	TextDrawSetProportional(SpeedometerTD[5], true);
	TextDrawSetShadow(SpeedometerTD[5], 0);

	SpeedometerTD[6] = TextDrawCreate(339.7667, 426.2738, "("); // пусто
	TextDrawLetterSize(SpeedometerTD[6], 0.1926, 0.8699);
	TextDrawAlignment(SpeedometerTD[6], 1);
	TextDrawColor(SpeedometerTD[6], -2139062017);
	TextDrawBackgroundColor(SpeedometerTD[6], 255);
	TextDrawFont(SpeedometerTD[6], 1);
	TextDrawSetProportional(SpeedometerTD[6], true);
	TextDrawSetShadow(SpeedometerTD[6], 0);

	SpeedometerTD[7] = TextDrawCreate(342.0002, 427.9331, "("); // пусто
	TextDrawLetterSize(SpeedometerTD[7], 0.2920, 0.5546);
	TextDrawAlignment(SpeedometerTD[7], 1);
	TextDrawColor(SpeedometerTD[7], -2139062017);
	TextDrawBackgroundColor(SpeedometerTD[7], 255);
	TextDrawFont(SpeedometerTD[7], 1);
	TextDrawSetProportional(SpeedometerTD[7], true);
	TextDrawSetShadow(SpeedometerTD[7], 0);

	SpeedometerTD[8] = TextDrawCreate(343.2003, 427.9331, ")"); // пусто
	TextDrawLetterSize(SpeedometerTD[8], 0.2920, 0.5546);
	TextDrawAlignment(SpeedometerTD[8], 1);
	TextDrawColor(SpeedometerTD[8], -2139062017);
	TextDrawBackgroundColor(SpeedometerTD[8], 255);
	TextDrawFont(SpeedometerTD[8], 1);
	TextDrawSetProportional(SpeedometerTD[8], true);
	TextDrawSetShadow(SpeedometerTD[8], 0);

	SpeedometerTD[9] = TextDrawCreate(343.6667, 429.3072, "LD_SPAC:white"); // пусто
	TextDrawTextSize(SpeedometerTD[9], 1.0000, 3.0000);
	TextDrawAlignment(SpeedometerTD[9], 1);
	TextDrawColor(SpeedometerTD[9], -2139062017);
	TextDrawBackgroundColor(SpeedometerTD[9], 255);
	TextDrawFont(SpeedometerTD[9], 4);
	TextDrawSetProportional(SpeedometerTD[9], false);
	TextDrawSetShadow(SpeedometerTD[9], 0);

	SpeedometerTD[10] = TextDrawCreate(288.4000, 420.6480, "KM/Н"); // пусто
	TextDrawLetterSize(SpeedometerTD[10], 0.1420, 0.8367);
	TextDrawAlignment(SpeedometerTD[10], 2);
	TextDrawColor(SpeedometerTD[10], -1);
	TextDrawBackgroundColor(SpeedometerTD[10], 255);
	TextDrawFont(SpeedometerTD[10], 2);
	TextDrawSetProportional(SpeedometerTD[10], true);
	TextDrawSetShadow(SpeedometerTD[10], 0);

	SpeedometerTD[11] = TextDrawCreate(322.3000, 427.6738, "LOCK"); // пусто
	TextDrawLetterSize(SpeedometerTD[11], 0.1260, 0.7869);
	TextDrawAlignment(SpeedometerTD[11], 1);
	TextDrawColor(SpeedometerTD[11], -347323649);
	TextDrawBackgroundColor(SpeedometerTD[11], 255);
	TextDrawFont(SpeedometerTD[11], 2);
	TextDrawSetProportional(SpeedometerTD[11], true);
	TextDrawSetShadow(SpeedometerTD[11], 0);

	SpeedometerTD[12] = TextDrawCreate(348.1001, 427.5034, "LIGHT"); // пусто
	TextDrawLetterSize(SpeedometerTD[12], 0.1233, 0.7952);
	TextDrawAlignment(SpeedometerTD[12], 1);
	TextDrawColor(SpeedometerTD[12], -347323649);
	TextDrawBackgroundColor(SpeedometerTD[12], 255);
	TextDrawFont(SpeedometerTD[12], 2);
	TextDrawSetProportional(SpeedometerTD[12], true);
	TextDrawSetShadow(SpeedometerTD[12], 0);

	return true;
}

CreateSpeedometerPTD(playerid)
{
	SpeedometerPTD[playerid][0] = CreatePlayerTextDraw(playerid, 338.6665, 399.9960, "ПOМЗЕЛO:_100_З"); // пусто
	PlayerTextDrawLetterSize(playerid, SpeedometerPTD[playerid][0], 0.1400, 1.0109);
	PlayerTextDrawAlignment(playerid, SpeedometerPTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, SpeedometerPTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, SpeedometerPTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, SpeedometerPTD[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, SpeedometerPTD[playerid][0], true);
	PlayerTextDrawSetShadow(playerid, SpeedometerPTD[playerid][0], 0);

	SpeedometerPTD[playerid][1] = CreatePlayerTextDraw(playerid, 338.6665, 412.3967, "МPOАEВ:_10000_KM"); // пусто
	PlayerTextDrawLetterSize(playerid, SpeedometerPTD[playerid][1], 0.1400, 1.0109);
	PlayerTextDrawAlignment(playerid, SpeedometerPTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, SpeedometerPTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, SpeedometerPTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, SpeedometerPTD[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, SpeedometerPTD[playerid][1], true);
	PlayerTextDrawSetShadow(playerid, SpeedometerPTD[playerid][1], 0);

	SpeedometerPTD[playerid][2] = CreatePlayerTextDraw(playerid, 288.6666, 401.0031, "0"); // пусто
	PlayerTextDrawLetterSize(playerid, SpeedometerPTD[playerid][2], 0.3286, 2.3964);
	PlayerTextDrawAlignment(playerid, SpeedometerPTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, SpeedometerPTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, SpeedometerPTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, SpeedometerPTD[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, SpeedometerPTD[playerid][2], true);
	PlayerTextDrawSetShadow(playerid, SpeedometerPTD[playerid][2], 0);

	return true;
}

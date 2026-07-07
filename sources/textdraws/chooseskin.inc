#include <YSI_Coding\y_hooks>

// √лобальные текстдравы
new Text:ChooseSkinTD[12];


hook OnGameModeInit()
{
	ChooseSkinTD[0] = TextDrawCreate(284.6780, 416.3334, "LD_SPAC:white"); // пусто
	TextDrawTextSize(ChooseSkinTD[0], 63.0000, 22.0000);
	TextDrawAlignment(ChooseSkinTD[0], 1);
	TextDrawColor(ChooseSkinTD[0], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[0], 255);
	TextDrawFont(ChooseSkinTD[0], 4);
	TextDrawSetProportional(ChooseSkinTD[0], false);
	TextDrawSetShadow(ChooseSkinTD[0], 0);

	ChooseSkinTD[1] = TextDrawCreate(334.4520, 411.1000, "LD_BEAT:chit"); // пусто
	TextDrawTextSize(ChooseSkinTD[1], 28.0000, 32.6399);
	TextDrawAlignment(ChooseSkinTD[1], 1);
	TextDrawColor(ChooseSkinTD[1], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[1], 255);
	TextDrawFont(ChooseSkinTD[1], 4);
	TextDrawSetProportional(ChooseSkinTD[1], false);
	TextDrawSetShadow(ChooseSkinTD[1], 0);

	ChooseSkinTD[2] = TextDrawCreate(269.6481, 411.1000, "LD_BEAT:chit"); // пусто
	TextDrawTextSize(ChooseSkinTD[2], 28.0000, 32.6399);
	TextDrawAlignment(ChooseSkinTD[2], 1);
	TextDrawColor(ChooseSkinTD[2], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[2], 255);
	TextDrawFont(ChooseSkinTD[2], 4);
	TextDrawSetProportional(ChooseSkinTD[2], false);
	TextDrawSetShadow(ChooseSkinTD[2], 0);

	ChooseSkinTD[3] = TextDrawCreate(317.9372, 423.2333, "SELECT"); // пусто
	TextDrawLetterSize(ChooseSkinTD[3], 0.2299, 0.8358);
	TextDrawTextSize(ChooseSkinTD[3], 6.0000, 57.0000);
	TextDrawAlignment(ChooseSkinTD[3], 2);
	TextDrawColor(ChooseSkinTD[3], -1);
	TextDrawUseBox(ChooseSkinTD[3], true);
	TextDrawBoxColor(ChooseSkinTD[3], 303174144);
	TextDrawBackgroundColor(ChooseSkinTD[3], 255);
	TextDrawFont(ChooseSkinTD[3], 2);
	TextDrawSetProportional(ChooseSkinTD[3], true);
	TextDrawSetShadow(ChooseSkinTD[3], 0);
	TextDrawSetSelectable(ChooseSkinTD[3], true);

	ChooseSkinTD[4] = TextDrawCreate(369.1542, 411.1000, "LD_BEAT:chit"); // пусто
	TextDrawTextSize(ChooseSkinTD[4], 28.0000, 32.6399);
	TextDrawAlignment(ChooseSkinTD[4], 1);
	TextDrawColor(ChooseSkinTD[4], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[4], 255);
	TextDrawFont(ChooseSkinTD[4], 4);
	TextDrawSetProportional(ChooseSkinTD[4], false);
	TextDrawSetShadow(ChooseSkinTD[4], 0);

	ChooseSkinTD[5] = TextDrawCreate(237.0461, 411.1000, "LD_BEAT:chit"); // пусто
	TextDrawTextSize(ChooseSkinTD[5], 28.0000, 32.6399);
	TextDrawAlignment(ChooseSkinTD[5], 1);
	TextDrawColor(ChooseSkinTD[5], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[5], 255);
	TextDrawFont(ChooseSkinTD[5], 4);
	TextDrawSetProportional(ChooseSkinTD[5], false);
	TextDrawSetShadow(ChooseSkinTD[5], 0);

	ChooseSkinTD[6] = TextDrawCreate(367.0472, 424.5167, "LD_BEAT:chit"); // пусто
	TextDrawTextSize(ChooseSkinTD[6], 6.0000, 7.0000);
	TextDrawAlignment(ChooseSkinTD[6], 1);
	TextDrawColor(ChooseSkinTD[6], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[6], 255);
	TextDrawFont(ChooseSkinTD[6], 4);
	TextDrawSetProportional(ChooseSkinTD[6], false);
	TextDrawSetShadow(ChooseSkinTD[6], 0);

	ChooseSkinTD[7] = TextDrawCreate(362.2319, 426.0335, "LD_BEAT:chit"); // пусто
	TextDrawTextSize(ChooseSkinTD[7], 3.0000, 4.0000);
	TextDrawAlignment(ChooseSkinTD[7], 1);
	TextDrawColor(ChooseSkinTD[7], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[7], 255);
	TextDrawFont(ChooseSkinTD[7], 4);
	TextDrawSetProportional(ChooseSkinTD[7], false);
	TextDrawSetShadow(ChooseSkinTD[7], 0);

	ChooseSkinTD[8] = TextDrawCreate(260.9407, 424.5167, "LD_BEAT:chit"); // пусто
	TextDrawTextSize(ChooseSkinTD[8], 6.0000, 7.0000);
	TextDrawAlignment(ChooseSkinTD[8], 1);
	TextDrawColor(ChooseSkinTD[8], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[8], 255);
	TextDrawFont(ChooseSkinTD[8], 4);
	TextDrawSetProportional(ChooseSkinTD[8], false);
	TextDrawSetShadow(ChooseSkinTD[8], 0);

	ChooseSkinTD[9] = TextDrawCreate(267.6261, 426.0335, "LD_BEAT:chit"); // пусто
	TextDrawTextSize(ChooseSkinTD[9], 3.0000, 4.0000);
	TextDrawAlignment(ChooseSkinTD[9], 1);
	TextDrawColor(ChooseSkinTD[9], 303174399);
	TextDrawBackgroundColor(ChooseSkinTD[9], 255);
	TextDrawFont(ChooseSkinTD[9], 4);
	TextDrawSetProportional(ChooseSkinTD[9], false);
	TextDrawSetShadow(ChooseSkinTD[9], 0);

	ChooseSkinTD[10] = TextDrawCreate(384.2413, 421.4332, ">>"); // пусто
	TextDrawLetterSize(ChooseSkinTD[10], 0.3381, 1.3316);
	TextDrawTextSize(ChooseSkinTD[10], 6.0000, 13.0000);
	TextDrawAlignment(ChooseSkinTD[10], 2);
	TextDrawColor(ChooseSkinTD[10], -1);
	TextDrawUseBox(ChooseSkinTD[10], true);
	TextDrawBoxColor(ChooseSkinTD[10], 303174144);
	TextDrawBackgroundColor(ChooseSkinTD[10], 255);
	TextDrawFont(ChooseSkinTD[10], 3);
	TextDrawSetProportional(ChooseSkinTD[10], true);
	TextDrawSetShadow(ChooseSkinTD[10], 0);
	TextDrawSetSelectable(ChooseSkinTD[10], true);

	ChooseSkinTD[11] = TextDrawCreate(251.2331, 421.7333, "<<"); // пусто
	TextDrawLetterSize(ChooseSkinTD[11], 0.3095, 1.2733);
	TextDrawTextSize(ChooseSkinTD[11], 6.0000, 13.0000);
	TextDrawAlignment(ChooseSkinTD[11], 2);
	TextDrawColor(ChooseSkinTD[11], -1);
	TextDrawUseBox(ChooseSkinTD[11], true);
	TextDrawBoxColor(ChooseSkinTD[11], 303174144);
	TextDrawBackgroundColor(ChooseSkinTD[11], 255);
	TextDrawFont(ChooseSkinTD[11], 3);
	TextDrawSetProportional(ChooseSkinTD[11], true);
	TextDrawSetShadow(ChooseSkinTD[11], 0);
	TextDrawSetSelectable(ChooseSkinTD[11], true);

}

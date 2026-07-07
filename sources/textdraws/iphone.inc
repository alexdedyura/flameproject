#if defined IPHONE_TEXTDRAWS_INCLUDED
	#endinput
#endif
#define IPHONE_TEXTDRAWS_INCLUDED

new Text:iPhone[80];

CreateIPhoneTD()
{	iPhone[0] = TextDrawCreate(518.8333, 197.6992, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[0], 32.0000, 40.0000);
	TextDrawAlignment(iPhone[0], 1);
	TextDrawColor(iPhone[0], 235802367);
	TextDrawBackgroundColor(iPhone[0], 255);
	TextDrawFont(iPhone[0], 4);
	TextDrawSetProportional(iPhone[0], false);
	TextDrawSetShadow(iPhone[0], 0);

	iPhone[1] = TextDrawCreate(583.5371, 197.6992, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[1], 32.0000, 40.0000);
	TextDrawAlignment(iPhone[1], 1);
	TextDrawColor(iPhone[1], 235802367);
	TextDrawBackgroundColor(iPhone[1], 255);
	TextDrawFont(iPhone[1], 4);
	TextDrawSetProportional(iPhone[1], false);
	TextDrawSetShadow(iPhone[1], 0);

	iPhone[2] = TextDrawCreate(518.9332, 384.6069, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[2], 32.0000, 40.0000);
	TextDrawAlignment(iPhone[2], 1);
	TextDrawColor(iPhone[2], 235802367);
	TextDrawBackgroundColor(iPhone[2], 255);
	TextDrawFont(iPhone[2], 4);
	TextDrawSetProportional(iPhone[2], false);
	TextDrawSetShadow(iPhone[2], 0);

	iPhone[3] = TextDrawCreate(583.5371, 384.7072, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[3], 32.0000, 40.0000);
	TextDrawAlignment(iPhone[3], 1);
	TextDrawColor(iPhone[3], 235802367);
	TextDrawBackgroundColor(iPhone[3], 255);
	TextDrawFont(iPhone[3], 4);
	TextDrawSetProportional(iPhone[3], false);
	TextDrawSetShadow(iPhone[3], 0);

	iPhone[4] = TextDrawCreate(524.3333, 217.9369, "LD_SPAC:white"); // ïóñòî
	TextDrawTextSize(iPhone[4], 85.9794, 187.0798);
	TextDrawAlignment(iPhone[4], 1);
	TextDrawColor(iPhone[4], 235802367);
	TextDrawBackgroundColor(iPhone[4], 255);
	TextDrawFont(iPhone[4], 4);
	TextDrawSetProportional(iPhone[4], false);
	TextDrawSetShadow(iPhone[4], 0);

	iPhone[5] = TextDrawCreate(534.7000, 204.4481, "LD_SPAC:white"); // ïóñòî
	TextDrawTextSize(iPhone[5], 66.0000, 213.5702);
	TextDrawAlignment(iPhone[5], 1);
	TextDrawColor(iPhone[5], 235802367);
	TextDrawBackgroundColor(iPhone[5], 255);
	TextDrawFont(iPhone[5], 4);
	TextDrawSetProportional(iPhone[5], false);
	TextDrawSetShadow(iPhone[5], 0);

	iPhone[6] = TextDrawCreate(528.1334, 217.5108, "LD_SPAC:white"); // Wallpaper Color
	TextDrawTextSize(iPhone[6], 78.0000, 188.0000);
	TextDrawAlignment(iPhone[6], 1);
	TextDrawColor(iPhone[6], -235802113);
	TextDrawBackgroundColor(iPhone[6], 255);
	TextDrawFont(iPhone[6], 4);
	TextDrawSetProportional(iPhone[6], false);
	TextDrawSetShadow(iPhone[6], 0);

	iPhone[7] = TextDrawCreate(535.7000, 208.3110, "LD_SPAC:white"); // Wallpaper Color
	TextDrawTextSize(iPhone[7], 63.0000, 204.7901);
	TextDrawAlignment(iPhone[7], 1);
	TextDrawColor(iPhone[7], -235802113);
	TextDrawBackgroundColor(iPhone[7], 255);
	TextDrawFont(iPhone[7], 4);
	TextDrawSetProportional(iPhone[7], false);
	TextDrawSetShadow(iPhone[7], 0);

	iPhone[8] = TextDrawCreate(524.5667, 392.2300, "LD_Beat:Chit"); // Wallpaper Color
	TextDrawTextSize(iPhone[8], 21.5799, 25.0000);
	TextDrawAlignment(iPhone[8], 1);
	TextDrawColor(iPhone[8], -235802113);
	TextDrawBackgroundColor(iPhone[8], 255);
	TextDrawFont(iPhone[8], 4);
	TextDrawSetProportional(iPhone[8], false);
	TextDrawSetShadow(iPhone[8], 0);

	iPhone[9] = TextDrawCreate(588.3626, 392.2300, "LD_Beat:Chit"); // Wallpaper Color
	TextDrawTextSize(iPhone[9], 21.5100, 25.0000);
	TextDrawAlignment(iPhone[9], 1);
	TextDrawColor(iPhone[9], -235802113);
	TextDrawBackgroundColor(iPhone[9], 255);
	TextDrawFont(iPhone[9], 4);
	TextDrawSetProportional(iPhone[9], false);
	TextDrawSetShadow(iPhone[9], 0);

	iPhone[10] = TextDrawCreate(524.4666, 204.2628, "LD_Beat:Chit"); // Wallpaper Color
	TextDrawTextSize(iPhone[10], 21.5799, 25.0000);
	TextDrawAlignment(iPhone[10], 1);
	TextDrawColor(iPhone[10], -235802113);
	TextDrawBackgroundColor(iPhone[10], 255);
	TextDrawFont(iPhone[10], 4);
	TextDrawSetProportional(iPhone[10], false);
	TextDrawSetShadow(iPhone[10], 0);

	iPhone[11] = TextDrawCreate(588.2625, 204.2628, "LD_Beat:Chit"); // Wallpaper Color
	TextDrawTextSize(iPhone[11], 21.5799, 25.0000);
	TextDrawAlignment(iPhone[11], 1);
	TextDrawColor(iPhone[11], -235802113);
	TextDrawBackgroundColor(iPhone[11], 255);
	TextDrawFont(iPhone[11], 4);
	TextDrawSetProportional(iPhone[11], false);
	TextDrawSetShadow(iPhone[11], 0);

	iPhone[12] = TextDrawCreate(537.6317, 209.5110, "09:41"); // Âðåìÿ
	TextDrawLetterSize(iPhone[12], 0.1412, 0.6499);
	TextDrawAlignment(iPhone[12], 2);
	TextDrawColor(iPhone[12], 255);
	TextDrawBackgroundColor(iPhone[12], 611826687);
	TextDrawFont(iPhone[12], 1);
	TextDrawSetProportional(iPhone[12], true);
	TextDrawSetShadow(iPhone[12], 0);

	iPhone[13] = TextDrawCreate(595.7647, 209.3701, "Wi-Fi"); // Ñâÿçü
	TextDrawLetterSize(iPhone[13], 0.1412, 0.6499);
	TextDrawAlignment(iPhone[13], 2);
	TextDrawColor(iPhone[13], 255);
	TextDrawBackgroundColor(iPhone[12], 611826687);
	TextDrawFont(iPhone[13], 1);
	TextDrawSetProportional(iPhone[12], true);
	TextDrawSetShadow(iPhone[13], 0);

	iPhone[14] = TextDrawCreate(523.3331, 243.5110, "I~N~I"); // ïóñòî
	TextDrawLetterSize(iPhone[14], 0.1726, 1.6246);
	TextDrawAlignment(iPhone[14], 1);
	TextDrawColor(iPhone[14], 255);
	TextDrawBackgroundColor(iPhone[14], 255);
	TextDrawFont(iPhone[14], 1);
	TextDrawSetProportional(iPhone[14], true);
	TextDrawSetShadow(iPhone[14], 0);

	iPhone[15] = TextDrawCreate(523.3331, 230.8103, "I"); // ïóñòî
	TextDrawLetterSize(iPhone[15], 0.1806, 1.0441);
	TextDrawAlignment(iPhone[15], 1);
	TextDrawColor(iPhone[15], 255);
	TextDrawBackgroundColor(iPhone[15], 255);
	TextDrawFont(iPhone[15], 1);
	TextDrawSetProportional(iPhone[15], true);
	TextDrawSetShadow(iPhone[15], 0);

	iPhone[16] = TextDrawCreate(609.6663, 237.4474, "I"); // ïóñòî
	TextDrawLetterSize(iPhone[16], 0.1870, 4.0970);
	TextDrawAlignment(iPhone[16], 1);
	TextDrawColor(iPhone[16], 255);
	TextDrawBackgroundColor(iPhone[16], 255);
	TextDrawFont(iPhone[16], 1);
	TextDrawSetProportional(iPhone[16], true);
	TextDrawSetShadow(iPhone[16], 0);

	iPhone[17] = TextDrawCreate(545.3673, 208.1257, "LD_SPAC:white"); // ïóñòî
	TextDrawTextSize(iPhone[17], 42.3899, 2.0000);
	TextDrawAlignment(iPhone[17], 1);
	TextDrawColor(iPhone[17], 235802367);
	TextDrawBackgroundColor(iPhone[17], 255);
	TextDrawFont(iPhone[17], 4);
	TextDrawSetProportional(iPhone[17], false);
	TextDrawSetShadow(iPhone[17], 0);

	iPhone[18] = TextDrawCreate(578.6027, 208.2666, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[18], 11.0000, 8.3400);
	TextDrawAlignment(iPhone[18], 1);
	TextDrawColor(iPhone[18], 235802367);
	TextDrawBackgroundColor(iPhone[18], 255);
	TextDrawFont(iPhone[18], 4);
	TextDrawSetProportional(iPhone[18], false);
	TextDrawSetShadow(iPhone[18], 0);

	iPhone[19] = TextDrawCreate(543.7006, 208.2666, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[19], 11.0000, 8.3599);
	TextDrawAlignment(iPhone[19], 1);
	TextDrawColor(iPhone[19], 235802367);
	TextDrawBackgroundColor(iPhone[19], 255);
	TextDrawFont(iPhone[19], 4);
	TextDrawSetProportional(iPhone[19], false);
	TextDrawSetShadow(iPhone[19], 0);

	iPhone[20] = TextDrawCreate(545.6337, 209.3406, "LD_SPAC:white"); // ïóñòî
	TextDrawTextSize(iPhone[20], 42.2401, 3.0000);
	TextDrawAlignment(iPhone[20], 1);
	TextDrawColor(iPhone[20], 235802367);
	TextDrawBackgroundColor(iPhone[20], 255);
	TextDrawFont(iPhone[20], 4);
	TextDrawSetProportional(iPhone[20], false);
	TextDrawSetShadow(iPhone[20], 0);

	iPhone[21] = TextDrawCreate(549.4669, 211.8294, "LD_SPAC:white"); // ïóñòî
	TextDrawTextSize(iPhone[21], 34.0000, 3.1298);
	TextDrawAlignment(iPhone[21], 1);
	TextDrawColor(iPhone[21], 235802367);
	TextDrawBackgroundColor(iPhone[21], 255);
	TextDrawFont(iPhone[21], 4);
	TextDrawSetProportional(iPhone[21], false);
	TextDrawSetShadow(iPhone[21], 0);

	iPhone[22] = TextDrawCreate(543.6997, 206.9223, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[22], 6.0000, 3.0000);
	TextDrawAlignment(iPhone[22], 1);
	TextDrawColor(iPhone[22], 235802367);
	TextDrawBackgroundColor(iPhone[22], 255);
	TextDrawFont(iPhone[22], 4);
	TextDrawSetProportional(iPhone[22], false);
	TextDrawSetShadow(iPhone[22], 0);

	iPhone[23] = TextDrawCreate(583.4332, 206.9223, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[23], 6.0000, 3.0000);
	TextDrawAlignment(iPhone[23], 1);
	TextDrawColor(iPhone[23], 235802367);
	TextDrawBackgroundColor(iPhone[23], 255);
	TextDrawFont(iPhone[23], 4);
	TextDrawSetProportional(iPhone[23], false);
	TextDrawSetShadow(iPhone[23], 0);

	iPhone[24] = TextDrawCreate(568.1334, 382.5888, "O"); // Icons
	TextDrawLetterSize(iPhone[24], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[24], 1);
	TextDrawColor(iPhone[24], -1380325633);
	TextDrawBackgroundColor(iPhone[24], 255);
	TextDrawFont(iPhone[24], 2);
	TextDrawSetProportional(iPhone[24], true);
	TextDrawSetShadow(iPhone[24], 0);

	iPhone[25] = TextDrawCreate(586.5288, 382.5888, "O"); // Icons
	TextDrawLetterSize(iPhone[25], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[25], 1);
	TextDrawColor(iPhone[25], -2139062017);
	TextDrawBackgroundColor(iPhone[25], 255);
	TextDrawFont(iPhone[25], 2);
	TextDrawSetProportional(iPhone[25], true);
	TextDrawSetShadow(iPhone[25], 0);

	iPhone[26] = TextDrawCreate(531.2003, 382.5888, "O"); // Icons
	TextDrawLetterSize(iPhone[26], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[26], 1);
	TextDrawColor(iPhone[26], 9568511);
	TextDrawBackgroundColor(iPhone[26], 255);
	TextDrawFont(iPhone[26], 2);
	TextDrawSetProportional(iPhone[26], true);
	TextDrawSetShadow(iPhone[26], 0);

	iPhone[27] = TextDrawCreate(549.5958, 382.5888, "O"); // Icons
	TextDrawLetterSize(iPhone[27], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[27], 1);
	TextDrawColor(iPhone[27], -347323649);
	TextDrawBackgroundColor(iPhone[27], 255);
	TextDrawFont(iPhone[27], 2);
	TextDrawSetProportional(iPhone[27], true);
	TextDrawSetShadow(iPhone[27], 0);

	iPhone[28] = TextDrawCreate(533.1333, 394.4776, "LD_SPAC:white"); // Calls
	TextDrawTextSize(iPhone[28], 12.0000, 14.0000);
	TextDrawAlignment(iPhone[28], 1);
	TextDrawColor(iPhone[28], 9568511);
	TextDrawBackgroundColor(iPhone[28], 255);
	TextDrawFont(iPhone[28], 4);
	TextDrawSetProportional(iPhone[28], false);
	TextDrawSetShadow(iPhone[28], 0);
	TextDrawSetSelectable(iPhone[28], true);

	iPhone[29] = TextDrawCreate(552.6665, 394.3481, "LD_SPAC:white"); // Contacts
	TextDrawTextSize(iPhone[29], 12.0000, 14.0000);
	TextDrawAlignment(iPhone[29], 1);
	TextDrawColor(iPhone[29], -347323649);
	TextDrawBackgroundColor(iPhone[29], 255);
	TextDrawFont(iPhone[29], 4);
	TextDrawSetProportional(iPhone[29], false);
	TextDrawSetShadow(iPhone[29], 0);
	TextDrawSetSelectable(iPhone[29], true);

	iPhone[30] = TextDrawCreate(570.6665, 393.9331, "LD_SPAC:white"); // Messages
	TextDrawTextSize(iPhone[30], 12.0000, 13.0000);
	TextDrawAlignment(iPhone[30], 1);
	TextDrawColor(iPhone[30], -1380319233);
	TextDrawBackgroundColor(iPhone[30], 255);
	TextDrawFont(iPhone[30], 4);
	TextDrawSetProportional(iPhone[30], false);
	TextDrawSetShadow(iPhone[30], 0);
	TextDrawSetSelectable(iPhone[30], true);

	iPhone[31] = TextDrawCreate(589.3331, 393.9331, "LD_SPAC:white"); // Settings
	TextDrawTextSize(iPhone[31], 12.0000, 13.0000);
	TextDrawAlignment(iPhone[31], 1);
	TextDrawColor(iPhone[31], -2139062017);
	TextDrawBackgroundColor(iPhone[31], 255);
	TextDrawFont(iPhone[31], 4);
	TextDrawSetProportional(iPhone[31], false);
	TextDrawSetShadow(iPhone[31], 0);
	TextDrawSetSelectable(iPhone[31], true);

	iPhone[32] = TextDrawCreate(567.0003, 239.7967, "09:41"); // ïóñòî
	TextDrawLetterSize(iPhone[32], 0.4000, 1.6000);
	TextDrawAlignment(iPhone[32], 2);
	TextDrawColor(iPhone[32], -1061109505);
	TextDrawBackgroundColor(iPhone[32], 12);
	TextDrawFont(iPhone[32], 1);
	TextDrawSetProportional(iPhone[32], true);
	TextDrawSetShadow(iPhone[32], 1);

	iPhone[33] = TextDrawCreate(567.0003, 250.7973, RusText("�������")); // ïóñòî
	TextDrawLetterSize(iPhone[33], 0.2813, 1.3178);
	TextDrawAlignment(iPhone[33], 2);
	TextDrawColor(iPhone[33], -1061109505);
	TextDrawBackgroundColor(iPhone[33], 11);
	TextDrawFont(iPhone[33], 1);
	TextDrawSetProportional(iPhone[33], true);
	TextDrawSetShadow(iPhone[33], 1);

	iPhone[34] = TextDrawCreate(566.9669, 260.4642, RusText("31 �������")); // ïóñòî
	TextDrawLetterSize(iPhone[34], 0.3145, 1.2553);
	TextDrawAlignment(iPhone[34], 2);
	TextDrawColor(iPhone[34], -1061109505);
	TextDrawBackgroundColor(iPhone[34], 11);
	TextDrawFont(iPhone[34], 1);
	TextDrawSetProportional(iPhone[34], true);
	TextDrawSetShadow(iPhone[34], 1);

	iPhone[35] = TextDrawCreate(530.0670, 418.5924, "particle:lamp_shad_64"); // ïóñòî
	TextDrawTextSize(iPhone[35], 77.0000, -8.0000);
	TextDrawAlignment(iPhone[35], 1);
	TextDrawColor(iPhone[35], -210);
	TextDrawBackgroundColor(iPhone[35], 255);
	TextDrawFont(iPhone[35], 4);
	TextDrawSetProportional(iPhone[35], false);
	TextDrawSetShadow(iPhone[35], 0);

	iPhone[36] = TextDrawCreate(571.1334, 392.3591, "o"); // ïóñòî
	TextDrawLetterSize(iPhone[36], 0.4189, 1.4838);
	TextDrawAlignment(iPhone[36], 1);
	TextDrawColor(iPhone[36], -1);
	TextDrawBackgroundColor(iPhone[36], 255);
	TextDrawFont(iPhone[36], 2);
	TextDrawSetProportional(iPhone[36], true);
	TextDrawSetShadow(iPhone[36], 0);

	iPhone[37] = TextDrawCreate(533.5996, 367.8258, " "); // ïóñòî
	TextDrawTextSize(iPhone[37], 48.0000, 69.0000);
	TextDrawAlignment(iPhone[37], 1);
	TextDrawColor(iPhone[37], -1);
	TextDrawFont(iPhone[37], 5);
	TextDrawSetProportional(iPhone[37], false);
	TextDrawSetShadow(iPhone[37], 0);
	TextDrawSetPreviewModel(iPhone[37], 19177);
	TextDrawSetPreviewRot(iPhone[37], 0.0000, 0.0000, 0.0000, 1.0000);
	TextDrawBackgroundColor(iPhone[37], 0xFFFFFF00);

	iPhone[38] = TextDrawCreate(554.0662, 393.5184, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[38], 7.1399, 9.0000);
	TextDrawAlignment(iPhone[38], 1);
	TextDrawColor(iPhone[38], -456998657);
	TextDrawBackgroundColor(iPhone[38], 255);
	TextDrawFont(iPhone[38], 4);
	TextDrawSetProportional(iPhone[38], false);
	TextDrawSetShadow(iPhone[38], 0);

	iPhone[39] = TextDrawCreate(572.7667, 397.4518, "LD_SPAC:white"); // ïóñòî
	TextDrawTextSize(iPhone[39], 7.0000, 5.0000);
	TextDrawAlignment(iPhone[39], 1);
	TextDrawColor(iPhone[39], -1);
	TextDrawBackgroundColor(iPhone[39], 255);
	TextDrawFont(iPhone[39], 4);
	TextDrawSetProportional(iPhone[39], false);
	TextDrawSetShadow(iPhone[39], 0);

	iPhone[40] = TextDrawCreate(571.6666, 397.0776, "/"); // ïóñòî
	TextDrawLetterSize(iPhone[40], 0.4343, 1.0109);
	TextDrawAlignment(iPhone[40], 1);
	TextDrawColor(iPhone[40], -1);
	TextDrawBackgroundColor(iPhone[40], 255);
	TextDrawFont(iPhone[40], 2);
	TextDrawSetProportional(iPhone[40], true);
	TextDrawSetShadow(iPhone[40], 0);

	iPhone[41] = TextDrawCreate(573.4663, 393.5444, "..."); // ïóñòî
	TextDrawLetterSize(iPhone[41], 0.2029, 0.9487);
	TextDrawAlignment(iPhone[41], 1);
	TextDrawColor(iPhone[41], -1380325633);
	TextDrawBackgroundColor(iPhone[41], 255);
	TextDrawFont(iPhone[41], 1);
	TextDrawSetProportional(iPhone[41], true);
	TextDrawSetShadow(iPhone[41], 0);

	iPhone[42] = TextDrawCreate(590.6666, 392.8442, "I_I_I"); // ïóñòî
	TextDrawLetterSize(iPhone[42], 0.1903, 1.5958);
	TextDrawAlignment(iPhone[42], 1);
	TextDrawColor(iPhone[42], -1);
	TextDrawBackgroundColor(iPhone[42], 255);
	TextDrawFont(iPhone[42], 1);
	TextDrawSetProportional(iPhone[42], true);
	TextDrawSetShadow(iPhone[42], 0);

	iPhone[43] = TextDrawCreate(589.9666, 397.1369, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[43], 2.7400, 4.0000);
	TextDrawAlignment(iPhone[43], 1);
	TextDrawColor(iPhone[43], -1);
	TextDrawBackgroundColor(iPhone[43], 255);
	TextDrawFont(iPhone[43], 4);
	TextDrawSetProportional(iPhone[43], false);
	TextDrawSetShadow(iPhone[43], 0);

	iPhone[44] = TextDrawCreate(593.2999, 400.6405, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[44], 2.7899, 4.0000);
	TextDrawAlignment(iPhone[44], 1);
	TextDrawColor(iPhone[44], -1);
	TextDrawBackgroundColor(iPhone[44], 255);
	TextDrawFont(iPhone[44], 4);
	TextDrawSetProportional(iPhone[44], false);
	TextDrawSetShadow(iPhone[44], 0);

	iPhone[45] = TextDrawCreate(596.6333, 398.0516, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[45], 2.7400, 4.0000);
	TextDrawAlignment(iPhone[45], 1);
	TextDrawColor(iPhone[45], -1);
	TextDrawBackgroundColor(iPhone[45], 255);
	TextDrawFont(iPhone[45], 4);
	TextDrawSetProportional(iPhone[45], false);
	TextDrawSetShadow(iPhone[45], 0);

	iPhone[46] = TextDrawCreate(534.4666, 408.9074, "/"); // ïóñòî
	TextDrawLetterSize(iPhone[46], 0.6563, -1.4986);
	TextDrawAlignment(iPhone[46], 1);
	TextDrawColor(iPhone[46], -1);
	TextDrawBackgroundColor(iPhone[46], 255);
	TextDrawFont(iPhone[46], 1);
	TextDrawSetProportional(iPhone[46], true);
	TextDrawSetShadow(iPhone[46], 0);

	iPhone[47] = TextDrawCreate(533.7999, 394.2333, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[47], 6.0000, 4.3997);
	TextDrawAlignment(iPhone[47], 1);
	TextDrawColor(iPhone[47], -1);
	TextDrawBackgroundColor(iPhone[47], 255);
	TextDrawFont(iPhone[47], 4);
	TextDrawSetProportional(iPhone[47], false);
	TextDrawSetShadow(iPhone[47], 0);

	iPhone[48] = TextDrawCreate(538.1331, 402.8297, "LD_Beat:Chit"); // ïóñòî
	TextDrawTextSize(iPhone[48], 6.0000, 4.1697);
	TextDrawAlignment(iPhone[48], 1);
	TextDrawColor(iPhone[48], -1);
	TextDrawBackgroundColor(iPhone[48], 255);
	TextDrawFont(iPhone[48], 4);
	TextDrawSetProportional(iPhone[48], false);
	TextDrawSetShadow(iPhone[48], 0);

	iPhone[49] = TextDrawCreate(568.1334, 287.2828, "O"); // Icons
	TextDrawLetterSize(iPhone[49], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[49], 1);
	TextDrawColor(iPhone[49], -347323649);
	TextDrawBackgroundColor(iPhone[49], 255);
	TextDrawFont(iPhone[49], 2);
	TextDrawSetProportional(iPhone[49], true);
	TextDrawSetShadow(iPhone[49], 0);

	iPhone[50] = TextDrawCreate(586.5288, 287.2828, "O"); // Icons
	TextDrawLetterSize(iPhone[50], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[50], 1);
	TextDrawColor(iPhone[50], 303174399);
	TextDrawBackgroundColor(iPhone[50], 255);
	TextDrawFont(iPhone[50], 2);
	TextDrawSetProportional(iPhone[50], true);
	TextDrawSetShadow(iPhone[50], 0);

	iPhone[51] = TextDrawCreate(531.2003, 287.2828, "o"); // Icons
	TextDrawLetterSize(iPhone[51], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[51], 1);
	TextDrawColor(iPhone[51], 8388863);
	TextDrawBackgroundColor(iPhone[51], 255);
	TextDrawFont(iPhone[51], 2);
	TextDrawSetProportional(iPhone[51], true);
	TextDrawSetShadow(iPhone[51], 0);

	iPhone[52] = TextDrawCreate(549.5958, 287.2828, "o"); // Icons
	TextDrawLetterSize(iPhone[52], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[52], 1);
	TextDrawColor(iPhone[52], 1605024511);
	TextDrawBackgroundColor(iPhone[52], 255);
	TextDrawFont(iPhone[52], 2);
	TextDrawSetProportional(iPhone[52], true);
	TextDrawSetShadow(iPhone[52], 0);

	iPhone[53] = TextDrawCreate(533.1333, 299.1716, "LD_SPAC:white"); // Bank
	TextDrawTextSize(iPhone[53], 12.0000, 14.0000);
	TextDrawAlignment(iPhone[53], 1);
	TextDrawColor(iPhone[53], 8388863);
	TextDrawBackgroundColor(iPhone[53], 255);
	TextDrawFont(iPhone[53], 4);
	TextDrawSetProportional(iPhone[53], false);
	TextDrawSetShadow(iPhone[53], 0);
	TextDrawSetSelectable(iPhone[53], true);

	iPhone[54] = TextDrawCreate(552.6665, 299.0422, "LD_SPAC:white"); // GPS
	TextDrawTextSize(iPhone[54], 12.0000, 14.0000);
	TextDrawAlignment(iPhone[54], 1);
	TextDrawColor(iPhone[54], 1605024511);
	TextDrawBackgroundColor(iPhone[54], 255);
	TextDrawFont(iPhone[54], 4);
	TextDrawSetProportional(iPhone[54], false);
	TextDrawSetShadow(iPhone[54], 0);
	TextDrawSetSelectable(iPhone[54], true);

	iPhone[55] = TextDrawCreate(570.6665, 298.6271, "LD_SPAC:white"); // Apple Music
	TextDrawTextSize(iPhone[55], 12.0000, 13.0000);
	TextDrawAlignment(iPhone[55], 1);
	TextDrawColor(iPhone[55], -347323649);
	TextDrawBackgroundColor(iPhone[55], 255);
	TextDrawFont(iPhone[55], 4);
	TextDrawSetProportional(iPhone[55], false);
	TextDrawSetShadow(iPhone[55], 0);
	TextDrawSetSelectable(iPhone[55], true);

	iPhone[56] = TextDrawCreate(589.3331, 298.6271, "LD_SPAC:white"); // Settings
	TextDrawTextSize(iPhone[56], 12.0000, 13.0000);
	TextDrawAlignment(iPhone[56], 1);
	TextDrawColor(iPhone[56], 303174399);
	TextDrawBackgroundColor(iPhone[56], 255);
	TextDrawFont(iPhone[56], 4);
	TextDrawSetProportional(iPhone[56], false);
	TextDrawSetShadow(iPhone[56], 0);
	TextDrawSetSelectable(iPhone[56], true);

	iPhone[57] = TextDrawCreate(568.1334, 307.9841, "O"); // Icons
	TextDrawLetterSize(iPhone[57], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[57], 1);
	TextDrawColor(iPhone[57], -1061109505);
	TextDrawBackgroundColor(iPhone[57], 255);
	TextDrawFont(iPhone[57], 2);
	TextDrawSetProportional(iPhone[57], true);
	TextDrawSetShadow(iPhone[57], 0);

	iPhone[58] = TextDrawCreate(586.5288, 307.9841, "O"); // Icons
	TextDrawLetterSize(iPhone[58], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[58], 1);
	TextDrawColor(iPhone[58], -1061109505);
	TextDrawBackgroundColor(iPhone[58], 255);
	TextDrawFont(iPhone[58], 2);
	TextDrawSetProportional(iPhone[58], true);
	TextDrawSetShadow(iPhone[58], 0);

	iPhone[59] = TextDrawCreate(531.2003, 307.9841, "o"); // Icons
	TextDrawLetterSize(iPhone[59], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[59], 1);
	TextDrawColor(iPhone[59], -1061109505);
	TextDrawBackgroundColor(iPhone[59], 255);
	TextDrawFont(iPhone[59], 2);
	TextDrawSetProportional(iPhone[59], true);
	TextDrawSetShadow(iPhone[59], 0);

	iPhone[60] = TextDrawCreate(549.5958, 307.9841, "0"); // Icons
	TextDrawLetterSize(iPhone[60], 0.7257, 3.4416);
	TextDrawAlignment(iPhone[60], 1);
	TextDrawColor(iPhone[60], -1061109505);
	TextDrawBackgroundColor(iPhone[60], 255);
	TextDrawFont(iPhone[60], 2);
	TextDrawSetProportional(iPhone[60], true);
	TextDrawSetShadow(iPhone[60], 0);

	iPhone[61] = TextDrawCreate(533.1333, 319.8728, "LD_SPAC:white"); // Calls
	TextDrawTextSize(iPhone[61], 12.0000, 14.0000);
	TextDrawAlignment(iPhone[61], 1);
	TextDrawColor(iPhone[61], -1061109505);
	TextDrawBackgroundColor(iPhone[61], 255);
	TextDrawFont(iPhone[61], 4);
	TextDrawSetProportional(iPhone[61], false);
	TextDrawSetShadow(iPhone[61], 0);
	TextDrawSetSelectable(iPhone[61], true);

	iPhone[62] = TextDrawCreate(552.6665, 319.7434, "LD_SPAC:white"); // Contacts
	TextDrawTextSize(iPhone[62], 12.0000, 14.0000);
	TextDrawAlignment(iPhone[62], 1);
	TextDrawColor(iPhone[62], -1061109505);
	TextDrawBackgroundColor(iPhone[62], 255);
	TextDrawFont(iPhone[62], 4);
	TextDrawSetProportional(iPhone[62], false);
	TextDrawSetShadow(iPhone[62], 0);
	TextDrawSetSelectable(iPhone[62], true);

	iPhone[63] = TextDrawCreate(570.6665, 319.3286, "LD_SPAC:white"); // Messages
	TextDrawTextSize(iPhone[63], 12.0000, 13.0000);
	TextDrawAlignment(iPhone[63], 1);
	TextDrawColor(iPhone[63], -1061109505);
	TextDrawBackgroundColor(iPhone[63], 255);
	TextDrawFont(iPhone[63], 4);
	TextDrawSetProportional(iPhone[63], false);
	TextDrawSetShadow(iPhone[63], 0);
	TextDrawSetSelectable(iPhone[63], true);

	iPhone[64] = TextDrawCreate(589.3331, 319.3283, "LD_SPAC:white"); // Settings
	TextDrawTextSize(iPhone[64], 12.0000, 13.0000);
	TextDrawAlignment(iPhone[64], 1);
	TextDrawColor(iPhone[64], -1061109505);
	TextDrawBackgroundColor(iPhone[64], 255);
	TextDrawFont(iPhone[64], 4);
	TextDrawSetProportional(iPhone[64], false);
	TextDrawSetShadow(iPhone[64], 0);
	TextDrawSetSelectable(iPhone[64], true);

	iPhone[65] = TextDrawCreate(568.1334, 329.0855, "O"); // Icons
	TextDrawLetterSize(iPhone[65], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[65], 1);
	TextDrawColor(iPhone[65], -1061109505);
	TextDrawBackgroundColor(iPhone[65], 255);
	TextDrawFont(iPhone[65], 2);
	TextDrawSetProportional(iPhone[65], true);
	TextDrawSetShadow(iPhone[65], 0);

	iPhone[66] = TextDrawCreate(586.5288, 329.0855, "O"); // Icons
	TextDrawLetterSize(iPhone[66], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[66], 1);
	TextDrawColor(iPhone[66], -1061109505);
	TextDrawBackgroundColor(iPhone[66], 255);
	TextDrawFont(iPhone[66], 2);
	TextDrawSetProportional(iPhone[66], true);
	TextDrawSetShadow(iPhone[66], 0);

	iPhone[67] = TextDrawCreate(531.2003, 329.0855, "O"); // Icons
	TextDrawLetterSize(iPhone[67], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[67], 1);
	TextDrawColor(iPhone[67], -1061109505);
	TextDrawBackgroundColor(iPhone[67], 255);
	TextDrawFont(iPhone[67], 2);
	TextDrawSetProportional(iPhone[67], true);
	TextDrawSetShadow(iPhone[67], 0);

	iPhone[68] = TextDrawCreate(549.5958, 329.0855, "o"); // Icons
	TextDrawLetterSize(iPhone[68], 0.6643, 3.4665);
	TextDrawAlignment(iPhone[68], 1);
	TextDrawColor(iPhone[68], -1061109505);
	TextDrawBackgroundColor(iPhone[68], 255);
	TextDrawFont(iPhone[68], 2);
	TextDrawSetProportional(iPhone[68], true);
	TextDrawSetShadow(iPhone[68], 0);

	iPhone[69] = TextDrawCreate(533.1333, 340.9743, "LD_SPAC:white"); // Calls
	TextDrawTextSize(iPhone[69], 12.0000, 14.0000);
	TextDrawAlignment(iPhone[69], 1);
	TextDrawColor(iPhone[69], -1061109505);
	TextDrawBackgroundColor(iPhone[69], 255);
	TextDrawFont(iPhone[69], 4);
	TextDrawSetProportional(iPhone[69], false);
	TextDrawSetShadow(iPhone[69], 0);
	TextDrawSetSelectable(iPhone[69], true);

	iPhone[70] = TextDrawCreate(552.6665, 340.8446, "LD_SPAC:white"); // Contacts
	TextDrawTextSize(iPhone[70], 12.0000, 14.0000);
	TextDrawAlignment(iPhone[70], 1);
	TextDrawColor(iPhone[70], -1061109505);
	TextDrawBackgroundColor(iPhone[70], 255);
	TextDrawFont(iPhone[70], 4);
	TextDrawSetProportional(iPhone[70], false);
	TextDrawSetShadow(iPhone[70], 0);
	TextDrawSetSelectable(iPhone[70], true);

	iPhone[71] = TextDrawCreate(570.6665, 340.4299, "LD_SPAC:white"); // Messages
	TextDrawTextSize(iPhone[71], 12.0000, 13.0000);
	TextDrawAlignment(iPhone[71], 1);
	TextDrawColor(iPhone[71], -1061109505);
	TextDrawBackgroundColor(iPhone[71], 255);
	TextDrawFont(iPhone[71], 4);
	TextDrawSetProportional(iPhone[71], false);
	TextDrawSetShadow(iPhone[71], 0);
	TextDrawSetSelectable(iPhone[71], true);

	iPhone[72] = TextDrawCreate(589.3331, 340.4298, "LD_SPAC:white"); // Settings
	TextDrawTextSize(iPhone[72], 12.0000, 13.0000);
	TextDrawAlignment(iPhone[72], 1);
	TextDrawColor(iPhone[72], -1061109505);
	TextDrawBackgroundColor(iPhone[72], 255);
	TextDrawFont(iPhone[72], 4);
	TextDrawSetProportional(iPhone[72], false);
	TextDrawSetShadow(iPhone[72], 0);
	TextDrawSetSelectable(iPhone[72], true);

	iPhone[73] = TextDrawCreate(574.4000, 320.3074, "?______?~N~~N~?______?"); // ïóñòî
	TextDrawLetterSize(iPhone[73], 0.2651, 1.1763);
	TextDrawAlignment(iPhone[73], 1);
	TextDrawColor(iPhone[73], -1);
	TextDrawBackgroundColor(iPhone[73], 255);
	TextDrawFont(iPhone[73], 1);
	TextDrawSetProportional(iPhone[73], true);
	TextDrawSetShadow(iPhone[73], 0);

	iPhone[74] = TextDrawCreate(537.3372, 320.2073, "?______?~N~~N~?______?"); // ïóñòî
	TextDrawLetterSize(iPhone[74], 0.2732, 1.1598);
	TextDrawAlignment(iPhone[74], 1);
	TextDrawColor(iPhone[74], -1);
	TextDrawBackgroundColor(iPhone[74], 255);
	TextDrawFont(iPhone[74], 1);
	TextDrawSetProportional(iPhone[74], true);
	TextDrawSetShadow(iPhone[74], 0);

	iPhone[75] = TextDrawCreate(536.5665, 297.0223, "$"); // ïóñòî
	TextDrawLetterSize(iPhone[75], 0.3242, 1.5834);
	TextDrawAlignment(iPhone[75], 1);
	TextDrawColor(iPhone[75], -1);
	TextDrawBackgroundColor(iPhone[75], 7930111);
	TextDrawFont(iPhone[75], 1);
	TextDrawSetProportional(iPhone[75], true);
	TextDrawSetShadow(iPhone[75], 1);

	iPhone[76] = TextDrawCreate(552.6666, 301.1852, "GPS"); // ïóñòî
	TextDrawLetterSize(iPhone[76], 0.1694, 0.7164);
	TextDrawAlignment(iPhone[76], 1);
	TextDrawColor(iPhone[76], -1);
	TextDrawBackgroundColor(iPhone[76], 255);
	TextDrawFont(iPhone[76], 1);
	TextDrawSetProportional(iPhone[76], true);
	TextDrawSetShadow(iPhone[76], 0);

	iPhone[77] = TextDrawCreate(553.2999, 307.6072, "LD_SPAC:white"); // ïóñòî
	TextDrawTextSize(iPhone[77], 9.0000, 1.0000);
	TextDrawAlignment(iPhone[77], 1);
	TextDrawColor(iPhone[77], -1);
	TextDrawBackgroundColor(iPhone[77], 255);
	TextDrawFont(iPhone[77], 4);
	TextDrawSetProportional(iPhone[77], false);
	TextDrawSetShadow(iPhone[77], 0);

	iPhone[78] = TextDrawCreate(591.0001, 299.7702, "hud:radar_impound"); // ïóñòî
	TextDrawTextSize(iPhone[78], 8.0000, 9.0000);
	TextDrawAlignment(iPhone[78], 1);
	TextDrawColor(iPhone[78], -1);
	TextDrawBackgroundColor(iPhone[78], 255);
	TextDrawFont(iPhone[78], 4);
	TextDrawSetProportional(iPhone[78], false);
	TextDrawSetShadow(iPhone[78], 0);

	iPhone[79] = TextDrawCreate(572.2647, 301.0296, "hud:radar_dateDisco"); // ïóñòî
	TextDrawTextSize(iPhone[79], 8.0000, 9.0000);
	TextDrawAlignment(iPhone[79], 1);
	TextDrawColor(iPhone[79], -1);
	TextDrawBackgroundColor(iPhone[79], 255);
	TextDrawFont(iPhone[79], 4);
	TextDrawSetProportional(iPhone[79], false);
	TextDrawSetShadow(iPhone[79], 0);
	return true;
}

ShowIPhoneTD(playerid)
{
	for(new i = 0; i < sizeof(iPhone); i++)
	{
		if(i >= 6 && i <= 11) continue;
		TextDrawShowForPlayer(playerid, iPhone[i]);
	}
	return true;
}

HideIPhoneTD(playerid)
{
	for(new i = 0; i < sizeof(iPhone); i++)
		TextDrawHideForPlayer(playerid, iPhone[i]);
	return true;
}

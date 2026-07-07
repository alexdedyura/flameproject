#include <YSI_Coding\y_hooks>

// "Horizon" starter job: cell-tower repair.
// Talk to the Horizon NPC (ALT) -> get a service van + a random tower marker ->
// drive there, leave the van, stop on the repair marker -> 10-step Y/N mini-game ->
// paid $50-$80 on hand, next tower is assigned. Quit via NPC or disconnect = fired, van removed.

#define HORIZON_ACTOR_SKIN      8
#define HORIZON_ACTOR_X         -2046.5615
#define HORIZON_ACTOR_Y         465.7402
#define HORIZON_ACTOR_Z         35.1719
#define HORIZON_ACTOR_FA        0.0
#define HORIZON_VAN_MODEL       552
#define HORIZON_REPAIR_STEPS    10
#define HORIZON_PAY_MIN         50
#define HORIZON_PAY_MAX         80
#define HORIZON_PRESS_DELAY     500 // ms between accepted QTE key presses
#define HORIZON_WRONG_COOLDOWN  3000 // ms penalty after a wrong QTE key
#define HORIZON_REACH_RADIUS    4.0  // on-foot distance to the tower that starts the repair

// Van spawn lots (x, y, z, angle)
new const Float:HorizonCarSpawns[8][4] = {
	{-2072.1089, 390.0395, 35.2643, 176.9852},
	{-2081.9365, 389.0187, 35.2643, 179.2402},
	{-2092.4678, 388.9921, 35.2642, 179.5023},
	{-2053.1494, 390.6523, 35.2642, 268.9449},
	{-2042.2688, 386.0550, 35.2642, 270.0880},
	{-2127.3594, 390.3889, 35.2643, 90.6055},
	{-2131.0662, 382.7628, 35.2644, 87.1740},
	{-2075.7385, 381.7166, 35.2642, 270.1666}
};

// Cell towers (x, y, z, angle)
new const Float:HorizonTowers[8][4] = {
	{-1786.5387, -558.9492, 15.6694, 2.8098},
	{-1544.8773, -1486.2775, 36.3430, 359.6764},
	{-2433.0286, -1318.2941, 311.3454, 86.4705},
	{-2878.1230, 344.5862, 12.3413, 177.6281},
	{-2434.9790, 676.9253, 35.0716, 179.8214},
	{-1904.2058, 1262.5216, 19.4429, 44.1467},
	{-2202.8716, -373.2075, 35.4684, 7.5100},
	{-2736.6855, 1249.8823, 11.7686, 182.6414}
};

new bool:HorizonActive[MAX_PLAYERS];
new HorizonVeh[MAX_PLAYERS];
new STREAMER_TAG_PICKUP:HorizonPickup[MAX_PLAYERS];
new HorizonTower[MAX_PLAYERS];
new bool:HorizonInGame[MAX_PLAYERS];
new HorizonStep[MAX_PLAYERS];
new HorizonReqKey[MAX_PLAYERS];
new HorizonLastPress[MAX_PLAYERS];
new HorizonPenalty[MAX_PLAYERS];
new PlayerText:HorizonQTE_TD[MAX_PLAYERS];

hook OnGameModeInit()
{
	CreateDynamicActor(HORIZON_ACTOR_SKIN, HORIZON_ACTOR_X, HORIZON_ACTOR_Y, HORIZON_ACTOR_Z, HORIZON_ACTOR_FA, true, 100.0, 0, 0);
	CreateDynamic3DTextLabel(!"Работник "FLAME_COLOR"Horizon"COLOR_WHITE"\nНажмите "FLAME_COLOR"ALT"COLOR_WHITE" для разговора", 0xFFFFFFFF, HORIZON_ACTOR_X, HORIZON_ACTOR_Y, HORIZON_ACTOR_Z + 0.7, 10.0, _, _, 1, 0, 0);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	HorizonResetState(playerid);
	HorizonCreateTD(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason

	HorizonEndJob(playerid, true);

	if(HorizonQTE_TD[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, HorizonQTE_TD[playerid]);
		HorizonQTE_TD[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(HorizonInGame[playerid])
	{
		new pressedYes = (newkeys & KEY_YES) && !(oldkeys & KEY_YES);
		new pressedNo  = (newkeys & KEY_NO)  && !(oldkeys & KEY_NO);

		if(pressedYes || pressedNo)
		{
			new tick = GetTickCount();

			if(HorizonPenalty[playerid] > tick)
				return 1; // wrong-press cooldown still active

			if(tick - HorizonLastPress[playerid] < HORIZON_PRESS_DELAY)
				return 1; // press cooldown not elapsed yet

			HorizonLastPress[playerid] = tick;

			new correct = (pressedYes && HorizonReqKey[playerid] == 0) || (pressedNo && HorizonReqKey[playerid] == 1);
			if(correct)
			{
				HorizonStep[playerid]++;
				if(HorizonStep[playerid] >= HORIZON_REPAIR_STEPS)
					HorizonFinishRepair(playerid);
				else
					HorizonNextStep(playerid);
			}
			else
			{
				HorizonPenalty[playerid] = tick + HORIZON_WRONG_COOLDOWN;
				GameTextForPlayer(playerid, RusText("~r~Неверная клавиша!~n~~w~Подождите 3 секунды"), HORIZON_WRONG_COOLDOWN, 5);
			}
		}
		return 1;
	}

	if((newkeys & KEY_WALK) && !(oldkeys & KEY_WALK) && !IsPlayerInAnyVehicle(playerid)
		&& IsPlayerInRangeOfPoint(playerid, 3.0, HORIZON_ACTOR_X, HORIZON_ACTOR_Y, HORIZON_ACTOR_Z)
		&& GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
	{
		HorizonShowDialog(playerid);
		return 1;
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_JOB_HORIZON)
	{
		if(!response) return 1;

		if(!HorizonActive[playerid])
			HorizonStartJob(playerid);
		else
			HorizonEndJob(playerid, true);
		return 1;
	}
	return 1;
}

hook OnPlayerPickUpDynamicPickup(playerid, STREAMER_TAG_PICKUP:pickupid)
{
	if(HorizonActive[playerid] && !HorizonInGame[playerid] && pickupid == HorizonPickup[playerid] && !IsPlayerInAnyVehicle(playerid))
		HorizonStartRepair(playerid);
	return 1;
}

// Reliable on-foot arrival trigger (the dynamic pickup alone is too sensitive to the exact Z).
Horizon_PlayerSecTimer(playerid)
{
	if(!HorizonActive[playerid] || HorizonInGame[playerid] || HorizonTower[playerid] < 0)
		return 1;
	if(IsPlayerInAnyVehicle(playerid))
		return 1;
	if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)
		return 1;

	new t = HorizonTower[playerid];
	if(IsPlayerInRangeOfPoint(playerid, HORIZON_REACH_RADIUS, HorizonTowers[t][0], HorizonTowers[t][1], HorizonTowers[t][2]))
		HorizonStartRepair(playerid);
	return 1;
}

HorizonCreateTD(playerid)
{
	HorizonQTE_TD[playerid] = CreatePlayerTextDraw(playerid, 320.0, 160.0, "_");
	PlayerTextDrawAlignment(playerid, HorizonQTE_TD[playerid], 2);
	PlayerTextDrawFont(playerid, HorizonQTE_TD[playerid], 1);
	PlayerTextDrawLetterSize(playerid, HorizonQTE_TD[playerid], 0.55, 2.4);
	PlayerTextDrawColor(playerid, HorizonQTE_TD[playerid], -1);
	PlayerTextDrawSetOutline(playerid, HorizonQTE_TD[playerid], 1);
	PlayerTextDrawSetShadow(playerid, HorizonQTE_TD[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, HorizonQTE_TD[playerid], 150);
	return 1;
}

HorizonResetState(playerid)
{
	HorizonActive[playerid] = false;
	HorizonInGame[playerid] = false;
	HorizonStep[playerid] = 0;
	HorizonReqKey[playerid] = 0;
	HorizonTower[playerid] = -1;
	HorizonLastPress[playerid] = 0;
	HorizonPenalty[playerid] = 0;
	HorizonVeh[playerid] = INVALID_VEHICLE_ID;
	HorizonPickup[playerid] = STREAMER_TAG_PICKUP:INVALID_STREAMER_ID;
	HorizonQTE_TD[playerid] = PlayerText:INVALID_TEXT_DRAW;
	DeletePVar(playerid, !"HorizonQTE");
	return 1;
}

HorizonShowDialog(playerid)
{
	new string[600];
	if(!HorizonActive[playerid])
	{
		format(string, sizeof(string),
			""COLOR_WHITE"Здравствуйте! Компания "FLAME_COLOR"Horizon"COLOR_WHITE" занимается обслуживанием сотовых вышек.\n\n\
			Мы выдадим вам служебный автомобиль и адрес вышки. Доберитесь до неё, выйдите из машины и проведите ремонт.\n\n\
			За каждую отремонтированную вышку вы получите "GREEN_COLOR"%d-%d$"COLOR_WHITE" наличными.\n\n\
			Хотите приступить к работе?",
			HORIZON_PAY_MIN, HORIZON_PAY_MAX);
		ShowPlayerDialog(playerid, D_JOB_HORIZON, DIALOG_STYLE_MSGBOX, !"Работа: Horizon", string, !"Начать", !"Отмена");
	}
	else
	{
		ShowPlayerDialog(playerid, D_JOB_HORIZON, DIALOG_STYLE_MSGBOX, !"Работа: Horizon",
			!""COLOR_WHITE"Вы уже работаете в "FLAME_COLOR"Horizon"COLOR_WHITE".\n\nХотите уволиться? Рабочий автомобиль будет изъят.",
			!"Уволиться", !"Назад");
	}
	return 1;
}

HorizonStartJob(playerid)
{
	if(HorizonActive[playerid]) return 1;

	new s = random(sizeof(HorizonCarSpawns));
	new vw = GetPlayerVirtualWorld(playerid);

	HorizonVeh[playerid] = CreateVehicle(HORIZON_VAN_MODEL, HorizonCarSpawns[s][0], HorizonCarSpawns[s][1], HorizonCarSpawns[s][2], HorizonCarSpawns[s][3], -1, -1, -1);
	VehicleInfo[HorizonVeh[playerid]][vType] = VEHICLE_TYPE_NONE;
	VehicleInfo[HorizonVeh[playerid]][vFuel] = float(random(6) + 10); // 10-15 liters
	SetVehicleVirtualWorld(HorizonVeh[playerid], vw);
	LinkVehicleToInterior(HorizonVeh[playerid], 0);

	SetPlayerInterior(playerid, 0);
	SetPlayerPos(playerid, HorizonCarSpawns[s][0], HorizonCarSpawns[s][1], HorizonCarSpawns[s][2]);
	PutPlayerInVehicle(playerid, HorizonVeh[playerid], 0);

	HorizonActive[playerid] = true;
	HorizonTower[playerid] = -1;

	SendClientMessage(playerid, COLOR_GREY, !"[Horizon]: "COLOR_WHITE"Вы устроились на работу. Доберитесь до отмеченной вышки.");
	HorizonGiveTower(playerid);
	return 1;
}

HorizonGiveTower(playerid)
{
	// Pick a tower uniformly among ALL the others (guarantees variety, no 2-tower bounce).
	new t;
	if(HorizonTower[playerid] < 0)
	{
		t = random(sizeof(HorizonTowers));
	}
	else
	{
		t = random(sizeof(HorizonTowers) - 1);
		if(t >= HorizonTower[playerid]) t++;
	}
	HorizonTower[playerid] = t;

	SetPlayerCheckpoint(playerid, HorizonTowers[t][0], HorizonTowers[t][1], HorizonTowers[t][2], 3.0);

	if(HorizonPickup[playerid] != STREAMER_TAG_PICKUP:INVALID_STREAMER_ID)
	{
		DestroyDynamicPickup(HorizonPickup[playerid]);
		HorizonPickup[playerid] = STREAMER_TAG_PICKUP:INVALID_STREAMER_ID;
	}
	HorizonPickup[playerid] = CreateDynamicPickup(19902, 1, HorizonTowers[t][0], HorizonTowers[t][1], HorizonTowers[t][2], 0, 0, playerid);

	SendClientMessage(playerid, COLOR_GREY, !"[Horizon]: "COLOR_WHITE"Доберитесь до вышки, выйдите из машины и встаньте на маркер ремонта.");
	return 1;
}

HorizonStartRepair(playerid)
{
	if(HorizonPickup[playerid] != STREAMER_TAG_PICKUP:INVALID_STREAMER_ID)
	{
		DestroyDynamicPickup(HorizonPickup[playerid]);
		HorizonPickup[playerid] = STREAMER_TAG_PICKUP:INVALID_STREAMER_ID;
	}
	DisablePlayerCheckpoint(playerid);

	HorizonInGame[playerid] = true;
	HorizonStep[playerid] = 0;
	HorizonLastPress[playerid] = 0; // allow the first press immediately
	HorizonPenalty[playerid] = 0;
	SetPVarInt(playerid, !"HorizonQTE", 1); // intercept Y/N so they don't open inventory/menu
	TogglePlayerControllable(playerid, false);

	SendClientMessage(playerid, COLOR_GREY, !"[Horizon]: "COLOR_WHITE"Начался ремонт! Нажимайте указанные клавиши.");
	HorizonNextStep(playerid);
	return 1;
}

HorizonNextStep(playerid)
{
	HorizonReqKey[playerid] = random(2);

	new string[80];
	if(HorizonReqKey[playerid] == 0)
		format(string, sizeof(string), "Ремонт вышки  %d/%d~n~Нажмите ~g~Y", HorizonStep[playerid] + 1, HORIZON_REPAIR_STEPS);
	else
		format(string, sizeof(string), "Ремонт вышки  %d/%d~n~Нажмите ~r~N", HorizonStep[playerid] + 1, HORIZON_REPAIR_STEPS);

	PlayerTextDrawSetString(playerid, HorizonQTE_TD[playerid], RusText(string));
	PlayerTextDrawShow(playerid, HorizonQTE_TD[playerid]);
	return 1;
}

HorizonFinishRepair(playerid)
{
	new reward = HORIZON_PAY_MIN + random(HORIZON_PAY_MAX - HORIZON_PAY_MIN + 1);

	HorizonInGame[playerid] = false;
	HorizonStep[playerid] = 0;
	DeletePVar(playerid, !"HorizonQTE");
	PlayerTextDrawHide(playerid, HorizonQTE_TD[playerid]);
	TogglePlayerControllable(playerid, true);

	UpdatePlayerMoney(playerid, reward);

	Quest_OnPlayerRepairTower(playerid); // count toward the "Begin Path" tower-repair task

	new string[64];
	format(string, sizeof(string), "~g~Ремонт завершен~n~~w~+%d$", reward);
	GameTextForPlayer(playerid, RusText(string), 4000, 3);
	SendClientMessageEx(playerid, COLOR_GREY, "[Horizon]: "COLOR_WHITE"Вышка отремонтирована. Вы получили "GREEN_COLOR"%d$"COLOR_WHITE".", reward);

	HorizonGiveTower(playerid);
	return 1;
}

HorizonEndJob(playerid, bool:fired = true)
{
	new bool:wasActive = HorizonActive[playerid];

	if(HorizonVeh[playerid] != INVALID_VEHICLE_ID)
	{
		DestroyVehicle(HorizonVeh[playerid]);
		HorizonVeh[playerid] = INVALID_VEHICLE_ID;
	}
	if(HorizonPickup[playerid] != STREAMER_TAG_PICKUP:INVALID_STREAMER_ID)
	{
		DestroyDynamicPickup(HorizonPickup[playerid]);
		HorizonPickup[playerid] = STREAMER_TAG_PICKUP:INVALID_STREAMER_ID;
	}
	if(IsPlayerConnected(playerid))
	{
		DisablePlayerCheckpoint(playerid);
		if(HorizonInGame[playerid])
		{
			TogglePlayerControllable(playerid, true);
			if(HorizonQTE_TD[playerid] != PlayerText:INVALID_TEXT_DRAW)
				PlayerTextDrawHide(playerid, HorizonQTE_TD[playerid]);
		}
		DeletePVar(playerid, !"HorizonQTE");
	}

	HorizonActive[playerid] = false;
	HorizonInGame[playerid] = false;
	HorizonStep[playerid] = 0;
	HorizonTower[playerid] = -1;

	if(fired && wasActive && IsPlayerConnected(playerid))
		SendClientMessage(playerid, COLOR_GREY, !"[Horizon]: "COLOR_WHITE"Вы уволились. Служебный автомобиль изъят.");
	return 1;
}

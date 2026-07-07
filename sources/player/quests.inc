#include <YSI_Coding\y_hooks>

#define QUEST_BEGIN_PATH_STARTED     (1)
#define QUEST_BEGIN_PATH_BUS         (2)
#define QUEST_BEGIN_PATH_ID_CARD     (4)
#define QUEST_BEGIN_PATH_DRIVE_B     (8)
#define QUEST_BEGIN_PATH_BANK_CARD   (16)
#define QUEST_BEGIN_PATH_TOWERS      (32)
#define QUEST_BEGIN_PATH_CARSHARING  (64)
#define QUEST_BEGIN_PATH_DONE        (QUEST_BEGIN_PATH_BUS | QUEST_BEGIN_PATH_ID_CARD | QUEST_BEGIN_PATH_DRIVE_B | QUEST_BEGIN_PATH_BANK_CARD | QUEST_BEGIN_PATH_TOWERS | QUEST_BEGIN_PATH_CARSHARING)

// Tower-repair task: progress counter packed into high bits of pQuestProgress (bits 8-11).
#define QUEST_TOWERS_REQUIRED        (10)
#define QUEST_TOWERS_SHIFT           (8)
#define QUEST_TOWERS_MASK            (15 << QUEST_TOWERS_SHIFT)

#define QUEST_GUIDE_POS              -1415.2441,-302.1331,14.1411
#define QUEST_GUIDE_FA               320.2899
#define QUEST_GOVERNMENT_BUS_POS     -2754.93,395.466,4.3359

new PlayerText:QuestCurrentPTD[MAX_PLAYERS][4];

hook OnGameModeInit()
{
	new __ms0[] = !"ALTER TABLE `accounts` ADD COLUMN IF NOT EXISTS `quest_progress` int(11) NOT NULL DEFAULT 0";
	mysql_query(ConnectMySQL, __ms0);

	CreateDynamicActor(305, QUEST_GUIDE_POS, QUEST_GUIDE_FA, true, 100.0, 0, 0);
	CreateDynamic3DTextLabel(
		"Джон Смит\nНажмите "FLAME_COLOR"ALT"COLOR_WHITE" для взаимодействия",
		0xFFFFFFFF,
		QUEST_GUIDE_POS + 0.5,
		5.0,
		_,
		_,
		1,
		0,
		0
	);
	return true;
}

hook OnPlayerConnect(playerid)
{
	QuestCurrentPTD[playerid][0] = CreatePlayerTextDraw(playerid, 426.0000, 388.0000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, QuestCurrentPTD[playerid][0], 206.0000, 45.0000);
	PlayerTextDrawAlignment(playerid, QuestCurrentPTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, QuestCurrentPTD[playerid][0], 235802367);
	PlayerTextDrawBackgroundColor(playerid, QuestCurrentPTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, QuestCurrentPTD[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, QuestCurrentPTD[playerid][0], false);
	PlayerTextDrawSetShadow(playerid, QuestCurrentPTD[playerid][0], 0);

	QuestCurrentPTD[playerid][1] = CreatePlayerTextDraw(playerid, 428.0000, 390.0000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, QuestCurrentPTD[playerid][1], 202.0000, 41.7298);
	PlayerTextDrawAlignment(playerid, QuestCurrentPTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, QuestCurrentPTD[playerid][1], 538976511);
	PlayerTextDrawBackgroundColor(playerid, QuestCurrentPTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, QuestCurrentPTD[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, QuestCurrentPTD[playerid][1], false);
	PlayerTextDrawSetShadow(playerid, QuestCurrentPTD[playerid][1], 0);

	QuestCurrentPTD[playerid][2] = CreatePlayerTextDraw(playerid, 529.0000, 393.5000, "CURRENT_QUEST");
	PlayerTextDrawLetterSize(playerid, QuestCurrentPTD[playerid][2], 0.1400, 1.0109);
	PlayerTextDrawAlignment(playerid, QuestCurrentPTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, QuestCurrentPTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, QuestCurrentPTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, QuestCurrentPTD[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, QuestCurrentPTD[playerid][2], true);
	PlayerTextDrawSetShadow(playerid, QuestCurrentPTD[playerid][2], 0);

	QuestCurrentPTD[playerid][3] = CreatePlayerTextDraw(playerid, 529.0000, 406.0000, "TASK");
	PlayerTextDrawLetterSize(playerid, QuestCurrentPTD[playerid][3], 0.1400, 1.0109);
	PlayerTextDrawAlignment(playerid, QuestCurrentPTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, QuestCurrentPTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, QuestCurrentPTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, QuestCurrentPTD[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, QuestCurrentPTD[playerid][3], true);
	PlayerTextDrawSetShadow(playerid, QuestCurrentPTD[playerid][3], 0);
	return true;
}

hook OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason

	for(new i = 0; i < sizeof(QuestCurrentPTD[]); i++)
	{
		if(QuestCurrentPTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, QuestCurrentPTD[playerid][i]);
			QuestCurrentPTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return true;
}

hook OnPlayerSpawn(playerid)
{
	Quest_UpdateCurrentTextDraw(playerid);
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_WALK) && !(oldkeys & KEY_WALK) && !IsPlayerInAnyVehicle(playerid)
		&& IsPlayerInRangeOfPoint(playerid, 3.0, QUEST_GUIDE_POS)
		&& GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
	{
		Quest_StartBeginPath(playerid);
		ShowPlayerBeginPathQuest(playerid, true);
		return true;
	}
	return true;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_QUESTS_MAIN)
	{
		if(!response) return true;
		if(listitem == 0) return ShowPlayerBeginPathQuest(playerid);
	}
	else if(dialogid == D_QUEST_BEGIN_PATH)
	{
		if(response) return ShowPlayerBeginPathTasks(playerid);
	}
	else if(dialogid == D_QUEST_BEGIN_TASKS)
	{
		if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_STARTED))
		{
			if(response) return ShowPlayerBeginPathQuest(playerid);
			return true;
		}
		if(!response) return ShowPlayerBeginPathQuest(playerid);
		return ShowPlayerBeginPathTaskDetails(playerid, listitem);
	}
	else if(dialogid == D_QUEST_TASK_DETAIL)
	{
		if(response) return ShowPlayerBeginPathTasks(playerid);
	}
	return true;
}

ShowPlayerQuests(playerid)
{
	new status[32];
	Quest_GetBeginPathStatus(playerid, status);

	new string[128];
	format(string, sizeof(string), "Квест\tСтатус\n"FLAME_COLOR"1. "COLOR_WHITE"Начало пути\t%s", status);
	ShowPlayerDialog(playerid, D_QUESTS_MAIN, DIALOG_STYLE_TABLIST_HEADERS, !"Квесты", string, !"Далее", !"Закрыть");
	return true;
}

ShowPlayerBeginPathQuest(playerid, bool:npc_dialog = false)
{
	new quest_status[32];
	Quest_GetBeginPathStatus(playerid, quest_status);

	new string[768];
	if(npc_dialog)
	{
		format(string, sizeof(string),
			""COLOR_WHITE"Здравствуйте. Меня зовут "FLAME_COLOR"Джон Смит"COLOR_WHITE".\n\
			Я помогу вам освоиться в штате: покажу, как добраться до правительства, оформить документы и получить первые права.\n\n\
			"COLOR_WHITE"Квест: "FLAME_COLOR"Начало пути\n"COLOR_WHITE"Статус: %s\n\n\
			Нажмите "FLAME_COLOR"Задания"COLOR_WHITE", чтобы посмотреть доступные подпункты квеста.",
			quest_status
		);
		ShowPlayerDialog(playerid, D_QUEST_BEGIN_PATH, DIALOG_STYLE_MSGBOX, !"Джон Смит", string, !"Задания", !"Закрыть");
	}
	else
	{
		format(string, sizeof(string),
			""COLOR_WHITE"Квест: "FLAME_COLOR"Начало пути\n"COLOR_WHITE"Статус: %s\n\n\
			"COLOR_WHITE"Куратор: "FLAME_COLOR"Джон Смит\n\n\
			"COLOR_WHITE"Подпункты квеста открываются постепенно. В списке заданий отображается выполненный путь и ближайшая новая цель.",
			quest_status
		);
		ShowPlayerDialog(playerid, D_QUEST_BEGIN_PATH, DIALOG_STYLE_MSGBOX, !"Начало пути", string, !"Задания", !"Закрыть");
	}
	return true;
}

ShowPlayerBeginPathTasks(playerid)
{
	if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_STARTED))
	{
		ShowPlayerDialog(playerid, D_QUEST_BEGIN_TASKS, DIALOG_STYLE_MSGBOX, !"Начало пути", !""COLOR_WHITE"Поговорите с "FLAME_COLOR"Джоном Смитом"COLOR_WHITE" на спавне, чтобы начать квест.", !"Назад", !"Закрыть");
		return true;
	}

	new string[768], task_status[32];
	format(string, sizeof(string), "Задание\tСтатус\tНаграда\n");

	Quest_GetTaskStatus(playerid, QUEST_BEGIN_PATH_BUS, task_status);
	format(string, sizeof(string), "%s"FLAME_COLOR"1. "COLOR_WHITE"Приехать в правительство на автобусе\t%s\t"GREEN_COLOR"10$\n", string, task_status);

	if(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_BUS)
	{
		Quest_GetTaskStatus(playerid, QUEST_BEGIN_PATH_ID_CARD, task_status);
		format(string, sizeof(string), "%s"FLAME_COLOR"2. "COLOR_WHITE"Получить ID карту\t%s\t"GREEN_COLOR"30$\n", string, task_status);
	}

	if(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_ID_CARD)
	{
		Quest_GetTaskStatus(playerid, QUEST_BEGIN_PATH_DRIVE_B, task_status);
		format(string, sizeof(string), "%s"FLAME_COLOR"3. "COLOR_WHITE"Сдать на права категории B\t%s\t"GREEN_COLOR"50$\n", string, task_status);
	}

	if(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_DRIVE_B)
	{
		Quest_GetTaskStatus(playerid, QUEST_BEGIN_PATH_BANK_CARD, task_status);
		format(string, sizeof(string), "%s"FLAME_COLOR"4. "COLOR_WHITE"Получить банковскую карту\t%s\t"GREEN_COLOR"70$", string, task_status);
	}

	if(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_BANK_CARD)
	{
		Quest_GetTaskStatus(playerid, QUEST_BEGIN_PATH_TOWERS, task_status);
		format(string, sizeof(string), "%s\n"FLAME_COLOR"5. "COLOR_WHITE"Отремонтировать вышки Horizon (%d/%d)\t%s\t"GREEN_COLOR"100$", string, Quest_GetTowerCount(playerid), QUEST_TOWERS_REQUIRED, task_status);
	}

	if(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_TOWERS)
	{
		Quest_GetTaskStatus(playerid, QUEST_BEGIN_PATH_CARSHARING, task_status);
		format(string, sizeof(string), "%s\n"FLAME_COLOR"6. "COLOR_WHITE"Арендовать транспорт в каршеринге\t%s\t"GREEN_COLOR"120$", string, task_status);
	}

	ShowPlayerDialog(playerid, D_QUEST_BEGIN_TASKS, DIALOG_STYLE_TABLIST_HEADERS, !"Начало пути: задания", string, !"Открыть", !"Назад");
	return true;
}

ShowPlayerBeginPathTaskDetails(playerid, listitem)
{
	new task_bit, reward, title[64], description[512];
	switch(listitem)
	{
		case 0:
		{
			task_bit = QUEST_BEGIN_PATH_BUS;
			reward = 10;
			format(title, sizeof(title), "Приехать в правительство на автобусе");
			format(description, sizeof(description), "Найдите ближайшую автобусную остановку и нажмите "FLAME_COLOR"ALT"COLOR_WHITE". В списке остановок выберите "FLAME_COLOR"Правительство"COLOR_WHITE" и дождитесь окончания поездки.");
		}
		case 1:
		{
			if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_BUS))
				return ShowPlayerBeginPathTasks(playerid);
			task_bit = QUEST_BEGIN_PATH_ID_CARD;
			reward = 30;
			format(title, sizeof(title), "Получить ID карту");
			format(description, sizeof(description), "Зайдите в здание правительства. У стойки получения ID-карты нажмите "FLAME_COLOR"ALT"COLOR_WHITE" и подтвердите оформление документа.");
		}
		case 2:
		{
			if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_ID_CARD))
				return ShowPlayerBeginPathTasks(playerid);
			task_bit = QUEST_BEGIN_PATH_DRIVE_B;
			reward = 50;
			format(title, sizeof(title), "Сдать на права категории B");
			format(description, sizeof(description), "Отправляйтесь в DMV, начните экзамен на категорию "FLAME_COLOR"B"COLOR_WHITE", сдайте теорию в компьютерном классе и завершите практический маршрут на легковом автомобиле.");
		}
		case 3:
		{
			if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_DRIVE_B))
				return ShowPlayerBeginPathTasks(playerid);
			task_bit = QUEST_BEGIN_PATH_BANK_CARD;
			reward = 70;
			format(title, sizeof(title), "Получить банковскую карту");
			format(description, sizeof(description), "Посетите национальный банк, подойдите к стойке обслуживания и нажмите "FLAME_COLOR"ALT"COLOR_WHITE". Подтвердите открытие счёта, чтобы получить банковскую карту в инвентарь.");
		}
		case 4:
		{
			if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_BANK_CARD))
				return ShowPlayerBeginPathTasks(playerid);
			task_bit = QUEST_BEGIN_PATH_TOWERS;
			reward = 100;
			format(title, sizeof(title), "Отремонтировать вышки Horizon");
			format(description, sizeof(description), "Устройтесь работником в "FLAME_COLOR"Horizon"COLOR_WHITE" у работника на спавне автопарка, получите служебный фургон и отремонтируйте "FLAME_COLOR"%d"COLOR_WHITE" сотовых вышек. Текущий прогресс: "FLAME_COLOR"%d/%d"COLOR_WHITE".", QUEST_TOWERS_REQUIRED, Quest_GetTowerCount(playerid), QUEST_TOWERS_REQUIRED);
		}
		case 5:
		{
			if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_TOWERS))
				return ShowPlayerBeginPathTasks(playerid);
			task_bit = QUEST_BEGIN_PATH_CARSHARING;
			reward = 120;
			format(title, sizeof(title), "Арендовать транспорт в каршеринге");
			format(description, sizeof(description), "Отправляйтесь в зону каршеринга, выберите любой автомобиль и оформите аренду сроком не менее 3 дней. Используйте клавишу "FLAME_COLOR"ALT"COLOR_WHITE" в зоне каршеринга, чтобы открыть меню аренды.");
		}
		default: return ShowPlayerBeginPathTasks(playerid);
	}

	new task_status[32], string[1024];
	Quest_GetTaskStatus(playerid, task_bit, task_status);
	format(string, sizeof(string),
		""COLOR_WHITE"Задание: "FLAME_COLOR"%s\n\n\
		"COLOR_WHITE"Что необходимо сделать:\n%s\n\n\
		"COLOR_WHITE"Награда: "GREEN_COLOR"%i$\n\
		"COLOR_WHITE"Статус: %s",
		title,
		description,
		reward,
		task_status
	);
	ShowPlayerDialog(playerid, D_QUEST_TASK_DETAIL, DIALOG_STYLE_MSGBOX, !"Описание задания", string, !"Назад", !"Закрыть");
	return true;
}

Quest_StartBeginPath(playerid)
{
	if(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_STARTED)
		return true;

	pData[playerid][pQuestProgress] |= QUEST_BEGIN_PATH_STARTED;
	Quest_SaveProgress(playerid);
	Quest_UpdateCurrentTextDraw(playerid);
	SendClientMessage(playerid, COLOR_GREY, !"[КВЕСТ]: "COLOR_WHITE"Вы начали квест "FLAME_COLOR"Начало пути"COLOR_WHITE".");
	return true;
}

Quest_OnPlayerFinishBusTravel(playerid, Float:x, Float:y, Float:z)
{
	if(GetDistanceBetweenPoints(x, y, z, QUEST_GOVERNMENT_BUS_POS) <= 10.0)
		return Quest_CompleteBeginPathTask(playerid, QUEST_BEGIN_PATH_BUS, 10, "Вы приехали в правительство на автобусе.");
	return true;
}

Quest_OnPlayerGetIDCard(playerid)
{
	return Quest_CompleteBeginPathTask(playerid, QUEST_BEGIN_PATH_ID_CARD, 30, "Вы получили ID карту.");
}

Quest_OnPlayerGetDriveLicB(playerid)
{
	return Quest_CompleteBeginPathTask(playerid, QUEST_BEGIN_PATH_DRIVE_B, 50, "Вы сдали на права категории B.");
}

Quest_OnPlayerGetBankCard(playerid)
{
	return Quest_CompleteBeginPathTask(playerid, QUEST_BEGIN_PATH_BANK_CARD, 70, "Вы получили банковскую карту.");
}

Quest_OnPlayerRentSharingVehicle(playerid, days)
{
	if(days < 3)
		return true;

	return Quest_CompleteBeginPathTask(playerid, QUEST_BEGIN_PATH_CARSHARING, 120, "Вы арендовали транспорт в каршеринге.");
}

Quest_GetTowerCount(playerid)
{
	return (pData[playerid][pQuestProgress] & QUEST_TOWERS_MASK) >> QUEST_TOWERS_SHIFT;
}

Quest_SetTowerCount(playerid, count)
{
	if(count < 0) count = 0;
	if(count > QUEST_TOWERS_REQUIRED) count = QUEST_TOWERS_REQUIRED;
	pData[playerid][pQuestProgress] = (pData[playerid][pQuestProgress] & ~QUEST_TOWERS_MASK) | ((count & 15) << QUEST_TOWERS_SHIFT);
	return count;
}

Quest_OnPlayerRepairTower(playerid)
{
	if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_STARTED))
		return true;
	if(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_TOWERS)
		return true;

	new count = Quest_GetTowerCount(playerid) + 1;
	Quest_SetTowerCount(playerid, count);

	if(count >= QUEST_TOWERS_REQUIRED)
		return Quest_CompleteBeginPathTask(playerid, QUEST_BEGIN_PATH_TOWERS, 100, "Вы отремонтировали 10 вышек Horizon.");

	Quest_SaveProgress(playerid);
	Quest_UpdateCurrentTextDraw(playerid);
	SendClientMessageEx(playerid, COLOR_GREY, "[КВЕСТ]: "COLOR_WHITE"Отремонтировано вышек: "FLAME_COLOR"%d/%d"COLOR_WHITE".", count, QUEST_TOWERS_REQUIRED);
	return true;
}

Quest_CompleteBeginPathTask(playerid, task_bit, reward, const message[])
{
	if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_STARTED))
		return true;
	if(pData[playerid][pQuestProgress] & task_bit)
		return true;

	pData[playerid][pQuestProgress] |= task_bit;
	Quest_SaveProgress(playerid);
	Quest_UpdateCurrentTextDraw(playerid);
	UpdatePlayerMoney(playerid, reward);
	SendClientMessageEx(playerid, COLOR_GREY, "[КВЕСТ]: "COLOR_WHITE"%s Награда: "GREEN_COLOR"%i$"COLOR_WHITE".", message, reward);

	if((pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_DONE) == QUEST_BEGIN_PATH_DONE)
	{
		Quest_HideCurrentTextDraw(playerid);
		GameTextForPlayer(playerid, RusText("~g~Квест выполнен"), 5000, 3);
		SendClientMessage(playerid, COLOR_GREY, !"[КВЕСТ]: "COLOR_WHITE"Квест "FLAME_COLOR"Начало пути"COLOR_WHITE" завершён!");
	}

	return true;
}

Quest_UpdateCurrentTextDraw(playerid)
{
	if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_STARTED)
		|| (pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_DONE) == QUEST_BEGIN_PATH_DONE)
	{
		Quest_HideCurrentTextDraw(playerid);
		return true;
	}

	new task[96];
	Quest_GetCurrentTaskText(playerid, task);

	new string[128];
	format(string, sizeof(string), "~r~CURRENT QUEST~w~: НАЧАЛО ПУТИ");
	PlayerTextDrawSetString(playerid, QuestCurrentPTD[playerid][2], RusText(string));
	format(string, sizeof(string), "~r~TASK~w~: %s", task);
	PlayerTextDrawSetString(playerid, QuestCurrentPTD[playerid][3], RusText(string));
	for(new i = 0; i < sizeof(QuestCurrentPTD[]); i++)
		PlayerTextDrawShow(playerid, QuestCurrentPTD[playerid][i]);
	return true;
}

Quest_HideCurrentTextDraw(playerid)
{
	for(new i = 0; i < sizeof(QuestCurrentPTD[]); i++)
		PlayerTextDrawHide(playerid, QuestCurrentPTD[playerid][i]);
	return true;
}

Quest_GetCurrentTaskText(playerid, task[], maxtask = sizeof task)
{
	if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_BUS))
		format(task, maxtask, "Добраться до правительства");
	else if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_ID_CARD))
		format(task, maxtask, "Получить ID карту");
	else if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_DRIVE_B))
		format(task, maxtask, "Сдать права категории B");
	else if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_BANK_CARD))
		format(task, maxtask, "Получить банковскую карту");
	else if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_TOWERS))
		format(task, maxtask, "Ремонт вышек (%d/%d)", Quest_GetTowerCount(playerid), QUEST_TOWERS_REQUIRED);
	else if(!(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_CARSHARING))
		format(task, maxtask, "Аренда транспорта (3 дня)");
	else
		format(task, maxtask, "Квест завершён");
	return true;
}

Quest_GetBeginPathStatus(playerid, status[], maxstatus = sizeof status)
{
	if((pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_DONE) == QUEST_BEGIN_PATH_DONE)
		format(status, maxstatus, GREEN_COLOR"Завершён");
	else if(pData[playerid][pQuestProgress] & QUEST_BEGIN_PATH_STARTED)
		format(status, maxstatus, FLAME_COLOR"В процессе");
	else
		format(status, maxstatus, GREY_COLOR"Не начат");
	return true;
}

Quest_GetTaskStatus(playerid, task_bit, status[], maxstatus = sizeof status)
{
	if(pData[playerid][pQuestProgress] & task_bit)
		format(status, maxstatus, GREEN_COLOR"Выполнено");
	else
		format(status, maxstatus, GREY_COLOR"Не выполнено");
	return true;
}

Quest_SaveProgress(playerid)
{
	if(pData[playerid][pID] > 0)
		UpdateBaseInt("accounts", "quest_progress", pData[playerid][pQuestProgress], pData[playerid][pID]);
	return true;
}
#include <YSI_Coding\y_hooks>

#define DRIVE_LIC_GAIN_POS -2027.4631,-163.0123,515.4039
#define DRIVE_LIC_GAIN_VW 17
#define DRIVE_LIC_GAIN_INT 3


new DrivingLessonVehicles[4];

static const Float:DRIVING_LESSON_COMPUTERS_POS[][] = 
{
	{-2025.7911,-147.7533,515.4051,270.6594}, // 1
	{-2028.0237,-147.7493,515.4045,270.3228}, // 2
	{-2030.2563,-147.7076,515.4045,268.4195}, // 3
	{-2025.7832,-151.5611,515.4051,274.6861}, // 4
	{-2027.8981,-151.5055,515.4045,271.4716}, // 5
	{-2030.2551,-151.5346,515.4045,270.0906}, // 6
	{-2025.7850,-155.1527,515.4039,276.0438}, // 7
	{-2028.0035,-155.0726,515.4045,270.9027}, // 8
	{-2030.2435,-155.0480,515.4039,270.0903}  // 9
};

static const Float:DRIVING_LESSON_CHECKPOINTS_POS[][] =
{
	{-2081.5898,-134.5941,35.1953}, // Сдача 1
	{-2090.7600,-145.9213,35.1952}, // Сдача 2
	{-2079.1172,-189.6928,35.1952}, // Сдача 3
	{-2079.4321,-209.1080,35.1952}, // Сдача 4
	{-2080.1243,-228.3631,35.1953}, // Сдача 5
	{-2056.2317,-220.5857,35.2004}, // Сдача 6
	{-2046.0618,-177.0057,35.1951}, // Сдача 7
	{-2052.5886,-105.4479,35.1315}, // Сдача 8
	{-2063.3403,-67.6034,35.0469}, // Сдача 9
	{-2152.8901,-68.2418,35.0468}, // Сдача 10
	{-2237.4695,-67.6834,35.0468}, // Сдача 11
	{-2358.3909,-67.9944,35.0389}, // Сдача 12
	{-2374.0256,-163.9484,35.0468}, // Сдача 13
	{-2223.1755,-192.3202,35.0855}, // Сдача 14
	{-2211.4587,-288.0160,35.1952}, // Сдача 15
	{-2011.3680,-294.6051,35.1953}, // Сдача 16
	{-2004.8077,-70.9240,35.0468}, // Сдача 17
	{-2045.2499,-67.1011,35.0468}, // Сдача 18
	{-2023.7938,-95.9468,35.0390} // Сдача 19
};

static const DRIVING_CHECKPOINTS_AMOUNT[] = {19, 19, 19};

static const DRIVING_LESSON_QUESTIONS[][][] =
{
	{"С какой стороны разрешен обгон?", ""FLAME_COLOR"1)"COLOR_WHITE" Разрешён с правой стороны", ""FLAME_COLOR"2)"COLOR_WHITE" Разрешён с левой стороны", ""FLAME_COLOR"3)"COLOR_WHITE" Как с правой, так и с левой стороны", ""FLAME_COLOR"4)"COLOR_WHITE" Обгон запрещен"},
	{"Какие действия следует считать обгоном?", ""FLAME_COLOR"1)"COLOR_WHITE" Опережение ТС с выездом на полосу попутного движения", ""FLAME_COLOR"2)"COLOR_WHITE" Опережение ТС связанное с выездом на обочину", ""FLAME_COLOR"3)"COLOR_WHITE" Опережение ТС с выездом на двойную сплошную", ""FLAME_COLOR"4)"COLOR_WHITE" Опережение ТС с выездом на полосу встречного движения"},
	{"Какие действия запрещены если вас обгоняют?", ""FLAME_COLOR"1)"COLOR_WHITE" Увеличивать скорость", ""FLAME_COLOR"2)"COLOR_WHITE" Подрезать обгоняющего", ""FLAME_COLOR"3)"COLOR_WHITE" Первые два действия", ""FLAME_COLOR"4)"COLOR_WHITE" Нет верного ответа"},
	{"Максимальная скорость в жилой зоне?", ""FLAME_COLOR"1)"COLOR_WHITE" 20 км/ч", ""FLAME_COLOR"2)"COLOR_WHITE" 50 км/ч", ""FLAME_COLOR"3)"COLOR_WHITE" 60 км/ч", ""FLAME_COLOR"4)"COLOR_WHITE" 80 км/ч"},
	{"Максимальная скорость в населенном пункте?", ""FLAME_COLOR"1)"COLOR_WHITE" 70 км/ч", ""FLAME_COLOR"2)"COLOR_WHITE" 80 км/ч", ""FLAME_COLOR"3)"COLOR_WHITE" 60 км/ч", ""FLAME_COLOR"4)"COLOR_WHITE" 120 км/ч"},
	{"Максимальная скорость вне населенного пункта?", ""FLAME_COLOR"1)"COLOR_WHITE" 80 км/ч", ""FLAME_COLOR"2)"COLOR_WHITE" 90 км/ч", ""FLAME_COLOR"3)"COLOR_WHITE" 120 км/ч", ""FLAME_COLOR"4)"COLOR_WHITE" Без ограничений"},
	{"В каких местах разрешена парковка?", ""FLAME_COLOR"1)"COLOR_WHITE" На перекрёстках", ""FLAME_COLOR"2)"COLOR_WHITE" На эстакадах", ""FLAME_COLOR"3)"COLOR_WHITE" На остановочных пунктах автобусов", ""FLAME_COLOR"4)"COLOR_WHITE" На парковке"}
};

static const DRIVING_LESSON_RIGHT_ANSWERS[] = {2, 4, 3, 1, 3, 4, 4};

enum E_DRIVE_DATA
{
	dlType,
	dlStage,
	dlQuestion,
	dlMistake,
	dlCar,
	dlCheckpoint
}
new DriveData[MAX_PLAYERS][E_DRIVE_DATA];

hook OnPlayerConnect(playerid)
{
	DriveData[playerid][dlType] = 0;
	DriveData[playerid][dlStage] = 0;
	DriveData[playerid][dlQuestion] = 0;
	DriveData[playerid][dlMistake] = 0;
	DriveData[playerid][dlCar] = 0;
	DriveData[playerid][dlCheckpoint] = 0;
	return 1;
}

hook OnGameModeInit()
{
	LoadDrivingLicVehicles();
	for(new i = 0; i < sizeof(DRIVING_LESSON_COMPUTERS_POS); i++)
	{
		new string[64];
		format(string, sizeof(string), "Компьютер №%i\nЧтобы занять компьютер нажмите "FLAME_COLOR"ALT", i + 1);
		CreateDynamic3DTextLabel(string, -1, DRIVING_LESSON_COMPUTERS_POS[i][0], DRIVING_LESSON_COMPUTERS_POS[i][1], DRIVING_LESSON_COMPUTERS_POS[i][2], 5.0);
	}

	CreateDynamicPickup(1239, 1, DRIVE_LIC_GAIN_POS, DRIVE_LIC_GAIN_VW, DRIVE_LIC_GAIN_INT);
	CreateDynamic3DTextLabel("Получение лицензий\nНажмите "FLAME_COLOR"ALT"COLOR_WHITE" для взаимодействия", 0xFFFFFFFF, DRIVE_LIC_GAIN_POS, 5.0, _, _, 1, DRIVE_LIC_GAIN_VW, DRIVE_LIC_GAIN_INT);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_WALK && !(oldkeys & KEY_WALK) && !IsPlayerInAnyVehicle(playerid) && IsPlayerInRangeOfPoint(playerid, 2.0, DRIVE_LIC_GAIN_POS) 
		&& GetPlayerVirtualWorld(playerid) == DRIVE_LIC_GAIN_VW && GetPlayerInterior(playerid) == DRIVE_LIC_GAIN_INT)
	{
		if(DriveData[playerid][dlType])
			return SendClientMessage(playerid, COLOR_GREY,!"[ИНФОРМАЦИЯ]: "COLOR_WHITE"Вы уже начали экзамен. Пройдите в компьютерный класс.");
		ShowPlayerDialog(playerid, D_DRIVING_LIC_GAIN, DIALOG_STYLE_LIST, "Получение лицензий", "Категория "FLAME_COLOR"A"COLOR_WHITE" - "GREEN_COLOR"30$"COLOR_WHITE" (Мото транспорт)"COLOR_WHITE"\n\
			Категория "FLAME_COLOR"B"COLOR_WHITE" - "GREEN_COLOR"50$"COLOR_WHITE" (Легковые автомобили и внедорожники)"COLOR_WHITE"\n\
			Категория "FLAME_COLOR"C"COLOR_WHITE" - "GREEN_COLOR"70$"COLOR_WHITE" (Фуры и тягачи)", "Выбрать", "Назад");
	}
	if(newkeys & KEY_WALK && !(oldkeys & KEY_WALK) && !IsPlayerInAnyVehicle(playerid))
		for(new i = 0; i < sizeof(DRIVING_LESSON_COMPUTERS_POS); i++)
			if(IsPlayerInRangeOfPoint(playerid, 2.0, DRIVING_LESSON_COMPUTERS_POS[i][0], DRIVING_LESSON_COMPUTERS_POS[i][1], DRIVING_LESSON_COMPUTERS_POS[i][2]))
			{
				if(DriveData[playerid][dlStage])
					return SendClientMessage(playerid, COLOR_GREY, !"[ИНФОРМАЦИЯ]: "COLOR_WHITE"Вы уже сдали теоретическую часть!");
				if(!DriveData[playerid][dlType])
					return SendClientMessage(playerid, COLOR_GREY,!"[ИНФОРМАЦИЯ]: "COLOR_WHITE"Вы не начали экзамен!");
				ShowPlayerDialog(playerid, D_DRIVING_LIC_RULES, DIALOG_STYLE_MSGBOX, "Правила Дорожного Движения", ""COLOR_WHITE"Общее положение:\n"FLAME_COLOR"1.1"COLOR_WHITE" Движение транспортного средства осуществляется только по правой стороне.\n"FLAME_COLOR"1.2"COLOR_WHITE" Высадка пассажиров со стороны проезжей части не разрешается.\n"FLAME_COLOR"1.3"COLOR_WHITE"Парковать транспорт разрешено только на специальных парковочных местах.\n"FLAME_COLOR"1.4"COLOR_WHITE" При движение транспортного средства с включенным проблесковым маячком необходимо уступить дорогу.\n"FLAME_COLOR"1.5"COLOR_WHITE" Незнание данных правил не освобождает вас от ответственности.\n\nСкорость движения:\n"FLAME_COLOR"2.1"COLOR_WHITE" Максимальная скорость движения в жилой зоне - 20 км/ч.\n"FLAME_COLOR"2.2"COLOR_WHITE" Максимальная скорость движения в населённом пункте - 60 км/ч.\n"FLAME_COLOR"2.3"COLOR_WHITE" Максимальная скорость движения вне населённого пункта - Без ограничений.\n\nОбгон:\n"FLAME_COLOR"3.1"COLOR_WHITE" Обгоном следует считать опережение движущегося ТС с выездом на полосу встречного движения.\n"FLAME_COLOR"3.2"COLOR_WHITE" Обгон транспортного средства разрешается только с левой стороны.\n"FLAME_COLOR"3.3"COLOR_WHITE" Если вас обгоняют, нельзя подрезать обгоняющего и увеличивать скорость.\n", "Далее", "");
			}
	return true;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_DRIVING_LIC_GAIN)
	{
		if(!response)
			return true;
		new price;
		switch(listitem)
		{
			case 0: price = 30;
			case 1: price = 50;
			case 2: price = 70;
		}
		if(pData[playerid][pMoney] < price)
			return SendClientMessage(playerid, COLOR_ERROR,!"[ОШИБКА]: "COLOR_WHITE"У Вас недостаточно денег!");
		UpdatePlayerMoney(playerid, -price);
		ReloadPlayerMoney(playerid);
		DriveData[playerid][dlType] = listitem + 1;
		SendClientMessage(playerid, COLOR_GREY,!"[ИНФОРМАЦИЯ]: "COLOR_WHITE"Для сдачи теоретической части пройдите в компьютерный класс.");
		return true;
	}
	else if(dialogid == D_DRIVING_LIC_RULES)
	{
		DriveData[playerid][dlQuestion] = 0;
		ShowPlayerDrivingLessonQuestion(playerid);
	}
	else if(dialogid == D_DRIVING_LIC_QUESTIONS)
	{
		new question = DriveData[playerid][dlQuestion];
		if(listitem != DRIVING_LESSON_RIGHT_ANSWERS[question] - 1)
		{
			if(DriveData[playerid][dlMistake] >= 2)
			{
				SendClientMessage(playerid, COLOR_ERROR,!"[ОШИБКА]: "COLOR_WHITE"Вы провалили теоретическую часть!");
				DriveData[playerid][dlQuestion] = 0;
				DriveData[playerid][dlType] = 0;
				DriveData[playerid][dlMistake] = 0;
				DriveData[playerid][dlStage] = 0;
				return true;
			}
			DriveData[playerid][dlMistake] = DriveData[playerid][dlMistake] + 1;
			SendClientMessage(playerid, COLOR_GREY,!"[ИНФОРМАЦИЯ]: "COLOR_WHITE"Вы допустили ошибку!");
		}
		if(DriveData[playerid][dlQuestion] >= 6)
		{
			DriveData[playerid][dlQuestion] = 0;
			DriveData[playerid][dlMistake] = 0;
			DriveData[playerid][dlStage] = 1;
			SendClientMessage(playerid, COLOR_GREY,!"[ИНФОРМАЦИЯ]: "COLOR_WHITE"Вы успешно сдали теорию, пройдите на задний двор автошколы для сдачи практической части.");
			return true;
		}
		DriveData[playerid][dlQuestion] = DriveData[playerid][dlQuestion] + 1;
		ShowPlayerDrivingLessonQuestion(playerid);
	}
	return true;
}

ShowPlayerDriveLic(playerid, targetid)
{
    new categories[10];
   	new ms_string[256];
   	new __ms3[] = "SELECT DATE_FORMAT(`issued`, '%%d.%%m.%%Y') as `issued`, DATE_FORMAT(`expired`, '%%d.%%m.%%Y') as `expired`,\
   	`param1`, `param2`, `param3` FROM `documents` WHERE `acc_id` = '%i' and `type` = '2'";
   	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms3, pData[playerid][pID]);
   	mysql_query(ConnectMySQL, ms_string);
   	new cat[3];
   	cat[0] = cache_get_field_content_int(0, "param1");
   	cat[1] = cache_get_field_content_int(0, "param2");
   	cat[2] = cache_get_field_content_int(0, "param3");
   	new issued[32], expired[32];
   	cache_get_field_content(0, "issued", issued);
   	cache_get_field_content(0, "expired", expired);

   	static const CATEGORY_NAMES[][] = {"A", "B", "C"};
   	for(new i = 0; i < sizeof(cat); i++)
   	{
   		if(cat[i])
   		{
   			if(strlen(categories))
   				strcat(categories, ", ");
   			strcat(categories, CATEGORY_NAMES[i]);
   		}
   	}
   	new string[256];
   	format(string, sizeof(string), ""COLOR_WHITE"ID: "FLAME_COLOR"DL%02i\n"COLOR_WHITE"Имя Фамилия: "FLAME_COLOR"%s\n"COLOR_WHITE"Категории: "FLAME_COLOR"%s\n"COLOR_WHITE"Выдано: "FLAME_COLOR"%s\n"COLOR_WHITE"Действительно до "FLAME_COLOR"%s", pData[playerid][pID],
   		pData[playerid][pName], categories, issued, expired);
   	ShowPlayerDialog(targetid, 0, DIALOG_STYLE_MSGBOX, "Водительские права", string, "ОК", "");
    return true;
}

ShowPlayerDrivingLessonQuestion(playerid)
{
	new question = DriveData[playerid][dlQuestion];
	new string[384];
	for(new i = 1; i < 5; i++)
	{
		strcat(string, DRIVING_LESSON_QUESTIONS[question][i]);
		strcat(string, "\n");
	}
	ShowPlayerDialog(playerid, D_DRIVING_LIC_QUESTIONS, DIALOG_STYLE_LIST, DRIVING_LESSON_QUESTIONS[question][0], string, !"Далее", "");
	return true;
}



LoadDrivingLicVehicles()
{ 	// Moto
    DrivingLessonVehicles[0] = AddStaticVehicle(586,-2014.182,-133.361,34.826,42.139,10,10);
    AddStaticVehicle(586,-2013.907,-131.809,34.828,46.709,10,10);
    AddStaticVehicle(586,-2013.577,-130.386,34.823,47.434,10,10);
    AddStaticVehicle(586,-2013.716,-128.883,34.807,54.212,10,10);

    // Cars
	DrivingLessonVehicles[1] = AddStaticVehicle(405,-2045.936,-125.506,35.134,178.895,10,10);
    AddStaticVehicle(405,-2041.680,-125.390,35.119,178.803,10,10);
    AddStaticVehicle(405,-2037.734,-125.485,35.101,179.041,10,10);
    AddStaticVehicle(405,-2033.952,-125.283,35.089,178.140,10,10);
    AddStaticVehicle(405,-2030.160,-125.244,35.092,180.153,10,10);
    AddStaticVehicle(405,-2026.474,-125.203,35.093,179.878,10,10);

    // Heavy
	DrivingLessonVehicles[2] = AddStaticVehicle(403,-2075.028,-108.435,35.933,179.444,10,10);
    AddStaticVehicle(403,-2085.590,-108.144,35.926,179.723,10,10);
    new lastLessonVehicle = AddStaticVehicle(403,-2064.898,-108.356,35.931,178.950,10,10);

	// Upper bound = id right after the last exam vehicle. Don't use
	// GetVehiclePoolSize() here: open.mp marks it broken (returns the whole
	// pool capacity), which made every vehicle fall inside the exam range.
	DrivingLessonVehicles[3] = lastLessonVehicle + 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		new newcar = GetPlayerVehicleID(playerid);
		if(newcar >= DrivingLessonVehicles[0] && newcar < DrivingLessonVehicles[3])
		{
			if(!DriveData[playerid][dlStage])
			{
				RemovePlayerFromVehicle(playerid);
				SendClientMessage(playerid, COLOR_GREY,!"[ИНФОРМАЦИЯ]: "COLOR_WHITE"Вы не начали экзамен!");
				return true;
			}
			new exam = DriveData[playerid][dlType] - 1;
			if(newcar < DrivingLessonVehicles[exam] || newcar >= DrivingLessonVehicles[exam + 1])
			{
				RemovePlayerFromVehicle(playerid);
				SendClientMessage(playerid, COLOR_GREY,!"[ИНФОРМАЦИЯ]: "COLOR_WHITE"Вы начали экзамен не на этом транспорте, пересядьте в другой!");
				return true;
			}

			StartExam(playerid);
		}
	}
	else if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER && DriveData[playerid][dlStage] && DriveData[playerid][dlCar])
	{
		SendClientMessage(playerid, COLOR_ERROR,!"[ОШИБКА]: "COLOR_WHITE"Вы покинули автомобиль до конца практической части. Экзамен завершён!");
		StopPlayerDriverLicExam(playerid);
	}
	return true;
}

StartExam(playerid)
{
	DriveData[playerid][dlCheckpoint] = 0;
	DriveData[playerid][dlCar] = GetPlayerVehicleID(playerid);
	DrivingExam(playerid);
	return true;
}

StopPlayerDriverLicExam(playerid)
{
	if(DriveData[playerid][dlCar])
		SetVehicleToRespawn(DriveData[playerid][dlCar]);
	DriveData[playerid][dlType] = 0;
	DriveData[playerid][dlMistake] = 0;
	DriveData[playerid][dlStage] = 0;
	DriveData[playerid][dlQuestion] = 0;
	DriveData[playerid][dlCar] = 0;
	DriveData[playerid][dlCheckpoint] = 0;
	DisablePlayerRaceCheckpoint(playerid);
	return true;
}

DrivingExam(playerid)
{
	DriveData[playerid][dlCheckpoint] = DriveData[playerid][dlCheckpoint] + 1;
	new exam = DriveData[playerid][dlCheckpoint] - 1;
	if(exam >= DRIVING_CHECKPOINTS_AMOUNT[DriveData[playerid][dlType]-1])
	{
		new Float:health;
		GetVehicleHealth(GetPlayerVehicleID(playerid),health);
		if(health <= 700)
		{
			SendClientMessage(playerid, COLOR_ERROR,!"[ОШИБКА]: "COLOR_WHITE"Экзамен провален, вы сильно повредили транспорт!");
			StopPlayerDriverLicExam(playerid);
			return true;
		}
		// окончание экзамена
		new category[2];
		switch(DriveData[playerid][dlType])
		{
			case 1: category = "A";
			case 2: category = "B";
			case 3: category = "C";
		}
		SendClientMessageEx(playerid, COLOR_GREY, "[ИНФОРМАЦИЯ]: "COLOR_WHITE"Поздравляем, вы успешно сдали экзамен на вождение категории "FLAME_COLOR"%s"COLOR_WHITE".", category);
		AddPlayerDrivingLicense(playerid, DriveData[playerid][dlType]);
		StopPlayerDriverLicExam(playerid);
		return true;
	}
	if(exam >= DRIVING_CHECKPOINTS_AMOUNT[DriveData[playerid][dlType]-1] - 1)
		SetPlayerRaceCheckpoint(playerid, 1, DRIVING_LESSON_CHECKPOINTS_POS[exam][0], DRIVING_LESSON_CHECKPOINTS_POS[exam][1], DRIVING_LESSON_CHECKPOINTS_POS[exam][2],
			0.0, 0.0, 0.0, 5.0);
	else
		SetPlayerRaceCheckpoint(playerid, 0, DRIVING_LESSON_CHECKPOINTS_POS[exam][0], DRIVING_LESSON_CHECKPOINTS_POS[exam][1], DRIVING_LESSON_CHECKPOINTS_POS[exam][2],
			DRIVING_LESSON_CHECKPOINTS_POS[exam+1][0], DRIVING_LESSON_CHECKPOINTS_POS[exam+1][1], DRIVING_LESSON_CHECKPOINTS_POS[exam+1][2], 5.0);
	return true;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	if(DriveData[playerid][dlType])
		return DrivingExam(playerid);
	return true;
}

AddPlayerDrivingLicense(playerid, cat)
{
	for(new i = 0; i < 10; i++)
		if(PlayerInventory[playerid][i][invID] == 1 && PlayerInventory[playerid][i][invParam] == 2)
			ClearPlayerInventorySlot(playerid, i, true);

	if(AddItemInInventory(playerid, 1, 2, 1) == -1)
		return SendClientMessage(playerid, COLOR_ERROR,!"[ОШИБКА]: "COLOR_WHITE"Инвентарь заполнен!");
	SaveInventory(playerid);
	new ms_string[128];
	new __ms2[] = "SELECT * FROM `documents` WHERE `acc_id` = '%i' and `type` = '2'";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms2, pData[playerid][pID]);
	mysql_query(ConnectMySQL, ms_string);
	if(cache_get_row_count())
	{
		new __ms1[] = "UPDATE `documents` SET `param%i` = '1' WHERE `acc_id` = '%i' and `type` = '2'";
		mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms1, cat, pData[playerid][pID]);
		mysql_tquery(ConnectMySQL, ms_string);
		if(cat == 2) Quest_OnPlayerGetDriveLicB(playerid);
		return true;
	}
	else
	{
		new __ms0[] = "INSERT INTO `documents` (`acc_id`, `type`, `param%i`, `expired`) VALUES ('%i', '2', '1', DATE_ADD(NOW(), INTERVAL 3 MONTH))";
		mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms0, cat, pData[playerid][pID]);
		mysql_tquery(ConnectMySQL, ms_string);
	}
	if(cat == 2) Quest_OnPlayerGetDriveLicB(playerid);
	return true;
}

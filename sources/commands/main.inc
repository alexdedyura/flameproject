#include <YSI_Coding\y_hooks>

#define WALK_DEFAULT    0
#define WALK_NORMAL     1
#define WALK_PED        2
#define WALK_GANGSTA    3
#define WALK_GANGSTA2   4
#define WALK_OLD        5
#define WALK_FAT_OLD    6
#define WALK_FAT        7
#define WALK_LADY       8
#define WALK_LADY2      9
#define WALK_WHORE      10
#define WALK_WHORE2     11
#define WALK_DRUNK      12
#define WALK_BLIND      13
new WalkStyle[MAX_PLAYERS];
new walktime[MAX_PLAYERS];
static const WalkAnimationNames[WALK_BLIND + 1][] =
{
	"",
	"WALK_player",
	"WALK_civi",
	"WALK_gang1",
	"WALK_gang2",
	"WALK_old",
	"WALK_fatold",
	"WALK_fat",
	"WOMAN_walknorm",
	"WOMAN_walkbusy",
	"WOMAN_walkpro",
	"WOMAN_walksexy",
	"WALK_drunk",
	"Walk_Wuzi"
};

CMD:help(playerid, params[])
{
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]: "COLOR_WHITE"/help [1-6] (1 - Автомобили | 2 - Чат | 3 - Прочее | 4 - Маппинг | 5 - CopChase | 6 - Актёры)");
	if(params[0] < 0 || params[0] > 6) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]: "COLOR_WHITE"/help [1-6] (1 - Автомобили | 2 - Чат | 3 - Прочее | 4 - Маппинг | 5 - CopChase | 6 - Актёры)");
	new string[2200];
	switch(params[0])
	{
		case 1:
		{
			strcat(string, ""COLOR_WHITE"Автомобили:\n");
			strcat(string, ""FLAME_COLOR"/veh"COLOR_WHITE"\t\t- создаёт автомобиль в Вашем мире.\n");
			strcat(string, ""FLAME_COLOR"/pveh"COLOR_WHITE"\t\t- создаёт автомобиль с сиреной в Вашем мире.\n");
			strcat(string, ""FLAME_COLOR"/delveh"COLOR_WHITE"\t\t- удаляет автомобиль.\n");
			strcat(string, ""FLAME_COLOR"/(en)gine"COLOR_WHITE"\t- заводит/глушит двигатель автомобиля в котором Вы находитесь.\n");
			strcat(string, ""FLAME_COLOR"/(li)ghts"COLOR_WHITE"\t\t- включает/выключает фары автомобиля в котором Вы нахоидтесь.\n");
			strcat(string, ""FLAME_COLOR"/bonnet"COLOR_WHITE"\t- открывает/закрывает капот автомобиля в котором Вы находитесь.\n");
			strcat(string, ""FLAME_COLOR"/boot"COLOR_WHITE"\t\t- открывает/закрывает багажник автомобиляв в котором Вы находитесь.\n");
			strcat(string, ""FLAME_COLOR"/fix"COLOR_WHITE"\t\t- чинит автомобиль в котором Вы находитесь.\n");
			strcat(string, ""FLAME_COLOR"/callsign"COLOR_WHITE"\t- устанавливает/удаляет маркировку на автомобиль(-е).\n");
			strcat(string, ""FLAME_COLOR"/nitro"COLOR_WHITE"\t\t- нитро режим.\n");
			strcat(string, ""FLAME_COLOR"/car"COLOR_WHITE"\t\t- выбор одного из процессуальных автомобилей PD/SD/DOC.\n");
			strcat(string, ""FLAME_COLOR"/carcolor"COLOR_WHITE"\t- перекрасить авто.\n");
			strcat(string, ""FLAME_COLOR"/gmcar"COLOR_WHITE"\t\t- автопочинка авто.\n");
			strcat(string, ""FLAME_COLOR"/flipcar"COLOR_WHITE"\t\t- перевернуть авто.\n");
			strcat(string, ""FLAME_COLOR"/paintjob"COLOR_WHITE"\t- покрасочные работы для авто.");
		}
		case 2:
		{
			strcat(string, ""COLOR_WHITE"Чат:\n");
			strcat(string, ""FLAME_COLOR"/me"COLOR_WHITE"\t\t- отыгровки от первого лица.\n");
			strcat(string, ""FLAME_COLOR"/do"COLOR_WHITE"\t\t- отыгровки от третьего лица.\n");
			strcat(string, ""FLAME_COLOR"/ame"COLOR_WHITE"\t\t- отыгровка коротких действий.\n");
			strcat(string, ""FLAME_COLOR"/pm"COLOR_WHITE"\t\t- приватное сообщение игроку.\n");
			strcat(string, ""FLAME_COLOR"/m"COLOR_WHITE"\t\t- мегафон.\n");
			strcat(string, ""FLAME_COLOR"/r"COLOR_WHITE"\t\t- рация.\n");
			strcat(string, ""FLAME_COLOR"/channel"COLOR_WHITE"\t- выбрать радиоканал.\n");
			strcat(string, ""FLAME_COLOR"/mute"COLOR_WHITE"\t\t- отключение чатов.\n");
			strcat(string, ""FLAME_COLOR"/b"COLOR_WHITE"\t\t- OOC чат.\n");
			strcat(string, ""FLAME_COLOR"/l(ow)"COLOR_WHITE"\t\t- говорить тихо.\n");
			strcat(string, ""FLAME_COLOR"/w(hisper)"COLOR_WHITE"\t- шептать определённому игроку.\n");
			strcat(string, ""FLAME_COLOR"/s(hout)"COLOR_WHITE"\t\t- кричать.");
		}
		case 3:
		{
			strcat(string, ""COLOR_WHITE"Прочие команды:\n");
			strcat(string, ""FLAME_COLOR"/rules"COLOR_WHITE"\t\t\t- правила сервера.\n");
			strcat(string, ""FLAME_COLOR"/stats"COLOR_WHITE"\t\t\t- статистика.\n");
			strcat(string, ""FLAME_COLOR"/world"COLOR_WHITE"\t\t\t- изменяет Ваш виртуальный мир.\n");
			strcat(string, ""FLAME_COLOR"/time"COLOR_WHITE"\t\t\t- меняет время индивидуально для Вас.\n");
			strcat(string, ""FLAME_COLOR"/tp"COLOR_WHITE"\t\t\t- телепортирует Вас к игроку.\n");
			strcat(string, ""FLAME_COLOR"/weapon & /gun"COLOR_WHITE"\t- выдаёт Вам требуемое оружие.\n");
			strcat(string, ""FLAME_COLOR"/s(kin)"COLOR_WHITE"\t\t\t- изменяет Ваш скин на нужный Вам самим.\n");
			strcat(string, ""FLAME_COLOR"/health"COLOR_WHITE"\t\t\t- восстанавливает Ваши ХП до отметки в 100 единиц.\n");
			strcat(string, ""FLAME_COLOR"/armour"COLOR_WHITE"\t\t- восстанавливает Вашу броню до отметки в 100 единиц.\n");
			strcat(string, ""FLAME_COLOR"/nameoff"COLOR_WHITE"\t\t- отключить отображение ников.\n");
			strcat(string, ""FLAME_COLOR"/nameon"COLOR_WHITE"\t\t- включить отображение ников.\n");
			strcat(string, ""FLAME_COLOR"/spawnme"COLOR_WHITE"\t\t- перевозродить игрока(отправляет на точку спавна).\n");
			strcat(string, ""FLAME_COLOR"/op"COLOR_WHITE"\t\t\t- различные спец. операции(захват).\n");
			strcat(string, ""FLAME_COLOR"/uniform"COLOR_WHITE"\t\t- выбор одного из процессуальных скинов PD/SD/DOC.\n");
			strcat(string, ""FLAME_COLOR"/attach"COLOR_WHITE"\t\t\t- прикрепление различных предметов к телу персонажа.\n");
			strcat(string, ""FLAME_COLOR"/gm"COLOR_WHITE"\t\t\t- включение/отключение режима бога.\n");
			strcat(string, ""FLAME_COLOR"/animlist"COLOR_WHITE"\t\t- список анимаций.\n");
			strcat(string, ""FLAME_COLOR"/taser"COLOR_WHITE"\t\t\t- достать тайзер.\n");
			strcat(string, ""FLAME_COLOR"/vw"COLOR_WHITE"\t\t\t- меню модерации виртуального мира.\n");
			strcat(string, ""FLAME_COLOR"/vkick"COLOR_WHITE"\t\t\t- выкинуть игрока из виртуального мира.\n");
			strcat(string, ""FLAME_COLOR"/slapme"COLOR_WHITE"\t\t- команда может пригодиться, если Вы застряли в текстурах.\n");
			strcat(string, ""FLAME_COLOR"/style"COLOR_WHITE"\t\t\t- поменять стиль боя.\n");
			strcat(string, ""FLAME_COLOR"/money"COLOR_WHITE"\t\t\t- выдача себе денег.\n");
			strcat(string, ""FLAME_COLOR"/skill"COLOR_WHITE"\t\t\t- установка уровня скилла на оружие.\n");
			strcat(string, ""FLAME_COLOR"/invite"COLOR_WHITE"\t\t\t- пригласить игрока в виртуальный мир.\n");
			strcat(string, ""FLAME_COLOR"/id"COLOR_WHITE"\t\t\t- поиск игрока по части ника или id.\n");
			strcat(string, ""FLAME_COLOR"/swalk"COLOR_WHITE"\t\t\t- стиль походки персонажа.\n");
			strcat(string, ""FLAME_COLOR"/rpdeath"COLOR_WHITE"\t\t- режим смерти как на РП серверах.\n");
			strcat(string, ""FLAME_COLOR"/rw"COLOR_WHITE"\t\t\t- обнулить оружие.\n");
			strcat(string, ""FLAME_COLOR"/rm"COLOR_WHITE"\t\t\t- обнулить деньги.\n");
			strcat(string, ""FLAME_COLOR"/xyz"COLOR_WHITE"\t\t\t- телепорт по координатам.\n");
			strcat(string, ""FLAME_COLOR"/admins"COLOR_WHITE"\t\t- вывести список админов.\n");
			strcat(string, ""FLAME_COLOR"/newpass"COLOR_WHITE"\t\t- изменить пароль.\n");
			strcat(string, ""FLAME_COLOR"/givegun"COLOR_WHITE"\t\t- выдать оружие.");
		}
		case 4:
		{
			strcat(string, ""COLOR_WHITE"Маппинг:\n");
			strcat(string, ""FLAME_COLOR"/oadd\t\t"COLOR_WHITE"- создаёт объект\n");
			strcat(string, ""FLAME_COLOR"/odell\t\t"COLOR_WHITE"- удаляет объект по уникальному ID.\n");
			strcat(string, ""FLAME_COLOR"/oedit\t\t"COLOR_WHITE"- включает режим редактирования объектов, просто кликните по объекту, либо введите его ID.\n");
			strcat(string, ""FLAME_COLOR"/cone\t\t"COLOR_WHITE"- быстрая установка конусов\n\n");
			strcat(string, ""FLAME_COLOR"/rb\t\t"COLOR_WHITE"- быстрая установка ограждений "FLAME_COLOR"/rb <1-6>");
		}
		case 5:
		{
			strcat(string, ""COLOR_WHITE"CopChase:\n");
			strcat(string, "Границы города ограничены, поэтому не советую выезжать за пределы Los Santos.\n\n");
			strcat(string, ""FLAME_COLOR"/copchase"COLOR_WHITE"\t- участие в мини-игре.\n");
			strcat(string, ""FLAME_COLOR"/r"COLOR_WHITE"\t\t- использовать рацию внутри игры.\n");
			strcat(string, ""FLAME_COLOR"/exit"COLOR_WHITE"\t\t- выйти из игры.\n");
			strcat(string, ""FLAME_COLOR"/report"COLOR_WHITE"\t\t- запрос на кик человека из copchase.\n");
			strcat(string, "Клавиша "FLAME_COLOR"Y"COLOR_WHITE"\t- включает маячок LSPD.\n\n");
			strcat(string, "Суть игры похожа чем-то на салочки. Цель преступника убежать, цель полиции поймать.\n");
			strcat(string, "Исходы игры бывают следующими:\n");
			strcat(string, "1. Suspect нейтрализован, побеждает LSPD.\n");
			strcat(string, "2. Suspect остаётся последним в игре, побеждает Suspect.\n");
			strcat(string, "3. Suspect выживает на протяжении 10 минут, побеждает Suspect.\n");
			strcat(string, "4. Suspect выходит в AFK либо теряет соединение, побеждает LSPD.");
		}
		case 6:
		{
			strcat(string, ""COLOR_WHITE"Актёры:\n");
			strcat(string, ""FLAME_COLOR"/actor"COLOR_WHITE"\t\t- создаёт актёра.\n");
			strcat(string, ""FLAME_COLOR"/actor <id>"COLOR_WHITE"\t- открыть меню созданного актёра.\n");
			strcat(string, "ПКМ - Правая кнопка мыши.\n");
			strcat(string, "Выделить актёра - зажав ПКМ навести курсор на актёра до появления зелёного треугольника над головой цели.\n");
			strcat(string, "Для взаимодействия с актёром выделите актёра, зажав ПКМ и нажмите пробел. Либо напишите /actor <id>\n");
			strcat(string, "Для воспроизведения дополнительной анимации актёра выделите актёра ПКМ и нажмите левый ALT.\n");
			strcat(string, "Если актёра убили, сбейте ему анимацию, либо выберите новую основную анимацию для того, чтобы его поднять.\n");
		}
	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, !"Помощь", string, !"Закрыть", !"");
	return true;
}

static const VehicleNamesIDs[212][] =
{
    "400 - Landstalker",   "401 - Bravura",   "402 - Buffalo",   "403 - Linerunner",   "404 - Pereniel",   "405 - Sentinel",   "406 - Dumper",   "407 - Firetruck",   "408 - Trashmaster",   "409 - Stretch",
    "410 - Manana",   "411 - Infernus",   "412 - Voodoo",   "413 - Pony",   "414 - Mule",   "415 - Cheetah",   "416 - Ambulance",   "417 - Leviathan",   "418 - Moonbeam",   "419 - Esperanto",   "420 - Taxi",
    "421 - Washington",   "422 - Bobcat",   "423 - Mr Whoopee",   "424 - BF Injection",   "425 - Hunter",   "426 - Premier",   "427 - Enforcer",   "428 - Securicar",   "429 - Banshee",   "430 - Predator",
    "431 - Bus",   "432 - Rhino",   "433 - Barracks",   "434 - Hotknife",   "435 - Trailer",   "436 - Previon",   "437 - Coach",   "438 - Cabbie",   "439 - Stallion",   "440 - Rumpo",   "441 - RC Bandit",    "442 - Romero",
    "443 - Packer",   "444 - Monster",   "445- Admiral",   "446 - Squalo",   "447 - Seasparrow",   "448 - Pizzaboy",   "449 - Tram",   "450 - Trailer",   "451 - Turismo",   "452 - Speeder",   "453 - Reefer",   "454 - Tropic",   "455 - Flatbed",
    "456 - Yankee",   "457 - Caddy",   "458 - Solair",   "459 - Berkley's RC Van",   "460 - Skimmer",   "461 - PCJ-600",   "462 - Faggio",   "463 - Freeway",   "464 - RC Baron",   "465 - RC Raider",
    "466 - Glendale",   "467 - Oceanic",   "468 - Sanchez",   "469 - Sparrow",   "470 - Patriot",   "471 - Quad",   "472 - Coastguard",   "473 - Dinghy",   "474 - Hermes",   "475 - Sabre",   "476 - Rustler",
    "477 - ZR350",   "478 - Walton",   "479 - Regina",   "480 - Comet",   "481 - BMX",   "482 - Burrito",   "483 - Camper",   "484 - Marquis",   "485 - Baggage",   "486 - Dozer",   "487 - Maverick",   "488 - News Chopper",
    "489 - Rancher",   "490 - FBI Rancher",   "491 - Virgo",   "492 - Greenwood",   "493 - Jetmax",   "494 - Hotring",   "495 - Sandking",   "496 - Blista Compact",   "497 - Police Maverick",
    "498 - Boxville",   "499 - Benson",   "500 - Mesa",   "501 - RC Goblin",   "502 - Hotring Racer",   "503 - Hotring Racer",   "504 - Bloodring Banger",   "505 - Rancher",   "506 - Super GT",
    "507 - Elegant",   "508 - Journey",   "509 - Bike",   "510 - Mountain Bike",   "511 - Beagle",   "512 - Cropdust",   "513 - Stunt",   "514 - Tanker",   "515 - RoadTrain",   "516 - Nebula",   "517 - Majestic",
    "518 - Buccaneer",   "519 - Shamal",   "520 - Hydra",   "521 - FCR-900",   "522 - NRG-500",   "523 - HPV1000",   "524 - Cement Truck",   "525 - Tow Truck",   "526 - Fortune",   "527 - Cadrona",   "528 - FBI Truck",
    "529 - Willard",   "530 - Forklift",   "531 - Tractor",   "532 - Combine",   "533 - Feltzer",   "534 - Remington",   "535 - Slamvan",   "536 - Blade",   "537 - Freight",   "538 - Streak",   "539 - Vortex",   "540 - Vincent",
    "541 - Bullet",   "542 - Clover",   "543 - Sadler",   "544 - Firetruck",   "545 - Hustler",   "546 - Intruder",   "547 - Primo",   "548 - Cargobob",   "549 - Tampa",   "550 - Sunrise",   "551 - Merit",   "552 - Utility",
    "553 - Nevada",   "554 - Yosemite",   "555 - Windsor",   "556 - Monster",   "557 - Monster",   "558 - Uranus",   "559 - Jester",   "560 - Sultan",   "561 - Stratum",   "562 - Elegy",   "563 - Raindance",   "564 - RC Tiger",
    "565 - Flash",   "566 - Tahoma",   "567 - Savanna",   "568 - Bandito",   "569 - Freight",   "570 - Trailer",   "571 - Kart",   "572 - Mower",   "573 - Duneride",   "574 - Sweeper",   "575 - Broadway",
    "576 - Tornado",   "577 - AT-400",   "578 - DFT-30",   "579 - Huntley",   "580 - Stafford",   "581 - BF-400",   "582 - Newsvan",   "583 - Tug",   "584 - Trailer",   "585 - Emperor",   "586 - Wayfarer",
    "587 - Euros",   "588 - Hotdog",   "589 - Club",   "590 - Trailer",   "591 - Trailer",   "592 - Andromada",   "593 - Dodo",   "594 - RC Cam",   "595 - Launch",   "596 - Police Car (LSPD)",   "597 - Police Car (SFPD)",
    "598 - Police Car (LVPD)",   "599 - Police Ranger",   "600 - Picador",   "601 - S.W.A.T. Van",   "602 - Alpha",   "603 - Phoenix",   "604 - Glendale",   "605 - Sadler",   "606 - Luggage Trailer A",
    "607 - Luggage Trailer B",   "608 - Stair Trailer",   "609 - Boxville",   "610 - Farm Plow",   "611 - Utility Trailer"
};

static const vehicles_ids [16][] =
{
	{562, 565, 559, 561, 560, 558},
	{429, 541, 415, 480, 434, 494, 502, 503, 411, 506, 451, 555, 477, 0},
	{536, 575, 534, 567, 535, 576, 412, 0},
	{602, 496, 401, 518, 527, 589, 419, 587, 533, 526, 474, 545, 517, 410, 600, 436, 439, 549, 491, 0},
	{445, 507, 585, 466, 492, 546, 551, 516, 467, 426, 547, 405, 580, 409, 550, 566, 540, 421, 529, 0},
	{579, 400, 404, 489, 479, 442, 458, 0},
	{402, 542, 603, 475, 0},
	{499, 498, 609, 524, 532, 578, 486, 406, 573, 455, 588, 403, 423, 414, 443, 515, 514, 531, 456, 0},
	{459, 422, 482, 530, 418, 572, 582, 413, 440, 543, 583, 478, 554, 0},
	{568, 424, 504, 457, 483, 508, 571, 500, 556, 557, 471, 495, 539, 0},
	{481, 509, 510, 581, 462, 521, 463, 522, 461, 448, 468, 586, 0},
	{485, 431, 438, 437, 574, 420, 525, 408, 552, 0},
	{416, 433, 427, 490, 528, 407, 544, 523, 470, 596, 597, 598, 599, 432, 428, 601, 0},
	{592, 511, 548, 512, 593, 425, 417, 487, 553, 488, 497, 563, 476, 447, 519, 460, 569, 513, 520, 0},
	{472, 493, 595, 484, 430, 453, 452, 446, 454, 0},
	{604, 605, 0}
};

CMD:veh(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_GREY, !"* Невозможно в транспорте!");
	new vehtext[32], color1 = -1, color2 = -1;
	sscanf(params,"s[32]ii", vehtext, color1, color2);
	new vehid;
	for(new i; i < 212; i++)
	{
		if(strfind(VehicleNamesIDs[i],vehtext, true) != -1)
		{
			vehid = i+400;
			break;
		}
	}
	if(!vehid) return ShowVehiclesDialog(playerid, 0);
	if(color1 == -1) color1 = random(128);
	if(color2 == -1) color2 = random(128);
	new Float:vehX, Float:vehY, Float:vehZ, Float:rot;
	GetPlayerPos(playerid, vehX, vehY, vehZ);
	GetPlayerFacingAngle(playerid, rot);
	vehid = CreateVehicle(vehid, vehX, vehY, vehZ, rot, color1, color2, -1);
	SetVehicleVirtualWorld(vehid, GetPlayerVirtualWorld(playerid));
	VehicleInfo[vehid][vType] = VEHICLE_TYPE_NONE; // Временный транспорт
	PutPlayerInVehicle(playerid, vehid, 0);

	VehicleInfo[vehid][vFuel] = 60.0;
	UpdateVehicleParamsEx(vehid);
	return true;
}

CMD:pveh(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_GREY, !"* Невозможно в транспорте!");
	new vehtext[32], color1 = -1, color2 = -1;
	sscanf(params,"s[32]ii", vehtext, color1, color2);
	new vehid;
	for(new i; i < 212; i++)
	{
		if(strfind(VehicleNamesIDs[i],vehtext, true) != -1)
		{
			vehid = i+400;
			break;
		}
	}
	if(!vehid) return ShowVehiclesDialog(playerid, 1);
	if(color1 == -1) color1 = random(128);
	if(color2 == -1) color2 = random(128);
	new Float:vehX, Float:vehY, Float:vehZ, Float:rot;
	GetPlayerPos(playerid, vehX, vehY, vehZ);
	GetPlayerFacingAngle(playerid, rot);
	vehid = CreateVehicle(vehid, vehX, vehY, vehZ, rot, color1, color2, 1);
	SetVehicleVirtualWorld(vehid, GetPlayerVirtualWorld(playerid));
	PutPlayerInVehicle(playerid, vehid, 0);
	return true;
}

ShowVehiclesDialog(playerid, siren = 0)
{
	SetPVarInt(playerid, !"VehSiren", siren);
	ShowPlayerDialog(playerid, D_VEHICLES, DIALOG_STYLE_LIST, !"Тип транспорта", !"\
		Стритрейсерские авто\nГоночные авто\nЛоурайдеры\nДвухдневные седаны\nЧетырёхдневные седаны\nДжипы\nМощные авто\nГрузовики и рабочий транспорт\nЛёгкие грузовики и фургоны\nТранспорт для развлечения\n\
		Велосипеды и мотоциклы\nАвто для транспортировки\nКоммерческий и государственный транспорт\nВоздушный транспорт\nВодный транспорта\nРадиоуправляемые и побитые авто", !"Далее", !"Отмена");
	return true;
}


hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_VEHICLES)
	{
		if(!response) return DeletePVar(playerid, !"VehSiren");
		SetPVarInt(playerid, !"VehType", listitem);
		new string[1024];
		new i = 0;
		while(vehicles_ids[listitem][i] != 0)
		{
			format(string, sizeof(string), "%s%i\t%s\n", string, vehicles_ids[listitem][i], VehicleNamesIDs[vehicles_ids[listitem][i]-400]);
			i++;
		}
		ShowPlayerDialog(playerid, D_VEHICLES_PREVIEW, DIALOG_STYLE_TABLIST, !"Vehicles list", string, !"SELECT", !"CANCEL");
	}
	else if(dialogid == D_VEHICLES_PREVIEW)
	{
		if(!response)
		{
			DeletePVar(playerid, !"VehType");
			DeletePVar(playerid, !"VehSiren");
			return true;
		}

		new str[6];
		valstr(str, vehicles_ids[GetPVarInt(playerid, !"VehType")][listitem]);
		return cmd_veh(playerid, str);
	}
	else if(dialogid == D_SPECIAL_VEHICLES)
	{
		if(!response) return true;
		static const vehicleids[21] = {596, 597, 598, 599, 427, 497, 596, 597, 598, 599, 427, 497, 523, 426, 560, 490, 415, 541, 428, 601, 528};
		new Float:vehX, Float:vehY, Float:vehZ;
		GetPlayerPos(playerid, vehX, vehY, vehZ);
		new color1, color2;
		if(listitem < 5) color1 = 0, color2 = 1;
		else if(listitem < 11) color1 = 16, color2 = 1;
		new vehid = CreateVehicle(vehicleids[listitem], vehX, vehY, vehZ, 0.0, color1, color2, 0, true);
		SetVehicleVirtualWorld(vehid, GetPlayerVirtualWorld(playerid));
		PutPlayerInVehicle(playerid, vehid, 0);
	}
	else if(dialogid == D_SPECIAL_SKINS)
	{
		if(!response) return true;
		new skinid;
		switch(listitem)
		{
			case 0: skinid = 265;
			case 1: skinid = 266;
			case 2: skinid = 267;
			case 3: skinid = 280;
			case 4: skinid = 281;
			case 5: skinid = 284;
			case 6: skinid = 300;
			case 7: skinid = 301;
			case 8: skinid = 306;
			case 9: skinid = 307;
			case 10: skinid = 282;
			case 11: skinid = 283;
			case 12: skinid = 288;
			case 13: skinid = 302;
			case 14: skinid = 310;
			case 15: skinid = 311;
			case 16: skinid = 309;
		}
		SetPlayerSkin(playerid, skinid);
		SetPlayerHealth(playerid, 1000.0);
		SetPlayerArmour(playerid, 1000.0);
		GivePlayerWeapon(playerid, 24, 21);
		GivePlayerWeapon(playerid, 3, 1);
	}
	else if(dialogid == D_MAINMENU)
	{
		if(!response) return true;
		switch(listitem)
		{
			case 0: // Инвентарь
			{
				ShowPlayerInventory(playerid);
			}
			case 1: // iPhone 12
			{
				return cmd_phone(playerid);
			}
			case 2: // Статистика
			{
				new p[] = ""; return cmd_stats(playerid, p);
			}
			case 3: // Связь с администрацией
			{
				return cmd_report(playerid);
			}
			case 4: // Команды сервера
			{
				new p[] = ""; return cmd_help(playerid, p);
			}
			case 5: // Мои настройки
			{
				ShowPlayerSettings(playerid);
			}
			case 6: // Квесты
			{
				ShowPlayerQuests(playerid);
			}
			case 7: // Донат
			{
				return cmd_donate(playerid);
			}
		}
	}
	else if(dialogid == D_SETTINGS)
	{
		if(!response) return true;
		switch(listitem)
		{
			case 0: // Ники игроков
			{
				if(GetPVarInt(playerid, !"HideNames")) return cmd_nameoff(playerid);
				else return cmd_nameon(playerid);
			}
			case 1: // Неуязвимость
			{
				return cmd_gm(playerid);
			}
			case 2: // РП смерть
			{
				new p[] = ""; return cmd_rpdeath(playerid, p);
			}
			case 3: // Приглашения в мир
			{
				if(GetPVarInt(playerid, !"WorldInvites")) DeletePVar(playerid, !"WorldInvites");
				else SetPVarInt(playerid, !"WorldInvites", 1);
			}
			case 4: // Заморозка после спавна
			{
				ShowPlayerDialog(playerid, D_SETTINGS_FREEZE, DIALOG_STYLE_INPUT, !"Заморозка при спавне", !""COLOR_WHITE"Введите желаемое количество миллисекунд задержки при спавне.\n1000 миллисекунд = 1 секунда\nЗначения от 0 до 5000!", !"Далее", !"Отмена");
				return true;
			}
			case 5: // Звук попадания из оружия
			{
				if(GetPVarInt(playerid, !"ShootSounds")) DeletePVar(playerid, !"ShootSounds");
				else SetPVarInt(playerid, !"ShootSounds", 1);
			}
			case 6: // Стиль боя
			{
				ShowPlayerDialog(playerid, D_SETTINGS_FIGHT, DIALOG_STYLE_LIST, !"Выбор стиля боя", !"Стандартный\nБокс\nКунг Фу\nКолено\nЗахват\nУдар локтём", !"Далее", !"Отменить");
				return true;
			}
			case 7: // Стиль походки
			{
				ShowPlayerDialog(playerid, 33, DIALOG_STYLE_LIST, "Стили походки","Обычная\nГражданская\nГангстерская 1\nГангстерская 2\nСтарика\nСтарухи\nЖенская 1\nЖенская 2\nЖенская 3\nШлюхи 1\nШлюхи 2\nПьяного", "Выбрать", "Отмена");
				return true;
			}
			case 8: // Скиллы оружия
			{
				new p[] = ""; return cmd_skill(playerid, p);
			}
			case 9: // Настройки чата
			{
				//return cmd_mute(playerid, "");
			}
			case 10: // Управление аттачами
			{
				return true;
			}
			case 11: // Стиль чата
			{
				ShowPlayerDialog(playerid, D_SETTINGS_CHAT, DIALOG_STYLE_LIST, !"Стиль разговора", !"1. Отсутствует\n2. По умолчанию\n3. Недоверие\n4. Открытость\n5. Неодобрение\n6. Настойчивость\n7. Позитивность\n8. Неуверенность", !"Далее", !"Отмена");
				return true;
			}
		}
		ShowPlayerSettings(playerid);
	}
	else if(dialogid == D_SETTINGS_FREEZE)
	{
		if(!response) return ShowPlayerSettings(playerid);
		if(strval(inputtext) < 0 || strval(inputtext) > 5000)
		{
			ShowPlayerDialog(playerid, D_SETTINGS_FREEZE, DIALOG_STYLE_INPUT, !"Заморозка при спавне", !""COLOR_WHITE"Введите желаемое количество миллисекунд задержки при спавне.\n1000 миллисекунд = 1 секунда\nЗначения от 0 до 5000!", !"Далее", !"Отмена");
			return true;
		}
		SetPVarInt(playerid, !"SpawnDelay", strval(inputtext));
		ShowPlayerSettings(playerid);
	}
	else if(dialogid == D_SETTINGS_FIGHT)
	{
		new params[3];
		valstr(params, listitem);
		if(response) return cmd_style(playerid, params);
		ShowPlayerSettings(playerid);
	}
	else if(dialogid == 33)
    {
	    if(response)
	    {
	    	if(listitem == 0)
            {
                    SetPlayerWalkingStyle (playerid, WALK_NORMAL);
                    SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 1)
            {
                    SetPlayerWalkingStyle (playerid, WALK_PED);
                    SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 2)
            {
                SetPlayerWalkingStyle (playerid, WALK_GANGSTA);
                SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 3)
            {
                    SetPlayerWalkingStyle (playerid, WALK_GANGSTA2);
                    SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 4)
            {
                SetPlayerWalkingStyle (playerid, WALK_OLD);
                SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 5)
            {
                SetPlayerWalkingStyle (playerid, WALK_FAT_OLD);
                SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 6)
            {
                SetPlayerWalkingStyle (playerid, WALK_FAT);
            	SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 7)
            {
                SetPlayerWalkingStyle (playerid, WALK_LADY);
                SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 8)
            {
                SetPlayerWalkingStyle (playerid, WALK_LADY2);
                SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 9)
            {
                SetPlayerWalkingStyle (playerid, WALK_WHORE);
                SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 10)
            {
                SetPlayerWalkingStyle (playerid, WALK_WHORE2);
                SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 11)
            {
                SetPlayerWalkingStyle (playerid, WALK_DRUNK);
            	SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 12)
            {
                SetPlayerWalkingStyle (playerid, WALK_BLIND);
            	SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
            if(listitem == 13)
            {
                SetPlayerWalkingStyle (playerid, WALK_DEFAULT);
                SendClientMessage(playerid, COLOR_GREY, "{E0E0E0} Вы изменили свой стиль походки. Использование: [{FFAF00}W{E0E0E0}] + [{FFAF00}ALT{E0E0E0}]");
            }
        }
    }
    else if(dialogid == D_SETTINGS_CHAT)
    {
    	if(!response) SetPVarInt(playerid, !"ChatAnim", listitem);
   		ShowPlayerSettings(playerid);
    }
	return true;
}

CMD:delveh(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	DestroyVehicle(GetPlayerVehicleID(playerid));
	return true;
}

CMD:fix(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	SetVehicleHealth(GetPlayerVehicleID(playerid), 1000.0);
	RepairVehicle(GetPlayerVehicleID(playerid));
	return true;
}

new Text3D:callsign[MAX_VEHICLES];

CMD:callsign(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
    Delete3DTextLabel(callsign[GetPlayerVehicleID(playerid)]);
    if(strlen(params))
    {
        callsign[GetPlayerVehicleID(playerid)] = Create3DTextLabel(params, -1, 0.0, 0.0, 0.0, 50.0, 0, true);
        Attach3DTextLabelToVehicle(callsign[GetPlayerVehicleID(playerid)], GetPlayerVehicleID(playerid), -0.8, -2.8, -0.3);
        SendClientMessage(playerid, -1, !"> Вы установили маркировку на автомобиль!");
    }
    else SendClientMessage(playerid, -1, !"> Вы удалили маркировку с автомобиля!");
	return true;
}

CMD:nitro(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	SetPVarInt(playerid, !"VehicleNitro", !GetPVarInt(playerid, !"VehicleNitro"));
	SendClientMessageEx(playerid, -1, "Вы %s "FLAME_COLOR"нитро-режим"COLOR_WHITE".", (GetPVarInt(playerid, !"VehicleNitro")) ? ("включили") : ("выключили"));
	if(GetPVarInt(playerid, !"VehicleNitro")) SendClientMessage(playerid, -1, !"Используйте "FLAME_COLOR"L.Alt, L.Ctrl"COLOR_WHITE".");
	return true;
}

CMD:carcolor(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	if(sscanf(params, "ii", params[0], params[1])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /carcolor [цвет1] [цвет2]");
	ChangeVehicleColor(GetPlayerVehicleID(playerid), params[0], params[1]);
	return true;
}

CMD:gmcar(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	if(!GetPVarInt(playerid, !"GMCar"))
	{
		SetPVarInt(playerid, !"GMCar", 1);
		SetTimerEx("RepairPlayerVehicle", 500, false, "i", playerid);
		SendClientMessage(playerid, -1, !"Вы включили режим неуязвимости транспорта");
	}
	else
	{
		SendClientMessage(playerid, -1, !"Вы отключили режим неуязвимости транспорта");
		DeletePVar(playerid, !"GMCar");
	}
	return true;
}

forward RepairPlayerVehicle(playerid);
public RepairPlayerVehicle(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || !GetPVarInt(playerid, !"GMCar")) return true;
	RepairVehicle(GetPlayerVehicleID(playerid));
	SetVehicleHealth(GetPlayerVehicleID(playerid), 1000.0);
	SetTimerEx("RepairPlayerVehicle", 500, false, "i", playerid);
	return true;
}

CMD:flipcar(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	new Float:angle;
	GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
	SetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
	return true;
}

CMD:paintjob(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, !"* Необходимо быть за рулём транспорта!");
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /paintjob [номер]");
	if(params[0] < 0 || params[0] > 3) return SendClientMessage(playerid, COLOR_GREY, !"* Номер от 0 до 2. 3 - убрать.");
	ChangeVehiclePaintjob(GetPlayerVehicleID(playerid), params[0]);
	return true;
}

CMD:car(playerid)
{
	if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_GREY, !"* Недоступно в транспорте!");
	new string[500];
	strcat(string, "Black and white LSPD cruiser\nBlack and white SFPD cruiser\nBlack and white LVPD cruiser\n");
	strcat(string, "Black and white police rancher\nBlack and white enforcer\nBlack and white police helicopter\nSASD/DOC LS cruiser\nSASD/DOC SF cruiser\nSASD/DOC LV cruiser\nSASD/DOC rancher\n");
	strcat(string, "SASD/DOC enforcer\nSASD/DOC helicopter\nPolice motorbike\nUnmarked premier\nUnmarked sultan\nUnmarked FBI rancher\nUnmarked cheetah\nUnmarked bullet\n");
	strcat(string, "Prisoner transport van\nWater pump van(SWAT truck)\nArmored FBI truck");
	ShowPlayerDialog(playerid, D_SPECIAL_VEHICLES, DIALOG_STYLE_LIST, !"Служебные автомобили", string, !"Выбрать", !"Закрыть");
	return true;
}

CMD:rules(playerid)
{
	new string[2500];
	strcat(string, ""FLAME_COLOR"1."COLOR_WHITE" Чат(мут от 10 до 60 минут)\n");
	strcat(string, ""FLAME_COLOR"1.1"COLOR_WHITE" Запрещены любые оскорбления личности в OOC чат.\n");
	strcat(string, ""FLAME_COLOR"1.2"COLOR_WHITE" Запрещена любая провокация игроков на конфликт/ответные оскорбления в OOC чат.\n");
	strcat(string, ""FLAME_COLOR"1.3"COLOR_WHITE" Запрещено засорять чат глупой и не нужной информацией/рекламой(Спам).\n");
	strcat(string, ""FLAME_COLOR"1.4"COLOR_WHITE" Запрещён флуд в любой из чатов (IC, OOC).\n");
	strcat(string, ""COLOR_WHITE"(Три однотипные сообщения на 12 строк чата - расцениваются как флуд).\n\n");
	strcat(string, ""FLAME_COLOR"2."COLOR_WHITE" Неадекватное поведение(блокировка)\n");
	strcat(string, ""FLAME_COLOR"2.1"COLOR_WHITE" Сообщения рассистского/националистического/экстремистского или просто неадекватного содержания,\n");
	strcat(string, "караются блокировкой.\n");
	strcat(string, ""FLAME_COLOR"2.2"COLOR_WHITE" Умышленное нанесение морального вреда какой-либо личности приведет к блокировке.\n");
	strcat(string, ""FLAME_COLOR"2.3"COLOR_WHITE" Сообщение сильно насыщенное оскорблениями или прямой провокацией может быть расценено как\n");
	strcat(string, "неадекватное поведение.\n\n");
	strcat(string, ""FLAME_COLOR"3."COLOR_WHITE" Репорт(предупреждение)\n");
	strcat(string, ""FLAME_COLOR"3.1"COLOR_WHITE" Report(доклад, жалоба) - используется исключительно для жалоб на кого-либо, нарушающих правила\n");
	strcat(string, "сервера. Использование репорта в других целях приведет к получению наказания в виде предупреждения.\n");
	strcat(string, "(Интересующие вас вопросы по моду или серверу вы можете спросить у помощников в /ask).\n\n");
	strcat(string, ""FLAME_COLOR"4."COLOR_WHITE" Потребительское отношение к администрации(блокировка).\n");
	strcat(string, ""FLAME_COLOR"4.1"COLOR_WHITE" Запрещается провоцировать администрацию на конфликт(блокировка).\n");
	strcat(string, ""FLAME_COLOR"4.2"COLOR_WHITE" Запрещается оскорблять администрацию и руководство проекта(блокировка).\n\n");
	strcat(string, ""FLAME_COLOR"5."COLOR_WHITE" Уход от наказания(блокировка)\n");
	strcat(string, ""FLAME_COLOR"5.1"COLOR_WHITE" Создание нового аккаунта, в случае, если хоть один из аккаунтов игрока заблокирован(ЧС проекта).\n");
	strcat(string, ""FLAME_COLOR"5.2"COLOR_WHITE" Игра на сервере с любого другого игрока, в случае, если вы уже были заблокированы(ЧС проекта).");
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, !"Правила сервера Flame Project:", string, !"ОК", !"");
	return true;
}

CMD:time(playerid, params[])
{
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /time [время]");
	if(params[0] < 0 || params[0] > 23) return SendClientMessage(playerid, COLOR_GREY, !"* Время от 0 до 23 часов!");
	SetPlayerTime(playerid, params[0], 00);
	return true;
}

CMD:tp(playerid, params[])
{
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /tp [playerid]");
	if(!IsPlayerConnected(params[0])) return SendClientMessage(playerid, COLOR_GREY, !"* Данный игрок не подключён!");
	new Float:tpX, Float:tpY, Float:tpZ;
	GetPlayerPos(params[0], tpX, tpY, tpZ);
	SetPlayerPos(playerid, tpX+1.0, tpY, tpZ);
	return true;
}

CMD:weapon(playerid, params[]) return cmd_gun(playerid, params);
CMD:gun(playerid, params[])
{
	if(sscanf(params, "ii", params[0], params[1])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE"/gun [weaponid] [патроны]");
	if(params[0] < 1 || params[0] > 46) return SendClientMessage(playerid, COLOR_GREY, !"* Номер оружия от 1 до 46.");
	if(params[1] < 1) return SendClientMessage(playerid, COLOR_GREY, !"* Неверное количество патронов!");
	GivePlayerWeapon(playerid, params[0], params[1]);
	return true;
}

CMD:skin(playerid, params[])
{
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /skin [номер]");
	if(params[0] < 1 || params[0] > 311) return SendClientMessage(playerid, COLOR_GREY, !"* Номер скина от 1 до 311.");
	SetPlayerSkin(playerid, params[0]);
	return true;
}

CMD:health(playerid)
{
	SetPlayerHealth(playerid, 100.0);
	return true;
}

CMD:armour(playerid)
{
	SetPlayerArmour(playerid, 100.0);
	return true;
}

CMD:nameoff(playerid)
{
	foreach(new i : Player) ShowPlayerNameTagForPlayer(i, playerid, false);
	SendClientMessage(playerid, -1, !"*Вы выключили отображение ников!");
	DeletePVar(playerid, !"HideNames");
	return true;
}
CMD:nameon(playerid)
{
	foreach(new i : Player) ShowPlayerNameTagForPlayer(i, playerid, true);
	SendClientMessage(playerid, -1, !"Вы включили отображение ников!");
	SetPVarInt(playerid, !"HideNames", 1);
	return true;
}

CMD:spawnme(playerid)
{
	GotoSpawn(playerid);
	return true;
}

CMD:slapme(playerid)
{
	new Float:slapX, Float:slapY, Float:slapZ;
	GetPlayerPos(playerid, slapX, slapY, slapZ);
	SetPlayerPos(playerid, slapX, slapY, slapZ + 5.0);
    PlayerPlaySound(playerid, 1130, slapX, slapY, slapZ + 5.0);
    return true;
}

CMD:style(playerid, params[])
{
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /style [номер]");
	if(params[0] < 0 || params[0] > 5) return SendClientMessage(playerid, COLOR_GREY, !"* Номер стиля боя от 0 до 5.");
	SetPVarInt(playerid, !"FightStyle", params[0]);
	switch(params[0])
	{
		case 0..3: params[0] += 4;
		case 4..5: params[0] += 11;
	}
	SetPlayerFightingStyle(playerid, params[0]);
	SendClientMessage(playerid, -1, !"Вы изменили стиль боя!");
	return true;
}

CMD:money(playerid, params[])
{
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /money [количество]");
	//GivePlayerMoney(playerid, params[0]);
	UpdatePlayerMoney(playerid, params[0]);
	return true;
}

CMD:rw(playerid)
{
	ResetPlayerWeapons(playerid);
	return true;
}

CMD:rm(playerid)
{
	ResetPlayerMoney(playerid);
	return true;
}

CMD:xyz(playerid, params[])
{
	new Float:tpX, Float:tpY, Float:tpZ;
	if(sscanf(params, "fff", tpX, tpY, tpZ)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /xyz [X] [Y] [Z]");
	SetPlayerPos(playerid, tpX, tpY, tpZ);
	return true;
}

CMD:admins(playerid)
{
	SendClientMessage(playerid, 0xFFFF00AA, "Администраторы онлайн:");
	new amount;
	foreach(new i : Player)
	{
		if(pData[i][pAdmin]) SendClientMessageEx(playerid, -1, "\t%s[%i]", pData[i][pName], i);
		amount++;
	}
	if(!amount) SendClientMessage(playerid, COLOR_GREY, !"Нет администрации в сети!");
	return true;
}

CMD:newpass(playerid, params[])
{
	new pass[32];
	if(sscanf(params, "s[32]", pass)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /newpass [пароль]");
	if(strlen(pass) < 6 || strlen(pass) > 32) return SendClientMessage(playerid, COLOR_GREY, !"* Длина пароля от 6 до 32 символов!");
	for(new i; i < strlen(pass); i++)
	{
		switch(pass[i])
		{
			case 'A'..'Z', 'a'..'z', '0'..'9': continue;
			default: return SendClientMessage(playerid, COLOR_GREY, !"* Пароль содержит недопустимые символы!");
		}
	}
	format(pData[playerid][pPassword], 32, "%s", pass);
	UpdateBaseStr("accounts", "Password", pass, pData[playerid][pID]);
	SendClientMessageEx(playerid, -1, "Вы изменили пароль на '%s'.", pass);
	return true;
}

CMD:id(playerid, params[])
{
	new name[24];
	if(sscanf(params, "s[24]", name)) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /id [ник]");
	new amount = 0;
	foreach(new i : Player)
	{
		if(strfind(pData[i][pName], name, true) != -1) amount++, SendClientMessageEx(playerid, -1, "%s[%i]", pData[i][pName], i);
	}
	if(!amount) SendClientMessage(playerid, COLOR_GREY, !"* Совпадений не найдено!");
	return true;
}

CMD:stats(playerid, params[])
{
	new string[256];
	format(string, sizeof(string), ""COLOR_WHITE"Статистика персонажа "FLAME_COLOR"#%i %s\n\n"COLOR_WHITE"Предупреждений:\t"FLAME_COLOR"%i\n"COLOR_WHITE"Убийств:\t\t\t"FLAME_COLOR"%i\n"COLOR_WHITE"Смертей:\t\t\t"FLAME_COLOR"%i\n\n\
		"COLOR_WHITE"Комментарий от администрации:\n"FLAME_COLOR"%s", pData[playerid][pID], pData[playerid][pName], pData[playerid][pWarns], pData[playerid][pKills], pData[playerid][pDeaths], pData[playerid][pComment]);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, !"Статистика", string, !"Закрыть", !"");
	return true;
}

CMD:uniform(playerid, params[])
{
	new string[790];
	strcat(string, "Наименование\tРаса\tПол\tID скина\n");
	strcat(string, "LSPD: tenpen\tЧернокожий\tМужской\t265\n");
	strcat(string, "LSPD: pulaski\tСветлокожий\tМужской\t266\n");
	strcat(string, "LSPD: Hernandez\tСветлокожий\tМужской\t267\n");
	strcat(string, "LSPD: lapd1\tСветлокожий\tМужской\t280\n");
	strcat(string, "LSPD: sfpd1\tСветлокожий\tМужской\t281\n");
	strcat(string, "LSPD: lapdm1\tСветлокожий\tМужской\t284\n");
	strcat(string, "LSPD: lapdna\tСветлокожий\tМужской\t300\n");
	strcat(string, "LSPD: sfpdna\tСветлокожий\tМужской\t301\n");
	strcat(string, "LSPD: WFYCLPD\tСветлокожая\tЖенский\t306\n");
	strcat(string, "LSPD: VBFYCPD\tТемнокожая\tЖенский\t307\n");
	strcat(string, "SASD/DOC: lvpd1\tСветлокожий\tМужской\t282\n");
	strcat(string, "SASD/DOC: csher\tСветлокожий\tМужской\t283\n");
	strcat(string, "SASD/DOC: dsher\tСветлокожий\tМужской\t288\n");
	strcat(string, "SASD/DOC: lvpdna\tСветлокожий\tМужской\t302\n");
	strcat(string, "SASD/DOC: csherna\tСветлокожий\tМужской\t310\n");
	strcat(string, "SASD/DOC: dsherna\tСветлокожий\tМужской\t311\n");
	strcat(string, "SASD/DOC: WFYCLLV\tСветлокожая\tЖенский\t309");
	ShowPlayerDialog(playerid, D_SPECIAL_SKINS, DIALOG_STYLE_TABLIST_HEADERS, !"Выход на дежурство", string, !"Выбрать", !"Закрыть");
	return true;
}

CMD:gm(playerid)
{
	if(GetPVarInt(playerid, !"PlayerGM"))
	{
		DeletePVar(playerid, !"PlayerGM");
		SendClientMessage(playerid, -1, !"Вы отключили режим бессмертия!");
	}
	else
	{
		SetPVarInt(playerid, !"PlayerGM", 1);
		SendClientMessage(playerid, -1, !"Вы включили режим бессмертия!");
	}
	return true;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(GetPVarInt(playerid, !"PlayerGM")) return SetPlayerHealth(playerid, 1000.0);
	return true;
}

CMD:givegun(playerid, params[])
{
	if(sscanf(params, "iii", params[0], params[1], params[2])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /givegun [playerid] [weaponid] [патроны]");
	GivePlayerWeapon(params[0], params[1], params[2]);
	return true;
}

CMD:skill(playerid, params[])
{
	if(sscanf(params, "ii", params[0], params[1]))
	{
		SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /skill [skillid] [значение]");
		SendClientMessage(playerid, -1, !"1 - 9mm | 2 - Silenced 9mm | 3 - Desert Eagle");
		SendClientMessage(playerid, -1, !"4 - Shotgun | 5 - Sawnoff | 6 - Combat Shotgun");
		SendClientMessage(playerid, -1, !"7 - Micro SMG/UZI | 8 - MP-5");
		SendClientMessage(playerid, -1, !"9 - AK-47 | 10 - M4 | 11 - Sniper Rifle");
		return true;
	}
	if(params[0] < 1 || params[0] > 11) return SendClientMessage(playerid, COLOR_GREY, !"* Номер скилла от 1 до 11!");
	if(params[1] < 0 || params[1] > 1000) return SendClientMessage(playerid, COLOR_GREY, !"* Значение от 0 до 1000!");
	SetPlayerSkillLevel(playerid, params[0]-1, params[1]);
	return true;
}

CMD:taser(playerid)
{
	if(!GetPVarInt(playerid, !"PlayerTaser"))
	{
		new weapons, ammo;
		GetPlayerWeaponData(playerid, 2, weapons, ammo);
		SetPVarInt(playerid, !"TaserWeaponID", weapons);
		SetPVarInt(playerid, !"TaserWeaponAmmo", ammo);
		GivePlayerWeapon(playerid, 23, 2000);
		SetPVarInt(playerid, !"PlayerTaser", 1);
	}
	else
	{
		DeletePVar(playerid, !"PlayerTaser");
		GivePlayerWeapon(playerid, GetPVarInt(playerid, !"TaserWeaponID"), GetPVarInt(playerid, !"TaserWeaponAmmo"));
		DeletePVar(playerid, !"TaserWeaponAmmo");
		DeletePVar(playerid, !"TaserWeaponID");
	}
	return true;
}

hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(GetPVarInt(playerid, !"PlayerTaser") && GetPlayerWeapon(playerid) == 23)
	{
		ApplyAnimation(damagedid, "CRACK", "CRCKIDLE2", 4.1, true, true, true, true, 0, 1);
		TogglePlayerControllable(damagedid, false);
		SetTimerEx("ClearTaser", 15000, false, "i", damagedid);
	}
}

forward ClearTaser(playerid);
public ClearTaser(playerid)
{
	ClearAnimations(playerid, 1);
	TogglePlayerControllable(playerid, true);
}

CMD:rpdeath(playerid, params[])
{
	if(GetPVarInt(playerid, !"RPDeath"))
	{
		DeletePVar(playerid, !"RPDeath");
		SendClientMessage(playerid, -1, !"Вы включили режим РП смерти!");
	}
	else
	{
		SetPVarInt(playerid, !"RPDeath", 1);
		SendClientMessage(playerid, -1, !"Вы выключили режим РП смерти!");
	}
	return true;
}

hook OnPlayerDeath(playerid)
{
	if(GetPVarInt(playerid, !"RPDeath"))
	{
		new Float:dX, Float:dY, Float:dZ;
		GetPlayerPos(playerid, dX, dY, dZ);
		GotoSpawn(playerid);
		SetPlayerPos(playerid, dX, dY, dZ);
		ApplyAnimation(playerid, "PED", "KO_SHOT_FRONT", 4.1, false, true, true, true, 0, 1);
		SetPVarInt(playerid, !"UseAnim", 1);
	}
}



CMD:swalk(playerid, params[])
{
	if(sscanf(params, "i", params[0])) return SendClientMessage(playerid, COLOR_GREY, !"[SYNTAX]:"COLOR_WHITE" /swalk [стиль(0-13)");
	if(params[0] < 0 || params[0] > 13) return SendClientMessage(playerid, COLOR_GREY, !"* Стиль походки от 0 до 13!");
	SetPlayerWalkingStyle(playerid, params[0]);
	return true;
}

CMD:clearchat(playerid, params[])
{

	for(new i; i < 20; i++) SendClientMessage(playerid, -1, !" ");
	return true;
}

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	SetPlayerPos(playerid, fX, fY, fZ);
}

CMD:mm(playerid) return cmd_menu(playerid);
CMD:mn(playerid) return cmd_menu(playerid);
CMD:menu(playerid)
{
	ShowPlayerDialog(playerid, D_MAINMENU, DIALOG_STYLE_LIST, !"Игровое Меню", !""FLAME_COLOR"1."COLOR_WHITE" Инвентарь\n"FLAME_COLOR"2."COLOR_WHITE" Смартфон\n"FLAME_COLOR"3."COLOR_WHITE" Статистика\n"FLAME_COLOR"4."COLOR_WHITE" Связь с администрацией\n"FLAME_COLOR"5."COLOR_WHITE" Команды сервера\n"FLAME_COLOR"6."COLOR_WHITE" Настройки\n"FLAME_COLOR"7."COLOR_WHITE" Квесты\n"FLAME_COLOR"8."COLOR_WHITE" Донат", !"Далее", !"Закрыть");
	return true;
}

CMD:phone(playerid)
{
	new slot = GetItemInInventorySlot(playerid, INV_ITEM_PHONE, INV_PHONE_PARAM);
	if(slot == -1) return SendClientMessage(playerid, COLOR_ERROR, !"* У Вас нет смартфона.");
	ShowPlayerPhone(playerid, slot);
	return true;
}

CMD:report(playerid)
{
	SendClientMessage(playerid, -1, !"DEVELOPMENT");
	return true;
}

CMD:donate(playerid)
{
	SendClientMessage(playerid, -1, !"DEVELOPMENT");
	return true;
}

CMD:cpanel(playerid)
{
	SendClientMessage(playerid, -1, !"DEVELOPMENT");
	return true;
}

ShowPlayerSettings(playerid)
{
	new string[512];
	format(string, sizeof(string), "1. Ники игроков\t[ %s ]\n2. Неуязвимость\t[ %s ]\n3. Режим РП смерти\t[ %s ]\n4. Приглашения в мир\t[ %s ]\n5. Заморозка после спауна\t[ %i ]\n\
		6. Звук попадания из оружия\t[ %s ]\n7. Стиль боя\t[ %s ]\n8. Стиль походки\t[ %s ]\n9. Скиллы оружия\n10. Настройки чата\n11. Управление аттачами\n12. Стиль чата\t[ %s ]",
		(GetPVarInt(playerid, !"HideNames")) ? ("OFF") : ("ON"), (GetPVarInt(playerid, !"PlayerGM")) ? ("ON") : ("OFF"), (GetPVarInt(playerid, !"RPDeath")) ? ("ON") : ("OFF"),
		(GetPVarInt(playerid, !"WorldInvites")) ? ("ON") : ("OFF"), GetPVarInt(playerid, !"SpawnDelay"), (GetPVarInt(playerid, !"ShootSounds")) ? ("ON") : ("OFF"),
		GetFightStyleName(GetPVarInt(playerid, !"FightStyle")), GetChatAnimName(GetPVarInt(playerid, "ChatAnim")), "Стандартный");
	ShowPlayerDialog(playerid, D_SETTINGS, DIALOG_STYLE_TABLIST, !"Настройки игрока", string, !"Далее", !"Выход");
	return true;
}

GetFightStyleName(fight)
{
	new string[16];
	switch(fight)
	{
		case 1: string = "Бокс";
		case 2: string = "Кунг Фу";
		case 3: string = "Колено";
		case 4: string = "Захват";
		case 5: string = "Удар локтём";
		default: string = "Стандартный";
	}
	return string;
}

forward WalkAnim(playerid);
public  WalkAnim(playerid)
{
	new style = GetPlayerWalkingStyle(playerid);
	if(style <= WALK_DEFAULT || style > WALK_BLIND)
		return true;

    new keys, updown, leftright;
    GetPlayerKeys(playerid, keys, updown, leftright);
    KillTimer(walktime[playerid]);

    if(IsPlayerUsingWalkMovement(keys, updown, leftright))
    {
        ApplyAnimation(playerid, "PED", WalkAnimationNames[style], 4.1, true, true, true, true, 1);
        walktime[playerid] = SetTimerEx("WalkAnim", 200, false, "d", playerid);
    }
    else ApplyAnimation(playerid, "PED", WalkAnimationNames[style], 4.0, false, false, false, false, 1);

    return true;
}
stock SetPlayerWalkingStyle(playerid, style) {  WalkStyle[playerid] = style;}
stock GetPlayerWalkingStyle(playerid) { return WalkStyle[playerid];}
stock IsPlayerUsingWalkMovement(keys, updown, leftright)
{
	return (keys & KEY_WALK) && ((updown & KEY_UP) || (updown & KEY_DOWN) || (leftright & KEY_LEFT) || (leftright & KEY_RIGHT));
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (((newkeys & KEY_WALK && newkeys & KEY_UP) || (newkeys & KEY_WALK && newkeys & KEY_DOWN) || (newkeys & KEY_WALK && newkeys & KEY_LEFT) || (newkeys & KEY_WALK && newkeys & KEY_RIGHT))
                || ((oldkeys & KEY_WALK && newkeys & KEY_UP) || (oldkeys & KEY_WALK && newkeys & KEY_DOWN) || (oldkeys & KEY_WALK && newkeys & KEY_LEFT) || (oldkeys & KEY_WALK && newkeys & KEY_RIGHT))
                || ((newkeys & KEY_WALK && oldkeys & KEY_UP) || (newkeys & KEY_WALK && oldkeys & KEY_DOWN) || (newkeys & KEY_WALK && oldkeys & KEY_LEFT) || (newkeys & KEY_WALK && oldkeys & KEY_RIGHT))
                && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) walktime[playerid] = SetTimerEx("WalkAnim",200,false,"d",playerid);
	else if(newkeys & KEY_SPRINT && GetPVarInt(playerid, !"UseAnim"))
	{
		ClearAnimations(playerid, 1);
		DeletePVar(playerid, !"UseAnim");
	}
}

GetChatAnimName(anim)
{
	new animtext[16];
	switch(anim)
	{
		case 1: animtext = "По умолчанию";
		case 2: animtext = "Недоверие";
		case 3: animtext = "Открытость";
		case 4: animtext = "Неодобрение";
		case 5: animtext = "Настойчивость";
		case 6: animtext = "Позитивность";
		case 7: animtext = "Неуверенность";
		default: animtext = "Отсутсвует";
	}
	return animtext;
}

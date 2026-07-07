#include <YSI_Coding\y_hooks>

#define BUS_INT_POS 2496.8643, -1662.6248, 3000.5364
#define BUS_INT_FA 360.0

#define MAX_BUS_STOPS 50
#define BUS_PRICE_PER_METER 0.0050
#define BUS_SEC_PER_METER 0.05

enum stop_info
{
	bsName[64],
	Float:bsPosX,
	Float:bsPosY,
	Float:bsPosZ,
	Float:bsPosFA,
	bsType
}
new BusStopInfo[MAX_BUS_STOPS][stop_info];
new TOTALBUSSTOPS = 0;

new BusWaitings[MAX_PLAYERS];

enum E_BUS_DATA
{
	busStop,
	busCategory,
	bool:busWaiting,
	bool:busTravel,
	busTravelTime,
	busTravelTo
}
new BusData[MAX_PLAYERS][E_BUS_DATA];

static const bus_stops_categories[][] = {"Важные места", "Частные организации "FLAME_COLOR"(Начальные работы)", "Государственные организации", "Супермаркеты", "Магазины электроники", "Автозаправочные станции", "Автосалоны & Каршеринг", "Магазины одежды", "Бары/Рестораны"};

hook OnPlayerConnect(playerid)
{
	BusData[playerid][busStop] = 0;
	BusData[playerid][busCategory] = 0;
	BusData[playerid][busWaiting] = false;
	BusData[playerid][busTravel] = false;
	BusData[playerid][busTravelTime] = 0;
	BusData[playerid][busTravelTo] = 0;
	return true;
}

hook OnGameModeInit()
{
	new __ms0[] = "SELECT * FROM `bus_stops`";
	new __ms1[] = "LoadBusStops";
	mysql_tquery(ConnectMySQL, __ms0, __ms1);
}

forward LoadBusStops();
public LoadBusStops()
{
	new rows = cache_get_row_count();
	for(new i = 0; i < rows; i++)
	{
		cache_get_field_content(i, "name", BusStopInfo[i][bsName], ConnectMySQL, 64);
		BusStopInfo[i][bsPosX] = cache_get_field_content_float(i, "pos_x");
		BusStopInfo[i][bsPosY] = cache_get_field_content_float(i, "pos_y");
		BusStopInfo[i][bsPosZ] = cache_get_field_content_float(i, "pos_z");
		BusStopInfo[i][bsPosFA] = cache_get_field_content_float(i, "pos_fa");
		BusStopInfo[i][bsType] = cache_get_field_content_int(i, "type");

		new string[128];
		format(string, sizeof(string), "Остановка "FLAME_COLOR"%s"COLOR_WHITE"\nДля взаимодействия нажмите "FLAME_COLOR"ALT", BusStopInfo[i][bsName]);
		CreateDynamic3DTextLabel(string, 0xFFFFFFFF, BusStopInfo[i][bsPosX], BusStopInfo[i][bsPosY], BusStopInfo[i][bsPosZ], 10.0);
		TOTALBUSSTOPS++;
	}
	printf("- Автобусные остановки успешно загружены! Всего %i шт.", TOTALBUSSTOPS);
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && oldkeys & KEY_WALK)
	{
		for(new i; i < TOTALBUSSTOPS; i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, BusStopInfo[i][bsPosX], BusStopInfo[i][bsPosY], BusStopInfo[i][bsPosZ]))
			{
				return ShowPlayerBusStops(playerid, i);
			}
		}
	}
	return true;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == D_BUS_CAT)
	{
		if(!response) return true;
		new bid = BusData[playerid][busStop];
		new string[1024] = "Остановка\tРайон\tСтоимость проезда\n";
		new amount = 1;
		BusData[playerid][busCategory] = listitem;
		for(new i = 0; i < TOTALBUSSTOPS; i++)
		{
			if(BusStopInfo[i][bsType] == listitem && i != bid)
			{
				new price = floatround(GetDistanceBetweenPoints(BusStopInfo[bid][bsPosX], BusStopInfo[bid][bsPosY], 0.0, BusStopInfo[i][bsPosX], BusStopInfo[i][bsPosY], 0.0)*BUS_PRICE_PER_METER);
				new zonaname[32];
				GetZonaName(BusStopInfo[i][bsPosX], BusStopInfo[i][bsPosY], zonaname);
				format(string, sizeof(string), "%s"FLAME_COLOR"%i. "COLOR_WHITE" %s\t%s\t"FLAME_COLOR"%i$\n", string, amount, BusStopInfo[i][bsName], zonaname, price);
				amount ++;
			}
		}
		ShowPlayerDialog(playerid, D_BUS_STOPS, DIALOG_STYLE_TABLIST_HEADERS, bus_stops_categories[listitem], string, !"Далее", !"Отмена");
	}
	else if(dialogid == D_BUS_STOPS)
	{
		if(!response) return true;
		new bid = BusData[playerid][busStop];
		new category = BusData[playerid][busCategory];
		new amount = -1;
		for(new i = 0; i < TOTALBUSSTOPS; i++)
		{
			if(BusStopInfo[i][bsType] == category && i != bid) amount++;
			if(amount == listitem)
			{
				new price = floatround(GetDistanceBetweenPoints(BusStopInfo[bid][bsPosX], BusStopInfo[bid][bsPosY], 0.0, BusStopInfo[i][bsPosX], BusStopInfo[i][bsPosY], 0.0)*BUS_PRICE_PER_METER);
				if(pData[playerid][pMoney] < price) return SendClientMessage(playerid, COLOR_ERROR, !"* У Вас недостаточно денег!");
				UpdatePlayerMoney(playerid, -price);
				BusData[playerid][busWaiting] = true;
				SendClientMessage(playerid, COLOR_GREY, !"* Автобус приедет на остановку в течение 15 секунд!");
				BusWaitings[playerid] = SetTimerEx("BusWaiting", 15*1000, false, "iii", playerid, bid, i);

				if(!IsPlayerInRangeOfPoint(playerid, 15.0, BusStopInfo[bid][bsPosX], BusStopInfo[bid][bsPosY], BusStopInfo[bid][bsPosZ]))
				{
					SendClientMessage(playerid, COLOR_GREY, !"* Вы покинули остановку и прервали свою поездку!");
					KillTimer(BusWaitings[playerid]);
					BusData[playerid][busWaiting] = false;
					return true;
				}

				return true;
			}
		}
	}
	return true;
}

ShowPlayerBusStops(playerid, bus)
{
	BusData[playerid][busStop] = bus;
	new string[512];
	for(new i = 0; i < sizeof(bus_stops_categories); i++)
	{
		format(string, sizeof(string), "%s"FLAME_COLOR"%i. "COLOR_WHITE"%s\n", string, i+1, bus_stops_categories[i]);
	}
	ShowPlayerDialog(playerid, D_BUS_CAT, DIALOG_STYLE_LIST, "Автобусные остановки", string, !"Далее", !"Отмена");
	return true;
}

forward BusWaiting(playerid, bid, i);
public BusWaiting(playerid, bid, i)
{
	StartPlayerBusTravel(playerid, bid, i);
}

StartPlayerBusTravel(playerid, from, to)
{
	BusData[playerid][busWaiting] = false;
	BusData[playerid][busTravel] = true;
	BusData[playerid][busTravelTime] = floatround(GetDistanceBetweenPoints(BusStopInfo[from][bsPosX], BusStopInfo[from][bsPosY], 0.0, BusStopInfo[to][bsPosX], BusStopInfo[to][bsPosY], 0.0)*BUS_SEC_PER_METER);
	BusData[playerid][busTravelTo] = to;
	SetPlayerPos(playerid, BUS_INT_POS);
	SetPlayerFacingAngle(playerid, BUS_INT_FA);
	SetCameraBehindPlayer(playerid);
	StartPlayerTextureLoading(playerid, 3);
}

SecUpdate_BusStop(playerid)
{
	if(BusData[playerid][busWaiting])
	{
		new bid = BusData[playerid][busStop];
		if(!IsPlayerInRangeOfPoint(playerid, 15.0, BusStopInfo[bid][bsPosX], BusStopInfo[bid][bsPosY], BusStopInfo[bid][bsPosZ]))
		{
			KillTimer(BusWaitings[playerid]);
			SendClientMessage(playerid, COLOR_GREY, !"* Вы покинули остановку до прибытия автобуса!");
			BusData[playerid][busWaiting] = false;
			return true;
		}
	}
	if(BusData[playerid][busTravel])
	{
		new lefttime = BusData[playerid][busTravelTime];
		if(lefttime < 1)
		{
			new bid = BusData[playerid][busTravelTo];
			SetPlayerPos(playerid, BusStopInfo[bid][bsPosX], BusStopInfo[bid][bsPosY], BusStopInfo[bid][bsPosZ]);
			SetPlayerFacingAngle(playerid, BusStopInfo[bid][bsPosFA]);
			SetCameraBehindPlayer(playerid);
			StartPlayerTextureLoading(playerid, 3);
			Quest_OnPlayerFinishBusTravel(playerid, BusStopInfo[bid][bsPosX], BusStopInfo[bid][bsPosY], BusStopInfo[bid][bsPosZ]);
			BusData[playerid][busTravel] = false;
			PlayerTextDrawHide(playerid, BusTimerTD[playerid]);
		}
		else
		{
			BusData[playerid][busTravelTime] = lefttime-1;
			new str[64];
			format(str, sizeof(str), "Осталось времени %i:%02i", lefttime / 60, lefttime % 60);
			PlayerTextDrawSetString(playerid, BusTimerTD[playerid], RusText(str));
			PlayerTextDrawShow(playerid, BusTimerTD[playerid]);
		}
	}
	return true;
}
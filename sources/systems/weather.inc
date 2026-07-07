#include <YSI_Coding\y_hooks>

#define WEATHER_INCLUDED

#define WEATHER_MINUTES 180

static const Float:WEATHER_ZONES_POSES[][] = {
	{-2986.0288,-914.5515, -2370.0254,-914.5041, -1169.2097,-2061.9485, -1727.0336,-1596.2230, -1739.9412,-720.4758, -1033.5297,-322.4772, -828.3244,254.6598, -1343.3311,1620.7217, -2986.0068, 1548.5804}, // SF
	{-828.3244,254.6598, -1343.3311,1620.7217, -2986.0068,1548.5804, -2986.0061,2986.0583, -1285.9908,2986.0034, -507.1661, 1073.0313}, // TR
	{-2986.0562,-2990.6062, -2986.0288,-914.5515, -2370.0254,-914.5041, -1169.2097,-2061.9485, -1727.0336,-1596.2230, -1193.0643,-2049.4326, -1163.2369,-2971.9451}, // WH
	{-1727.0336,-1596.2230, -1193.0643,-2049.4326, -1163.2369,-2971.9451, 82.7322,-2957.9473, 74.4673,-992.6114, -356.5310,-322.5394, -1033.5297,-322.4772, -1739.9412,-720.4758}	 // FC
};

static const WEATHER_ZONES_POSES_AMOUNTS[] = {18, 12, 14, 14};

static const MinTemperature[] = {5, 4, 2, 15};

// Per-zone cumulative upper bounds (pr 0..99) for weather types 1..4.
static const WEATHER_CHANCES[][4] = {
	{20, 38, 44, 99}, // SF
	{11, 42, 51, 99}, // TR
	{16, 41, 53, 99}, // WH
	{ 0,  4,  4, 99}  // FC (no overcast)
};

static const WeatherNames[][] = {"Дождь", "Туман", "Пасмурно", "Ясно"};
static const WeatherZonesNames[][] = {"San Fierro", "Tierra Robada", "Whetstone", "Flint County"};

new Weather[sizeof(WEATHER_ZONES_POSES)];
new Temperature[sizeof(WEATHER_ZONES_POSES)];

new WeatherArea[sizeof(WEATHER_ZONES_POSES)];

hook OnGameModeInit()
{
	for(new i = 0; i < sizeof(WEATHER_ZONES_POSES); i++)
	{
		WeatherArea[i] = CreateDynamicPolygon(WEATHER_ZONES_POSES[i], _, _, WEATHER_ZONES_POSES_AMOUNTS[i], 0, 0);
	}
	GenerateNewWeather();
	SetTimer("GenerateNewWeather", WEATHER_MINUTES*60*1000, true);
}


stock W_EnterDynamicArea(playerid, areaid)
{
	if(areaid >= WeatherArea[0] && areaid <= WeatherArea[sizeof(WEATHER_ZONES_POSES)-1])
	{
		if(areaid == WeatherArea[3])
		{
			UpdatePlayerWeather(playerid, IsPlayerInDynamicArea(playerid, WeatherArea[0]) ? 0 : 3);
			return true;
		}
		for(new i = 0; i < sizeof(WEATHER_ZONES_POSES); i++)
		{
			if(WeatherArea[i] == areaid)
			{
				UpdatePlayerWeather(playerid, i);
				return true;
			}
		}
	}
	return true;
}


forward GenerateNewWeather();
public GenerateNewWeather()
{
	SendClientMessageToAll(0xFFFFFFFF, "Текущая погода в штате:");
	for(new i = 0; i < sizeof(WEATHER_ZONES_POSES); i++)
	{
		Temperature[i] = MinTemperature[i]+random(21);
		Weather[i] = GetWeatherForZone(i, random(100));
		new str[128];
		format(str, sizeof(str), " - "FLAME_COLOR"%s"COLOR_WHITE" | %i°C | %s", WeatherZonesNames[i], Temperature[i], WeatherNames[Weather[i]-1]);
		SendClientMessageToAll(0xFFFFFFFF, str);
	}
	foreach(new i : Player)
	{
		if(!IsPlayerInAnyDynamicArea(i)) continue;
		for(new j = 0; j < sizeof(WEATHER_ZONES_POSES); j++)
		{
			if(IsPlayerInDynamicArea(i, WeatherArea[j]))
			{
				UpdatePlayerWeather(i, j);
				break;
			}
		}
	}
}

UpdatePlayerWeather(playerid, zone)
{
	ShowWeatherTextDraw(playerid, WeatherZonesNames[zone], Temperature[zone]);
	switch(Weather[zone])
	{
		case 1: SetPlayerWeather(playerid, 8);
		case 2: SetPlayerWeather(playerid, 32);
		case 3: SetPlayerWeather(playerid, 20);
		case 4: SetPlayerWeather(playerid, 1);
	}
	return true;
}

GetWeatherForZone(zone, pr)
{
	for(new w = 0; w < 4; w++)
	{
		if(pr <= WEATHER_CHANCES[zone][w]) return w + 1;
	}
	return 0;
}


CMD:genweather(playerid)
{
	GenerateNewWeather();
	return true;
}
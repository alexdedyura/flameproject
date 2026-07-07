#include <YSI_Coding\y_hooks>

#define _MAX_PICKUPS 128

enum pick_info
{
	Float:pEnterPosX,
	Float:pEnterPosY,
	Float:pEnterPosZ,
	Float:pEnterPosFA,
	pEnterPosVW,
	pEnterPosInt,
	Float:pExitPosX,
	Float:pExitPosY,
	Float:pExitPosZ,
	Float:pExitPosFA,
	pExitPosVW,
	pExitPosInt
}

new PickInfo[_MAX_PICKUPS][pick_info];
new TOTALPICKUPS = 0;

hook OnGameModeInit()
{
	new __ms0[] = "SELECT * FROM `pickups`";
	new __ms1[] = "LoadPickups";
	mysql_tquery(ConnectMySQL, __ms0, __ms1);
}

forward LoadPickups();
public LoadPickups()
{
	new rows = cache_get_row_count();
	for(new i = 0; i < rows; i++)
	{
		new pickupName[64] = "";
		cache_get_field_content(i, "name", pickupName);

		PickInfo[i][pEnterPosX] = cache_get_field_content_float(i, "enter_pos_x");
		PickInfo[i][pEnterPosY] = cache_get_field_content_float(i, "enter_pos_y");
		PickInfo[i][pEnterPosZ] = cache_get_field_content_float(i, "enter_pos_z");
		PickInfo[i][pEnterPosFA] = cache_get_field_content_float(i, "enter_pos_fa");
		PickInfo[i][pEnterPosVW] = cache_get_field_content_int(i, "enter_pos_vw");
		PickInfo[i][pEnterPosInt] = cache_get_field_content_int(i, "enter_pos_int");

		PickInfo[i][pExitPosX] = cache_get_field_content_float(i, "exit_pos_x");
		PickInfo[i][pExitPosY] = cache_get_field_content_float(i, "exit_pos_y");
		PickInfo[i][pExitPosZ] = cache_get_field_content_float(i, "exit_pos_z");
		PickInfo[i][pExitPosFA] = cache_get_field_content_float(i, "exit_pos_fa");
		PickInfo[i][pExitPosVW] = cache_get_field_content_int(i, "exit_pos_vw");
		PickInfo[i][pExitPosInt] = cache_get_field_content_int(i, "exit_pos_int");

		CreateDynamicPickup(19902, 1, PickInfo[i][pEnterPosX], PickInfo[i][pEnterPosY], PickInfo[i][pEnterPosZ], PickInfo[i][pEnterPosVW], PickInfo[i][pEnterPosInt]);
		CreateDynamicPickup(19902, 1, PickInfo[i][pExitPosX], PickInfo[i][pExitPosY], PickInfo[i][pExitPosZ], PickInfo[i][pExitPosVW], PickInfo[i][pExitPosInt]);

		new str[256];
		format(str, sizeof(str), "%s{FFFFFF}\nНажмите "FLAME_COLOR"ALT{FFFFFF} чтобы войти.", pickupName);
		CreateDynamic3DTextLabel(str, COLOR_FLAME, PickInfo[i][pEnterPosX], PickInfo[i][pEnterPosY], PickInfo[i][pEnterPosZ], 15.0, _, _, 1, PickInfo[i][pEnterPosVW], PickInfo[i][pEnterPosInt]);
		CreateDynamic3DTextLabel("Нажмите "FLAME_COLOR"ALT{FFFFFF} чтобы выйти", 0xFFFFFFFF, PickInfo[i][pExitPosX], PickInfo[i][pExitPosY], PickInfo[i][pExitPosZ], 15.0, _, _, 1, PickInfo[i][pExitPosVW], PickInfo[i][pExitPosInt]);

		TOTALPICKUPS++;		
	}
	printf("- Пикапы успешно загружены! Всего %i шт.", TOTALPICKUPS);
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(!IsPlayerInAnyVehicle(playerid) && newkeys & KEY_WALK && !(oldkeys & KEY_WALK))
	{
		for(new i = 0; i < TOTALPICKUPS; i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 1.5, PickInfo[i][pEnterPosX], PickInfo[i][pEnterPosY], PickInfo[i][pEnterPosZ]) && 
				GetPlayerVirtualWorld(playerid) == PickInfo[i][pEnterPosVW] && GetPlayerInterior(playerid) == PickInfo[i][pEnterPosInt])
			{
				SetPlayerVirtualWorld(playerid, PickInfo[i][pExitPosVW]);
				SetPlayerInterior(playerid, PickInfo[i][pExitPosInt]);
				SetPlayerPos(playerid, PickInfo[i][pExitPosX], PickInfo[i][pExitPosY], PickInfo[i][pExitPosZ]);
				SetPlayerFacingAngle(playerid, PickInfo[i][pExitPosFA]);
				SetCameraBehindPlayer(playerid);
				StartPlayerTextureLoading(playerid, 3);
				return true;
			}
			if(IsPlayerInRangeOfPoint(playerid, 1.5, PickInfo[i][pExitPosX], PickInfo[i][pExitPosY], PickInfo[i][pExitPosZ]) && 
				GetPlayerVirtualWorld(playerid) == PickInfo[i][pExitPosVW] && GetPlayerInterior(playerid) == PickInfo[i][pExitPosInt])
			{
				SetPlayerVirtualWorld(playerid, PickInfo[i][pEnterPosVW]);
				SetPlayerInterior(playerid, PickInfo[i][pEnterPosInt]);
				SetPlayerPos(playerid, PickInfo[i][pEnterPosX], PickInfo[i][pEnterPosY], PickInfo[i][pEnterPosZ]);
				SetPlayerFacingAngle(playerid, PickInfo[i][pEnterPosFA]);
				SetCameraBehindPlayer(playerid);
				StartPlayerTextureLoading(playerid, 3);
				return true;
			}
		}
	}
	return true;
}
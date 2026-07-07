
VTax_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	#pragma unused inputtext
	switch(dialogid)
	{
		case D_VEHICLES_MENU_TAX:
		{
			new slot = GetPVarInt(playerid, "VMenuSlot");
			if(!response)
				return ShowPlayerVehicleMenu(playerid, slot);
			if(!IsGarageSlotUsed(playerid, slot))
				return true;

			new amount = GetGarageTaxAmount(playerid, slot);
			if(pData[playerid][pMoney] < amount)
				return SendClientMessage(playerid, -1, !"У Вас недостаточно денег!");

			UpdatePlayerMoney(playerid, -amount);
			PlayerGarage[playerid][slot][vTaxWeeks] = 0;

			new dbid = PlayerGarage[playerid][slot][vID];
			new q[96];
			new qfmt[] = "UPDATE vehicles SET tax_weeks = 0 WHERE id = %i";
			mysql_format(ConnectMySQL, q, sizeof(q), qfmt, dbid);
			mysql_tquery(ConnectMySQL, q);

			new vehid = pData[playerid][pVehicles][slot];
			if(vehid && IsValidVehicle(vehid))
			{
				new wasUnspawned = IsVehicleUnspawned(vehid);
				VehicleInfo[vehid][vTaxWeeks] = 0;
				if(wasUnspawned)
					SetVehicleToRespawn(vehid);
			}

			SendClientMessage(playerid, -1, !"Вы оплатили налог на транспорт!");
		}
	}

	return true;
}

Vehicles_NewWeek()
{
	new ms_string[512];
	new __ms0[] = "UPDATE vehicles SET tax_weeks = tax_weeks + 1 WHERE type = %i";
	mysql_format(ConnectMySQL, ms_string, sizeof(ms_string), __ms0, VEHICLE_TYPE_PERSONAL);
	mysql_tquery(ConnectMySQL, ms_string);

	foreach(new i : Vehicle)
	{
		if(VehicleInfo[i][vID] && VehicleInfo[i][vType] == VEHICLE_TYPE_PERSONAL)
		{
			VehicleInfo[i][vTaxWeeks]++;
			if(VehicleInfo[i][vTaxWeeks] >= DELETE_TAX_WEEKS)
				DeleteVehicle(i);
			else if(VehicleInfo[i][vTaxWeeks] >= UNSPAWN_TAX_WEEKS)
				SetVehicleToRespawn(i);

		}
	}

	foreach(new pid : Player)
	{
		for(new s = 0; s < MAX_PLAYER_VEHICLES; s++)
		{
			if(!IsGarageSlotUsed(pid, s))
				break;
			if(PlayerGarage[pid][s][vType] != VEHICLE_TYPE_PERSONAL)
				continue;
			if(pData[pid][pVehicles][s]) // spawned -> handled by foreach(Vehicle) above
				continue;

			PlayerGarage[pid][s][vTaxWeeks]++;
			if(PlayerGarage[pid][s][vTaxWeeks] >= DELETE_TAX_WEEKS)
			{
				DeleteGarageVehicle(pid, s);
				s--;
			}
		}
	}

	return true;
}

ShowPlayerVehicleTaxes(playerid, slot)
{
	SyncGarageFromSpawn(playerid, slot);

	new string[512];
	format(string, sizeof(string), ""COLOR_WHITE"Необходимо оплатить:"FLAME_COLOR" %i$.\n"COLOR_WHITE"Недельный налог на ваш автомобиль:"FLAME_COLOR" %i$.\n\n"COLOR_WHITE"При задержке уплаты налога сроком 2 недели ваш транспорт будет эвакуирован налоговой службой.\nПри задержке в 4 недели автомобиль будет конфискован НАВСЕГДА.",
		GetGarageTaxAmount(playerid, slot),
		GetVehicleTax(PlayerGarage[playerid][slot][vModel]));

	ShowPlayerDialog(playerid, D_VEHICLES_MENU_TAX, DIALOG_STYLE_MSGBOX, !"Оплата налогов", string, !"Далее", !"Назад");
	return true;
}

IsVehicleUnspawned(vehid)
{
	return (VehicleInfo[vehid][vTaxWeeks] >= UNSPAWN_TAX_WEEKS);
}

// Test
CMD:newday()
{
	NewDay();
	return true;
}


// Test
CMD:newweek()
{
	NewWeek();
	return true;
}
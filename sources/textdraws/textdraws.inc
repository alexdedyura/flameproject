
#include <..\..\sources\textdraws\chooseskin.inc>
#include <..\..\sources\textdraws\logo.inc>
#include <..\..\sources\textdraws\loading.inc>
#include <..\..\sources\textdraws\bustimer.inc>
#include <..\..\sources\textdraws\inventory.inc>
#include <..\..\sources\textdraws\info.inc>
#include <..\..\sources\textdraws\speedometer.inc>
#include <..\..\sources\textdraws\vehicles_shop.inc>
#include <..\..\sources\textdraws\iphone.inc>

#include <YSI_Coding\y_hooks>

TextDraws_OnGameModeInit()
{
	CreateSpeedometerTD();
	CreateVehiclesShopTD();
	CreateIPhoneTD();

	return true;
}
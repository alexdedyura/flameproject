#include <YSI_Coding\y_hooks>


hook OnGameModeInit()
{
	printf("MAPPING Bus All Station has loaded");
	
	// Bus All Station
	tmpobjid = CreateDynamicObject(1257, -2024.269653, -76.930557, 35.620323, -0.000009, -0.000167, -89.999076, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -2589.093994, 574.775390, 14.870946, 0.000012, -0.000161, 90.000793, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -2755.861328, 395.727996, 4.592825, -0.000003, -0.000176, -179.999023, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -2656.797607, 396.276428, 4.572824, -0.000009, -0.000153, 0.000890, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -2015.203002, 89.298858, 27.947509, -0.000003, -0.000176, -179.999023, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -1548.658081, 528.938415, 7.439695, -0.000009, -0.000153, 0.000891, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -2153.043457, 230.116592, 35.561874, -0.000003, -0.000176, -179.999008, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -2119.050781, -367.325042, 35.521598, -0.000009, -0.000159, 0.000891, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -1766.616088, 860.396423, 25.142822, 0.000003, -0.000161, 90.000816, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(19981, -1751.939208, 868.659179, 23.827812, -0.000007, 0.000007, -0.000007, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-95-percent", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18646, "matcolours", "grey-95-percent", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 18646, "matcolours", "grey-95-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(19483, -1750.874389, 868.633178, 25.937807, -0.000007, -0.000007, -89.999961, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterialText(tmpobjid, 0, "AT&T", 130, "Arial", 40, 1, 0xFFFFFFFF, 0x00000000, 0);
	tmpobjid = CreateDynamicObject(1257, -1705.070312, 794.873596, 25.154390, -0.000001, -0.000153, 0.000868, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1257, -2603.172119, 1340.574707, 7.495322, 0.000076, -0.000272, 134.000717, object_world, object_int, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 5, 18646, "matcolours", "grey-60-percent", 0x00000000);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tmpobjid = CreateDynamicObject(1257, -1625.777465, 722.149597, 14.860927, -0.000017, -0.000167, -89.999038, object_world, object_int, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(1257, -1603.683349, 861.008972, 7.939074, 0.000004, -0.000161, 90.000816, object_world, object_int, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(1257, -2407.482666, -616.601928, 132.761276, 0.000011, -0.000140, 45.000858, object_world, object_int, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(1569, -1747.837036, 869.145812, 24.085937, 0.000000, -0.000007, 179.999954, object_world, object_int, -1, 300.00, 300.00); 
	tmpobjid = CreateDynamicObject(1569, -1750.837280, 869.145812, 24.085937, 0.000000, 0.000007, 0.000000, object_world, object_int, -1, 300.00, 300.00); 

}	

hook OnPlayerConnect(playerid)
{
	// Баганная остановка
	RemoveBuildingForPlayer(playerid, 1257, -2292.979, 557.257, 35.070, 0.250);
	RemoveBuildingForPlayer(playerid, 1300, -2289.149, 556.820, 34.585, 0.250);
}		
#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
	// Популярные места
	CreateDynamicMapIcon(-1415.9719, -300.6621, 14.1484, 5, -1, 0, 0, -1, 300.0, -1); // Airport
	CreateDynamicMapIcon(-2022.2557, -105.0313, 36.1177, 36, -1, 0, 0, -1, 300.0, -1); // DMV
	CreateDynamicMapIcon(-1600.2570, 873.8332, 9.2298, 52, -1, 0, 0, -1, 300.0, -1); // National Bank

	// Автосалон
	CreateDynamicMapIcon(-1966.5798,293.9247,35.4687, 55, -1, 0, 0, -1, 300.0, -1); // Автосалон

	// Частные организации
	CreateDynamicMapIcon(-2067.6655,-859.9653,32.1719, 55, -1, 0, 0, -1, 300.0, -1); // Uber
	CreateDynamicMapIcon(-1954.8175,-866.2745,32.2266, 56, -1, 0, 0, -1, 300.0, -1); // Apple
	CreateDynamicMapIcon(-2002.9036,-1020.2568,32.1719, 27, -1, 0, 0, -1, 300.0, -1); // Foxconn
	CreateDynamicMapIcon(-1972.6044,-1020.3567,32.1719, 51, -1, 0, 0, -1, 300.0, -1); // FedEX

}
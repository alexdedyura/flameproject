#include <YSI_Coding\y_hooks>

#define MAX_PLAYER_PERSONAL_VEHICLES 3
#define MAX_PLAYER_SHARING_VEHICLES 3
#define MAX_PLAYER_VEHICLES 6

enum playerdata
{
	pID,
	pName[24],
	pPassword[32],
	pEmail[32],
	pGender,
	pAge,
	pDefault_Skin,
	pMoney,
	pBankMoney,
	pBankLastUse,
	pRegIP[16],
	pRegDate,
	pLastIP[16],
	pAdmin,
	pChatSettings[5],
	pWarns,
	pDeaths,
	pKills,
	pComment[32],
    pRPExp,
    pRPLevel,
    pDescText[128],
    pDescTime,
    pQuestProgress,

    // Не сохраняется в базе данных
    Float:pInvWeight,
    pRPAntiFloodTime,
    Text3D:pDescLabel,
    Text3D:pActionLabel,
    pVehicles[MAX_PLAYER_VEHICLES]
}
new pData[MAX_PLAYERS][playerdata];
new bool:Logged[MAX_PLAYERS];
new PlayerMapSlotsNames[MAX_PLAYERS][3][32];
new PlayerWeaponSlots[MAX_PLAYERS][13];

new Text3D:CarActionLabel[MAX_VEHICLES];

new LastCommandText[MAX_PLAYERS][128];

ClearPlayerData(playerid)
{
    format(LastCommandText[playerid], 128, "");
    pData[playerid][pRPAntiFloodTime] = 0;
    pData[playerid][pDescText] = EOS;
    pData[playerid][pDescTime] = 0;
    pData[playerid][pQuestProgress] = 0;
    pData[playerid][pRPExp] = 0;
    pData[playerid][pRPLevel] = 0;
    pData[playerid][pInvWeight] = 0.0;
    pData[playerid][pAge] = 0;

	pData[playerid][pID] = 0;
	pData[playerid][pName] = EOS;
	pData[playerid][pPassword] = EOS;
	pData[playerid][pEmail] = EOS;
	pData[playerid][pGender] = 0;
	pData[playerid][pDefault_Skin] = 0;
	pData[playerid][pMoney] = 0;
	pData[playerid][pBankMoney] = 0;
	pData[playerid][pBankLastUse] = 0;
	pData[playerid][pRegIP] = EOS;
	pData[playerid][pRegDate] = 0;
	pData[playerid][pLastIP] = EOS;
	pData[playerid][pAdmin] = 0;
	for(new i; i < 5; i++) pData[playerid][pChatSettings][i] = 0;
	pData[playerid][pWarns] = 0;
	pData[playerid][pDeaths] = 0;
	pData[playerid][pKills] = 0;
	pData[playerid][pComment] = EOS;
	Logged[playerid] = false;
	for(new i; i < 3; i++) format(PlayerMapSlotsNames[playerid][i], 32, "");
    for(new i; i < sizeof(PlayerWeaponSlots[]); i++) PlayerWeaponSlots[playerid][i] = -1;
	SetPVarInt(playerid, !"SpawnDelay", 1000);
    ClearInventory(playerid);
}

enum inventory_info
{
    invID, // ID предмета в инвентаре
    invParam, // Параметры предмета
    invAmount, // Количество предмета
    invInfo
}
new PlayerInventory[MAX_PLAYERS][15][inventory_info];

// open.mp: inventory UI state in native arrays instead of slow PVar hashmap lookups
new bool:InventoryShowed[MAX_PLAYERS];
new InventorySlot[MAX_PLAYERS];
new LastInventorySlot[MAX_PLAYERS];
new InventoryGiveTarget[MAX_PLAYERS];

ClearInventory(playerid)
{
    for(new i = 0; i < sizeof(PlayerInventory[]); i++)
    {
        PlayerInventory[playerid][i][invID] = 0;
        PlayerInventory[playerid][i][invParam] = 0;
        PlayerInventory[playerid][i][invAmount] = 0;
        PlayerInventory[playerid][i][invInfo] = 0;
    }
    InventoryShowed[playerid] = false;
    InventorySlot[playerid] = -1;
    LastInventorySlot[playerid] = 0;
    InventoryGiveTarget[playerid] = 0;
    return true;
}

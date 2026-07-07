#include <YSI_Coding\y_hooks>

#define MAX_DROPS 1024

enum drop_info
{
    drID,
    drParam,
    drAmount,

    Float:drPosX,
    Float:drPosY,
    Float:drPosZ,
    drInt,
    drVW,
    Text3D:drText,
    drObject
}
new DropInfo[MAX_DROPS][drop_info];
new TOTALDROPS = 0;

ItemDrop(playerid, slot)
{
    if(!CanItemBeDropped(PlayerInventory[playerid][slot][invID], PlayerInventory[playerid][slot][invParam]))
        return SendClientMessage(playerid, -1, !"Данный предмет не может быть выброшен!");
    
    new dropid = -1;
    for(new i = 0; i < sizeof(DropInfo); i++)
    {
        if(DropInfo[i][drID] == 0)
        {
            dropid = i;
            break;
        }
    }

    if(dropid > TOTALDROPS) TOTALDROPS = dropid;

    GetPlayerPos(playerid, DropInfo[dropid][drPosX], DropInfo[dropid][drPosY], DropInfo[dropid][drPosZ]);
    DropInfo[dropid][drInt] = GetPlayerInterior(playerid);
    DropInfo[dropid][drVW] = GetPlayerVirtualWorld(playerid);

    new itemid = PlayerInventory[playerid][slot][invID];
    new itemnum = PlayerInventory[playerid][slot][invParam];

    DropInfo[dropid][drID] = itemid;
    DropInfo[dropid][drParam] = itemnum;
    DropInfo[dropid][drAmount] = PlayerInventory[playerid][slot][invAmount];


    new str[128];
    GetItemName(itemid, itemnum, str);
    SendClientMessageEx(playerid, -1, "Вы выбросили предмет "FLAME_COLOR"'%s'"COLOR_WHITE".", str);
    format(str, sizeof(str), "%s\n"COLOR_WHITE"Чтобы поднять нажмите ALT", str);
    DropInfo[dropid][drText] = CreateDynamic3DTextLabel(str, COLOR_FLAME, DropInfo[dropid][drPosX], DropInfo[dropid][drPosY], DropInfo[dropid][drPosZ]-1.0, 5.0, _, _, 0, DropInfo[dropid][drVW], DropInfo[dropid][drInt]);
    DropInfo[dropid][drObject] = CreateDynamicObject(GetItemDropModel(itemid, itemnum), DropInfo[dropid][drPosX], DropInfo[dropid][drPosY], DropInfo[dropid][drPosZ]-0.99, 90.0, 0.0, 0.0, DropInfo[dropid][drVW], DropInfo[dropid][drInt]);
    ClearPlayerInventorySlot(playerid, slot);
    UpdateInventoryCell(playerid, slot);
    return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(!IsPlayerInAnyVehicle(playerid) && newkeys & KEY_WALK && !(oldkeys & KEY_WALK))
    {
        for(new i = 0; i <= TOTALDROPS; i++)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.5, DropInfo[i][drPosX], DropInfo[i][drPosY], DropInfo[i][drPosZ]) && DropInfo[i][drVW] == GetPlayerVirtualWorld(playerid) &&
                DropInfo[i][drInt] == GetPlayerInterior(playerid))
            {
                if(!CheckAddItemWeight(playerid, DropInfo[i][drID], DropInfo[i][drParam], DropInfo[i][drAmount])) 
                    return SendClientMessage(playerid, COLOR_ERROR, !"* Вам столько не унести!");
                new result = AddItemInInventory(playerid, DropInfo[i][drID], DropInfo[i][drParam], DropInfo[i][drAmount]);
                if(result == -1) return SendClientMessage(playerid, COLOR_ERROR, !"* У Вас нет пустых слотов в инвентаре!");

                new name[64];
                GetItemName(DropInfo[i][drID], DropInfo[i][drParam], name);
                SendClientMessageEx(playerid, -1, "Вы подобрали предмет "FLAME_COLOR"'%s'"COLOR_WHITE".", name);

                DropInfo[i][drID] = 0;
                DropInfo[i][drParam] = 0;
                DropInfo[i][drAmount] = 0;

                DropInfo[i][drPosX] = 0.0;
                DropInfo[i][drPosY] = 0.0;
                DropInfo[i][drPosZ] = 0.0;

                DropInfo[i][drInt] = 0;
                DropInfo[i][drVW] = 0;

                DestroyDynamic3DTextLabel(DropInfo[i][drText]);
                DestroyDynamicObject(DropInfo[i][drObject]);

                if(i == TOTALDROPS) TOTALDROPS--;
                return true;
            }
        }
    }
    return true;
}

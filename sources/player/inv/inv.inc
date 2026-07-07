#include <YSI_Coding\y_hooks>

#include <..\..\sources\player\inv\items.inc>
#include <..\..\sources\player\inv\show.inc>
#include <..\..\sources\player\inv\use.inc>
#include <..\..\sources\player\inv\drop.inc>


CMD:inventory(playerid)
{
	ShowPlayerInventory(playerid);
	return true;
}

CMD:givephone(playerid)
{
    if(IsItemInInventory(playerid, INV_ITEM_PHONE, INV_PHONE_PARAM)) return SendClientMessage(playerid, COLOR_ERROR, !"* У Вас уже есть смартфон.");
    new slot = AddItemInInventory(playerid, INV_ITEM_PHONE, INV_PHONE_PARAM, 1);
    if(slot == -1) return SendClientMessage(playerid, COLOR_ERROR, !"* Инвентарь заполнен!");
    PlayerInventory[playerid][slot][invInfo] = 0;
    if(InventoryShowed[playerid]) UpdateInventoryCell(playerid, slot);
    SendClientMessage(playerid, -1, !"Вы получили смартфон.");
    return true;
}

CMD:giveitem(playerid, params[])
{
    new itemid, itemnum, amount;
    if(sscanf(params, "iii", itemid, itemnum, amount)) return SendClientMessage(playerid, -1, "/getitem [itemid] [itemnum] [amount]");
    if(AddItemInInventory(playerid, itemid, itemnum, amount) == -1) return SendClientMessage(playerid, -1, "Инвентарь заполнен!");
    return true;
}

SaveInventory(playerid)
{
    SyncPlayerMoneyInventory(playerid);

    new ids[64], nums[96], amounts[200], infos[64], tmp[16];
    for(new i = 0; i < INV_SLOTS; i++)
    {
        format(tmp, sizeof(tmp), "%d ", PlayerInventory[playerid][i][invID]);     strcat(ids, tmp);
        format(tmp, sizeof(tmp), "%d ", PlayerInventory[playerid][i][invParam]);  strcat(nums, tmp);
        format(tmp, sizeof(tmp), "%d ", PlayerInventory[playerid][i][invAmount]); strcat(amounts, tmp);
        format(tmp, sizeof(tmp), "%d ", PlayerInventory[playerid][i][invInfo]);   strcat(infos, tmp);
    }

    new query[768];
    new fmt[] = "UPDATE `inventory` SET `item_ids` = '%s', `item_nums` = '%s', `item_amount` = '%s', `item_info` = '%s' WHERE `id` = '%d'";
    mysql_format(ConnectMySQL, query, sizeof(query), fmt, ids, nums, amounts, infos, pData[playerid][pID]);
    mysql_tquery(ConnectMySQL, query);
    return true;
}

IsItemInInventory(playerid, id, num)
{
    for(new i = 0; i < sizeof(PlayerInventory[]); i++)
    {
        if(PlayerInventory[playerid][i][invID] == id && PlayerInventory[playerid][i][invParam] == num)
            return true;
    }

    return false;
}

GetItemInInventorySlot(playerid, id, num)
{
    new result = -1;

    for(new i = 0; i < sizeof(PlayerInventory[]); i++)
    {
        if(PlayerInventory[playerid][i][invID] == id && PlayerInventory[playerid][i][invParam] == num)
        {
            result = i;
            break;
        }
    }   

    return result;
}
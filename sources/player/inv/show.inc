#include <YSI_Coding\y_hooks>

#define INVENTORY_INCLUDED

#define DEFAULT_CELL_COLOR 538976511
#define SELECTED_CELL_COLOR 1077953022

RefreshInventoryWeightText(playerid)
{
    RecalculateInventoryWeight(playerid);
    new str[16];
    format(str, sizeof(str), "%.02f/15.00КГ", pData[playerid][pInvWeight]);
    PlayerTextDrawSetString(playerid, InventoryPTD[playerid][15], RusText(str));
    return true;
}

ShowPlayerInventory(playerid)
{
    SyncPlayerMoneyInventory(playerid);
    InventoryShowed[playerid] = true;
    InventorySlot[playerid] = -1;
    for(new i = 0; i < sizeof(InventoryTD); i++) TextDrawShowForPlayer(playerid, InventoryTD[i]);
    RefreshInventoryWeightText(playerid);
    for(new i = 0; i <= 14; i ++) UpdateInventoryCell(playerid, i);
    for(new i = 0; i < sizeof(InventoryPTD[]); i++) PlayerTextDrawShow(playerid, InventoryPTD[playerid][i]);
    SelectTextDraw(playerid, 0xFFFFFFAA);
    return true;
}

// cancelSelect=false lets a caller switch straight into another textdraw-select
// UI (e.g. the phone) without dropping selection mode. Cancelling and then
// re-selecting in the same frame makes the client emit a stray
// OnPlayerClickTextDraw(INVALID_TEXT_DRAW), which would instantly close the
// freshly opened UI.
HidePlayerInventory(playerid, bool:cancelSelect = true)
{
    InventoryShowed[playerid] = false;
    InventorySelectCell(playerid, -1);
    for(new i = 0; i < sizeof(InventoryTD); i++) TextDrawHideForPlayer(playerid, InventoryTD[i]);
    for(new i = 0; i < sizeof(InventoryPTD[]); i++) PlayerTextDrawHide(playerid, InventoryPTD[playerid][i]);
    if(cancelSelect)
        CancelSelectTextDraw(playerid);
    return true;
}

RecalculateInventoryWeight(playerid)
{
    pData[playerid][pInvWeight] = 0.0;
    for(new i = 0; i < sizeof(PlayerInventory[]); i++)
    {
        new itemid = PlayerInventory[playerid][i][invID];
        new itemnum = PlayerInventory[playerid][i][invParam];
        new amount = PlayerInventory[playerid][i][invAmount];
        new Float:weight;
        GetItemWeight(itemid, itemnum, amount, weight);
        pData[playerid][pInvWeight] += weight;
    }
    return true;
}

InventorySelectCell(playerid, slot)
{
    new oldslot = InventorySlot[playerid];
    if(slot >= 0)
    {
        if(!PlayerInventory[playerid][slot][invID])
            return true;
        PlayerTextDrawHide(playerid, InventoryPTD[playerid][slot]);
        PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][slot], SELECTED_CELL_COLOR);
        PlayerTextDrawShow(playerid, InventoryPTD[playerid][slot]);
    }
    InventorySlot[playerid] = slot;
    if(oldslot >= 0) 
        InventoryUnSelectCell(playerid, oldslot);
    return true;
}

InventoryUnSelectCell(playerid, slot)
{
    if(slot >= 0)
    {
        PlayerTextDrawHide(playerid, InventoryPTD[playerid][slot]);
        PlayerTextDrawBackgroundColor(playerid, InventoryPTD[playerid][slot], DEFAULT_CELL_COLOR);
        PlayerTextDrawShow(playerid, InventoryPTD[playerid][slot]);
    }
    return true;
}

UpdateInventoryCell(playerid, slot)
{
    new itemid = PlayerInventory[playerid][slot][invID];
    new itemnum = PlayerInventory[playerid][slot][invParam];
    PlayerTextDrawHide(playerid, InventoryPTD[playerid][slot]);
    new Float:zoom;
    GetItemPreviewModelZoom(itemid, itemnum, zoom);
    new Float:rotX, Float:rotY, Float:rotZ;
    GetItemPreviewModelRot(itemid, itemnum, rotX, rotY, rotZ);
    PlayerTextDrawSetPreviewModel(playerid, InventoryPTD[playerid][slot], GetItemPreviewModel(itemid, itemnum));
    PlayerTextDrawSetPreviewRot(playerid, InventoryPTD[playerid][slot], rotX, rotY, rotZ, zoom);
    if(InventoryShowed[playerid]) PlayerTextDrawShow(playerid, InventoryPTD[playerid][slot]);
    return true;
}

INV_ClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(InventoryShowed[playerid] && playertextid >= InventoryPTD[playerid][0] && playertextid <= InventoryPTD[playerid][sizeof(InventoryPTD[])-1])
    {
        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
        for(new i = 0; i < 10; i++)
        {
            if(playertextid == InventoryPTD[playerid][i])
            {
                if(i == InventorySlot[playerid]) return InventorySelectCell(playerid, -1);
                else if(InventorySlot[playerid] >= 0) return MoveInventoryItem(playerid, InventorySlot[playerid], i), InventorySelectCell(playerid, -1);
                InventorySelectCell(playerid, i);
                return true;
            }
        }

        for(new i = 10; i < sizeof(InventoryPTD[])-1; i++)
        {
            if(playertextid == InventoryPTD[playerid][i])
            {
                if(PlayerInventory[playerid][i][invID]) RemoveItemFromActiveSlot(playerid, i);
                else InventorySelectCell(playerid, -1);
            }
        }

    }
    return true;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == INVALID_TEXT_DRAW && InventoryShowed[playerid]) return HidePlayerInventory(playerid);
    if(InventoryShowed[playerid])
    {
        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
        if(clickedid == InventoryTD[7]) return HidePlayerInventory(playerid);
        //else if(clickedid == InventoryTD[9]) return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Информация", !"Версия инвентаря: 0.1 Alpha\n1. Использование предметов\nЧтобы использовать предмет вы должны его выбрать, затем нажать 'Использовать'" , !"Закрыть", !"");
        new slot = InventorySlot[playerid];
        if(slot == -1) return true;
        new itemid = PlayerInventory[playerid][slot][invID];
        if(!itemid) return true;
        //new itemnum = PlayerInventory[playerid][slot][invParam];

        if(clickedid == InventoryTD[2])
        {
            ShowPlayerDialog(playerid, D_INV_GIVE, DIALOG_STYLE_INPUT, "Передать предмет", ""COLOR_WHITE"Введите "FLAME_COLOR"ID игрока"COLOR_WHITE", чтобы передать предмет", !"Далее", !"Отмена");
        }
        else if(clickedid == InventoryTD[3])
        {
            ShowInventoryRemove(playerid, slot);
        }
        else if(clickedid == InventoryTD[4])
        {
            PlayerUseItem(playerid, slot);
            InventorySelectCell(playerid, -1);
        }
        else if(clickedid == InventoryTD[5])
        {
            ItemDrop(playerid, slot);
            InventorySelectCell(playerid, -1);
        }
        else if(clickedid == InventoryTD[9])
        {
            ShowInventoryInfo(playerid, slot);
        }        
    }
    return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(GetPVarInt(playerid, !"HorizonQTE")) return true;

    if (PRESSED(KEY_YES))
    {
        ShowPlayerInventory(playerid);
    }

    if (PRESSED(KEY_NO))
    {
        return cmd_mm(playerid);
    }  

    return true;
}
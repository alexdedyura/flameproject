#include <YSI_Coding\y_hooks>

#define DEFAULT_MALE_SKIN 97
#define DEFAULT_FEMALE_SKIN 140

PlayerUseItem(playerid, slot)
{
    new itemid = PlayerInventory[playerid][slot][invID];
    new itemnum = PlayerInventory[playerid][slot][invParam];
    //new amount = PlayerInventory[playerid][slot][invAmount];
    switch(itemid)
    {
        case 1: // Документы
        {
            switch(itemnum)
            {
                case 1: ShowPlayerIDCard(playerid, playerid);
                case 2: ShowPlayerDriveLic(playerid, playerid);
                case 3: ShowPlayerGunLic(playerid, playerid);
                case 4: ShowPlayerBizLic(playerid, playerid);
            }
        }
        case INV_ITEM_PHONE:
        {
            ShowPlayerPhone(playerid, slot);
        }
        case 2: // Скины
        {
            new newslot = -1;
            for(new i = 10; i < 15; i++)
            {
                if(PlayerInventory[playerid][i][invID] == 0 || PlayerInventory[playerid][i][invID] == 2)
                {
                    newslot = i;
                    break;
                }
            }
            if(newslot == -1) return SendClientMessage(playerid, COLOR_ERROR, "* У Вас нет свободных активных слотов!");
            MoveInventoryItem(playerid, slot, newslot);
            pData[playerid][pDefault_Skin] = itemnum;
            UpdateBaseInt("accounts", "default_skin", itemnum, pData[playerid][pID]);
            SetPlayerSkin(playerid, itemnum);
            UpdateInventoryCell(playerid, newslot);
            UpdateInventoryCell(playerid, slot);
            new name[64];
            GetItemName(itemid, itemnum, name);
            SendClientMessageEx(playerid, -1, "Вы надели "FLAME_COLOR"'%s'"COLOR_WHITE".", name);
            SendClientMessage(playerid, -1, "Чтобы положить предмет обратно пропишите "FLAME_COLOR"/put_inventory"COLOR_WHITE" или нажмите по активной ячейке в инвентаре.");
            SendClientMessage(playerid, COLOR_FLAME, "(Предметы остаются активными, пока не положить их обратно)");
            LastInventorySlot[playerid] = newslot;
        }
        case 3: // Оружие
        {
            new newslot = -1;
            for(new i = 10; i < 15; i++)
            {
                if(PlayerInventory[playerid][i][invID] == 0)
                {
                    newslot = i;
                    break;
                }
            }
            if(newslot == -1) return SendClientMessage(playerid, COLOR_ERROR, "* У Вас нет свободных активных слотов!");
            MoveInventoryItem(playerid, slot, newslot);
            UpdatePlayerWeapons(playerid);
            UpdateInventoryCell(playerid, newslot);
            UpdateInventoryCell(playerid, slot);
            new name[64];
            GetItemName(itemid, itemnum, name);
            SendClientMessageEx(playerid, -1, "Вы взяли "FLAME_COLOR"'%s'"COLOR_WHITE" в руки.", name);
            SendClientMessage(playerid, -1, "Чтобы положить предмет обратно пропишите "FLAME_COLOR"/put_inventory"COLOR_WHITE" или нажмите по активной ячейке в инвентаре.");
            SendClientMessage(playerid, COLOR_FLAME, "(Предметы остаются активными, пока не положить их обратно)");
            LastInventorySlot[playerid] = newslot;
        }
    }
    return true;
}

AddItemInInventory(playerid, itemid, itemnum, amount, active = 1)
{
    if(IsMoneyInventoryItem(itemid, itemnum))
    {
        UpdatePlayerMoney(playerid, amount);
        return GetPlayerMoneyInventorySlot(playerid);
    }

    new slot = -1;
    new maxi = (active) ? 15 : 10;
    for(new i = 0; i < maxi; i++)
    {
        if(PlayerInventory[playerid][i][invID] == itemid && PlayerInventory[playerid][i][invParam] == itemnum)
        {
            slot = i;
            break;
        }
    }
    if(slot == -1)
    {
        for(new i = 0; i < 10; i++)
        {
            if(PlayerInventory[playerid][i][invID] == 0)
            {
                slot = i;
                break;
            }
        }
    }
    if(slot >= 0)
    {
        if(PlayerInventory[playerid][slot][invID] != itemid || PlayerInventory[playerid][slot][invParam] != itemnum)
            PlayerInventory[playerid][slot][invInfo] = 0;
        PlayerInventory[playerid][slot][invID] = itemid;
        PlayerInventory[playerid][slot][invParam] = itemnum;
        PlayerInventory[playerid][slot][invAmount] = amount;
    }
    return slot;
}

stock GetInventoryFreeSlot(playerid)
{
    new slot = -1;
    for(new i = 0; i < 10; i++)
    {
        if(PlayerInventory[playerid][i][invID] == 0)
        {
            slot = i;
            break;
        }
    }
    return slot;
}

MoveInventoryItem(playerid, oldslot, newslot)
{
    new temp;
    temp = PlayerInventory[playerid][oldslot][invID];
    PlayerInventory[playerid][oldslot][invID] = PlayerInventory[playerid][newslot][invID];
    PlayerInventory[playerid][newslot][invID] = temp;

    temp = PlayerInventory[playerid][oldslot][invParam];
    PlayerInventory[playerid][oldslot][invParam] = PlayerInventory[playerid][newslot][invParam];
    PlayerInventory[playerid][newslot][invParam] = temp;

    temp = PlayerInventory[playerid][oldslot][invAmount];
    PlayerInventory[playerid][oldslot][invAmount] = PlayerInventory[playerid][newslot][invAmount];
    PlayerInventory[playerid][newslot][invAmount] = temp;

    temp = PlayerInventory[playerid][oldslot][invInfo];
    PlayerInventory[playerid][oldslot][invInfo] = PlayerInventory[playerid][newslot][invInfo];
    PlayerInventory[playerid][newslot][invInfo] = temp;

    UpdateInventoryCell(playerid, oldslot);
    UpdateInventoryCell(playerid, newslot);
    return true;
}

ClearPlayerInventorySlot(playerid, slot, bool:force = false)
{
    if(!force && (IsProtectedDocumentItem(PlayerInventory[playerid][slot][invID], PlayerInventory[playerid][slot][invParam]) || IsMoneyInventoryItem(PlayerInventory[playerid][slot][invID], PlayerInventory[playerid][slot][invParam])))
        return false;

    PlayerInventory[playerid][slot][invID] = 0;
    PlayerInventory[playerid][slot][invParam] = 0;
    PlayerInventory[playerid][slot][invAmount] = 0;
    PlayerInventory[playerid][slot][invInfo] = 0;
    return true;
}

RemoveItemFromActiveSlot(playerid, slot)
{
    new itemid = PlayerInventory[playerid][slot][invID];
    new itemnum = PlayerInventory[playerid][slot][invParam];
    new amount = PlayerInventory[playerid][slot][invAmount];
    new newslot = AddItemInInventory(playerid, itemid, itemnum, amount, 0);
    if(newslot == -1) return SendClientMessage(playerid, COLOR_ERROR, !"* У Вас нет пустых слотов!");
    if(itemid == 2) // Одежда
    {
        pData[playerid][pDefault_Skin] = (pData[playerid][pGender]) ? DEFAULT_MALE_SKIN : DEFAULT_FEMALE_SKIN;
        UpdateBaseInt("accounts", "default_skin", itemnum, pData[playerid][pID]);
        SetPlayerSkin(playerid, pData[playerid][pDefault_Skin]);

    }
    ClearPlayerInventorySlot(playerid, slot);
    if(itemid == 3) // Оружие
    {
        UpdatePlayerWeapons(playerid);
    }
    UpdateInventoryCell(playerid, newslot);
    UpdateInventoryCell(playerid, slot);
    return true;
}

UpdatePlayerWeapons(playerid)
{
    for(new i; i < sizeof(PlayerWeaponSlots[]); i++) PlayerWeaponSlots[playerid][i] = -1;
    ResetPlayerWeapons(playerid);
    for(new i = 10; i < 15; i++)
    {
        if(PlayerInventory[playerid][i][invID] == 3)
        {
            GivePlayerWeapon(playerid, PlayerInventory[playerid][i][invParam], PlayerInventory[playerid][i][invAmount]);
            PlayerWeaponSlots[playerid][GetInvWeaponSlot(PlayerInventory[playerid][i][invParam])] = i;
        }
    }
    return true;
}

CheckAddItemWeight(playerid, itemid, itemnum, amount)
{
    new Float:weight;
    GetItemWeight(itemid, itemnum, amount, weight);
    if(pData[playerid][pInvWeight] + weight > 15.0) return false;
    return true;
}

ShowInventoryInfo(playerid, slot)
{
    new desc[128];
    new itemid = PlayerInventory[playerid][slot][invID];
    new itemnum = PlayerInventory[playerid][slot][invParam];
    new amount = PlayerInventory[playerid][slot][invAmount];
    GetItemDescription(itemid, itemnum, desc);
    new name[64];
    GetItemName(itemid, itemnum, name);

    new Float:weight;
    GetItemWeight(itemid, itemnum, amount, weight);

    new string[256];
    if(IsMoneyInventoryItem(itemid, itemnum))
    {
        format(string, sizeof(string), ""COLOR_WHITE"%s\nСумма: "FLAME_COLOR"$%s\n"COLOR_WHITE"Вес: "FLAME_COLOR"%.02f"COLOR_WHITE" кг.", desc, convertNumber(amount), weight);
    }
    else
    {
        format(string, sizeof(string), ""COLOR_WHITE"%s\nКоличество: "FLAME_COLOR"%i"COLOR_WHITE" шт.\nВес: "FLAME_COLOR"%.02f"COLOR_WHITE" кг.", desc, amount, weight);
    }
    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, name, string, !"OK", !"");
}

ShowInventoryRemove(playerid, slot)
{
    if(!CanItemBeDeleted(PlayerInventory[playerid][slot][invID], PlayerInventory[playerid][slot][invParam], playerid))
        return SendClientMessage(playerid, -1, !"Данный предмет не может быть удалён!");
    new name[64];
    GetItemName(PlayerInventory[playerid][slot][invID], PlayerInventory[playerid][slot][invParam], name);
    ClearPlayerInventorySlot(playerid, slot);
    UpdateInventoryCell(playerid, slot);
    SendClientMessageEx(playerid, -1, "Вы удалили предмет "FLAME_COLOR"'%s'"COLOR_WHITE".", name);
    return true;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == D_INV_GIVE)
    {
        if(!response) return true;
        new targetid = strval(inputtext);
        new bool:success = false;
        if(!IsPlayerConnected(targetid)) SendClientMessage(playerid, COLOR_ERROR, "Данный игрок не подключён!");
        else if(!Logged[targetid]) SendClientMessage(playerid, COLOR_ERROR, "Данный игрок не авторизован!");
        else if(playerid == targetid)
            SendClientMessage(playerid, COLOR_ERROR, "Нельзя передать предмет самому себе!");
        else if(!DistancePlayer(10.0, playerid, targetid)) SendClientMessage(playerid, COLOR_ERROR, !"* Данный игрок не рядом с Вами!");
        else success = true;
        if(!success) return ShowPlayerDialog(playerid, D_INV_GIVE, DIALOG_STYLE_INPUT, "Передать предмет", ""COLOR_WHITE"Введите "FLAME_COLOR"ID игрока"COLOR_WHITE", чтобы передать предмет", !"Далее", !"Отмена");

        new slot = InventorySlot[playerid];
        new itemid = PlayerInventory[playerid][slot][invID];
        new itemnum = PlayerInventory[playerid][slot][invParam];
        new amount = PlayerInventory[playerid][slot][invAmount];
        if(IsMoneyInventoryItem(itemid, itemnum))
        {
            InventoryGiveTarget[playerid] = targetid;
            new string[160];
            format(string, sizeof(string), ""COLOR_WHITE"Получатель: "FLAME_COLOR"%s\n"COLOR_WHITE"Доступно наличными: "FLAME_COLOR"$%s\n\n"COLOR_WHITE"Введите сумму передачи.", pData[targetid][pName], convertNumber(pData[playerid][pMoney]));
            return ShowPlayerDialog(playerid, D_INV_SETTINGS, DIALOG_STYLE_INPUT, "Передать деньги", string, !"Далее", !"Отмена");
        }
        if(IsProtectedDocumentItem(itemid, itemnum)) return SendClientMessage(playerid, COLOR_ERROR, !"* Документы, лицензии и банковскую карту нельзя передать другому игроку.");
        if(!CheckAddItemWeight(targetid, itemid, itemnum, amount)) return SendClientMessage(playerid, COLOR_ERROR, "* У данного игрока недостаточно места!");
        new result = AddItemInInventory(targetid, itemid, itemnum, amount);
        if(result == -1) return SendClientMessage(playerid, COLOR_ERROR, "* У данного игрока недостаточно места!");
        UpdateInventoryCell(targetid, result);
        new name[64];
        GetItemName(itemid, itemnum, name);
        ClearPlayerInventorySlot(playerid, slot);
        UpdateInventoryCell(playerid, slot);

        SendClientMessageEx(playerid, -1, "Вы передали "FLAME_COLOR"%s"COLOR_WHITE" предмет "FLAME_COLOR"'%s'"COLOR_WHITE".", pData[targetid][pName], name);
        SendClientMessageEx(targetid, -1, ""FLAME_COLOR"'%s'"COLOR_WHITE" передал Вам предмет "FLAME_COLOR"%s"COLOR_WHITE".", pData[playerid][pName], name);
        return true;
    }
    else if(dialogid == D_INV_SETTINGS)
    {
        if(!response) return true;

        new slot = InventorySlot[playerid];
        new itemid = PlayerInventory[playerid][slot][invID];
        new itemnum = PlayerInventory[playerid][slot][invParam];
        if(!IsMoneyInventoryItem(itemid, itemnum)) return true;

        new targetid = InventoryGiveTarget[playerid];
        if(!IsPlayerConnected(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Данный игрок не подключён!");
        if(!Logged[targetid]) return SendClientMessage(playerid, COLOR_ERROR, "Данный игрок не авторизован!");
        if(playerid == targetid) return SendClientMessage(playerid, COLOR_ERROR, "Нельзя передать деньги самому себе!");
        if(!DistancePlayer(10.0, playerid, targetid)) return SendClientMessage(playerid, COLOR_ERROR, !"* Данный игрок не рядом с Вами!");

        new money;
        if(sscanf(inputtext, "i", money)) return SendClientMessage(playerid, COLOR_ERROR, !"* Сумма указана неверно.");
        if(money <= 0) return SendClientMessage(playerid, COLOR_ERROR, !"* Сумма должна быть положительной.");
        if(pData[playerid][pMoney] < money) return SendClientMessage(playerid, COLOR_ERROR, !"* У Вас недостаточно наличных.");
        if(!CanReceiveInvMoney(targetid, money)) return SendClientMessage(playerid, COLOR_ERROR, !"* У данного игрока недостаточно места под деньги.");

        UpdatePlayerMoney(playerid, -money);
        UpdatePlayerMoney(targetid, money);

        new sender_slot = GetPlayerMoneyInventorySlot(playerid);
        if(sender_slot != -1) UpdateInventoryCell(playerid, sender_slot);
        new target_slot = GetPlayerMoneyInventorySlot(targetid);
        if(target_slot != -1) UpdateInventoryCell(targetid, target_slot);

        SendClientMessageEx(playerid, -1, "Вы передали "FLAME_COLOR"%s"COLOR_WHITE" наличные в размере "FLAME_COLOR"$%s"COLOR_WHITE".", pData[targetid][pName], convertNumber(money));
        SendClientMessageEx(targetid, -1, ""FLAME_COLOR"'%s'"COLOR_WHITE" передал Вам "FLAME_COLOR"$%s"COLOR_WHITE" наличными.", pData[playerid][pName], convertNumber(money));
        return true;
    }
/*  else if(dialogid == D_INV_SETTINGS)
    {
        if(!response) return true;
        new slot = InventorySlot[playerid];
        switch(listitem)
        {
            case 0: // Информация
            {
                new desc[128];
                new itemid = PlayerInventory[playerid][slot][invID];
                new itemnum = PlayerInventory[playerid][slot][invParam];
    new amount = PlayerInventory[playerid][slot][invAmount];
                GetItemDescription(itemid, itemnum, desc);
                new name[64];
                GetItemName(itemid, itemnum, name);

                new Float:weight;
                GetItemWeight(itemid, itemnum, amount, weight);

                new string[256];
                format(string, sizeof(string), ""COLOR_WHITE"%s\nКоличество: %i шт.\nВес: %.02f", desc, amount, weight);
                ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, name, string, !"OK", !"");
            }
            case 1: // Удалить
            {
                new name[64];
                GetItemName(PlayerInventory[playerid][slot][invID], PlayerInventory[playerid][slot][invParam], name);
                ClearPlayerInventorySlot(playerid, slot);
                UpdateInventoryCell(playerid, slot);
                SendClientMessageEx(playerid, -1, "Вы удалили предмет '%s'.", name);
            }
        }
    } */
    return true;
}

hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(weaponid >= 16 && weaponid <= 43)
    {
        new slot = PlayerWeaponSlots[playerid][GetInvWeaponSlot(weaponid)];
        if(slot == -1) return true;
        if(PlayerInventory[playerid][slot][invAmount] <= 0)
        {
            ClearPlayerInventorySlot(playerid, slot);
            UpdateInventoryCell(playerid, slot);
            UpdatePlayerWeapons(playerid);
        }
        PlayerInventory[playerid][slot][invAmount]--;
    }
    return true;
}

CMD:put_inventory(playerid)
{
    if(LastInventorySlot[playerid] < 10) return true;
    new slot = LastInventorySlot[playerid];
    if(PlayerInventory[playerid][slot][invID] == 0) return true;
    RemoveItemFromActiveSlot(playerid, slot);
    return true;
}

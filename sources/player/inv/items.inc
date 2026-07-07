#include <YSI_Coding\y_hooks>

#define INV_ITEM_MONEY 5
#define INV_MONEY_PARAM 1
#define INV_ITEM_PHONE 6
#define INV_PHONE_PARAM 1
#define MONEY_WEIGHT_DOLLARS_PER_KG 100000.0

#define INV_SLOTS 15           // total inventory cells (0..14)
#define INV_BAG_SLOTS 10       // backpack cells (0..9)
#define INV_ACTIVE_START 10    // first active/equipped cell (10..14)


stock IsMoneyInventoryItem(category, num)
{
    return (category == INV_ITEM_MONEY && num == INV_MONEY_PARAM);
}

stock IsPhoneInventoryItem(category, num)
{
    return (category == INV_ITEM_PHONE && num == INV_PHONE_PARAM);
}

stock GetPlayerMoneyInventorySlot(playerid)
{
    for(new i = 0; i < sizeof(PlayerInventory[]); i++)
    {
        if(IsMoneyInventoryItem(PlayerInventory[playerid][i][invID], PlayerInventory[playerid][i][invParam]))
            return i;
    }
    return -1;
}

stock GetMoneyFreeInvSlot(playerid)
{
    for(new i = 0; i < 10; i++)
    {
        if(PlayerInventory[playerid][i][invID] == 0)
            return i;
    }
    return -1;
}

stock SyncPlayerMoneyInventory(playerid)
{
    new slot = -1;
    for(new i = 0; i < sizeof(PlayerInventory[]); i++)
    {
        if(IsMoneyInventoryItem(PlayerInventory[playerid][i][invID], PlayerInventory[playerid][i][invParam]))
        {
            if(slot == -1) slot = i;
            else
            {
                ClearPlayerInventorySlot(playerid, i, true);
                if(InventoryShowed[playerid]) UpdateInventoryCell(playerid, i);
            }
        }
    }

    if(pData[playerid][pMoney] <= 0)
    {
        if(slot != -1)
        {
            ClearPlayerInventorySlot(playerid, slot, true);
            if(InventoryShowed[playerid]) UpdateInventoryCell(playerid, slot);
        }
        return true;
    }

    if(slot == -1)
    {
        slot = GetMoneyFreeInvSlot(playerid);
        if(slot == -1) return false;
    }

    PlayerInventory[playerid][slot][invID] = INV_ITEM_MONEY;
    PlayerInventory[playerid][slot][invParam] = INV_MONEY_PARAM;
    PlayerInventory[playerid][slot][invAmount] = pData[playerid][pMoney];

    if(InventoryShowed[playerid]) UpdateInventoryCell(playerid, slot);
    return true;
}

stock CanReceiveInvMoney(playerid, amount)
{
    if(amount <= 0) return false;
    SyncPlayerMoneyInventory(playerid);
    if(pData[playerid][pMoney] <= 0 && GetPlayerMoneyInventorySlot(playerid) == -1 && GetMoneyFreeInvSlot(playerid) == -1)
        return false;

    new Float:weight = float(amount) / MONEY_WEIGHT_DOLLARS_PER_KG;
    RecalculateInventoryWeight(playerid);
    if(pData[playerid][pInvWeight] + weight > 15.0) return false;
    return true;
}
GetItemName(category, num, name[], maxname = sizeof name)
{
    new n[64];
    switch(category)
    {
        case 1: // Документы
        {
            switch(num)
            {
                case 1: n = "ID карта";
                case 2: n = "Лицензия на вождение";
                case 3: n = "Лицензия на ношение оружия";
                case 4: n = "Лицензия на владение бизнесом";
                case 5: n = "Банковская карта";
            }
        }
        case 2: // Одежда
        {
            format(n, sizeof(n), "Одежда №%i", num);
        }
        case 3: // Оружие
        {
            format(n, sizeof(n), "%s", WEAPON_NAMES[num]);
        }
        case 4: // Ключи от тс
        {
            format(n, sizeof(n), "Ключи от транспорта №%i", num);
        }
        case INV_ITEM_MONEY: n = "Наличные";
        case INV_ITEM_PHONE: n = "Смартфон";
    }
    format(name, maxname, "%s", n);
    return true;
}

GetItemWeight(category, num, amount, &Float:w)
{
    switch(category)
    {
        case 1: // Документы
        {
            switch(num)
            {
                case 1: w = 0.0; // ID карта
                case 2: w = 0.0; // Лицензия на вождение
                case 3: w = 0.0; // Лицензия на ношение оружия
                case 4: w = 0.0; // Лицензия на владение бизнесом
                case 5: w = 0.0; // Банковская карта
            }
        }
        case 2: // Одежда
        {
            w = 1.0; 
        }
        case 3: // Оружие
        {
            switch(num)
            {
                case 1: w = 2.0;
                default: w = 3.0;
            }
        }
        case 4: // Ключи от тс
        {
            w = 0.0;
        }
        case INV_ITEM_MONEY: w = float(amount) / MONEY_WEIGHT_DOLLARS_PER_KG;
        case INV_ITEM_PHONE: w = 0.2;
    }
    if(category != 3 && category != INV_ITEM_MONEY && category != INV_ITEM_PHONE)
        w = w * amount;
    return true;
}

GetItemDescription(category, num, desc[], maxdesc = sizeof desc)
{
    new d[128];
    switch(category)
    {
        case 1: // Документы
        {
            switch(num)
            {
                case 1: d = "ID карта";
                case 5: d = "Банковская карта";
                default: d = "Документы";
            }
        }
        case 2: // Одежда
        {
            d = "Одежда";
        }
        case 3: // Оружие
        {
            d = "Оружие";
        }
        case 4: // Ключи от тс
        {
            d = "Ключи от транспорта";
        }
        case INV_ITEM_MONEY: d = "Наличные деньги";
        case INV_ITEM_PHONE: d = "Смартфон с приложениями, SMS и вызовом автомобиля";
    }
    format(desc, maxdesc, "%s", d);
    return true;
}

GetInvWeaponModel(num)
{
    new m = 4637;
    switch(num)
    {
        case 1: m = 331;
        case 2: m = 333;
        case 3: m = 334;
        case 4: m = 335;
        case 5: m = 336;
        case 6: m = 337;
        case 7: m = 338;
        case 8: m = 339;
        case 9: m = 341;
        case 10: m = 321;
        case 11: m = 322;
        case 12: m = 323;
        case 13: m = 324;
        case 14: m = 325;
        case 15: m = 326;
        case 16: m = 342;
        case 17: m = 343;
        case 18: m = 344;
        case 22: m = 346;
        case 23: m = 347;
        case 24: m = 348;
        case 25: m = 349;
        case 26: m = 350;
        case 27: m = 351;
        case 28: m = 352;
        case 29: m = 353;
        case 30: m = 355;
        case 31: m = 356;
        case 32: m = 372;
        case 33: m = 357;
        case 34: m = 358;
        case 35: m = 359;
        case 36: m = 360;
        case 37: m = 361;
        case 38: m = 362;
        case 39: m = 363;
        case 40: m = 364;
        case 41: m = 365;
        case 42: m = 366;
        case 43: m = 367;
        case 44: m = 368;
        case 45: m = 368;
        case 46: m = 371;
    }
    return m;
}

GetItemPreviewModel(category, num)
{
    new m = 4637;
    switch(category)
    {
        case 1: // Документы
        {
            switch(num)
            {
                case 1: m = 1581;
                case 2: m = 2684;
                case 3: m = 2684;
                case 4: m = 2684;
                case 5: m = 19792;
            }
        }
        case 2: // Одежда
        {
            m = num;
        }
        case 3: // Оружие
        {
            m = GetInvWeaponModel(num);
        }
        case 4: // Ключи от тс
        {
            m = 11746;
        }
        case INV_ITEM_MONEY: m = 1212;
        case INV_ITEM_PHONE: m = 18867;
    }
    return m;
}

GetItemDropModel(category, num)
{
    new m = 4637;
    switch(category)
    {
        case 1: // Документы
        {
            switch(num)
            {
                case 1: m = 1581;
                case 2: m = 2684;
                case 3: m = 2684;
                case 4: m = 2684;  
                case 5: m = 19792;
            }
        }
        case 2: // Одежда
        {
            m = 2384;
        }
        case 3: // Оружие
        {
            m = GetInvWeaponModel(num);
        }
        case INV_ITEM_MONEY: m = 1212;
        case INV_ITEM_PHONE: m = 18867;
    }
    return m;
}

GetItemPreviewModelZoom(category, num, &Float:m)
{
    #pragma unused num
    m = 1.0;
    switch(category)
    {
        case 1: // Документы
        {
            switch(num)
            {
                case 2:  m = 1.0;
                case 3:  m = 1.0;
                case 4:  m = 1.0;
                case 5:  m = 0.5;
            }
        }
        case 3: // Оружие
        {
            m = 2.0;
        }
    }
    return true;
}

GetItemPreviewModelRot(category, num, &Float:rotX, &Float:rotY, &Float:rotZ)
{
    #pragma unused rotZ
    switch(category)
    {
        case 1: // Документы
        {
            switch(num)
            {
                case 1: // ID карта
                {
                    rotX = 180.0;
                    rotY = 180.0;
                }
                case 5: // Bank Card
                {
                    rotX = -90.0;
                }
            }
        }
    }
    return true;
}

stock IsProtectedDocumentItem(cat, num)
{
    return (cat == 1 && num >= 1 && num <= 5);
}

CanItemBeDropped(cat, num)
{
    if(IsProtectedDocumentItem(cat, num))
        return false;

    if(IsMoneyInventoryItem(cat, num))
        return false;

    if(IsPhoneInventoryItem(cat, num))
        return false;

    if(cat == 4)
        return false;

    return true;
}

CanItemBeDeleted(cat, num, playerid = -1)
{
    if(IsProtectedDocumentItem(cat, num))
        return false;

    if(IsMoneyInventoryItem(cat, num))
        return false;

    if(IsPhoneInventoryItem(cat, num))
        return false;

    if(cat == 4 && IsValidVehicle(GetVehicleByID(num)) && IsPlayerVehicleOwner(playerid, GetVehicleByID(num)))
        return false;

    return true;
}

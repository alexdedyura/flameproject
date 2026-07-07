#include <YSI_Coding\y_hooks>

#define POS_BANK_PICKUP -1660.9996,950.2525,693.4631
#define VW_BANK 15 //15
#define INT_BANK 3 //3

#define BANK_TRANSACTION_DEPOSIT 0
#define BANK_TRANSACTION_WITHDRAW 1
#define BANK_TRANSACTION_TRANSFER_OUT 2
#define BANK_TRANSACTION_TRANSFER_IN 3
#define BANK_TRANSACTION_INTEREST 4

#define BANK_INTEREST_SETTING_NAME "deposit_interest_rate"

new PlayerChosenTransferID[MAX_PLAYERS];
new PlayerChosenTransferName[MAX_PLAYERS][MAX_PLAYER_NAME];
new Float:BankInterestRate;

new const BankTransactionNames[][] =
{
    "Пополнение",
    "Снятие",
    "Перевод",
    "Получение",
    "Проценты"
};

stock ShowBankMainDialog(playerid)
{
    new string[256];
    format(string, sizeof(string),
        ""FLAME_COLOR"1."COLOR_WHITE" Информация о счете\n\
        "FLAME_COLOR"2."COLOR_WHITE" Пополнить счет\n\
        "FLAME_COLOR"3."COLOR_WHITE" Снять со счета\n\
        "FLAME_COLOR"4."COLOR_WHITE" Перевести игроку\n\
        "FLAME_COLOR"5."COLOR_WHITE" История транзакций");

    ShowPlayerDialog(playerid, D_BANK_MAIN, DIALOG_STYLE_LIST, !"Банковские операции", string, !"Далее", !"Закрыть");
    return true;
}

stock ShowBankAccountInfoDialog(playerid)
{
    new last_use[18] = "не использовалась";
    if(pData[playerid][pBankLastUse] > 0)
    {
        format(last_use, sizeof(last_use), "%s", dateMX("%dd.%mm.%yyyy, %hh:%ii", pData[playerid][pBankLastUse]));
    }

    new string[256];
    format(string, sizeof(string),
        ""COLOR_WHITE"Баланс счета: "FLAME_COLOR"$%s\n\
        "COLOR_WHITE"Процентная ставка: "FLAME_COLOR"%.2f%%\n\
        "COLOR_WHITE"Последнее использование карты: "FLAME_COLOR"%s",
        convertNumber(pData[playerid][pBankMoney]), BankInterestRate, last_use);

    ShowPlayerDialog(playerid, D_BANK_BALANCE, DIALOG_STYLE_MSGBOX, !"Информация о счете", string, !"Назад", !"");
    return true;
}

stock HasPlayerBankCard(playerid)
{
    return IsItemInInventory(playerid, 1, 5);
}

stock ShowBankOpenAccountDialog(playerid)
{
    ShowPlayerDialog(playerid, D_BANK_OPEN_ACCOUNT, DIALOG_STYLE_MSGBOX, !"Национальный банк",
        ""COLOR_WHITE"Вы хотите открыть счет в национальном банке?", !"Да", !"Нет");
    return true;
}

stock BankUpdateLastCardUse(playerid)
{
    pData[playerid][pBankLastUse] = gettime();
    UpdateBaseInt("accounts", "bank_last_use", pData[playerid][pBankLastUse], pData[playerid][pID]);
    return true;
}


stock BankCheckAccess(playerid)
{
    if(!HasPlayerBankCard(playerid))
    {
        SendClientMessage(playerid, COLOR_ERROR, !"* Для доступа к банку необходима банковская карта в инвентаре.");
        return false;
    }
    return true;
}

stock GivePlayerBankCard(playerid)
{
    if(HasPlayerBankCard(playerid)) return true;

    new slot = AddItemInInventory(playerid, 1, 5, 1);
    if(slot == -1)
    {
        SendClientMessage(playerid, COLOR_ERROR, !"* В инвентаре нет свободного слота для банковской карты.");
        return false;
    }

    UpdateInventoryCell(playerid, slot);
    SaveInventory(playerid);
    SendClientMessage(playerid, COLOR_GREEN, !"* Вы открыли счет в национальном банке и получили банковскую карту.");
    Quest_OnPlayerGetBankCard(playerid);
    return true;
}

stock ShowBankDepositDialog(playerid)
{
    new string[192];
    format(string, sizeof(string),
        ""COLOR_WHITE"Введите сумму для пополнения банковского счета.\n\n\
        "COLOR_WHITE"Доступно наличными: "FLAME_COLOR"$%s",
        convertNumber(pData[playerid][pMoney]));

    ShowPlayerDialog(playerid, D_BANK_DEPOSIT, DIALOG_STYLE_INPUT, !"Пополнение счета", string, !"Далее", !"Назад");
    return true;
}

stock ShowBankWithdrawDialog(playerid)
{
    new string[192];
    format(string, sizeof(string),
        ""COLOR_WHITE"Введите сумму для снятия с банковского счета.\n\n\
        "COLOR_WHITE"Доступно на счете: "FLAME_COLOR"$%s",
        convertNumber(pData[playerid][pBankMoney]));

    ShowPlayerDialog(playerid, D_BANK_WITHDRAW, DIALOG_STYLE_INPUT, !"Снятие со счета", string, !"Далее", !"Назад");
    return true;
}

stock ShowBankTransferNameDialog(playerid)
{
    ShowPlayerDialog(playerid, D_BANK_TRANSFER_PLAYER_ID, DIALOG_STYLE_INPUT, !"Банковский перевод",
        ""COLOR_WHITE"Введите точный никнейм игрока, которому хотите перевести деньги.",
        !"Далее", !"Назад");
    return true;
}

stock ShowBankTransferAmountDialog(playerid)
{
    new string[256];
    format(string, sizeof(string),
        ""COLOR_WHITE"Получатель: "FLAME_COLOR"%s\n\
        "COLOR_WHITE"Доступно на счете: "FLAME_COLOR"$%s\n\n\
        "COLOR_WHITE"Введите сумму перевода.",
        PlayerChosenTransferName[playerid], convertNumber(pData[playerid][pBankMoney]));

    ShowPlayerDialog(playerid, D_BANK_TRANSFER_AMOUNT, DIALOG_STYLE_INPUT, !"Банковский перевод", string, !"Далее", !"Назад");
    return true;
}

stock ShowBankErrorDialog(playerid, const message[])
{
    new string[256];
    format(string, sizeof(string), ""COLOR_WHITE"%s", message);
    ShowPlayerDialog(playerid, D_BANK_ERROR, DIALOG_STYLE_MSGBOX, !"Банковские операции", string, !"Назад", !"");
    return true;
}

stock ShowBankSuccessDialog(playerid, const message[])
{
    new string[256];
    format(string, sizeof(string), ""COLOR_WHITE"%s", message);
    ShowPlayerDialog(playerid, D_BANK_SUCCESS, DIALOG_STYLE_MSGBOX, !"Банковские операции", string, !"Назад", !"");
    return true;
}

stock ShowBankHistoryDialog(playerid)
{
    new query[256], Cache:result;
    new __ms12[] = "SELECT Type, Amount, RelatedName, FROM_UNIXTIME(Date, '%%d/%%m/%%Y %%H:%%i') as TransactionDate FROM bank_transactions WHERE AccountID=%d ORDER BY Date DESC, ID DESC LIMIT 15";
    mysql_format(ConnectMySQL, query, sizeof(query), __ms12, pData[playerid][pID]);
    result = mysql_query(ConnectMySQL, query);

    new rows = cache_num_rows();
    if(!rows)
    {
        cache_delete(result);
        return ShowBankErrorDialog(playerid, "История банковских операций пуста.");
    }

    new list[2048], related_name[MAX_PLAYER_NAME], date[20], type, amount;
    format(list, sizeof(list), "Операция\tСумма\tИгрок\tДата\n");

    for(new i; i < rows; i++)
    {
        type = cache_get_field_content_int(i, "Type");
        if(type < 0 || type >= sizeof(BankTransactionNames)) type = 0;
        amount = cache_get_field_content_int(i, "Amount");
        cache_get_field_content(i, "RelatedName", related_name, ConnectMySQL, MAX_PLAYER_NAME);
        cache_get_field_content(i, "TransactionDate", date, ConnectMySQL, 20);

        if(!strlen(related_name)) format(related_name, sizeof(related_name), "-");
        format(list, sizeof(list), "%s"FLAME_COLOR"%s"COLOR_WHITE"\t$%s\t%s\t%s\n",
            list, BankTransactionNames[type], convertNumber(amount), related_name, date);
    }

    ShowPlayerDialog(playerid, D_BANK_HISTORY, DIALOG_STYLE_TABLIST_HEADERS, !"История транзакций", list, !"Назад", !"");
    cache_delete(result);
    return true;
}

stock BankCreateTables()
{
    new Cache:result;
    new __ms11[] = "ALTER TABLE `accounts` ADD COLUMN IF NOT EXISTS `bank_last_use` int(11) NOT NULL DEFAULT 0";
    result = mysql_query(ConnectMySQL, __ms11);
    cache_delete(result);

    new __ms10[] = "CREATE TABLE IF NOT EXISTS `bank_transactions` (\
        `ID` int(11) NOT NULL AUTO_INCREMENT,\
        `AccountID` int(11) NOT NULL,\
        `Type` tinyint(4) NOT NULL,\
        `Amount` int(11) NOT NULL,\
        `RelatedAccountID` int(11) NOT NULL DEFAULT 0,\
        `RelatedName` varchar(24) NOT NULL DEFAULT '',\
        `Date` int(11) NOT NULL,\
        PRIMARY KEY (`ID`),\
        KEY `account_date` (`AccountID`,`Date`)\
    ) ENGINE=MyISAM DEFAULT CHARSET=utf8;";
    result = mysql_query(ConnectMySQL, __ms10);
    cache_delete(result);

    new __ms9[] = "CREATE TABLE IF NOT EXISTS `bank_settings` (`ID` int(11) NOT NULL, `SettingName` varchar(32) NOT NULL DEFAULT '', `InterestRate` float NOT NULL DEFAULT 0, PRIMARY KEY (`ID`)) ENGINE=MyISAM DEFAULT CHARSET=utf8;";
    result = mysql_query(ConnectMySQL, __ms9);
    cache_delete(result);

    new __ms8[] = "ALTER TABLE `bank_settings` ADD COLUMN IF NOT EXISTS `SettingName` varchar(32) NOT NULL DEFAULT ''";
    result = mysql_query(ConnectMySQL, __ms8);
    cache_delete(result);

    new __ms7[] = "INSERT INTO `bank_settings` (`ID`, `SettingName`, `InterestRate`) VALUES (1, '"BANK_INTEREST_SETTING_NAME"', 0) ON DUPLICATE KEY UPDATE `SettingName` = '"BANK_INTEREST_SETTING_NAME"'";
    result = mysql_query(ConnectMySQL, __ms7);
    cache_delete(result);

    new __ms6[] = "SELECT InterestRate FROM `bank_settings` WHERE `SettingName` = '"BANK_INTEREST_SETTING_NAME"' LIMIT 1";
    result = mysql_query(ConnectMySQL, __ms6);
    if(cache_num_rows()) BankInterestRate = cache_get_field_content_float(0, "InterestRate");
    cache_delete(result);
    return true;
}

stock BankLogTransaction(account_id, type, amount, related_account_id = 0, const related_name[] = "")
{
    new query[256];
    new __ms5[] = "INSERT INTO bank_transactions SET AccountID=%d, Type=%d, Amount=%d, RelatedAccountID=%d, RelatedName='%e', Date=UNIX_TIMESTAMP()";
    mysql_format(ConnectMySQL, query, sizeof(query), __ms5, account_id, type, amount, related_account_id, related_name);
    mysql_tquery(ConnectMySQL, query);
    return true;
}

stock BankFindOnlinePlayerByAccount(account_id)
{
    foreach(new i : Player)
    {
        if(Logged[i] && pData[i][pID] == account_id)
        {
            return i;
        }
    }
    return INVALID_PLAYER_ID;
}

stock BankFindAccountByName(const target_name[], &account_id, account_name[], account_name_size = sizeof account_name)
{
    new query[128], Cache:result;
    new __ms4[] = "SELECT id, name FROM accounts WHERE name = '%e' LIMIT 1";
    mysql_format(ConnectMySQL, query, sizeof(query), __ms4, target_name);
    result = mysql_query(ConnectMySQL, query);

    if(!cache_num_rows())
    {
        cache_delete(result);
        return false;
    }

    account_id = cache_get_field_content_int(0, "id");
    cache_get_field_content(0, "name", account_name, ConnectMySQL, account_name_size);
    cache_delete(result);
    return true;
}

stock BankSetInterestRate(Float:rate)
{
    BankInterestRate = rate;

    new query[128];
    new __ms3[] = "UPDATE `bank_settings` SET InterestRate=%f WHERE `SettingName` = '"BANK_INTEREST_SETTING_NAME"'";
    mysql_format(ConnectMySQL, query, sizeof(query), __ms3, BankInterestRate);
    mysql_tquery(ConnectMySQL, query);
    return true;
}

Bank_NewDay()
{
    if(BankInterestRate <= 0.0) return true;

    new query[512];
    new __ms2[] = "INSERT INTO bank_transactions (AccountID, Type, Amount, Date) SELECT id, %d, FLOOR(bank_money * %f / 100), UNIX_TIMESTAMP() FROM accounts WHERE bank_money > 0 AND FLOOR(bank_money * %f / 100) > 0";
    mysql_format(ConnectMySQL, query, sizeof(query), __ms2, BANK_TRANSACTION_INTEREST, BankInterestRate, BankInterestRate);
    mysql_tquery(ConnectMySQL, query);

    new __ms1[] = "UPDATE accounts SET bank_money = bank_money + FLOOR(bank_money * %f / 100) WHERE bank_money > 0 AND FLOOR(bank_money * %f / 100) > 0";
    mysql_format(ConnectMySQL, query, sizeof(query), __ms1, BankInterestRate, BankInterestRate);
    mysql_tquery(ConnectMySQL, query);

    foreach(new i : Player)
    {
        if(Logged[i])
        {
            new interest = floatround(pData[i][pBankMoney] * BankInterestRate / 100.0, floatround_floor);
            if(interest > 0) pData[i][pBankMoney] += interest;
        }
    }
    return true;
}

hook OnGameModeInit()
{
    BankCreateTables();
    CreateDynamicPickup(1239, 1, POS_BANK_PICKUP, VW_BANK, INT_BANK);
    CreateDynamic3DTextLabel("Банковские операции\nНажмите "FLAME_COLOR"ALT"COLOR_WHITE" для взаимодействия", -1, POS_BANK_PICKUP, 5.0, _, _, 1, VW_BANK, INT_BANK);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_WALK && !(oldkeys & KEY_WALK) && !IsPlayerInAnyVehicle(playerid) && IsPlayerInRangeOfPoint(playerid, 2.0, POS_BANK_PICKUP)
        && GetPlayerVirtualWorld(playerid) == VW_BANK && GetPlayerInterior(playerid) == INT_BANK)
    {
        if(!HasPlayerBankCard(playerid)) return ShowBankOpenAccountDialog(playerid);
        BankUpdateLastCardUse(playerid);
        Quest_OnPlayerGetBankCard(playerid);
        ShowBankMainDialog(playerid);
    }
    return true;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == D_BANK_OPEN_ACCOUNT)
    {
        if(!response) return true;
        if(!GivePlayerBankCard(playerid)) return true;

        BankUpdateLastCardUse(playerid);
        return ShowBankMainDialog(playerid);
    }

    if(dialogid == D_BANK_MAIN)
    {
        if(!response) return true;

        switch(listitem)
        {
            case 0: ShowBankAccountInfoDialog(playerid);
            case 1: ShowBankDepositDialog(playerid);
            case 2: ShowBankWithdrawDialog(playerid);
            case 3: ShowBankTransferNameDialog(playerid);
            case 4: ShowBankHistoryDialog(playerid);
        }
        return true;
    }
    if(dialogid == D_BANK_BALANCE || dialogid == D_BANK_ERROR || dialogid == D_BANK_SUCCESS || dialogid == D_BANK_HISTORY)
    {
        return ShowBankMainDialog(playerid);
    }

    if(dialogid == D_BANK_DEPOSIT)
    {
        if(!response) return ShowBankMainDialog(playerid);

        new amount;
        if(sscanf(inputtext, "i", amount)) return ShowBankErrorDialog(playerid, "Сумма пополнения указана в неверном формате.");
        if(amount <= 0) return ShowBankErrorDialog(playerid, "Сумма пополнения должна быть положительной.");
        if(pData[playerid][pMoney] < amount) return ShowBankErrorDialog(playerid, "У вас недостаточно наличных для пополнения счета.");

        DepositMoney(playerid, amount);
        return ShowBankSuccessDialog(playerid, "Операция пополнения выполнена успешно.");
    }

    if(dialogid == D_BANK_WITHDRAW)
    {
        if(!response) return ShowBankMainDialog(playerid);

        new amount;
        if(sscanf(inputtext, "i", amount)) return ShowBankErrorDialog(playerid, "Сумма снятия указана в неверном формате.");
        if(amount <= 0) return ShowBankErrorDialog(playerid, "Сумма снятия должна быть положительной.");
        if(pData[playerid][pBankMoney] < amount) return ShowBankErrorDialog(playerid, "У вас недостаточно денег на банковском счете.");

        WithdrawMoney(playerid, amount);
        return ShowBankSuccessDialog(playerid, "Операция снятия выполнена успешно.");
    }

    if(dialogid == D_BANK_TRANSFER_PLAYER_ID)
    {
        if(!response) return ShowBankMainDialog(playerid);
        if(!strlen(inputtext)) return ShowBankErrorDialog(playerid, "Введите никнейм получателя перевода.");

        new account_id, account_name[MAX_PLAYER_NAME];
        if(!BankFindAccountByName(inputtext, account_id, account_name))
        {
            return ShowBankErrorDialog(playerid, "Аккаунт с таким никнеймом не найден.");
        }
        if(account_id == pData[playerid][pID])
        {
            return ShowBankErrorDialog(playerid, "Нельзя переводить деньги самому себе.");
        }

        PlayerChosenTransferID[playerid] = account_id;
        format(PlayerChosenTransferName[playerid], MAX_PLAYER_NAME, "%s", account_name);
        return ShowBankTransferAmountDialog(playerid);
    }

    if(dialogid == D_BANK_TRANSFER_AMOUNT)
    {
        if(!response) return ShowBankTransferNameDialog(playerid);

        new amount;
        if(sscanf(inputtext, "i", amount)) return ShowBankErrorDialog(playerid, "Сумма перевода указана в неверном формате.");
        if(amount <= 0) return ShowBankErrorDialog(playerid, "Сумма перевода должна быть положительной.");
        if(pData[playerid][pBankMoney] < amount) return ShowBankErrorDialog(playerid, "У вас недостаточно денег на банковском счете.");

        TransferMoney(playerid, PlayerChosenTransferID[playerid], PlayerChosenTransferName[playerid], amount);
        return true;
    }
    return false;
}

stock DepositMoney(playerid, amount)
{
    UpdatePlayerMoney(playerid, -amount);
    UpdatePlayerBankMoney(playerid, amount, true);
    BankLogTransaction(pData[playerid][pID], BANK_TRANSACTION_DEPOSIT, amount);
    return true;
}

stock WithdrawMoney(playerid, amount)
{
    if(amount <= 0) return false;
    if(pData[playerid][pBankMoney] < amount) return false;

    UpdatePlayerMoney(playerid, amount);
    UpdatePlayerBankMoney(playerid, amount, false);
    BankLogTransaction(pData[playerid][pID], BANK_TRANSACTION_WITHDRAW, amount);
    return true;
}

stock TransferMoney(playerid, target_account_id, const target_name[], amount, bool:show_dialog = true)
{
    if(amount <= 0) return false;
    if(target_account_id == pData[playerid][pID]) return false;
    if(pData[playerid][pBankMoney] < amount) return false;

    UpdatePlayerBankMoney(playerid, amount, false);

    new targetid = BankFindOnlinePlayerByAccount(target_account_id);
    if(targetid != INVALID_PLAYER_ID)
    {
        UpdatePlayerBankMoney(targetid, amount, true);
    }
    else
    {
        new query[128];
        new __ms0[] = "UPDATE accounts SET bank_money = bank_money + %d WHERE id = %d";
        mysql_format(ConnectMySQL, query, sizeof(query), __ms0, amount, target_account_id);
        mysql_tquery(ConnectMySQL, query);
    }

    BankLogTransaction(pData[playerid][pID], BANK_TRANSACTION_TRANSFER_OUT, amount, target_account_id, target_name);
    BankLogTransaction(target_account_id, BANK_TRANSACTION_TRANSFER_IN, amount, pData[playerid][pID], pData[playerid][pName]);

    new string[144];
    format(string, sizeof(string), "* Вы перевели $%s игроку %s.", convertNumber(amount), target_name);
    SendClientMessage(playerid, COLOR_GREEN, string);

    if(targetid != INVALID_PLAYER_ID)
    {
        format(string, sizeof(string), "* Вы получили банковский перевод $%s от %s.", convertNumber(amount), pData[playerid][pName]);
        SendClientMessage(targetid, COLOR_GREEN, string);
    }

    if(show_dialog) return ShowBankSuccessDialog(playerid, "Операция перевода выполнена успешно.");
    return true;
}

CMD:deposit(playerid, params[])
{
    if(!BankCheckAccess(playerid)) return true;
    new amount;
    if(sscanf(params, "i", amount)) return SendClientMessage(playerid, COLOR_GREY, !"Использование: /deposit <сумма>");
    if(amount <= 0) return SendClientMessage(playerid, COLOR_GREY, !"* Сумма должна быть положительной.");
    if(pData[playerid][pMoney] < amount) return SendClientMessage(playerid, COLOR_GREY, !"* У вас недостаточно наличных.");

    DepositMoney(playerid, amount);
    SendClientMessageEx(playerid, COLOR_GREEN, "* Вы внесли $%s на банковский счет.", convertNumber(amount));
    return true;
}

CMD:withdraw(playerid, params[])
{
    if(!BankCheckAccess(playerid)) return true;
    new amount;
    if(sscanf(params, "i", amount)) return SendClientMessage(playerid, COLOR_GREY, !"Использование: /withdraw <сумма>");
    if(amount <= 0) return SendClientMessage(playerid, COLOR_GREY, !"* Сумма должна быть положительной.");
    if(pData[playerid][pBankMoney] < amount) return SendClientMessage(playerid, COLOR_GREY, !"* У вас недостаточно денег на банковском счете.");

    WithdrawMoney(playerid, amount);
    SendClientMessageEx(playerid, COLOR_GREEN, "* Вы сняли $%s с банковского счета.", convertNumber(amount));
    return true;
}

CMD:transfer(playerid, params[])
{
    if(!BankCheckAccess(playerid)) return true;
    new target_name[MAX_PLAYER_NAME], amount;
    if(sscanf(params, "s[24]i", target_name, amount)) return SendClientMessage(playerid, COLOR_GREY, !"Использование: /transfer <никнейм> <сумма>");
    if(amount <= 0) return SendClientMessage(playerid, COLOR_GREY, !"* Сумма должна быть положительной.");
    if(pData[playerid][pBankMoney] < amount) return SendClientMessage(playerid, COLOR_GREY, !"* У вас недостаточно денег на банковском счете.");

    new account_id, account_name[MAX_PLAYER_NAME];
    if(!BankFindAccountByName(target_name, account_id, account_name)) return SendClientMessage(playerid, COLOR_GREY, !"* Аккаунт с таким никнеймом не найден.");
    if(account_id == pData[playerid][pID]) return SendClientMessage(playerid, COLOR_GREY, !"* Нельзя переводить деньги самому себе.");

    TransferMoney(playerid, account_id, account_name, amount, false);
    return true;
}

CMD:balance(playerid, params[])
{
    if(!BankCheckAccess(playerid)) return true;
    SendClientMessageEx(playerid, COLOR_GREY, "* Наличными: $%s | Банк: $%s", convertNumber(pData[playerid][pMoney]), convertNumber(pData[playerid][pBankMoney]));
    return true;
}

CMD:stavka(playerid, params[])
{
    //if(!pData[playerid][pAdmin]) return SendClientMessage(playerid, COLOR_GREY, !"* У вас нет доступа к этой команде.");

    new Float:rate;
    if(sscanf(params, "f", rate)) return SendClientMessageEx(playerid, COLOR_GREY, "Использование: /stavka <процент>. Текущая ставка: %.2f%%", BankInterestRate);
    if(rate < 0.0 || rate > 100.0) return SendClientMessage(playerid, COLOR_GREY, !"* Процентная ставка должна быть от 0 до 100.");

    BankSetInterestRate(rate);
    SendClientMessageEx(playerid, COLOR_GREEN, "* Процентная ставка банка изменена на %.2f%%.", BankInterestRate);
    return true;
}

CMD:transactions(playerid, params[])
{
    if(!BankCheckAccess(playerid)) return true;
    ShowBankHistoryDialog(playerid);
    return true;
}

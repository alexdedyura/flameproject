#if !defined IsValidVehicle
native IsValidVehicle(vehicleid);
#endif

RusText(const text[])
{
    new ret[256];
    new tmp[256];
    strcat(tmp, text, sizeof(tmp));
    GetRussifierText(GetDefaultRussifierType(), tmp, ret);
    return ret;
}


SendClientMessageEx(playerid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args
        #emit SYSREQ.C format

        SendClientMessage(playerid, color, string);

        #emit LCTRL 5
        #emit SCTRL 4
        #emit RETN
    }
    return SendClientMessage(playerid, color, str);
}

#define     KickEx(%1)           SetTimerEx("kick", 100, false, "i", %1)


forward kick(playerid);
public kick(playerid)
{
	Kick(playerid);
}

stock Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
    return VectorSize(x1 - x2, y1 - y2, z1 - z2);
}

new const WEAPON_NAMES[][] =
{
    "Рукопашный бой","Кастет","Клюшка","Резиновая дубинка","Нож","Бита","Лопата","Кий","Катана","Бензопила","Дилдо",
    "Дилдо","Дилдо","Дилдо","Цветы","Трость","Граната","Дымовая граната","Коктейль молотова","NONE","NONE","NONE","Colt","SD Pistol",
    "Desert Eagle","Shotgun","Spawn-Off Shotgun","Стрёмная штука","UZI","MP-5","AK-47","M4A1","TEC-9","Rifle",
    "Sniper Rifle","Ракетница","Рокетница","Огнемет","Миниган","Взрывчатка", "Детонатор","Балончик","Огнетушитель",  "Фотоаппарат", "ПНВ", "Тепловизор", "Парашют"
};


stock GetInvWeaponSlot(weaponid)
{
    if (weaponid < 0 || weaponid > 46) return -1;

    switch (weaponid)
    {
        case 0: return 0; // Без оружия
        case 1: return 0; // Кулаки
        case 2..9: return 1; // Холодное оружие
        case 22..24: return 2; // Пистолеты
        case 25..27: return 3; // Дробовики
        case 28, 29, 32: return 4; // Пистолеты-пулеметы
        case 30, 31: return 5; // Автоматы
        case 33, 34: return 6; // Винтовки
        case 35..38: return 7; // Тяжелое оружие
        case 16..18, 39: return 8; // Гранаты
        case 41..43: return 9; // Спреи
        case 10..15: return 10; // Подарки
        case 44..46: return 11; // Особые предметы
        case 40: return 12; // Детонатор
    }
    return -1;
}

StringToUpper(const string[])
{
    new newstring[256];
    new i = 0;
    while(i < strlen(string))
        newstring[i] = toupper(string[i]), i++;
    return newstring;
}

convertNumber(value)
{
	// http://forum.sa-mp.com/showthread.php?p=843781#post843781
    new string[24];
    format(string, sizeof(string), "%d", value);

    for(new i = (strlen(string) - 3); i > (value < 0 ? 1 : 0) ; i -= 3)
    {
        strins(string[i], ",", 0);
    }

    return string;
}

#include <..\..\sources\core\dialogs.inc>
#include <..\..\sources\core\mysql.inc>
#include <..\..\sources\core\colors.inc>
#include <..\..\sources\core\macrosses.inc>
#include <..\..\sources\core\nearbymessage.inc>
#include <..\..\sources\core\zones.inc>
#include <..\..\sources\core\mapicon.inc>
#include <..\..\sources\core\pos_info.inc>
#include <..\..\sources\core\strlib.inc>
#include <..\..\sources\core\mxdate.inc>
#include <..\..\sources\core\vehicles_int.inc>
#include <..\..\sources\core\timers.inc>
#include <..\..\sources\core\dates.inc>

#include <YSI_Coding\y_hooks>

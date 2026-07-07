#include <YSI_Coding\y_hooks>

SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144];

    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if (args > 16)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for(end = start + (args - 16); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit CONST.alt 4
        #emit SUB
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if (DistancePlayer(radius,i, playerid))
                SendClientMessage(i, color, string);
        }
        return true;
    }
    foreach (new i : Player)
    {
        if (DistancePlayer(radius,i, playerid))
            SendClientMessage(i, color, str);
    }
    return true;
}
DistancePlayer(Float:radius, playerid, targetid)
{
    new Float: X, Float: Y, Float: Z;
    GetPlayerPos(targetid, X, Y, Z);
    if(IsPlayerInRangeOfPoint(playerid, radius, X, Y, Z) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) return true;
    return false;
}
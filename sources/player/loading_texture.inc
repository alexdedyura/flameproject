#include <YSI_Coding\y_hooks>

// Константы
#define LOADING_UPDATE_INTERVAL 500 // Интервал обновления прогресс-бара в миллисекундах (1000 мс = 1 секунда)
#define LOADING_BAR_WIDTH 158.1993 // Ширина прогресс-бара в пикселях

enum E_LOADING_DATA
{
    bool:loadActive,
    loadStartTime,
    loadTimeLeft,
    loadTimer
}
new LoadingData[MAX_PLAYERS][E_LOADING_DATA];

hook OnPlayerConnect(playerid)
{
    LoadingData[playerid][loadActive] = false;
    LoadingData[playerid][loadStartTime] = 0;
    LoadingData[playerid][loadTimeLeft] = 0;
    LoadingData[playerid][loadTimer] = -1;
    return 1;
}

// Показ/скрытие всех элементов экрана загрузки
ShowLoadingTextDraws(playerid)
{
    for (new i = 0; i < sizeof(LoadingTD); i++)
        if (_:LoadingTD[i] != -1) TextDrawShowForPlayer(playerid, LoadingTD[i]);
    for (new i = 0; i < sizeof(LoadingPTD[]); i++)
        if (_:LoadingPTD[playerid][i] != -1) PlayerTextDrawShow(playerid, LoadingPTD[playerid][i]);
}

HideLoadingTextDraws(playerid)
{
    for (new i = 0; i < sizeof(LoadingTD); i++)
        if (_:LoadingTD[i] != -1) TextDrawHideForPlayer(playerid, LoadingTD[i]);
    for (new i = 0; i < sizeof(LoadingPTD[]); i++)
        if (_:LoadingPTD[playerid][i] != -1) PlayerTextDrawHide(playerid, LoadingPTD[playerid][i]);
}

// Остановка таймера загрузки (если запущен)
StopLoadingTimer(playerid)
{
    if (LoadingData[playerid][loadTimer] != -1)
    {
        KillTimer(LoadingData[playerid][loadTimer]);
        LoadingData[playerid][loadTimer] = -1;
    }
}

// Завершение загрузки: вернуть управление, скрыть UI, остановить таймер
FinishPlayerTextureLoading(playerid, bool:restore_control = true)
{
    if (restore_control) TogglePlayerControllable(playerid, true);
    HideLoadingTextDraws(playerid);
    StopLoadingTimer(playerid);
    LoadingData[playerid][loadActive] = false;
}

// Запуск загрузки текстур для игрока
stock StartPlayerTextureLoading(playerid, time)
{
    if (time <= 0)
    {
        SendClientMessage(playerid, COLOR_ERROR, !"* Ошибка: некорректное время загрузки!");
        return false;
    }

    // Конвертация времени в количество тиков (на основе интервала)
    new ticks = floatround(float(time) * 1000.0 / float(LOADING_UPDATE_INTERVAL), floatround_ceil);
    TogglePlayerControllable(playerid, false);

    ShowLoadingTextDraws(playerid);
    PlayerTextDrawTextSize(playerid, LoadingPTD[playerid][0], 1.0, 15.0);
    PlayerTextDrawSetString(playerid, LoadingPTD[playerid][1], "0%");

    // Перезапуск: убиваем предыдущий таймер, чтобы они не накапливались
    StopLoadingTimer(playerid);
    LoadingData[playerid][loadActive] = true;
    LoadingData[playerid][loadStartTime] = ticks;
    LoadingData[playerid][loadTimeLeft] = ticks;
    LoadingData[playerid][loadTimer] = SetTimerEx("LoadingTimer", LOADING_UPDATE_INTERVAL, true, "i", playerid);
    return true;
}

// Таймер для обновления прогресс-бара
forward LoadingTimer(playerid);
public LoadingTimer(playerid)
{
    if (!LoadingData[playerid][loadActive])
    {
        StopLoadingTimer(playerid); // подстраховка от "осиротевшего" таймера
        return 0;
    }

    new timeLeft = LoadingData[playerid][loadTimeLeft];
    new startTime = LoadingData[playerid][loadStartTime];

    if (timeLeft <= 0)
    {
        FinishPlayerTextureLoading(playerid);
        return 0;
    }

    LoadingData[playerid][loadTimeLeft] = timeLeft - 1;

    // Обновление ширины прогресс-бара
    new Float:progress = (float(startTime - timeLeft) / float(startTime)) * LOADING_BAR_WIDTH;
    PlayerTextDrawTextSize(playerid, LoadingPTD[playerid][0], progress, 15.0);
    PlayerTextDrawShow(playerid, LoadingPTD[playerid][0]);

    // Обновление процента
    new percent = floatround((float(startTime - timeLeft) / float(startTime)) * 100.0);
    new str[8];
    format(str, sizeof(str), "%d%%", percent);
    PlayerTextDrawSetString(playerid, LoadingPTD[playerid][1], str);

    return 1;
}

// Обработка отключения игрока
hook OnPlayerDisconnect(playerid, reason)
{
    if (LoadingData[playerid][loadActive])
        FinishPlayerTextureLoading(playerid, false); // игрок уходит, управление не трогаем
    StopLoadingTimer(playerid);
    return 1;
}
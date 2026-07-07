

#include <YSI_Coding\y_hooks>

new Text:logo;

hook OnGameModeInit()
{
	logo = TextDrawCreate(554.482385, 11.499990, "FLAMEPROJECT"); 
	TextDrawLetterSize(logo, 0.189412, 0.883165); 
	TextDrawAlignment(logo, 1); 
	TextDrawColor(logo, -1); 
	TextDrawSetShadow(logo, 0); 
	TextDrawSetOutline(logo, 0); 
	TextDrawBackgroundColor(logo, 255); 
	TextDrawFont(logo, 2); 
	TextDrawSetProportional(logo, true); 
	TextDrawSetShadow(logo, 0);
}

hook OnPlayerConnect(playerid)
{
	TextDrawShowForPlayer(playerid, logo);
}
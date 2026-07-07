#include <YSI_Coding\y_hooks>

/*
new 
	const anim_list[][][ e_ANIM_INFO ] = 
	{
		{	//Действие - сесть
			{ "sit", "аккуратно сесть на стул" },
			{ "seat", "развалиться на стуле" },
			{ "fsit", "сесть, сложить нога на ногу и опереться левой рукой на что-то" },
			{ "ksit", "сесть на стул и положить руки на стол" },
			{ "rseat", "разложиться на стуле и опереться головой на левую руку" },
			{ "gro", "сесть на землю" },
			{ "csit", "сесть и начать печатать на компьютере (1)" },
			{ "hsit", "сесть и начать печатать на компьютере (2)" },
			{ "esit", "выпить что-то сидя" },
			{ "sprawl", "присесть на что-то и опереться руками на колени" },
			{ "wsit", "сесть на колено с дробовиком в руках" },
			{ "copa", "сесть на колено и что-то делать правой рукой" },
			{ "squat", "выстрелить и присесть" },
			{ "tatto", "сесть и опереться локтем на что-то (вправо)" },
			{ "hide", "сесть и сложить руки за голову" },
			{ "crack", "[3,5] сидеть под наркотиками" },
			{ "tgro", "сесть на колено" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" }
		},
		{	//Действие - лечь
			{ "lay", "лечь" },
			{ "crack", "[1,2,4,6,7] лежать под наркотиками" },
			{ "sleepl", "спать на правом боку" },
			{ "sleepr", "спать на левом боку" },
			{ "csdead", "лежать на животе" },
			{ "injured", "лежать раненым" },
			{ "tired", "лечь на капот для обыска" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" }
		},
		{	//Действие с оружием
			{ "bomb", "заложить бомбу" },
			{ "colt", "держать пистолет" },
			{ "lookoutr", "спрятаться за стену с пистолетом (вправо)" },
			{ "lookoutl", "спрятаться за стену с пистолетом (влево)" },
			{ "shotgun", "держать дробовик" },
			{ "bat", "держать биту" },
			{ "waimr", "целится вправо" },
			{ "waiml", "целится влево" },
			{ "shelter", "выстрелить из дробовика" },
			{ "gunthreat", "направить дробовик на кого-либо" },
			{ "squat", "выстрелить и присесть" },
			{ "faim", "встать в боевую стойку с катаной" },
			{ "robr", "поднять руки" },
			{ "wsit", "сесть на колено с дробовиком в руках" },
			{ "grnd", "положить что-либо на пол" },
			{ "aim", "целиться" },
			{ "handsup", "поднять руки" },
			{ "waim", "держать на прицеле (можно ходить)" },
			{ "", "" },
			{ "", "" },
			{ "", "" }
		},
		{	//Удары и падения
			{ "push", "толкнуть впереди стоящего" },
			{ "lowbodypush", "толкнуть боком впереди стоящего" },
			{ "kostomach", "падение от удара в грудь" },
			{ "rollfall", "кувырок назад" },
			{ "flip", "кувырок на месте" },
			{ "box", "боксировать" },
			{ "gpunch", "ударить рукой лежачего" },
			{ "akick", "толчок ногой" },
			{ "koface", "падение от удара в голову" },
			{ "lifejump", "кувырок вперед" },
			{ "gkick", "пнуть ногой лежачего" },
			{ "nflip", "упасть назад" },
			{ "nfall", "получить удар по лицу и упасть на попу" },
			{ "extend", "растолкать толпу" },
			{ "backwalk", "растолкать толпу" },
			{ "despair", "резкий удар кулаком по столу" },
			{ "frontfall", "упасть на живот" },
			{ "wallow", "упасть на землю" },
			{ "tramplefloor", "бить ногой о землю" },
			{ "fail", "ударить кулаком по столу с разочарованием" },
			{ "swingback", "упасть назад и встать" }
		},
		{	//Взаимодействие с игроком
			{ "yes", "согласиться" },
			{ "no", "отказаться" },
			{ "wave", "приветствие" },
			{ "medic", "искусственное дыхание" },
			{ "cmon", "спорить" },
			{ "givecash", "дать денег" },
			{ "rtake", "поцеловать в щеку" },
			{ "bj", "[1,3,5,7] делать минет" },
			{ "bj", "[2,4,6] наслаждаться минетом" },
			{ "spank", "[2,4,5,8] шлепать по попе" },
			{ "slapass", "шлепнуть по попе (cлева)" },
			{ "blowj", "сделать минет" },
			{ "heist", "погладить кого-то правой рукой" },
			{ "tpull", "достать что-то из заднего кармана и протянуть вперед" },
			{ "police", "анимация для полиции" },
			{ "deal", "[1] дилер" },
			{ "getarrested", "протянуть руки для ареста" },
			{ "beckon", "махнуть рукой (позвать к себе кого-то)" },
			{ "wobalance", "помахать руками с моста" },
			{ "follow", "жест следования" },
			{ "stopit", "резко вытянуть руку вперед с требованием остановки" }
		},
		{	//Взаимодействие с автомобилем
			{ "onehand", "облокотится на машину задом и поставить ногу на колесо" },
			{ "repcar", "ремонтировать машину (залезть под неё)" },
			{ "саr", "изменить анимацию в авто" },
			{ "pullo", "открыть окно" },
			{ "stoptaxi", "махнуть рукой вправо" },
			{ "catch", "уцепиться за бампер авто" },
			{ "tsit", "опереться левой рукой на дверь (в автомобиле)" },
			{ "taxil", "ловить такси (слева)" },
			{ "taxir", "ловить такси (справа)" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" }
		},
		{	//Эмоции персонажа
			{ "cry", "плакать" },
			{ "sh", "кричать" },
			{ "sho", "крикнуть что-то" },
			{ "wshow", "кричать в даль" },
			{ "win", "радоваться" },
			{ "facepalm", "ударить себя по лбу с изображением разочарования" },
			{ "tfacepalm", "разочароваться" },
			{ "lose", "разочароваться" },
			{ "fucku", "поднять правую руку с возмущением" },
			{ "laugh", "смех" },
			{ "joy", "поднять руки и подпрыгнуть от радости" },
			{ "gog", "прикрыть лицо руками" },
			{ "mshow", "указать левой рукой на что-то и прикрыть рот от шока" },
			{ "delight", "развернуться и сделать жест радости" },
			{ "cmouth", "поднести руку ко рту" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" }
		},
		{	//Позы персонажа
			{ "stand", "встать в ровную стойку и расставить руки" },
			{ "feettog", "встать в ровную стойку" },
			{ "crossarms", "сложить руки" },
			{ "spank", "[1,3,6,7] встать в позу, чтобы быть отшлепанным" },
			{ "spyglass", "держать камеру над собой" },
			{ "lean", "опереться" },
			{ "pool", "принять стойку для игры в бильярд" },
			{ "pullhand", "держаться за что-то" },
			{ "caim", "держать в руке что-либо" },
			{ "hstand", "опереться головой на правую руку" },
			{ "looksky", "смотреть в даль" },
			{ "nlean", "встать как статуя" },
			{ "hips", "положить руки на пояс и сложить их перед грудью" },
			{ "tlean", "положить руки на перила" },
			{ "daim", "отклониться назад" },
			{ "rhandr", "поднять правую руку" },
			{ "rhandl", "поднять левую руку" },
			{ "readtable", "сделать резкий жест в сторону и опереться вперед" },
			{ "piss", "растегнуть ширинку и писать" },
			{ "crossfingers", "взяться за расстегнутый пиджак перед грудью" },
			{ "takehead", "держаться за что-то справа" }
		},
		{	//Еда
			{ "eat", "есть" },
			{ "sipdrink", "пить напиток" },
			{ "esit", "выпить что-то сидя" },
			{ "swallow", "съесть что-то" },
			{ "taction", "нарезать что-то на столе" },
			{ "bar", "достать из-под барной стойки что-то" },
			{ "еsit", "выпить что-то сидя" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" },
			{ "", "" }
		},
		{	//Спорт
			{ "rod", "поднять штангу на тренажере" },
			{ "lookfloor", "взяться за что-то перед собой (штанга)" },
			{ "protection", "встать в боевую стойку" },
			{ "stand", "встать в ровную стойку и немного расставить руки" },
			{ "feettog", "встать в ровную стойку" },
			{ "faim", "встать в боевую стойку с катаной" },
			{ "taichi", "медитировать" },
			{ "box", "боксировать" },
			{ "abp", "разминка" },
			{ "nbp", "делать различные жесты и в конце показать силу" },
			{ "bracing", "разминка тела" },
			{ "swing", "поднять гантели" },
			{ "hangon", "повиснуть на турнике" },
			{ "climb", "повиснуть на турнике" },
			{ "nlook", "разминка плеч" },
			{ "lookback", "разминка тела" },
			{ "scatch", "повиснуть на что-либо" },
			{ "crushjump", "резкий прыжок влево с кувырком" },
			{ "pushup", "встать с пола" },
			{ "", "" },
			{ "", "" }
		},
		{	//Цикличные
			{ "drunk", "пьяная походка" },
			{ "chant", "болеть за кого-либо" },
			{ "strip", "танцевать стриптиз" },
			{ "walk", "автоматическая походка" },
			{ "polwalk", "держать на прицеле и идти" },
			{ "dance", "танцевать" },
			{ "gsign", "жесты руками" },
			{ "chat", "говорить" },
			{ "ssearch", "искать что-то на колене" },
			{ "rap", "читать рэп" },
			{ "wave", "[2] приветствие" },
			{ "bat", "держать биту" },
			{ "police", "анимация полиции" },
			{ "deal", "[2,3] дилер" },
			{ "creep", "настороженно идти" },
			{ "chant", "болеть за кого-либо" },
			{ "rooting", "болеть за кого-либо" },
			{ "asmoke", "[1,2,3] курить" },
			{ "wear", "нести что-то на руках" },
			{ "agreement", "сделать задумчивый вид" },
			{ "taichi", "медитация" }
		},
		{	//Разное
			{ "lookout", "надеть маску" },
			{ "crawl", "ползти" },
			{ "aspray", "рисовать баллончиком граффити" },
			{ "lowthrow", "кинуть что-то правой рукой" },
			{ "riot", "поднять руки и развести в стороны" },
			{ "sroll", "перепрыгнуть через ограждение и спрятаться за ним" },
			{ "asmoke", "курить" },
			{ "gesture", "жест рукой влево" },
			{ "ssearch", "искать что-то на колене" },
			{ "climb", "повиснуть на заборе" },
			{ "serend", "открыть кассу и положить деньги" },
			{ "pants", "застегнуть ширинку" },
			{ "obalance", "посмотреть вниз с моста/крыши" },
			{ "hshow", "указать левой рукой на что-то" },
			{ "bend", "прислушаться" },
			{ "showtable", "подвинуть вперед что-то на столе (стоя)" },
			{ "hnds", "распальцовки" },
			{ "throwmoney", "пританцовывая, бросить деньги" },
			{ "vomit", "тошнота" },
			{ "balls", "чесать между ног" },
			{ "backwalk", "нагнувшись и схватившись за голову, идти назад" }
		}
	};

#define anim_dialog		"\
								"FLAME_COLOR"1. "COLOR_WHITE"Действие - сесть\n\
								"FLAME_COLOR"2. "COLOR_WHITE"Действие - лечь\n\
								"FLAME_COLOR"3. "COLOR_WHITE"Действия с оружием\n\
								"FLAME_COLOR"4. "COLOR_WHITE"Удары и падения\n\
								"FLAME_COLOR"5. "COLOR_WHITE"Взаимодействие с игроком\n\
								"FLAME_COLOR"6. "COLOR_WHITE"Взаимодействие с автомобилем\n\
								"FLAME_COLOR"7. "COLOR_WHITE"Эмоции персонажа\n\
								"FLAME_COLOR"8. "COLOR_WHITE"Позы персонажа\n\
								"FLAME_COLOR"9. "COLOR_WHITE"Еда\n\
								"FLAME_COLOR"10. "COLOR_WHITE"Спорт\n\
								"FLAME_COLOR"11. "COLOR_WHITE"Цикличные\n\
								"FLAME_COLOR"12. "COLOR_WHITE"Разное\
							"
*/
stock PreloadAnim( playerid ) 
{
	PreloadAnimLib(playerid,"BOMBER");
	PreloadAnimLib(playerid,"RAPPING");
	PreloadAnimLib(playerid,"SHOP");
	PreloadAnimLib(playerid,"BEACH");
	PreloadAnimLib(playerid,"SMOKING");
	PreloadAnimLib(playerid,"FOOD");
	PreloadAnimLib(playerid,"ON_LOOKERS");
	PreloadAnimLib(playerid,"DEALER");
	PreloadAnimLib(playerid,"CRACK");
	PreloadAnimLib(playerid,"CARRY");
	PreloadAnimLib(playerid,"COP_AMBIENT");
	PreloadAnimLib(playerid,"PARK");
	PreloadAnimLib(playerid,"INT_HOUSE");
	PreloadAnimLib(playerid,"FOOD");
	PreloadAnimLib(playerid,"GHANDS");
	PreloadAnimLib(playerid,"GANGS");
	PreloadAnimLib(playerid,"PED");
	PreloadAnimLib(playerid,"RIOT");
	PreloadAnimLib(playerid,"PAULNMAC");
	PreloadAnimLib(playerid,"FIGHT_B");
	PreloadAnimLib(playerid,"FIGHT_D");
	PreloadAnimLib(playerid,"SPRAYCAN");
	PreloadAnimLib(playerid,"MISC");
	PreloadAnimLib(playerid,"GRAVEYARD");
	PreloadAnimLib(playerid,"POLICE");
	PreloadAnimLib(playerid,"CAR_CHAT");
	PreloadAnimLib(playerid,"SWEET");
	PreloadAnimLib(playerid,"SUNBATHE");
	PreloadAnimLib(playerid,"CRIB");
	PreloadAnimLib(playerid,"BAR");
	PreloadAnimLib(playerid,"DANCING");
	PreloadAnimLib(playerid,"VENDING");
	PreloadAnimLib(playerid,"BSKTBALL");
	PreloadAnimLib(playerid,"BD_FIRE");
	PreloadAnimLib(playerid,"COLT45");
	PreloadAnimLib(playerid,"SILENCED");
	PreloadAnimLib(playerid,"TEC");
	PreloadAnimLib(playerid,"UZI");
	PreloadAnimLib(playerid,"OTB");
	PreloadAnimLib(playerid,"CAR");
	PreloadAnimLib(playerid,"MEDIC");
	PreloadAnimLib(playerid,"WUZI");
	PreloadAnimLib(playerid,"BLOWJOBZ");
	PreloadAnimLib(playerid,"LOWRIDER");
	PreloadAnimLib(playerid,"FINALE");
	PreloadAnimLib(playerid,"CLOTHES");
	PreloadAnimLib(playerid,"SNM" );
	PreloadAnimLib(playerid,"SEX" );
	return 1;
}

stock UseAnim(playerid, const animlib[], const animname[], Float:speed, bool:looping, bool:lockx, bool:locky, bool:lockz, lp, time = 0) 
{
	SetPVarInt(playerid, "Anim:States", 1);
    ApplyAnimation(playerid, animlib, animname, speed, looping, lockx, locky, lockz, lp, time);
    ApplyAnimation(playerid, animlib, animname, speed, looping, lockx, locky, lockz, lp, time);
    ApplyAnimation(playerid, animlib, animname, speed, looping, lockx, locky, lockz, lp, time);
}

stock PreloadAnimLib(playerid, const animlib[]) {
	ApplyAnimation(playerid,animlib,"null",0.0,false,false,false,false,0);
}

stock StopUsingAnim(playerid) {
	DeletePVar(playerid, "Anim:States");
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, false, false, false, false, 0);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, false, false, false, false, 0);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, false, false, false, false, 0);
}

/*CMD:animlist( playerid )
{
	
    return ShowPlayerDialog( playerid, d_anim, DIALOG_STYLE_LIST, "Анимации", anim_dialog, "Выбрать", "Закрыть" );   
} */

CMD:stop( playerid ) return cmd_stopanim( playerid );
CMD:sa( playerid ) return cmd_stopanim( playerid );

CMD:stopanim( playerid ) 
{
		
	StopUsingAnim( playerid );
	return 1;
}

// ---------------------------------Команды анимаций-----------------------------------

CMD:handsup(playerid, params[]) {
	
	UseAnim(playerid, "ROB_BANK","SHP_HandsUp_Scr", 4.0, false, true, true, true, 0);
	return true;
}

CMD:sit(playerid, params[]) {
	
	UseAnim(playerid,"PED","SEAT_down",4.0,false,false,true,true,0);
	return true;
}

CMD:aim(playerid, params[]) {
	
	UseAnim(playerid,"PED","gang_gunstand",3.0,false,true,true,true,0);
	return true;
}

CMD:cellin(playerid, params[]) {
	
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
	return true;
}

CMD:cellout(playerid, params[]) {
	
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
	return true;
}


CMD:drunk(playerid, params[]) {
	
	UseAnim(playerid,"PED","WALK_DRUNK",4.1,true,true,true,true,1);
	return true;
}

CMD:bomb(playerid, params[]) {
	
	UseAnim(playerid, "BOMBER","BOM_Plant",4.0,false,false,false,false,0);
	return true;
}

CMD:bar(playerid, params[]) {
	
	UseAnim(playerid,"BAR","Barserve_bottle",4.0,false,false,false,false,0);
	return true;
}

CMD:stoptaxi(playerid, params[]) {
	
	UseAnim(playerid,"PED","IDLE_taxi",4.0,false,false,false,false,0);
	return true;
}

CMD:getarrested(playerid, params[]) {
	
	UseAnim(playerid,"ped", "ARRESTgun", 4.0, false, true, true, true, -1);
	return true;
}

CMD:laugh(playerid, params[]) {
	
	UseAnim(playerid, "RAPPING", "Laugh_01", 4.0, false, false, false, false, 0);
	return true;
}

CMD:lookout(playerid, params[]) {
	
	UseAnim(playerid, "SHOP", "ROB_Shifty", 4.0, false, false, false, false, 0);
	return true;
}

CMD:crossarms(playerid, params[]) {
	
	UseAnim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, false, true, true, true, -1);
	return true;
}

CMD:hide(playerid, params[]) {
	
	UseAnim(playerid, "ped", "cower", 3.0, true, false, false, false, 0);
	return true;
}

CMD:vomit(playerid, params[]) {
	
	UseAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, false, false, false, false, 0);
	return true;
}

CMD:eat(playerid, params[]) {
	
	UseAnim(playerid, "FOOD", "EAT_Burger", 4.1,true,true,true,true,1);
	return true;
}

CMD:sipdrink(playerid, params[]) {
	
	UseAnim(playerid, "GANGS", "drnkbr_prtl", 4.1,true,true,true,true,1);
	return true;
}

CMD:slapass(playerid, params[]) {
	
	UseAnim(playerid, "SWEET", "sweet_ass_slap", 4.0, false, false, false, false, 0);
	return true;
}

CMD:chat(playerid, params[]) {
	
	UseAnim(playerid,"PED","IDLE_CHAT",4.0,true,false,false,true,1);
	return true;
}

CMD:fucku(playerid, params[]) {
	
	UseAnim(playerid,"PED","fucku",4.0,false,false,false,false,0);
	return true;
}

CMD:taichi(playerid, params[]) {
	
	UseAnim(playerid,"PARK","Tai_Chi_Loop",4.0,true,false,false,false,0);
	return true;
}

CMD:injured(playerid, params[]) {
	
	UseAnim(playerid, "SWEET", "Sweet_injuredloop", 4.0,false,false,true,true,0);
	return true;
}

CMD:no(playerid, params[]) {
	
	UseAnim(playerid,"GANGS","Invite_No",4.0,false,false,false,false,0);
	return true;
}

CMD:yes(playerid, params[]) {
	
	UseAnim(playerid,"GANGS","Invite_Yes",4.0,false,false,false,false,0);
	return true;
}

CMD:crawl(playerid, params[]) {
	
	UseAnim(playerid,"PED","CAR_crawloutRHS",4.0,false,false,false,false,0);
	return true;
}

CMD:push(playerid, params[]) {
	
	UseAnim(playerid,"GANGS","shake_cara",4.0,false,false,false,false,0);
	return true;
}

CMD:akick(playerid, params[]) {
	
	UseAnim(playerid,"POLICE","Door_Kick",4.0,false,false,false,false,0);
	return true;
}

CMD:facepalm(playerid, params[]) {
	
	UseAnim(playerid,"MISC","plyr_shkhead",4.0,false,false,false,false,0);
	return true;
}

CMD:balls(playerid, params[]) {
	
	UseAnim(playerid,"MISC","scratchballs_01",4.0,false,false,false,false,0);
	return true;
}

CMD:lowbodypush(playerid, params[]) {
	UseAnim(playerid,"GANGS","shake_carSH",4.0,false,false,false,false,0);
	return true;
}

CMD:aspray(playerid, params[]) {
	
	UseAnim(playerid,"SPRAYCAN","spraycan_full",4.0,false,false,false,false,0);
	return true;
}

CMD:medic(playerid, params[]) {
	
	UseAnim(playerid,"MEDIC","CPR",4.0,false,false,false,false,0);
	return true;
}

CMD:koface(playerid, params[]) {
	
	UseAnim(playerid,"PED","KO_shot_face",4.0,false,true,true,true,0);
	return true;
}

CMD:kostomach(playerid, params[]) {
	
	UseAnim(playerid,"PED","KO_shot_stom",4.0,false,true,true,true,0);
	return true;
}

CMD:lifejump(playerid, params[]) {
	
	UseAnim(playerid,"PED","EV_dive",4.0,false,true,true,true,0);
	return true;
}

CMD:rollfall(playerid, params[]) {
	
	UseAnim(playerid,"PED","BIKE_fallR",4.0,false,true,true,true,0);
	return true;
}

CMD:hoodfrisked(playerid, params[]) {
	
	UseAnim(playerid,"POLICE","crm_drgbst_01",1.0,false,true,true,true,0);
	return true;
}

CMD:flip(playerid, params[]) {
	
	UseAnim(playerid,"PED","KD_left",4.1,false,true,true,true,0);
	return true;
}

CMD:box(playerid, params[]) {
	
	UseAnim(playerid,"GYMNASIUM","GYMshadowbox",4.0,true,true,true,true,0);
	return true;
}

CMD:chant(playerid, params[]) {
	
	UseAnim(playerid,"RIOT","RIOT_CHANT",4.0,true,true,true,true,0);
	return true;
}

CMD:finger(playerid, params[]) {
	
	UseAnim(playerid,"RIOT","RIOT_FUKU",2.0,false,false,false,false,0);
	return true;
}

CMD:gpunch(playerid, params[]) {
	
	UseAnim(playerid,"FIGHT_B","FightB_G",4.0,false,false,false,false,0);
	return true;
}

CMD:gkick(playerid, params[]) {
	
	UseAnim(playerid,"FIGHT_D","FightD_G",4.0,false,false,false,false,0);
	return true;
}

CMD:lowthrow(playerid, params[]) {
	
	UseAnim(playerid,"GRENADE","WEAPON_throwu",3.0,false,false,false,false,0);
	return true;
}

CMD:riot(playerid, params[]) {
	
	UseAnim(playerid,"RIOT","RIOT_ANGRY",4.0,false,false,false,false,0);
	return true;
}

CMD:abp(playerid, params[]) {
	
	UseAnim(playerid,"benchpress","gym_bp_celebrate",4.0,false,false,false,false,0);
	return true;
}

CMD:cry(playerid, params[]) {
	
	UseAnim(playerid,"GRAVEYARD","mrnF_loop",4.0,true,false,false,false,0);
	return true;
}

CMD:taxir(playerid, params[]) {
	
	UseAnim(playerid, "MISC","hiker_pose", 3.0,false,true,true,true,0);
	return true;
}

CMD:taxil(playerid, params[]) {
	
	UseAnim(playerid, "MISC","hiker_pose_L", 3.0,false,true,true,true,0);
	return true;
}

CMD:gro(playerid, params[]) {
	
	UseAnim(playerid,"BEACH", "ParkSit_M_loop", 4.0, true, false, false, false, 0);
	return true;
}

CMD:seat(playerid, params[]) {
	
	UseAnim(playerid,"INT_HOUSE","LOU_In",4.0,false,false,true,true,0);
	return true;
}

CMD:tatto(playerid, params[]) {
	
	UseAnim(playerid,"TATTOOS", "TAT_ArmR_Pose_P", 4.1, false, true, true, true, 0);
	return true;
}

CMD:waiml(playerid, params[]) 
{
	
	UseAnim(playerid,"PED","Driveby_L",4.1,false,true,true,true,1);
	return 1;
}

CMD:waimr(playerid, params[]) {
	
	UseAnim(playerid,"PED","Driveby_R",4.1,false,true,true,true,1);
	return true;
}

CMD:caim(playerid, params[]) {
	
	UseAnim(playerid,"PED","IDLE_ROCKET",4.1,false,true,true,true,1);
	return true;
}

CMD:creep(playerid, params[]) {
	
	UseAnim(playerid,"PED","Player_Sneak",4.1,true,true,true,true,1);
	return true;
}

CMD:sroll(playerid, params[]) {
	
	UseAnim(playerid,"SWAT","JMP_Wall1m_180",4.1,false,true,true,true,0);
	return true;
}

CMD:gesture(playerid, params[]) {
	
	UseAnim(playerid,"SWAT","swt_lkt",4.0,false,false,false,false,0);
	return true;
}

CMD:lookoutr(playerid, params[]) {
	
	UseAnim(playerid,"SWAT","swt_wllpk_L",4.0,false,false,true,true,0);
	return true;
}

CMD:lookoutl(playerid, params[]) {
	
	UseAnim(playerid,"SWAT","swt_wllpk_R",4.0,false,false,true,true,0);
	return true;
}

CMD:agreement(playerid, params[]) {
	
	UseAnim(playerid,"COP_AMBIENT","Coplook_think",4.0,true,false,false,false,0);
	return true;
}

CMD:bend(playerid, params[]) {
	
	UseAnim(playerid,"BAR","Barserve_order",4.0,false,false,false,false,0);
	return true;
}

CMD:rod(playerid, params[]) {
	
	UseAnim(playerid,"benchpress","gym_bp_up_A",4.0,false,false,true,true,0);
	return true;
}

CMD:tgro(playerid, params[]) {
	
	UseAnim(playerid,"CAMERA","camcrch_cmon",4.0,false,false,true,true,0);
	return true;
}

CMD:cmouth(playerid, params[]) {
	
	UseAnim(playerid,"ON_LOOKERS","panic_in",4.0,false,false,true,true,0);
	return true;
}

CMD:gog(playerid, params[]) {
	
	UseAnim(playerid,"goggles","goggles_put_on",4.1,false,true,true,true,1);
	return true;
}

CMD:nfall(playerid, params[]) {
	
	UseAnim(playerid,"HEIST9","CAS_G2_GasKO",4.1,false,true,true,true,0);
	return true;
}

CMD:hsit(playerid, params[]) {
	
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Bored_Loop",4.0,true,false,true,true,0);
	return true;
}

CMD:csit(playerid, params[]) {
	
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Type_Loop",4.0,true,false,true,true,0);
	return true;
}

CMD:bracing(playerid, params[]) {
	
	UseAnim(playerid,"PLAYIDLES","stretch",4.0,false,false,false,false,0);
	return true;
}

CMD:pool(playerid, params[]) {
	
	UseAnim(playerid,"POOL","POOL_Long_Start",4.1,false,true,true,true,0);
	return true;
}

CMD:ssearch(playerid, params[]) {
	
	UseAnim(playerid,"ROB_BANK","CAT_Safe_Rob",4.0,true,false,false,false,0);
	return true;
}

CMD:daim(playerid, params[]) {
	
	UseAnim(playerid,"RYDER","Van_Stand_Crate",3.0,false,true,true,true,0);
	return true;
}

CMD:rhandl(playerid, params[]) {
	
	UseAnim(playerid,"SCRATCHING","scdlulp",4.0,false,false,true,true,0);
	return true;
}

CMD:rhandr(playerid, params[]) {
	
	UseAnim(playerid,"SCRATCHING","scdrulp",4.0,false,false,true,true,0);
	return true;
}

CMD:hstand(playerid, params[]) {
	
	UseAnim(playerid,"SCRATCHING","scdrdlp",4.0,false,false,true,true,0);
	return true;
}

CMD:nlean(playerid, params[]) {
	
	UseAnim(playerid,"SHAMAL","SHAMAL_align",4.1,false,true,true,true,0);
	return true;
}

CMD:shelter(playerid, params[]) {
	
	UseAnim(playerid,"SHOP","SHP_Duck_Fire",4.0,false,false,true,true,0);
	return true;
}

CMD:lookback(playerid, params[]) {
	
	UseAnim(playerid,"PED","flee_lkaround_01",4.0,false,false,false,false,0);
	return true;
}

CMD:wsit(playerid, params[]) {
	
	UseAnim(playerid,"SHOP","SHP_Gun_Duck",4.0,false,false,true,true,0);
	return true;
}

CMD:waim(playerid, params[]) {
	
	UseAnim(playerid,"TEC","TEC_reload",4.1,false,true,true,true,1);
	return true;
}

CMD:hangon(playerid, params[]) {
	
	UseAnim(playerid,"TRAIN","tran_ouch",4.0,false,false,true,true,0);
	return true;
}

CMD:sleepl(playerid, params[]) {
	
	UseAnim(playerid,"INT_HOUSE","BED_In_L",4.0,false,false,true,true,0);
	return true;
}

CMD:sleepr(playerid, params[]) {
	
	UseAnim(playerid,"INT_HOUSE","BED_In_R",4.0,false,false,true,true,0);
	return true;
}

CMD:blowj(playerid, params[]) {
	
	UseAnim(playerid,"BLOWJOBZ", "BJ_COUCH_START_W", 4.1, false, true, true, true, 0 );
	return true;
}

CMD:rseat(playerid, params[]) {
	
	UseAnim(playerid,"BLOWJOBZ", "BJ_COUCH_START_P", 4.1, false, true, true, true, 0 );
	return true;
}

CMD:polwalk(playerid, params[]) {
	
	UseAnim(playerid,"POLICE","Cop_move_FWD",3.0,true,true,true,true,1);
	return true;
}

CMD:nflip(playerid, params[]) {
	
	UseAnim(playerid,"PED","BIKE_fall_off",4.1,false,true,true,true,0);
	return true;
}

CMD:csdead(playerid, params[]) {
	
	UseAnim(playerid,"WUZI","CS_Dead_Guy",4.1,false,true,true,true,0);
	return true;
}

CMD:follow(playerid, params[]) {
	
	UseAnim(playerid,"WUZI","Wuzi_follow",4.1,false,true,true,true,1);
	return true;
}

CMD:grnd(playerid, params[]) {
	
	UseAnim(playerid,"WUZI","Wuzi_grnd_chk",4.0,false,false,false,false,0);
	return true;
}

CMD:copa(playerid, params[]) {
	
	UseAnim(playerid,"COP_AMBIENT","Copbrowse_in",4.1,false,true,true,true,0);
	return true;
}

CMD:cmon(playerid, params[]) {
	
	UseAnim(playerid,"OTB","wtchrace_cmon",4.1,false,true,true,true,0);
	return true;
}

CMD:lose(playerid, params[]) {
	
	UseAnim(playerid,"OTB","wtchrace_lose",4.1,false,true,true,true,0);
	return true;
}

CMD:win(playerid, params[]) {
	
	UseAnim(playerid,"OTB","wtchrace_win",4.1,false,true,true,true,0);
	return true;
}

CMD:gunthreat(playerid, params[]) {
	
	UseAnim(playerid,"SHOP","SHP_Gun_Threat",4.1,false,true,true,true,0);
	return true;
}

CMD:givecash(playerid, params[]) {
	
	UseAnim(playerid,"SHOP","SHP_Rob_GiveCash",4.1,false,true,true,true,0);
	return true;
}

CMD:robr(playerid, params[]) {
	
	UseAnim(playerid,"SHOP","SHP_Rob_React",4.1,false,true,true,true,0);
	return true;
}

CMD:serend(playerid, params[]) {
	
	UseAnim(playerid,"SHOP","SHP_Serve_End",4.1,false,true,true,true,0);
	return true;
}

CMD:heist(playerid, params[]) {
	
	UseAnim(playerid,"HEIST9","Use_SwipeCard",4.0,false,false,false,false,0);
	return true;
}

CMD:frontfall(playerid, params[]) {
	
	UseAnim(playerid,"PED","FLOOR_hit_f",4.1,false,true,true,true,0);
	return true;
}

CMD:pants(playerid, params[]) {
	
	UseAnim(playerid,"BLOWJOBZ","BJ_STAND_END_P",4.0,false,false,false,false,0);
	return true;
}
/////////////////////////////////////////////////////////////////////////
CMD:tired(playerid, params[]) {
	
	UseAnim(playerid,"FAT","IDLE_tired",4.0,false,false,true,true,0);
	return true;
}

CMD:climb(playerid, params[]) {
	
	UseAnim(playerid,"PED","CLIMB_jump",4.0,false,false,true,true,0);
	return true;
}

CMD:tlean(playerid, params[]) {
	
	UseAnim(playerid,"PED","DRIVE_BOAT",4.0,false,false,true,true,0);
	return true;
}

CMD:pushup(playerid, params[]) {
	
	UseAnim(playerid,"PED","getup_front",4.0,true,false,true,true,0);
	return true;
}

CMD:protection(playerid, params[]) {
	
	UseAnim(playerid,"PED","FightShB",4.0,false,true,true,true,1);
	return true;
}

CMD:swallow(playerid, params[]) {
	
	UseAnim(playerid,"PED","gum_eat",4.0,false,false,false,false,0);
	return true;
}

CMD:stand(playerid, params[]) {
	
	UseAnim(playerid,"PED","IDLE_HBHB",3.0,false,true,true,true,0);
	return true;
}

CMD:pullhand(playerid, params[]) {
	
	UseAnim(playerid,"PED","Jetpack_Idle",3.0,false,true,true,true,0);
	return true;
}

CMD:nlook(playerid, params[]) {
	
	UseAnim(playerid,"PED","roadcross_gang",4.0,false,false,false,false,0);
	return true;
}

CMD:extend(playerid, params[]) {
	
	UseAnim(playerid,"PED","Shove_Partial",4.1,false,true,true,true,1);
	return true;
}

CMD:stopit(playerid, params[]) {
	
	UseAnim(playerid,"PED","Walk_DoorPartial",4.0,false,false,false,false,0);
	return true;
}

CMD:ksit(playerid, params[]) {
	
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Crash",4.0,true,false,true,true,0);
	return true;
}

CMD:esit(playerid, params[]) {
	
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Drink",4.0,true,false,true,true,0);
	return true;
}

CMD:tsit(playerid, params[]) {
	
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Watch",4.0,false,false,true,true,0);
	return true;
}

CMD:rtake(playerid, params[]) {
	
	UseAnim(playerid,"BAR","Barserve_give",4.0,false,false,false,false,0);
	return true;
}

CMD:forwardlook(playerid, params[]) {
	
	UseAnim(playerid,"BD_FIRE","BD_Panic_02",4.1,false,true,true,true,0);
	return true;
}

CMD:wforwardlook(playerid, params[]) {
	
	UseAnim(playerid,"BD_FIRE","BD_Panic_03",4.1,false,true,true,true,0);
	return true;
}

CMD:taction(playerid, params[]) {
	
	UseAnim(playerid,"BD_FIRE","wash_up",4.0,false,false,false,false,0);
	return true;
}

CMD:catch(playerid, params[]) {
	
	UseAnim(playerid,"MD_CHASE","MD_HANG_Loop",4.1,false,true,true,true,0);
	return true;
}

CMD:despair(playerid, params[]) {
	
	UseAnim(playerid,"BSKTBALL","BBALL_react_miss",4.0,false,false,false,false,0);
	return true;
}

CMD:rooting(playerid, params[]) {
	
	UseAnim(playerid,"BSKTBALL","BBALL_react_score",4.1,true,true,true,true,0);
	return true;
}

CMD:spyglass(playerid, params[]) {
	
	UseAnim(playerid,"CAMERA","picstnd_take",4.1,false,true,true,true,0);
	return true;
}

CMD:looksky(playerid, params[]) {
	
	UseAnim(playerid,"ON_LOOKERS","lkup_loop",4.1,false,true,true,true,0);
	return true;
}

CMD:mshow(playerid, params[]) {
	
	UseAnim(playerid,"ON_LOOKERS","panic_point",4.1,false,true,true,true,0);
	return true;
}

CMD:wshow(playerid, params[]) {
	
	UseAnim(playerid,"ON_LOOKERS","panic_shout",4.1,false,true,true,true,0);
	return true;
}

CMD:hshow(playerid, params[]) {
	
	UseAnim(playerid,"ON_LOOKERS","point_loop",4.1,false,true,true,true,0);
	return true;
}

CMD:sh(playerid, params[]) {
	
	UseAnim(playerid,"ON_LOOKERS","shout_in",4.0,false,false,false,false,0);
	return true;
}

CMD:crossfingers(playerid, params[]) {
	
	UseAnim(playerid,"CASINO","cards_loop",4.1,false,true,true,true,0);
	return true;
}

CMD:delight(playerid, params[]) {
	
	UseAnim(playerid,"CASINO","manwinb",4.0,false,false,false,false,0);
	return true;
}

CMD:hdelight(playerid, params[]) {
	
	UseAnim(playerid,"CASINO","manwind",4.0,false,false,false,false,0);
	return true;
}

CMD:showtable(playerid, params[]) {
	
	UseAnim(playerid,"CASINO","Roulette_bet",4.1,false,true,true,true,0);
	return true;
}

CMD:tfacepalm(playerid, params[]) {
	
	UseAnim(playerid,"CASINO","Roulette_lose",4.1,false,true,true,true,0);
	return true;
}

CMD:tpull(playerid, params[]) {
	
	UseAnim(playerid,"CASINO","Slot_in",4.1,false,true,true,true,0);
	return true;
}

CMD:fail(playerid, params[]) {
	
	UseAnim(playerid,"CASINO","Slot_lose_out",4.0,false,false,false,false,0);
	return true;
}

CMD:joy(playerid, params[]) {
	
	UseAnim(playerid,"CASINO","Slot_win_out",4.0,false,false,false,false,0);
	return true;
}

CMD:wear(playerid, params[]) {
	
	UseAnim(playerid,"CARRY","crry_prtial",4.1,false,true,true,true,1);
	return true;
}

CMD:fsit(playerid, params[]) {
	
	UseAnim(playerid,"JST_BUISNESS","girl_02",4.1,false,true,true,true,0);
	return true;
}

CMD:crushjump(playerid, params[]) {
	
	UseAnim(playerid,"DODGE","Crush_Jump",4.1,false,true,true,true,0);
	return true;
}

CMD:scatch(playerid, params[]) {
	
	UseAnim(playerid,"FINALE","FIN_LegsUp_Loop",4.1,false,true,true,true,0);
	return true;
}

CMD:lookfloor(playerid, params[]) {
	
	UseAnim(playerid,"FINALE","FIN_Cop1_Loop",4.1,false,true,true,true,0);
	return true;
}

CMD:tramplefloor(playerid, params[]) {
	
	UseAnim(playerid,"FINALE","FIN_Cop1_Stomp",4.1,true,true,true,true,0);
	return true;
}

CMD:swing(playerid, params[]) {
	
	UseAnim(playerid,"Freeweights","gym_free_B",4.1,false,true,true,true,0);
	return true;
}

CMD:nbp(playerid, params[]) {
	
	UseAnim(playerid,"Freeweights","gym_free_celebrate",4.0,false,false,false,false,0);
	return true;
}

CMD:takehead(playerid, params[]) {
	
	UseAnim(playerid,"HAIRCUTS","BRB_Cut",4.1,false,true,true,true,0);
	return true;
}

CMD:readtable(playerid, params[]) {
	
	UseAnim(playerid,"SCRATCHING","sclng_r",4.1,false,true,true,true,0);
	return true;
}

CMD:squat(playerid, params[]) {
	
	UseAnim(playerid,"TEC","TEC_crouchfire",4.1,false,true,true,true,0);
	return true;
}

CMD:sprawl(playerid, params[]) {
	
	UseAnim(playerid,"TATTOOS","TAT_Idle_Loop_T",4.1,false,true,true,true,0);
	return true;
}

CMD:throwmoney(playerid, params[]) {
	
	UseAnim(playerid,"STRIP","PUN_CASH",4.0,false,false,false,false,0);
	return true;
}

CMD:sho(playerid, params[]) {
	
	UseAnim(playerid,"STRIP","PUN_HOLLER",4.0,false,false,false,false,0);
	return true;
}

CMD:faim(playerid, params[]) {
	
	UseAnim(playerid,"SWORD","sword_IDLE",4.1,false,true,true,true,0);
	return true;
}

CMD:piss(playerid, params[]) {
	
	UseAnim(playerid,"PAULNMAC","Piss_in",4.1,false,true,true,true,0);
	return true;
}

CMD:swingback(playerid, params[]) {
	
	UseAnim(playerid,"PED","getup",4.1,true,true,true,true,0);
	return true;
}

CMD:onehand(playerid, params[]) {
	
	UseAnim(playerid,"PED","CLIMB_jump2fall",4.1,false,true,true,true,0);
	return true;
}

CMD:backwalk(playerid, params[]) {
	
	UseAnim( playerid, "PED", "gas_cwr", 4.1, true, true, true, true, 1 );
	return true;
}

CMD:feettog(playerid, params[]) {
	
	UseAnim(playerid,"PED","Idlestance_fat",4.1,false,true,true,true,0);
	return true;
}

CMD:mirro(playerid, params[]) {
	
	UseAnim(playerid,"CLOTHES","CLO_Pose_Hat",4.1,false,true,true,true,0);
	return true;
}

CMD:hips(playerid, params[]) {
	
	UseAnim(playerid,"COP_AMBIENT","Coplook_shake",4.1,false,true,true,true,0);
	return true;
}

CMD:pullo(playerid, params[]) {
	
	UseAnim(playerid,"AIRPORT","thrw_barl_thrw",4.1,false,true,true,true,0);
	return true;
}

CMD:obalance(playerid, params[]) {
	
	UseAnim(playerid,"BD_FIRE","BD_Panic_02",4.1,false,true,true,true,0);
	return true;
}

CMD:wobalance(playerid, params[]) {
	
	UseAnim(playerid,"BD_FIRE","BD_Panic_03",4.1,false,true,true,true,0);
	return true;
}

CMD:dance(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /dance [1-12]");
	switch(params[0]) {
		case 1 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
		case 2 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
		case 3 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
		case 4 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
		case 5 : UseAnim(playerid,"DANCING","bd_clap",4.1,true,true,true,true,1);
		case 6 : UseAnim(playerid,"DANCING","bd_clap1",4.1,true,true,true,true,1);
		case 7 : UseAnim(playerid,"DANCING","DAN_Down_A",4.1,true,true,true,true,1);
		case 8 : UseAnim(playerid,"DANCING","DAN_Left_A",4.1,true,true,true,true,1);
		case 9 : UseAnim(playerid,"DANCING","DAN_Loop_A",4.1,true,true,true,true,1);
		case 10 : UseAnim(playerid,"DANCING","DAN_Right_A",4.1,true,true,true,true,1);
		case 11 : UseAnim(playerid,"DANCING","DAN_Up_A",4.1,true,true,true,true,1);
		case 12 : UseAnim(playerid,"DANCING","dnce_M_a",4.1,true,true,true,true,1);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /dance [1-12]");
	}
	return true;
}

CMD:repcar(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /repcar [1-2]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"CAR","Fixn_Car_Loop",3.0,false,true,true,true,0);
		case 2 : UseAnim(playerid,"CAR","Fixn_Car_Out",3.0,false,true,true,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /repcar [1-2]");
	}
	return true;
}


CMD:hnds(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /hnds [1-7]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkB",4.1,false,true,true,true,1);
		case 2 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkC",4.1,false,true,true,true,1);
		case 3 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkD",4.1,false,true,true,true,1);
		case 4 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkE",4.1,false,true,true,true,1);
		case 5 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkF",4.1,false,true,true,true,1);
		case 6 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkG",4.1,false,true,true,true,1);
		case 7 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkH",4.1,false,true,true,true,1);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /hnds [1-7]");
	}
	return true;
}

CMD:strip(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /strip [1-14]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"STRIP", "strip_A", 4.1, true, true, true, true, 1 );
		case 2 : UseAnim(playerid,"STRIP", "strip_B", 4.1, true, true, true, true, 1 );
		case 3 : UseAnim(playerid,"STRIP", "strip_C", 4.1, true, true, true, true, 1 );
		case 4 : UseAnim(playerid,"STRIP", "strip_D", 4.1, true, true, true, true, 1 );
		case 5 : UseAnim(playerid,"STRIP", "strip_E", 4.1, true, true, true, true, 1 );
		case 6 : UseAnim(playerid,"STRIP", "strip_F", 4.1, true, true, true, true, 1 );
		case 7 : UseAnim(playerid,"STRIP", "strip_G", 4.1, true, true, true, true, 1 );
     	case 8: ApplyAnimation(playerid,"STRIP","STR_A2B",4.1,true,true,true,true,1);
        case 9: ApplyAnimation(playerid,"STRIP","STR_B2C",4.1,true,true,true,true,1);
        case 10: ApplyAnimation(playerid,"STRIP","STR_C1",4.1,true,true,true,true,1);
        case 11: ApplyAnimation(playerid,"STRIP","STR_C2",4.1,true,true,true,true,1);
        case 12: ApplyAnimation(playerid,"STRIP","STR_Loop_A",4.1,true,true,true,true,1);
        case 13: ApplyAnimation(playerid,"STRIP","STR_Loop_B",4.1,true,true,true,true,1);
        case 14: ApplyAnimation(playerid,"STRIP","STR_Loop_C",4.1,true,true,true,true,1);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /strip [1-14]");
	}
	return true;
}


CMD:deal(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /deal [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid, "DEALER", "DEALER_DEAL", 4.0, false, false, false, false, 0);
		case 2 : UseAnim(playerid, "DEALER","DEALER_IDLE", 3.0,false,true,true,true,0);
		case 3 : UseAnim(playerid,"GRAVEYARD","mrnM_loop",3.0,false,true,true,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /deal [1-3]");
	}
	return true;
}

CMD:asmoke(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /asmoke [1-6]");
	switch(params[0]) {
		case 1 : UseAnim(playerid, "SMOKING", "M_smklean_loop", 4.0, true, false, false, false, 0);
		case 2 : UseAnim(playerid, "SMOKING", "F_smklean_loop", 4.0, true, false, false, false, 0);
		case 3 : UseAnim(playerid, "SMOKING","M_smkstnd_loop", 4.0, true, false, false, false, 0);
		case 4 : UseAnim(playerid, "SMOKING","M_smk_out", 4.0, false, false, false, false, 0);
		case 5 : UseAnim(playerid, "SMOKING","M_smk_in",3.0,false,false,false,false,0);
		case 6 : UseAnim(playerid, "SMOKING","M_smk_tap",3.0,false,false,false,false,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /asmoke [1-6]");
	}
	return true;
}

CMD:rap(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /rap [1-9]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"RAPPING","RAP_A_Loop",4.0,true,false,false,false,0);
		case 2 : UseAnim(playerid,"RAPPING","RAP_C_Loop",4.0,true,false,false,false,0);
		case 3 : UseAnim(playerid,"GANGS","prtial_gngtlkD",4.0,true,false,false,true,1);
		case 4 : UseAnim(playerid,"GANGS","prtial_gngtlkH",4.0,true,false,false,true,1);
		case 5 : UseAnim(playerid,"GANGS","prtial_gngtlkF",4.0,true,false,false,true,1);
		case 6 : UseAnim(playerid,"GANGS","prtial_gngtlkG",4.0,true,false,false,true,1);
		case 7 : UseAnim(playerid,"PED","ATM",4.0,false,false,false,false,0);
		case 8 : UseAnim(playerid,"RAPPING","RAP_B_IN",3.0,false,true,true,true,0);
		case 9 : UseAnim(playerid,"GYMNASIUM","gym_tread_celebrate",4.1,false,true,true,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /rap [1-9]");
	}
	return true;
}

CMD:bat(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /bat [1-2]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"CRACK","Bbalbat_Idle_02",4.0, true, false, false, false, 0);
		case 2 : UseAnim(playerid,"CRACK","Bbalbat_Idle_01",4.0, true, false, false, false, 0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /bat [1-2]");
	}
	return true;
}

CMD:basket(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /basket [1-6]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"BSKTBALL","BBALL_idleloop",4.0,true,false,false,false,0);
		case 2 : UseAnim(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,false,false,false,false,0);
		case 3 : UseAnim(playerid,"BSKTBALL","BBALL_pickup",4.0,false,false,false,false,0);
		case 4 : UseAnim(playerid,"BSKTBALL","BBALL_run",4.1,true,true,true,true,1);
		case 5 : UseAnim(playerid,"BSKTBALL","BBALL_def_loop",4.0,true,false,false,false,0);
		case 6 : UseAnim(playerid,"BSKTBALL","BBALL_Dnk",4.0,false,false,false,false,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /basket [1-6]");
	}
	return true;
}

CMD:lean(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /lean [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"GANGS","leanIDLE",4.0,false,false,true,true,0);
		case 2 : UseAnim(playerid,"MISC","Plyrlean_loop",4.0,false,true,true,true,0);
		case 3 : UseAnim(playerid,"CAR_CHAT","car_talkm_loop",4.0,false,true,true,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /lean [1-3]");
	}
	return true;
}

CMD:lay(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /lay [1-5]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"BEACH", "bather", 4.0, true, false, false, false, 0);
		case 2 : UseAnim(playerid,"SUNBATHE","Lay_Bac_in",3.0,false,true,true,true,0);
		case 3 : UseAnim(playerid,"BEACH","ParkSit_W_loop",3.0,false,true,true,true,0);
		case 4 : UseAnim(playerid,"BEACH","SitnWait_loop_W",4.0, true, false, false, false, 0);
		case 5 : UseAnim(playerid,"SUNBATHE","SBATHE_F_LieB2Sit",3.0,false,true,true,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /lay [1-5]");
	}
	return true;
}

CMD:gsign(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /gsign [1-10]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"GHANDS","gsign1",4.1,false,true,true,true,1);
		case 2 : UseAnim(playerid,"GHANDS","gsign1LH",4.1,false,true,true,true,1);
		case 3 : UseAnim(playerid,"GHANDS","gsign2",4.1,false,true,true,true,1);
		case 4 : UseAnim(playerid,"GHANDS","gsign2LH",4.1,false,true,true,true,1);
		case 5 : UseAnim(playerid,"GHANDS","gsign3",4.1,false,true,true,true,1);
		case 6 : UseAnim(playerid,"GHANDS","gsign3LH",4.1,false,true,true,true,1);
		case 7 : UseAnim(playerid,"GHANDS","gsign4",4.1,false,true,true,true,1);
		case 8 : UseAnim(playerid,"GHANDS","gsign4LH",4.1,false,true,true,true,1);
		case 9 : UseAnim(playerid,"GHANDS","gsign5",4.1,false,true,true,true,1);
		case 10 : UseAnim(playerid,"GHANDS","gsign5LH",4.1,false,true,true,true,1);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /gsign [1-10]");
	}
	return true;
}

CMD:wave(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /wave [1-4]");
	switch(params[0]) {
		case 1 : UseAnim(playerid, "KISSING","gfwave2", 4.1,false,true,true,false,0);
		case 2 : UseAnim(playerid, "ON_LOOKERS","wave_loop", 4.1,true,true,true,false,0);
		case 3 : UseAnim(playerid,"CAMERA","camstnd_cmon",4.0,false,false,false,false,0);
		case 4 : UseAnim(playerid,"PED","endchat_01",4.1,false,true,true,false,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /wave [1-4]");
	}
	return true;
}

CMD:police(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /police [1-4]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"POLICE","CopTraf_Away",3.0,true,false,false,true,0);
		case 2 : UseAnim(playerid,"POLICE","CopTraf_Come",3.0,true,false,false,true,0);
		case 3 : UseAnim(playerid,"POLICE","CopTraf_Left",3.0,true,false,false,true,0);
		case 4 : UseAnim(playerid,"POLICE","CopTraf_Stop",3.0,true,false,false,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /police [1-4]");
	}
	return true;
}

CMD:crack(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /crack [1-7]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"CRACK","crckdeth2",3.0,true,true,true,true,0);
		case 2 : UseAnim(playerid,"CRACK","crckdeth4",3.0,false,true,true,true,0);
		case 3 : UseAnim(playerid,"CRACK","crckidle1",3.0,false,true,true,true,0);
		case 4 : UseAnim(playerid,"CRACK","crckidle2",3.0,false,true,true,true,0);
		case 5 : UseAnim(playerid,"CRACK","crckidle3",3.0,false,true,true,true,0);
		case 6 : UseAnim(playerid,"CRACK","crckdeth1",3.0,false,true,true,true,0);
		case 7 : UseAnim(playerid,"CRACK","crckdeth3",3.0,false,true,true,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /crack [1-7]");
	}
	return true;
}

CMD:car_anim(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /car [1-11]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"LOWRIDER","lrgirl_bdbnce",4.1,false,true,true,true,0);
		case 2 : UseAnim(playerid,"LOWRIDER","lrgirl_hair",4.1,false,true,true,true,0);
		case 3 : UseAnim(playerid,"LOWRIDER","lrgirl_idle_to_l0",4.1,false,true,true,true,0);
		case 4 : UseAnim(playerid,"PED","Tap_hand",4.1,false,true,true,true,0);
		case 5 : UseAnim(playerid,"PED","Tap_handP",4.1,false,true,true,true,0);
		case 6 : UseAnim(playerid,"LOWRIDER","lrgirl_l12_to_l0",4.1,false,true,true,true,0);
		case 7 : UseAnim(playerid,"LOWRIDER","lrgirl_l2_to_l3",4.1,false,true,true,true,0);
		case 8 : UseAnim(playerid,"PED","CAR_LB",4.1,false,true,true,true,0);
		case 9 : UseAnim(playerid,"PED","CAR_sitp",4.1,false,true,true,true,0);
		case 10 : UseAnim(playerid,"PED","CAR_sitpLO",4.1,false,true,true,true,0);
		case 11 : UseAnim(playerid,"CAR_CHAT","carfone_loopA",4.1,true,true,true,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /car [1-11]");
	}
	return true;
}

CMD:wallow(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /wallow [1-2]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll",4.1,false,true,true,true,0);
		case 2 : UseAnim(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll_F",4.1,false,true,true,true,0);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /wallow [1-2]");
	}
	return true;
}

CMD:beckon(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /beckon [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"RYDER","RYD_Beckon_01",4.1,false,true,true,true,1);
		case 2 : UseAnim(playerid,"RYDER","RYD_Beckon_02",4.1,false,true,true,true,1);
		case 3 : UseAnim(playerid,"RYDER","RYD_Beckon_03",4.1,false,true,true,true,1);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /beckon [1-3]");
	}
	return true;
}

CMD:shotgun(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /shotgun [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"SHOTGUN","shotgun_crouchfire",4.1,false,true,true,true,1);
		case 2 : UseAnim(playerid,"SHOTGUN","shotgun_fire",4.1,false,true,true,true,1);
		case 3 : UseAnim(playerid,"SHOTGUN","shotgun_fire_poor",4.1,false,true,true,true,1);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /shotgun [1-3]");
	}
	return true;
}

CMD:colt(playerid, params[]) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /colt [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"COLT45","colt45_fire_2hands",4.1,false,true,true,true,1);
		case 2 : UseAnim(playerid,"COLT45","colt45_reload",4.1,false,true,true,true,1);
		case 3 : UseAnim(playerid,"COLT45","sawnoff_reload",4.1,false,true,true,true,1);
		default : SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /colt [1-3]");
	}
	return true;
}

CMD:bj( playerid, params[] ) {
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /bj [1-18]");
	switch (params[0]) {
		  case 1: UseAnim(playerid, "BLOWJOBZ", "BJ_COUCH_START_W", 4.0, true, true, true, true, 1);
		  case 2: UseAnim(playerid, "BLOWJOBZ", "BJ_COUCH_START_P", 4.0, true, true, true, true, 1);
		  case 3: UseAnim(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.0, true, true, true, true, 1);
		  case 4: UseAnim(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.0, true, true, true, true, 1);
		  case 5: UseAnim(playerid, "BLOWJOBZ", "BJ_COUCH_END_W", 4.0, true, true, true, true, 1);
		  case 6: UseAnim(playerid, "BLOWJOBZ", "BJ_COUCH_END_P", 4.0, true, true, true, true, 1);
		  case 7: UseAnim(playerid, "BLOWJOBZ", "BJ_STAND_START_W", 4.0, true, true, true, true, 1);
		  case 8: UseAnim(playerid, "BLOWJOBZ", "BJ_STAND_START_P", 4.0, true, true, true, true, 1);
		  case 9: UseAnim(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.0, true, true, true, true, 1);
		  case 10: UseAnim(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.0, true, true, true, true, 1);
		  case 11: UseAnim(playerid, "BLOWJOBZ", "BJ_STAND_END_W", 4.0, true, true, true, true, 1);
		  case 12: UseAnim(playerid, "BLOWJOBZ", "BJ_STAND_END_P", 4.0, true, true, true, true, 1);
		  case 13: UseAnim(playerid, "BLOWJOBZ", "BJ_CAR_START_W", 4.0, true, true, true, true, 1);
		  case 14: UseAnim(playerid, "BLOWJOBZ", "BJ_CAR_START_P", 4.0, true, true, true, true, 1);
		  case 15: UseAnim(playerid, "BLOWJOBZ", "BJ_CAR_LOOP_W", 4.0, true, true, true, true, 1);
		  case 16: UseAnim(playerid, "BLOWJOBZ", "BJ_CAR_LOOP_P", 4.0, true, true, true, true, 1);
		  case 17: UseAnim(playerid, "BLOWJOBZ", "BJ_CAR_END_W", 4.0, true, true, true, true, 1);
		  case 18: UseAnim(playerid, "BLOWJOBZ", "BJ_CAR_END_P", 4.0, true, true, true, true, 1);
		  default: SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /bj [1-18]");
  	}
  	return 1;
}

CMD:spank( playerid, params[] ) 
{
	
	if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /spank [1-8]");
	switch (params[0]) {
		  case 1: UseAnim(playerid, "SNM", "SPANKING_IDLEW", 4.0, true, true, true, true, 1);
		  case 2: UseAnim(playerid, "SNM", "SPANKING_IDLEP", 4.0, true, true, true, true, 1);
		  case 3: UseAnim(playerid, "SNM", "SPANKINGW", 4.0, true, true, true, true, 1);
		  case 4: UseAnim(playerid, "SNM", "SPANKINGP", 4.0, true, true, true, true, 1);
		  case 5: UseAnim(playerid, "SNM", "SPANKEDW", 4.0, true, true, true, true, 1);
		  case 6: UseAnim(playerid, "SNM", "SPANKEDP", 4.0, true, true, true, true, 1);
		  case 7: UseAnim(playerid, "SNM", "SPANKING_ENDW", 4.0, true, true, true, true, 1);
		  case 8: UseAnim(playerid, "SNM", "SPANKING_ENDP", 4.0, true, true, true, true, 1);
		  default: SendClientMessage(playerid, COLOR_GREY, ""COLOR_WHITE"Введите: /spank [1-8]");
  	}
  	return 1;
}

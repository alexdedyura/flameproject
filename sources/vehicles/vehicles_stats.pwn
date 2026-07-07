GetVehicleFuelConsumption(model) // Расход топлива (литров на 100 км)
{
	new result = 0;

	switch(model)
	{
        case 400: // Landstalker
            result = 13;
        case 401: // Bravura
            result = 10;
        case 402: // Buffalo
            result = 9;
        case 403: // Linerunner
            result = 20;
        case 404: // Perenniel
            result = 11;
        case 405: // Sentinel
            result = 10;
        case 406: // Dumper
            result = 22;
        case 407: // Firetruck
            result = 18;
        case 408: // Trashmaster
            result = 19;
        case 409: // Stretch
            result = 12;
        case 410: // Manana
            result = 10;
        case 411: // Infernus
            result = 8;
        case 412: // Voodoo
            result = 11;
        case 413: // Pony
            result = 16;
        case 414: // Mule
            result = 17;
        case 415: // Cheetah
            result = 9;
        case 416: // Ambulance
            result = 12;
        case 418: // Moonbeam
            result = 12;
        case 419: // Esperanto
            result = 10;
        case 420: // Taxi
            result = 11;
        case 421: // Washington
            result = 10;
        case 422: // Bobcat
            result = 14;
        case 423: // Mr Whoopee
            result = 13;
        case 424: // BF Injection
            result = 12;
        case 426: // Premier
            result = 10;
        case 427: // Enforcer
            result = 13;
        case 428: // Securicar
            result = 14;
        case 429: // Banshee
            result = 8;
        case 431: // Bus
            result = 20;
        case 432: // Rhino
            result = 25;
        case 433: // Barracks
            result = 18;
        case 434: // Hotknife
            result = 9;
        case 436: // Previon
            result = 10;
        case 437: // Coach
            result = 22;
        case 438: // Cabbie
            result = 11;
        case 439: // Stallion
            result = 9;
        case 440: // Rumpo
            result = 15;
        case 442: // Romero
            result = 12;
        case 443: // Packer
            result = 18;
        case 444: // Monster
            result = 20;
        case 445: // Admiral
            result = 10;
        case 448: // Pizzaboy
            result = 6;
        case 451: // Turismo
            result = 8;
        case 455: // Flatbed
            result = 21;
        case 456: // Yankee
            result = 16;
        case 457: // Caddy
            result = 10;
        case 458: // Solair
            result = 11;
        case 459: // Topfun Van (Berkley's RC)
            result = 15;
        case 461: // PCJ-600
            result = 5;
        case 462: // Faggio
            result = 4;
        case 463: // Freeway
            result = 6;
        case 466: // Glendale
            result = 11;
        case 467: // Oceanic
            result = 10;
        case 468: // Sanchez
            result = 7;
        case 470: // Patriot
            result = 13;
        case 471: // Quad
            result = 8;
        case 474: // Hermes
            result = 10;
        case 475: // Sabre
            result = 11;
        case 477: // ZR-350
            result = 9;
        case 478: // Walton
            result = 14;
        case 479: // Regina
            result = 11;
        case 480: // Comet
            result = 9;
        case 482: // Burrito
            result = 14;
        case 483: // Camper
            result = 16;
        case 485: // Baggage
            result = 0;
        case 486: // Dozer
            result = 0;
        case 489: // Rancher
            result = 14;
        case 490: // FBI Rancher
            result = 13;
        case 491: // Virgo
            result = 10;
        case 492: // Greenwood
            result = 10;
        case 494: // Hotring Racer
            result = 9;
        case 495: // Sandking
            result = 15;
        case 496: // Blista Compact
            result = 9;
        case 498: // Boxville
            result = 15;
        case 499: // Benson
            result = 16;
        case 500: // Mesa
            result = 13;
        case 502: // Hotring Racer
            result = 9;
        case 503: // Hotring Racer
            result = 9;
        case 504: // Bloodring Banger
            result = 12;
        case 505: // Rancher
            result = 14;
        case 506: // Super GT
            result = 8;
        case 507: // Elegant
            result = 10;
        case 508: // Journey
            result = 15;
        case 515: // Roadtrain
            result = 23;
        case 516: // Nebula
            result = 11;
        case 517: // Majestic
            result = 11;
        case 518: // Buccaneer
            result = 12;
        case 521: // FCR-900
            result = 5;
        case 522: // NRG-500
            result = 5;
        case 523: // HPV1000
            result = 6;
        case 524: // Cement Truck
            result = 20;
        case 525: // Towtruck
            result = 15;
        case 526: // Fortune
            result = 10;
        case 527: // Cadrona
            result = 10;
        case 528: // FBI Truck
            result = 13;
        case 529: // Willard
            result = 10;
        case 530: // Forklift
            result = 0;
        case 531: // Tractor
            result = 15;
        case 532: // Combine Harvester
            result = 20;
        case 533: // Feltzer
            result = 9;
        case 534: // Remington
            result = 11;
        case 535: // Slamvan
            result = 11;
        case 536: // Blade
            result = 11;
        case 539: // Vortex
            result = 10;
        case 540: // Vincent
            result = 10;
        case 541: // Bullet
            result = 8;
        case 542: // Clover
            result = 10;
        case 543: // Sadler
            result = 14;
        case 544: // Firetruck LA
            result = 18;
        case 545: // Hustler
            result = 10;
        case 546: // Intruder
            result = 10;
        case 547: // Primo
            result = 10;
        case 549: // Tampa
            result = 10;
        case 550: // Sunrise
            result = 10;
        case 551: // Merit
            result = 10;
        case 552: // Utility Van
            result = 15;
        case 554: // Yosemite
            result = 14;
        case 555: // Windsor
            result = 9;
        case 556: // Monster "A"
            result = 20;
        case 557: // Monster "B"
            result = 20;
        case 558: // Uranus
            result = 9;
        case 559: // Jester
            result = 9;
        case 560: // Sultan
            result = 9;
        case 561: // Stratum
            result = 11;
        case 562: // Elegy
            result = 8;            
        case 565: // Flash
            result = 9;
        case 566: // Tahoma
            result = 11;
        case 567: // Savanna
            result = 11;
        case 568: // Bandito
            result = 12;
        case 571: // Kart
            result = 8;
        case 572: // Mower
            result = 10;
        case 573: // Dune
            result = 20;
        case 574: // Sweeper
            result = 10;
        case 575: // Broadway
            result = 11;
        case 576: // Tornado
            result = 11;
        case 578: // DFT-30
            result = 18;
        case 579: // Huntley
            result = 13;
        case 580: // Stafford
            result = 10;
        case 581: // BF-400
            result = 6;
        case 582: // Newsvan
            result = 15;
        case 583: // Tug
            result = 10;
        case 585: // Emperor
            result = 10;
        case 586: // Wayfarer
            result = 6;
        case 587: // Euros
            result = 9;
        case 588: // Hotdog
            result = 13;
        case 589: // Club
            result = 9;
        case 596: // Police Car (LSPD)
            result = 11;
        case 597: // Police Car (SFPD)
            result = 11;
        case 598: // Police Car (LVPD)
            result = 11;
        case 599: // Police Ranger
            result = 13;
        case 600: // Picador
            result = 14;
        case 601: // S.W.A.T.
            result = 15;
        case 602: // Alpha
            result = 9;
        case 603: // Phoenix
            result = 9;
        case 604: // Glendale Shit
            result = 11;
        case 605: // Sadler Shit
            result = 14;
        case 609: // Boxville
            result = 15;
	}

	return result;
}

GetVehiclePrice(model)
{
	new result = 0;

	switch(model)
	{
        case 400: // Landstalker
            result = 35000;
        case 401: // Bravura
            result = 15000;
        case 402: // Buffalo
            result = 50000;
        case 404: // Perenniel
            result = 18000;
        case 405: // Sentinel
            result = 30000;
        case 409: // Stretch
            result = 40000;
        case 410: // Manana
            result = 12000;
        case 411: // Infernus
            result = 100000;
        case 412: // Voodoo
            result = 30000;
        case 413: // Pony
            result = 20000;
        case 415: // Cheetah
            result = 90000;
        case 418: // Moonbeam
            result = 18000;
        case 419: // Esperanto
            result = 20000;
        case 421: // Washington
            result = 35000;
        case 422: // Bobcat
            result = 25000;
        case 426: // Premier
            result = 25000;
        case 429: // Banshee
            result = 95000;
        case 436: // Previon
            result = 15000;
        case 439: // Stallion
            result = 25000;
        case 440: // Rumpo
            result = 20000;
        case 442: // Romero
            result = 25000;
        case 445: // Admiral
            result = 25000;
        case 448: // Pizzaboy
            result = 5000;
        case 451: // Turismo
            result = 95000;
        case 458: // Solair
            result = 20000;
        case 459: // Topfun Van (Berkley's RC)
            result = 20000;
        case 461: // PCJ-600
            result = 10000;
        case 462: // Faggio
            result = 3000;
        case 463: // Freeway
            result = 8000;
        case 466: // Glendale
            result = 18000;
        case 467: // Oceanic
            result = 18000;
        case 468: // Sanchez
            result = 6000;
        case 474: // Hermes
            result = 20000;
        case 475: // Sabre
            result = 25000;
        case 477: // ZR-350
            result = 85000;
        case 479: // Regina
            result = 20000;
        case 480: // Comet
            result = 90000;
        case 481: // BMX
            result = 500;
        case 489: // Rancher
            result = 30000;
        case 491: // Virgo
            result = 18000;
        case 492: // Greenwood
            result = 18000;
        case 494: // Hotring Racer
            result = 100000;
        case 496: // Blista Compact
            result = 20000;
        case 502: // Hotring Racer
            result = 100000;
        case 503: // Hotring Racer
            result = 100000;
        case 509: // Bike
            result = 500;
        case 510: // Mountain Bike
            result = 700;
        case 516: // Nebula
            result = 20000;
        case 517: // Majestic
            result = 20000;
        case 518: // Buccaneer
            result = 20000;
        case 521: // FCR-900
            result = 12000;
        case 522: // NRG-500
            result = 15000;
        case 526: // Fortune
            result = 20000;
        case 527: // Cadrona
            result = 18000;
        case 529: // Willard
            result = 18000;
        case 530: // Forklift
            result = 10000;
        case 534: // Remington
            result = 30000;
        case 535: // Slamvan
            result = 35000;
        case 536: // Blade
            result = 30000;
        case 543: // Sadler
            result = 25000;
        case 545: // Hustler
            result = 20000;
        case 546: // Intruder
            result = 20000;
        case 547: // Primo
            result = 18000;
        case 549: // Tampa
            result = 15000;
        case 550: // Sunrise
            result = 20000;
        case 551: // Merit
            result = 25000;
        case 554: // Yosemite
            result = 30000;
        case 555: // Windsor
            result = 85000;
        case 558: // Uranus
            result = 60000;
        case 559: // Jester
            result = 65000;
        case 560: // Sultan
            result = 70000;
        case 561: // Stratum
            result = 25000;
        case 565: // Flash
            result = 60000;
        case 566: // Tahoma
            result = 20000;
        case 567: // Savanna
            result = 30000;
        case 575: // Broadway
            result = 30000;
        case 576: // Tornado
            result = 30000;
        case 579: // Huntley
            result = 40000;
        case 580: // Stafford
            result = 30000;
        case 581: // BF-400
            result = 8000;
        case 582: // Newsvan
            result = 20000;
        case 583: // Tug
            result = 10000;
        case 585: // Emperor
            result = 20000;
        case 586: // Wayfarer
            result = 7000;
        case 587: // Euros
            result = 25000;
        case 602: // Alpha
            result = 40000;
        case 603: // Phoenix
            result = 45000;
	}

	return result;
}

GetVehicleMaxFuel(model)
{
	new result = 0;

	switch(model)
	{
        case 400: // Landstalker
            result = 80;
        case 401: // Bravura
            result = 60;
        case 402: // Buffalo
            result = 70;
        case 403: // Linerunner
            result = 150;
        case 404: // Perenniel
            result = 65;
        case 405: // Sentinel
            result = 60;
        case 406: // Dumper
            result = 200;
        case 407: // Firetruck
            result = 120;
        case 408: // Trashmaster
            result = 150;
        case 409: // Stretch
            result = 80;
        case 410: // Manana
            result = 55;
        case 411: // Infernus
            result = 75;
        case 412: // Voodoo
            result = 65;
        case 413: // Pony
            result = 100;
        case 414: // Mule
            result = 100;
        case 415: // Cheetah
            result = 70;
        case 416: // Ambulance
            result = 80;
        case 418: // Moonbeam
            result = 70;
        case 419: // Esperanto
            result = 60;
        case 420: // Taxi
            result = 65;
        case 421: // Washington
            result = 60;
        case 422: // Bobcat
            result = 80;
        case 423: // Mr Whoopee
            result = 70;
        case 424: // BF Injection
            result = 70;
        case 426: // Premier
            result = 60;
        case 427: // Enforcer
            result = 90;
        case 428: // Securicar
            result = 90;
        case 429: // Banshee
            result = 70;
        case 431: // Bus
            result = 150;
        case 432: // Rhino
            result = 200;
        case 433: // Barracks
            result = 120;
        case 434: // Hotknife
            result = 65;
        case 436: // Previon
            result = 60;
        case 437: // Coach
            result = 150;
        case 438: // Cabbie
            result = 65;
        case 439: // Stallion
            result = 65;
        case 440: // Rumpo
            result = 80;
        case 442: // Romero
            result = 70;
        case 443: // Packer
            result = 120;
        case 444: // Monster
            result = 100;
        case 445: // Admiral
            result = 60;
        case 448: // Pizzaboy
            result = 15;
        case 451: // Turismo
            result = 75;
        case 455: // Flatbed
            result = 150;
        case 456: // Yankee
            result = 100;
        case 457: // Caddy
            result = 20;
        case 458: // Solair
            result = 65;
        case 459: // Topfun Van (Berkley's RC)
            result = 80;
        case 461: // PCJ-600
            result = 15;
        case 462: // Faggio
            result = 10;
        case 463: // Freeway
            result = 15;
        case 466: // Glendale
            result = 60;
        case 467: // Oceanic
            result = 60;
        case 468: // Sanchez
            result = 15;
        case 470: // Patriot
            result = 80;
        case 471: // Quad
            result = 20;
        case 474: // Hermes
            result = 60;
        case 475: // Sabre
            result = 65;
        case 477: // ZR-350
            result = 70;
        case 478: // Walton
            result = 80;
        case 479: // Regina
            result = 65;
        case 480: // Comet
            result = 70;
        case 482: // Burrito
            result = 80;
        case 483: // Camper
            result = 80;
        case 485: // Baggage
            result = 0;
        case 486: // Dozer
            result = 0;
        case 489: // Rancher
            result = 80;
        case 490: // FBI Rancher
            result = 80;
        case 491: // Virgo
            result = 60;
        case 492: // Greenwood
            result = 60;
        case 494: // Hotring Racer
            result = 70;
        case 495: // Sandking
            result = 80;
        case 496: // Blista Compact
            result = 60;
        case 498: // Boxville
            result = 100;
        case 499: // Benson
            result = 100;
        case 500: // Mesa
            result = 80;
        case 502: // Hotring Racer
            result = 70;
        case 503: // Hotring Racer
            result = 70;
        case 504: // Bloodring Banger
            result = 65;
        case 505: // Rancher
            result = 80;
        case 506: // Super GT
            result = 75;
        case 507: // Elegant
            result = 60;
        case 508: // Journey
            result = 100;
        case 515: // Roadtrain
            result = 200;
        case 516: // Nebula
            result = 60;
        case 517: // Majestic
            result = 60;
        case 518: // Buccaneer
            result = 65;
        case 521: // FCR-900
            result = 15;
        case 522: // NRG-500
            result = 15;
        case 523: // HPV1000
            result = 15;
        case 524: // Cement Truck
            result = 150;
        case 525: // Towtruck
            result = 80;
        case 526: // Fortune
            result = 60;
        case 527: // Cadrona
            result = 60;
        case 528: // FBI Truck
            result = 80;
        case 529: // Willard
            result = 60;
        case 530: // Forklift
            result = 0;
        case 531: // Tractor
            result = 80;
        case 532: // Combine Harvester
            result = 150;
        case 533: // Feltzer
            result = 70;
        case 534: // Remington
            result = 65;
        case 535: // Slamvan
            result = 65;
        case 536: // Blade
            result = 65;
        case 539: // Vortex
            result = 20;
        case 540: // Vincent
            result = 60;
        case 541: // Bullet
            result = 75;
        case 542: // Clover
            result = 60;
        case 543: // Sadler
            result = 80;
        case 544: // Firetruck LA
            result = 120;
        case 545: // Hustler
            result = 60;
        case 546: // Intruder
            result = 60;
        case 547: // Primo
            result = 60;
        case 549: // Tampa
            result = 60;
        case 550: // Sunrise
            result = 60;
        case 551: // Merit
            result = 60;
        case 552: // Utility Van
            result = 80;
        case 554: // Yosemite
            result = 80;
        case 555: // Windsor
            result = 70;
        case 556: // Monster "A"
            result = 100;
        case 557: // Monster "B"
            result = 100;
        case 558: // Uranus
            result = 70;
        case 559: // Jester
            result = 70;
        case 560: // Sultan
            result = 70;
        case 561: // Stratum
            result = 65;
        case 562: // Elegy
            result = 65;            
        case 565: // Flash
            result = 70;
        case 566: // Tahoma
            result = 65;
        case 567: // Savanna
            result = 65;
        case 568: // Bandito
            result = 70;
        case 571: // Kart
            result = 20;
        case 572: // Mower
            result = 20;
        case 573: // Dune
            result = 100;
        case 574: // Sweeper
            result = 20;
        case 575: // Broadway
            result = 65;
        case 576: // Tornado
            result = 65;
        case 578: // DFT-30
            result = 120;
        case 579: // Huntley
            result = 80;
        case 580: // Stafford
            result = 60;
        case 581: // BF-400
            result = 15;
        case 582: // Newsvan
            result = 80;
        case 583: // Tug
            result = 20;
        case 585: // Emperor
            result = 60;
        case 586: // Wayfarer
            result = 15;
        case 587: // Euros
            result = 70;
        case 588: // Hotdog
            result = 70;
        case 589: // Club
            result = 70;
        case 596: // Police Car (LSPD)
            result = 65;
        case 597: // Police Car (SFPD)
            result = 65;
        case 598: // Police Car (LVPD)
            result = 65;
        case 599: // Police Ranger
            result = 80;
        case 600: // Picador
            result = 80;
        case 601: // S.W.A.T.
            result = 100;
        case 602: // Alpha
            result = 70;
        case 603: // Phoenix
            result = 70;
        case 604: // Glendale Shit
            result = 60;
        case 605: // Sadler Shit
            result = 80;
        case 609: // Boxville
            result = 100;
	}

	return result;
}

GetVehicleComplectationName(comp)
{
	new result[32];

	switch(comp)
	{
		case 0: result = "Standart Edition";
		case 1: result = "Extended Edition";
		case 2: result = "Perfomance Edition";
	}

	return result;
}

GetVehicleColorName(color)
{
	new result[64];

	switch(color)
	{
		case 0: result = "Чёрный";
		case 1: result = "Белый";
		case 3: result = "Благородный красный";
		case 6: result = "Солнечный оранжевый";
		case 36: result = "Космический серый";
		case 79: result = "Тихоокеанский синий";
		case 86: result = "Яблочный зелёный";
	}

	return result;
}

GetVehicleMaxSpeed(model)
{
    new max_speed = 0;
    switch(model)
    {
        case 400: max_speed = 145;
        case 401: max_speed = 135;
        case 402: max_speed = 171;
        case 403: max_speed = 101;
        case 404: max_speed = 122;
        case 405: max_speed = 150;
        case 406: max_speed = 101;
        case 407: max_speed = 136;
        case 408: max_speed = 91;
        case 409: max_speed = 145;
        case 410: max_speed = 119;
        case 411: max_speed = 203;
        case 412: max_speed = 154;
        case 413: max_speed = 101;
        case 414: max_speed = 97;
        case 415: max_speed = 176;
        case 416: max_speed = 141;
        case 418: max_speed = 106;
        case 419: max_speed = 137;
        case 420: max_speed = 133;
        case 421: max_speed = 141;
        case 422: max_speed = 128;
        case 423: max_speed = 90;
        case 424: max_speed = 124;
        case 426: max_speed = 159;
        case 427: max_speed = 152;
        case 428: max_speed = 144;
        case 429: max_speed = 185;
        case 431: max_speed = 119;
        case 432: max_speed = 86;
        case 433: max_speed = 101;
        case 434: max_speed = 153;
        case 436: max_speed = 137;
        case 437: max_speed = 145;
        case 438: max_speed = 131;
        case 439: max_speed = 154;
        case 440: max_speed = 125;
        case 442: max_speed = 128;
        case 443: max_speed = 116;
        case 444: max_speed = 101;
        case 445: max_speed = 150;
        case 448: max_speed = 97;
        case 451: max_speed = 177;
        case 455: max_speed = 144;
        case 456: max_speed = 97;
        case 457: max_speed = 87;
        case 458: max_speed = 144;
        case 459: max_speed = 125;
        case 461: max_speed = 148;
        case 462: max_speed = 104;
        case 463: max_speed = 132;
        case 466: max_speed = 135;
        case 467: max_speed = 129;
        case 468: max_speed = 133;
        case 470: max_speed = 145;
        case 471: max_speed = 101;
        case 474: max_speed = 137;
        case 475: max_speed = 158;
        case 477: max_speed = 171;
        case 478: max_speed = 108;
        case 479: max_speed = 128;
        case 480: max_speed = 169;
        case 482: max_speed = 143;
        case 483: max_speed = 112;
        case 485: max_speed = 91;
        case 486: max_speed = 59;
        case 489: max_speed = 128;
        case 490: max_speed = 144;
        case 491: max_speed = 137;
        case 492: max_speed = 129;
        case 494: max_speed = 197;
        case 495: max_speed = 162;
        case 496: max_speed = 149;
        case 498: max_speed = 99;
        case 499: max_speed = 113;
        case 500: max_speed = 129;
        case 502: max_speed = 197;
        case 503: max_speed = 197;
        case 504: max_speed = 158;
        case 505: max_speed = 128;
        case 506: max_speed = 164;
        case 507: max_speed = 152;
        case 508: max_speed = 99;
        case 515: max_speed = 139;
        case 516: max_speed = 144;
        case 517: max_speed = 144;
        case 518: max_speed = 151;
        case 521: max_speed = 147;
        case 522: max_speed = 161;
        case 523: max_speed = 139;
        case 524: max_speed = 118;
        case 525: max_speed = 147;
        case 526: max_speed = 144;
        case 527: max_speed = 137;
        case 528: max_speed = 162;
        case 529: max_speed = 137;
        case 530: max_speed = 55;
        case 531: max_speed = 64;
        case 532: max_speed = 101;
        case 533: max_speed = 153;
        case 534: max_speed = 154;
        case 535: max_speed = 145;
        case 536: max_speed = 158;
        case 539: max_speed = 91;
        case 540: max_speed = 137;
        case 541: max_speed = 186;
        case 542: max_speed = 150;
        case 543: max_speed = 138;
        case 544: max_speed = 136;
        case 545: max_speed = 135;
        case 546: max_speed = 137;
        case 547: max_speed = 131;
        case 549: max_speed = 141;
        case 550: max_speed = 133;
        case 551: max_speed = 144;
        case 552: max_speed = 111;
        case 554: max_speed = 132;
        case 555: max_speed = 145;
        case 556: max_speed = 101;
        case 557: max_speed = 101;
        case 558: max_speed = 143;
        case 559: max_speed = 163;
        case 560: max_speed = 155;
        case 561: max_speed = 141;
        case 562: max_speed = 163;
        case 565: max_speed = 151;
        case 566: max_speed = 146;
        case 567: max_speed = 158;
        case 568: max_speed = 134;
        case 571: max_speed = 85;
        case 572: max_speed = 55;
        case 573: max_speed = 101;
        case 574: max_speed = 55;
        case 575: max_speed = 145;
        case 576: max_speed = 145;
        case 578: max_speed = 119;
        case 579: max_speed = 145;
        case 580: max_speed = 140;
        case 581: max_speed = 140;
        case 582: max_speed = 125;
        case 583: max_speed = 78;
        case 585: max_speed = 140;
        case 586: max_speed = 132;
        case 587: max_speed = 151;
        case 588: max_speed = 99;
        case 589: max_speed = 149;
        case 596: max_speed = 161;
        case 597: max_speed = 161;
        case 598: max_speed = 161;
        case 599: max_speed = 145;
        case 600: max_speed = 138;
        case 601: max_speed = 101;
        case 602: max_speed = 155;
        case 603: max_speed = 157;
        case 604: max_speed = 135;
        case 605: max_speed = 138;
        case 609: max_speed = 99;
    }
    return max_speed;
}

GetVehicleTax(model)
{
	new Float:coeff = 0.07;
	if(GetVehiclePrice(model) > 25000)
		coeff = 0.15;

	return floatround(GetVehiclePrice(model) * coeff);
}
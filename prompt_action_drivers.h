#ifndef PROMPT_ACTION_DRIVERS_H
#define PROMPT_ACTION_DRIVERS_H

#include "ui_utils.h"
#include "flires_internals.h"
#include <conio.h>

void pCHomeDriver(callbackArgs* cA) {
	clearStdOut();
	COORD pco = cA->pC->createPrompt();
	char opt;
	cA->pC->promptInput(&opt, SELECTION_TYPE, pco);

	switch (opt) {
	case '1':
	{
		clearStdOut();
		callbackArgs cA1;
		cA1.pC = cA -> pC->children[0];
		cA->pC->children[0]->execpromptActionDriver(&cA1);
		break;
	}
	case '2':
	{
		clearStdOut();
		COORD aPrIn = cA->pC->children[1]->createPrompt();
		char opt;
		cA->pC->children[1]->promptInput(&opt, SELECTION_TYPE, aPrIn);
		callbackArgs cA1;
		cA1.charType0 = opt;
		cA1.pC = cA->pC->children[1];
		cA->pC->children[1]->execpromptActionDriver(&cA1);
		break;
	}

	case '3':
	{
		clearStdOut();
		COORD _ = cA->pC->children[2]->createPrompt();
		_getch();
		clearStdOut();
		COORD aPrIn = cA->pC->createPrompt();
		char opt;
		cA->pC->promptInput(&opt, SELECTION_TYPE, aPrIn);
		callbackArgs cA1;
		cA1.charType0 = opt;
		cA1.pC = cA->pC;
		cA->pC->execpromptActionDriver(&cA1);
		exit(0);
	}
	
	case '4':
	{
		exit(0);
	}

	default:
	{
		generateErrorMsg("Invalid Option!, retry after 2s", 1800);
		cA->pC->execpromptActionDriver(cA);
	}
	}
}


void pCPCountDriver(callbackArgs* cA) {
	clearStdOut();
	Booking bK;
	cA->bK = &bK;
	COORD aPrIn = cA->pC->createPrompt();
	std::string passengerCount;
	cA->pC->promptInput(&passengerCount, STRING_TYPE, aPrIn);
	cA->bK->flC.passengerCount = passengerCount;
	callbackArgs cA1;
	cA1.pC = cA->pC->children[0];
	cA1.bK = cA->bK;
	cA->pC->children[0]->execpromptActionDriver(&cA1);
}

void pCPInputDriver(callbackArgs* cA) {
	clearStdOut();
	Booking* bK = cA->bK;
	COORD aPrIn = cA->pC->createPrompt();
	Sleep(000);
	int status = readTicketData(bK);
	 if (!status) {
		 generateErrorMsg("All fields are necessary!, retry in 2s", 2000);
		 cA->pC->execpromptActionDriver(cA);
		 return;
	 }
	FlightBooking flBk =  FlightBooking("flight#1", bK);
	flBk.createBooking(bK);
	callbackArgs cA1;
	cA1.pC = cA->pC->children[0];
	cA1.flBk = &flBk;
	cA->pC->children[0]->execpromptActionDriver(&cA1);	
}

void pCATypeDriver(callbackArgs* cA) {
	clearStdOut();
	COORD aPrIn = cA->pC->createPrompt();
	char opt;
	cA->pC->promptInput(&opt, SELECTION_TYPE, aPrIn);
	callbackArgs cA1;
	cA1.flBk = cA->flBk;
	switch (opt) {
	case '1': {
		cA1.flBk->bK->aircraftType = LIGHT;
		cA1.pC = cA->pC->children[0];
		break;
	}
	case '2': {
		cA1.flBk->bK->aircraftType = MIDESIZE;
		cA1.pC = cA->pC->children[1];
		break;
	}
	case '3': {
		cA1.flBk->bK->aircraftType = LARGECABIN;
		cA1.pC = cA->pC->children[2];
		break;
	}

	}
	cA1.pC->execpromptActionDriver(&cA1);
}

void pCADriver(callbackArgs* cA) {
	clearStdOut();
	AIRCRAFT_TYPE aircraftType = cA->flBk->bK->aircraftType;
	switch (aircraftType) {
	case LIGHT: {
		COORD afPrIn = cA->pC->createPrompt();
		char opt;
		cA->pC->promptInput(&opt, SELECTION_TYPE, afPrIn);
		switch (opt) {
		case '1':
		{
			cA->flBk->bK->aircraftName = "Citation Ultra";
			break;
		}
		case '2':
		{
			cA->flBk->bK->aircraftName = "Citation CJ3";
			break;
		}
		case '3':
		{
			cA->flBk->bK->aircraftName = "Citation 300";
			break;
		}
		}

		break;
	}
	case MIDESIZE: {
		COORD afPrIn = cA->pC->createPrompt();
		char opt;
		cA->pC->promptInput(&opt, SELECTION_TYPE, afPrIn);

		switch (opt) {
		case '1':
		{
			cA->flBk->bK->aircraftName = "Citation XL/XLS";
			break;
		}
		case '2':
		{
			cA->flBk->bK->aircraftName = "Hawker 800XP";
			break;
		}
		}

		break;
	}

	case LARGECABIN: {
		COORD aPrIn = cA->pC->createPrompt();
		char opt;
		cA->pC->promptInput(&opt, SELECTION_TYPE, aPrIn);

		switch (opt) {
		case '1':
		{
			cA->flBk->bK->aircraftName = "Gulfstream GIV-SP";
			break;
		}
		case '2':
		{
			cA->flBk->bK->aircraftName = "Challenger 850";
			break;
		}
		case '3':
		{
			cA->flBk->bK->aircraftName = "Legacy 650";
			break;
		}
		}

		break;
	}
	}
	callbackArgs cA1;
	cA1.pC = cA->pC->children[0];
	cA1.flBk = cA->flBk;
	cA->pC->children[0]->execpromptActionDriver(&cA1);
}

void pCDesCounDriver(callbackArgs* cA) {
	clearStdOut();
	COORD afPrInCo = cA->pC->createPrompt();
	char opt;
	cA->pC->promptInput(&opt, SELECTION_TYPE, afPrInCo);
	callbackArgs cA1;
	switch (opt) {
		case '1': {
			cA->flBk->bK->destinationCountry = "Malaysia";
			cA1.pC = cA->pC->children[0];
			break;
		}

		case '2': {
			cA->flBk->bK->destinationCountry = "Turkey";
			cA1.pC = cA->pC->children[1];
			break;
		}

		case '3': {
			cA->flBk->bK->destinationCountry = "Australia";
			cA1.pC = cA->pC->children[2];
			break;
		}

		case '4': {
			cA->flBk->bK->destinationCountry = "Saudia Arabia";
			cA1.pC = cA->pC->children[3];
			break;
		}
		case '5': {
			cA->flBk->bK->destinationCountry = "Qatar";
			cA1.pC = cA->pC->children[4];
			break;
		}
		case '6': {
			cA->flBk->bK->destinationCountry = "Switzerland";
			cA1.pC = cA->pC->children[5];
			break;
		}
		case '7': {
			cA->flBk->bK->destinationCountry = "Indonesia";
			cA1.pC = cA->pC->children[6];
			break;
		}
	}

	cA1.flBk = cA->flBk;
	cA1.pC->execpromptActionDriver(&cA1);
}

void pCDesCitDriver(callbackArgs* cA) {
	clearStdOut();
	const char* destCountry = cA->flBk->bK->destinationCountry.c_str();
	COORD aPrIn = cA->pC->createPrompt();
	char opt;
	cA->pC->promptInput(&opt, SELECTION_TYPE, aPrIn);
	if (destCountry == "Malaysia") {
		switch (opt) {
		case '1': {
			cA->flBk->bK->destinationCity = "Kuala Lumpur";
			break;
		}
		case '2': {
			cA->flBk->bK->destinationCity = "Johor Bahru";
			break;
		}
		}
	}

	else if (destCountry == "Turkey") {
		switch (opt) {
		case '1': {
			cA->flBk->bK->destinationCity = "Istanbul";
			break;
		}
		case '2': {
			cA->flBk->bK->destinationCity = "Ankara";
			break;
		}
		}

	}

	else if (destCountry == "Australia") {
		switch (opt) {
		case '1': {
			cA->flBk->bK->destinationCity = "Sydney";
			break;
		}
		case '2': {
			cA->flBk->bK->destinationCity = "Melbourne";
			break;
		}
		}

	}

	else if (destCountry == "Saudia Arabia") {
		switch (opt) {
		case '1': {
			cA->flBk->bK->destinationCity = "Riyadh";
			break;
		}
		case '2': {
			cA->flBk->bK->destinationCity = "Medina";
			break;
		}
		}
	
	}

	else if (destCountry == "Qatar") {
		switch (opt) {
		case '1': {
			cA->flBk->bK->destinationCity = "Doha";
			break;
		}
		case '2': {
			cA->flBk->bK->destinationCity = "Dukhan";
			break;
		}
		}

	}

	else if (destCountry == "Switzerland") {
		switch (opt) {
		case '1': {
			cA->flBk->bK->destinationCity = "Geneva";
			break;
		}
		case '2': {
			cA->flBk->bK->destinationCity = "Bern";
			break;
		}
		}

	}

	else if (destCountry == "Indonesia") {
		switch (opt) {
		case '1': {
			cA->flBk->bK->destinationCity = "Jakarta";
			break;
		}
		case '2': {
			cA->flBk->bK->destinationCity = "Medan";
			break;
		}
		}

	}
}

void pCDepDateDriver(callbackArgs* cA) {
	clearStdOut();
}



#endif // !PROMPT_ACTION_DRIVERS_H

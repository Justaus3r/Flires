#ifndef PROMPT_ACTION_DRIVERS_H
#define PROMPT_ACTION_DRIVERS_H

#include "ui_utils.h"
#include "flires_internals.h"
#include <conio.h>

void pCHomeDriver(callbackArgs* cA) {
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
		cA->pC->createPrompt();
		break;
	}

	case LARGECABIN: {
		cA->pC->createPrompt();
		break;
	}
	}
	callbackArgs cA1;
	cA1.pC = cA->pC->children[0];
	cA->pC->children[0]->execpromptActionDriver(&cA1);
}

void pCDesCounDriver(callbackArgs* cA) {
	clearStdOut();
	cA->pC->createPrompt();
	_getch();
}

void pCDesCitDriver(callbackArgs* cA) {
	clearStdOut();
}

void pCDepDateDriver(callbackArgs* cA) {
	clearStdOut();
}



#endif // !PROMPT_ACTION_DRIVERS_H

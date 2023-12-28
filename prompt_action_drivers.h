#ifndef PROMPT_ACTION_DRIVERS_H
#define PROMPT_ACTION_DRIVERS_H

#include "ui_utils.h"
#include "flires_internals.h"
#include <conio.h>

void pCHomeDriver(callbackArgs* cA) {
	char opt = cA->charType0;
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
	Sleep(6000);
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
	switch (opt) {
	case '1': {
		cA1.pC = cA->pC->children[0];
		break;
	}
	case '2': {
		cA1.pC = cA->pC->children[1];
		break;
	}
	case '3': {
		cA1.pC = cA->pC->children[2];
		break;
	}
	
	}
}

void pCADriver(callbackArgs* cA) {
	clearStdOut();
}

void pCDesCitDriver(callbackArgs* cA) {
	clearStdOut();
}

void pCDepDateDriver(callbackArgs* cA) {
	clearStdOut();
}



#endif // !PROMPT_ACTION_DRIVERS_H

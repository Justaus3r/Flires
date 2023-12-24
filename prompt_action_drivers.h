#ifndef PROMPT_ACTION_DRIVERS_H
#define PROMPT_ACTION_DRIVERS_H

#include "ui_utils.h"
#include <conio.h>

//char* opt, PromptCreator *pC
void pCHomeDriver(callbackArgs* cA) {
	char opt = cA->charType0;
	std::cout <<"\nVal: " << opt << std::endl;
	switch (opt) {
	case '1':
	{
		clearStdOut();
		//std::cout << cA->pC->children.size()<<std::endl;
		COORD aPrIn = cA->pC->children[0]->createPrompt();
		//std::cout << aPrIn.X << std::endl;
		int opt;
		cA->pC->children[0]->promptInput(&opt, INT_TYPE, {0,0});

		callbackArgs cA1;
		cA1.intType0 = opt;
		cA1.pC = cA->pC->children[0];
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
		COORD aPrIn = cA->pC->children[2]->createPrompt();
		_getch();
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
	int passengerCount = cA->intType0;
	cA->bK->flC.passengerCount = passengerCount;
	cA->pC->createPrompt();
	callbackArgs cA1;
	cA1.pC = cA->pC->children[0];
	cA->pC->children[0]->execpromptActionDriver(&cA1);
}

void pCPInputDriver(callbackArgs* cA) {

	;
}

void pCATypeDriver(callbackArgs* cA) {
	;
}

void pCA1Driver(callbackArgs* cA) {
	;
}

void pCA2Driver(callbackArgs* cA) {
	;
}


void pCA3Driver(callbackArgs* cA) {
	;
}

void pCDesCitDriver(callbackArgs* cA) {
	;
}

void pCDepDateDriver(callbackArgs* cA) {
	;
}

void pCQueSerDriver(callbackArgs* cA) {
	;
}



#endif // !PROMPT_ACTION_DRIVERS_H

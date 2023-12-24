#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <Windows.h>
#include <iostream>
#include <vector>
#include "flires_internals.h"

#define WHITE FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY

#define INPUT_PROMPT "[*]>>"


enum Datatype {
	INT_TYPE,
	FLOAT_TYPE,
	STRING_TYPE,
	DATE_TYPE,
	SELECTION_TYPE
};

class PromptCreator;

struct callbackArgs {
	Booking* bK;
	PromptCreator* pC;
	std::string strType0;
	std::string strType1;
	int intType0;
	int intType1;
	float floatType0;
	float floatType1;
	char charType0;
	char charType1;	
};


void writeToStdout(COORD pos, std::string writable, WORD wAttr);

void clearStdOut();

BOOL setWindowTitle(LPCTSTR winT);

BOOL setWindowPosNSize(COORD winPos);

bool moveToPos(COORD conCoord);

SHORT generateErrorMsg(const char* errMsg, int afterSleep);

COORD getTerminalSize();

class PromptCreator {
public:
	std::vector<std::string> rows;
	std::vector<WORD> rowWAttrs;
	std::vector<SHORT> rowsSize;
	char const* promptName;
	char const* promptTitle;
	WORD titleTxtAttrs;
	int maxRowSize = 0;
	std::vector<PromptCreator*> children;
	void (*actionCallback)(callbackArgs* cA);
	PromptCreator(char const* promptName, char const* prompTitle, WORD titleTxtAttrs = WHITE);
	void addRow(std::string row, WORD rowWAttr);
	COORD createPrompt();
	void promptInput(void* dtaPtr, enum Datatype dTyp, COORD afterPromptCords);
	void addChild(PromptCreator* child);
	void setPromptActionDriver(void (* actionCallback)(callbackArgs * cA));
	void execpromptActionDriver(callbackArgs* cA);
};

#endif
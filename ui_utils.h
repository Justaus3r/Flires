#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <Windows.h>

struct TerminalPosition {
	int x;
	int y;
};

void writeToStdout();

void clearScreen();

void changeConsoleColor();

bool moveToPos(COORD conCoord);


TerminalPosition get_terminal_size();

class PromptCreator {
public:
	PromptCreator();
	bool attachToCommunicator();
	COORD createPrompt();

};


#endif

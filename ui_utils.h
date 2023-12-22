#ifndef UI_UTILS_H
#define UI_UTILS_H

#include <windows.h>
#include <iostream>
#include <vector>

struct TerminalCoords {
	int x;
	int y;
};

void writeToStdout(COORD pos, std::string writable, WORD wAttr);

void clearStdOut();

bool moveToPos(COORD conCoord);


TerminalCoords get_terminal_size();

class PromptCreator {
public:
	std::vector<std::string> rows;
	PromptCreator();
	void addRow(std::string row);
	COORD createPrompt();
	bool attachToCommunicator();
};


#endif

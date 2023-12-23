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

void setWindowTitle(const char* winTitle);

void setWindowSize(COORD winSize);

void setWindowPos(COORD winPos);

bool moveToPos(COORD conCoord);


TerminalCoords get_terminal_size();

class PromptCreator {
public:
	std::vector<std::string> rows;
	std::vector<WORD> rowWAttrs;
	bool isTitle = false;
	PromptCreator();
	void addRow(std::string row, WORD rowWAttr, bool isTitle);
	COORD createPrompt();
	bool attachToCommunicator();
};


#endif

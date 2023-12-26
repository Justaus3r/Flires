#include <iostream>
#include <conio.h>
#include "ui_utils.h"
#include "flires_internals.h"
#include "prompt_action_drivers.h"


int main() {
/*
------------------------
Start Prompt definitions
------------------------
*/ 
PromptCreator pCHome = PromptCreator("Home", "Choose an Option:");
pCHome.addRow("[1]: Make Flight Reservation", WHITE);
pCHome.addRow("[2]: Query Services", WHITE);
pCHome.addRow("[3]: Contact Us", WHITE);
pCHome.addRow("[4]: Quit", WHITE);
pCHome.addRow(INPUT_PROMPT, FOREGROUND_RED);


PromptCreator pCPCount = PromptCreator("Passenger-Count", "Please Input the Passenger count(1-16)");
pCPCount.addRow(INPUT_PROMPT, WHITE);

PromptCreator pCPInput = PromptCreator("Passenger-Input", "A Text editor is being opened for free-input(in 6s)");
pCPInput.addRow("Please Input all the PassengerNames,", WHITE);
pCPInput.addRow("age, gender, weightage per head(in lbs)", WHITE);
pCPInput.addRow("in the editor, seperated by a newline.", WHITE);
pCPInput.addRow("Save and close the file after doing so.", WHITE);
pCPInput.addRow("Waiting for the Input...", WHITE);


PromptCreator pCAType = PromptCreator("Aircraft-Type", "Choose Aircraft Type");
pCAType.addRow("[1]: Light", WHITE);
pCAType.addRow("[2]: MidSize", WHITE);
pCAType.addRow("[3]: Large Cabin", WHITE);
pCAType.addRow(INPUT_PROMPT, WHITE);


PromptCreator pCA1 = PromptCreator("Aircraft-Type-1", "Choose Aircraft");
pCA1.addRow("[1]: Citation Ultra", WHITE);
pCA1.addRow("[2]: Citation CJ3", WHITE);
pCA1.addRow("[3]: Citation 300", WHITE);
pCA1.addRow(INPUT_PROMPT, WHITE);


PromptCreator pCA2 = PromptCreator("Aircraft-Type-2", "Choose Aircraft");
pCA2.addRow("[1]: Citation XL/XLS", WHITE);
pCA2.addRow("[2]: Hawker 800XP", WHITE);
pCA2.addRow(INPUT_PROMPT, WHITE);


PromptCreator pCA3 = PromptCreator("Aircraft-Type-2", "Choose Aircraft");
pCA3.addRow("[1]:Gulfstream GIV-SP", WHITE);
pCA3.addRow("[2]:Challenger 850", WHITE);
pCA3.addRow("[3]:Legacy 650", WHITE);
pCA3.addRow(INPUT_PROMPT, WHITE);


PromptCreator pCDesCoun = PromptCreator("Destination-Country", "Choose the Destination Country");
pCDesCoun.addRow("[1]: Malaysia", WHITE);
pCDesCoun.addRow("[2]: Turkey", WHITE);
pCDesCoun.addRow("[3]: Australia", WHITE);
pCDesCoun.addRow("[4]: Saudia Arabia", WHITE);
pCDesCoun.addRow("[5]: Qatar", WHITE);
pCDesCoun.addRow("[6]: Switzerland", WHITE);
pCDesCoun.addRow("[7]: Indonesia", WHITE);
pCDesCoun.addRow(INPUT_PROMPT, WHITE);

const char* promptName = "Destination-Country's-City";
const char* promptTitle = "Choose any of the following Cities";

PromptCreator pCDesCit1 = PromptCreator(promptName, promptTitle);
pCDesCit1.addRow("[1]: Kuala Lumpur", WHITE);
pCDesCit1.addRow("[2]: Johor Bahru", WHITE);
pCDesCit1.addRow(INPUT_PROMPT, WHITE);

PromptCreator pCDesCit2 = PromptCreator(promptName, promptTitle);
pCDesCit1.addRow("[1]: Istanbul", WHITE);
pCDesCit1.addRow("[2]: Ankara", WHITE);
pCDesCit1.addRow(INPUT_PROMPT, WHITE);

PromptCreator pCDesCit3 = PromptCreator(promptName, promptTitle);
pCDesCit1.addRow("[1]: Sydney", WHITE);
pCDesCit1.addRow("[2]: Melbourne", WHITE);
pCDesCit1.addRow(INPUT_PROMPT, WHITE);

PromptCreator pCDesCit4 = PromptCreator(promptName, promptTitle);
pCDesCit1.addRow("[1]: Riyadh", WHITE);
pCDesCit1.addRow("[2]: Medina", WHITE);
pCDesCit1.addRow(INPUT_PROMPT, WHITE);


PromptCreator pCDesCit5 = PromptCreator(promptName, promptTitle);
pCDesCit1.addRow("[1]: Doha", WHITE);
pCDesCit1.addRow("[2]: Dukhan", WHITE);
pCDesCit1.addRow(INPUT_PROMPT, WHITE);

PromptCreator pCDesCit6 = PromptCreator(promptName, promptTitle);
pCDesCit1.addRow("[1]: Geneva", WHITE);
pCDesCit1.addRow("[2]: Bern", WHITE);
pCDesCit1.addRow(INPUT_PROMPT, WHITE);

PromptCreator pCDesCit7 = PromptCreator(promptName, promptTitle);
pCDesCit1.addRow("[1]: Jakarta", WHITE);
pCDesCit1.addRow("[2]: Medan", WHITE);
pCDesCit1.addRow(INPUT_PROMPT, WHITE);


PromptCreator pCDepDate = PromptCreator("Departure-Date", "Input Departure Date");
pCDepDate.addRow("*Must be in DD/MM/YYYY Format!", WHITE);
pCDepDate.addRow(INPUT_PROMPT, WHITE);


PromptCreator pCTicketGen = PromptCreator("Ticket-Generation", NULL);
pCTicketGen.addRow("Generating tickets ...", WHITE);

PromptCreator pCTicketGenDone = PromptCreator("Ticket-Generation-Done", NULL);
pCTicketGen.addRow("Tickets Generation Done...", WHITE);


PromptCreator pCQueSer = PromptCreator("Query-Services-prooompt", "Choose an Option");
pCQueSer.addRow("[1]: View tickets", WHITE);
pCQueSer.addRow("[2]: Check flight details", WHITE);
pCQueSer.addRow("[3]: Compare Charter Fare Types", WHITE);
pCQueSer.addRow("[*]>>", WHITE);

PromptCreator pCContUs = PromptCreator("Contact-Us(plz don't)", NULL);
pCContUs.addRow("You can contact us by mailing us at x-neron@pm.me.", WHITE);
pCContUs.addRow("				         AND                         ", WHITE);
pCContUs.addRow("Report bugs at: https://github.com/Justaus3r/Flires-Issues", WHITE);
pCContUs.addRow("Press any key to continue...", WHITE);
/*
-----------------------------
Add children to their ancestors,i.e: 
A kind of linked list to 
child prompts
-----------------------------
*/

pCHome.addChild(&pCPCount);
pCHome.addChild(&pCQueSer);
pCHome.addChild(&pCContUs);
pCPCount.addChild(&pCPInput);
pCPInput.addChild(&pCAType);

pCAType.addChild(&pCA1);
pCAType.addChild(&pCA2);
pCAType.addChild(&pCA3);

pCA1.addChild(&pCDesCoun);
pCA2.addChild(&pCDesCoun);
pCA3.addChild(&pCDesCoun);

pCDesCoun.addChild(&pCDesCit1);
pCDesCoun.addChild(&pCDesCit2);
pCDesCoun.addChild(&pCDesCit3);
pCDesCoun.addChild(&pCDesCit4);
pCDesCoun.addChild(&pCDesCit5);
pCDesCoun.addChild(&pCDesCit6);
pCDesCoun.addChild(&pCDesCit7);

pCDesCit1.addChild(&pCDepDate);
pCDesCit2.addChild(&pCDepDate);
pCDesCit3.addChild(&pCDepDate);
pCDesCit4.addChild(&pCDepDate);
pCDesCit5.addChild(&pCDepDate);
pCDesCit6.addChild(&pCDepDate);
pCDesCit7.addChild(&pCDepDate);

pCDepDate.addChild(&pCTicketGen);

pCTicketGen.addChild(&pCTicketGenDone);


/*
--------------------------------------
Set callbacks for every prompt action
--------------------------------------
*/
void (*callbackHome)(callbackArgs* cA);
void (*callbackPCount)(callbackArgs* cA);
void (*callbackPInput)(callbackArgs* cA);
void (*callbackAType)(callbackArgs* cA);
void (*callbackA)(callbackArgs* cA);
void (*callbackDesCoun)(callbackArgs* cA);
void (*callbackDesCit)(callbackArgs* cA);
void (*callbackDepDate)(callbackArgs * cA);
void (*callbackTicketGen)(callbackArgs * cA);
void (*callbackTicketGenDone)(callbackArgs * cA);



callbackHome = pCHomeDriver;
callbackPCount = pCPCountDriver;
callbackPInput = pCPInputDriver;
pCHome.setPromptActionDriver(callbackHome);
pCPCount.setPromptActionDriver(callbackPCount);
pCPInput.setPromptActionDriver(callbackPInput);
/*
-----------------------------
End children append
-----------------------------
*/




/*
-----------------------
 End prompt definitions
-----------------------
*/


	BOOL stat = setWindowTitle("Flires FMS"); // Y
	COORD wnSize = {120, 35};
	setWindowPosNSize(wnSize);
	clearStdOut();
	//moveToPos(co); //Y
	//std::cout << "WRKN";
	//while (true)
	//{




	COORD pco = pCHome.createPrompt();
	char optC = ' ';
	pCHome.promptInput(&optC, SELECTION_TYPE, pco);
	callbackArgs cA;
	cA.charType0 = optC;
	cA.pC = &pCHome;
	pCHome.execpromptActionDriver(&cA);
	std::cout << pCHome.children.size()<<std::endl;
	_getch();

}
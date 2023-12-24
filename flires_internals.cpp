#include "flires_internals.h"
#include "ticket_creation_internal.h"

FlightBooking::FlightBooking(const char* fName) {
	this->fName = fName;
}

void FlightBooking::createBooking(Booking* bK) {
	this->bK->aircraftName = bK->aircraftName;
	this->bK->aircraftType = bK->aircraftType;
	this->bK->departureDate = bK->departureDate;
	this->bK->destinationCity = bK->destinationCity;
	this->bK->destinationCountry = bK->destinationCountry;
	this->bK->flC = bK->flC;
	this->bK->flightName = this->fName;
}

void FlightBooking::createTicket() {
	;
}

void FlightBooking::compostTicketHtml() {
	;
}


std::vector<std::string> stringSplit(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(input);
    std::string token;

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


void readTicketData(Booking* bK) {
    system("notepad tmp.ticketinfo.txt");
    std::ifstream fh;
    std::vector<std::string> passengersName;
    std::vector<std::string> passengerGender;
    std::vector<std::string> passengersAge;
    std::vector<std::string> passengerWeightage;

    fh.open("tmp.ticketinfo.txt");

    if (!fh.is_open()) {
        std::cerr << "Error opening ticket file: tmp.ticketinfo.txt" << std::endl;
        exit(0);

    }

    std::string tKLine;

    while (getline(fh, tKLine)) {
        std::vector<std::string> str = stringSplit(tKLine, ' ');
        passengersName.push_back(str[0]);
        passengersAge.push_back(str[1]);
        passengerGender.push_back(str[2]);
        passengerWeightage.push_back(str[3]);
    }

    fh.close();

    bK->flC.passengersName = passengersName;
    bK->flC.passengersAge = passengersAge;
    bK->flC.passengerGender = passengerGender;
    bK->flC.passengerWeightage = passengerWeightage;
}


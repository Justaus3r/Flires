#ifndef FLIRES_INTERNALS_H
#define FLIRES_INTERNALS_H

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

struct flightCrew {
	//Most Passengers a charter plane can carry are 19
	// Reference: https://compareprivateplanes.com/articles/how-many-passengers-can-a-private-jet-fit
	std::vector<std::string> passengersName;
	std::vector<std::string> passengerGender;
	std::vector<std::string> passengersAge;
    std::vector<std::string> passengerWeightage;
	std::string passengerCount;
	bool charterPilot;
};


enum AIRCRAFT_TYPE {
	LIGHT,
	MIDESIZE,
	LARGECABIN
};

struct Booking {
	const char* flightName;
	AIRCRAFT_TYPE aircraftType;
	const char* aircraftName;
	flightCrew flC;
	std:: string departureDate;
	std::string destinationCountry;
	std::string destinationCity;
	
};

class FlightBooking {
	public:
		const char* fName;	
		Booking* bK;
		FlightBooking(const char* fName, Booking* bK);
		void createBooking(Booking *bK);
		void createTicket();
	private:	
		void compostTicketHtml();


};

std::vector<std::string> stringSplit(const std::string& input, char delimiter);
int readTicketData(Booking* bK);



#endif

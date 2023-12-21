#ifndef FLIRES_INTERNAL_H
#define FLIRES_INTERNAL_H

#include <iostream>

struct flightCrew {
	//Most Passengers a charter plane can carry are 19
	// Reference: https://compareprivateplanes.com/articles/how-many-passengers-can-a-private-jet-fit
	std::string passengersName[19];
	int passengersAge[19];
	float passengerWeightage[19];

};


struct Booking {
	const char* flightName;
	const char* aircraftType;
	const char* aircraftName;
	flightCrew flC;
	std:: string departureDate;
	std::string destinationCountry;
	std::string destinationCity;
	
};

class FlightBooking {
	public:
		const char* fName;
		flightCrew* flCrew;
		FlightBooking(const char* fName, struct flightCrew* fCrew);
		void createBooking(Booking *bK);
		void viewBooking();
		void modifyBooking(Booking* bK);
		void deleteBooking(Booking* bK);
	private:
		void retrieveData(void *data);


};

class PromptCommunicator {
	// retreive data from PromptCreator and communicate with FlightBooking
	// PromptCreator will prolly store data in some struct or some var
	// we pass the pointer to that struct/var to PromptCommunicator
	// which then communicates that to special subroutine that has 
	// a specific signature. maybe we pass that subroutine as a callback
};


#endif

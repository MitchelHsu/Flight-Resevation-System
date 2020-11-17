// FlightSchedule.cpp
// Member-function definitions for class FlightSchedule.
#include <iostream>
#include <fstream>
#include "FlightSchedule.h" // FlightSchedule class definition

// FlightSchedule default constructor loads flight schedule from the file Flight Schedule.dat
FlightSchedule::FlightSchedule()
{
   loadFlightSchedule();
}

FlightSchedule::~FlightSchedule()
{
}

int FlightSchedule::getDepartureAirport( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   if( it != flights.end() )
      return it->getDepartureAirport();

   return 0;
}

int FlightSchedule::getArrivalAirport( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   if( it != flights.end() )
      return it->getArrivalAirport();

   return 0;
}

string FlightSchedule::getDepartureTime( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   return it->getDepartureTime();
}

string FlightSchedule::getArrivalTime( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   return it->getArrivalTime();
}

bool FlightSchedule::exist( string flightNo, int departureAirport, int arrivalAirport )
{
	vector < Flight >::iterator it = flights.begin();

	for (; it != flights.end(); ++it)
	{
		if (it->getDepartureAirport() == departureAirport && it->getArrivalAirport() == arrivalAirport && it->getFlightNo() == flightNo)
			return true;
	}

	return false;
}

void FlightSchedule::display( int departureAirport, int arrivalAirport, string date )
{
	cout << "Flight   Departure   Arrival   Fare" << endl;

	vector < Flight >::iterator it = flights.begin();

	for (; it != flights.end(); ++it)
	{
		if (it->getDepartureAirport() == departureAirport && it->getArrivalAirport() == arrivalAirport)
			it->display(date);
	}

	/*for (; it != flights.end(); ++it)
	{
		cout << " " << it->getFlightNo() << "      ";
		cout << it->getDepartureTime() << "     ";
		cout << it->getArrivalTime() << "    ";
		cout << fullFare[it->getDepartureAirport()][it->getArrivalAirport()] << endl;
	}*/
}

vector< Flight >::iterator FlightSchedule::getFlight( string flightNo )
{
   // loop through flightSchedule searching for matching flight number
   for( vector< Flight >::iterator it = flights.begin(); it != flights.end(); ++it )
      if( it->getFlightNo() == flightNo ) // ( it.operator->() )->getFlightNo()
         return it;

   return flights.end(); // if no matching flight was found, return flights.end()
}

void FlightSchedule::loadFlightSchedule()
{
	ifstream inFile("Flight Schedule.dat", ios::binary);

	if (!inFile)
		cerr << "File could not be opened. " << endl;

	else
	{
		Flight tempt;
		while (inFile.read(reinterpret_cast<char*>(&tempt), sizeof(tempt)))
		{
			flights.push_back(tempt);
		}
	}
}
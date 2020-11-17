// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "FlightSchedule.h" // FlightSchedule class definition

// ReservationDatabase default constructor loads flight reservations from the file Reservations.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores flight reservations into the file Reservations.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
   storeReservations();
}

void ReservationDatabase::cancelReservation( string id, int n )
{
	vector< Reservation >::iterator it = reservations.begin();

	for (int i = 1; it != reservations.end(); ++it)
	{
		if (id == it->getId())
		{
			if (i == n)
			{
				reservations.erase(it);
				break;
			}
			i++;
		}
	}
} // end function cancelReservation

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::existReservation( string id )
{
	vector< Reservation >::iterator it = reservations.begin();

	for (; it != reservations.end(); ++it)
	{
		if (it->getId() == id)
			return true;
	}

	return false;
}

bool ReservationDatabase::existReservation( Reservation reservation )
{
	return true;
}

void ReservationDatabase::display(string id)
{
	FlightSchedule flightSchedule;

	vector< Reservation >::iterator it = reservations.begin();

	for (int i = 1; it != reservations.end(); ++it)
	{
		if (it->getId() == id)
		{
			cout << "\n" << i << ". ";
			cout << "\nDate: " << it->getDate() << endl;
			cout << "Flight: B7-" << it->getFlightNo() << endl;

			cout << endl;

			cout << " " << airportName[flightSchedule.getDepartureAirport(it->getFlightNo())] << " -> "
				<< airportName[flightSchedule.getArrivalAirport(it->getFlightNo())] << endl;
			cout << "    " << flightSchedule.getDepartureTime(it->getFlightNo())
				<< "    " << flightSchedule.getArrivalTime(it->getFlightNo()) << endl;

			int depart = flightSchedule.getDepartureAirport(it->getFlightNo());
			int arrive = flightSchedule.getArrivalAirport(it->getFlightNo());
			int sum = 0;
			for (int i = 1; i < 8; i++)
			{
				if (it->getTicket(i) != 0)
				{
					switch (i)
					{
					case 1:
						cout << "Full Fare   TWD    " << fullFare[depart][arrive] << " x " << it->getTicket(i) << endl;
						sum += fullFare[depart][arrive];
						break;
					case 2:
						cout << "Child Fare   TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << it->getTicket(i) << endl;
						sum += fullFare[depart][arrive] * discount[i] / 100;
						break;
					case 3:
						cout << "Infant Child Fare   TWD    0 x " << it->getTicket(i) << endl;
						break;
					case 4:
						cout << "Senior Citizen TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << it->getTicket(i) << endl;
						sum += fullFare[depart][arrive] * discount[i] / 100;;
						break;
					case 5:
						cout << " Impaired TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << it->getTicket(i) << endl;
						sum += fullFare[depart][arrive] * discount[i] / 100;;
						break;
					case 6:
						cout << "Impaired Companion TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << it->getTicket(i) << endl;
						sum += fullFare[depart][arrive] * discount[i] / 100;;
						break;
					case 7:
						cout << "Military TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << it->getTicket(i) << endl;
						sum += fullFare[depart][arrive] * discount[i] / 100;;
						break;
					}
				}
			}
			cout << "\nTotal : " << sum << endl;
			i++;
		}
	}
}

void ReservationDatabase::loadReservations()
{
	ifstream inFile("Reservations.dat", ios::binary);

	if (!inFile)
		cerr << "File could not be opened. " << endl;
	else
	{
		Reservation tempt;

		while (inFile.read(reinterpret_cast<char*>(&tempt), sizeof(tempt)))
		{
			reservations.push_back(tempt);
		}
	}
}

void ReservationDatabase::storeReservations()
{
	ofstream save("Reservations.dat", ios::binary);

	if (!save)
		cout << "File could not be saved. " << endl;
	else
	{
		vector< Reservation >::iterator it = reservations.begin();
		for (; it != reservations.end(); ++it)
		{
			save.write(reinterpret_cast<const char*>(&(*it)), sizeof(*it));
		}
	}
}
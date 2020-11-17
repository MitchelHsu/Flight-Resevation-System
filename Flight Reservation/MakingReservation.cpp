// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

// MakingReservation constructor initializes data members
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      FlightSchedule &theFlightSchedule )
   : reservationDatabase( theReservationDatabase ),
     flightSchedule( theFlightSchedule )
{
} // end MakingReservation constructor

void MakingReservation::execute()
{
	Reservation reservation;

	int departureAirport;
	do {
		cout << "\nDeparture airport:\n";
		for (int i = 1; i <= 12; i++)
			cout << setw(2) << i << ". " << airportName[i] << endl;
		cout << "? ";

		cin >> departureAirport;
	} while (departureAirport < 1 || departureAirport > 12);

	int arrivalAirport;
	// choose arrival airport by input its code, and assign the code to arrivalAirport
	chooseArrivalAirport(departureAirport, arrivalAirport);

	string date;
	cout << "\nDeparture date (yyyy/mm/dd): ";
	cin >> date;
	cout << endl;
	reservation.setDate(date);

	flightSchedule.display(departureAirport, arrivalAirport, date);

	string flightnum;
	while (!flightSchedule.exist(flightnum, departureAirport, arrivalAirport))
	{
		cout << "\nFlight number: " << endl;
		cin >> flightnum;
	}
	cout << endl;
	reservation.setFlightNo(flightnum);
	
	int tickets[8];
	inputNumTickets(tickets);
	reservation.setTickets(tickets);

	displayReservation(reservation);

	string id;
	cout << "\nID number: ";
	cin >> id;
	reservation.setId(id);

	string mobile;
	cout << "\nMobile: ";
	cin >> mobile;
	reservation.setMobile(mobile);

	
	reservationDatabase.addReservation(reservation);

	cout << "\nReservation complete! " << endl;
	cout << endl;
}

// choose arrival airport by input its code, and assign the code to arrivalAirport
void MakingReservation::chooseArrivalAirport( int departureAirport, int &arrivalAirport )
{
	cout << "Arrival Airport : " << endl;

	arrivalAirport = 0;
	while (fullFare[departureAirport][arrivalAirport] == 0)
	{
		for (int i = 1; i < 13; i++)
		{
			if (fullFare[departureAirport][i] != 0)
			{
				cout << i << ". " << " ";
				cout << airportName[i] << endl;
			}
		}
		cin >> arrivalAirport;
	}
}

// input the number of tickets for each ticket type, and assign them to tickets
void MakingReservation::inputNumTickets( int tickets[] )
{
	int sum = 5;

	while (sum > 4)
	{
		sum = 0;
		for (int i = 1; i < 8; i++)
		{
			switch (i)
			{
			case 1:
				cout << "Number of Full Fare Ticket (0 ~ 4): ";
				cin >> tickets[i];
				while (tickets[i] > 4)
				{
					cout << "Number of Full Fare Ticket (0 ~ 4): ";
					cin >> tickets[i];
				}
				sum += tickets[i];
				while (sum > 4)
				{
					sum -= tickets[i];
					cout << "You can buy at most 4 tickets in one transaction! " << endl;
					cout << "Number of Full Fare Ticket (0 ~ 4): ";
					cin >> tickets[i];
					sum += tickets[i];
				}
				break;
			case 2:
				cout << "Number of Child Ticket (0 ~ 4): ";
				cin >> tickets[i];
				while (tickets[i] > 4)
				{
					cout << "Number of Child Ticket (0 ~ 4): ";
					cin >> tickets[i];
				}
				sum += tickets[i];
				while (sum > 4)
				{
					sum -= tickets[i];
					cout << "You can buy at most 4 tickets in one transaction! " << endl;
					cout << "Number of Child Ticket (0 ~ 4): ";
					cin >> tickets[i];
					sum += tickets[i];
				}
				break;
			case 3:
				cout << "Number of Infant Ticket (0 ~ 4): ";
				cin >> tickets[i];
				while (tickets[i] > 4)
				{
					cout << "Number of Infant Ticket (0 ~ 4): ";
					cin >> tickets[i];
				}
				sum += tickets[i];
				while (sum > 4)
				{
					sum -= tickets[i];
					cout << "You can buy at most 4 tickets in one transaction! " << endl;
					cout << "Number of Infant Ticket (0 ~ 4): ";
					cin >> tickets[i];
					sum += tickets[i];
				}
				break;
			case 4:
				cout << "Number of Senior Citizen Ticket (0 ~ 4): ";
				cin >> tickets[i];
				while (tickets[i] > 4)
				{
					cout << "Number of Senior Citizen Ticket (0 ~ 4): ";
					cin >> tickets[i];
				}
				sum += tickets[i];
				while (sum > 4)
				{
					sum -= tickets[i];
					cout << "You can buy at most 4 tickets in one transaction! " << endl;
					cout << "Number of Senior Citizen Ticket (0 ~ 4): ";
					cin >> tickets[i];
					sum += tickets[i];
				}
				break;
			case 5:
				cout << "Number of impaired tickets (0 ~ 4): ";
				cin >> tickets[i];
				while (tickets[i] > 4)
				{
					sum -= tickets[i];
					cout << "Number of impaired tickets (0 ~ 4): ";
					cin >> tickets[i];
				}
				sum += tickets[i];
				while (sum > 4)
				{
					cout << "You can buy at most 4 tickets in one transaction! " << endl;
					cout << "Number of impaired tickets (0 ~ 4): ";
					cin >> tickets[i];
					sum += tickets[i];
				}
				break;
			case 6:
				cout << "Number of impaired companion tickets (0 ~ 4): ";
				cin >> tickets[i];
				while (tickets[i] > 4)
				{
					cout << "Number of impaired companion tickets (0 ~ 4): ";
					cin >> tickets[i];
				}
				sum += tickets[i];
				while (sum > 4)
				{
					sum -= tickets[i];
					cout << "You can buy at most 4 tickets in one transaction! " << endl;
					cout << "Number of impaired companion tickets (0 ~ 4): ";
					cin >> tickets[i];
					sum += tickets[i];
				}
				break;
			case 7:
				cout << "Number of military tickets (0 ~ 4): ";
				cin >> tickets[i];
				while (tickets[i] > 4)
				{
					cout << "Number of military tickets (0 ~ 4): ";
					cin >> tickets[i];
				}
				sum += tickets[i];
				while (sum > 4)
				{
					sum -= tickets[i];
					cout << "You can buy at most 4 tickets in one transaction! " << endl;
					cout << "Number of military tickets (0 ~ 4): ";
					cin >> tickets[i];
					sum += tickets[i];
				}
				break;
			}
		}
	}
}

void MakingReservation::displayReservation( Reservation reservation )
{
	cout << "\n\nTicket information: " << endl;

	cout << "\nDate: " << reservation.getDate() << endl;
	cout << "Flight: B7-" << reservation.getFlightNo() << endl;

	cout << endl;

	cout << " " << airportName[flightSchedule.getDepartureAirport(reservation.getFlightNo())] << " -> "
		<< airportName[flightSchedule.getArrivalAirport(reservation.getFlightNo())] << endl;
	cout << "  " << flightSchedule.getDepartureTime(reservation.getFlightNo())
		<< "      " << flightSchedule.getArrivalTime(reservation.getFlightNo()) << endl;

	int depart = flightSchedule.getDepartureAirport(reservation.getFlightNo());
	int arrive = flightSchedule.getArrivalAirport(reservation.getFlightNo());
	int sum = 0;
	for (int i = 1; i < 8; i++)
	{
		if (reservation.getTicket(i) != 0)
		{
			switch (i)
			{
			case 1:
				cout << "Full Fare   TWD    " << fullFare[depart][arrive] << " x " << reservation.getTicket(i) << endl;
				sum += fullFare[depart][arrive];
				break;
			case 2:
				cout << "Child Fare   TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << reservation.getTicket(i) << endl;
				sum += fullFare[depart][arrive] * discount[i] / 100;
				break;
			case 3:
				cout << "Infant Child Fare   TWD    0 x " << reservation.getTicket(i) << endl;
				break;
			case 4:
				cout << "Senior Citizen TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << reservation.getTicket(i) << endl;
				sum += fullFare[depart][arrive] * discount[i] / 100;;
				break;
			case 5:
				cout << " Impaired TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << reservation.getTicket(i) << endl;
				sum += fullFare[depart][arrive] * discount[i] / 100;;
				break;
			case 6:
				cout << "Impaired Companion TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << reservation.getTicket(i) << endl;
				sum += fullFare[depart][arrive] * discount[i] / 100;;
				break;
			case 7:
				cout << "Military TWD    " << fullFare[depart][arrive] * discount[i] / 100 << " x " << reservation.getTicket(i) << endl;
				sum += fullFare[depart][arrive] * discount[i] / 100;;
				break;
			}
		}
	}
	cout << "\nTotal : " << sum << endl;
}
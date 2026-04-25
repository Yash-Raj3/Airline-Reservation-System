#include "Seat.h"
#include <iostream>
using namespace std;

const double EconomySeat::BASE_PRICE = 150.00;
const int EconomySeat::BAGGAGE_KG = 15;

const double BusinessSeat::BASE_PRICE = 450.00;
const int BusinessSeat::BAGGAGE_KG = 30;

const double FirstClassSeat::BASE_PRICE = 1200.00;
const int FirstClassSeat::BAGGAGE_KG = 50;

// Helper function to easily display the seat class as text
string seatClassToString(SeatClass sc)
{
    switch (sc)
    {
    case SeatClass::ECONOMY:
        return "Economy";
    case SeatClass::BUSINESS:
        return "Business";
    case SeatClass::FIRST_CLASS:
        return "First Class";
    default:
        return "Unknown";
    }
}

// --- Base Seat Class Implementation ---

Seat::Seat(const string &seatNumber, SeatClass seatClass)
    : seatClass(seatClass), isBooked(false), passengerID("")
{
    if (seatNumber.empty())
    {
        cout << "ERROR: Seat number cannot be empty.\n";
        this->seatNumber = "Unknown";
    } else {
        this->seatNumber = seatNumber;
    }
}

// Assigns the seat to a passenger if it's available
bool Seat::bookSeat(const string &pid)
{
    if (pid.empty())
    {
        cout << "ERROR: Passenger ID cannot be empty.\n";
        return false;
    }
    if (isBooked)
    {
        cout << "ERROR: Seat " << seatNumber << " is already booked.\n";
        return false;
    }
    isBooked = true;
    passengerID = pid;
    cout << "SUCCESS: Seat " << seatNumber << " booked for passenger " << pid << ".\n";
    return true;
}

// Removes the current passenger and makes the seat available again
bool Seat::cancelBooking()
{
    if (!isBooked)
    {
        cout << "WARNING: Seat " << seatNumber << " is not currently booked.\n";
        return false;
    }
    isBooked = false;
    passengerID = "";
    cout << "SUCCESS: Seat " << seatNumber << " booking cancelled.\n";
    return true;
}

// Basic attribute getters
bool Seat::getIsBooked() const { return isBooked; }
string Seat::getSeatNumber() const { return seatNumber; }
string Seat::getPassengerID() const { return passengerID; }
SeatClass Seat::getSeatClass() const { return seatClass; }

// --- Economy Seat Implementation ---

EconomySeat::EconomySeat(const string &seatNumber)
    : Seat(seatNumber, SeatClass::ECONOMY) {}

double EconomySeat::getPrice() const { return BASE_PRICE; }
int EconomySeat::getBaggageLimit() const { return BAGGAGE_KG; }
string EconomySeat::getMealType() const { return "Standard Meal"; }
bool EconomySeat::hasLoungeAccess() const { return false; }
string EconomySeat::getClassName() const { return "Economy"; }

void EconomySeat::displayInfo() const
{
    cout << "\n  [Economy Seat " << seatNumber << "]\n";
    cout << "  Status   : " << (isBooked ? "Booked" : "Available") << "\n";
    cout << "  Price    : $" << BASE_PRICE << "\n";
    cout << "  Baggage  : " << BAGGAGE_KG << "kg\n";
    cout << "  Meal     : " << getMealType() << "\n";
    cout << "  Lounge   : No\n";
}

// --- Business Seat Implementation ---

BusinessSeat::BusinessSeat(const string &seatNumber, bool flatBed)
    : Seat(seatNumber, SeatClass::BUSINESS), flatBedAvailable(flatBed) {}

double BusinessSeat::getPrice() const { return BASE_PRICE; }
int BusinessSeat::getBaggageLimit() const { return BAGGAGE_KG; }
string BusinessSeat::getMealType() const { return "Premium Multi-Course"; }
bool BusinessSeat::hasLoungeAccess() const { return true; }
string BusinessSeat::getClassName() const { return "Business"; }
bool BusinessSeat::getFlatBed() const { return flatBedAvailable; }

void BusinessSeat::displayInfo() const
{
    cout << "\n  [Business Seat " << seatNumber << "]\n";
    cout << "  Status   : " << (isBooked ? "Booked" : "Available") << "\n";
    cout << "  Price    : $" << BASE_PRICE << "\n";
    cout << "  Baggage  : " << BAGGAGE_KG << "kg\n";
    cout << "  Meal     : " << getMealType() << "\n";
    cout << "  Lounge   : Yes\n";
    cout << "  Flat Bed : " << (flatBedAvailable ? "Yes" : "No") << "\n";
}

// --- First Class Seat Implementation ---

FirstClassSeat::FirstClassSeat(const string &seatNumber, bool limo, bool suite)
    : Seat(seatNumber, SeatClass::FIRST_CLASS),
      limoTransfer(limo), privateSuite(suite) {}

double FirstClassSeat::getPrice() const { return BASE_PRICE; }
int FirstClassSeat::getBaggageLimit() const { return BAGGAGE_KG; }
string FirstClassSeat::getMealType() const { return "Gourmet Fine Dining"; }
bool FirstClassSeat::hasLoungeAccess() const { return true; }
string FirstClassSeat::getClassName() const { return "First Class"; }
bool FirstClassSeat::getLimoTransfer() const { return limoTransfer; }
bool FirstClassSeat::getPrivateSuite() const { return privateSuite; }

void FirstClassSeat::displayInfo() const
{
    cout << "\n  [First Class Seat " << seatNumber << "]\n";
    cout << "  Status   : " << (isBooked ? "Booked" : "Available") << "\n";
    cout << "  Price    : $" << BASE_PRICE << "\n";
    cout << "  Baggage  : " << BAGGAGE_KG << "kg\n";
    cout << "  Meal     : " << getMealType() << "\n";
    cout << "  Lounge   : Yes\n";
    cout << "  Limo     : " << (limoTransfer ? "Yes" : "No") << "\n";
    cout << "  Suite    : " << (privateSuite ? "Yes" : "No") << "\n";
}

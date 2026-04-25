#include "Flight.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Helper function to get the current system time
static string getNow() {
    time_t now = time(0);
    string dt = ctime(&now);
    if (!dt.empty() && dt[dt.length() - 1] == '\n') {
        dt.erase(dt.length() - 1);
    }
    return dt;
}

// --- Reservation Implementation ---

int Reservation::nextResId = 5001; 

Reservation::Reservation(const string &passengerID,
                         const string &flightNumber,
                         const string &seatNumber,
                         const string &seatClass,
                         double price)
    : reservationId(nextResId++),
      passengerID(passengerID),
      flightNumber(flightNumber),
      seatNumber(seatNumber),
      seatClassName(seatClass),
      totalPrice(price),
      isCancelled(false),
      bookingTime(getNow()) {}

// Mark reservation as cancelled
void Reservation::cancel()
{
    isCancelled = true;
    cout << "SUCCESS: Reservation #" << reservationId << " has been cancelled.\n";
}

// Print a formatted boarding ticket
void Reservation::displayTicket() const
{
    cout << "\n--- BOOKING TICKET ---\n";
    cout << "Res ID    : #" << reservationId << "\n";
    cout << "Passenger : " << passengerID << "\n";
    cout << "Flight    : " << flightNumber << "\n";
    cout << "Seat      : " << seatNumber << "\n";
    cout << "Class     : " << seatClassName << "\n";
    cout << "Price     : $" << totalPrice << "\n";
    cout << "Booked At : " << bookingTime << "\n";
    cout << "Status    : " << (isCancelled ? "CANCELLED" : "CONFIRMED") << "\n";
    cout << "----------------------\n";
}

// Getters
int Reservation::getReservationId() const { return reservationId; }
string Reservation::getPassengerID() const { return passengerID; }
string Reservation::getFlightNumber() const { return flightNumber; }
string Reservation::getSeatNumber() const { return seatNumber; }
bool Reservation::getIsCancelled() const { return isCancelled; }
double Reservation::getTotalPrice() const { return totalPrice; }

// --- Flight Implementation ---

Flight::Flight(const string &flightNumber, const string &origin,
               const string &destination, const string &departure,
               const string &arrival, const string &aircraft)
    : flightNumber(flightNumber), origin(origin),
      destination(destination), departureTime(departure),
      arrivalTime(arrival), aircraftType(aircraft),
      isCancelled(false), loyaltyPointsEarned(100), numSeats(0)
{
    if (flightNumber.empty() || origin.empty() || destination.empty() || 
        departure.empty() || arrival.empty() || aircraft.empty()) {
        cout << "WARNING: One or more flight details are empty.\n";
    }
}

// Destructor: clean up all seat objects
Flight::~Flight()
{
    for (int i = 0; i < numSeats; i++)
        delete seats[i];
}

// Add any seat (Economy, Business, or First Class)
void Flight::addSeat(Seat *seat)
{
    if (!seat)
    {
        cout << "ERROR: Cannot add a null seat pointer.\n";
        return;
    }
    if (findSeat(seat->getSeatNumber()) != nullptr)
    {
        cout << "WARNING: Seat " << seat->getSeatNumber() << " already exists on flight "
             << flightNumber << ". Duplicate seat ignored.\n";
        delete seat;
        return;
    }
    if (numSeats >= MAX_SEATS) {
        cout << "ERROR: Maximum seat capacity reached for flight " << flightNumber << ".\n";
        delete seat;
        return;
    }
    seats[numSeats++] = seat;
}

// Generate exactly 100 seats per flight
// A1-A10 (First Class), B1-B30 (Business), C1-C60 (Economy)
void Flight::generateDefaultSeats()
{
    // First Class (A1 to A10)
    for (int i = 1; i <= 10; ++i) {
        addSeat(new FirstClassSeat("A" + to_string(i)));
    }
    // Business Class (B1 to B30)
    for (int i = 1; i <= 30; ++i) {
        addSeat(new BusinessSeat("B" + to_string(i)));
    }
    // Economy Class (C1 to C60)
    for (int i = 1; i <= 60; ++i) {
        addSeat(new EconomySeat("C" + to_string(i)));
    }
}

// Find a seat by its seat number
Seat *Flight::findSeat(const string &seatNumber)
{
    for (int i = 0; i < numSeats; i++)
        if (seats[i]->getSeatNumber() == seatNumber)
            return seats[i];
    return nullptr;
}

// Find first available (unbooked) seat in a given class
Seat *Flight::findAvailableSeat(SeatClass sc)
{
    for (int i = 0; i < numSeats; i++)
        if (seats[i]->getSeatClass() == sc && !seats[i]->getIsBooked())
            return seats[i];
    return nullptr;
}

// Show only unbooked seats
void Flight::displayAvailableSeats() const
{
    cout << "\nAvailable Seats on Flight " << flightNumber << ":\n";
    bool found = false;
    for (int i = 0; i < numSeats; i++)
    {
        if (!seats[i]->getIsBooked())
        {
            seats[i]->displayInfo(); // Polymorphic call
            found = true;
        }
    }
    if (!found)
        cout << "  No seats available.\n";
}

// Show all seats with status
void Flight::displayAllSeats() const
{
    cout << "\nAll Seats on Flight " << flightNumber << ":\n";
    for (int i = 0; i < numSeats; i++)
        seats[i]->displayInfo(); // Polymorphic — calls correct displayInfo()
}

// Cancel this flight
void Flight::cancelFlight()
{
    if (isCancelled)
    {
        cout << "WARNING: Flight " << flightNumber << " is already cancelled.\n";
        return;
    }
    isCancelled = true;
    cout << "SUCCESS: Flight " << flightNumber << " has been cancelled.\n";
}

// Display a summary card of the flight
void Flight::displayInfo() const
{
    cout << "\n  " << flightNumber
         << " | " << origin << " -> " << destination
         << " | Dep: " << departureTime
         << " | Arr: " << arrivalTime
         << " | " << aircraftType
         << " | " << (isCancelled ? "CANCELLED" : "On Schedule")
         << "\n";
}

// Getters
string Flight::getFlightNumber() const { return flightNumber; }
string Flight::getOrigin() const { return origin; }
string Flight::getDestination() const { return destination; }
string Flight::getDepartureTime() const { return departureTime; }
string Flight::getArrivalTime() const { return arrivalTime; }
bool Flight::getIsCancelled() const { return isCancelled; }
int Flight::getLoyaltyPoints() const { return loyaltyPointsEarned; }

void Flight::setDepartureTime(const string& time) { departureTime = time; }
void Flight::setArrivalTime(const string& time) { arrivalTime = time; }

// --- Airline System Implementation ---

AirlineSystem::AirlineSystem(const string &name) 
    : airlineName(name), numFlights(0), numPassengers(0), numReservations(0) {}

// Destructor: clean up all heap-allocated objects
AirlineSystem::~AirlineSystem()
{
    for (int i = 0; i < numFlights; i++)
        delete flights[i];
    for (int i = 0; i < numPassengers; i++)
        delete passengers[i];
    for (int i = 0; i < numReservations; i++)
        delete reservations[i];
}

void AirlineSystem::registerPassenger(Passenger *p)
{
    if (!p)
    {
        cout << "ERROR: Cannot register a null passenger pointer.\n";
        return;
    }
    if (findPassenger(p->getId()) != nullptr)
    {
        cout << "WARNING: Passenger ID " << p->getId() << " already registered. Duplicate ignored.\n";
        delete p;
        return;
    }
    if (numPassengers >= MAX_PASSENGERS) {
        cout << "ERROR: Maximum passenger capacity reached.\n";
        delete p;
        return;
    }
    passengers[numPassengers++] = p;
}

void AirlineSystem::addFlight(Flight *f)
{
    if (!f)
    {
        cout << "ERROR: Cannot add a null flight pointer.\n";
        return;
    }
    if (findFlight(f->getFlightNumber()) != nullptr)
    {
        cout << "WARNING: Flight " << f->getFlightNumber() << " already exists. Duplicate ignored.\n";
        delete f;
        return;
    }
    if (numFlights >= MAX_FLIGHTS) {
        cout << "ERROR: Maximum flight capacity reached.\n";
        delete f;
        return;
    }
    flights[numFlights++] = f;
}

// Search flight by flight number
Flight *AirlineSystem::findFlight(const string &fn)
{
    for (int i = 0; i < numFlights; i++)
        if (flights[i]->getFlightNumber() == fn)
            return flights[i];
    return nullptr;
}

// Search passenger by ID
Passenger *AirlineSystem::findPassenger(const string &pid)
{
    for (int i = 0; i < numPassengers; i++)
        if (passengers[i]->getId() == pid)
            return passengers[i];
    return nullptr;
}

// Handles the end-to-step process of booking a seat for a passenger.
// Returns a pointer to the created Reservation, or nullptr if booking failed.
Reservation *AirlineSystem::bookSeat(const string &passengerID,
                                     const string &flightNumber,
                                     const string &seatNumber)
{
    // Validate flight exists
    Flight *flight = findFlight(flightNumber);
    if (!flight)
    {
        cout << "ERROR: Flight " << flightNumber << " not found.\n";
        return nullptr;
    }
    if (flight->getIsCancelled())
    {
        cout << "ERROR: Flight " << flightNumber << " is cancelled.\n";
        return nullptr;
    }

    // Validate passenger exists
    Passenger *passenger = findPassenger(passengerID);
    if (!passenger)
    {
        cout << "ERROR: Passenger " << passengerID << " not found.\n";
        return nullptr;
    }

    for (int i = 0; i < numReservations; i++)
    {
        Reservation *r = reservations[i];
        if (!r->getIsCancelled() &&
            r->getPassengerID() == passengerID &&
            r->getFlightNumber() == flightNumber)
        {
            cout << "ERROR: Passenger " << passengerID
                 << " already has an active booking on flight "
                 << flightNumber << ".\n";
            return nullptr;
        }
    }

    // Validate seat exists on this flight
    Seat *seat = flight->findSeat(seatNumber);
    if (!seat)
    {
        cout << "ERROR: Seat " << seatNumber << " not found on this flight.\n";
        return nullptr;
    }

    // Attempt to book seat (seat handles its own booking logic)
    if (!seat->bookSeat(passengerID))
        return nullptr;

    // Create and store the reservation
    Reservation *res = new Reservation(
        passengerID, flightNumber,
        seatNumber, seat->getClassName(),
        seat->getPrice());
        
    if (numReservations >= MAX_RESERVATIONS) {
        cout << "ERROR: Maximum reservation capacity reached.\n";
        delete res;
        return nullptr;
    }
    reservations[numReservations++] = res;

    // Award loyalty points and increment flight count
    passenger->addLoyaltyPoints(flight->getLoyaltyPoints());
    passenger->incrementFlights();

    cout << "SUCCESS: Booking confirmed. Loyalty points awarded: "
         << flight->getLoyaltyPoints() << "\n";

    res->displayTicket();
    return res;
}

// Cancel a reservation by its ID
bool AirlineSystem::cancelReservation(int resId)
{
    for (int i = 0; i < numReservations; i++)
    {
        Reservation *r = reservations[i];
        if (r->getReservationId() == resId && !r->getIsCancelled())
        {
            // Also free the seat on the flight
            Flight *flight = findFlight(r->getFlightNumber());
            if (flight)
            {
                Seat *seat = flight->findSeat(r->getSeatNumber());
                if (seat)
                    seat->cancelBooking();
            }
            r->cancel();
            return true;
        }
    }
    cout << "WARNING: Reservation #" << resId << " not found or already cancelled.\n";
    return false;
}

// --- Update & Delete Operations ---
void AirlineSystem::updatePassenger(const string& pid, const string& newEmail, const string& newPhone) {
    Passenger* p = findPassenger(pid);
    if (!p) {
        cout << "ERROR: Passenger " << pid << " not found.\n";
        return;
    }
    p->setEmail(newEmail);
    p->setPhone(newPhone);
    cout << "SUCCESS: Passenger " << pid << " updated successfully.\n";
}

void AirlineSystem::removePassenger(const string& pid) {
    for (int i = 0; i < numPassengers; i++) {
        if (passengers[i]->getId() == pid) {
            for (int j = 0; j < numReservations; j++) {
                Reservation* r = reservations[j];
                if (r->getPassengerID() == pid && !r->getIsCancelled()) {
                    cancelReservation(r->getReservationId());
                }
            }
            delete passengers[i];
            for (int k = i; k < numPassengers - 1; k++) {
                passengers[k] = passengers[k + 1];
            }
            numPassengers--;
            cout << "SUCCESS: Passenger " << pid << " removed successfully.\n";
            return;
        }
    }
    cout << "ERROR: Passenger " << pid << " not found.\n";
}

void AirlineSystem::updateFlight(const string& flightNumber, const string& newDepTime, const string& newArrTime) {
    Flight* f = findFlight(flightNumber);
    if (!f) {
        cout << "ERROR: Flight " << flightNumber << " not found.\n";
        return;
    }
    f->setDepartureTime(newDepTime);
    f->setArrivalTime(newArrTime);
    cout << "SUCCESS: Flight " << flightNumber << " updated successfully.\n";
}

void AirlineSystem::removeFlight(const string& flightNumber) {
    for (int i = 0; i < numFlights; i++) {
        if (flights[i]->getFlightNumber() == flightNumber) {
            for (int j = 0; j < numReservations; j++) {
                Reservation* r = reservations[j];
                if (r->getFlightNumber() == flightNumber && !r->getIsCancelled()) {
                    r->cancel();
                }
            }
            delete flights[i];
            for (int k = i; k < numFlights - 1; k++) {
                flights[k] = flights[k + 1];
            }
            numFlights--;
            cout << "SUCCESS: Flight " << flightNumber << " removed successfully.\n";
            return;
        }
    }
    cout << "ERROR: Flight " << flightNumber << " not found.\n";
}

// --- Data Persistence Operations ---
void AirlineSystem::saveData() const {
    ofstream pOut("passengers.txt");
    if (pOut) {
        for (int i = 0; i < numPassengers; i++) {
            Passenger* p = passengers[i];
            pOut << p->getName() << "," << p->getId() << "," << p->getAge() << ","
                 << p->getEmail() << "," << p->getPhone() << "," << p->getLoyaltyPoints() << "\n";
        }
    }
    pOut.close();

    ofstream fOut("flights.txt");
    if (fOut) {
        for (int i = 0; i < numFlights; i++) {
            Flight* f = flights[i];
            fOut << f->getFlightNumber() << "," << f->getOrigin() << "," << f->getDestination() << ","
                 << f->getDepartureTime() << "," << f->getArrivalTime() << "\n";
        }
    }
    fOut.close();
    cout << "SUCCESS: System data successfully saved to files.\n";
}

void AirlineSystem::loadData() {
    ifstream pIn("passengers.txt");
    if (pIn) {
        string line;
        while (getline(pIn, line)) {
            size_t p1 = line.find(',');
            size_t p2 = line.find(',', p1 + 1);
            size_t p3 = line.find(',', p2 + 1);
            size_t p4 = line.find(',', p3 + 1);
            size_t p5 = line.find(',', p4 + 1);
            if (p1 != string::npos && p5 != string::npos) {
                string name = line.substr(0, p1);
                string id = line.substr(p1 + 1, p2 - p1 - 1);
                int age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
                string email = line.substr(p3 + 1, p4 - p3 - 1);
                string phone = line.substr(p4 + 1, p5 - p4 - 1);
                int pts = stoi(line.substr(p5 + 1));
                
                if (!findPassenger(id)) {
                    Passenger* p = new Passenger(name, id, age, email, phone);
                    p->addLoyaltyPoints(pts);
                    if (numPassengers < MAX_PASSENGERS) {
                        passengers[numPassengers++] = p;
                    } else {
                        cout << "ERROR: Maximum passenger capacity reached while loading.\n";
                        delete p;
                    }
                }
            }
        }
        pIn.close();
    } else {
        cout << "WARNING: Could not open passengers.txt. File might not exist or working directory is incorrect.\n";
    }

    ifstream fIn("flights.txt");
    if (fIn) {
        string line;
        while (getline(fIn, line)) {
            size_t p1 = line.find(',');
            size_t p2 = line.find(',', p1 + 1);
            size_t p3 = line.find(',', p2 + 1);
            size_t p4 = line.find(',', p3 + 1);
            if (p1 != string::npos && p4 != string::npos) {
                string fnum = line.substr(0, p1);
                string org = line.substr(p1 + 1, p2 - p1 - 1);
                string dest = line.substr(p2 + 1, p3 - p2 - 1);
                string dep = line.substr(p3 + 1, p4 - p3 - 1);
                string arr = line.substr(p4 + 1);
                
                if (!findFlight(fnum)) {
                    Flight* f = new Flight(fnum, org, dest, dep, arr, "Boeing 737");
                    f->generateDefaultSeats();
                    if (numFlights < MAX_FLIGHTS) {
                        flights[numFlights++] = f;
                    } else {
                        cout << "ERROR: Maximum flight capacity reached while loading.\n";
                        delete f;
                    }
                }
            }
        }
        fIn.close();
    } else {
        cout << "WARNING: Could not open flights.txt. File might not exist or working directory is incorrect.\n";
    }
    
    if (pIn || fIn) {
        cout << "SUCCESS: System data loading process finished.\n";
    }
}

// List all flights
void AirlineSystem::displayAllFlights() const
{
    cout << "\n======== ALL FLIGHTS ========\n";
    if (numFlights == 0)
    {
        cout << "No flights available.\n";
        return;
    }
    for (int i = 0; i < numFlights; i++)
        flights[i]->displayInfo();
}

// List all registered passengers
void AirlineSystem::displayAllPassengers() const
{
    cout << "\n====== ALL PASSENGERS ======\n";
    if (numPassengers == 0)
    {
        cout << "No passengers registered.\n";
        return;
    }
    for (int i = 0; i < numPassengers; i++)
        passengers[i]->displayInfo();
}

// List all reservations
void AirlineSystem::displayAllReservations() const
{
    cout << "\n===== ALL RESERVATIONS =====\n";
    if (numReservations == 0)
    {
        cout << "No reservations found.\n";
        return;
    }
    for (int i = 0; i < numReservations; i++)
        reservations[i]->displayTicket();
}

// Show all reservations for a specific passenger
void AirlineSystem::displayPassengerBookings(const string &pid) const
{
    cout << "\nBookings for Passenger: " << pid << "\n";
    bool found = false;
    for (int i = 0; i < numReservations; i++)
    {
        Reservation *r = reservations[i];
        if (r->getPassengerID() == pid)
        {
            r->displayTicket();
            found = true;
        }
    }
    if (!found)
        cout << "  No bookings found.\n";
}

// Print welcome banner
void AirlineSystem::printWelcome() const
{
    cout << "\n======================================\n";
    cout << " Welcome to " << airlineName << "\n";
    cout << "      Airline Reservation System      \n";
    cout << "======================================\n";
}

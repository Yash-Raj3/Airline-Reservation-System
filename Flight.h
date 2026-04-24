#ifndef FLIGHT_H
#define FLIGHT_H

// Core module for the Airline System handling flights, reservations,
// and the main system controller.

#include "Person.h"
#include "Seat.h"
#include <string>

// Reservation Class
// Represents a booked ticket linking a passenger to a flight seat.
class Reservation {
private:
    static int nextResId;        // Auto-increment reservation ID
    int reservationId;           // Unique booking ID
    string passengerID;          // Passenger who booked
    string flightNumber;         // Flight booked on
    string seatNumber;           // Seat reserved
    string seatClassName;        // Economy / Business / First Class
    double totalPrice;           // Final ticket price
    bool   isCancelled;          // Cancellation flag
    string bookingTime;          // Timestamp of booking

public:
    // Constructor
    Reservation(const string& passengerID, const string& flightNumber,
                const string& seatNumber,  const string& seatClass,
                double price);

    // Cancel this reservation
    void cancel();

    // Display the booking ticket
    void displayTicket() const;

    // Reservation attribute getters
    int    getReservationId()  const;
    string getPassengerID()    const;
    string getFlightNumber()   const;
    string getSeatNumber()     const;
    bool   getIsCancelled()    const;
    double getTotalPrice()     const;
};

// Flight Class
// Represents a scheduled flight and manages its associated seats.
class Flight {
private:
    string flightNumber;     // e.g., "PK-301"
    string origin;           // Departure city
    string destination;      // Arrival city
    string departureTime;    // Scheduled departure
    string arrivalTime;      // Scheduled arrival
    string aircraftType;     // e.g., "Boeing 737"
    bool   isCancelled;      // Flight status
    int    loyaltyPointsEarned; // Points given to passengers

    // Polymorphic seat storage — holds all seat types
    static const int MAX_SEATS = 300;
    Seat* seats[MAX_SEATS];
    int numSeats;

public:
    // Constructor
    Flight(const string& flightNumber, const string& origin,
           const string& destination,  const string& departure,
           const string& arrival,      const string& aircraft);

    // Destructor — frees all dynamically allocated seats
    ~Flight();

    // Methods for adding, finding, and managing seats
    void generateDefaultSeats();                     // Generate 100 prefixed seats
    void addSeat(Seat* seat);                        // Add any seat type
    Seat* findSeat(const string& seatNumber);        // Lookup seat
    Seat* findAvailableSeat(SeatClass sc);           // Find free seat
    void displayAvailableSeats() const;              // List open seats
    void displayAllSeats() const;                    // List all seats
    void cancelFlight();                             // Cancel flight

    // Flight attribute getters and setters
    string getFlightNumber()  const;
    string getOrigin()        const;
    string getDestination()   const;
    string getDepartureTime() const;
    string getArrivalTime()   const;
    bool   getIsCancelled()   const;
    int    getLoyaltyPoints() const;

    void   setDepartureTime(const string& time);
    void   setArrivalTime(const string& time);

    // Display flight summary
    void displayInfo() const;
};

// AirlineSystem Class
// Main controller managing all passengers, flights, and system data.
class AirlineSystem {
private:
    string airlineName;                   // e.g., "SkyLine Air"
    static const int MAX_FLIGHTS = 100;
    static const int MAX_PASSENGERS = 500;
    static const int MAX_RESERVATIONS = 1000;
    
    Flight* flights[MAX_FLIGHTS];         // All flights
    int numFlights;
    
    Passenger* passengers[MAX_PASSENGERS]; // Registered passengers
    int numPassengers;
    
    Reservation* reservations[MAX_RESERVATIONS]; // All bookings
    int numReservations;

public:
    // Constructor / Destructor
    AirlineSystem(const string& airlineName);
    ~AirlineSystem();

    // Add new entities to the system
    void addFlight(Flight* flight);
    void registerPassenger(Passenger* passenger);

    // Lookup methods
    Flight*    findFlight(const string& flightNumber);
    Passenger* findPassenger(const string& passengerID);

    // Primary system actions
    // Book a seat on a flight for a passenger
    Reservation* bookSeat(const string& passengerID,
                          const string& flightNumber,
                          const string& seatNumber);

    // Cancel an existing reservation by ID
    bool cancelReservation(int reservationId);

    // Modification and removal methods
    void updatePassenger(const string& pid, const string& newEmail, const string& newPhone);
    void removePassenger(const string& pid);
    void updateFlight(const string& flightNumber, const string& newDepTime, const string& newArrTime);
    void removeFlight(const string& flightNumber);

    // Data persistence methods
    void saveData() const;
    void loadData();

    // System reporting tools
    void displayAllFlights()     const;
    void displayAllPassengers()  const;
    void displayAllReservations() const;
    void displayPassengerBookings(const string& passengerID) const;

    // Print welcome banner
    void printWelcome() const;
};

#endif // FLIGHT_H

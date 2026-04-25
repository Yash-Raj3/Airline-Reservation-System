#ifndef FLIGHT_H
#define FLIGHT_H

#include "Person.h"
#include "Seat.h"
#include <string>

// Reservation Class
class Reservation {
private:
    static int nextResId;        
    int reservationId;           
    string passengerID;         
    string flightNumber;         
    string seatNumber;           
    string seatClassName;        
    double totalPrice;           
    bool   isCancelled;         
    string bookingTime;          

public:

    Reservation(const string& passengerID, const string& flightNumber,
                const string& seatNumber,  const string& seatClass,
                double price);

    // Cancel this reservation
    void cancel();

    // Display the booking ticket
    void displayTicket() const;

    
    int    getReservationId()  const;
    string getPassengerID()    const;
    string getFlightNumber()   const;
    string getSeatNumber()     const;
    bool   getIsCancelled()    const;
    double getTotalPrice()     const;
};

// Flight Class

class Flight {
private:
    string flightNumber;     
    string origin;           
    string destination;      
    string departureTime;   
    string arrivalTime;      
    string aircraftType;    
    bool   isCancelled;      
    int    loyaltyPointsEarned; 
    static const int MAX_SEATS = 300;
    Seat* seats[MAX_SEATS];
    int numSeats;

public:

    Flight(const string& flightNumber, const string& origin,
           const string& destination,  const string& departure,
           const string& arrival,      const string& aircraft);
    ~Flight();

    // Methods for adding, finding, and managing seats
    void generateDefaultSeats();                     
    void addSeat(Seat* seat);                        
    Seat* findSeat(const string& seatNumber);       
    Seat* findAvailableSeat(SeatClass sc);           
    void displayAvailableSeats() const;              
    void displayAllSeats() const;                    
    void cancelFlight();                             

    string getFlightNumber()  const;
    string getOrigin()        const;
    string getDestination()   const;
    string getDepartureTime() const;
    string getArrivalTime()   const;
    bool   getIsCancelled()   const;
    int    getLoyaltyPoints() const;

    void   setDepartureTime(const string& time);
    void   setArrivalTime(const string& time);

    
    void displayInfo() const;
};

// AirlineSystem Class
class AirlineSystem {
private:
    string airlineName;                   
    static const int MAX_FLIGHTS = 100;
    static const int MAX_PASSENGERS = 500;
    static const int MAX_RESERVATIONS = 1000;
    
    Flight* flights[MAX_FLIGHTS];         
    int numFlights;
    
    Passenger* passengers[MAX_PASSENGERS]; 
    int numPassengers;
    
    Reservation* reservations[MAX_RESERVATIONS]; 
    int numReservations;

public:
    
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

#endif

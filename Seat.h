#ifndef SEAT_H
#define SEAT_H

// Defines the Seat hierarchy: Base abstract Seat class,
// and derived classes for Economy, Business, and First Class.

#include <string>
#include <iostream>
using namespace std;

// Enum representing the different types of seats available
enum class SeatClass {
    ECONOMY,
    BUSINESS,
    FIRST_CLASS
};

// Convert SeatClass to readable string
string seatClassToString(SeatClass sc);

// Abstract Base Class: Seat
// Defines the common properties and required methods for all seat types.
class Seat {
protected:
    string seatNumber;   // e.g., "12A", "3B"
    SeatClass seatClass; // Economy / Business / First
    bool isBooked;       // Booking status
    string passengerID;  // ID of booked passenger (empty if free)

public:
    // Constructor
    Seat(const string& seatNumber, SeatClass seatClass);

    // Virtual destructor for safe polymorphic deletion
    virtual ~Seat() {}

    // Pure virtual methods to be implemented by specific seat classes
    virtual double      getPrice()      const = 0; // Ticket price
    virtual int         getBaggageLimit() const = 0; // KG allowed
    virtual string      getMealType()   const = 0; // Food service
    virtual bool        hasLoungeAccess() const = 0; // Lounge perk
    virtual void        displayInfo()   const = 0; // Show details
    virtual string      getClassName()  const = 0; // Class name

    // Common operations available for all seats
    bool bookSeat(const string& passengerID);   // Reserve the seat
    bool cancelBooking();                        // Free the seat
    bool getIsBooked()      const;
    string getSeatNumber()  const;
    string getPassengerID() const;
    SeatClass getSeatClass() const;
};

// EconomySeat Class
// Standard seating with basic amenities.
class EconomySeat : public Seat {
private:
    static const double BASE_PRICE;      // Fixed base price
    static const int    BAGGAGE_KG;      // Baggage allowance

public:
    EconomySeat(const string& seatNumber);

    // Implementation of base class methods
    double getPrice()         const override;
    int    getBaggageLimit()  const override;
    string getMealType()      const override;
    bool   hasLoungeAccess()  const override;
    void   displayInfo()      const override;
    string getClassName()     const override;
};

// BusinessSeat Class
// Premium seating with enhanced comfort and services.
class BusinessSeat : public Seat {
private:
    static const double BASE_PRICE;
    static const int    BAGGAGE_KG;
    bool flatBedAvailable; // Business class lie-flat seat

public:
    BusinessSeat(const string& seatNumber, bool flatBed = true);

    // Implementation of base class methods
    double getPrice()         const override;
    int    getBaggageLimit()  const override;
    string getMealType()      const override;
    bool   hasLoungeAccess()  const override;
    void   displayInfo()      const override;
    string getClassName()     const override;

    bool getFlatBed() const;
};

// FirstClassSeat Class
// Luxury seating with exclusive top-tier perks.
class FirstClassSeat : public Seat {
private:
    static const double BASE_PRICE;
    static const int    BAGGAGE_KG;
    bool limoTransfer;      // Airport limo pickup
    bool privateSuite;      // Private enclosed suite

public:
    FirstClassSeat(const string& seatNumber,
                   bool limo = true, bool suite = true);

    // Implementation of base class methods
    double getPrice()         const override;
    int    getBaggageLimit()  const override;
    string getMealType()      const override;
    bool   hasLoungeAccess()  const override;
    void   displayInfo()      const override;
    string getClassName()     const override;

    bool getLimoTransfer()  const;
    bool getPrivateSuite()  const;
};

#endif // SEAT_H

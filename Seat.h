#ifndef SEAT_H
#define SEAT_H
#include <string>
#include <iostream>
using namespace std;

// Enum representing the different types of seats available
enum class SeatClass {
    ECONOMY,
    BUSINESS,
    FIRST_CLASS
};


string seatClassToString(SeatClass sc);

// Abstract Base Class: Seat

class Seat {
protected:
    string seatNumber;  
    SeatClass seatClass; 
    bool isBooked;       
    string passengerID;  

public:
    
    Seat(const string& seatNumber, SeatClass seatClass);


    virtual ~Seat() {}

    // Pure virtual methods to be implemented by specific seat classes
    virtual double      getPrice()      const = 0; 
    virtual int         getBaggageLimit() const = 0; 
    virtual string      getMealType()   const = 0; 
    virtual bool        hasLoungeAccess() const = 0; 
    virtual void        displayInfo()   const = 0; 
    virtual string      getClassName()  const = 0; 

    // Common operations available for all seats
    bool bookSeat(const string& passengerID);   // Reserve the seat
    bool cancelBooking();                        // Free the seat
    bool getIsBooked()      const;
    string getSeatNumber()  const;
    string getPassengerID() const;
    SeatClass getSeatClass() const;
};

// EconomySeat Class

class EconomySeat : public Seat {
private:
    static const double BASE_PRICE;      
    static const int    BAGGAGE_KG;      

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

class BusinessSeat : public Seat {
private:
    static const double BASE_PRICE;
    static const int    BAGGAGE_KG;
    bool flatBedAvailable;

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

#endif 

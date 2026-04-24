#ifndef PERSON_H
#define PERSON_H

// Module for Person and Passenger details, including loyalty levels.

#include <string>
#include <iostream>
using namespace std;

// Loyalty levels for frequent flyers
enum class LoyaltyTier {
    NONE,
    BRONZE,
    SILVER,
    GOLD,
    PLATINUM
};

// Convert LoyaltyTier enum to readable string
string tierToString(LoyaltyTier tier);

// Abstract Base Class: Person
// Core class representing a generic individual in the system.
class Person {
protected:
    string name;   // Full name of the person
    string id;     // Unique ID (passport / staff ID)
    int age;       // Age of the person

public:
    // Constructor
    Person(const string& name, const string& id, int age);

    // Virtual destructor — important for safe polymorphic deletion
    virtual ~Person() {}

    // Required methods for all persons
    virtual void displayInfo() const = 0;  // Show person details
    virtual string getRole() const = 0;    // Return role name

    // Basic attribute getters
    string getName() const;
    string getId()   const;
    int    getAge()  const;
};

// Passenger Class
// Represents a traveler, tracking their contact details and loyalty status.
class Passenger : public Person {
private:
    string email;           // Contact email
    string phone;           // Contact phone number
    int loyaltyPoints;      // Accumulated loyalty points
    LoyaltyTier tier;       // Current loyalty tier
    int totalFlights;       // Total flights taken

    // Private helper: updates tier based on points
    void updateTier();

public:
    // Constructor
    Passenger(const string& name, const string& id, int age,
              const string& email, const string& phone);

    // Implementation of base person methods
    void   displayInfo() const override;
    string getRole()     const override;

    // Loyalty and rewards management
    void addLoyaltyPoints(int points);   // Add points after flight
    int  getLoyaltyPoints() const;
    LoyaltyTier getTier() const;
    bool isPriorityBoarding() const;     // Gold/Platinum get priority
    bool isEligibleForUpgrade() const;   // Platinum gets free upgrade

    // Travel history tracking
    void incrementFlights();
    int  getTotalFlights() const;

    // Passenger attribute accessors
    string getEmail() const;
    string getPhone() const;
    void setEmail(const string& newEmail);
    void setPhone(const string& newPhone);
};

#endif // PERSON_H

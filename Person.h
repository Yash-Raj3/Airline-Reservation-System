#ifndef PERSON_H
#define PERSON_H
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


string tierToString(LoyaltyTier tier);

// Abstract Base Class: Person

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

    
    virtual void displayInfo() const = 0;  // Show person details
    virtual string getRole() const = 0;    // Return role name

    
    string getName() const;
    string getId()   const;
    int    getAge()  const;
};

// Passenger Class

class Passenger : public Person {
private:
    string email;           
    string phone;           
    int loyaltyPoints;      
    LoyaltyTier tier;       
    int totalFlights;       

    // Private helper: updates tier based on points
    void updateTier();

public:
    
    Passenger(const string& name, const string& id, int age,
              const string& email, const string& phone);

    
    void   displayInfo() const override;
    string getRole()     const override;

    // Loyalty and rewards management
    void addLoyaltyPoints(int points);   
    int  getLoyaltyPoints() const;
    LoyaltyTier getTier() const;
    bool isPriorityBoarding() const;     // Gold/Platinum get priority
    bool isEligibleForUpgrade() const;  

    // Travel history tracking
    void incrementFlights();
    int  getTotalFlights() const;

    // Passenger attribute accessors
    string getEmail() const;
    string getPhone() const;
    void setEmail(const string& newEmail);
    void setPhone(const string& newPhone);
};

#endif 

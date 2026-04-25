#include "Person.h"
#include <iostream>
using namespace std;

// Helper to convert LoyaltyTier values into readable text
string tierToString(LoyaltyTier tier)
{
    switch (tier)
    {
    case LoyaltyTier::BRONZE:
        return "Bronze";
    case LoyaltyTier::SILVER:
        return "Silver";
    case LoyaltyTier::GOLD:
        return "Gold";
    case LoyaltyTier::PLATINUM:
        return "Platinum";
    default:
        return "None";
    }
}

// --- Person Class Implementation ---
Person::Person(const string &name, const string &id, int age)
{
    if (name.empty()) cout << "ERROR: Person name cannot be empty.\n";
    this->name = name.empty() ? "Unknown" : name;
    
    if (id.empty()) cout << "ERROR: Person ID cannot be empty.\n";
    this->id = id.empty() ? "N/A" : id;
    
    if (age < 0) cout << "ERROR: Person age cannot be negative.\n";
    this->age = age < 0 ? 0 : age;
}


string Person::getName() const { return name; }
string Person::getId() const { return id; }
int Person::getAge() const { return age; }
Passenger::Passenger(const string &name, const string &id, int age,
                     const string &email, const string &phone)
    : Person(name, id, age),
      loyaltyPoints(0), tier(LoyaltyTier::NONE),
      totalFlights(0)
{
    if (email.empty()) cout << "ERROR: Passenger email cannot be empty.\n";
    this->email = email.empty() ? "N/A" : email;
    
    if (phone.empty()) cout << "ERROR: Passenger phone cannot be empty.\n";
    this->phone = phone.empty() ? "N/A" : phone;
}


string Passenger::getRole() const { return "Passenger"; }

void Passenger::displayInfo() const
{
    cout << "\n--- PASSENGER PROFILE ---\n";
    cout << "Name    : " << name << "\n";
    cout << "ID      : " << id << "\n";
    cout << "Age     : " << age << "\n";
    cout << "Email   : " << email << "\n";
    cout << "Phone   : " << phone << "\n";
    cout << "Tier    : " << tierToString(tier) << "\n";
    cout << "Points  : " << loyaltyPoints << "\n";
    cout << "Flights : " << totalFlights << "\n";
    cout << "-------------------------\n";
}

// --- Loyalty System Management ---

// Add points after completing a flight, then re-evaluate tier
void Passenger::addLoyaltyPoints(int points)
{
    if (points < 0)
    {
        cout << "ERROR: Loyalty points cannot be negative.\n";
        return;
    }
    loyaltyPoints += points;
    updateTier(); 
}

void Passenger::updateTier()
{
    if (loyaltyPoints >= 6000)
        tier = LoyaltyTier::PLATINUM;
    else if (loyaltyPoints >= 3000)
        tier = LoyaltyTier::GOLD;
    else if (loyaltyPoints >= 1500)
        tier = LoyaltyTier::SILVER;
    else if (loyaltyPoints >= 500)
        tier = LoyaltyTier::BRONZE;
    else
        tier = LoyaltyTier::NONE;
}

// Gold and Platinum passengers board before everyone else
bool Passenger::isPriorityBoarding() const
{
    return tier == LoyaltyTier::GOLD || tier == LoyaltyTier::PLATINUM;
}

// Only Platinum passengers qualify for free seat upgrades
bool Passenger::isEligibleForUpgrade() const
{
    return tier == LoyaltyTier::PLATINUM;
}

int Passenger::getLoyaltyPoints() const { return loyaltyPoints; }
LoyaltyTier Passenger::getTier() const { return tier; }
string Passenger::getEmail() const { return email; }
string Passenger::getPhone() const { return phone; }

void Passenger::setEmail(const string& newEmail) { email = newEmail; }
void Passenger::setPhone(const string& newPhone) { phone = newPhone; }

void Passenger::incrementFlights() { totalFlights++; }
int Passenger::getTotalFlights() const { return totalFlights; }

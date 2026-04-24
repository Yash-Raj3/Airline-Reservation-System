// Main entry point for the Airline Reservation System.
// Provides an interactive menu for managing passengers, flights, and bookings.

#include "Person.h"
#include "Seat.h"
#include "Flight.h"
#include <iostream>
#include <string>

using namespace std;

// Function to convert string to uppercase
void toUpperCase(string& str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A'); 
        }
    }
}

// Function to clear input buffer safely
void clearInput() {
    cin.clear();
    char c;
    while (cin.get(c) && c != '\n') {}
}

void displayMainMenu() {
    cout << "\n==============================================\n";
    cout << "          AIRLINE RESERVATION SYSTEM          \n";
    cout << "==============================================\n";
    cout << "  1. Passenger Management\n";
    cout << "  2. Flight Management\n";
    cout << "  3. Book a Seat\n";
    cout << "  4. View System Reports (All Data)\n";
    cout << "  5. Save Data to Disk\n";
    cout << "  6. Load Data from Disk\n";
    cout << "  0. Exit System\n";
    cout << "==============================================\n";
    cout << " Enter choice: ";
}

void displayPassengerMenu() {
    cout << "\n--- PASSENGER MANAGEMENT ---\n";
    cout << "  1. Add New Passenger\n";
    cout << "  2. Update Passenger Contact\n";
    cout << "  3. Remove Passenger\n";
    cout << "  4. View Specific Passenger Bookings\n";
    cout << "  0. Back to Main Menu\n";
    cout << "----------------------------\n";
    cout << " Enter choice: ";
}

void displayFlightMenu() {
    cout << "\n--- FLIGHT MANAGEMENT ---\n";
    cout << "  1. Add New Flight\n";
    cout << "  2. Reschedule Flight\n";
    cout << "  3. Remove Flight\n";
    cout << "  4. Cancel a Booking\n";
    cout << "  0. Back to Main Menu\n";
    cout << "-------------------------\n";
    cout << " Enter choice: ";
}

int main() {
    AirlineSystem airline("Express Air");
    airline.printWelcome();
    
    // Automatically load data on startup
    airline.loadData();

    int mainChoice = -1;
    while (mainChoice != 0) {
        displayMainMenu();
        if (!(cin >> mainChoice)) {
            cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        switch (mainChoice) {
            case 1: { // Passenger Management
                int passChoice = -1;
                while (passChoice != 0) {
                    displayPassengerMenu();
                    if (!(cin >> passChoice)) {
                        cout << "Invalid input.\n";
                        clearInput();
                        continue;
                    }
                    switch (passChoice) {
                        case 1: {
                            string name, id, email, phone;
                            int age;
                            cout << "Enter ID (e.g., P001): "; cin >> id; toUpperCase(id);
                            cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                            cout << "Enter Age: "; cin >> age;
                            cout << "Enter Email: "; cin >> email;
                            cout << "Enter Phone: "; cin >> phone;
                            Passenger* p = new Passenger(name, id, age, email, phone);
                            airline.registerPassenger(p);
                            cout << "SUCCESS: Passenger added.\n";
                            break;
                        }
                        case 2: {
                            string id, email, phone;
                            cout << "Enter Passenger ID to update: "; cin >> id; toUpperCase(id);
                            cout << "Enter New Email: "; cin >> email;
                            cout << "Enter New Phone: "; cin >> phone;
                            airline.updatePassenger(id, email, phone);
                            break;
                        }
                        case 3: {
                            string id;
                            cout << "Enter Passenger ID to remove: "; cin >> id; toUpperCase(id);
                            airline.removePassenger(id);
                            break;
                        }
                        case 4: {
                            string pid;
                            cout << "Enter Passenger ID: "; cin >> pid; toUpperCase(pid);
                            airline.displayPassengerBookings(pid);
                            break;
                        }
                        case 0:
                            break; // Back to main menu
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                }
                break;
            }
            case 2: { // Flight Management
                int flightChoice = -1;
                while (flightChoice != 0) {
                    displayFlightMenu();
                    if (!(cin >> flightChoice)) {
                        cout << "Invalid input.\n";
                        clearInput();
                        continue;
                    }
                    switch (flightChoice) {
                        case 1: {
                            string fnum, org, dest, dep, arr;
                            cout << "Enter Flight Number (e.g., SK-101): "; cin >> fnum; toUpperCase(fnum);
                            cout << "Enter Origin: "; cin >> org;
                            cout << "Enter Destination: "; cin >> dest;
                            cout << "Enter Departure Time (HH:MM): "; cin >> dep;
                            cout << "Enter Arrival Time (HH:MM): "; cin >> arr;
                            
                            Flight* f = new Flight(fnum, org, dest, dep, arr, "Boeing 777");
                            f->generateDefaultSeats();
                            airline.addFlight(f);
                            cout << "SUCCESS: Flight added with 100 prefixed seats (A, B, C).\n";
                            break;
                        }
                        case 2: {
                            string fnum, dep, arr;
                            cout << "Enter Flight Number to reschedule: "; cin >> fnum; toUpperCase(fnum);
                            cout << "Enter New Departure Time (HH:MM): "; cin >> dep;
                            cout << "Enter New Arrival Time (HH:MM): "; cin >> arr;
                            airline.updateFlight(fnum, dep, arr);
                            break;
                        }
                        case 3: {
                            string fnum;
                            cout << "Enter Flight Number to remove: "; cin >> fnum; toUpperCase(fnum);
                            airline.removeFlight(fnum);
                            break;
                        }
                        case 4: {
                            int resId;
                            cout << "Enter Reservation ID to cancel: "; cin >> resId;
                            airline.cancelReservation(resId);
                            break;
                        }
                        case 0:
                            break; // Back to main menu
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                }
                break;
            }
            case 3: { // Book a Seat
                string pid, fnum, snum;
                cout << "Enter Passenger ID: "; cin >> pid; toUpperCase(pid);
                cout << "Enter Flight Number: "; cin >> fnum; toUpperCase(fnum);
                cout << "Enter Seat Number (e.g., A10): "; cin >> snum; toUpperCase(snum);
                airline.bookSeat(pid, fnum, snum);
                break;
            }
            case 4: {
                cout << "\n--- SYSTEM REPORTS ---\n";
                airline.displayAllFlights();
                airline.displayAllPassengers();
                airline.displayAllReservations();
                break;
            }
            case 5: {
                airline.saveData();
                break;
            }
            case 6: {
                airline.loadData();
                break;
            }
            case 0:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

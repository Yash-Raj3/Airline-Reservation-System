# Express Air - Airline Reservation System

## Project Description
This is a fully functional Airline Reservation System built using C++. It features a nested console menu that allows users to manage passengers, schedule flights, book seats, and manage the overall system. The project makes heavy use of OOP concepts including Encapsulation, Inheritance, Polymorphism, and Dynamic Memory Management.

## Group Members
- **Name:** Yash Raj | **Student ID:** 25k-0878
- **Name:** Khunais Baig | **Student ID:** 25k-0508
- **Name:** Mohammad Qasim | **Student ID:** 25k-0608

## Use Cases of the System
1. **Manage Passengers:** You can register new passengers into the system, update their email or phone numbers, and remove them if needed.
2. **Schedule Flights:** You can add new flights to the schedule by providing the origin, destination, and timings. You can also reschedule or delete flights.
3. **Auto-Generate Seats:** Whenever a flight is added, the system automatically creates 100 seats for it, divided into First Class (A1-A10), Business Class (B1-B30), and Economy Class (C1-C60).
4. **Book Tickets:** You can book an available seat for a passenger. The system records the exact time the booking was made using the live system clock.
5. **Loyalty Tiers:** When a passenger books a flight, they automatically earn points. As points add up, they are automatically promoted through different loyalty tiers (Bronze, Silver, Gold, Platinum).
6. **Save & Load Data:** You can save all passenger and flight records to text files (`passengers.txt` and `flights.txt`). The system automatically loads this data the next time you run the program so nothing is lost.

## How to Compile the Project
Make sure you have a C++ compiler (like GCC) installed. Open your terminal in the project folder and run:
```bash
g++ *.cpp -o main.exe
```

## How to Run the Project
Once it compiles, you can run the program by typing:
```bash
.\main.exe
```
*(If you're using Linux or a Mac, run `./main.exe` or `./a.out` instead).*

## How to Use the System
The program uses a simple number-based menu. Just type the number of the option you want and press Enter:
1. Type `1` to open the **Passenger Management** menu (add/edit/remove passengers).
2. Type `2` to open the **Flight Management** menu (add/edit/remove flights).
3. Type `3` from the Main Menu to **Book a Seat**. (Inputs are case-insensitive, so typing `p001` or `P001` both work fine!).
4. Type `4` to **View System Reports**, which prints out a list of all flights, passengers, and bookings.
5. Type `0` whenever you want to go back to the previous menu or quit the program entirely.

## Assumptions & Limitations
- **Console Only:** We built this as a terminal application, so there is no visual GUI.
- **File Formatting:** The save files (`passengers.txt` and `flights.txt`) use a strict comma-separated format. If someone edits these files manually and messes up the commas, the program might fail to load the data properly.
- **No Login System:** We didn't include a password or login system. Anyone running the executable has full admin access to change data.
- **Fixed Seating:** Every plane is currently hardcoded to have exactly 100 seats (10 First Class, 30 Business, 60 Economy).

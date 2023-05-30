#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Flight {
public:
    string destination;
    string departureTime;
    string arrivalTime;

    Flight(string dest, string depTime, string arrTime)
        : destination(dest), departureTime(depTime), arrivalTime(arrTime) {}
};

bool hasConflict(const vector<Flight>& flights, const Flight& newFlight) {
    for (const Flight& flight : flights) {
        if (flight.destination == newFlight.destination &&
            flight.departureTime <= newFlight.arrivalTime &&
            flight.arrivalTime >= newFlight.departureTime) {
            return true; // Conflicting flight found
        }
    }
    return false; // No conflicts
}

void displayFlights(const vector<Flight>& flights) {
    if (flights.empty()) {
        cout << "No flights registered." << endl;
        return;
    }

    cout << "Registered flights:" << endl;
    for (const Flight& flight : flights) {
        cout << "Destination: " << flight.destination << endl;
        cout << "Departure time: " << flight.departureTime << endl;
        cout << "Arrival time: " << flight.arrivalTime << endl;
        cout << "-----------------------------" << endl;
    }
}

void writeFlightLog(const vector<Flight>& flights, const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    for (const Flight& flight : flights) {
        outputFile << flight.destination << " "
            << flight.departureTime << " "
            << flight.arrivalTime << endl;
    }

    outputFile.close();
}

int main() {
    vector<Flight> registeredFlights;

    // Read flights from a text file
    ifstream inputFile("flights.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string destination, departureTime, arrivalTime;
    while (inputFile >> destination >> departureTime >> arrivalTime) {
        Flight newFlight(destination, departureTime, arrivalTime);

        if (hasConflict(registeredFlights, newFlight)) {
            cout << "Conflicting flight detected: "
                << newFlight.destination << " at "
                << newFlight.departureTime << "-" << newFlight.arrivalTime
                << endl;
        }
        else {
            registeredFlights.push_back(newFlight);
            cout << "Flight registered: "
                << newFlight.destination << " at "
                << newFlight.departureTime << "-" << newFlight.arrivalTime
                << endl;
        }
    }

    inputFile.close();

    int choice = 0;
    while (choice != 3) {
        cout << "Menu:" << endl;
        cout << "1. Add a new flight" << endl;
        cout << "2. Display all current flights" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string destination, departureTime, arrivalTime;
            cout << "Enter destination: ";
            cin >> destination;
            cout << "Enter departure time: ";
            cin >> departureTime;
            cout << "Enter arrival time: ";
            cin >> arrivalTime;

            Flight newFlight(destination, departureTime, arrivalTime);

            if (hasConflict(registeredFlights, newFlight)) {
                cout << "Conflicting flight detected: "
                    << newFlight.destination << " at "
                    << newFlight.departureTime << "-" << newFlight.arrivalTime
                    << endl;
            }
            else {
                registeredFlights.push_back(newFlight);
                cout << "Flight registered: "
                    << newFlight.destination << " at "
                    << newFlight.departureTime << "-" << newFlight.arrivalTime
                    << endl;
                writeFlightLog(registeredFlights, "flights.txt");
            }

            break;
        }
        case 2:
            displayFlights(registeredFlights);
            break;
        case 3:
            cout << "Exiting the program..." << endl;
            writeFlightLog(registeredFlights, "flights.txt");
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        cout << endl;
    }

    return 0;
}

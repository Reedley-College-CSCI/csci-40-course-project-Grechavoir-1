// CSCI-40 Final Project
// Author: Jaxon Ahumada

/* 
My project is a space exploration journey where the user will be navigating in a spaceship and can drop off and pick up materials on different planets and space stations.  
The spacecraft will have a fuel that must be refilled to restrict unlimited distance.  
The system will track all changes to the stations on the different locations.  
The system will also keep track of how long each travel was and determine the amount of fuel used.
The system will keep track of every visit and also save every material dropped off and picked up in each location.  
I don't know if I want to add an a cost system or not but if I do I would keep a system for the cost of every material and any price changes on them as well as money spent of fuel.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

void printPlanets(); // Function prototype to print planet names from a file
void loadRoutes(); // Function prototype to load routes from a file
double calculateDistance(const string& from, const string& to); // Function prototype to calculate distance between planets
double calculateFuelNeeded(double distance); // Function prototype to calculate fuel needed for a trip
double calculateTravelTime(double distance); // Function prototype to calculate travel time for a trip

struct Route {
     string from;
     string to; 
     double distance; // In millions of kilometers
};

struct Material {
    string name; // Name of the material
    double amount; // Amount of material (tons)
    double cost; // Cost per unit
};

const int MAX_ROUTES = 100; // Maximum number of routes
Route routes[MAX_ROUTES]; // Array to store routes
int routeCount = 0; // Variable to keep track of the number of routes
const int MAX_PLANETS = 8; // Maximum number of planets

const int MAX_MATERIALS = 100; // Maximum number of materials
string materials[MAX_MATERIALS]; // Array to store materials
int materialCount = 0; // Variable to keep track of the number of materials
double kilogramToTon = 907.18; // Conversion factor from kilograms to tons
double MAX_CARGO_WEIGHT = 50; // Maximum cargo weight in tons

int hoursTraveled = 0; // Variable to track the number of hours traveled
double MAX_TOTAL_HOURS = 17520; // Maximum total hours for 2 year mission
double income = 0.0; // Variable to track income
double FLAT_RATE_PAY_HOUR = 200.0; // Flat pay rate for each hour of travel

double MAX_FUEL = 1500.0; // Maximum fuel capacity
double FLAT_FUEL_CONSUMPTION_RATE = 0.5; // Flat fuel consumption rate per million kilometers
int rateOfSpeed = 15; // Speed of the spaceship in million kilometers per day

int main() {
    cout << fixed << setprecision(2); // Set decimal precision for output

    double fuel = 1500.0; // Initial fuel
    double fuelPercentage = (fuel / MAX_FUEL) * 100;

    cout << "Hello..." << endl << "Please enter your name:" << endl;

    string charName;
    getline(cin, charName);

    cout << "Are you ready to start your journey? (yes/no)" << endl;

    string ready;
    cin >> ready;

    for (int i = 0; i < ready.length(); i++) {
        ready[i] = tolower(ready[i]); // Convert the rest of the letters to lowercase
    }

    while (ready != "yes" && ready != "no") {
        cout << "Invalid input. Please enter 'yes' or 'no':" << endl;
        cin >> ready;

        for (int i = 0; i < ready.length(); i++) {
            ready[i] = tolower(ready[i]); // Convert the rest of the letters to lowercase
        }
    }

    if (ready != "yes") {
        cout << "Take your time to prepare. Come back when you are ready!" << endl;
        return 0;
    }

    cout << "\nWelcome to the Space Exploration Journey!" << endl;
    cout << "You have been drafted to venture the cosmos and"
         << " be a hero for your home planet!" << endl;

     
    cout << "\n...Loading...\n...loading...\n...loading...\n" << endl;
    cout << "You are now in your spaceship, ready to explore the universe!" << endl;
    cout << "Your spaceship is at " << fuelPercentage << "% fuel." << endl;

    cout << "Do not fear the darkness of space, but look forward to the"
         << " nearest star!" << endl;
    cout << "Godspeed " << charName << "!" << endl;

    loadRoutes(); // Call the function to load routes from the file

    cout << "Here are the available planets you can travel to:" << endl;
    printPlanets(); // Call the function to print planet names

    string destination;
    string origin = "Earth"; // Starting point

    cout << "You are currently on " << origin << ". Where would you like to go?" << endl;
    cin >> destination;

    for (int i = 0; i < destination.length(); i++) {
        destination[i] = tolower(destination[i]); // Convert the rest of the letters to lowercase
    }
    destination[0] = toupper(destination[0]); // Capitalize the first letter

    while (destination != "Mercury" && destination != "Venus" && destination != "Earth" && destination != "Mars" && destination != "Jupiter"
      && destination != "Saturn" && destination != "Neptune" && destination != "Uranus") {
        cout << "Invalid destination. Please choose from the available planets." << endl;
        cin >> destination;

        for (int i = 0; i < destination.length(); i++) {
        destination[i] = tolower(destination[i]); // Convert the rest of the letters to lowercase
        }
        destination[0] = toupper(destination[0]); // Capitalize the first letter
    }

    while (destination == "Earth") {
        cout << "You are already on Earth! Please choose a different destination." << endl;
        
        cin >> destination;

        for (int i = 0; i < destination.length(); i++) {
        destination[i] = tolower(destination[i]); // Convert the rest of the letters to lowercase
        }
        destination[0] = toupper(destination[0]); // Capitalize the first letter
    }

    if (destination == "Mercury" || destination == "Venus" || destination == "Mars"|| destination == "Jupiter"
      || destination == "Saturn" || destination == "Neptune" || destination == "Uranus") {
        cout << "You have chosen to travel to " << destination << "!" << endl;
    } 

    cout << "Calculating route from " << origin << " to " << destination << "..." << endl;

    double distance = -1; // Initialize distance to an invalid value
    distance = calculateDistance(origin, destination);

    if (distance < 0) {
        cout << "Unable to calculate distance." << endl;
        return 0;
    }
    cout << "The distance from " << origin << " to " << destination << " is " << distance << " million kilometers." << endl;

    cout << "Calculating fuel needed for the trip..." << endl;
    double fuelNeeded = calculateFuelNeeded(distance);
    cout << endl << "Fuel needed for the trip: " << fuelNeeded << " units." << endl;

    while (fuelNeeded > fuel) {
        cout << "You do not have enough fuel for this trip. Please choose another destination." << endl;
        cin >> destination;

            for (int i = 0; i < destination.length(); i++) {
                destination[i] = tolower(destination[i]);
            }
        destination[0] = toupper(destination[0]);

        distance = calculateDistance(origin, destination);

        if (distance < 0) {
        cout << "Unable to calculate distance." << endl;
        return 0;
        }

        cout << "The distance from " << origin << " to " << destination << " is " << distance << " million kilometers." << endl;

        cout << "Calculating fuel needed for the trip..." << endl;

        fuelNeeded = calculateFuelNeeded(distance);
        
        cout << endl << "Fuel needed for the trip: " << fuelNeeded << " units." << endl;
        
    }
    
    fuel -= fuelNeeded; // Update fuel after the trip
    fuelPercentage = (fuel / MAX_FUEL) * 100; // Update fuel percentage
    cout << "You have successfully traveled to " << destination << "!" << endl;
    cout << "Remaining fuel: " << fuelPercentage << "%." << endl;
    
    return 0;
}

//Print planet names
void printPlanets() {
    fstream infile("planets.txt"); // Open the file for reading

    int count = 0; // Variable to count the number of planets

    if (!infile) {
        cout << "Error: Could not open file\n";
        return;
    } // Check if the file was opened successfully

    string planet;

    cout << "\nAvailable Planets:\n";

    while (count < MAX_PLANETS && getline(infile, planet)) { // Read each line from the file
        cout << "*** " << planet << " ###" <<endl;
        count++;
    }

    infile.close();
}

//Open the routes.txt file and load the routes into the routes array
void loadRoutes() {
    fstream infile("routes.txt"); // Open the file for reading

    if (!infile) {
        cout << "Error: Could not open routes.txt\n";
        return;
    } // Check if the file was opened successfully

    while (routeCount < MAX_ROUTES && infile >> routes[routeCount].from >> routes[routeCount].to >> routes[routeCount].distance) {
        routeCount++;
    }
    
    infile.close();
}

//calculate distance between planets
double calculateDistance(const string& from, const string& to) {
     for (int i = 0; i < routeCount; i++) {
        if (routes[i].from == from && routes[i].to == to) {
            return routes[i].distance;
        }
    }
    cout << "Error: Route from " << from << " to " << to << " not found.\n";
    return -1; // indicate that the route was not found
}

//calculate fuel needed for a trip
double calculateFuelNeeded(double distance) {
    double fuelNeeded = distance * FLAT_FUEL_CONSUMPTION_RATE;
    return fuelNeeded;
}

//calculate travel time for a trip
double calculateTravelTime(double distance) {
    double timeNeeded = distance / rateOfSpeed; // Time in days
    return timeNeeded;
}
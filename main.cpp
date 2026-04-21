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
struct Route {
     string from;
     string to; 
     double distance; // In millions of kilometers
};

const int MAX_ROUTES = 100; // Maximum number of routes
const int MAX_PLANETS = 8; // Maximum number of planets
Route routes[MAX_ROUTES]; // Array to store routes
int routeCount = 0; // Variable to keep track of the number of routes


double MAX_FUEL = 1000.0; // Maximum fuel capacity

int main() {
    cout << fixed << setprecision(2); // Set decimal precision for output

    double fuel = 1000.0; // Initial fuel
    double fuelPercentage = (fuel / MAX_FUEL) * 100;

    cout << "Hello..." << endl << "Enter your name:" << endl;

    string charName;
    getline(cin, charName);

    cout << "\nWelcome to the Space Exploration Journey!" << endl;
    cout << "You have been drafted to venture the cosmos and"
         << " be a hero for your home planet!" << endl;
    cout << "Do not fear the darkness of space, but look forward to the"
         << " nearest star!" << endl;
    cout << "Godspeed " << charName << "!" << endl;

     
    cout << "\n...Loading...\n...loading...\n...loading...\n" << endl;
    cout << "You are now in your spaceship, ready to explore the universe!" << endl;
    cout << "Your spaceship is at " << fuelPercentage << "% fuel." << endl;

    printPlanets(); // Call the function to print planet names
    loadRoutes(); // Call the function to load routes from the file

    string destination;
    string origin = "Earth"; // Starting point

    cout << "You are currently on " << origin << ". Where would you like to go?" << endl;
    getline(cin, destination);




    for (int i = 0; i < destination.length(); i++) {
        destination[i] = tolower(destination[i]); // Convert the rest of the letters to lowercase
    }
    destination[0] = toupper(destination[0]); // Capitalize the first letter of the destination

    if (destination == "Earth") {
        cout << "You are already on Earth! Please choose a different destination." << endl;
        return 0;
    }

    if (destination == "Mercury" || destination == "Venus" || destination == "Mars"|| destination == "Jupiter"
      || destination == "Saturn" || destination == "Neptune" || destination == "Uranus") {
        cout << "You have chosen to travel to " << destination << "!" << endl;
    } 
    else {
        cout << "Sorry, we do not have information on that destination. Please choose from the available planets." << endl;
        return 0;
    }

    cout << "Calculating route from " << origin << " to " << destination << "..." << endl;

    double distance = -1; // Initialize distance to an invalid value
    distance = calculateDistance(origin, destination);

    if (distance < 0) {
        cout << "Unable to calculate distance." << endl;
        return 0;
    }

    cout << "The distance from " << origin << " to " << destination << " is " << distance << " million kilometers." << endl;
    
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
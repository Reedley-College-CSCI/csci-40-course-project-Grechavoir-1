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
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_MATERIALS = 100; // Maximum number of materials
const int MAX_ROUTES = 100; // Maximum number of routes
const int MAX_PLANETS = 8; // Maximum number of planets

class SpaceTravel {
    private:
        struct Route {
            string from; // Origin
            string to; // Destination
            double distance; // In millions of kilometers
        };
        struct Material {
            string name; // Name of the material
            double amount; // Amount of material (tons)
            double cost; // Cost per unit
        };
        struct PlanetMaterial {
            string planet; // Name of planet
            string material; // Element or resource on planet
        };
        int hoursTraveled = 0; // Variable to track the number of hours traveled
        double MAX_FUEL = 1500.0; // Maximum fuel capacity
        double FLAT_FUEL_CONSUMPTION_RATE = 0.5; // Flat fuel consumption rate per million kilometers
        double rateOfSpeed = (1500000.0 / 24.0); // Speed of the spaceship in kilometers per hour
        int materialCount = 0; // Variable to keep track of the number of materials
        double tonToKilogram = 907.18; // Conversion factor from kilograms to tons
        double MAX_CARGO_WEIGHT = 50; // Maximum cargo weight in tons
        double MAX_TOTAL_HOURS = 17520; // Maximum total hours for 2 year mission
        double income = 0.0; // Variable to track income
        double FLAT_RATE_PAY_HOUR = 200.0; // Flat pay rate for each hour of travel
        double cargoWeight = 0.0; // initial cargo weight
        int routeCount = 0; // Variable to keep track of the number of routes
        int planetMaterialCount = 0; // Variable to keep track of how many materials are on a planet
        int cargoCount = 0; // Variable to keep track of
        double refuelSpeed = 5.0; // Variable for how many units per hour are refueled in the ship
        Route routes[MAX_ROUTES]; // Array to store routes
        Material materials[MAX_MATERIALS]; // Array to store materials
        Material cargo[MAX_MATERIALS]; // Array to track current cargo on ship
        PlanetMaterial planetMaterial[MAX_MATERIALS]; // Array to store planet materials
    
    public:
        void printPlanets(); // Function prototype to print planet names from a file
        void loadRoutes(); // Function prototype to load routes from a file
        void loadMaterials(); // Function prototype to load materials from a file
        void printMaterials(); // Function prototype to print materials from the file
        void loadPlanetMaterials(); // Function prototype to load planet_materials.txt
        void showPlanetMaterials(const string& planet);
        void generatePlanetPackages(const string& planet);
        void printPlanetDistances(const string& location);
        double calculateDistance(const string& from, const string& to); // Function prototype to calculate distance between planets
        double calculateFuelNeeded(double distance); // Function prototype to calculate fuel needed for a trip
        double calculateTravelTime(double distance); // Function prototype to calculate travel time for a trip
        double calculateFuelPercentage(double fuel); // Function prototype to calculate fuel percetage in spaceship
        double getMaterialPrice(const string& materialName); // Function prototype to get material price from materials.txt
        double calculateCargoValue(); // Function prototype to determine the total cost of a cargo package
        double flatMaterialIncrease(const string& planet); // Function prototype to give different planets larger cargo
        double timeToRefuel(double fuel); // Function prototype to both refuel and keep track of the time it takes
};

// Open the routes.txt file and read the routes into the routes array
void SpaceTravel::loadRoutes() {
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

//Print planet names
void SpaceTravel::printPlanets() {
    fstream infile("planets.txt"); // Open the file for reading

    int count = 0; // Variable to keep track of the number of planets

    if (!infile) {
        cout << "Error: Could not open planets.txt\n";
        return;
    } // Check if the file was opened successfully

    string planet;

    cout << "\nAvailable Planets:\n";

    while (count < MAX_PLANETS && getline(infile, planet)) {
        cout << "- " << planet << endl;
        count++;
    }

    infile.close();
}

//Load materials
void SpaceTravel::loadMaterials() {
    fstream infile("materials.txt"); // Open the file for reading

    if (!infile) {
        cout << "Error: Could not open materials.txt\n";
        return;
    } // Check if the file was opened successfully

    while (materialCount < MAX_MATERIALS && infile >> materials[materialCount].name >> materials[materialCount].amount >> materials[materialCount].cost) {
        materialCount++;
    }
    
    infile.close();
}

// Open the routes.txt file and read the routes into the routes array
void SpaceTravel::loadPlanetMaterials() {
    fstream infile("planet_materials.txt"); // Open the file for reading

    if (!infile) {
        cout << "Error: Could not open planet_materials.txt\n";
        return;
    } // Check if the file was opened successfully

    while (planetMaterialCount < MAX_MATERIALS && infile >> planetMaterial[planetMaterialCount].planet >> planetMaterial[planetMaterialCount].material) {
        planetMaterialCount++;
    }
    
    infile.close(); // closed text file
}

//Print materials
void SpaceTravel::printMaterials() {
    cout << "\nAvailable Materials:\n";

    for (int i = 0; i < materialCount; i++) {
        cout << "** " << materials[i].name << " **\n"
            << " Amount: " << materials[i].amount << " tons"
            << " Price: $" << materials[i].cost << endl;
    }
}

//Show materials at target planet
void SpaceTravel::showPlanetMaterials(const string& planet){
    cout << "\nPossible materials found on " << planet << ":\n";

    bool found = false;

    for (int i = 0; i < planetMaterialCount; i++) {
        if (planetMaterial[i].planet == planet) {

            cout << "- " << planetMaterial[i].material << endl; // Using planet_materials text file

            found = true;
        }
    }

    if (!found) {
        cout << "No materials found.\n";
    }
}

//Make the cargo
void SpaceTravel::generatePlanetPackages(const string& planet) {

    cout << "\nPre-packed cargo available on " << planet << ":\n";

    cargoCount = 0;

    for (int i = 0; i < planetMaterialCount; i++) {

        if (planetMaterial[i].planet == planet) {

            int kilograms = 100 + rand() % 901;

            cargo[cargoCount].name = planetMaterial[i].material;

            cargo[cargoCount].amount = kilograms + (flatMaterialIncrease(planet) * cargo[cargoCount].amount);

            cargo[cargoCount].cost = getMaterialPrice(planetMaterial[i].material);
                
            cout << "- " << cargo[cargoCount].name << ": " << cargo[cargoCount].amount << " kg\n";

            cargoCount++;
        }
    }
}

//Search for material price
double SpaceTravel::getMaterialPrice(const string& materialName) {

    for (int i = 0; i < materialCount; i++) {

        if (materials[i].name == materialName) {
            return materials[i].cost;
        }
    }

    return 0;
}

//Calculating cargo value
double SpaceTravel::calculateCargoValue() {

    double total = 0;

    for (int i = 0; i < cargoCount; i++) {
        total += cargo[i].amount * cargo[i].cost;
    }

    return total;
}

//Give the planets further from Earth an increase to their cargo size
double SpaceTravel::flatMaterialIncrease(const string& planet) {
    if (planet == "Mercury") {
        return 0.022; //(Distance from Earth to Mercury / Earth to Venus / 100) this applies to all of the other with Veus
                      //Venus as the standard
    }

    else if (planet == "Venus") {
        return 0.010;
    }

    else if (planet == "Mars") {
        return 0.019;
    }

    else if (planet == "Jupiter") {
        return 0.153;
    }

    else if (planet == "Saturn") {
        return 0.311;
    }

    else if (planet == "Uranus") {
        return 0.664;
    }

    else if (planet == "Neptune") {
        return 1.061;
    }

    else {
        return 0;
    }
}

//calculate distance between planets
double SpaceTravel::calculateDistance(const string& from, const string& to) {
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].from == from && routes[i].to == to) {
            return routes[i].distance;
        }
    }
    cout << "Error: Route from " << from << " to " << to << " not found.\n";
    return -1; // indicate that the route was not found}
}

//calculate fuel needed for a trip
double SpaceTravel::calculateFuelNeeded(double distance) {
    double fuelNeeded = distance * FLAT_FUEL_CONSUMPTION_RATE;
    return fuelNeeded;
}

//calculate current fuel in spaceship
double SpaceTravel::calculateFuelPercentage(double fuel) {
    double fuelPercentage = (fuel / MAX_FUEL) * 100;
    return fuelPercentage;
}

//calculate travel time for a trip
double SpaceTravel::calculateTravelTime(double distance) {
    double timeNeeded = (distance * 1000000) / rateOfSpeed; // Time in hours
    return timeNeeded;
}

double SpaceTravel::timeToRefuel(double fuel) {
    int time = 0;
    while (MAX_FUEL > fuel) {
        fuel += refuelSpeed;
        time++;
    }
    return time;
}

void SpaceTravel::printPlanetDistances(const string& location) {
    cout << "Here are your possible destinations and the distances.\n";

    int i = 0; 
    int j = 0;
    Route planetRoutes[MAX_ROUTES];
    int count = 0;

    // Collect only routes leaving from the selected planet
    for (i = 0; i < routeCount; i++) {
        if (routes[i].from == location) {
            planetRoutes[count] = routes[i];
            count++;
        }
    }

    // Sort routes by distance (smallest to largest) with selection sort
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (planetRoutes[i].distance > planetRoutes[j].distance) {

                // Swap routes
                Route temp = planetRoutes[i];
                planetRoutes[i] = planetRoutes[j];
                planetRoutes[j] = temp;
            }
        }
    }

    // Print sorted routes
    for (i = 0; i < count; i++) {
        cout << "- " << planetRoutes[i].to
             << " : " << planetRoutes[i].distance
             << " million kilometers\n";
    }
}

void helloWorld();
void introMessage(const string& charName);
string capitalizeWord(string text);

void helloWorld() {
    cout << "Hello..." << endl << "Please enter your name:" << endl;
}

void introMessage(const string& charName) {
    cout << "\nWelcome to the Space Exploration Journey!\n";
    cout << "You have been drafted to venture the cosmos and"
         << " be a hero for your home planet!\n";
    
    cout << "\n...Loading...\n...loading...\n...loading...\n";
    cout << "You are now in your spaceship, ready to explore the universe!\n";
    cout << "Your spaceship is fully loaded with fuel and ready to go.\n";
    cout << "\n\nDo not fear the darkness of space, but look forward to the"
        << " nearest star!\n";
    cout << "Godspeed " << charName << "!\n";
    cout << "Here are the available planets you can travel to:" << endl;
}

string capitalizeWord(string text){
    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]); // Convert the letters to lowercase
    }
    text[0] = toupper(text[0]); // Capitalize the first letter
    
    return text;
}

int main() {
    srand(time(0));
    cout << fixed << setprecision(2); // Set decimal precision for output
    SpaceTravel journey;

    journey.loadMaterials(); // Call the function to load materials from the file
    journey.loadRoutes(); // Call the function to load routes from the file
    journey.loadPlanetMaterials();
    
    double fuel = 1500.0; // Initial fuel
    double tank = journey.calculateFuelPercentage(fuel);

    helloWorld();

    string charName;
    getline(cin, charName);

    cout << "Are you ready to start your journey? (yes/no)" << endl;

    string ready;
    cin >> ready;

    ready = capitalizeWord(ready);

    while (ready != "Yes" && ready != "No") {
        cout << "Invalid input. Please enter 'yes' or 'no':" << endl;
        cin >> ready;

        ready = capitalizeWord(ready);
    }

    if (ready != "Yes") {
        cout << "Take your time to prepare. Come back when you are ready!" << endl;
        return 0;
    }

    introMessage(charName);

    string destination;
    string origin = "Earth"; // Starting point

    cout << "You are currently on " << origin << ". Where would you like to go?\n";

    journey.printPlanetDistances(origin);
    cin >> destination;

    destination = capitalizeWord(destination);

    while (destination != "Mercury" && destination != "Venus" && destination != "Earth" && destination != "Mars" && destination != "Jupiter"
      && destination != "Saturn" && destination != "Neptune" && destination != "Uranus") {
        cout << "Invalid destination. Please choose from the available planets." << endl;
        cin >> destination;

        destination = capitalizeWord(destination);
    }

    while (destination == "Earth") {
        cout << "You are already on Earth! Please choose a different destination." << endl;
        cin >> destination;

        destination = capitalizeWord(destination);
    }

    string confirm;

    if (destination == "Mercury" || destination == "Venus" || destination == "Mars"|| destination == "Jupiter"
    || destination == "Saturn" || destination == "Neptune" || destination == "Uranus") {
        cout << "You have chosen to travel to " << destination << "!" << endl;
    } 
    
    journey.showPlanetMaterials(destination);

    cout << "Do you wish to choose " << destination << " as your destination? (type confirm to begin)\n";
    cin >> confirm;
    confirm = capitalizeWord(confirm);

    while (confirm != "Confirm") {
        cout << "Where would you like to go to instead?\n";
        cin >> destination;

        destination = capitalizeWord(destination);

        while (destination != "Mercury" && destination != "Venus" && destination != "Earth" && destination != "Mars" && destination != "Jupiter"
            && destination != "Saturn" && destination != "Neptune" && destination != "Uranus") {
            cout << "Invalid destination. Please choose from the available planets.\n";
            cin >> destination;

            destination = capitalizeWord(destination);
        }

        while (destination == "Earth") {
            cout << "You are already on Earth! Please choose a different destination.\n";
            cin >> destination;

            destination = capitalizeWord(destination);
        }

        journey.showPlanetMaterials(destination);

    cout << "Do you wish to choose " << destination << " as your destination? (type confirm to begin)\n";
    cin >> confirm;
    confirm = capitalizeWord(confirm);
    }
    

    cout << "Calculating route from " << origin << " to " << destination << "...\n";

    double distance = -1; // Initialize distance to an invalid value
    distance = journey.calculateDistance(origin, destination);

    if (distance < 0) {
        cout << "Unable to calculate distance.\n";
        return 0;
    }

    cout << "The distance from " << origin << " to " << destination << " is " << distance << " million kilometers.\n";

    cout << "Calculating fuel needed for the trip...\n";
    double fuelNeeded = journey.calculateFuelNeeded(distance);
    cout << endl << "Fuel needed for the trip: " << fuelNeeded << " units.\n";

    while (fuelNeeded > fuel) {
        cout << "You do not have enough fuel for this trip. Please choose another destination.\n";

        cin >> destination;

        distance = journey.calculateDistance(origin, destination);

        if (distance < 0) {
        cout << "Unable to calculate distance." << endl;
        return 0;
        }

        cout << "The distance from " << origin << " to " << destination << " is " << distance << " million kilometers.\n";
    
        cout << "Calculating fuel needed for the trip...\n";
        fuelNeeded = journey.calculateFuelNeeded(distance);

        cout << endl << "Fuel needed for the trip: " << fuelNeeded << " units.\n";
        
    }
    
    fuel -= fuelNeeded; // Update fuel after the trip
    tank = journey.calculateFuelPercentage(fuel);
    cout << "You have successfully traveled to " << destination << "!\n";
    cout << "Remaining fuel: " << tank << "%.\n";
    double time = journey.calculateTravelTime(distance);
    cout << "Travel time: " << (time / 24.0) << " days.\n";

    journey.generatePlanetPackages(destination);

    cout << "\nTotal cargo value: $" << journey.calculateCargoValue() << endl;

    int refuelTime = journey.timeToRefuel(fuel);
    cout << "After " << refuelTime << " hours, your spaceship is ready to fly again.\n";
    journey.printPlanetDistances(destination);

    return 0;
}
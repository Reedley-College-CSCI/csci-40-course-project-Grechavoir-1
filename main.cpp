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

void introMessage(const string& charName);
string capitalizeWord(string text);

void introMessage(const string& charName) {
    cout << "\nWelcome to the Space Exploration Journey!\n";
    cout << "You have been drafted to venture the cosmos and"
         << " be a hero for your home planet!\n";
    
    cout << "\n...Loading...\n...loading...\n...loading...\n";
    cout << "\nYou are now in your spaceship, ready to explore the universe!\n";
    cout << "Your spaceship is fully loaded with fuel and ready to go.\n";
    cout << "\nDo not fear the darkness of space, but look forward to the"
        << " nearest star!\n";
    cout << "Godspeed " << charName << "!\n";
}

string capitalizeWord(string text){
    if (text.length() == 0) { // Issues if user doesn't enter anything
        return text;
    }

    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]); // Convert the letters to lowercase
    }
    text[0] = toupper(text[0]); // Capitalize the first letter
    
    return text;
}

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
        struct Journey {
            string from;
            string to;
            double distance;
            double totalHours;
            double cargo;
        };
        struct Mission {
            string planet;
            double distance;
        };
        double MAX_FUEL = 2500.0; // Maximum fuel capacity
        double MAX_CARGO_WEIGHT = 50; // Maximum cargo weight in tons
        double MAX_TOTAL_HOURS = 175200.0; // Maximum total hours for 20 year mission
        double FLAT_FUEL_CONSUMPTION_RATE = 0.5; // Flat fuel consumption rate per million kilometers
        double FLAT_RATE_PAY_HOUR = 50.0; // Flat pay rate for each hour of travel
        
        double rateOfSpeed = (6000000.0 / 24.0); // Speed of the spaceship in kilometers per hour
        double tonToKilogram = 907.18; // Conversion factor from kilograms to tons
        double refuelSpeed = 5.0; // Variable for how many units per hour are refueled in the ship
        
        double totalDistanceTraveled = 0.0;
        double totalHoursAway = 0.0;
        double cargoWeight = 0.0;
        double totalCargo = 0.0;
        
        Route routes[MAX_ROUTES];
        int routeCount = 0;
        Material materials[MAX_MATERIALS];
        int materialCount = 0;
        Material cargo[MAX_MATERIALS];
        int cargoCount = 0;
        PlanetMaterial planetMaterial[MAX_MATERIALS];
        int planetMaterialCount = 0;
        Journey travelLog[MAX_ROUTES];
        int trips = 0;
        string planets[MAX_PLANETS];
        int planetCount = 0;
        Mission options[MAX_PLANETS];
        int optionCount = 0;
    
    public:
        // Function prototypes to open and read text files
        void loadRoutes(); 
        void loadMaterials(); 
        void loadPlanets();
        void loadPlanetMaterials(); 

        void printPlanets(); // Function prototype to print planet names from a file
        void printMaterials(); // Function prototype to print materials from the file
        void printPlanetDistances(const string& location);

        string getDestinationPlanet();
        string confirmUserChoice();
        bool trip(string& origin, string destination, double& fuel);
        bool fuelCheck(string origin, string destination, double fuel);
        
        void showPlanetMaterials(const string& planet);
        void generatePlanetPackages(const string& planet);
        int countPlanetMaterials(const string& planet);
        void printMissionPlanets(const string& origin, const string& material);
        string generateMissionMaterial();

        double calculateCargoWeight();
        void convertCargoWeight();
        void printCurrentCargoCapacity();
        bool cargoTooClose();
        void dropOffCargo();
        void clockCountdown();
        void cargoStatistics();

        double calculateTravelTime(double distance); // Function prototype to calculate travel time for a trip
        double cargoSpeedSlowDown();
        
        double calculateDistance(const string& from, const string& to); // Function prototype to calculate distance between planets
        double calculateFuelNeeded(double distance); // Function prototype to calculate fuel needed for a trip
        double calculateFuelPercentage(double fuel); // Function prototype to calculate fuel percetage in spaceship
        
        double getMaterialPrice(const string& materialName); // Function prototype to get material price from materials.txt
        double calculateCargoValue(); // Function prototype to determine the total cost of a cargo package
        double flatMaterialIncrease(const string& planet); // Function prototype to give different planets larger cargo
        double timeToRefuel(double& fuel); // Function prototype to both refuel and keep track of the time it takes
        bool validDestination(const string& destination);
        
        // Function to keep a running total of stats
        void updateStats(string from, string to, double distance, double travelTime, double refuelTime, double cargo); 
        void printStats();
        bool outOfTime();

        void goodbyeLog(const string& charName);

        void addNewMaterial();
        bool validPlanetName(const string& planet);
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

void SpaceTravel::loadPlanets() {
    fstream infile("planets.txt"); // Open the file for reading

    if (!infile) {
        cout << "Error: Could not open planets.txt\n";
        return;
    }

    while (planetCount < MAX_PLANETS && infile >> planets[planetCount]) {
        planetCount++;
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

string SpaceTravel::getDestinationPlanet() {
    string destination;

    cout << "Which planet would you like to travel to?\n";
    cin >> destination;
    destination = capitalizeWord(destination);

    while (!validDestination(destination)) {
        cout << "That planet does not contain the required materials. Choose one from the list.\n";
        cin >> destination;
        destination = capitalizeWord(destination);
    }

    return destination;
}

string SpaceTravel::confirmUserChoice() {
    string confirm;

    cout << "Type confirm to begin or no to choose another destination:\n";
    cin >> confirm;
    confirm = capitalizeWord(confirm);

    while (confirm != "Confirm" && confirm != "No") {
        cout << "Invalid input. Type confirm or no:\n";
        cin >> confirm;
        confirm = capitalizeWord(confirm);
    }

    return confirm;
}

bool SpaceTravel::trip(string& origin, string destination, double& fuel) {
    double distance = calculateDistance(origin, destination);
    if (distance < 0) {
        cout << "Unable to calculate distance.\n";
        return false;
    }

    double fuelNeeded = calculateFuelNeeded(distance);

    fuel -= fuelNeeded;

    double travelTime = calculateTravelTime(distance);

    cout << "You have successfully traveled to " << destination << "!\n";
    cout << "Travel time: " << travelTime / 24.0 << " days.\n";

    generatePlanetPackages(destination);

    double refuelTime = timeToRefuel(fuel);
    double cargoValue = calculateCargoValue();

    convertCargoWeight();
    updateStats(origin, destination, distance, travelTime, refuelTime, cargoValue);

    origin = destination;

    if (origin == "Earth") {
        dropOffCargo();
    }

    cout << "After " << refuelTime << " hours, your spaceship is ready to fly again.\n";
    cout << "Your tank is now at " << fuel << " units.\n";

    return true;
}

bool SpaceTravel::fuelCheck(string origin, string destination, double fuel) {
    double distance = calculateDistance(origin, destination);
    double fuelNeeded = calculateFuelNeeded(distance);

    return fuelNeeded <= fuel;
}

string SpaceTravel::generateMissionMaterial() {
    int randomIndex = rand() % materialCount;
    return materials[randomIndex].name;
}

void SpaceTravel::printMissionPlanets(const string& origin, const string& material) {
    optionCount = 0;

    // Linear search for planets that have the required material because the data is not sorted
    for (int i = 0; i < planetMaterialCount; i++) {
        if (planetMaterial[i].material == material && planetMaterial[i].planet != origin) {

            double distance = calculateDistance(origin, planetMaterial[i].planet);

            if (distance >= 0) {
                options[optionCount].planet = planetMaterial[i].planet;
                options[optionCount].distance = distance;
                optionCount++;
            }
        }
    }

    // Sort planets by distance using selection sort
    for (int i = 0; i < optionCount - 1; i++) {
        for (int j = i + 1; j < optionCount; j++) {
            if (options[i].distance > options[j].distance) {
                Mission temp = options[i];
                options[i] = options[j];
                options[j] = temp;
            }
        }
    }

    cout << "\nPlanets that contain " << material << ":\n";

    if (optionCount == 0) {
        cout << "No planets found with that material.\n";
        return;
    }

    for (int i = 0; i < optionCount; i++) {
        cout << "- " << options[i].planet << " : " << options[i].distance << " million kilometers\n";
    }
}

bool SpaceTravel::validDestination(const string& destination) {
    for (int i = 0; i < optionCount; i++) {

        if (destination == options[i].planet) {
            return true;
        }
    }

    return false;
}



void SpaceTravel::updateStats(string from, string to, double distance, double travelTime, double refuelTime, double cargo) {
    if (trips < MAX_ROUTES) {
        double tripTotalHours = travelTime + refuelTime;

        travelLog[trips].from = from;
        travelLog[trips].to = to;
        travelLog[trips].distance = distance;
        travelLog[trips].totalHours = tripTotalHours;
        travelLog[trips].cargo = cargo;

        trips++;

        totalDistanceTraveled += distance;
        totalHoursAway += tripTotalHours;
        totalCargo += cargo;
    }
}

void SpaceTravel::printStats() {
    cout << fixed << setprecision(2);
    cout << "\nFrom the cargo you dropped off you added an additional $" << (totalCargo / 100.0) << " to your payment.\n";
    cout << "You made $" << (totalHoursAway * FLAT_RATE_PAY_HOUR) << " from your salary.\n";
    cout << "You worked " << (totalHoursAway / 24.0) << " days\n";
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

    if (planet == "Earth") { // Stop the program from outputing a zero dollar package when returning to earth
        cargoCount = 0;
        return;
    }

    cout << "\nPre-packed cargo available on " << planet << ":\n";

    cargoCount = 0;

    int materialTotal = countPlanetMaterials(planet);

    if (materialTotal == 0) {
        cout << "No cargo available.\n";
        return;
    }

    for (int i = 0; i < planetMaterialCount; i++) {

        if (planetMaterial[i].planet == planet) {

            int kilograms = 500 + rand() % 5001; // generate random number for each material

            cargo[cargoCount].name = planetMaterial[i].material; // start filling array for the name

            //To balance the planets, the material total is going to be divided from the kilograms so that a planet with
            //20 elements for will be just as equal to a planet with 10 elements apart from their distances and the randomness
            cargo[cargoCount].amount =
                (kilograms / static_cast<double>(materialTotal)) * (1 + flatMaterialIncrease(planet));

            cargo[cargoCount].cost = getMaterialPrice(planetMaterial[i].material); // Use the materials.txt file to get the cost

            cout << "- " << cargo[cargoCount].name << ": " << cargo[cargoCount].amount << " kg\n";  //output what we got

            cargoCount++;
        }
    }
    cout << "\nTotal cargo value: $" << calculateCargoValue() << endl; // Use our function to display the price of our cargo
}

int SpaceTravel::countPlanetMaterials(const string& planet) {
    int count = 0;

    for (int i = 0; i < planetMaterialCount; i++) {
        if (planetMaterial[i].planet == planet) {
            count++;
        }
    }

    return count;

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

double SpaceTravel::calculateCargoWeight() {
    double totalWeight = 0.0;

    for (int i = 0; i < cargoCount; i++) {
        totalWeight += cargo[i].amount;
    }

    return totalWeight;
}

void SpaceTravel::convertCargoWeight() {
    double cargoKilograms = calculateCargoWeight();

    cargoWeight += (cargoKilograms / tonToKilogram);
}

bool SpaceTravel::cargoTooClose() {
    return cargoWeight >= (MAX_CARGO_WEIGHT * 0.85);
}

void SpaceTravel::dropOffCargo() {
    cargoWeight = 0.0;
    cout << "\nCargo has successfully been dropped off on Earth!\n";
    cout << "You now have an empty bay to fill. Get to it.\n";
}

void SpaceTravel::clockCountdown() {
    double hoursLeft = MAX_TOTAL_HOURS - totalHoursAway;

    double yearsLeft = hoursLeft / 24.0 / 365.0;
    double daysLeft = hoursLeft / 24.0;

    cout << fixed << setprecision(2);

    cout << "Time remaining until mandatory retirement:\n";
    cout << daysLeft << " days (" << yearsLeft << " years)\n";
}

void SpaceTravel::cargoStatistics() {
    double cargoPercent = (cargoWeight / MAX_CARGO_WEIGHT) * 100.0;
    double slowdownMultiplier = cargoSpeedSlowDown();
    double slowdownPercent = (slowdownMultiplier - 1.0) * 100.0;

    cout << fixed << setprecision(2);

    cout << "Your cargo bay is at " << cargoPercent << "%\n";
    cout << "The cargo bay is holding " << cargoWeight << " tons\n";
    cout << "This is causing your trips to be " << slowdownPercent << "% longer\n";
}

//Give the planets further from Earth an increase to their cargo size
double SpaceTravel::flatMaterialIncrease(const string& planet) {
    if (planet == "Mercury") {
    return 0.05;
}
else if (planet == "Venus") {
    return 0.03;
}
else if (planet == "Mars") {
    return 0.08;
}
else if (planet == "Jupiter") {
    return 0.75;
}
else if (planet == "Saturn") {
    return 1.25;
}
else if (planet == "Uranus") {
    return 2.00;
}
else if (planet == "Neptune") {
    return 3.00;
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
    double slowed = cargoSpeedSlowDown();

    return (timeNeeded * slowed);
}

double SpaceTravel::cargoSpeedSlowDown() {
    double cargoPercent = cargoWeight / MAX_CARGO_WEIGHT;

    return 1 + (cargoPercent * 0.35);
}

double SpaceTravel::timeToRefuel(double& fuel) {
    double time = 0;
    while (MAX_FUEL > fuel) {
        fuel += refuelSpeed;
        time++;
    }

    if (MAX_FUEL < fuel) {
            fuel = MAX_FUEL;
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

bool SpaceTravel::outOfTime() {
    return totalHoursAway >= MAX_TOTAL_HOURS;
}

void SpaceTravel::goodbyeLog(const string& charName) {
    ofstream outFS;

    // Open file
   outFS.open("Farewell.txt");

   if (!outFS.is_open()) {
      cout << "Could not open file Farewell.txt." << endl;
      return;
   }

   outFS << "Here is your report captain " << charName << endl;

   outFS << fixed << setprecision(2);

   for (int i = 0; i < trips; i++) {
        outFS << "Trip #" << i + 1 << endl;
        outFS << "From: " << travelLog[i].from << endl;
        outFS << "To: " << travelLog[i].to << endl;
        outFS << "Distance: " << travelLog[i].distance << " million kilometers" << endl;
        outFS << "Time: " << travelLog[i].totalHours / 24.0 << " days" << endl;
        outFS << "Cargo value: $" << travelLog[i].cargo << endl << endl;
    }

    outFS << "Total cargo payment bonus: $" << totalCargo / 100.0 << endl;
    outFS << "Total salary: $" << totalHoursAway * FLAT_RATE_PAY_HOUR << endl;
    outFS << "Total days worked: " << totalHoursAway / 24.0 << endl;

    outFS.close();

    cout << "\nTravel log saved to Farewell.txt\n";
}

void SpaceTravel::addNewMaterial() {
    
    ofstream materialFS("materials.txt", ios::app);
    ofstream planetFS("planet_materials.txt", ios::app);

    if (!materialFS.is_open()) {
        cout << "Could not open materials.txt\n";
        return;
    }

    if (!planetFS.is_open()) {
        cout << "Could not open planet_materials.txt\n";
        return;
    }

    string material;
    string planet;
    double cost;

    cout << "Enter new material name:\n";
    cin >> material;
    material = capitalizeWord(material);

    cout << "Enter material price per kg:\n";
    cin >> cost;

    // Add material to materials.txt
    materialFS << fixed << setprecision(2);
    materialFS << endl << material << " 0 " << cost;

    cout << "\nEnter planets where " << material << " is found.\n";
    cout << "Type 'done' when finished.\n";

    while (true) {

        cout << "Planet: ";
        cin >> planet;

        planet = capitalizeWord(planet);

        if (planet == "Done") {
            break;
        }

        while (!validPlanetName(planet)) {
            cout << "Invalid planet. Please choose one of the known planets.\n";

            cin >> planet;
            planet = capitalizeWord(planet);

            if (planet == "Done") {
                break;
            }
        }

        planetFS << endl << planet << " " << material;

        cout << material << " added to " << planet << ".\n";
    }

    materialFS.close();
    planetFS.close();

    cout << "\nNew material successfully added.\n";
}

bool SpaceTravel::validPlanetName(const string& planet) {
    for (int i = 0; i < planetCount; i++) {
        if (planet == planets[i]) {
            return true;
        }
    }

    return false;

}

int main() {
    srand(time(0));
    cout << fixed << setprecision(2); // Set decimal precision for output
    SpaceTravel journey;
    string confirm;
    string charName;
    string ready;
    string destination;
    string origin = "Earth"; // Starting point
    string keepGoing = "Yes";
    string requiredMaterial;

    // Call functions to load the text files into the program
    journey.loadMaterials();
    journey.loadRoutes();
    journey.loadPlanetMaterials();
    journey.loadPlanets();
    
    double fuel = 2500.0; // Initial fuel

    cout << "Hello traveler... can you please tell us your name?\n";
    
    getline(cin, charName);

    cout << "Are you ready to start your journey? (yes/no)" << endl;
    
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

    cout << "Before you get started on your journey.  Do you wish to add any elements to the database? (yes/no)\n";
    cout << "Note: Adding multiple elements to one planet does not gain an advantage as it program adjusts to make it fair.\n";
    string add;
    cin >> add;
    add = capitalizeWord(add);

    while (add != "Yes" && add != "No") {
        cout << "Please type yes or no:\n";
        cin >> add;

        add = capitalizeWord(add);
    }

    while (add == "Yes") {

    journey.addNewMaterial();

    cout << "\nWould you like to add another material? (yes/no)\n";
    cin >> add;

    add = capitalizeWord(add);

    while (add != "Yes" && add != "No") {
        cout << "Please type yes or no:\n";
        cin >> add;

        add = capitalizeWord(add);
    }
}



    while (keepGoing == "Yes" && !journey.outOfTime()) {
        requiredMaterial = journey.generateMissionMaterial();

        cout << "\nMission: Find and collect " << requiredMaterial << "!\n";
        journey.printMissionPlanets(origin, requiredMaterial);

        destination = journey.getDestinationPlanet();

        journey.showPlanetMaterials(destination);

        confirm = journey.confirmUserChoice();

        while (confirm == "No") {
            destination = journey.getDestinationPlanet();

            journey.showPlanetMaterials(destination);
            confirm = journey.confirmUserChoice();
        }

        bool tripWorked = journey.trip(origin, destination, fuel);

        if (!tripWorked) {
            cout << "Trip canceled. Please choose another destination.\n";
            continue;
        }

        if (journey.cargoTooClose() && origin != "Earth") {
            cout << "\nWarning: Your cargo bay is almost full.\n";
            cout << "You should return to Earth soon to unload cargo.\n";
        }

        journey.cargoStatistics();
        journey.clockCountdown();

        if (journey.cargoTooClose() && origin != "Earth") {
            cout << "\n***Warning***\t" << "***AUTO PILOT ACTIVATED***\n";
            cout << "Cargo bay is reaching full capacity and returning to Earth\n";
            
            bool returned = journey.trip(origin, "Earth", fuel);

            if (!returned) {
                cout << "Autopilot failed. Not enough fuel to return to Earth.\n";
            }
            continue;
        }

        cout << "\nWould you like to keep traveling? (yes/no)\n";
        cin >> keepGoing;
        keepGoing = capitalizeWord(keepGoing);

        while (keepGoing != "Yes" && keepGoing != "No") {
            cout << "Please type 'yes' or 'no'\n";
            cout << "Would you like to keep traveling? (yes/no)\n";
            cin >> keepGoing;
            keepGoing = capitalizeWord(keepGoing);
        }
    }
    journey.printStats();
    journey.goodbyeLog(charName);

    return 0;
}
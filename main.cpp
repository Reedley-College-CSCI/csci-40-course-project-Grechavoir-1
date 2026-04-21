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
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
    cout << "Hello..." << endl << "Enter your name:" << endl;

    string charName;
    getline(cin, charName);

    cout << "Welcome to the Space Exploration Journey!" << endl;
    cout << "You have been drafted to venture the cosmos and"
         << " be a hero for your home planet!" << endl;
    cout << "Do not fear the darkness of space, but look forward to the"
         << " nearest star!" << endl;
    cout << "Godspeed " << charName << "!" << endl;

    return 0;
}

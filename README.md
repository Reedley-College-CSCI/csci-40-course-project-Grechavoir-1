[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Ay551EX-)
# CS1 Final Project - [A Space Journey]

## 1. Overview
- What problem does your project solve?  
- Briefly describe the purpose and key features of your program.  
This project solves the problem of creating an interactive space exploration simulation where the player manages travel, cargo collection, fuel consumption, and time limitations while traveling between planets.

The purpose of the program is to simulate the experience of a space traveler completing missions throughout the solar system. The player receives randomized material collection missions, chooses planets to travel to, collects cargo, and returns materials to Earth while being able to add their own materials to the mission.

Key features of the program include: 
Randomly generated missions and package sizes
Planetary travel system
Fuel consumption and automatic refueling
Cargo generation and cargo weight management
Travel time calculations
Automatic auto pilot to return user to Earth when cargo becomes too heavy
Persistent data storage using text files
Mission and travel log generation
Ability for users to add new materials and planets dynamically
---

## 2. Design Decisions
- What fundamental programming constructs and data types did you use, and why?  
Variables and constants
Functions
Arrays
Structs
Loops
Conditional statements
File input/output
Searching and sorting algorithms
Random number generation

- Why did you choose to structure your data using structs?  
I chose to structure my data using structs because structs allow multiple related variables to be grouped together into one object. For example, my text files all have different formats with important data so structs helped format the program.

- How did you implement searching and sorting? What algorithms did you use and why? 
 Sorting was implemented using selection sort to organize planets and routes by distance. This was beacuse the data was small and the algorithm was easy to implement into my program

- How do you ensure data persistence between program runs?  
The text files are properly opened and closed and all data that is written to them is not overwriting the original data apart from the travel log that makes a new text file.

- Did you consider alternative approaches? If so, why did you not use them?  


---

## 3. Testing Summary
- **Structured Testing Log:** Include a table with test cases, expected output, actual output, and pass/fail status.  
| Test Case ID | Description | Input | Expected Output | Actual Output | Pass/Fail
| TC-01 | Start game with valid input | `Yes` when asked to begin | Program starts the journey and displays intro message | Intro message displayed and game continued normally | Pass
| TC-02 | Enter invalid yes/no input | `Maybe`| Program asks user to enter valid input again | Reprompt displayed correctly| Pass
| TC-03 | Travel to a valid planet | `Mars`| Spaceship travels successfully and displays travel time| Trip completed and cargo generated| Pass
| TC-04| Enter invalid planet name | `Pluto`| Program rejects input and asks again| Invalid planet message displayed | Pass
| TC-05 | Confirm destination properly| `Confirm`| Trip begins | Trip started successfully  | Pass 
| TC-06| Reject destination and choose another | `No`  | Program allows another destination selection  | New destination prompt displayed  | Pass 
| TC-07| Attempt trip without enough fuel | Select distant planet with low fuel| Trip canceled and fuel warning displayed| Warning displayed and trip prevented | Pass 
| TC-08  | Cargo reaches dangerous level    | Continue collecting cargo until near max capacity | Autopilot activates and returns player to Earth  | Autopilot activated correctly   | Pass 
| TC-09 | Add a new material   | `Titanium` with valid planet names | Material saved to text files| Material appeared in files after reload | Pass
| TC-10 | Enter invalid planet while adding material | `Plutox` | Program rejects invalid planet name | Error message displayed and reprompted | Pass 
| TC-11 | Missing data file | Remove `materials.txt` before running| Program displays file error | Error message shown correctly | Pass
| TC-12| End journey voluntarily  | `No` when asked to continue | Program exits and writes farewell log| Farewell.txt created successfully | Pass
| TC-13| Retirement timer expires | Continue traveling until time runs out | Game ends automatically| Program ended correctly | Pass
| TC-14 | Generate mission material | Random material generation  | Mission displays a valid material| Valid material shown from database | Pass 
| TC-15 | Return to Earth with cargo | Travel back to Earth | Cargo dropped off and cargo weight reset| Cargo successfully reset to zero | Pass

- What testing methods did you use?  
- Provide examples of test inputs (valid and invalid) and describe how your program responds.  

---

## 4. Technical Walkthrough
- Explain the main functionality of your program.  
- **Include a link to your required video demonstration** showcasing how the project works (**3-7 minutes**). 
    Make sure it shareable without approval needed.
https://youtu.be/UvAQUGSbMgU
---

## 5. Challenges and Lessons Learned
- What challenges did you encounter while working on this project?  
One major challenge was organizing large amounts of data across multiple structs, arrays, and functions. It was difficult to keep track of how different parts of the program interacted with each other.
- What key lessons did you learn about programming and problem-solving?  
I also learned how important it is to test programs repeatedly with both valid and invalid inputs.

---

## 6. Future Improvements
- If you had more time, what changes or enhancements would you make?  
I really wanted to add a realistic orbit for the planets instead of a static distance approach.  However, I lacked the knowledge to impement these elliptical orbits not only into the program but also get them smoothly working.
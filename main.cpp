#include <iostream>
#include <chrono>
#include <deque>
#include <array>
#include "Car-1.h"

using namespace std;
using namespace chrono;

void print_vehicles(const deque<Car>&);
void print_lanes(const array<deque<Car>,4>&);
void update_lanes(array<deque<Car>,4>&);
void init_lanes(array<deque<Car>,4>&);

int timeOperations = 0;

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    // Initializes our lanes and prints them out
    cout << "Initial queue:" << endl;
    array<deque<Car>,4> lanes; 
    init_lanes(lanes); 
    print_lanes(lanes); 

    // Initalizes our timer
    time_point start = high_resolution_clock::now();
    time_point now = high_resolution_clock::now();

    // Run our program for 20 time operations
    while(timeOperations<20){
        now = high_resolution_clock::now(); 
        milliseconds duration = duration_cast<milliseconds>(now-start); 

        // Checks if the timer has hit 1000 milliseconds 
        if(duration.count() > 1000){
            cout << "\nTime: " << timeOperations+1 << endl;

            update_lanes(lanes);
            print_lanes(lanes);

            start = high_resolution_clock::now(); // Resets the timer
            timeOperations++; 
        }
    }
    return 0;
}

/// @brief Initializes our Lanes
/// @param lanes The lanes that will be initialized
void init_lanes(array<deque<Car>,4> &lanes){
    for(deque<Car> &vehicles: lanes)
        for (int i = 0; i <= rand()%4; i++) 
            vehicles.push_back(Car());
};

/// @brief Updates our lanes. 39% chance car joins. 46% car leaves. 15% car switches lane. If a lane is empty it has a 50% chance for a car to join its lane.
/// @param lanes This lanes array will be modified/updated.
void update_lanes(array<deque<Car>,4> &lanes){
    int currentLane = 0;
    
    int chanceJoin = 39, chanceLeave = 46, chanceSwitch = 15; // The percent chance of something happening when a lane isn't empty
    int chanceJoinEmpty = 50 ; // The percent chance of something happening when a lane is empty

    // Iterates through every lane
    for(deque<Car> &vehicles: lanes){
        cout << "Lane: " << currentLane+1 << " ";
        int event = rand() % 100 + 1; // Determines whether a car will leave or join the line

        // Checks if the lane is empty
        if(vehicles.empty()){
            // If the lane is empty a (chanceJoinEmpty)% chance of a vehicle joining the lane 
            if(event <= chanceJoinEmpty){
                vehicles.push_back(Car());
                cout << "Joined: ";
                vehicles.back().print();
            }else{
                cout << "Empty" << endl;
            }
        }
        else{
            // 39% chance a car joins the lane
            if(event <= chanceJoin){
                // Adds a car to the back of the lane
                vehicles.push_back(Car());
                cout << "Joined: ";
                vehicles.back().print(); // Prints the recently added car
            }
            // 46% chance a car pays the toll leaving the lane
            else if(event<= chanceJoin + chanceLeave) {
                // Removes a car from the front of the lane
                cout << "Car paid: ";
                vehicles.front().print(); // Prints the car before its removed
                vehicles.pop_front();
            }
            // 15% chance a car pays the toll leaving the lane
            else{
                int newLane = rand()% 4; 
                while(newLane == currentLane) {newLane = rand() % 4 ;}

                cout << "Switched: ";

                Car temp = vehicles.back(); // Gets newest car
                vehicles.pop_back(); // Removes newest car;
                temp.print(); // Prints the car thats moving
                
                // Gets the new lane and make's sure its not the same as the current lane

                lanes.at(newLane).push_back(temp);
            }
        }

        currentLane++; // Iterates our current lane
    }
}

/// @brief It Prints the lanes to the terminal. Does not modify lanes
/// @param lanes These lanes will be printed not modified.
void print_lanes(const array<deque<Car>, 4> &lanes){
    int laneNumber = 0;

    // Iterates through lanes and prints each dequeue<Car> queue
    for(deque<Car> vehicles: lanes){
        laneNumber++;
        cout << "Lane " << laneNumber << " Queue:"<< endl;
        print_vehicles(vehicles);
    }
}

/// @brief It Prints all the cars in a deque to the terminal. Does not modify the deque
/// @param vehicles These vehicles will be printed not modified
void print_vehicles(const deque<Car> &vehicles){
    // Better option allows us to make the print function constant
    if(vehicles.empty()) {cout << "\t Empty" << endl;}

    for(Car vehicle: vehicles){
        cout << '\t';
        vehicle.print();
    }
}
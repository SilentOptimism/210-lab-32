#include <iostream>
#include <chrono>
#include <deque>
#include "Car-1.h"

using namespace std;
using namespace chrono;

void printVehicles();

deque<Car> vehicles; // The queue storing all of our vehicles
int timeOperations = 0;

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    cout << "Initial queue:" << endl;

    // Sets up our 2 initial vehicles in the line
    vehicles.push_back(Car());
    vehicles.back().print();
    vehicles.push_back(Car());
    vehicles.back().print();

    // Starts of our timers
    time_point start = high_resolution_clock::now();
    time_point now = high_resolution_clock::now();

    // Keeps running through out the loop until the lane is empty
    while(!vehicles.empty()){
        now = high_resolution_clock::now(); // gets up to date time
        milliseconds duration = duration_cast<milliseconds>(now-start); // Gets up to date duration since last time based operation

        // Checks if 1 second has pased since the last operation
        if(duration.count() > 1000){
            // Iterates how many time op's there have been
            cout << "Time " << timeOperations+1 << " Operation: ";

            int event = rand() % 100 + 1; // Determines whether a car will leave or join the line

            // 45% chance a car joins the lane
            if(event <= 45){
                // Adds a car to the back of the lane
                vehicles.push_back(Car());
                cout << "Joined lane: ";
                vehicles.back().print(); // Prints the recently added car

                // Prints the all the vehicles in the lane
                cout << "Queue:" << endl;
                printVehicles();
            }
            // 55% chance a car pays the toll leaving the lane
            else {
                // Removes a car from the front of the lane
                cout << "Car paid: ";
                vehicles.front().print(); // Prints the car before its removed
                vehicles.pop_front();

                // Prints the all the vehicles in the lane
                cout << "Queue:" << endl;
                printVehicles();
            }

            start = high_resolution_clock::now(); // Resets the duration timer
            timeOperations++; // Iterates how many time operations have occured
        }
    }

    return 0;
}

/// @brief Prints all the vehicles in our deque with '\t' before all descriptions. If the dequeue is empty prints empty
void printVehicles(){
    // Our iterators to go through our dequeue
    deque<Car>::iterator begin = vehicles.begin();
    deque<Car>::iterator end = vehicles.end();

    // Checks if our dequeue is empty
    if(begin == end) {cout << "\tEmpty" << endl;}

    while(begin != end){
        cout << "\t";
        begin->print();
        begin++;
    }

}
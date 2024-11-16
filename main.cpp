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

            //
            if(event <= 45){
                vehicles.push_back(Car());
                cout << "Joined lane: ";
                vehicles.back().print();

                // Prints the Queue
                cout << "Queue:" << endl;
                printVehicles();
            }
            else {
                cout << "Car paid: ";
                vehicles.front().print();
                vehicles.pop_front();
                cout << "Queue:" << endl;
                printVehicles();
            }

            start = high_resolution_clock::now();
            timeOperations++;
        }
    }

    return 0;
}

void printVehicles(){
    deque<Car>::iterator begin = vehicles.begin();
    deque<Car>::iterator end = vehicles.end();

    if(begin == end){
        cout << "\tEmpty" << endl;
    }

    while(begin != end){
        cout << "\t";
        begin->print();
        begin++;
    }

}
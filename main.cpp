#include <iostream>
#include <chrono>
#include <deque>
#include "Car-1.h"

using namespace std;
using namespace chrono;

deque<Car> vehicles;
int timeOperations = 0;

int main(int argc, char const *argv[])
{
    srand(time(NULL));



    cout << "Initial queue:" << endl;

    vehicles.push_back(Car());
    vehicles.back().print();

    vehicles.push_back(Car());
    vehicles.back().print();

    time_point start = high_resolution_clock::now();
    time_point now = high_resolution_clock::now();

    while(true){
        now = high_resolution_clock::now();
        milliseconds duration = duration_cast<milliseconds>(now-start);

        if(duration.count() > 1000){
            cout << "Time " << timeOperations+1 << " Operation: ";

            int event = rand() % 100 + 1;

            if(event <= 45){
                cout << "Joined the line";

            }
            else {
                cout << "Payed their toll";

            }

            start = high_resolution_clock::now();
            timeOperations++;
        }
    }

    return 0;
}

#include <iostream>
#include <chrono>
#include "Car-1.h"

using namespace std;
using namespace chrono;

int main(int argc, char const *argv[])
{

    time_point start = high_resolution_clock::now();
    time_point now = high_resolution_clock::now();

    cout << "Initial queue:" << endl;

    while(true){
        now = high_resolution_clock::now();
        milliseconds duration = duration_cast<milliseconds>(now-start);

        if(duration.count() % 1000 == 0){
            cout << duration.count() << endl;
        }
        


    }
    return 0;
}

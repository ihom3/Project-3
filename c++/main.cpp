//
//  main.cpp
//  Project3
//
//  Created by Ian Blasko on 12/3/22.
//

#include <iostream>
#include "DataSet.hpp"
#include <algorithm>
#include <chrono>
using namespace std::chrono;

vector<string> consumptionTypes() {
    return { "Commercial Coal",
        "Commercial Distillate Fuel Oil",
        "Commercial Geothermal",
        "Commercial Hydropower",
        "Commercial Kerosene",
        "Commercial Petroleum",
        "Commercial Natural Gas",
        "Commercial Solar",
        "Commercial Wind",
        "Commercial Wood",
        "Electric Power Coal",
        "Electric Power Distillate Fuel Oil",
        "Electric Power Natural Gas",
        "Electric Power Wood",
        "Industrial Coal",
        "Industrial Distillate Fuel Oil",
        "Industrial Geothermal",
        "Industrial Hydropower",
        "Industrial Kerosene",
        "Industrial Petroleum",
        "Industrial Natural Gas",
        "Industrial Other Petroleum Products",
        "Industrial Solar",
        "Industrial Wind",
        "Industrial Wood",
        "Refinery Coal",
        "Refinery Distillate Fuel",
        "Refinery Natural Gas",
        "Residential Coal",
        "Residential Distillate Fuel Oil",
        "Residential Geothermal",
        "Residential Kerosene",
        "Residential Petroleum",
        "Residential Natural Gas",
        "Residential Wood"};
}
void printExamples(DataSet& d) {
    vector<vector<pair<string,int>>> print = {
        d.getConsumptionTypes("Florida", 1960),
        d.getStates("Industrial Coal", 1961),
        d.getYears("Florida", "Industrial Coal")
    };
    for(auto i: print) {
        for(auto j : i)
            cout << j.first << ": " << j.second << endl;
        cout << endl;
    }
}
// NOTE: Main is only provided as an example. When converting this project to Web Assembly, 
// an instance of the DataSet class is created in JavaScript like in main below. Therefore,
// none of the code from main.cpp is compiled into WebAssembly and it is purely for testing the DataSet class
int main(int argc, const char * argv[]) {
    DataSet d("energy.csv", consumptionTypes());
    printExamples(d);
    
    //get vector pair for given inputs, ex. consumption types/corresponding values for FLorida in 1960
    vector<pair<string, int>> Florida1960 = d.getConsumptionTypes("Florida", 1960);

    //example of using sorting algorithm
    d.quickSort(Florida1960, 0, Florida1960.size() -1);
    //Florida1960 should now be sorted with quick sort
    return 0;
}


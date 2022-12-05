//
//  DataSet.hpp
//  Project3Resumed
//
//  Created by Ian Blasko on 12/3/22.
//

#ifndef DataSet_hpp
#define DataSet_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include "State.hpp"

using namespace std;

class DataSet {
    map<string, State> states;
    vector<string> consumptionTypes;
    void removeQuotes(string& s);
public:
    DataSet(string filename, vector<string> consumptionTypes);
    vector<pair<string, int>> getConsumptionTypes(string state_, int year_);
    vector<pair<string, int>> getStates(string consumptionType_, int year_);
    vector<pair<string, int>> getYears(string state_, string consumptionType_);
    
};

#endif /* DataSet_hpp */

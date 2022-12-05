//
//  DataSet.cpp
//  Project3Resumed
//
//  Created by Ian Blasko on 12/3/22.
//

#include "DataSet.hpp"



void DataSet::removeQuotes(string& s) {
    s.erase(remove(s.begin(), s.end(), '\"' ), s.end());
};

DataSet::DataSet(string filename, vector<string> consumptionNames) : consumptionTypes(consumptionNames) {
    ifstream infile(filename);
    string lineFromFile;
    getline(infile, lineFromFile);
    while(getline(infile, lineFromFile)) {
        string name;
        string year;
        istringstream stream(lineFromFile);
        getline(stream, name, ',');
        getline(stream, year, ',');
        removeQuotes(name);
        removeQuotes(year);
        string data;
        getline(stream, data, ',');
        vector<pair<string, int>> tempValues;
        for(unsigned int i = 0; i < 35; i++) {
            getline(stream, data, ',');
            removeQuotes(data);
            tempValues.push_back(pair<string, int>(consumptionTypes[i], stoi(data)));
        }
        if(states.contains(name)) states[name].consumption[stoi(year)] = tempValues;
        else {
            State tempState;
            tempState.consumption[stoi(year)] = tempValues;
            states[name] = tempState;
        }
    }
};

vector<pair<string, int>> DataSet::getConsumptionTypes(string state_, int year_) {
    return states[state_].consumption[year_];
};

vector<pair<string, int>> DataSet::getStates(string consumptionType_, int year_) {
    vector<pair<string, int>> tempStates;
    for(auto i: states){
        pair<string, int> tempPair;
        tempPair.first = i.first;
        int index = 0;
        auto it = find(consumptionTypes.begin(), consumptionTypes.end(), consumptionType_);
        if (it != consumptionTypes.end())
            index = it - consumptionTypes.begin();
        
        tempPair.second = i.second.consumption[year_][index].second;
        tempStates.push_back(tempPair);
    }
    return tempStates;
};

vector<pair<string, int>> DataSet::getYears(string state_, string consumptionType_) {
    vector<pair<string, int>> tempYearValues;
    for(auto i: states[state_].consumption) {
        pair<string, int> tempPair;
        tempPair.first = to_string(i.first);
        for(auto j: i.second) {
            if(j.first == consumptionType_) {
                tempPair.second = j.second;
                break;
            }
        }
        tempYearValues.push_back(tempPair);
    }
    return tempYearValues;
};

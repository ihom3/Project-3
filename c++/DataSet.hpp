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
#include <algorithm>
#include <tuple>
#include "State.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;

class DataSet {
    map<string, State> states;
    vector<string> consumptionTypes;
    void merge(vector<pair<string, int>>& list, int left, int mid, int right);
    int partition(vector<pair<string, int>>& list, int low, int high);
    void removeQuotes(string& s);
public:
    DataSet(string filename, vector<string> consumptionTypes);
    vector<pair<string, int>> getConsumptionTypes(string state_, int year_);
    vector<pair<string, int>> getStates(string consumptionType_, int year_);
    vector<pair<string, int>> getYears(const string state_, const string consumptionType_);
    vector<string> GetStateList();
    vector<int> GetYearList();
    void mergeSort(vector<pair<string, int>>& list, int left, int right);
    void quickSort(vector<pair<string, int>>& list, int low, int high);
};


#endif /* DataSet_hpp */

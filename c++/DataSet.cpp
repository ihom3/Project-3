//
//  DataSet.cpp
//  Project3
//
//  Created by Ian Blasko on 12/3/22.
//

#include "DataSet.hpp"
#include "emscripten/bind.h"

using namespace emscripten;

using namespace std::chrono;
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
        if (states.find(name) != states.end()) states[name].consumption[stoi(year)] = tempValues;
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
        ptrdiff_t index = distance(consumptionTypes.begin(), find(consumptionTypes.begin(), consumptionTypes.end(), consumptionType_));
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
vector<string> DataSet::GetStateList() {
    vector<string> stateNames;
    for(auto i: states)
    stateNames.push_back(i.first);
    return stateNames;
}
vector<int> DataSet::GetYearList() {
    vector<int> years;
    for(auto i: states) {
        for(auto j : i.second.consumption)
            years.push_back(j.first);
        break;
        }
    return years;
}
void DataSet::mergeSort(vector<pair<string, int>>& list, int left, int right) {
     if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(list, left, mid);
		mergeSort(list, mid + 1, right);
		// Merge the sorted subarrays
		merge(list, left, mid, right);
	}
}
void DataSet::merge(vector<pair<string, int>>& list, int left, int mid, int right) {
	// Create X ← arr[left..mid] & Y ← arr[mid+1..right]
	int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<pair<string, int>> X, Y;

	for (int i = 0; i < n1; i++)
		X.push_back(list[left + i]);

	for (int j = 0; j < n2; j++)
		Y.push_back(list[(mid + 1 + j)]);

	// Merge the arrays X and Y into arr
	int i, j, k;
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (X[i].second <= Y[j].second) {
			list[k] = X[i];
			i++;
		}
		else {
			list[k] = Y[j];
			j++;
		}
		k++;

	}
	// When we run out of elementsin either X or Y append the remaining elements
	while (i < n1) {
		list[k] = X[i];
		i++;
		k++;
	}
	while (j < n2) {
		list[k] = Y[j];
		j++;
		k++;
	}
}
void DataSet::quickSort(vector<pair<string, int>>& list, int low, int high) {
   if (low < high) {
		int pivot = partition(list, low, high);
        quickSort(list, low, pivot - 1);
		quickSort(list, pivot + 1, high);
	}
}

int DataSet::partition(vector<pair<string, int>>& list, int low, int high) {
    	// Select the pivot element
    
	int pivot = list[low].second;
	int up = low, down = high;

	while (up < down) {
		for (int j = up; j < high; j++) {
			if (list[up].second > pivot)
				break;
			up++;
		}
		for (int j = high; j > low; j--) {
			if (list[down].second < pivot)
				break;
			down--;
		}
		if (up < down)
			swap(list[up], list[down]);
	}
	swap(list[low], list[down]);
	return down;
}
EMSCRIPTEN_BINDINGS (c) {
    register_vector<string>("StringVector");
    register_vector<int>("IntVector");
    register_vector<pair<string, int>>("PairVector");
    value_array<pair<string, int>>("Pair")
    .element(&pair<string, int>::first)
    .element(&pair<string, int>::second);
    class_<DataSet>("DataSet")
    .constructor<string, vector<string>>()
    .function("getConsumptionTypes", &DataSet::getConsumptionTypes)
    .function("getStates", &DataSet::getStates)
    .function("getYears", &DataSet::getYears)
    .function("GetYearList", &DataSet::GetYearList)
    .function("GetStateList", &DataSet::GetStateList)
    .function("mergeSort", &DataSet::mergeSort)
    .function("quickSort", &DataSet::quickSort);
}
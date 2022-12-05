//
//  SortingAlgorithms.hpp
//  Project3Resumed
//
//  Created by Ian Blasko on 12/5/22.
//

#ifndef SortingAlgorithms_hpp
#define SortingAlgorithms_hpp

#include <stdio.h>

#include <string>
#include <vector>

using namespace std;

namespace SortingAlgorithms {
    void mergeSort(vector<pair<string, int>>& original);
    void quickSort(vector<pair<string, int>>& original);
};

#endif /* SortingAlgorithms_hpp */

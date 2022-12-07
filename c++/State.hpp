//
//  State.hpp
//  Project3
//
//  Created by Ian Blasko on 12/3/22.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct State {
    State() {};
    map<int, vector<pair<string, int>>> consumption;
};

#endif /* State_hpp */

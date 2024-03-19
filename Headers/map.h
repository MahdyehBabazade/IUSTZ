#pragma once
#include "../Headers/encounter.h"
#include <iostream>
#include <string>

using namespace std;

class Map{
private:
    int Floor;
    string ShowMap;
    vector<int> Path1;
    vector<int> Path2;
    vector<int> Path3;
    vector<int> Path4;
    vector<vector<Encounter*>> GenerateEncounter;
public:
    string getMap();
    Map(int floor,string map,vector<int> path1, vector<int> path2, vector<int> path3 ,vector<int> path4,vector<vector<Encounter*>> generateEncounter);
};
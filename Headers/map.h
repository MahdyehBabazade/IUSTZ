#pragma once
#include "../Headers/encounter.h"
#include <iostream>
#include <string>

using namespace std;

class Map{
private:
    int Floor;
    pair<int , int> CurrentNode;
    vector<int> PassedNodes;
    vector<int> Path1;
    vector<int> Path2;
    vector<int> Path3;
    vector<int> Path4;
    vector<int> Path5;
    vector<vector<string>> GenerateEncounter;
public:
    Map(int floor,vector<int> path1, vector<int> path2, vector<int> path3 ,vector<int> path4,
    vector<int> Path5 , vector<vector<string>> generateEncounter);
    string ShowMap();
    int getFloor();
    pair<int , int> getCurrentNode();
    void setCurrentNode(pair<int , int> CurrentNode);
    vector<int> getPassedNodes();
    void addPassedNodes(int Node);
    vector<bool> PossibleWays();
    void move();
};
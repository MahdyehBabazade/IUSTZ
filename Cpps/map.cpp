#include "../Headers/map.h"
#include <iostream>

vector<int> PathFinding1();

vector<int> PathFinding2(vector<int> path1);

vector<int> PathFinding3(vector<int> path1,vector<int> path2);

vector<int> PathFinding4(vector<int> path1,vector<int> path2,vector<int>path3);

string Showmap(vector<int> path1, vector<int> path2, vector<int> path3 ,vector<int> path4,vector<vector<Encounter*>> generateEncounter);

Map::Map(int floor,string map,vector<int> path1, vector<int> path2, vector<int> path3 ,vector<int> path4 ,vector<vector<Encounter*>> generateEncounter)
: Floor(floor),ShowMap(map), Path1(path1), Path2(path2), Path3(path3) ,Path4(path4) ,GenerateEncounter(generateEncounter){}

string Map::getMap() { return ShowMap;}
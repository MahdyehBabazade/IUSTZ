#include "../Headers/map.h"
#include <iostream>
#include <typeinfo>
#include <random>
#include <algorythm>

int Index_Weighted_Random(vector<int> weights){
    random_device rd;
    default_random_engine gen(rd());
    discrete_distribution<> dist(weights.begin(),weights.end());
    return dist(gen);
}

/*vector<int> Shuffle(vector<int> vec){ 
    random_device rd;
    default_random_engine abs(rd());
    shuffle(vec.begin(), vec.end(), abs);
    return vec;
}*/

vector<int> PathFinding1(){
    vector<int> path={0,0,0,0,0,0,0,0,0,0};
    path[0]=rand()%6;
    for(int i=1;i<10;i++){
        if(path[i-1]==0){
            vector<int> nexthome={path[i-1],path[i-1]+1};
            random_device rd;
            default_random_engine abs(rd());
            shuffle(nexthome.begin(), nexthome.end(), abs);
            path[i]=nexthome[0];
        }
        else if(path[i-1]==5){
            vector<int> nexthome={path[i-1],path[i-1]-1};
            random_device rd;
            default_random_engine abs(rd());
            shuffle(nexthome.begin(), nexthome.end(), abs);
            path[i]=nexthome[0];
        }
        else{
            vector<int> nexthome={path[i-1],path[i-1]+1,path[i-1]-1};
            random_device rd;
            default_random_engine abs(rd());
            shuffle(nexthome.begin(), nexthome.end(), abs);
            path[i]=nexthome[0];
        }
    }
    return path;
}

vector<int> PathFinding2(vector<int> path1){
    vector<int> path={0,0,0,0,0,0,0,0,0,0};
    path[0]=rand()%6;
    for(int i=1;i<10;i++){
        if(path[i-1]==0){
            if((path1[i-1]==1)&&(path1[i]==0)){
                path[i]=0;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else if(path[i-1]==5){
            if((path1[i-1]==4)&&(path1[i]==5)){
                path[i]=5;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else{
            if((path1[i-1]==path[i-1]+1)&&(path1[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            if((path1[i-1]==path[i-1]-1)&&(path1[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]+1,path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
    }
    return path;
}

vector<int> PathFinding3(vector<int> path1,vector<int> path2){
    vector<int> path={0,0,0,0,0,0,0,0,0,0};
    path[0]=rand()% 6;
    for(int i=1;i<10;i++){
        if(path[i-1]==0){
            if((path1[i-1]==1&& path1[i]==0)||(path2[i-1]==1&&path2[i]==0)){
                path[i]=0;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        if(path[i-1]==5){
            if((path1[i-1]==4 && path1[i]==5)||(path2[i-1]==4 &&path2[i]==5)){
                path[i]=5;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else{
            if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1] && path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])){
                path[i]==path[i-1];
            }
            else if((path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            ||(path1[i-1]==path[i-1]+1 && path2[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else if((path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            || (path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else{
                vector<int> nexthome={ path[i-1], path[i-1]+1, path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
    }
    return path;
}

vector<int> PathFinding4(vector<int> path1,vector<int> path2,vector<int>path3);

vector<vector<Encounter*>> generateEncounters(vector<int> path1 , vector<int> path2 , vector<int> path3 , vector<int> path4){
    vector<vector<Encounter*>> Encounters;
    vector<vector<int>> VisitedNodes;
    for(int i = 0; i < 10; i++){
        VisitedNodes.push_back({});
        VisitedNodes[i].push_back(path1[i]);
        if(path2[i] != path1[i])
            VisitedNodes[i].push_back(path2[i]);
        if(path3[i] != path1[i] && path2[i] != path3[i])
            VisitedNodes[i].push_back(path3[i]);
        if(path4[i] != path3[i] && path4[i] != path1[i] && path2[i] != path4[i])
            VisitedNodes[i].push_back(path4[i]);
    }
    for(int i = 0; i < 10 ; i++){
        vector<Encounter*> encounters2 = {};
        Encounters.push_back(encounters2);
        for(int j = 0; j < 6; i++){
            Encounters[i].push_back(nullptr);
        }
        if(i == 0){
            for(int j = 0; j < VisitedNodes[0].size();j++){
                Encounters[i][VisitedNodes[0][j]] = new Fight; // Encounter generation to be included
            }
        }
        else if(i < 3){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {45 , 22 , 5};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(Fight))
                        weights[0] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(RandomEncounter))
                        weights[1] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(Shop))
                        weights[2] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(typeid(*Encounters[i][inRow[m]]) == typeid(Fight))
                        weights[0] = 0;
                    else if(typeid(*Encounters[i][inRow[m]]) == typeid(RandomEncounter))
                        weights[1] = 0;
                    else if(typeid(*Encounters[i][inRow[m]]) == typeid(Shop))
                        weights[2] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] = new Fight; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] = new RandomEncounter; //RandomEncounter Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] = new Shop; //Shop Constructor to be included
                }
            }
        }
        else if(i < 8){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {45 , 22 , 16 , 12 , 5};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(Fight))
                        weights[0] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(RandomEncounter))
                        weights[1] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(MiniBoss))
                        weights[2] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(Hospital))
                        weights[3] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(Shop))
                        weights[4] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(typeid(*Encounters[i][inRow[m]]) == typeid(Fight))
                        weights[0] = 0;
                    else if(typeid(*Encounters[i][inRow[m]]) == typeid(RandomEncounter))
                        weights[1] = 0;
                    else if(typeid(*Encounters[i - 1][inRow[m]]) == typeid(MiniBoss))
                        weights[2] = 0;
                    else if(typeid(*Encounters[i - 1][inRow[m]]) == typeid(Hospital))
                        weights[3] = 0;
                    else if(typeid(*Encounters[i][inRow[m]]) == typeid(Shop))
                        weights[4] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] = new Fight; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] = new RandomEncounter; //RandomEncounter Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] = new MiniBoss; //MiniBoss Constructor to be included
                }
                if(enc == 3){
                    Encounters[i][VisitedNodes[i][j]] = new Hospital; //Hospital Constructor to be included
                }
                if(enc == 4){
                    Encounters[i][VisitedNodes[i][j]] = new Shop; //Shop Constructor to be included
                }
            }
        }
        else if(i == 8){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {45 , 22 , 16 , 5};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(Fight))
                        weights[0] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(RandomEncounter))
                        weights[1] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(MiniBoss))
                        weights[2] = 0;
                    else if(typeid(*Encounters[i - 1][Visits[m]]) == typeid(Shop))
                        weights[3] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(typeid(*Encounters[i][inRow[m]]) == typeid(Fight))
                        weights[0] = 0;
                    else if(typeid(*Encounters[i][inRow[m]]) == typeid(RandomEncounter))
                        weights[1] = 0;
                    else if(typeid(*Encounters[i - 1][inRow[m]]) == typeid(MiniBoss))
                        weights[2] = 0;
                    else if(typeid(*Encounters[i][inRow[m]]) == typeid(Shop))
                        weights[3] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] = new Fight; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] = new RandomEncounter; //RandomEncounter Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] = new MiniBoss; //MiniBoss Constructor to be included
                }
                if(enc == 3){
                    Encounters[i][VisitedNodes[i][j]] = new Hospital; //Hospital Constructor to be included
                }
            }
        }
        else{
            for(int j = 0; j < VisitedNodes[i].size(); j++){
                Encounters[i][VisitedNodes[i][j]] = new Hospital; // Hospital Constructor to be included
            }
        }
    }
}

string Showmap(vector<int> path1, vector<int> path2, vector<int> path3 ,vector<int> path4,vector<vector<Encounter*>> generateEncounter);

Map::Map(int floor,string map,vector<int> path1, vector<int> path2, vector<int> path3 ,vector<int> path4 ,vector<vector<Encounter*>> generateEncounter)
: Floor(floor),ShowMap(map), Path1(path1), Path2(path2), Path3(path3) ,Path4(path4) ,GenerateEncounter(generateEncounter){}

string Map::getMap() { return ShowMap;}
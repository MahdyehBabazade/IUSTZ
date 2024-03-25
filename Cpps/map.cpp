#include "../Headers/map.h"
#include <iostream>
#include <typeinfo>
#include <random>
#include <algorithm>
#include <iomanip>

const string yellow("\033[1;33m");
const string red("\033[0;31m");
const string reset("\033[0m");
const string cyan("\033[0;36m");
const string green("\033[1;32m");

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
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    path[0]=rand() %6;
    for(int i=1;i<15;i++){
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
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    do{
        path[0]=rand() %6;
    }while(path[0]==path1[0]);
    for(int i=1;i<15;i++){
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
            else if((path1[i-1]==path[i-1]-1)&&(path1[i]==path[i-1])){
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
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    do{
        path[0]=rand() %6;
    }while(path[0]==path1[0] || path[0]==path2[0]);
    path[0]=rand()% 6;
    for(int i=1;i<15;i++){
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
        else if(path[i-1]==5){
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

vector<int> PathFinding4(vector<int> path1,vector<int> path2,vector<int>path3){
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    path[0]=rand() %6;
    for(int i=1; i<15 ;i++){
        if(path[i-1]==0){
            if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            || (path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])){
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
            if((path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            || (path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])){
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
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            ||(path2[i-1]==path[i-1]-1 && path2[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path2[i-1]==path[i-1]+1 && path2[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])){
                path[i]=path[i-1];
            }
            else if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1]) 
            || (path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else if((path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]-1 && path2[i]==path[i-1]) 
            || (path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1,path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
    }
    return path;
}

vector<int> PathFinding5(vector<int> path1,vector<int> path2,vector<int>path3 , vector<int> path4){
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    path[0]=rand() %6;
    for(int i=1; i<15 ;i++){
        if(path[i-1]==0){
            if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            || (path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            || (path4[i-1]==path[i-1]+1 && path4[i]==path[i-1])){
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
            if((path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            || (path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            || (path4[i-1]==path[i-1]-1 && path4[i]==path[i-1])){
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
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            ||(path2[i-1]==path[i-1]-1 && path2[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path2[i-1]==path[i-1]+1 && path2[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path4[i-1]==path[i-1]+1 && path4[i]==path[i-1])
            ||(path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path4[i-1]==path[i-1]-1 && path4[i]==path[i-1])
            ||(path2[i-1]==path[i-1]-1 && path2[i]==path[i-1] && path4[i-1]==path[i-1]+1 && path4[i]==path[i-1])
            ||(path2[i-1]==path[i-1]+1 && path2[i]==path[i-1] && path4[i-1]==path[i-1]-1 && path4[i]==path[i-1])
            ||(path4[i-1]==path[i-1]-1 && path4[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path4[i-1]==path[i-1]+1 && path4[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])){
                path[i]=path[i-1];
            }
            else if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1]) 
            || (path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            || (path4[i-1]==path[i-1]+1 && path4[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else if((path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]-1 && path2[i]==path[i-1]) 
            || (path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            || (path4[i-1]==path[i-1]-1 && path4[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1,path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
    }
    return path;
}

vector<vector<string>> generateEncounters(vector<int> path1 , vector<int> path2 , vector<int> path3 , 
vector<int> path4 , vector<int> path5){
    vector<vector<string>> Encounters = {};
    vector<vector<int>> VisitedNodes = {};
    for(int i = 0; i < 15; i++){
        VisitedNodes.push_back({});
        VisitedNodes[i].push_back(path1[i]);
        if(path2[i] != path1[i])
            VisitedNodes[i].push_back(path2[i]);
        if(path3[i] != path1[i] && path2[i] != path3[i])
            VisitedNodes[i].push_back(path3[i]);
        if(path4[i] != path3[i] && path4[i] != path1[i] && path2[i] != path4[i])
            VisitedNodes[i].push_back(path4[i]);
        if(path5[i] != path3[i] && path5[i] != path1[i] && path2[i] != path5[i] && path5[i] != path4[i])
            VisitedNodes[i].push_back(path5[i]);
    }
    for(int i = 0; i < 15 ; i++){
        Encounters.push_back({});
        for(int j = 0; j < 6; j++){
            Encounters[i].push_back("");
        }
        if(i == 0){
            for(int j = 0; j < VisitedNodes[0].size();j++){
                Encounters[i][VisitedNodes[0][j]] = "Fight"; // Encounter generation to be included
            }
        }
        else if(i < 5){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {40 , 25 , 9};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                if(path5[i] == VisitedNodes[i][j])
                    Visits.push_back(path5[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(path5[i - 1] == Visits[m] && path5[i] != VisitedNodes[i][j])
                        inRow.push_back(path5[i]);
                    if(Encounters[i - 1][Visits[m]] == "Shop")
                        weights[2] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(Encounters[i][inRow[m]] == "Fight")
                        weights[0] = 0;
                    else if(Encounters[i][inRow[m]] == "Random")
                        weights[1] = 0;
                    else if(Encounters[i][inRow[m]] == "Shop")
                        weights[2] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] = "Fight"; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] = "Random"; //Random Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] = "Shop"; //Shop Constructor to be included
                }
            }
        }
        else if(i < 13){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {40 , 25 , 16 , 10 , 9};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                if(path5[i] == VisitedNodes[i][j])
                    Visits.push_back(path5[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(path5[i - 1] == Visits[m] && path5[i] != VisitedNodes[i][j])
                        inRow.push_back(path5[i]);
                    if(Encounters[i - 1][Visits[m]] == "MiniBoss")
                        weights[2] = 0;
                    else if(Encounters[i - 1][Visits[m]] == "Hospital")
                        weights[3] = 0;
                    else if(Encounters[i - 1][Visits[m]] == "Shop")
                        weights[4] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(Encounters[i][inRow[m]] == "Fight")
                        weights[0] = 0;
                    else if(Encounters[i][inRow[m]] == "Random")
                        weights[1] = 0;
                    else if(Encounters[i][inRow[m]] == "MiniBoss")
                        weights[2] = 0;
                    else if(Encounters[i][inRow[m]] == "Hospital")
                        weights[3] = 0;
                    else if(Encounters[i][inRow[m]] == "Shop")
                        weights[4] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] =  "Fight"; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] =  "Random"; //Random Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] =  "MiniBoss"; //MiniBoss Constructor to be included
                }
                if(enc == 3){
                    Encounters[i][VisitedNodes[i][j]] =  "Hospital"; //Hospital Constructor to be included
                }
                if(enc == 4){
                    Encounters[i][VisitedNodes[i][j]] =  "Shop"; //Shop Constructor to be included
                }
            }
        }
        else if(i == 13){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {40 , 25 , 16 , 9};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                if(path5[i] == VisitedNodes[i][j])
                    Visits.push_back(path5[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(path5[i - 1] == Visits[m] && path5[i] != VisitedNodes[i][j])
                        inRow.push_back(path5[i]);
                    if(Encounters[i - 1][Visits[m]] == "MiniBoss")
                        weights[2] = 0;
                    else if(Encounters[i - 1][Visits[m]] == "Shop")
                        weights[3] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(Encounters[i][inRow[m]] == "Fight")
                        weights[0] = 0;
                    else if(Encounters[i][inRow[m]] == "Random")
                        weights[1] = 0;
                    else if(Encounters[i - 1][inRow[m]] == "MiniBoss")
                        weights[2] = 0;
                    else if(Encounters[i][inRow[m]] == "Shop")
                        weights[3] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] = "Fight"; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] = "Random"; //Random Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] = "MiniBoss"; //MiniBoss Constructor to be included
                }
                if(enc == 3){
                    Encounters[i][VisitedNodes[i][j]] = "Shop"; //Hospital Constructor to be included
                }
            }
        }
        else{
            for(int j = 0; j < VisitedNodes[i].size(); j++){
                Encounters[i][VisitedNodes[i][j]] = "Hospital"; // Hospital Constructor to be included
            }
        }
    }
    return Encounters;
}

string Map :: ShowMap(){
    string map;
    for(int i=0; i<14 ;i++){
        vector<bool> slash={false,false,false,false,false};
        vector<bool> backSlash={false,false,false,false,false};
        vector<bool> line={false,false,false,false,false,false};
        if(Path1[i+1]==Path1[i]+1 )
            backSlash[Path1[i]]=true;
        else if(Path1[i+1]==Path1[i]-1 )
            slash[Path1[i]-1]=true;
        else if(Path1[i+1]==Path1[i] )  
            line[Path1[i]]=true;
        if(Path2[i+1]==Path2[i]+1 )
            backSlash[Path2[i]]=true;
        else if(Path2[i+1]==Path2[i]-1 )
            slash[Path2[i]-1]=true;
        else if(Path2[i+1]==Path2[i])
            line[Path2[i]]=true;
        if(Path3[i+1]==Path3[i]+1)
            backSlash[Path3[i]]=true;
        else if(Path3[i+1]==Path3[i]-1)
            slash[Path3[i]-1]=true;
        else if(Path3[i+1]==Path3[i])
            line[Path3[i]]=true;
        if(Path4[i+1]==Path4[i]+1)
            backSlash[Path4[i]]=true;
        else if(Path4[i+1]==Path4[i]-1)
            slash[Path4[i]-1]=true;
        else if(Path4[i+1]==Path4[i])
            line[Path4[i]]=true;
        if(Path5[i+1]==Path5[i]+1)
            backSlash[Path5[i]]=true;
        else if(Path5[i+1]==Path5[i]-1)
            slash[Path5[i]-1]=true;
        else if(Path5[i+1]==Path5[i])
            line[Path5[i]]=true;
        for(int z=0;z<3;z++){
            for(int j=0;j<6;j++){
                if(i < PassedNodes.size())
                    if(PassedNodes[i] == j)
                        map+=red;
                if(i == CurrentNode.first && j == CurrentNode.second)
                    map+=yellow;
                if(GenerateEncounter[i][j]=="")
                    map+="   ";
                else if(GenerateEncounter[i][j]=="Hospital")
                    map+="+++";
                else if(GenerateEncounter[i][j]=="Shop")
                    map+="$$$";
                else if(GenerateEncounter[i][j]=="Random")
                    map+="???";
                else if(GenerateEncounter[i][j]=="Fight"){
                    if(z==0)
                        map+=" - ";
                    if(z==1)
                        map+="/ \\";
                    if(z==2)
                        map+=" | ";
                }
                else if(GenerateEncounter[i][j]=="MiniBoss"){
                    if(z==0)
                        map+="*_*";
                    if(z==1)
                        map+=" | ";
                    if(z==2)
                        map+="/ \\";                    
                }
                map += reset + "   ";
            }
            
            map+="\n";
        }
        map+="\n";
        
        for(int j=0;j<5 ;j++){
            for(int z=0;z<5;z++){
                if(z==0)
                    map+=" ";
                if(line[z]==true){
                    if(i < PassedNodes.size() - 1 && z == PassedNodes[i] && z==PassedNodes[i + 1])
                        map += green;
                    map+="|";
                    map+=reset;
                }
                else
                    map+=" ";
                if(slash[z]==true){
                    if(i < PassedNodes.size() - 1 && z == PassedNodes[i] - 1 && z == PassedNodes[i + 1])
                        map += green;
                    for(int k = 0; k < 4 - j; k++){
                        map+=" ";
                    }
                    map+="/";
                    for(int k = 0; k < j; k++){
                        map+=" ";
                    }
                }
                else if(backSlash[z]==true){
                    if(i < PassedNodes.size() - 1 && z == PassedNodes[i] && z ==PassedNodes[i + 1] - 1)
                        map += green;
                    for(int k = 0; k < j; k++){
                        map+=" ";
                    }
                    map+="\\";
                    for(int k = 0; k < 4 - j; k++){
                        map+=" ";
                    }
                }
                else
                    map+="     ";
                map += reset;
            }
            if(line[5] == true){
                if(i < PassedNodes.size() - 1 && 5 == PassedNodes[i] && 5 == PassedNodes[i + 1])
                    map += green;
                map+="|";
                map+=reset;
            }
            map+=" \n";
        }
        map+="\n";
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<6;j++){
            if(PassedNodes.size() < 15)
                if(PassedNodes[14] == j)
                    map += green;
            if(CurrentNode.first==14 && CurrentNode.second == j)
                map += yellow;
            if(GenerateEncounter[14][j] =="")
                map+="   ";
            else
                map+="+++";
            map+= reset + "   ";
        }
        map+="\n";            
    }
    return map;
}

Map::Map(int floor , vector<int> path1 , vector<int> path2 , vector<int> path3 , vector<int> path4 ,
vector<int> path5 , vector<vector<string>> generateEncounter)
: Floor(floor), Path1(path1), Path2(path2), Path3(path3) ,Path4(path4) , Path5(path5) , GenerateEncounter(generateEncounter){
    this->PassedNodes={};
    this->CurrentNode=make_pair(-1,-1);
}

pair<int , int> Map :: getCurrentNode(){return CurrentNode;}

void Map::setCurrentNode(pair<int,int> CurrentNode){this->CurrentNode = CurrentNode;}

vector<int> Map::getPassedNodes(){return PassedNodes;}

void Map::addPassedNodes(int Node){PassedNodes.push_back(Node);}

vector<bool> Map::PossibleWays(){
    vector<bool> possibleways = {false , false , false};
    if(Path1[CurrentNode.first] == CurrentNode.second){
        if(Path1[CurrentNode.first+1] == CurrentNode.second - 1)
            possibleways[0] = true;
        if(Path1[CurrentNode.first+1] == CurrentNode.second)
            possibleways[1] = true;
        if(Path1[CurrentNode.first+1] == CurrentNode.second + 1)
            possibleways[2] = true;
    }
    if(Path2[CurrentNode.first] == CurrentNode.second){
        if(Path2[CurrentNode.first+1] == CurrentNode.second - 1)
            possibleways[0] = true;
        if(Path2[CurrentNode.first+1] == CurrentNode.second)
            possibleways[1] = true;
        if(Path2[CurrentNode.first+1] == CurrentNode.second + 1)
            possibleways[2] = true;
    }
    if(Path3[CurrentNode.first] == CurrentNode.second){
        if(Path3[CurrentNode.first+1] == CurrentNode.second - 1)
            possibleways[0] = true;
        if(Path3[CurrentNode.first+1] == CurrentNode.second)
            possibleways[1] = true;
        if(Path3[CurrentNode.first+1] == CurrentNode.second + 1)
            possibleways[2] = true;
    }
    if(Path4[CurrentNode.first] == CurrentNode.second){
        if(Path4[CurrentNode.first+1] == CurrentNode.second - 1)
            possibleways[0] = true;
        if(Path4[CurrentNode.first+1] == CurrentNode.second)
            possibleways[1] = true;
        if(Path4[CurrentNode.first+1] == CurrentNode.second + 1)
            possibleways[2] = true;
    }
    if(Path5[CurrentNode.first] == CurrentNode.second){
        if(Path5[CurrentNode.first+1] == CurrentNode.second - 1)
            possibleways[0] = true;
        if(Path5[CurrentNode.first+1] == CurrentNode.second)
            possibleways[1] = true;
        if(Path5[CurrentNode.first+1] == CurrentNode.second + 1)
            possibleways[2] = true;
    }
    return possibleways;
}
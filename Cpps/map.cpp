#include "../Headers/map.h"
#include <iostream>
#include <typeinfo>
#include <random>
#include <algorithm>

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
    path[0]=rand() %6;
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
    do{
        path[0]=rand() %6;
    }while(path[0]==path1[0]);
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
    vector<int> path={0,0,0,0,0,0,0,0,0,0};
    do{
        path[0]=rand() %6;
    }while(path[0]==path1[0] || path[0]==path2[0]);
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
    vector<int> path={0,0,0,0,0,0,0,0,0,0};
    path[0]=rand() %6;
    for(int i=1; i<10 ;i++){
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

vector<vector<string>> generateEncounters(vector<int> path1 , vector<int> path2 , vector<int> path3 , vector<int> path4){
    vector<vector<string>> Encounters = {};
    vector<vector<int>> VisitedNodes = {};
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
        Encounters.push_back({});
        for(int j = 0; j < 6; j++){
            Encounters[i].push_back("");
        }
        if(i == 0){
            for(int j = 0; j < VisitedNodes[0].size();j++){
                Encounters[i][VisitedNodes[0][j]] = "Fight"; // Encounter generation to be included
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
                    Encounters[i][VisitedNodes[i][j]] = "Hospital"; //Hospital Constructor to be included
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


string Showmap(vector<int> path1, vector<int> path2, vector<int> path3 ,vector<int> path4,vector<vector<string>> generateEncounter){
    string map;
    for(int i=0; i<9 ;i++){
        vector<bool> slash={false,false,false,false,false};
        vector<bool> backSlash={false,false,false,false,false};
        vector<bool> line={false,false,false,false,false,false};
        if(path1[i+1]==path1[i]+1 )
            backSlash[path1[i]]=true;
        else if(path1[i+1]==path1[i]-1 )
            slash[path1[i]-1]=true;
        else if(path1[i+1]==path1[i] )  
            line[path1[i]]=true;
        if(path2[i+1]==path2[i]+1 )
            backSlash[path2[i]]=true;
        else if(path2[i+1]==path2[i]-1 )
            slash[path2[i]-1]=true;
        else if(path2[i+1]==path2[i])
            line[path2[i]]=true;
        if(path3[i+1]==path3[i]+1)
            backSlash[path3[i]]=true;
        else if(path3[i+1]==path3[i]-1)
            slash[path3[i]-1]=true;
        else if(path3[i+1]==path3[i])
            line[path3[i]]=true;
        if(path4[i+1]==path4[i]+1)
            backSlash[path4[i]]=true;
        else if(path4[i+1]==path4[i]-1)
            slash[path4[i]-1]=true;
        else if(path4[i+1]==path4[i])
            line[path4[i]]=true;
        for(int z=0;z<3;z++){
            for(int j=0;j<6;j++){
                if(generateEncounter[i][j]=="")
                    map+="   ";
                if(generateEncounter[i][j]=="Hospital")
                    map+="+++";
                if(generateEncounter[i][j]=="Shop")
                    map+="$$$";
                if(generateEncounter[i][j]=="Random")
                    map+="???";
                if(generateEncounter[i][j]=="Fight"){
                    if(z==0)
                        map+=" - ";
                    if(z==1)
                        map+="/ \\";
                    if(z==2)
                        map+=" | ";
                }
                if(generateEncounter[i][j]=="MiniBoss"){
                    if(z==0)
                        map+="*_*";
                    if(z==1)
                        map+=" | ";
                    if(z==2)
                        map+="/ \\";                    
                }
                map += "   ";
            }
            map+="\n";
        }
        
        for(int j=0;j<4 ;j++){
            for(int z=0;z<5;z++){
                if(z==0)
                    map+=" ";
                if(line[z]==true)
                    map+="|";
                else
                    map+=" ";
                if(slash[z]==true){
                    for(int k = 0; k < 3 - j; k++){
                        map+=" ";
                    }
                    map+="/";
                    for(int k = 0; k < j + 1; k++){
                        map+=" ";
                    }
                }
                else if(backSlash[z]==true){
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
            }
            if(line[5] == true)
                map+="|";
            map+=" \n";
        }     
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<6;j++){
            if(generateEncounter[9][j]=="")
                map+="   ";
            if(generateEncounter[9][j]=="Hospital")
                map+="+++";
            if(generateEncounter[9][j]=="Shop")
                map+="$$$";
            if(generateEncounter[9][j]=="Random")
               map+="???";
            if(generateEncounter[9][j]=="Fight"){
                if(i==0)
                    map+=" - ";
                if(i==1)
                    map+="/ \\";
                if(i==2)
                    map+=" | ";
            }
            if(generateEncounter[9][j]=="MiniBoss"){
                if(i==0)
                    map+="*_*";
                if(i==1)
                    map+=" | ";
                if(i==2)
                    map+="/ \\";                    
            }
            map+="   ";
        }
        map+="\n";            
    }
    return map;
}

Map::Map(int floor,string map,vector<int> path1, vector<int> path2, vector<int> path3 ,vector<int> path4 ,vector<vector<Encounter*>> generateEncounter)
: Floor(floor),ShowMap(map), Path1(path1), Path2(path2), Path3(path3) ,Path4(path4) ,GenerateEncounter(generateEncounter){}

string Map::getMap() { return ShowMap;}

pair<int , int> Map :: getCurrentNode(){return CurrentNode;}

void Map::setCurrentNode(pair<int,int> CurrentNode){this->CurrentNode = CurrentNode;}

int main(){
    vector<int> a , b , c , d;
    a = PathFinding1();
    b = PathFinding2(a);
    c = PathFinding3(a , b);
    d = PathFinding4(a , b , c);
    vector<vector<string>> e = generateEncounters(a , b , c , d);
    cout << Showmap(a , b , c , d , e);
}
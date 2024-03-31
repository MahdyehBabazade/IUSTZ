#include "../Headers/map.h"
#include "functions.cpp"
#include <iostream>
#include <typeinfo>
#include <random>
#include <algorithm>
#include <iomanip>
#include <conio.h>

using namespace std;

const string yellow("\033[1;33m");
const string red("\033[0;31m");
const string reset("\033[0m");
const string cyan("\033[0;36m");
const string green("\033[1;32m");
const string magenta("\033[0;35m");
const string grey("\033[90m");

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
                        map+=cyan;
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
                    if(i < PassedNodes.size() - 1 && !PassedNodes.empty())
                        if(z == PassedNodes[i] && z==PassedNodes[i + 1])
                            map += green;
                    map+="|";
                    map+=reset;
                }
                else
                    map+=" ";
                if(slash[z]==true){
                    if(i < PassedNodes.size() - 1 && !PassedNodes.empty())
                        if(z == PassedNodes[i] - 1 && z == PassedNodes[i + 1])
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
                    if(i < PassedNodes.size() - 1 && !PassedNodes.empty())
                        if(z == PassedNodes[i] && z ==PassedNodes[i + 1] - 1)
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
                if(i < PassedNodes.size() - 1 && !PassedNodes.empty() && 5 == PassedNodes[i] && 5 == PassedNodes[i + 1])
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
            if(PassedNodes.size() == 15)
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
    this->PassedNodes = {};
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

void Map::move(){
    string map = ShowMap();
    if(CurrentNode.first == -1){
        string sizecounter = "";
        vector<int> Options;
        for(int i = 0; i < 6; i++){
            if(GenerateEncounter[0][i] != "")
                Options.push_back(i);
        }
        int m = 0;
        bool breaker = true;
        while(breaker){
            clearScreen();
            cout << map << "\n\n\n";
            sizecounter = "";
            for(int i = 0; i < 6; i++){
                if(GenerateEncounter[0][i] == "")
                    sizecounter += grey;
                if(i == Options[m % Options.size()])
                    sizecounter += green;
                sizecounter += to_string(i + 1) + ". " + GenerateEncounter[0][i] + "\n";
                sizecounter += reset;
            }
            sizecounter += "Move between options with W & S and choose the option with Enter.\n";
            cout << sizecounter;
            char key = _getch();
            switch (key)
            {
            case 'w':
                m--;
                break;
            case 's':
                m++;
                break;
            case '\r':
                breaker = false;
                break;
            default:
                break;
            }
            for(int i = 0; i < 7; i++)
                cout << "\r\b";
        }
        CurrentNode = make_pair(0 , Options[m % Options.size()]);
        addPassedNodes(Options[m % Options.size()]);
    }
    else{
        vector<bool> possibleways = PossibleWays();
        vector<int> Options;
        for(int i = 0; i < 3; i++){
            if(possibleways[i])
                Options.push_back(i);
        }
        int m = 0;
        bool breaker = true;
        string sizecounter;
        while(breaker){
            clearScreen();
            cout << map << "\n\n\n";
            sizecounter = "";
            for(int i = 0; i < 3; i++){
                if(i == Options[m % Options.size()])
                    sizecounter += green;
                if(!possibleways[i])
                    sizecounter += grey;
                if(i == 0)
                    sizecounter += to_string(i + 1) + ". Bottom Left\n";
                else if(i == 1)
                    sizecounter += to_string(i + 1) + ". Straight Bottom\n";
                else
                    sizecounter += to_string(i + 1) + ". Bottom Right\n";
                sizecounter += reset;
            }
            sizecounter += "Move between options with W & S and choose the option with Enter.\n";
            cout << sizecounter;
            char key = _getch();
            switch (key)
            {
            case 'w':
                m--;
                break;
            case 's':
                m++;
                break;
            case '\r':
                breaker = false;
                break;
            default:
                break;
            }
        }
        CurrentNode = make_pair(CurrentNode.first + 1 , CurrentNode.second + Options[(m % Options.size())] - 1);
        addPassedNodes(CurrentNode.second);
    }
}
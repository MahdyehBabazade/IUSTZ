#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <conio.h>

using namespace std;

const string yellow("\033[1;33m");
const string red("\033[0;31m");
const string reset("\033[0m");
const string cyan("\033[0;36m");
const string green("\033[1;32m");
const string magenta("\033[0;35m");
const string grey("\033[90m");


int random_num(int min,int max){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(min,max); 

    return dist(rng);
}

template <typename T>
vector<T> ShuffleVec(vector<T> vec){ // Shuffles a vector
    random_device rd;
    default_random_engine abs(rd());
    shuffle(vec.begin(), vec.end(), abs);   
    return vec;
}

int Index_Weighted_Random(vector<int> weights){
    random_device rd;
    default_random_engine gen(rd());
    discrete_distribution<> dist(weights.begin(),weights.end());
    return dist(gen);
}

vector<int> Shuffle(vector<int> vec){ 
    random_device rd;
    default_random_engine abs(rd());
    shuffle(vec.begin(), vec.end(), abs);
    return vec;
}

void clearScreen(){
    system("cls");
}


int Choose(vector<string> Options){
    int option =0;
    int vecSize = Options.size();
    while(true){
        clearScreen();
        for(int i = 0; i < Options.size() ; i++){
            if(i == option){
                cout << green <<Options[i] << reset << endl;
            }else {
                cout << Options[i] << endl;
            }
        }
        char input = _getch();
        switch(tolower(input)){
            case 'w':
            {
                option --;
                option %= vecSize;
                continue;
            }
            case 's':
            {
                option++;
                option %=vecSize;
                continue;
            }
            case '\r':
                break;
            
            default:
                continue;
                
        }
        break;
    }
    return option % Options.size() +1;
}


int Choose(vector<string> Descriptions ,vector<string> Options){
    int option =0;
    int vecSize = Options.size();
    while(true){
        clearScreen();
        for(int i = 0; i < Descriptions.size() ; i++){
            cout << Descriptions[i];
        }
        for(int i = 0; i < Options.size() ; i++){
            if(i == option % Options.size()){
                cout << green <<Options[i] << reset << endl;
            }else {
                cout << Options[i] << endl;
            }
        }
        char input = _getch();
        switch(tolower(input)){
            case 'w':
            {
                option --;
                option %= vecSize;
                continue;
            }
            case 's':
            {
                option++;
                option %=vecSize;
                continue;
            }
            case '\r':
                break;
            
            default:
                continue;
                
        }
        break;
    }
    return option % Options.size() + 1;
}

int Choose(vector<string> Options,vector<bool> Chooseable){
    int option =find(Chooseable.begin(),Chooseable.end(),true) - Chooseable.begin();
    int vecSize = Options.size();
    while(true){
        system("cls");
        cout << "option : " << option << endl;
        for(int i = 0; i < Options.size() ; i++){
            if(i == option){
                cout << green <<Options[i] << reset << endl;
            }else if(Chooseable[i]){
                cout << Options[i] << endl;
            }else {
                cout << red << Options[i] << reset << endl;
            }
        }
        char input = _getch();
        switch(tolower(input)){
            case 'w':
            {
                int index = find(Chooseable.rbegin() + vecSize - option,Chooseable.rend(),true) - Chooseable.rbegin();
                if(index == vecSize){
                    index = find(Chooseable.rbegin() ,Chooseable.rend(),true) - Chooseable.rbegin();
                }
                index = vecSize - index - 1;
                
                option = index;
                
                continue;
            }
            case 's':
            {
                int index = find(Chooseable.begin() + option + 1,Chooseable.end(),true) - Chooseable.begin();
                if(index == vecSize){
                    index = find(Chooseable.begin() ,Chooseable.end(),true) - Chooseable.begin();
                }
                option = index;
                continue;
            }
            case '\r':
                break;
            
            default:
                continue;
                
        }
        break;
    }
    return option % Options.size() + 1;
}
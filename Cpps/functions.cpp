#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <stdlib.h>

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

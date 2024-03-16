#include "Headers/creature.h"
#include "Headers/items.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

vector<string> ShuffleVec(vector<string> vec){
    random_device rd;
    default_random_engine rng(rd());
    shuffle(vec.begin(), vec.end(), rng);
    return vec;
}

void check_attack(){
    Weapon* weapon = new Snipe("sniper",5,20,20, 4, 1 , 2 , 1);
    Consumable*  consumable = new Consumable("hiHPPoition" , "HPPotion" , 1 , 10 , 30); 
    vector<pair<Item*,int>> items = {make_pair(consumable , 1),make_pair(weapon,1)};
    vector<pair<Weapon* , int>> Weapons = {make_pair(weapon,1)};
    vector<pair<Consumable* , int>> Consumables = {make_pair(consumable , 1)};
    vector<Equipment*> Equipments;
    Player* player = new Player("O",100,100,1.0,100,0,100,40,50,items,Weapons,Consumables , Equipments);
    HumanEnemy* enemy = new HumanEnemy("enemy1",30,30,0.0,0,items,Weapons,Equipments,Consumables);
}

int main(){
    
}
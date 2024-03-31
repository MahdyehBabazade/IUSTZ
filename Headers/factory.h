#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"
#include "../Headers/map.h"
using namespace std;

class ShopFactory{
private:
    Map* map;
    Shop* shop;
public:
    ShopFactory() = default;
    ShopFactory(Map* map, Shop* shop);
    void Generate(Shop* shop);
};

class EnemyFactory{

private:
    Map* map;
    int Difficulty;
    string ZombieNameset();
    string HumanEnemyNameset();
    double Armorset();
    int MaxHPset();
    vector<pair<Weapon*,int>> Weaponset(int type);
    vector<pair<Consumable*,int>> Consumableset(int type);
    vector<pair<Item*,int>> Itemset(vector<pair<Weapon* , int>> Weapons , vector<pair<Consumable* , int>> Consumables);
    HumanEnemy* HumanEnemyMaker();
    Zombie* ZombieMaker();

public:
    EnemyFactory(Map* map);
    void setDifficulty(int Difficulty);
    vector<Character*> FightEnemy();
    vector<Character*> MiniBossEnemy();
    vector<Character*> BossEnemy();
};

class MapFactory{

private:
    int Floor;
    vector<int> PathFinding1();
    vector<int> PathFinding2(vector<int> path1);
    vector<int> PathFinding3(vector<int> path1 , vector<int> path2);
    vector<int> PathFinding4(vector<int> path1 , vector<int> path2 , vector<int> path3);
    vector<int> PathFinding5(vector<int> path1 , vector<int> path2 , vector<int> path3 , vector<int> path4);
    vector<vector<string>> generateEncounters(vector<int> path1 , vector<int> path2 , vector<int> path3 , 
    vector<int> path4 , vector<int> path5);
public:
    MapFactory(int floor);
    Map* GenerateMap();
};
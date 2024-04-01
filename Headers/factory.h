#pragma once
#include "../Cpps/creature.cpp"
#include "../Cpps/map.cpp"
#include "../Cpps/encounter.cpp"
using namespace std;

class ShopFactory{
private:
    Map* map;
    Player* player;
    Shopkeeper* shopkeeper;
public:
    ShopFactory(Map* map, Player* player, Shopkeeper* shopkeeper);
    Shop* Generate();
};

class EnemyFactory{

private:
    Map* map;
    int Difficulty;
    void setDifficulty(int Difficulty);
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

class FightFactory{
private:
    Player* player;
    Map* map;
    
public:
    FightFactory(Player* player, Map* map);
    Fight* GenerateNormalFight();
    Fight* GenerateMiniBoss();
    Fight* GenerateBoss();
};
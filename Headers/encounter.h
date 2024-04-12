#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"
#include "../Headers/MVC.h"
#include "../Headers/map.h"
#include <iostream>
using namespace std;

class Encounter{
protected:
    string Story;
public: 
    string getStory();
};

class Shop : public Encounter{
private:    
    Player* player;
    vector<Weapon*> weapons;
    vector<Consumable*> consumables;
    vector<Equipment*> equipments;
    Shopkeeper* shopkeeper;
    
    bool WantsToQuit;
    int BaseUpgradePrice;
    int UpgradesLeft;
    
public:
    // Constructor
    Shop(Player* player, vector<Weapon*> weapons, vector<Consumable*> consumables, vector<Equipment*> equipments, Shopkeeper* shopkeeper);
    
    // Getters
    vector<Weapon*> getWeapons();
    vector<Consumable*> getConsumables();
    vector<Equipment*> getEquipments();
    
    // Setters
    void setWeapons(vector<Weapon*> weapons);
    void setConsumables(vector<Consumable*> consumables);
    void setEquipments(vector<Equipment*> equipments);
    
    // Other Functions
    void Upgrade(Weapon* Weapon , string dialogue);
    void Sell(Item* item , int choice); // The shopkeeper sells sth to the player
    void Buy(Item* item); // The shopkeeper buys sth from the player
    void Menu(); 
    string getStat();
    
    void addItem(Item* item);
    void removeItem(Item* item , int choice);
};

class Hospital : public Encounter{
    
private:
    Player* player;
    Medic* medic;
    int MaxHpIncreasePrice;
    int FullHealPrice;
    int HalfHealPrice;
    bool HasHealed;
public:
    Hospital(Player* player,Medic* medic);
    
    void MaxHpIncrease();
    void FullHeal();
    void HalfHeal();
    void Menu();
    string getStat();
};

class RandomEncounter : public Encounter{
private:
    Player* player;
public:
    RandomEncounter(Player* player);
    void Menu(Player* player, Map* map);
};

class Fight : public Encounter{
private:
    Player* player;
    //vector<Character*> players;
    int type; // 0 for normal fight, 1 for miniboss, 2 for boss
    vector<Character*> enemies;
    vector<Item*> items;
    int droppedCoins;
    vector<Relic*> relics;

    Control::FightControl* fightControl;
    
    
public:
    Fight(Player* player, int type, vector<Character*> enemies, vector<Item*> items, int droppedCoins, vector<Relic*> relics);
    
    void start();
};
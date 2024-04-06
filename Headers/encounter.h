#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"
#include "../Headers/MVC.h"
#include <iostream>
using namespace std;

class Encounter{
protected:
    string Story;
public: 
    Encounter(string Story);
    Encounter()=default;
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
    Shop() = default;
    
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
    void Sell(Item* item); // The shopkeeper sells sth to the player
    void Buy(Item* item); // The shopkeeper buys sth from the player
    void Menu(); 
    
    void addItem(Item* item);
    void removeItem(Item* item);
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
    Hospital()=default;
    
    void MaxHpIncrease();
    void FullHeal();
    void HalfHeal();
    
    void Menu();
};

class RandomEncounter : public Encounter{
private:
    Player* player;
public:
    RandomEncounter() = default;
    RandomEncounter(Player* player);
    void Menu();
};

class Fight : public Encounter{
private:
    Player* player;
    //vector<Character*> players;
    int type; // 0 for normal fight, 1 for miniboss, 2 for boss
    vector<Character*> enemies;
    vector<Item*> items;
    int droppedCoins;
    
    Control::FightControl* fightControl;
    
    
public:
    Fight()=default;
    Fight(Player* player, int type, vector<Character*> enemies, vector<Item*> items,int droppedCoins);
    
    void start();
};

class MiniBoss : public Encounter{
public:
    MiniBoss()=default;
};
class Boss : public Encounter{
public:
    Boss() = default;
    
};
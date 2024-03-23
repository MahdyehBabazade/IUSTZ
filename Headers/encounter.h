#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"
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
    Shop(Player* player, vector<Weapon*> weapons, vector<Consumable*> consumables, vector<Equipment*> equipments, Shopkeeper* shopkeeper,string Story);
    Shop() = default;
    // Getters
    vector<Weapon*> getWeapons();
    vector<Consumable*> getConsumables();
    vector<Equipment*> getEquipments();
    
    // Setters
    // void setWeapons(vector<Weapon*> weapons);
    // void setConsumables(vector<Consumable*> consumables);
    // void setEquipments(vector<Equipment*> equipments);
    
    // Other Functions
    void Upgrade(Weapon* Weapon);
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
    Hospital(Player* player,Medic* medic,int MaxHpIncresePrice,int FullHealPrice,int HalfHealPrice,string Story);
    Hospital()=default;
    
    void MaxHpIncrease();
    void FullHeal();
    void HalfHeal();
    
    void Menu();
};

class RandomEncounter : public Encounter{
public:
    RandomEncounter() = default;
};

class Fight : public Encounter{
public:
    Fight()=default;
};

class MiniBoss : public Encounter{
public:
    MiniBoss()=default;
};
class Boss : public Encounter{
public:
    Boss() = default;
    
};
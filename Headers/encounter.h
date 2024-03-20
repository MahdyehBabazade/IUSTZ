#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"
#include <iostream>
using namespace std;

class Encounter{
private:
    string Story;
public: 
    Encounter(string Story);
    
    string getStory();
    
};

class Shop : Encounter{
private:    
    Player* player;
    vector<Weapon*> weapons;
    vector<Consumable*> consumables;
    vector<Equipment*> equipments;
    Shopkeeper* shopkeeper;
    
    bool WantsToQuit;
    
public:
    // Constructor
    Shop(Player* player, vector<Weapon*> weapons, vector<Consumable*> consumables, vector<Equipment*> equipments, Shopkeeper* shopkeeper,string Story);

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
};

class Hospital : Encounter{
    
private:
    Player* player;
    Medic* medic;
    int MaxHpIncreasePrice;
    int FullHealPrice;
    int HalfHealPrice;
    bool HasHealed;
public:
    Hospital(Player* player,Medic* medic,int MaxHpIncresePrice,int FullHealPrice,int HalfHealPrice,string Story);
    
    void MaxHpIncrease();
    void FullHeal();
    void HalfHeal();
    
    void Menu();
};

class RandomEncounter : Encounter{
    
};

class Fight : Encounter{
    
};

class MiniBoss : Encounter{
    
};
class Boss : Encounter{
    
};
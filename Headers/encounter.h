#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"

class Shop{
private:    
    Player* player;
    vector<Weapon*> Weapons;
    vector<Consumable*> Consumables;
    vector<Equipment*> Equipments;
    ShopKeeper* shopKeeper;
    
public:
    Shop(Player* player,vector<Weapon*> weapons,vector<Consumable*> consumables,vector<Equipment*> equipments,ShopKeeper* shopKeeper);
    /*
    vector<Weapon*> getWeapons();
    vector<Consumable*> getConsumables();
    vector<Equipment*> getEquipments();
    
    void setWeapons();
    void setConsumables();
    void setEquipments();
    */
};

class Hospital{
private:
    Player* player;
    Medic* medic;
public:
    Hospital(Player* player,Medic* medic);
    
};

class Random{
    
};

class Fight{
    
};





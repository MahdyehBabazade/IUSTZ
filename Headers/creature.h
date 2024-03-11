#pragma once
#include "../Headers/items.h"
#include <vector>
#include <string>
using namespace std;

// explainings to be included
class Character{

private:
    int HP;
    int MaxHP;
    double Armor;
    int Shield;

protected:
    vector<pair<Item* , int>> Items;
    vector<pair<Weapon* , int>> Weapons;
    vector<Equipment*> Equipments;

public:
    Character(int HP , int MaxHP , int Armor , int Shield , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipments);
    int getHP();
    void setHP(int HP);
    int getMaxHP();
    void setMaxHP(int MaxHP);
    int getArmor();
    void setArmor(double Armor);
    int getShield();
    void setShield(int Shield);
    void takeDamage(int damageTaken);
    vector<pair<Item* , int>> getItems();
    vector<pair<Weapon* , int>> getWeapons();
    vector<Equipment*> getEquipments();

    void Attack(vector<Character*> &characters, vector<Weapon*> &weapons);

};

class Player : public Character{

private:
    string Name;
    int BackPackCapacity;
    int BackPackWeight;
    int Energy;
    int MaxEnergy;
    int Coin;
    vector<Relic*> Relics;
    vector<pair<Consumable* , int>> Consumables;

public:
    Player(string Name, int HP, int MaxHP, double Armor, int BackPackCapacity , int BackPackWeight , int MaxEnergy
    , int Coin , int Shield , vector<pair<Item* , int>> Items , vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipments); // Equipments to be included
    ~Player();
    // void Attack(Enemy* enemy); // can't fully develop yet?!
    string getName();
    void setBackPackCapacity(int BackPackCapacity);
    int getBackPackCapacity();
    void setBackPackWeight(int BackPackWeight);
    int getBackPackWeight();
    void setEnergy(int Energy);
    int getEnergy();
    void setMaxEnergy(int MaxEnergy);
    int getMaxEnergy();
    void addCoin(int CoinToBeAdded);
    void removeCoin(int CoinToBeAdded);
    int getCoin();
    void addItem(Item* item);
    void removeItem(Item* item);
    vector<Relic*> getRelic();
    void addRelic(Relic* relic); // relic usage to be add
    void addWeapon(Weapon* Weapon);
    void removeWeapon(Weapon* Weapon);
    void addEquipment(Equipment* Equipment);
    void removeEquipment(Equipment* Equipment);
    vector<pair<Consumable* , int>> getConsumables();
    void addConsumable(Consumable* Consumable);
    void removeConsumable(Consumable* Consumable);
};

class HumanEnemy: public Character{

private:
    string Name;
    vector<pair<Consumable* , int>> Consumables;
    void RajazKhani();

public:
    string getName();
    HumanEnemy(int HP , int MaxHP , double Armor , string Name, int Shield , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipments , vector<pair<Consumable* , int>> Consumables); //items to add?!
    // void Attack(Player player) override; // can't fully develop yet?! // rajazKhani to be include
    // consume function to be added
    // void Consume(Consumable* consumable); // to be included
    void removeItem(Item* item); // when we throw a throwable item and consumables
    ~HumanEnemy();
};

class Zombie: public Character{

private:
    string Type;

public:
    string getType();
    // void Attack(Player player) override; // can't fully develop yet?!
    Zombie(int HP , int MaxHP , double Armor , string Type , int shield ,
    vector<pair<Item* , int>> Items , vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipment);
    ~Zombie();
    // random bullshit to be included
};

class Shopkeeper{

private:
    string Name;

public:
    Shopkeeper(string Name);
    string getName();
    void HiDialogue();
    void ByeDialogue();
    void SellDialogue(Item* item);
    void BuyDialogue(Item* item);
    void NoMoneyDialogue();
};

class Medic{

private:
    string Name;
    void HealDialogue();

public:
    Medic(string Name);
    string getName();
    void HiDialogue();
    void ByeDialogue();
    void NoMoneyDialogue();
    void Heal(Player player);
    void MaxHPIncrease(Player player);
};
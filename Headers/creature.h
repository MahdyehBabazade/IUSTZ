#pragma once
#include "../Headers/items.h"
#include <vector>
#include <string>
using namespace std;

// explainings to be included
class Character{
private:
    string Name;
    int HP;
    int MaxHP;
    double Armor;
    int Shield;
protected:
    vector<pair<Item* , int>> Items;
    vector<pair<Weapon* , int>> Weapons;
    vector<Equipment*> Equipments;
public:
    Character(string Name , int HP , int MaxHP , double Armor , int Shield , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon*,int>> Weapons);
    string getName();
    void setName(string Name);
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

    string getStat(); //to be deleted later
};

class Player : public Character{

private:
    int BackPackCapacity;
    int BackPackWeight;
    int Energy;
    int MaxEnergy;
    int Coin;
    vector<Relic*> Relics;
    vector<pair<Consumable* , int>> Consumables;
    void addWeapon(Weapon* Weapon);
    void removeWeapon(Weapon* Weapon);
    void addEquipment(Equipment* Equipment);
    void removeEquipment(Equipment* Equipment);
    void addConsumable(Consumable* Consumable);
    void removeConsumable(Consumable* Consumable);

public:
    Player(string Name, int HP, int MaxHP, double Armor, int BackPackCapacity , int BackPackWeight , int MaxEnergy
    , int Coin , int Shield , vector<pair<Item* , int>> Items , vector<pair<Weapon* , int>> Weapons ,
    vector<pair<Consumable* , int>> Consumables , vector<Equipment*> Equipments); // Equipments to be included
    ~Player();
    // void Attack(Enemy* enemy); // can't fully develop yet?!
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
    vector<Relic*> getRelic();
    void addRelic(Relic* relic); // relic usage to be add
    void addItem(Item* item);
    void removeItem(Item* item);
    vector<pair<Consumable* , int>> getConsumables();
    void Consume(Consumable* Consumable);
    Weapon* ChooseWeapon(vector<Weapon*> weapons); // to be deleted later (?)
    void Attack(vector<Character*> &characters, vector<Weapon*> &weapons);
};

class HumanEnemy: public Character{

private:
    vector<pair<Consumable* , int>> Consumables;
    void removeItem(Item* item); // when we throw a throwable item or consumables
    void RajazKhani();

public:
    HumanEnemy(string Name,int HP , int MaxHP , double Armor, int Shield , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipments , vector<pair<Consumable* , int>> Consumables); //items to add?!
    // void Attack(Player player) override; // can't fully develop yet?! // rajazKhani to be include
    void removeConsumable(Consumable* Consumable);
    void removeWeapon(Weapon* Weapon);
    void Consume(Consumable* consumable); // to be included
    ~HumanEnemy();
};

class Zombie: public Character{
public:
    // void Attack(Player player) override; // can't fully develop yet?!
    Zombie(string Name,int HP , int MaxHP , double Armor, int shield , vector<pair<Item* , int>> Items , 
    vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipment);
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
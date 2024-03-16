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
    
    // Constructor
    Character(string Name , int HP , int MaxHP , double Armor , int Shield , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon*,int>> Weapons);
    
    // getters
    string getName();
    int getHP();
    int getMaxHP();
    int getArmor();
    int getShield();
    vector<pair<Item* , int>> getItems(); 
    vector<pair<Weapon* , int>> getWeapons();
    vector<Equipment*> getEquipments();
    
    // setters
    void setName(string Name);
    void setHP(int HP);
    void setMaxHP(int MaxHP);
    void setArmor(double Armor);
    void setShield(int Shield);

    void takeDamage(int damageTaken); // reduces the hp of characters based on their Armor and Shield

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
    
    // Updates the list of specific types of Items based on what item is picked in a sorted manner
    void addWeapon(Weapon* Weapon);
    void removeWeapon(Weapon* Weapon);
    void addEquipment(Equipment* Equipment);
    void removeEquipment(Equipment* Equipment);
    void addConsumable(Consumable* Consumable);
    void removeConsumable(Consumable* Consumable);

public:
    // Constructor and Destructor
    Player(string Name, int HP, int MaxHP, double Armor, int BackPackCapacity , int BackPackWeight , int MaxEnergy
    , int Coin , int Shield , vector<pair<Item* , int>> Items , vector<pair<Weapon* , int>> Weapons ,
    vector<pair<Consumable* , int>> Consumables , vector<Equipment*> Equipments); // Equipments to be included
    ~Player();

    // getters
    int getBackPackCapacity();
    int getBackPackWeight();
    int getEnergy();
    int getMaxEnergy();
    int getCoin();
    vector<Relic*> getRelic();
    vector<pair<Consumable* , int>> getConsumables();
    
    // setters
    void setBackPackCapacity(int BackPackCapacity);
    void setBackPackWeight(int BackPackWeight);
    void setEnergy(int Energy);
    void setMaxEnergy(int MaxEnergy);

    // Updates the amount of Coins the player has
    void addCoin(int CoinToBeAdded);
    void removeCoin(int CoinToBeAdded);

    // Updates the list of Relics and their Aplications
    void addRelic(Relic* relic);

    // Updates the list of Items in a sorted manner
    void addItem(Item* item);
    void removeItem(Item* item);

    void Consume(Consumable* Consumable); // the function for when a Consumable is used
    Weapon* ChooseWeapon(); // to be deleted later (?)
    void Attack(vector<Character*> &characters , Weapon* weapon); // Attack function
};

class HumanEnemy: public Character{

private:
    vector<pair<Consumable* , int>> Consumables;
    
    // Updates the list of Specific types of Items after they are thrown or used
    void removeConsumable(Consumable* Consumable);
    void removeWeapon(Weapon* Weapon);
    
    // fun little Dialogues :)
    void RajazKhani();

public:
    
    // Constructor and Destructor
    HumanEnemy(string Name,int HP , int MaxHP , double Armor, int Shield , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipments , vector<pair<Consumable* , int>> Consumables); //items to add?!
    ~HumanEnemy();

    void Attack(vector<Character*> player , Weapon* weapon , int choice); // Attack function
    void Consume(Consumable* consumable); // When a Consumable is used
    void removeItem(Item* item); // when a throwable is thrown or a Consumable is used;
};

class Zombie: public Character{

public:
    // Constructor and Destructor
    Zombie(string Name,int HP , int MaxHP , double Armor, int shield , vector<pair<Item* , int>> Items , 
    vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipment);
    ~Zombie();

    void Attack(vector<Character*> &player , Punch* punch); // Attack function for zombie it can only attack with its Punch
};

class Shopkeeper{

private:
    string Name;

public:
    // Constructor
    Shopkeeper(string Name);

    string getName();
    // Dialogues
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
    // Constructor
    Medic(string Name);

    string getName();
    // Dialogues
    void HiDialogue();
    void ByeDialogue();
    void NoMoneyDialogue();

    void Heal(Player player);
    void MaxHPIncrease(Player player);
};
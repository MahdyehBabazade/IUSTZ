#pragma once
#include "../Headers/items.h"
#include <vector>
#include <string>
using namespace std;

// explainings to be included

class Player{

private:
    string Name;
    int HP;
    int MaxHP;
    double Armor;
    int BackPackCapacity;
    int BackPackWeight;
    int Energy;
    int Coin;
    int Shield;
    vector<pair<Item*, int>> Items;
    vector<Weapon*> weapons;
    vector<Relic*> Relics;

public:
    Player(string Name, int HP, int MaxHP, double Armor, int BackPackCapacity , int BackPackWeight , int Energy , int Coin , int Shield , vector<pair<Item* , int>> Items , vector<Relic*> Relics); // items to be included
    ~Player();
    // void Attack(Enemy* enemy); // can't fully develop yet?!
    void takeDamage(int damagetaken);
    string getName();
    void setHP(int HP);
    int getHP();
    void setMaxHP(int MaxHP);
    int getMaxHP();
    void setArmor(double Armor);
    int getArmor();
    void setBackPackCapacity(int BackPackCapacity);
    int getBackPackCapacity();
    void setBackPackWeight(int BackPackWeight);
    int getBackPackWeight();
    void setEnergy(int Energy);
    int getEnergy();
    void addCoin(int CoinToBeAdded);
    void removeCoin(int CoinToBeAdded);
    int getCoin();
    void setShield(int Shield);
    int getShield();
    vector<pair<Item* , int>> getItem();
    void addItem(Item* item);
    void removeItem(Item* item);
    vector<Relic*> getRelic();
    void addRelic(Relic* relic); // relic usage to be add
};

class Enemy{

private:
    int HP;
    int MaxHP;
    double Armor;
    Item* item;
    int Shield;

public:
    Enemy(int HP , int MaxHP , double Armor , Item* item , int Shield);
    // constructors to add?! (factory?!!!!!)
    virtual void Attack(Player player) = 0; // can't fully develop yet?!
    void takeDamage(int damagetaken);
    void setHP(int HP);
    int getHP();
    void setMaxHP(int MaxHP);
    int getMaxHP();
    void setArmor(double Armor);
    int getArmor();
    void setShield(int Shield);
    int getShield();
    
};

class HumanEnemy: public Enemy{

private:
    string Name;
    vector<Item*> items;
public:
    string getName();
    HumanEnemy(int HP , int MaxHP , double Armor , string Name, Item* item , int shield); //items to add?!
    void Attack(Player player) override; // can't fully develop yet?!
    // consume function to be added
    void Consume(Consumable* consumable);
    void removeItem(Item* item); // when we throw a throwable item
    // rajaz khani to be included
    void RajazKhani();
    string getStats(); // return Name/Type + (HP)
    ~HumanEnemy();
};

class Zombie: public Enemy{

private:
    string Type;

public:
    string getType();
    void Attack(Player player) override; // can't fully develop yet?!
    Zombie(int HP , int MaxHP , double Armor , string Type , Item* item , int shield); // items may be added
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
    void SellDialogue(Item* item); // item to be included
    void BuyDialogue(Item* item); // item to be included
    void NoMoneyDialogue();
};

class Medic{

private:
    string Name;
    void ByeDialogue();
    void HealDialogue();

public:
    Medic(string Name);
    string getName();
    void HiDialogue();
    void NoMoneyDialogue();
    void Heal(Player player);
    void MaxHPIncrease(Player player);
};
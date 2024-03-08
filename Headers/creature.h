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
    void removeItem(int index);
    vector<Relic*> getRelic();
    void addRelic(Relic* relic); // relic usage to be add
};

class Enemy{

private:
    int HP;
    int MaxHP;
    double Armor;
    // items to be included

public:
    Enemy(int HP , int MaxHP , double Armor);
    // constructors to add?! (factory?!!!!!)
    virtual void Attack(Player player) = 0; // can't fully develop yet?!
    void takeDamage(int damagetaken); // items should be included
    void setHP(int HP);
    int getHP();
    void setMaxHP(int MaxHP);
    int getMaxHP();
    void setArmor(double Armor);
    int getArmor();
};

class HumanEnemy: public Enemy{

private:
    string Name;
public:
    string getName();
    HumanEnemy(int HP , int MaxHP , double Armor , string Name); //items to add?!
    void Attack(Player player) override; // can't fully develop yet?!
    // consume function to be added
    // rajaz khani to be included
    ~HumanEnemy();
};

class Zombie: public Enemy{

private:
    string Type;

public:
    string getType();
    void Attack(Player player) override; // can't fully develop yet?!
    Zombie(int HP , int MaxHP , double Armor , string Type);
    ~Zombie(); //cout << "Aaauugh";
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
    void SellDialogue(); // item to be included
    void BuyDialogue(); // item to be included
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
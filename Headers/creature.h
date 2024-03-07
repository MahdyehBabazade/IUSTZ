#pragma once
#include <iostream>
using namespace std;


class Player{

private:
    string Name;
    int Hp;
    int MaxHp;
    int Armor;
    int BackPackCapacity;
    int Energy;
    int Coin;
    // items to be included

public:
    Player(string Name, int HP, int MaxHp, int Armor, int BackPackCapacity , int Energy , int Coin); // items to be included
    ~Player();
    void Attack(Enemy* enemy); // can't fully develop yet?!
    string getName();
    void setHp(int Hp);
    int getHp();
    void setMaxHp(int MaxHp);
    int getMaxHp();
    void setArmor(int Armor);
    int getArmor();
    void setBackPackCapacity(int BackPackCapacity);
    int getBackPackCapacity();
    void setEnergy(int Energy);
    int getEnergy();
    // add/remove items to be included
    // consume function to be added
};

class Enemy{

private:
    int Hp;
    int MaxHp;
    int Armor;
    // items to be included

public:
    // constructors to add?! (factory?!!!!!)
    virtual void Attack(Player player) = 0; // can't fully develop yet?!
    void Death();
    void setHp(int Hp);
    int getHp();
    void setMaxHp(int MaxHp);
    int getMaxHp();
    void setArmor(int Armor);
    int getArmor();
};

class HumanEnemy: public Enemy{

private:
    string Name;
public:
    string getName();
    HumanEnemy(int Hp , int MaxHp , int Armor , string Name); //items to add?!
    void Attack(Player player) override; // can't fully develop yet?!
    // consume function to be added
    // rajaz khani to be included
    ~HumanEnemy(); // cout << "I can't believe this is  how it ends";
};

class Zombie: public Enemy{

private:
    string Type;

public:
    string getType();
    void Attack(Player player) override; // can't fully develop yet?!
    Zombie(int Hp , int MaxHp , int Armor , string Type);
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
    void SellDialogue();
    void BuyDialogue();
    void NoMoneyDialogue();
};

class 
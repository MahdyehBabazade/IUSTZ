#pragma once
using namespace std;

// explainings to be included

class Player{

private:
    string Name;
    int HP;
    int MaxHP;
    int Armor;
    int BackPackCapacity;
    int Energy;
    int Coin;
    // items to be included

public:
    Player(string Name, int HP, int MaxHP, int Armor, int BackPackCapacity , int Energy , int Coin); // items to be included
    ~Player();
    void Attack(Enemy* enemy); // can't fully develop yet?!
    void takeDamage(int damagetaken); // items should be included
    string getName();
    void setHP(int HP);
    int getHP();
    void setMaxHP(int MaxHP);
    int getMaxHP();
    void setArmor(int Armor);
    int getArmor();
    void setBackPackCapacity(int BackPackCapacity);
    int getBackPackCapacity();
    void setEnergy(int Energy);
    int getEnergy();
    void addCoin(int coin);
    void removeCoin(int coin);
    int getCoin();
    // add/remove items to be included
    // consume function to be added
};

class Enemy{

private:
    int HP;
    int MaxHP;
    int Armor;
    // items to be included

public:
    // constructors to add?! (factory?!!!!!)
    virtual void Attack(Player player) = 0; // can't fully develop yet?!
    void takeDamage(); // items should be included
    void Death();
    void setHP(int HP);
    int getHP();
    void setMaxHP(int MaxHP);
    int getMaxHP();
    void setArmor(int Armor);
    int getArmor();
};

class HumanEnemy: public Enemy{

private:
    string Name;
public:
    string getName();
    HumanEnemy(int HP , int MaxHP , int Armor , string Name); //items to add?!
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
    Zombie(int HP , int MaxHP , int Armor , string Type);
    ~Zombie(); //cout << "Aaauugh";
    // random bullshit to be included
};

class Shopkeeper{

private:
    string Name;

public:
    Shopkeeper(string Name);
    ~Shopkeeper();
    string getName();
    void HiDialogue(Player player);
    void ByeDialogue(Player player);
    void SellDialogue(); // item to be included
    void BuyDialogue(); // item to be included
    void NoMoneyDialogue(Player player);
};

class Priest{

private:
    string Name;

public:
    Priest(string Name);
    ~Priest();
    string getName();
    void HiDialogue(Player player);
    void ByeDialogue(Player player);
    void HealDialogue(Player player);
    void MaxHPDialogue(Player player);
    void NoMoneyDialogue(Player player);
    void Heal(Player player);
    void MaxHP(Player player);
};
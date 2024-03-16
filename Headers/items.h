#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "../Headers/creature.h"
using namespace std;

class Item {
protected:
    string Name;
    int Capacity; // space it takes in the backpack
    int Price;
public:
    Item(string name, int capacity, int Price);
    void setCapacity(int capacity);
    void setPrice(int price);

    string getName();
    int getCapacity();
    int getPrice();

    bool operator==(Item a); // checks if the names are the same
    //virtual ~Item()=0; // default constructor

    virtual string getStat();
    Item();
};

//--------------------------------
class Weapon: public Item{
protected:
    int Damage;
    int EnergyNeeded;
public:
    Weapon(string name,int capacity,int damage,int price,int energyNeeded);
    virtual void Attack(vector<Character*> &characters); // takes an enemy and calls its TakeDamage function
    void setDamage(int damage);
    void setEnergyNeeded(int energy);
    int getDamage();
    int getEnergyNeeded();

    string getStat() override; // returns the properties
};

class Punch: public Weapon{
public:
    Punch(string name,int capacity,int damage,int price,int energyNeeded);
    Punch();
};

class Gun:public Weapon{
protected:
    int MaxAmmo;
    int Ammo;
    int ReloadEnergy;
public:
    void setAmmo(int ammo);
    int getAmmo();
    //void Attack(vector<Character*> &characters);
    int getReloadEnergy();
    void setReloadEnergy(int reloadEnergy);
    void Reload();
    Gun(string name,int capacity,int price,int damage,int energyNeeded,int ammo,int reloadEnergy);

    string getStat() override;
};

class Shotgun:public Gun{
private:
    int MinDamagePercent; // the least amount of damage it can deal based on the distance
public:
    int getMinDamagePercent();
    void setMinDamagePercent(int minDamagePercent);
    void Attack(vector<Character*> &characters) override; // checks the range and deals damage based on it
    Shotgun(string name,int capacity, int price ,int damage,int energyNeeded,int reloadEnergy,int ammo);

    string getStat() override;

    Shotgun();
};

class Snipe: public Gun{
public:
    void Attack(vector<Character*> &characters) override; // takes a character and attacks both the selected character and the one behind it
    Snipe(string name,int capacity, int price,int damage,int energyNeeded,int reloadEnergy,int ammo;
    Snipe();
};

class SMG: public Gun{
    SMG(string name,int capacity, int price ,int damage,int energyNeeded,int reloadEnergy,int ammo);
    SMG();
    void Attack(vector<Character*> &characters) override; // attacks every enemy
};

class Rifle: public Gun{
private:
    int MaxAttackAmount; // max amount of enemies it can attack
public:
    int getMaxAttackAmount();
    void setMaxAttackAmount(int maxAttackAmount);
    void Attack(vector<Character*> &characters) override; // attacks chooses a certain amount of enemies and the damage is divided between them
    Rifle(string name,int capacity, int price ,int damage,int energyNeeded,int reloadEnergy,int ammo);
    Rifle();
    string getStat() override;
};

class ColdWeapon: public Weapon{
private:
    int ThrowDamagePercent; // damage increase when it's thrown
public:
    int getThrowDamagePercent();
    void setThrowDamagePercent(int throwDamagePercent);
    void Throw(vector<Character*> &characters); //throws the coldWeapon and removes it from the items
    ColdWeapon(string name,int capacity,int price ,int damage,int energyNeeded);
    ColdWeapon();
};

class Throwable: public Weapon {
public:
    Throwable(string name,int capacity, int price,int damage,int energyNeeded);
};

class Grenade: public Throwable{
public:
    Grenade();
    Grenade(string name,int capacity, int price,int damage,int energyNeeded);
    void Attack(vector<Character*> &characters) override;
};

class BoomRang: public Throwable{
public:
    BoomRang();
    BoomRang(string name,int capacity, int price,int damage,int energyNeeded);
    void Attack(vector<Character*> &characters) override; // attacks all the characters twice
};

//--------------------------------
class Consumable: public Item{
private:
    int Amount; // how much it's going to increase
    string Type;
public:
    void setAmount(int amount);
    int getAmount();

    string getType();
    void setType(string type);
    Consumable();
    Consumable(string name,string type,int capacity,int price,int amount);
    string getStat() override;

};
//------------------------------
class Equipment: public Item{
protected:
    int Amount; // the percent
public:
    Equipment(string name,int capacity,int price,int amount);
    int getAmount();
    void setAmount(int amount);
};
class Vest: public Equipment{
public:
    Vest();
    Vest(string name,int capacity,int price,int amount);
};
class HeadGear: public Equipment{
public:
    HeadGear();
    HeadGear(string name,int capacity,int price,int amount);
};
class FootWear: public Equipment{
public:
    FootWear();
    FootWear(string name,int capacity,int price,int amount);
};
class Boot : public Equipment{
public:
    Boot();
    Boot(string name,int capacity,int price,int amount);
};
                                                                                                      
//------------------------------
class Relic: public Item {
private:
    int MaxHP; // how much percent of maxHP is being added
    int MaxEnergy; // how much percent of maxEnergy is being added
public:
    void setMaxHP(int MaxHP);
    void setMaxEnergy(int MaxEnergy);
    int getMaxEnergy();
    int getMaxHP();
    Relic();
    Relic(string name, int capacity, int price,int MaxHP,int maxEnergy); // remember capacity=0
    string getStat() override;
};
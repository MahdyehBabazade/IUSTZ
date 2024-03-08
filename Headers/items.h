#pragma once
#include <string>
class Item {
protected:
    string Name;
    int Capacity;
    int Price;
public:
    Item(string name, int capacity, int Price);
    void setCapacity(int capacity);
    void setPrice(int price);

    string getName();
    int getCapacity();
    int getPrice();
};

//--------------------------------
class Weapon: public Item{
protected:
    int Damage;
    int EnergyNeeded;
    int AttackRange;
public:
    Weapon(string name,int capacity,int damage,int price,int energyNeed,int attackRange);

    void Attack(); // takes an enemy and calls its TakeDamage function
    void decreaseEnergy(); //decreases player's energy

    void setDamage(int damage);
    void setAttackRange(int attackRange);
    void setEnergyNeeded(int energy);

    int getDamage();
    int getEnergyNeeded();
    int getAttackRange();

};

class Punch: public Weapon{
public:
    void Attack();
};

class Gun:public Weapon{
private:
    int Ammo;
public:
    void Shoot();
    void setRange(int range);
    void setAmmo(int ammo);
    int getAmmo();
    Gun(string name,int capacity,int price,int damage,int energyNeed,int attackRange,int ammo);
};

class Shotgun:public Gun{
public:
    void Shoot(); // checks the range and deals damage based on it
    Shotgun(string name,int capacity, int price ,int damage,int energyNeed,int attackRange,int ammo);
};

class Snipe: public Gun{
public:
    void Shoot(); // takes multiple enemies and attacks them all
    Snipe(string name,int capacity, int price,int damage,int energyNeed,int attackRange,int ammo);
};

class Rifle: public Gun{
public:
    void Shoot(); // takes some enemies and the damage is divided between
    Rifle(string name,int capacity, int price ,int damage,int energyNeed,int attackRange,int ammo);
};

class coldWeapon: public Weapon{
public:
    void Throw(); //throws the coldWeapon and loses it
    coldWeapon(string name,int capacity,int price ,int damage,int energyNeed,int attackRange);
};

class Bomb: public Weapon {
public:
    void Attack(); // deals damage to nearby enemies
    Bomb(string name,int capacity, int price,int damage,int energyNeed,int attackRange);
};

//--------------------------------

class Consumable: Item{
private:
    int Amount;
public:
    void setAmount(int amount);
    int getAmount();
    Consumable(string name,int capacity,int price,int amount);
};

class HealingItem: public Consumable{
public:
    void Heal(); // heals the player
    HealingItem(string name,int capacity,int price,int amount);
};

class Energizer: public Consumable{
public:
    void Energize(); // increases player's energy
    Energizer(string name,int capacity,int price , int amount);
};
//------------------------------

class Armor: public Item{
private:
    int Amount;
public:
    Armor(string name,int capacity,int price,int amount);
    void setAmount(int amount);
    int getAmount();
    void setAmount(int amount);
};
//------------------------------

class Relic: Item{
public:
    Relic(string name,int capacity,int price,int amount); // remember capacity=0
    void Ability();
};
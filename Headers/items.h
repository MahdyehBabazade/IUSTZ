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

    bool operator==(Item a);
};

//--------------------------------
class Weapon: public Item{
protected:
    int Damage;
    int EnergyNeeded;
    int AttackRange;
public:
    Weapon(string name,int capacity,int damage,int price,int energyNeed,int attackRange);

    virtual void Attack(); // takes an enemy and calls its TakeDamage function
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
    Punch(string name,int capacity,int damage,int price,int energyNeed,int attackRange);
};

class Gun:public Weapon{
private:
    int Ammo;
public:
    void setAmmo(int ammo);
    int getAmmo();
    Gun(string name,int capacity,int price,int damage,int energyNeed,int attackRange,int ammo);
};

class Shotgun:public Gun{
public:
    void Attack() override; // checks the range and deals damage based on it
    Shotgun(string name,int capacity, int price ,int damage,int energyNeed,int attackRange,int ammo);
};

class Snipe: public Gun{
public:
    void Attack() override; // takes multiple enemies and attacks them all
    Snipe(string name,int capacity, int price,int damage,int energyNeed,int attackRange,int ammo);
};

class Rifle: public Gun{
public:
    void Attack() override; // takes some enemies and the damage is divided between
    Rifle(string name,int capacity, int price ,int damage,int energyNeed,int attackRange,int ammo);
};

class coldWeapon: public Weapon{
public:
    void Throw(); //throws the coldWeapon and loses it
    coldWeapon(string name,int capacity,int price ,int damage,int energyNeed,int attackRange);
};

class Throwable: public Weapon {
public:
    Throwable(string name,int capacity, int price,int damage,int energyNeed,int attackRange);
};

class Grenade: public Throwable{
public:
    Grenade(string name,int capacity, int price,int damage,int energyNeed,int attackRange);
    void Attack() override;
};

class BoomRang: public Throwable{
public:
    BoomRang(string name,int capacity, int price,int damage,int energyNeed,int attackRange);
    void Attack() override;
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

class ShieldPotion: public Consumable{
public:
    ShieldPotion(string name,int capacity,int price , int amount);
    void GiveShield(); //increases shield
};
//------------------------------
class Armor: public Item{
private:
    int Amount;
public:
    Armor(string name,int capacity,int price,int amount);
    int getAmount();
    void setAmount(int amount);
};
class Vest: public Armor{
public:
    Vest(string name,int capacity,int price,int amount);
};
class HeadGear: public Armor{
public:
    HeadGear(string name,int capacity,int price,int amount);
};
class FootWear: public Armor{
public:
    FootWear(string name,int capacity,int price,int amount);
};
//------------------------------

class Relic: Item{
private:
public:
    Relic(string name,int capacity,int price,int amount); // remember capacity=0
};
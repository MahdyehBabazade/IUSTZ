#pragma once
#include <string>
#include <algorithm>
#include "../Headers/creature.h"

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
public:
    Weapon(string name,int capacity,int damage,int price,int energyNeeded);
    virtual void Attack(vector<Character*> &characters); // takes an enemy and calls its TakeDamage function
    void decreaseEnergy(Player* player); //decreases player's energy
    void setDamage(int damage);
    void setEnergyNeeded(int energy);
    int getDamage();
    int getEnergyNeeded();

    string GetStat() override;
};

class Punch: public Weapon{
public:
    Punch(string name,int capacity,int damage,int price,int energyNeeded);
};

class Gun:public Weapon{
private:
    int MaxAmmo;
    int Ammo;
    int ReloadEnergy;
    int AmmoNeeded;
public:
    void setAmmo(int ammo);
    int getAmmo();
    int getAmmoNeeded();
    void setAmmoNeeded(int ammoNeeded);
    void Attack(vector<Character*> &characters);
    int getReloadEnergy();
    void setReloadEnergy(int reloadEnergy);
    //void operator-=(int amount);
    void Reload();
    Gun(string name,int capacity,int price,int damage,int energyNeeded,int ammo,int reloadEnergy,int ammoNeeded);
    string GetStat() override;
};

class Shotgun:public Gun{
public:
    void Attack(vector<Character*> &characters) override; // checks the range and deals damage based on it
    Shotgun(string name,int capacity, int price ,int damage,int energyNeeded,int ammo,int ammoNeeded);
};

class Snipe: public Gun{
public:
    void Attack(vector<Character*> &characters) override; // takes multiple characters and attacks them all
    Snipe(string name,int capacity, int price,int damage,int energyNeeded,int ammo,int ammoNeeded);
};

class Rifle: public Gun{
public:
    void Attack(vector<Character*> &characters) override; // takes some characters and the damage is divided between
    Rifle(string name,int capacity, int price ,int damage,int energyNeeded,int ammo,int ammoNeeded);
};

class ColdWeapon: public Weapon{
public:
    void Throw(vector<Character*> &characters); //throws the coldWeapon and loses it
    ColdWeapon(string name,int capacity,int price ,int damage,int energyNeeded);
};

class Throwable: public Weapon {
public:
    Throwable(string name,int capacity, int price,int damage,int energyNeeded);
};

class Grenade: public Throwable{
public:
    Grenade(string name,int capacity, int price,int damage,int energyNeeded);
    void Attack(vector<Character*> &characters) override;
};

class BoomRang: public Throwable{
public:
    BoomRang(string name,int capacity, int price,int damage,int energyNeeded);
    void Attack(vector<Character*> &characters) override;
};

//--------------------------------
class Consumable: public Item{
private:
    int Amount;
public:
    void setAmount(int amount);
    int getAmount();
    Consumable(string name,int capacity,int price,int amount);
};

class HealingItem: public Consumable{
public:
    HealingItem(string name,int capacity,int price,int amount);
};

class Energizer: public Consumable{
public:
    Energizer(string name,int capacity,int price , int amount);
};

class ShieldPotion: public Consumable{
public:
    ShieldPotion(string name,int capacity,int price , int amount);
};
//------------------------------
class Equipment: public Item{
private:
    int Amount;
public:
    Equipment(string name,int capacity,int price,int amount);
    int getAmount();
    void setAmount(int amount);
};
class Vest: public Equipment{
public:
    Vest(string name,int capacity,int price,int amount);
};
class HeadGear: public Equipment{
public:
    HeadGear(string name,int capacity,int price,int amount);
};
class FootWear: public Equipment{
public:
    FootWear(string name,int capacity,int price,int amount);
};
class Boot : public Equipment{
public:
    Boot(string name,int capacity,int price,int amount);
};
                                                                                                      
//------------------------------
class Relic: public Item {
private:
    int MaxHP;
    int MaxEnergy;
public:
    void setMaxHP(int MaxHP);
    void setMaxEnergy(int MaxEnergy);
    int getMaxEnergy();
    int getMaxHP();
    Relic(string name, int capacity, int price,int MaxHP,int maxEnergy); // remember capacity=0
};
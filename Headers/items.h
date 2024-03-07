#pragma once


class Item {
protected:
    string Name;
    int Capacity;
    int Price;
public:
    item(string name,int capacity);
    void setCapacity(int capacity);
    void drop();
    void pick();
};

//--------------------------------
class Weapon: public Item{
protected:
    int Damage;
    int EnergyNeeded;
    int AttackRange;
public:
    Weapon(string name,int capacity,int damage);
    void setDamage(int damage);
    void Attack(); // takes an enemy and calls its TakeDamage function
    void decreaseEnergy(); //decreases player's energy
};
class Gun:public Weapon{
private:
    int ammo;
public:
    void Shoot() override; //checks the range for the attack and decreases the ammo
    void setRange(int range);
};

class Shotgun:public Gun{
public:
    void Shoot(); // checks the range and deals damage based on it
};

class Snipe: public Gun{
public:
    void shoot(); // takes multiple enemies and attacks them all
};

class Rifle: public Weapon{
public:
    void Shoot(); // takes some enemies and the damage is divided between
};

class coldWeapon: public Weapon{
public:
    void throw(); //throws the coldWeapon and loses it
};

class Throwable: public Weapon {
private:

public:
    void throw();
};

class Bomb : public Throwable{
private:
    int damage;
public:
    void
};


//--------------------------------

class Consu

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <cmath>
#include <algorithm>
#include <random>
#include "../Headers/items.h"

using namespace std;

Item :: Item(string name,int capacity,int price) : Name(name), Capacity(capacity),Price(price){}

void Item :: setCapacity(int capacity){Capacity=capacity;}
void Item ::setPrice(int price){Price=price;}
string Item :: getName() {return Name;}
int Item :: getCapacity() {return Capacity;}
int Item :: getPrice() {return Price;}
bool Item ::operator==(Item a) {return a.getName() == Name;}

//------------------------------------
Weapon :: Weapon(string name,int capacity,int price,int damage,int energyNeed)
        : Damage(damage),EnergyNeeded(energyNeed), Item(name, capacity, price) {};

int Weapon:: getDamage() {return Damage;}

void Weapon::setDamage(int damage) {Damage = damage;}

void Weapon::setEnergyNeeded(int energy) {EnergyNeeded = energy;}
string Weapon::GetStat() {
    string outPut = Name + "(Damage: " + to_string(Damage) + " Energy Needed: " + to_string(EnergyNeeded) + ")";
    return outPut;
}

void Gun:: setAmmoNeeded(int ammoNeeded){AmmoNeeded=ammoNeeded;}
int Gun::getAmmoNeeded(){return AmmoNeeded;}

Weapon* choose_weapon(vector<Weapon*> &weapons){
    cout << "choose your weapon: \n";
    int x = 0;
    for(Weapon* &weapon:  weapons){
        x++;
        cout << x << ". " << weapon->GetStat() << endl;
    }
    int choice;
    cout << "choose: ";
    cin >> choice;
    choice -=1;

    return weapons[choice];
}

Character* choose_character(vector<Character*> &characters){
    /*
    cout << "choose the enemy you want to attack: \n";
    int x = 0;
    for(Character* &character:  characters){
        x++;
        cout << x << ". " << character->GetStat() << endl;
    }
    int choice;
    cout << "choose: ";
    cin >> choice;
    choice -=1;
    return characters[choice];
     */
}

void Weapon::Attack(vector<Character*> &Chars) {
    Character* Character = choose_character(Chars);
    Character->takeDamage(Damage);
}
//............
Punch :: Punch(string name, int capacity, int damage, int price, int energyNeed)
        : Weapon(name, capacity, price, damage, energyNeed){}
//.............
Gun ::Gun(string name, int capacity,int price, int damage, int energyNeed, int ammo,int reloadEnergy,int ammoNeeded)
        : AmmoNeeded(ammoNeeded),ReloadEnergy(reloadEnergy), Ammo(ammo),Weapon(name, capacity, price, damage, energyNeed){};

string Gun::GetStat() {
    string outPut = Name + "(Damage: " + to_string(Damage) +
                    " Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    " Energy Needed: " + to_string(EnergyNeeded) +
                    " Reload Energy: " + to_string(ReloadEnergy);
    return outPut;
}

int Gun ::getAmmo() {return Ammo;}
void Gun::setAmmo(int ammo) {Ammo=ammo;}
int Gun::getReloadEnergy() {return ReloadEnergy;}
void Gun::setReloadEnergy(int reloadEnergy) {ReloadEnergy=reloadEnergy;}

void Gun::Attack(vector<Character*> &characters) {};
void Gun::Reload() {Ammo = MaxAmmo;}

//..............
Shotgun ::Shotgun(string name, int capacity,int price, int damage, int energyNeeded,int reloadEnergy,int ammo,int ammoNeeded)
        : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,ammoNeeded){}


void Shotgun ::Attack(vector<Character*> &characters) {
    Character* character = choose_character(characters);
    int EnemyDistance = characters.size() - (find(characters.begin(), characters.end(),character) - characters.begin());
    int damage = max(int(getDamage()*(MinDamagePercent/100)),int((EnemyDistance/characters.size())*getDamage()));
    character->takeDamage(damage);
}
int Shotgun::getMinDamagePercent() {return MinDamagePercent;}
void Shotgun::setMinDamagePercent(int minDamagePercent) {MinDamagePercent=minDamagePercent;}

//..
Snipe ::Snipe(std::string name, int capacity, int price, int damage, int energyNeeded,int reloadEnergy, int ammo,int ammoNeeded)
        : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,ammoNeeded) {}

void Snipe ::Attack(vector<Character*> &characters) {
    Character* character= choose_character(characters);
    int index= find(characters.begin(),characters.end(),character) - characters.begin();
    character->takeDamage(getDamage());
    if(characters[index+1]!=nullptr){
        characters[index+1]->takeDamage(getDamage());
    }
}

//..
Rifle ::Rifle(std::string name, int capacity, int price , int damage, int energyNeeded,int reloadEnergy, int ammo,int ammoNeeded)
        : Gun( name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,ammoNeeded){}

void Rifle ::Attack(vector<Character*> &characters) {
    int damage=this->getDamage()/characters.size();
    for(Character* character: characters){
        character->takeDamage(Damage);
    }
}

//..
ColdWeapon ::ColdWeapon(string name, int capacity,int price, int damage, int energyNeeded)
        : Weapon( name, capacity, price, damage, energyNeeded){}

void ColdWeapon :: Throw(vector<Character*> &characters){
    Character* character= choose_character(characters);
    character->takeDamage(int(this->getDamage()*((100+ThrowDamagePercent)/100)));
}
int ColdWeapon::getThrowDamagePercent(){return ThrowDamagePercent;}
void ColdWeapon:: setThrowDamagePercent(int throwDamagePercent){ThrowDamagePercent=throwDamagePercent;}
//..
Throwable :: Throwable(string name, int capacity,int price, int damage, int energyNeeded)
        : Weapon( name, capacity, price, damage, energyNeeded) {}

Grenade :: Grenade(string name, int capacity, int price, int damage, int energyNeeded)
        : Throwable(name,capacity,price,damage,energyNeeded){};

void Grenade :: Attack(vector<Character*> &characters) {
    for(Character* character: characters){
        character->takeDamage(this->getDamage());
    }
}

void BoomRang ::Attack(vector<Character*> &characters) {
    for(Character* character:characters){
        character->takeDamage(this->getDamage()*2);
    }
}

//-------------------------------
Consumable ::Consumable(string name,string type, int capacity, int price,int amount)
        :Amount(amount),Type(type), Item( name, capacity, price){}

void Consumable ::setAmount(int amount) {Amount=amount;}

int Consumable::getAmount() {return Amount;}
void Consumable:: setType(string type){Type = type;}
string Consumable::getType() {return Type;}
//---------------------------
Equipment ::Equipment(std::string name, int capacity, int price, int amount)
        : Amount(amount),Item( name, capacity, price) {}

void Equipment ::setAmount(int amount) {Amount=amount;}
int Equipment::getAmount() {return Amount;}

Vest ::Vest(std::string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};
HeadGear ::HeadGear(string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};
FootWear ::FootWear(string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};
Boot::Boot(string name,int capacity,int price,int amount)
        : Equipment(name,capacity,price,amount){};
//-----------------------------
Relic::Relic(std::string name, int capacity, int price,int MaxHP,int maxEnergy)
        :MaxHP(MaxHP),MaxEnergy(maxEnergy), Item( name, capacity, price){}

void Relic:: setMaxHP(int Maxhp){MaxHP = Maxhp;}

void Relic::setMaxEnergy(int Maxenergy) {MaxEnergy = Maxenergy;}

int Relic::getMaxHP() {return MaxHP;}

int Relic::getMaxEnergy() {return MaxEnergy;}

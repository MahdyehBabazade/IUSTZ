#include "../Headers/items.h"
#include "../Headers/creature.h"
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

Item :: Item(string name,int capacity,int price) : Name(name), Capacity(capacity),Price(price){}

void Item :: setCapacity(int capacity){Capacity=capacity;}
void Item ::setPrice(int price){Price=price;}
string Item :: getName() {return Name;}
int Item :: getCapacity() {return Capacity;}
int Item :: getPrice() {return Price;}
bool Item ::operator==(Item a) {return a.getName() == Name;}

string Item ::getStat() {
    string outPut = Name + "(price: " + to_string(Price) +", Capacity: " + to_string(Capacity) + ")";
    return outPut;
}
// deffau
Item::Item() : Name("item 1"),Capacity(3),Price(3){};
//------------------------------------
Weapon :: Weapon(string name,int capacity,int price,int damage,int energyNeed)
        : Damage(damage),EnergyNeeded(energyNeed), Item(name, capacity, price) {};

int Weapon:: getDamage() {return Damage;}

void Weapon::setDamage(int damage) {Damage = damage;}

void Weapon::setEnergyNeeded(int energy) {EnergyNeeded = energy;}

string Weapon::getStat() {
    string outPut = Name + "(Damage: " + to_string(Damage) + " Energy Needed: " + to_string(EnergyNeeded) + ")";
    return outPut;
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

string Weapon::getStat() {
    string outPut = Name + " (Damage:  " + to_string(Damage) + ", EnergyNeeded: " + to_string(EnergyNeeded)+")";
    return outPut;
}
//............
Punch :: Punch(string name, int capacity, int damage, int price, int energyNeed)
        : Weapon(name, capacity, price, damage, energyNeed){};
Punch ::Punch() : Weapon("Punch",0,0,1,1) {};
//.............
Gun ::Gun(string name, int capacity,int price, int damage, int energyNeed, int ammo,int reloadEnergy)
        : ReloadEnergy(reloadEnergy), Ammo(ammo),Weapon(name, capacity, price, damage, energyNeed){};

string Gun::getStat() {
    string outPut = Name + "(Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) + ")";
    return outPut;
}

int Gun ::getAmmo() {return Ammo;}
void Gun::setAmmo(int ammo) {Ammo=ammo;}
int Gun::getReloadEnergy() {return ReloadEnergy;}
void Gun::setReloadEnergy(int reloadEnergy) {ReloadEnergy=reloadEnergy;}

//void Gun::Attack(vector<Character*> &characters) {};
void Gun::Reload() {Ammo = MaxAmmo;}

//..............
Shotgun ::Shotgun(string name, int capacity,int price, int damage, int energyNeeded,int reloadEnergy,int ammo)
        : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo){}

void Shotgun ::Attack(vector<Character*> &characters) {
    Character* character = choose_character(characters);
    int EnemyDistance = characters.size() - (find(characters.begin(), characters.end(),character) - characters.begin());
    int damage = max(int(getDamage()*(MinDamagePercent/100)),int((EnemyDistance/characters.size())*getDamage()));
    character->takeDamage(damage);
}
int Shotgun::getMinDamagePercent() {return MinDamagePercent;}
void Shotgun::setMinDamagePercent(int minDamagePercent) {MinDamagePercent=minDamagePercent;}

string Shotgun::getStat() {
    int minDamage = (MinDamagePercent+100)/100*Damage;
    string outPut = Name + "(Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +
                    "Min Damage: "+ to_string(minDamage) +")";
    return outPut;
}

Shotgun ::Shotgun(): Gun("Shotgun",4,15,10,4,4,1) {}
//..
Snipe ::Snipe(std::string name, int capacity, int price, int damage, int energyNeeded,int reloadEnergy, int ammo)
        : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo) {}

Snipe::Snipe() : Gun("snipe",5,17,10,5,5,2){}

void Snipe ::Attack(vector<Character*> &characters) {
    Character* character= choose_character(characters);
    int index= find(characters.begin(),characters.end(),character) - characters.begin();
    character->takeDamage(getDamage());
    if(characters[index+1]!=nullptr){
        characters[index+1]->takeDamage(getDamage()/2);
    }
}
//..
SMG ::SMG(string name, int capacity, int price, int damage, int energyNeeded, int reloadEnergy, int ammo)
    : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo) {};

SMG::SMG() : Gun("SMG",4,15,10,5,5,3){}

void SMG ::Attack(vector<Character *> &characters) {
    for (Character* character: characters){
        character->takeDamage(getDamage());
    }
}

//..
Rifle ::Rifle(std::string name, int capacity, int price , int damage, int energyNeeded,int reloadEnergy, int ammo)
        : Gun( name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo){}
Rifle::Rifle() : Gun("Riflr",5,18,10,5,8,4){}

void Rifle ::Attack(vector<Character*> &characters){
    int damage=getDamage()/characters.size();
    for(Character* character: characters){
        character->takeDamage(damage);
    }
}

void Rifle ::setMaxAttackAmount(int maxAttackAmount) {MaxAttackAmount = maxAttackAmount;}
int Rifle ::getMaxAttackAmount() {return MaxAttackAmount;}

string Rifle::getStat() {
    string outPut = Name + "(Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +
                    "Max Attackable Enemies:"+ to_string(MaxAttackAmount) + ")";
    return outPut;
}
//..
ColdWeapon ::ColdWeapon(string name, int capacity,int price, int damage, int energyNeeded)
        : Weapon( name, capacity, price, damage, energyNeeded){}

ColdWeapon::ColdWeapon() : Weapon("ColdWeapon",3,12,8,4){}

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

Grenade::Grenade() : Throwable("grenade",10,10,8,3) {}
void Grenade :: Attack(vector<Character*> &characters) {
    for(Character* character: characters){
        character->takeDamage(this->getDamage());
    }
}
//..
BoomRang::BoomRang(string name, int capacity, int price, int damage, int energyNeeded)
    :Throwable(name,capacity,price,damage,energyNeeded){}

BoomRang::BoomRang():Throwable("boomi",4,15,10,4){}

void BoomRang ::Attack(vector<Character*> &characters) {
    for(Character* character:characters){
        character->takeDamage(this->getDamage()*2);
    }
}

//-------------------------------
Consumable ::Consumable(string name,string type, int capacity, int price,int amount)
        :Amount(amount),Type(type), Item( name, capacity, price){}
Consumable::Consumable() {
    Name="consumable";
    Type="HPPotion";
    Capacity=5;
    Price=7;
    Amount=10;
}

void Consumable ::setAmount(int amount) {Amount=amount;}

int Consumable::getAmount() {return Amount;}
void Consumable:: setType(string type){Type = type;}
string Consumable::getType() {return Type;}

string Consumable::getStat() {
    string outPut = Name + "(" + Type + " increase amount: " + to_string(Amount) +")";
    return outPut;
}
//---------------------------
Equipment ::Equipment(std::string name, int capacity, int price, int amount)
        : Amount(amount),Item( name, capacity, price) {}

void Equipment ::setAmount(int amount) {Amount=amount;}
int Equipment::getAmount() {return Amount;}

//..
Vest ::Vest(std::string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};
Vest::Vest()  : Equipment("headgear",15,20,20){}

//..
HeadGear ::HeadGear(string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};

HeadGear::HeadGear() : Equipment("headgear",15,20,20){}

//..
FootWear ::FootWear(string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};
FootWear::FootWear() : Equipment("footwear",15,20,20){}

//..
Boot::Boot(string name,int capacity,int price,int amount)
        : Equipment(name,capacity,price,amount){};
Boot::Boot()  : Equipment("boot",15,20,20){}
//-----------------------------
Relic::Relic(std::string name, int capacity, int price,int MaxHP,int maxEnergy)
        :MaxHP(MaxHP),MaxEnergy(maxEnergy), Item( name, capacity, price){}
Relic::Relic() : Item("relic",10,0), MaxHP(10),MaxEnergy(-10) {}
void Relic:: setMaxHP(int Maxhp){MaxHP = Maxhp;}

void Relic::setMaxEnergy(int Maxenergy) {MaxEnergy = Maxenergy;}

int Relic::getMaxHP() {return MaxHP;}

int Relic::getMaxEnergy() {return MaxEnergy;}

string Relic::getStat() {
    string outPut = Name + "(Hp Increase: " + to_string(MaxHP) +
                    " Energy Increase: " + to_string(MaxEnergy);
    return outPut;
}

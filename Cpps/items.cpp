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
void Item ::setName(string name){Name = name;}
string Item :: getName() {return Name;}
int Item :: getCapacity() {return Capacity;}
int Item :: getPrice() {return Price;}
bool Item ::operator==(Item a) {return a.getName() == Name;}

string Item ::getStat() {
    string outPut = Name + " (price: " + to_string(Price) +"$"+", Capacity: " + to_string(Capacity) + ")";
    return outPut;
}
string Item::getShortStat(){
    return Name;
}
//------------------------------------
Weapon :: Weapon(string name,int capacity,int price,int damage,int energyNeed,int upgradeLimit)
        : Damage(damage),EnergyNeeded(energyNeed),UpgradeAmount(0),UpgradeLimit(upgradeLimit), Item(name, capacity, price) {};

int Weapon:: getDamage() {return Damage;}

int Weapon::getEnergyNeeded(){return EnergyNeeded;}

int Weapon::getUpgradeAmount(){return UpgradeAmount;}

int Weapon::getUpgradeLimit(){return UpgradeLimit;}

void Weapon::setUpgradeAmount(int upgrades){UpgradeAmount = upgrades;}

void Weapon::setUpgradeLimit(int upgradeLimit){UpgradeLimit = upgradeLimit;}

void Weapon::setDamage(int damage) {Damage = damage;}

void Weapon::setEnergyNeeded(int energy) {EnergyNeeded = energy;}

void Weapon::Attack(Character* Enemey) {
    Enemey->takeDamage(Damage);
}

string Weapon::getStat() {
    string outPut = Name + " (Damage:  " + to_string(Damage) +", EnergyNeeded: " + to_string(EnergyNeeded)+
        ", Price: "+to_string(Price)+"$"+", Capacity: "+ to_string(Capacity)+ ")";
    return outPut;
}
string Weapon::getShortStat(){
    string outPut = Name + " (Damage: " + to_string(Damage) + ", EnergyNeeded: " + to_string(EnergyNeeded) +")";
    return outPut;
}

//............
Punch :: Punch(string name, int capacity, int damage, int price, int energyNeed)
        : Weapon(name, capacity, price, damage, energyNeed,0){};
//.............
Gun ::Gun(string name, int capacity,int price, int damage, int energyNeed,int reloadEnergy, int ammo,int upgradeLimit)
        : ReloadEnergy(reloadEnergy), Ammo(ammo),MaxAmmo(ammo),Weapon(name, capacity, price, damage, energyNeed,upgradeLimit){};

string Gun::getStat() {
    string outPut = Name + " (Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+ 
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +", Price: "+to_string(Price)+"$"+", Capacity: "+ to_string(Capacity)+ ")";
    return outPut;
}
string Gun::getShortStat(){
    string outPut = Name + " (Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+ 
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +")";
    return outPut;
}

int Gun ::getAmmo() {return Ammo;}
void Gun::setAmmo(int ammo) {Ammo=ammo;}
int Gun::getReloadEnergy() {return ReloadEnergy;}
void Gun::setReloadEnergy(int reloadEnergy) {ReloadEnergy=reloadEnergy;}
int Gun::getMaxAmmo(){return MaxAmmo;}

//void Gun::Attack(vector<Character*> &characters) {};
void Gun::Reload() {Ammo = MaxAmmo;}
void Gun::Attack(Character* Target){
    Target->takeDamage(getDamage());
    Ammo-=1;
}
//..............
Shotgun ::Shotgun(string name, int capacity,int price, int damage, int energyNeeded,int reloadEnergy,int ammo,int minDamagePercent,int upgradeLimit)
        : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,upgradeLimit), MinDamagePercent(minDamagePercent){}

void Shotgun ::Attack(vector<Character*> Targets,Character* Target) {
    int EnemyDistance = Targets.size() - (find(Targets.begin(), Targets.end(),Target) - Targets.begin());
    double damage1 = double(EnemyDistance)/Targets.size()*getDamage();
    double damage2 = double(getDamage())*(MinDamagePercent/100);
    int damage = max(damage1,damage2);
    Target->takeDamage(damage);
    setAmmo(getAmmo()-1);
}
int Shotgun::getMinDamagePercent() {return MinDamagePercent;}
void Shotgun::setMinDamagePercent(int minDamagePercent) {MinDamagePercent=minDamagePercent;}

string Shotgun::getStat() {
    int minDamage = int((MinDamagePercent+100)/100*Damage);
    string outPut = Name + " (Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +
                    "Min Damage: "+ to_string(minDamage) +", Price: "+to_string(Price)+"$"+", Capacity: "+ to_string(Capacity)+")";
    return outPut;
}
string Shotgun::getShortStat(){
    int minDamage = int((MinDamagePercent+100)/100*Damage);
    string outPut = Name + " (Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +
                    "Min Damage: "+ to_string(minDamage) +")";
    return outPut;
}

//..
Snipe ::Snipe(std::string name, int capacity, int price, int damage, int energyNeeded,int reloadEnergy, int ammo,int upgradeLimit)
        : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,upgradeLimit) {}

void Snipe ::Attack(vector<Character*> Targets,Character* Target) {
    int index= find(Targets.begin(),Targets.end(),Target) - Targets.begin();
    Target->takeDamage(getDamage());
    if(Targets.size()-1 > index){
        Targets[index+1]->takeDamage(getDamage()/2);
    }
    
    setAmmo(getAmmo()-1);
}
//..
SMG ::SMG(string name, int capacity, int price, int damage, int energyNeeded, int reloadEnergy, int ammo,int upgradeLimit)
    : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,upgradeLimit) {};


void SMG ::Attack(vector<Character*> Targets) {
    for (Character* Target: Targets){
        Target->takeDamage(getDamage());
    }
    setAmmo(getAmmo()-Targets.size());
}

//..
Rifle ::Rifle(std::string name, int capacity, int price , int damage, int energyNeeded,int reloadEnergy, int ammo,int maxAttackAmount,int upgradeLimit)
        : Gun( name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,upgradeLimit),MaxAttackAmount(maxAttackAmount){}

void Rifle ::Attack(vector<Character*> Targets){
    int damage=getDamage()/Targets.size();
    for(Character* Target: Targets){
        Target->takeDamage(damage);
    }
    
    setAmmo(getAmmo() - Targets.size());
}

void Rifle ::setMaxAttackAmount(int maxAttackAmount) {MaxAttackAmount = maxAttackAmount;}
int Rifle ::getMaxAttackAmount() {return MaxAttackAmount;}

string Rifle::getStat() {
    string outPut = Name + " (Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +
                    "Max Attackable Targets:"+ to_string(MaxAttackAmount) + ", Price: "+to_string(Price)+"$"+", Capacity: "+ to_string(Capacity)+")";
    return outPut;
}
string Rifle::getShortStat(){
    string outPut = Name + " (Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +
                    "Max Attackable Targets:"+ to_string(MaxAttackAmount) +")";
    return outPut;
}
//..
ColdWeapon ::ColdWeapon(string name, int capacity,int price, int damage, int energyNeeded,int upgradeLimit)
        : Weapon( name, capacity, price, damage, energyNeeded,upgradeLimit){}

void ColdWeapon :: Throw(Character* Target){
    Target->takeDamage(int(this->getDamage()*1.2));
}

//-----------------------------
Throwable :: Throwable(string name, int capacity,int price, int damage, int energyNeeded,int upgradeLimit)
        : Weapon( name, capacity, price, damage, energyNeeded,upgradeLimit) {}

void Throwable :: Attack(vector<Character*> Targets) {
    for(Character* Target: Targets){
        Target->takeDamage(getDamage());
    }
}

//..
Grenade :: Grenade(string name, int capacity, int price, int damage, int energyNeeded,int upgradeLimit)
        : Throwable(name,capacity,price,damage,energyNeeded,upgradeLimit){};

//..
BoomRang::BoomRang(string name, int capacity, int price, int damage, int energyNeeded,int upgradeLimit)
    :Throwable(name,capacity,price,damage,energyNeeded,upgradeLimit){}

void BoomRang ::Attack(vector<Character*> Targets) {
    for(Character* Target:Targets){
        Target->takeDamage(getDamage()*2);
    }
}

//-------------------------------
Consumable ::Consumable(string name,string type, int capacity, int price,int amount)
        :Amount(amount),Type(type), Item( name, capacity, price){}

void Consumable ::setAmount(int amount) {Amount=amount;}

int Consumable::getAmount() {return Amount;}
void Consumable:: setType(string type){Type = type;}
string Consumable::getType() {return Type;}

string Consumable::getStat() {
    string outPut = Name + " (" + Type + " increase amount: " + to_string(Amount) +", Price: "+to_string(Price)+"$"+", Capacity: "+ to_string(Capacity)+")";
    return outPut;
}
string Consumable::getShortStat(){
    string outPut = Name + " (" + Type + " increase amount: " + to_string(Amount) +")";
    return outPut;
}
//---------------------------
Equipment ::Equipment(std::string name, int capacity, int price, int amount)
        : Amount(amount),Item( name, capacity, price) {}

void Equipment ::setAmount(int amount) {Amount=amount;}
int Equipment::getAmount() {return Amount;}

string Equipment ::getStat(){
    string output=Name + "(" + ", Protection: "+to_string(Amount) + "%"+ ", Price: "+ to_string(Price)+ "$"+
        ", Capacity: "+ to_string(Capacity) +")";
        return output;
}
string Equipment ::getShortStat(){
    string output=Name + "(" + ", Protection: "+to_string(Amount) + "%)";
    return output;
}
//..
Vest ::Vest(std::string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};

//..
HeadGear ::HeadGear(string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};

//..
FootWear ::FootWear(string name, int capacity, int price, int amount)
        : Equipment(name,capacity,price,amount){};

//..
Boot::Boot(string name,int capacity,int price,int amount)
        : Equipment(name,capacity,price,amount){};
//-----------------------------
Relic::Relic(std::string name, int capacity, int price,int MaxHP,int maxEnergy)
        :MaxHP(MaxHP),MaxEnergy(maxEnergy), Item( name, capacity, price){}

void Relic:: setMaxHP(int Maxhp){MaxHP = Maxhp;}

void Relic::setMaxEnergy(int Maxenergy) {MaxEnergy = Maxenergy;}

int Relic::getMaxHP() {return MaxHP;}

int Relic::getMaxEnergy() {return MaxEnergy;}

string Relic::getStat() {
    string outPut = Name + " (Hp Increase: " + to_string(MaxHP) +
                    " Energy Increase: " + to_string(MaxEnergy)+")";
    return outPut;
}
string Relic::getShortStat(){
    return getStat();
}

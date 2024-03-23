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

void Weapon::setUpgradeAmount(int upgrades){UpgradeAmount = upgrades;}

void Weapon::setDamage(int damage) {Damage = damage;}

void Weapon::setEnergyNeeded(int energy) {EnergyNeeded = energy;}



Character* choose_character(vector<Character*> &characters){
    cout << "choose the enemy you want to attack: \n";
    int x = 0;
    for(Character* &character:  characters){
        x++;
        cout << x << ". " << character->getStat() << endl;
    }
    int choice;
    cout << "choose: ";
    cin >> choice;
    choice -=1;
    return characters[choice];
    
}

void Weapon::Attack(vector<Character*> &Chars) {
    Character* Character = choose_character(Chars);
    Character->takeDamage(Damage);
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
Gun ::Gun(string name, int capacity,int price, int damage, int energyNeed, int ammo,int reloadEnergy,int upgradeLimit)
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

//void Gun::Attack(vector<Character*> &characters) {};
void Gun::Reload() {Ammo = MaxAmmo;}

//..............
Shotgun ::Shotgun(string name, int capacity,int price, int damage, int energyNeeded,int reloadEnergy,int ammo,int minDamagePercent,int upgradeLimit)
        : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,upgradeLimit), MinDamagePercent(minDamagePercent){}

void Shotgun ::Attack(vector<Character*> &characters) {
    Character* character = choose_character(characters);
    int EnemyDistance = characters.size() - (find(characters.begin(), characters.end(),character) - characters.begin());
    double damage1 = double(EnemyDistance)/characters.size()*getDamage();
    double damage2 = double(getDamage())*(MinDamagePercent/100);
    int damage = max(damage1,damage2);
    character->takeDamage(damage);
    
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

void Snipe ::Attack(vector<Character*> &characters) {
    Character* character= choose_character(characters);
    int index= find(characters.begin(),characters.end(),character) - characters.begin();
    character->takeDamage(getDamage());
    if(characters.size() > index+1){
        characters[index+1]->takeDamage(getDamage()/2);
    }
    
    setAmmo(getAmmo()-1);
}
//..
SMG ::SMG(string name, int capacity, int price, int damage, int energyNeeded, int reloadEnergy, int ammo,int upgradeLimit)
    : Gun(name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,upgradeLimit) {};


void SMG ::Attack(vector<Character *> &characters) {
    for (Character* character: characters){
        character->takeDamage(getDamage());
    }
    setAmmo(getAmmo()-characters.size());
}

//..
Rifle ::Rifle(std::string name, int capacity, int price , int damage, int energyNeeded,int reloadEnergy, int ammo,int maxAttackAmount,int upgradeLimit)
        : Gun( name,  capacity, price, damage,  energyNeeded,reloadEnergy, ammo,upgradeLimit),MaxAttackAmount(maxAttackAmount){}

void Rifle ::Attack(vector<Character*> &characters){
    int damage=getDamage()/characters.size();
    for(Character* character: characters){
        character->takeDamage(damage);
    }
    
    setAmmo(getAmmo() - characters.size());
}

void Rifle ::setMaxAttackAmount(int maxAttackAmount) {MaxAttackAmount = maxAttackAmount;}
int Rifle ::getMaxAttackAmount() {return MaxAttackAmount;}

string Rifle::getStat() {
    string outPut = Name + " (Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +
                    "Max Attackable Enemies:"+ to_string(MaxAttackAmount) + ", Price: "+to_string(Price)+"$"+", Capacity: "+ to_string(Capacity)+")";
    return outPut;
}
string Rifle::getShortStat(){
    string outPut = Name + " (Damage: " + to_string(Damage) +
                    ", Ammo: " + to_string(Ammo) + "/" + to_string(MaxAmmo)+
                    ", Energy Needed: " + to_string(EnergyNeeded) +
                    ", Reload Energy: " + to_string(ReloadEnergy) +
                    "Max Attackable Enemies:"+ to_string(MaxAttackAmount) +")";
    return outPut;
}
//..
ColdWeapon ::ColdWeapon(string name, int capacity,int price, int damage, int energyNeeded,int upgradeLimit)
        : Weapon( name, capacity, price, damage, energyNeeded,upgradeLimit){}

void ColdWeapon :: Throw(vector<Character*> &characters){
    Character* character= choose_character(characters);
    character->takeDamage(int(this->getDamage()*((100+ThrowDamagePercent)/100)));
}
int ColdWeapon::getThrowDamagePercent(){return ThrowDamagePercent;}
void ColdWeapon:: setThrowDamagePercent(int throwDamagePercent){ThrowDamagePercent=throwDamagePercent;}
//..
Throwable :: Throwable(string name, int capacity,int price, int damage, int energyNeeded,int upgradeLimit)
        : Weapon( name, capacity, price, damage, energyNeeded,upgradeLimit) {}

Grenade :: Grenade(string name, int capacity, int price, int damage, int energyNeeded,int upgradeLimit)
        : Throwable(name,capacity,price,damage,energyNeeded,upgradeLimit){};

void Grenade :: Attack(vector<Character*> &characters) {
    for(Character* character: characters){
        character->takeDamage(this->getDamage());
    }
}
//..
BoomRang::BoomRang(string name, int capacity, int price, int damage, int energyNeeded,int upgradeLimit)
    :Throwable(name,capacity,price,damage,energyNeeded,upgradeLimit){}

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

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

void Item :: setCapacity(int capacity){
    Capacity=capacity;
}
void Item ::setPrice(int price){
    Price=price;
}
string Item :: getName() {
    return Name;
}
int Item :: getCapacity() {
    return Capacity;
}
int Item :: getPrice() {
    return Price;
}
bool Item ::operator==(Item a) {
    return a.getName() == Name;
}

//------------------------------------
Weapon :: Weapon(string name,int capacity,int price,int damage,int energyNeed)
        : Damage(damage),EnergyNeeded(energyNeed), Item(name, capacity, price) {};

int Weapon:: getDamage() {
    return Damage;
}

void Weapon::setDamage(int damage) {
    Damage = damage;
}


void Weapon::setEnergyNeeded(int energy) {
    EnergyNeeded = energy;
}
string Weapon::GetStat() {
    string outPut = Name + "(Damage: " + to_string(Damage) + " Energy Needed: " + to_string(EnergyNeeded) + ")";
    return outPut;
}
void setAmmoNeeded(int ammoNeeded){
    AmmoNeeded=ammoneeded;
}
int getAmmoNNeeded(){
    return AmmoNeeded;
}
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
    cout << "choose the enemy you want to attack: \n";
    int x = 0;
    for(Enemy* &enemy:  enemies){
        x++;
        cout << x << ". " << enemy->GetStat() << endl;
    }
    int choice;
    cout << "choose: ";
    cin >> choice;
    choice -=1;

    return enemies[choice];
}

void Weapon::Attack(vector<Character*> &Chars) {
    Character* Character = choose_character(Chars);
    Character->takeDamage(Damage);
}
void Weapon ::decreaseEnergy(Player* player) {
    player->setEnergy(player->getEnergy() - EnergyNeeded);
}
//............
Punch :: Punch(string name, int capacity, int damage, int price, int energyNeed)
        : Weapon(name, capacity, price, damage, energyNeed){}
//.............
Gun ::Gun(string name, int capacity,int price, int damage, int energyNeed, int ammo,int reloadEnergy,int ammoNeeded)
        : AmmoNeeded(ammoNeeded),ReloadEnergy(reloadEnergy), Ammo(ammo),Weapon(name, capacity, price, damage, energyNeed){};

string Gun::GetStat() {
    string outPut = Name + "(Damage: " + Damage +
                    " Ammo: " + Ammo + "/" + MaxAmmo+
                    " Energy Needed: " + EnergyNeeded +
                    " Reload Energy: " + ReloadEnergy;
    return outPut;
}

int Gun ::getAmmo() {
    return Ammo;
}
void Gun::setAmmo(int ammo) {
    Ammo=ammo;
}
int Gun::getReloadEnergy() {
    return ReloadEnergy;
}
void Gun::setReloadEnergy(int reloadEnergy) {
    ReloadEnergy=reloadEnergy;
}
void Gun::Attack(vector<Character*> &characters) {};
void Gun::Reload() {
    Ammo = MaxAmmo;f
}
//..............
Shotgun ::Shotgun(string name, int capacity,int price, int damage, int energyNeeded, int ammo,int ammoNeeded)
        : Gun(name,  capacity, price, damage,  energyNeed, ammo,ammoNeeded){}

/*
void Gun::operator-=(int amount) {
    Ammo-=1;
}
 */


void Shotgun ::Attack(vector<Character*> &characters) {
    Character* character = choose_character(characters);
    int EnemyDistance = characters.size() - (find(characters.begin(), characters.end(),character) - characters.begin());
    int damage = max(int(getDamage()/2),int((EnemyDistance/characters.size())*getDamage()));
    character->takeDamage(damage);
}
//..
Snipe ::Snipe(std::string name, int capacity, int price, int damage, int energyNeeded, int ammo,int ammoNeeded)
        : Gun( name,  capacity, price, damage,  energyNeed, ammo,ammoNeeded) {}

void Snipe ::Attack(vector<Character*> &characters) {
    Character* character= choose_character(characters);
    int index= find(characters.begin(),characters.end(),character);
    character->takeDamage(getDamage());
    if(characters[index+1]!=nullptr){
        characters[index+1]->takeDamage(getDamage();
    }
}

//..
Rifle ::Rifle(std::string name, int capacity, int price , int damage, int energyNeeded, int ammo,int ammoNeeded)
        : Gun( name,  capacity, price, damage,  energyNeed, ammo,ammoNeeded){}

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
    character->takeDamage(int(this->getDamage()*1.2));
    //what the fuck did you do? //throwable coldweapon
}

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
Consumable ::Consumable(std::string name, int capacity, int price,int amount,int type)
        :Amount(amount),Type(type), Item( name, capacity, price){}

void Consumable ::setAmount(int amount) {
    Amount=amount;
}

int Consumable::getAmount() {
    return Amount;
}

HealingItem ::HealingItem(std::string name, int capacity,int price, int amount)
        :Consumable( name, capacity, price, amount){}

Energizer ::Energizer(std::string name, int capacity,int price, int amount)
        : Consumable(name, capacity, price, amount){}

ShieldPotion::ShieldPotion(string name, int capacity, int price, int amount)
        : Consumable(name, capacity, price, amount){}
//---------------------------
Equipment ::Equipment(std::string name, int capacity, int price, int amount)
        : Amount(amount),Item( name, capacity, price) {}

void Equipment ::setAmount(int amount) {
    Amount=amount;
}
int Equipment::getAmount() {
    return Amount;
}

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

void Relic:: setMaxHP(int Maxhp){
    MaxHP = Maxhp;
}

void Relic::setMaxEnergy(int Maxenergy) {
    MaxEnergy = Maxenergy;
}

int Relic::getMaxHP() {
    return MaxHP;
}

int Relic::getMaxEnergy() {
    return MaxEnergy;
}

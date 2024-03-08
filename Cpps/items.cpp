#include <iostream>
#include <vector>
#include <string>
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
Weapon :: Weapon(string name,int capacity,int price,int damage,int energyNeed,int attackRange)
        : Damage(damage),EnergyNeeded(energyNeed), AttackRange(attackRange), Item(name, capacity, price) {};

int Weapon:: getDamage() {
    return Damage;
}
int Weapon::getAttackRange() {
    return AttackRange;
}

void Weapon::setDamage(int damage) {
    Damage = damage;
}
void Weapon::setAttackRange(int attackRange) {
    AttackRange = attackRange;
}
void Weapon::setEnergyNeeded(int energy) {
    EnergyNeeded = energy;
}
string Weapon::GetStat() {
    string outPut = Name+"(Damage: " + to_string(Damage) + "Attack Range: " + to_string(AttackRange) +")";
    return outPut;
}

void Weapon::Attack(vector<Enemy*> &enemies,vector<pair<Item*, int>> &items) {
    cout << "choose your weapon: \n";
    int x = 0;
    for(pair<Item*, int> &z:  items){
        x++;
        cout << x << ". " << static_cast<Weapon*>(z.first)
    }


}
void Weapon ::decreaseEnergy(Player* player) {
    player->setEnergy(player->getEnergy() - getEnergyNeeded());
}
//............
Punch :: Punch(string name, int capacity, int damage, int price, int energyNeed, int attackRange)
       : Weapon(name, capacity, price, damage, energyNeed, attackRange){}

//.............
Gun ::Gun(string name, int capacity,int price, int damage, int energyNeed, int attackRange, int ammo)
        : Ammo(ammo),Weapon(name, capacity, price, damage, energyNeed, attackRange){}

int Gun ::getAmmo() {
    return Ammo;
}
void Gun::setAmmo(int ammo) {
    Ammo=ammo;
}
//..............
Shotgun ::Shotgun(string name, int capacity,int price, int damage, int energyNeed, int attackRange, int ammo)
: Gun(name,  capacity, price, damage,  energyNeed,  attackRange,  ammo){}

void Shotgun ::Attack() {

}
//..
Snipe ::Snipe(std::string name, int capacity, int price, int damage, int energyNeed, int attackRange, int ammo)
: Gun( name,  capacity, price, damage,  energyNeed,  attackRange,  ammo) {}

void Snipe ::Attack() {

}

//..
Rifle ::Rifle(std::string name, int capacity, int price , int damage, int energyNeed, int attackRange, int ammo)
: Gun( name,  capacity, price, damage,  energyNeed,  attackRange,  ammo){}

void Rifle ::Attack() {

}

//..
coldWeapon ::coldWeapon(string name, int capacity,int price, int damage, int energyNeed, int attackRange)
: Weapon( name, capacity, price, damage, energyNeed, attackRange){}

void coldWeapon :: Throw(){
}

//..
Throwable :: Throwable(string name, int capacity,int price, int damage, int energyNeed, int attackRange)
: Weapon( name, capacity, price, damage, energyNeed, attackRange) {}

Grenade :: Grenade(string name, int capacity, int price, int damage, int energyNeed, int attackRange)
         : Throwable(name,capacity,price,damage,energyNeed,attackRange){};
void Grenade :: Attack() {
}

void BoomRang ::Attack() {

}

//-------------------------------
Consumable ::Consumable(std::string name, int capacity, int price,int amount)
:Amount(amount), Item( name, capacity, price){}

void Consumable ::setAmount(int amount) {
    Amount=amount;
}

int Consumable::getAmount() {
    return Amount;
}

HealingItem ::HealingItem(std::string name, int capacity,int price, int amount)
:Consumable( name, capacity, price, amount){}

void HealingItem ::Heal() {

}

Energizer ::Energizer(std::string name, int capacity,int price, int amount)
: Consumable(name, capacity, price, amount){}

ShieldPotion ::ShieldPotion(std::string name, int capacity, int price, int amount)
              : Consumable(name, capacity, price, amount){};
void ShieldPotion ::GiveShield() {

}
//---------------------------
Armor ::Armor(std::string name, int capacity,int price, int amount)
: Amount(amount),Item( name, capacity, price) {}

void Armor ::setAmount(int amount) {
    Amount=amount;
}
int Armor::getAmount() {
    return Amount;
}

Vest ::Vest(std::string name, int capacity, int price, int amount)
      : Armor(name,capacity,price,amount){};

HeadGear ::HeadGear(string name, int capacity, int price, int amount)
          : Armor(name,capacity,price,amount){};

FootWear ::FootWear(string name, int capacity, int price, int amount)
          : Armor(name,capacity,price,amount){};
//-----------------------------
Relic::Relic(std::string name, int capacity, int price, int amount)
: Item( name, capacity, price){}


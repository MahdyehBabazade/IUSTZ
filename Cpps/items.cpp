#include <iostream>
#include "../Headers/items.h"
using namespace std;

Item :: Item(string name,int capacity,int price) : Name(name), Capacity(capacity),Price(price){}

void Item :: setCapacity(int capacity){
    Capacity=capacity;
}
void Item ::setPrice(int price){
    Price=price;
}
Weapon :: Weapon(string name,int capacity,int price,int damage,int energyNeed,int attackRange)
    : Damage(damage),EnergyNeeded(energyNeed), AttackRange(attackRange), Item(name, capacity, price) {};

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
void Weapon ::decreaseEnergy() {
}


int Gun ::getAmmo() {
    return Ammo;
}
void Gun::setAmmo(int ammo) {
    Ammo=ammo;
}
Gun ::Gun(string name, int capacity,int price, int damage, int energyNeed, int attackRange, int ammo)
: Ammo(ammo),Weapon( name, capacity, price, damage, energyNeed, attackRange){}

void Gun ::setRange(int range) {
    AttackRange = range;
}

Shotgun ::Shotgun(std::string name, int capacity,int price, int damage, int energyNeed, int attackRange, int ammo)
: Gun( name,  capacity, price, damage,  energyNeed,  attackRange,  ammo){}

Snipe ::Snipe(std::string name, int capacity, int price, int damage, int energyNeed, int attackRange, int ammo)
: Gun( name,  capacity, price, damage,  energyNeed,  attackRange,  ammo) {}

void Snipe ::Shoot() {

}

Rifle ::Rifle(std::string name, int capacity, int price , int damage, int energyNeed, int attackRange, int ammo)
: Gun( name,  capacity, price, damage,  energyNeed,  attackRange,  ammo){}

coldWeapon ::coldWeapon(std::string name, int capacity,int price, int damage, int energyNeed, int attackRange)
: Weapon( name, capacity, price, damage, energyNeed, attackRange){}

void coldWeapon :: Throw(){

}

Bomb ::Bomb(std::string name, int capacity,int price, int damage, int energyNeed, int attackRange)
: Weapon( name, capacity, price, damage, energyNeed, attackRange) {}

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
: Consumable( name, capacity, price, amount){}

Armor ::Armor(std::string name, int capacity,int price, int amount)
: Amount(amount),Item( name, capacity, price) {}

void Armor ::setAmount(int amount) {
    Amount=amount;
}

int Armor::getAmount() {
    return Amount;
}

Relic::Relic(std::string name, int capacity, int price, int amount)
: Item( name, capacity, price){}

void Relic ::Ability() {

}

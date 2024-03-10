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
Enemy* choose_character(vector<Enemy*> &enemies){
    /*
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
     */
}

void Weapon::Attack(vector<Character*> &Chars) {
    Character* Character = choose_character(Chars);
    character->takeDamage(Damage);
}
void Weapon ::decreaseEnergy(Player* player) {
    player->setEnergy(player->getEnergy() - EnergyNeeded);
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

void Shotgun ::Attack(vector<Character*> &characters) {
    Character* character = choose_character(characters);
    int EnemyDistance = characters.size() - (find(characters.begin(), characters.end(),character) - characters.begin());
    int damage = max(int(getDamage()/2),int((EnemyDistance/characters.size())*getDamage()));
    character->takeDamage(damage);
}
//..
Snipe ::Snipe(std::string name, int capacity, int price, int damage, int energyNeed, int attackRange, int ammo)
: Gun( name,  capacity, price, damage,  energyNeed,  attackRange,  ammo) {}

void Snipe ::Attack(vector<Character*> characters) {
    for(int i=0;i<min(1,int(characters.size()));i++){
        if(i==0){
            characters[i]->takeDamage(this->getDamage());
        }else {
            characters[i]->takeDamage(int(this->getDamage()/2));
        }
    }
}

//..
Rifle ::Rifle(std::string name, int capacity, int price , int damage, int energyNeed, int attackRange, int ammo)
: Gun( name,  capacity, price, damage,  energyNeed,  attackRange,  ammo){}

void Rifle ::Attack(vector<Character*> characters) {
    int damage=this->getDamage()/characters.size();
    for(Character* character: characters){
        character->takeDamage(damage);
    }
}

//..
coldWeapon ::coldWeapon(string name, int capacity,int price, int damage, int energyNeed, int attackRange)
: Weapon( name, capacity, price, damage, energyNeed, attackRange){}

void coldWeapon :: Throw(vector<Character*> characters){
    Character* character= choose_character(characters);
    character->takeDamage(int(this->getDamage()*1.2));
    what the fuck did you do? //throwable coldweapon
}

//..
Throwable :: Throwable(string name, int capacity,int price, int damage, int energyNeed, int attackRange)
: Weapon( name, capacity, price, damage, energyNeed, attackRange) {}

Grenade :: Grenade(string name, int capacity, int price, int damage, int energyNeed, int attackRange)
         : Throwable(name,capacity,price,damage,energyNeed,attackRange){};

void Grenade :: Attack(vector<Character*> characters) {
    for(Character* character: characters){
        character->takeDamage(this->getDamage());
    }
}

void BoomRang ::Attack(vector<Character*> characters) {
    for(Character* character:characters){
        character->takeDamage(this->getDamage()*2);
    }
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

void HealingItem ::Heal(Player* player) {
    player->setHP(player->getHP()+getAmount());
}

Energizer ::Energizer(std::string name, int capacity,int price, int amount)
: Consumable(name, capacity, price, amount){}
void Energizer ::Energize(Player *player) {
    player->setEnergy(player->getEnergy()+getAmount());
}

ShieldPotion ::ShieldPotion(std::string name, int capacity, int price, int amount)
              : Consumable(name, capacity, price, amount){};
void ShieldPotion ::GiveShield(Player *player) {
    player->setShield(player->getShield()+getAmount());
}
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
//-----------------------------
Relic::Relic(std::string name, int capacity, int price)
: Item( name, capacity, price){}

int getRandomNumber()
{
    int number = rand() % 6 + 1;
    number = number * 5;
    return number;
}

vector<int> Relic ::Randomize() {
    //health,energy,equipment,weapon 
    vector<int> result = {0,0,getRandomNumber(),getRandomNumber() };
    shuffle(result.begin(), result.end());
    return result;
}
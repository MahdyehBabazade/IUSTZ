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
Enemy* choose_enemy(vector<Enemy*> &enemies){
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

void Weapon::Attack(vector<Enemy*> &enemies,vector<Weapon*> &weapons) {
    Weapon* weapon = choose_weapon(weapons);
    if(typeid(weapon) == typeid(Shotgun)){
        Gun* gun = dynamic_cast<Gun*>(weapon);
        Shotgun* shotgun = dynamic_cast<Shotgun*>(gun);
        shotgun->Attack(enemies,weapons);
        return;
    }else if(typeid(weapon) == typeid(Rifle)){
        Gun* gun = dynamic_cast<Gun*>(weapon);
        Rifle* rifle = dynamic_cast<Rifle*>(gun);
        rifle->Attack(enemies);
        return;
    }else if(typeid(weapon) == typeid(Snipe)) {
        Gun *gun = dynamic_cast<Gun *>(weapon);
        Snipe *snipe = dynamic_cast<Snipe *>(gun);
        snipe->Attack(enemies);
        return;
    }else if(typeid(weapon) == typeid(Grenade)) {
        Throwable *throwable = dynamic_cast<Throwable *>(weapon);
        Grenade *grenade = dynamic_cast<Grenade *>(throwable);
        grenade->Attack(enemies);
        return;
    }else if(typeid(weapon) == typeid(BoomRang)) {
        Throwable *throwable = dynamic_cast<Throwable *>(weapon);
        BoomRang *boomRang = dynamic_cast<BoomRang *>(throwable);
        boomRang->Attack(enemies);
        return;
    }
    Enemy* enemy = choose_enemy(enemies);

    enemy->takeDamage(weapon->getDamage());
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

void Shotgun ::Attack(vector<Enemy*> &enemies) {
    Enemy* enemy = choose_enemy(enemies);
    int EnemyDistance = enemies.size() - (find(enemies.begin(), enemies.end(),enemy) - enemies.begin());
    int damage = max(int(this->getDamage()/2),int((EnemyDistance/enemies.size())*this->getDamage()));
    enemy->takeDamage(damage);
}
//..
Snipe ::Snipe(std::string name, int capacity, int price, int damage, int energyNeed, int attackRange, int ammo)
: Gun( name,  capacity, price, damage,  energyNeed,  attackRange,  ammo) {}

void Snipe ::Attack(vector<Enemy*> enemies) {
    for(int i=0;i<min(1,int(enemies.size()));i++){
        if(i==0){
            enemies[i]->takeDamage(this->getDamage());
        }else {
            enemies[i]->takeDamage(int(this->getDamage()/2));
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
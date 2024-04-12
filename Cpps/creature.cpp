#pragma once
#include "../Headers/creature.h"
#include "functions.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <string>
#include <typeinfo>
using namespace std;

Character :: Character(string Name , int MaxHP , vector<pair<Item* , int>> Items , vector<pair<Weapon*,int>> Weapons){
    this -> Name = Name;
    this -> HP = MaxHP;
    this -> MaxHP = MaxHP;
    this -> Armor = 0;
    this -> Shield = 0;
    this -> Items = Items;
    this -> Weapons = Weapons;
    this -> Equipments = {nullptr , nullptr , nullptr , nullptr};
}

string Character :: getName(){return Name;}

void Character :: setName(string Name){this -> Name = Name;}

int Character :: getHP(){return HP;}

void Character :: setHP(int HP){this -> HP = min(HP , MaxHP);}

int Character :: getMaxHP(){return MaxHP;}

void Character :: setMaxHP(int MaxHP){this -> MaxHP = MaxHP;}

double Character :: getArmor(){return Armor;}

void Character :: setArmor(double Armor){this -> Armor = Armor;}

void Character :: setShield(int Shield){this->Shield = Shield;}

int Character :: getShield(){return Shield;}

void Character :: takeDamage(int damagetaken){
    // If the shield could handle more damage than the damage the weapon causes, then the weapon damages the shield not the character.
    if(Shield>=damagetaken){ 
        Shield -= damagetaken; 
        damagetaken = 0;       
    }
    // If not, the shield just reduces the damage given by the weapon and damages the character less than it could have.
    else{
        damagetaken -= Shield; 
        Shield = 0;
    }
    setHP(getHP() - (int) (damagetaken * (100 - Armor) / 100));
}

void Character :: death(){
    delete this;
}

string Character :: getStat(){
    return Name + "\t" + to_string(getHP()) + "/" + to_string(getMaxHP()) + "\t" + to_string(getShield()) + "\t"
    + to_string(getArmor());
}

string Character :: DeathDialogue(){return "";}

vector<pair<Item* , int>> Character :: getItems(){return Items;} // Returns the Items the character owns

vector<pair<Weapon* , int>> Character :: getWeapons(){return Weapons;} // Returns the Weapons the character owns

vector<Equipment*> Character :: getEquipments(){return Equipments;} // Returns the Equipments the character owns

Weapon* Player::ChooseWeapon(){ // Lists the weapons for you and the lets you choose one from your backpack
    for(int i = 0; i< Weapons.size(); i++){
        cout << i + 1 << "." << Weapons[i].first->getStat() << endl;
    }
    cout << "Choose: ";
    int choice;
    cin >> choice;
    choice --;
    return Weapons[choice].first;
}
Player :: Player(string Name, int MaxHP , int BackPackCapacity , int BackPackWeight
, int MaxEnergy , int Coin ,vector<pair<Item* , int>> Items
, vector<pair<Weapon* , int>> Weapons) : Character(Name , MaxHP, Items ,  Weapons){
    this -> BackPackCapacity = BackPackCapacity;
    this -> BackPackWeight = BackPackWeight;
    this -> Energy = MaxEnergy;
    this -> MaxEnergy = MaxEnergy;
    this -> Coin = Coin;
}

Player :: ~Player(){
    clearScreen();
    cout << "Not good enough" << endl << "Defeated!!!" << endl << "Welcome to HELLMOS\n";
    cout << "Press anything to return to the start menu\n";
    getch();
}

void Player :: setBackPackCapacity(int BackPackCapacity){this -> BackPackCapacity = BackPackCapacity;}

int Player :: getBackPackCapacity(){return BackPackCapacity;}

void Player :: setBackPackWeight(int BackPackWeight){this-> BackPackWeight = BackPackWeight;}

int Player :: getBackPackWeight(){return BackPackWeight;}

void Player :: setEnergy(int Energy){this -> Energy = Energy;}

int Player :: getEnergy(){return Energy;}

void Player :: setMaxEnergy(int MaxEnergy){this -> MaxEnergy = MaxEnergy;}

int Player :: getMaxEnergy(){return MaxEnergy;}

void Player :: addCoin(int CoinToBeAdded){this -> Coin += CoinToBeAdded;}

void Player :: removeCoin(int CoinToBeRemoved){this -> Coin -= CoinToBeRemoved;}

int Player :: getCoin(){return Coin;}

void Player :: addItem(Item* Item){ //adds items depending on its capacity and the backpack capacity
    if(BackPackWeight + Item->getCapacity() <= BackPackCapacity){
        bool IsAdded = false;
        if(dynamic_cast<Gun *>(Item) == nullptr)
            for(int i = 0; i < Items.size(); i++)
                if(*Items[i].first== *Item){
                    Items[i].second++;
                    IsAdded = true;
                    break;
                }
        if(!IsAdded){
            if(dynamic_cast<Shotgun *>(Item) != nullptr){
                for(int i = 0; i < Items.size(); i++){
                    if(dynamic_cast<Shotgun *>(Items[i].first) != nullptr){
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                        }
                        if(i == Items.size() - 1){
                            Items.push_back(make_pair(Item , 1));
                            break;
                        }
                    }
                    else if(dynamic_cast<Shotgun *>(Items[i].first) == nullptr){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(dynamic_cast<Snipe *>(Item) != nullptr){
                for(int i = 0; i < Items.size(); i++){
                    if(dynamic_cast<Snipe *>(Items[i].first) != nullptr){
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                        }
                        if(i == Items.size() - 1){
                            Items.push_back(make_pair(Item , 1));
                            break;
                        }
                    }
                    else if(dynamic_cast<Shotgun *>(Items[i].first) == nullptr){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(dynamic_cast<SMG *>(Item) != nullptr){
                for(int i = 0; i < Items.size(); i++){
                    if(dynamic_cast<SMG *>(Items[i].first) != nullptr){
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                        }
                        if(i == Items.size() - 1){
                            Items.push_back(make_pair(Item , 1));
                            break;
                        }
                    }
                    else if(dynamic_cast<Shotgun *>(Items[i].first) == nullptr && dynamic_cast<Snipe *>(Items[i].first) == nullptr){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(dynamic_cast<Rifle *>(Item) != nullptr){
                for(int i = 0; i < Items.size(); i++){
                    if(dynamic_cast<Rifle *>(Items[i].first) != nullptr){
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            IsAdded = true;
                            break;
                        }
                        if(i == Items.size() - 1){
                            Items.push_back(make_pair(Item , 1));
                            break;
                        }
                    }
                    else if(dynamic_cast<Shotgun *>(Items[i].first) == nullptr && dynamic_cast<Snipe *>(Items[i].first) == nullptr
                    && dynamic_cast<SMG *>(Items[i].first) != nullptr){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(dynamic_cast<ColdWeapon *>(Item) != nullptr){
                for(int i = 0; i < Items.size(); i++){
                    if(dynamic_cast<ColdWeapon *>(Items[i].first) != nullptr){
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                        }
                        if(i == Items.size() - 1){
                            Items.push_back(make_pair(Item , 1));
                            break;
                        }
                    }else if(dynamic_cast<Gun *>(Items[i].first) == nullptr){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(dynamic_cast<Grenade *>(Item) != nullptr){
                for(int i = 0; i < Items.size(); i++){
                    if(dynamic_cast<Grenade*>(Items[i].first) != nullptr){
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                        }
                        if(i == Items.size() - 1){
                            Items.push_back(make_pair(Item , 1));
                            break;
                        }
                    }
                    else if(dynamic_cast<Gun *>(Items[i].first) == nullptr
                    && dynamic_cast<ColdWeapon *>(Items[i].first) == nullptr){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(dynamic_cast<BoomRang *>(Item) != nullptr){
                for(int i = 0; i < Items.size(); i++){
                    if(dynamic_cast<BoomRang *>(Items[i].first) != nullptr){
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                        }
                        if(i == Items.size() - 1){
                            Items.push_back(make_pair(Item , 1));
                            break;
                        }
                    }
                    else if(dynamic_cast<Gun *>(Items[i].first) == nullptr
                    && dynamic_cast<ColdWeapon *>(Items[i].first) == nullptr
                    && dynamic_cast<Grenade *>(Items[i].first) == nullptr){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(dynamic_cast<Consumable *>(Item) != nullptr){
                for(int i = 0; i < Items.size(); i++){
                    if(dynamic_cast<Consumable *>(Items[i].first) != nullptr && Items[i].first->getName() >= Item->getName()){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(dynamic_cast<Equipment *>(Items[i].first) != nullptr){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(dynamic_cast<Equipment *>(Item) != nullptr){
                Items.push_back(make_pair(Item , 1));
            }
        }
        if(Items.empty()){
            Items.push_back(make_pair(Item , 1));
        }
        BackPackWeight += Item->getCapacity();
        if(dynamic_cast<Weapon *>(Item) != nullptr)
            addWeapon(dynamic_cast<Weapon *>(Item));
        else if(dynamic_cast<Equipment *>(Item) != nullptr)
            addEquipment(dynamic_cast<Equipment *>(Item));
        else if(dynamic_cast<Consumable *>(Item) != nullptr)
            addConsumable(dynamic_cast<Consumable *>(Item));
    }
}

void Player :: removeItem(Item* Item){ //deletes the items considering their numbers 
    for (int i = 0; i < Items.size(); i++){
        if (*Item == *Items[i].first){
            BackPackWeight -= Items[i].first->getCapacity();
            if(Items[i].second == 1){
                Items.erase(Items.begin()+i); //this may still consume some Bytes
            }
            else
                Items[i].second--;
        }
    }
    if(dynamic_cast<Weapon *>(Item) != nullptr)
            removeWeapon(dynamic_cast<Weapon *>(Item));
        else if(dynamic_cast<Equipment *>(Item) != nullptr)
            removeEquipment(dynamic_cast<Equipment *>(Item));
        else if(dynamic_cast<Consumable *>(Item) != nullptr)
            removeConsumable(dynamic_cast<Consumable *>(Item));
}


vector<Relic*> Player :: getRelic(){return Relics;}

void Player :: addRelic(Relic* Relic){
    setMaxHP(getMaxHP()*(100+Relic->getMaxHP())/100);
    setMaxEnergy(getMaxEnergy()*(100+Relic->getMaxEnergy())/100);
    Relics.push_back(Relic);
}

void Player :: addWeapon(Weapon* Weapon){ //adds weapons checking if already existed or not,
    bool isAdded = false;
    //if existed, just increases the number by one
    if(dynamic_cast<Gun *>(Weapon) == nullptr){
        for(int i = 0; i < Weapons.size(); i++){
            if(*Weapon == *Weapons[i].first){
                Weapons[i].second++;
                isAdded = true;
                break;
            }
        }
    }
    //if not, inserts the weapon in
    if(!isAdded){
        if(dynamic_cast<Shotgun *>(Weapon) != nullptr){
            for(int i = 0; i < Weapons.size(); i++){
                if(dynamic_cast<Shotgun *>(Weapons[i].first) != nullptr){
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                    }
                    if(i == Weapons.size() - 1){
                        Weapons.push_back(make_pair(Weapon , 1));
                        break;
                    }
                }
                else if(dynamic_cast<Shotgun *>(Weapons[i].first) == nullptr){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
            }
        }
        else if(dynamic_cast<Snipe*>(Weapon) != nullptr){
            for(int i = 0; i < Weapons.size(); i++){
                if(dynamic_cast<Snipe*>(Weapons[i].first) != nullptr){
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                    }
                    if(i == Weapons.size() - 1){
                        Weapons.push_back(make_pair(Weapon , 1));
                        break;
                    }
                }
                else if(dynamic_cast<Shotgun *>(Weapons[i].first) == nullptr){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                    break;
                }
            }
        }
        else if(dynamic_cast<SMG *>(Weapon) != nullptr){
            for(int i = 0; i < Weapons.size(); i++){
                if(dynamic_cast<SMG *>(Weapons[i].first) != nullptr){
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                    }
                }
                else if(dynamic_cast<Shotgun *>(Weapons[i].first) == nullptr && dynamic_cast<Snipe*>(Weapons[i].first) == nullptr){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                    break;
                }
            }
        }
        else if(dynamic_cast<Rifle *>(Weapon) != nullptr){
            for(int i = 0; i < Weapons.size(); i++){
                if(dynamic_cast<Rifle *>(Weapons[i].first) != nullptr)
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                }
                else if(dynamic_cast<Shotgun *>(Weapons[i].first) == nullptr && dynamic_cast<Snipe *>(Weapons[i].first) == nullptr
                && dynamic_cast<SMG *>(Weapons[i].first) == nullptr){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                    break;
                }
            }
        }
        else if(dynamic_cast<ColdWeapon *>(Weapon) != nullptr){
            for(int i = 0; i < Weapons.size(); i++){
                if(dynamic_cast<ColdWeapon *>(Weapons[i].first) != nullptr){
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                    }
                }
                else if(dynamic_cast<Gun *>(Weapons[i].first) == nullptr){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                    break;
                }
            }
        }
        else if(dynamic_cast<Grenade *>(Weapon) != nullptr){
            for(int i = 0; i < Weapons.size(); i++){
                if(dynamic_cast<Grenade *>(Weapons[i].first) != nullptr)
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                }
                else if(dynamic_cast<Gun *>(Weapons[i].first) == nullptr && 
                dynamic_cast<ColdWeapon*>(Weapons[i].first) == nullptr){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                    break;
                }
            }
        }
        else if(dynamic_cast<BoomRang *>(Weapon) != nullptr){
            for(int i = 0; i < Weapons.size(); i++){
                if(dynamic_cast<BoomRang *>(Weapons[i].first) != nullptr)
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                }
                else if(dynamic_cast<Gun *>(Weapons[i].first) == nullptr && 
                dynamic_cast<ColdWeapon *>(Weapons[i].first) == nullptr && dynamic_cast<Grenade *>(Weapons[i].first) == nullptr){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                    break;
                }
            }
        }
    }
    if(Weapons.size() == 0){
        Weapons.push_back(make_pair(Weapon , 1));
    }
}

void Player :: removeWeapon(Weapon* Weapon){ //deletes the weapon considering its numbers, thus an item is also deleted
    for(int i = 0; i < Weapons.size(); i++){
        if(*Weapons[i].first == *Weapon){
            if(Weapons[i].second == 1)
                Weapons.erase(Weapons.begin()+ i);
            else
                Weapons[i].second--;
        }
    }
}


void Player :: addEquipment(Equipment* Equipment){ // adds the equipment if you buy it, to the Equipments' vector
    setArmor(getArmor() + Equipment->getAmount());
    if(dynamic_cast<HeadGear *>(Equipment) != nullptr){
        if(Equipments[0] != nullptr)
            removeItem(Equipments[0]);
        Equipments[0] = Equipment;
    }
    else if(dynamic_cast<Vest *>(Equipment) != nullptr){
        if(Equipments[1] != nullptr)
            removeItem(Equipments[1]);
        Equipments[1] = Equipment;
    }
    else if(dynamic_cast<FootWear *>(Equipment) != nullptr){
        if(Equipments[2] != nullptr)
            removeItem(Equipments[2]);
        Equipments[2] = Equipment;
    }
    else if(dynamic_cast<Boot *>(Equipment) != nullptr){
        if(Equipments[3] != nullptr)
            removeItem(Equipments[3]);
        Equipments[3] = Equipment;
    }
}

void Player :: removeEquipment(Equipment* Equipment){ //removes the equipment if you sell or lose it, from the Equipments' vector
    setArmor(getArmor() - Equipment->getAmount());
    if(dynamic_cast<HeadGear *>(Equipment) != nullptr)
        Equipments[0] = nullptr;
    else if(dynamic_cast<Vest *>(Equipment) != nullptr)
        Equipments[1] = nullptr;
    else if(dynamic_cast<FootWear *>(Equipment) != nullptr)
        Equipments[2] = nullptr;
    else if(dynamic_cast<Boot *>(Equipment) != nullptr)
        Equipments[3] = nullptr;
}

vector<pair<Consumable* , int>> Player :: getConsumables(){return Consumables;}

void Player :: addConsumable(Consumable* Consumable){ //adds consumables checking if already existed or not,
    bool isAdded = false;
    //if existed, just increases the number by one
    for(int i = 0; i < Consumables.size(); i++){
        if(*Consumable == *Consumables[i].first){
            Consumables[i].second++;
            isAdded = true;
            break;
        }
    }
    //if not, inserts the consumable in
    if(!isAdded)
        for(int i = 0; i < Consumables.size(); i++){
            if(Consumables[i].first->getName()>=Consumable->getName()){
                Consumables.insert(Consumables.begin()+ i , make_pair(Consumable , 1));
                break;
            }
            if(i == Consumables.size() - 1){
                Consumables.push_back(make_pair(Consumable , 1));
                break;
            }
        }
    if(Consumables.size() == 0){
        Consumables.push_back(make_pair(Consumable , 1));
    }
}

void Player :: removeConsumable(Consumable* Consumable){ //deletes the consumable considering its numbers, thus an item is also deleted
    for(int i = 0; i < Consumables.size(); i++){
        if(*Consumables[i].first == *Consumable){
            if(Consumables[i].second == 1)
                Consumables.erase(Consumables.begin()+ i);
            else
                Consumables[i].second--;
        }
    }
}

void Player :: Consume(Consumable* Consumable){
    if(Consumable->getType() == "ShieldPotion"){ // if the player consumes ShieldPotion the shield amount increases
        setShield(getShield() + Consumable->getAmount());
        removeItem(Consumable);
    }
    else if(Consumable->getType() == "HPPotion"){
        setHP(min(getMaxHP() , getHP() + Consumable->getAmount())); // if the player consumes  HealingItem the hp increases
        removeItem(Consumable);
    }
    else if(Consumable->getType() == "EnergyPotion"){
        setEnergy(min(MaxEnergy , Energy + Consumable->getAmount())); // if the player consumes Energizer the energy increases
        removeItem(Consumable);
    }
}


string HumanEnemy :: RajazKhani(){
    vector<string> curse ={"MOTHER FUCKER" , "BITCH" , "Asshole" };
    string RajazKhani = "Got u, " + ShuffleVec(curse)[0];
    vector<string> Rajaz = {RajazKhani , "Loser" , "Almost there!" , "You think you can defeat me? Pathetic!" , 
        "I'll crush you like a bug!" , "You're nothing but a stain on the battlefield!"};
    return ShuffleVec(Rajaz)[0];
}

HumanEnemy :: HumanEnemy(string Name , int MaxHP , double Armor , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon* , int>> Weapons , vector<pair<Consumable* , int>> Consumables)
    : Character(Name , MaxHP , Items , Weapons){
    this->Consumables = Consumables;
    setArmor(Armor);
    state = State::Heal;
    
    for(pair<Weapon*,int> x : Weapons){
        if(dynamic_cast<Gun *>(x.first) != nullptr){
            Guns.emplace_back(dynamic_cast<Gun*>(x.first),x.second);
        }else {
            noneGuns.emplace_back(x);
        }
    }
    
}
void HumanEnemy :: StateMachine(Player* player,Control::FightControl* fightControl){
    while(true){
        switch (state)
        {
        case State::Heal:
        {
            // cout << "heal initiated" << endl;
            
            if(getHP() > getMaxHP()/2){
                state = State::Shield;
                continue;
            }
                
            bool hasPotion = false;
            for(pair<Consumable* , int> x:Consumables){
                Consumable* Potion = x.first;
                if(Potion->getType() == "HPPotion"){
                    hasPotion = true;
                    Consume(Potion);
                    fightControl->getView()->print("HP +" + to_string(Potion->getAmount()));
                    break;
                }
            }
            if(!hasPotion){
                state = State::Shield;
            }
            continue;
        }
        case State::Shield:
        {
            // cout << "Shield initiated" << endl;
            if(getShield() > getMaxHP()/4){ // cahracters can have max shield of maxhp/2
                state = State::Attack;
                continue;
            }  
            
            bool hasPotion = false;      
            for(pair<Consumable* , int> x:Consumables){
                Consumable* Potion = x.first;
                if(Potion->getType() == "ShieldPotion"){
                    Consume(Potion);
                    hasPotion = true;
                    fightControl->getView()->print("Sheild " + to_string(getShield()) + " +");
                    break;
                }
            }
            
            if(!hasPotion){
                state = State::Attack;
            }
            
            continue;
        }
        case State::NoneGunAttack:{
        {
            noneGuns = ShuffleVec(noneGuns);
            Weapon* weapon = noneGuns[0].first;
            if(dynamic_cast<ColdWeapon *>(weapon) != nullptr){   
                int amount = 0;
                for(pair<Weapon*,int> p:noneGuns){
                    if(dynamic_cast<ColdWeapon *>(weapon))
                        amount += p.second;
                }
                if(amount >=2){
                    if(random_num(1,5) == 5){                 // 20% chance of throwing the cold weapon
                        // cout << "throw" << endl;
                        Attack(player,weapon,1);
                    }else{
                        // cout << "cold weapon attack" << endl;
                        Attack(player,weapon,0);
                    }
                }else{
                    Attack(player,weapon,0);
                }
            }else if (dynamic_cast<Throwable *>(weapon) != nullptr){
                // cout << "throwable attack" << endl;
                Attack(player,weapon,0);
            }
            
            fightControl->getView()->print("Dealt " + to_string(weapon->getDamage()) + " Damage");
            break;
        }
        }
        case State::Reload:
            // cout << "reloaded" << endl;
            fightControl->getView()->print("Reloaded!");
            Guns[0].first->Reload();
            break;
            
        case State::GunAttack:
        {   
            Guns = ShuffleVec(Guns);
            bool hasAttacked = false;
            for(pair<Gun*,int> x:Guns){
                if(x.first->getAmmo() > 0){
                    // cout << "gun attack" << endl;
                    Attack(player,x.first,0);
                    //cout << "attacked with " << x.first->getShortStat();
                    fightControl->getView()->print("Dealt " + to_string(x.first->getDamage()) + " Damage");
                    hasAttacked = true;
                    break;
                }
            }
            
            if(hasAttacked){
                break;
            }
            
            if(!noneGuns.empty()){
                if(random_num(1,2) == 1){ 
                    state = State::Reload;
                    continue;
                }else{
                    state = State::NoneGunAttack;
                    continue;
                }
            }else{
                state = State::Reload;
                continue;
            }
            
            
        }
        case State::Attack:
            if(!Guns.empty()){
                state = State::GunAttack;
            }else{
                state = State::NoneGunAttack;
            }
            
            continue;
        default:
            break;
        }

        break;
    }
    state = State::Heal;
}


string HumanEnemy::DeathDialogue(){
    vector<string> EnemyDeathQuotes = { "I can't believe this is how it all ends!", "You fucking bastard!",
    "Wasted!" , "Nooo, I can't die yet!" , "My child , take care o..." , "I'll damn you" , 
    "My brother will get my revenge!!!" , "I'll be waiting , you SoB!!!" , "That was a fun fight" , 
    "See you on the other side"};
    return ShuffleVec(EnemyDeathQuotes)[0];
}

void HumanEnemy::Attack(Player* player , Weapon* weapon , int choice){
    if (dynamic_cast<Gun *>(weapon) != nullptr) {
        if(dynamic_cast<Shotgun *>(weapon) != nullptr){
            Shotgun* shotgun = dynamic_cast<Shotgun*>(weapon);
            shotgun->Attack({player},player);
        }else if(dynamic_cast<Snipe *>(weapon) != nullptr){
            Snipe* snipe = dynamic_cast<Snipe*>(weapon);
            snipe->Attack({player},player);
        }else if(dynamic_cast<Rifle *>(weapon) != nullptr){
            Rifle* rifle = dynamic_cast<Rifle*>(weapon);
            rifle->Attack({player});
        }else if(dynamic_cast<Rifle *>(weapon) != nullptr){
            SMG* smg = dynamic_cast<SMG*>(weapon);
            smg->Attack({player});
        }else{
            Gun* gun = dynamic_cast<Shotgun*>(weapon);
            gun->Attack(player);
        }
    }
    else if(dynamic_cast<Throwable *>(weapon) != nullptr){
        Throwable *throwable = dynamic_cast<Throwable *>(weapon);
        throwable->Attack({player});
        removeItem(throwable); //removes the throwable from the backpack after it dropped
    }
    else if(dynamic_cast<ColdWeapon *>(weapon) != nullptr){
        ColdWeapon *coldWeapon = dynamic_cast<ColdWeapon *>(weapon);
        if(choice ==1){
            coldWeapon->Throw(player); //if attack, it calls the Attack function of the cold weapon
        }
        else{
            coldWeapon->Attack(player); //if throw, it calls the Throw function of the cold weapon then removes it from the backpack
            removeItem(coldWeapon); 
        }
    }
    else{
        weapon->Attack(player);
    }
}

void HumanEnemy :: removeConsumable(Consumable* Consumable){ //deletes the consumable considering its numbers, thus an item is also deleted (for throwables)
    for(int i = 0; i < Consumables.size(); i++){
        if(*Consumables[i].first == *Consumable){
            if(Consumables[i].second == 1)
                Consumables.erase(Consumables.begin()+ i);
            else
                Consumables[i].second--;
        }
    }
}

void HumanEnemy :: Consume(Consumable* Consumable){
    if(Consumable->getType() == "ShieldPotion"){ // if the human enemy consumes ShieldPotion the shield amount increases
        setShield(getShield() + Consumable->getAmount());
        removeItem(Consumable);
    }
    else if(Consumable->getType() == "HPPotion"){ // if the human enemy consumes  HealingItem the hp increases
        setHP(min(getMaxHP() , getHP() + Consumable->getAmount()));
        removeItem(Consumable);
    }
}

void HumanEnemy::removeWeapon(Weapon* Weapon){
    for(int i = 0; i < Weapons.size(); i++){
        if(*Weapons[i].first == *Weapon){
            if(Weapons[i].second == 1)
                Weapons.erase(Weapons.begin()+ i);
            else
                Weapons[i].second--;
        }
    }
    for(int i = 0; i < noneGuns.size(); i++){
        if(*noneGuns[i].first == *Weapon){
            if(noneGuns[i].second == 1)
                noneGuns.erase(noneGuns.begin()+ i);
            else
                noneGuns[i].second--;
        }
    }
}

void HumanEnemy :: removeItem(Item* Item){ //deletes the items considering their numbers 
    for (int i = 0; i < Items.size(); i++){
        if (*Item == *Items[i].first){
            if(Items[i].second == 1)
                Items.erase(Items.begin()+i);
            else
                Items[i].second--;
        }
    }
    if(dynamic_cast<Gun *>(Item) != nullptr || dynamic_cast<ColdWeapon *>(Item) != nullptr ||
    dynamic_cast<Throwable *>(Item) != nullptr)
        removeWeapon(dynamic_cast<Weapon *>(Item));
    else if(dynamic_cast<Consumable *>(Item) != nullptr)
        removeConsumable(dynamic_cast<Consumable *>(Item));
}


Zombie :: Zombie(string Name , int MaxHP , double Armor , vector<pair<Item* , int>> Items
, vector<pair<Weapon* , int>> Weapons)
: Character(Name , MaxHP , Items , Weapons){
    setArmor(Armor);
}


string Zombie::DeathDialogue(){
    vector<string> ZombieDeathQuotes = {"Aaauugh!!!!" , "Haaauugh!!!" , "Blauugh!" , "Guaargh!!" , "Bluargh!!!"};
    return ShuffleVec(ZombieDeathQuotes)[0];
}

void Zombie :: Attack(Player* player,Control::FightControl* fightControl){
    Weapon* punch = ShuffleVec(Weapons)[0].first;
    punch->Attack(player);
    fightControl->getView()->print("Dealt " + to_string(punch->getDamage()) + " damge");
}

Shopkeeper :: Shopkeeper(string Name){this->Name = Name;}

string Shopkeeper :: getName(){return Name;}

string Shopkeeper :: HiDialogue(){ // The shopkeeper says hi
    vector<string> ShopkeeperHi = {"Salute soldier! How can I help?" , "Hi commander! Is there anything I can provide?" , "Welcome to my shop!"};
    return Name + ": " + ShuffleVec(ShopkeeperHi)[0] + "\n";
}

string Shopkeeper :: ByeDialogue(){ // The shopkeeper says bye
    return Name + ": " + "Good luck, Soldier.\n";
}

string Shopkeeper :: SellDialogue(Item* item){ // The shopkeeper sells sth to the player
    vector<string> ShopkeeperSell = {"So you've bought " + item->getName() , "You chose one of the best items." ,
    "Wish " + item->getName() + " helps you survive."};
    return Name + ": " + ShuffleVec(ShopkeeperSell)[0] + "\n";
} // items to be included

string Shopkeeper :: BuyDialogue(Item* item){ // The shopkeeper buys sth from the player
    return Name + ": " + "I'll buy that for " + to_string(item->getPrice()) + " coins.\n";
} // items to be included

string Shopkeeper::UpgradeLimitDialogue(Weapon* weapon){
    vector<string> UpgradeLimit = {weapon->getName() + " has been fined too many times already." , 
    weapon->getName() + " has reached it's limits." + weapon->getName() + " is as fine as it gets!"};
    return Name + ": " + ShuffleVec(UpgradeLimit)[0] + "\n";
}

string Shopkeeper::UpgradeLimitDialogue(){
    vector<string> UpgradeLimit = {"I'm so tired!" , "I can't refine your items anymore!" , 
    "I'm out of refinement resources."};
    return Name + ": " + ShuffleVec(UpgradeLimit)[0] + "\n";
}

string Shopkeeper :: NoMoneyDialogue(){ // What the shopkeeper says when the player has less money than the item's price
    vector<string> PoorSoldier = {"You don't have enough coins!" , "Poor soldier!!!" , "Can't get you that!" ,
    "So little for so much?!"};
    if (rand() % 9 == 0)
    {
        return "...";
    }
    return Name + ": " + ShuffleVec(PoorSoldier)[0] + "\n";
}

Medic :: Medic(string Name){this->Name = Name;}

string Medic :: getName(){return Name;}

string Medic :: HiDialogue(){
    vector<string> MedicSayHi = {"Hi, Soldier." , "Salute soldier! How can I help?" , "Hi commander! Are you hurt somewhere?"};
    return Name + ": " + ShuffleVec(MedicSayHi)[0]+"\n";
}

string Medic :: ByeDialogue(){return Name + ": " + "Have a safe journey.\n";}

string Medic :: HealDialogue(){return Name + ": " + "I've patched you up!\n";}

string Medic :: NoMoneyDialogue(){
    vector<string> PoorSoldier = {"You don't have enough coins!" , "Poor soldier!" , "Can't Heal you with that much coin!" , 
    "So little for so much?!"};
    if (rand() % 9 == 0)
    {
        return "...";
    }
    return Name + ": " + ShuffleVec(PoorSoldier)[0] + "\n";
}

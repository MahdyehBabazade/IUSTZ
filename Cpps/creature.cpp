#include "../Headers/creature.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <string>
#include <typeinfo>
using namespace std;

vector<string> ShuffleVec(vector<string> vec){ // Shuffles a vector
    random_device rd;
    default_random_engine abs(rd());
    shuffle(vec.begin(), vec.end(), abs);
    return vec;
}

Character :: Character(string Name , int HP , int MaxHP , double Armor , int Shield ,
vector<pair<Item* , int>> Items , vector<pair<Weapon*,int>> Weapons){
    this -> Name = Name;
    this -> HP = HP;
    this -> MaxHP = MaxHP;
    this -> Armor = Armor;
    this -> Shield = Shield;
    this -> Items = Items;
    this -> Weapons = Weapons;
    this -> Equipments = {{nullptr} , {nullptr} , {nullptr} , {nullptr}};
}

string Character :: getName(){return Name;}

void Character :: setName(string Name){this -> Name = Name;}

int Character :: getHP(){return HP;}

void Character :: setHP(int HP){this -> HP = HP;}

int Character :: getMaxHP(){return MaxHP;}

void Character :: setMaxHP(int MaxHP){this -> MaxHP = MaxHP;}

int Character :: getArmor(){return Armor;}

void Character :: setArmor(double Armor){this -> Armor = Armor;}

void Character :: setShield(int Shield){this->Shield = Shield;}

int Character :: getShield(){return Shield;}

void Character :: takeDamage(int damagetaken){
    //if the shield could handle more damage than the damage the weapon causes, then the weapon damages the shield not the character.
    if(Shield>=damagetaken){ 
        Shield -= damagetaken; 
        damagetaken = 0;       
    }
    //if not, the shield just reduces the damage given by the weapon and damages the character less than it could have.
    else{
        damagetaken -= Shield; 
        Shield = 0;
    }
    setHP(getHP() - (int) (damagetaken * (100 - Armor) / 100));
}

vector<pair<Item* , int>> Character :: getItems(){return Items;} //returns the Items the character owns

vector<pair<Weapon* , int>> Character :: getWeapons(){return Weapons;} //returns the Weapons the character owns

vector<Equipment*> Character :: getEquipments(){return Equipments;} //returns the Equipments the character owns

Weapon* Player::ChooseWeapon(){ //lists the weapons for you and the lets you choose one from your backpack
    for(int i = 0; i< Weapons.size(); i++){
        cout << i + 1 << "." << Weapons[i].first->getStat() << endl;
    }
    cout << "Choose: ";
    int choice;
    cin >> choice;
    choice --;
    return Weapons[choice].first;
}
void Player :: Attack(vector<Character *> &characters , Weapon* weapon , int choice){ 
    //attacks the enemies with guns, cold weapons or throwables
    if(getEnergy()>=weapon->getEnergyNeeded()){
        //checks which type of weapon, the weapon you chose is, then calls the Attack function of that weapon
        if (typeid(*weapon) == typeid(Gun)) {
            Gun *gun = dynamic_cast<Gun *>(weapon);
            if (gun->getAmmo() >= gun->getAmmoNeeded()) {
                gun->Attack(characters);
                gun->setAmmo(gun->getAmmo()-gun->getAmmoNeeded()); //reduces the number of ammos after the gun shot.
            }
        }
        else if(typeid(*weapon) == typeid(Throwable)){
            Throwable *throwable = dynamic_cast<Throwable *>(weapon);
            throwable->Attack(characters);
            removeItem(throwable); //removes the throwable from the backpack after it dropped
        }
        else if(typeid(*weapon) == typeid(ColdWeapon)){
            ColdWeapon *coldWeapon = dynamic_cast<ColdWeapon *>(weapon);
            //checks if we want to throw the cold weapon or attack with it
            if(choice ==1){
                coldWeapon->Attack(characters); //if attack, it calls the Attack function of the cold weapon
            }
            else{
                coldWeapon->Throw(characters); //if throw, it calls the Throw function of the cold weapon then removes it from the backpack
                removeItem(coldWeapon); 
            }
        }
        else{
            weapon->Attack(characters);
        }
        setEnergy(getEnergy()-weapon->getEnergyNeeded()); //reduces the energy needed to use that kind of weapon from the energy the character has
    }

}

Player :: Player(string Name, int HP, int MaxHP, double Armor, int BackPackCapacity , int BackPackWeight
, int MaxEnergy , int Coin , int Shield ,vector<pair<Item* , int>> Items
, vector<pair<Weapon* , int>> Weapons , vector<pair<Consumable* , int>> Consumables , vector<Equipment*> Equipments) : Character(Name , HP , MaxHP , Armor , Shield , Items ,  Weapons){
    this -> BackPackCapacity = BackPackCapacity;
    this -> BackPackWeight = BackPackWeight;
    this -> MaxEnergy = MaxEnergy;
    this -> Coin = Coin;
    this -> Consumables = Consumables;
    this -> Equipments = Equipments;
}

Player :: ~Player(){
    cout << "Not good enough" << endl << "Defeated!!!" << endl << "Welcome to HELLMOS";
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
        if(typeid(*Item)!=typeid(Gun))
            for(int i = 0; i < Items.size(); i++)
                if(*Items[i].first== *Item){
                    Items[i].second++;
                    IsAdded = true;
                    break;
                }
        if(!IsAdded){
            if(typeid(*Item) == typeid(Shotgun)){
                for(int i = 0; i < Items.size(); i++){
                    if(typeid(*Items[i].first) == typeid(Shotgun))
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                    }
                    else if(typeid(*Items[i].first) != typeid(Shotgun)){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                    }
                }
            }
            else if(typeid(*Item) == typeid(Snipe)){
                for(int i = 0; i < Items.size(); i++){
                    if(typeid(*Items[i].first) == typeid(Snipe))
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                    }
                    else if(typeid(*Items[i].first) != typeid(Shotgun)){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                    }
                }
            }
            else if(typeid(*Item) == typeid(SMG)){
                for(int i = 0; i < Items.size(); i++){
                    if(typeid(*Items[i].first) == typeid(SMG))
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                    }
                    else if(typeid(*Items[i].first) != typeid(Shotgun) && typeid(*Items[i].first) != typeid(Snipe)){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                    }
                }
            }
            else if(typeid(*Item) == typeid(Rifle)){
                for(int i = 0; i < Items.size(); i++){
                    if(typeid(*Items[i].first) == typeid(Rifle))
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                    }
                    else if(typeid(*Items[i].first) != typeid(Shotgun) && typeid(*Items[i].first) != typeid(Snipe)
                    && typeid(*Items[i].first) != typeid(SMG)){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                    }
                }
            }
            else if(typeid(*Item) == typeid(ColdWeapon)){
                for(int i = 0; i < Items.size(); i++){
                    if(typeid(*Items[i].first) == typeid(ColdWeapon))
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                    }
                    else if(typeid(*Items[i].first) != typeid(Gun)){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                    }
                }
            }
            else if(typeid(*Item) == typeid(Grenade)){
                for(int i = 0; i < Items.size(); i++){
                    if(typeid(*Items[i].first) == typeid(Grenade))
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                    }
                    else if(typeid(*Items[i].first) != typeid(Gun) && typeid(*Items[i].first) != typeid(ColdWeapon)){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                    }
                }
            }
            else if(typeid(*Item) == typeid(BoomRang)){
                for(int i = 0; i < Items.size(); i++){
                    if(typeid(*Items[i].first) == typeid(BoomRang))
                        if(Items[i].first->getName()>=Item->getName()){
                            Items.insert(Items.begin()+ i , make_pair(Item , 1));
                            break;
                    }
                    else if(typeid(*Items[i].first) != typeid(Gun) && typeid(*Items[i].first) != typeid(ColdWeapon) &&
                    typeid(*Items[i].first) != typeid(Grenade)){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                    }
                }
            }
            else if(typeid(*Item) == typeid(Consumable)){
                for(int i = 0; i < Items.size(); i++){
                    if(typeid(*Items[i].first) == typeid(Consumable) && Items[i].first->getName() >= Item->getName()){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(typeid(*Items[i].first) == typeid(Equipment)){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                        break;
                    }
                }
            }
            else if(typeid(*Item) == typeid(Equipment)){
                for(int i = 0; i < Items.size() ; i++){
                    if(typeid(*Items[i].first) == typeid(Equipment) && Items[i].first->getName() >= Item->getName()){
                        Items.insert(Items.begin()+ i , make_pair(Item , 1));
                        break;
                    }
                    else if(i == Items.size() - 1){
                        Items.push_back(make_pair(Item , 1));
                    }
                }
            }
        }
        if(Items.size() == 0){
            Items.push_back(make_pair(Item , 1));
        }
        BackPackWeight += Item->getCapacity();
        if(typeid(*Item) == typeid(Weapon))
            addWeapon(dynamic_cast<Weapon *>(Item));
        else if(typeid(*Item) == typeid(Equipment))
            addEquipment(dynamic_cast<Equipment *>(Item));
        else if(typeid(*Item) == typeid(Consumable))
            addConsumable(dynamic_cast<Consumable *>(Item));
    }
    else
        cout << "You can't handle this";
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
    if(typeid(*Item) == typeid(Weapon))
        removeWeapon(dynamic_cast<Weapon *>(Item));
    else if(typeid(*Item) == typeid(Equipment))
        removeEquipment(dynamic_cast<Equipment *>(Item));
    else if(typeid(*Item) == typeid(Consumable))
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
    if(typeid(*Weapon) != typeid(Gun))
        for(int i = 0; i < Weapons.size(); i++)
            if(*Weapon == *Weapons[i].first){
                Weapons[i].second++;
                isAdded = true;
                break;
            }
    //if not, inserts the weapon in
    if(!isAdded){
        if(typeid(*Weapon) == typeid(Shotgun)){
            for(int i = 0; i < Weapons.size(); i++){
                if(typeid(*Weapons[i].first) == typeid(Shotgun))
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                }
                else if(typeid(*Weapons[i].first) != typeid(Shotgun)){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                else if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                }
            }
        }
        else if(typeid(*Weapon) == typeid(Snipe)){
            for(int i = 0; i < Weapons.size(); i++){
                if(typeid(*Weapons[i].first) == typeid(Snipe))
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                }
                else if(typeid(*Weapons[i].first) != typeid(Shotgun)){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                else if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                }
            }
        }
        else if(typeid(*Weapon) == typeid(SMG)){
            for(int i = 0; i < Weapons.size(); i++){
                if(typeid(*Weapons[i].first) == typeid(SMG))
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                    }
                else if(typeid(*Weapons[i].first) != typeid(Shotgun) && typeid(*Weapons[i].first) != typeid(Snipe)){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                else if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                }
            }
        }
        else if(typeid(*Weapon) == typeid(Rifle)){
            for(int i = 0; i < Weapons.size(); i++){
                if(typeid(*Weapons[i].first) == typeid(Rifle))
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                }
                else if(typeid(*Weapons[i].first) != typeid(Shotgun) && typeid(*Weapons[i].first) != typeid(Snipe)
                && typeid(*Weapons[i].first) != typeid(SMG)){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                else if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                }
            }
        }
        else if(typeid(*Weapon) == typeid(ColdWeapon)){
            for(int i = 0; i < Weapons.size(); i++){
                if(typeid(*Weapons[i].first) == typeid(ColdWeapon))
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                    }
                else if(typeid(*Weapons[i].first) != typeid(Gun)){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                else if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                }
            }
        }
        else if(typeid(*Weapon) == typeid(Grenade)){
            for(int i = 0; i < Weapons.size(); i++){
                if(typeid(*Weapons[i].first) == typeid(Grenade))
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                }
                else if(typeid(*Weapons[i].first) != typeid(Gun) && typeid(*Weapons[i].first) != typeid(ColdWeapon)){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                else if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
                }
            }
        }
        else if(typeid(*Weapon) == typeid(BoomRang)){
            for(int i = 0; i < Weapons.size(); i++){
                if(typeid(*Weapons[i].first) == typeid(BoomRang))
                    if(Weapons[i].first->getName()>=Weapon->getName()){
                        Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                        break;
                }
                else if(typeid(*Weapons[i].first) != typeid(Gun) && typeid(*Weapons[i].first) != typeid(ColdWeapon) &&
                typeid(*Weapons[i].first) != typeid(Grenade)){
                    Weapons.insert(Weapons.begin()+ i , make_pair(Weapon , 1));
                    break;
                }
                else if(i == Weapons.size() - 1){
                    Weapons.push_back(make_pair(Weapon , 1));
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
    if(typeid(*Equipment) == typeid(HeadGear)){
        if(Equipments[0] != nullptr)
            removeItem(Equipments[0]);
        Equipments[0] = Equipment;
    }
    else if(typeid(*Equipment) == typeid(Vest)){
        if(Equipments[1] != nullptr)
            removeItem(Equipments[1]);
        Equipments[1] = Equipment;
    }
    else if(typeid(*Equipment) == typeid(FootWear)){
        if(Equipments[2] != nullptr)
            removeItem(Equipments[2]);
        Equipments[2] = Equipment;
    }
    else if(typeid(*Equipment) == typeid(Boot)){
        if(Equipments[3] != nullptr)
            removeItem(Equipments[3]);
        Equipments[3] = Equipment;
    }
}

void Player :: removeEquipment(Equipment* Equipment){ //removes the equipment if you sell or lose it, from the Equipments' vector
    setArmor(getArmor() - Equipment->getAmount());
    if(typeid(*Equipment) == typeid(HeadGear))
        Equipments[0] = nullptr;
    else if(typeid(*Equipment) == typeid(Vest))
        Equipments[1] = nullptr;
    else if(typeid(*Equipment) == typeid(FootWear))
        Equipments[2] = nullptr;
    else if(typeid(*Equipment) == typeid(Boot))
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
            else if(i == Consumables.size() - 1){
                Consumables.push_back(make_pair(Consumable , 1));
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

void HumanEnemy :: RajazKhani(){
    vector<string> curse ={"MOTHER FUCKER" , "BITCH" , "Asshole" };
    string RajazKhani = "Got u, " + ShuffleVec(curse)[0];
    vector<string> Rajaz = {RajazKhani , "Loser" , "Almost there!" , "You think you can defeat me? Pathetic!" , 
        "I'll crush you like a bug!" , "You're nothing but a stain on the battlefield!"};
    if (rand() % 5 == 0){ // There is a 1/5 chance that human enemy insult the player befor attacking him/her
        cout << ShuffleVec(Rajaz)[0];
    }
}

HumanEnemy :: HumanEnemy(string Name ,int HP , int MaxHP , double Armor , int Shield , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon* , int>> , vector<Equipment*> Equipments , vector<pair<Consumable* , int>> Consumables)
    : Character(Name , HP , MaxHP , Armor , Shield , Items , Weapons){
    this->Consumables = Consumables;
    this->Equipments = Equipments;
}

HumanEnemy :: ~HumanEnemy(){
    // What the enemy says when he/she dies
    vector<string> EnemyDeathQuotes = { "I can't believe this is how it all ends!", "You fucking bastard!",
    "Wasted!" , "Nooo, I can't die yet!" , "My child , take care o..." , "I'll damn you" , 
    "My brother will get my revenge!!!" , "I'll be waiting , you SoB!!!" , "That was a fun fight" , 
    "See you on the other side"};
    cout << ShuffleVec(EnemyDeathQuotes)[0];
}

void HumanEnemy::Attack(vector<Character*> characters , Weapon* weapon , int choice){
    if (typeid(*weapon) == typeid(Gun)) {
        Gun *gun = dynamic_cast<Gun *>(weapon);
        if (gun->getAmmo() >= gun->getAmmoNeeded()) {
            gun->Attack(characters);
            gun->setAmmo(gun->getAmmo()-gun->getAmmoNeeded()); //reduces the number of ammos after the gun shot.
        }
    }
    else if(typeid(*weapon) == typeid(Throwable)){
        Throwable *throwable = dynamic_cast<Throwable *>(weapon);
        throwable->Attack(characters);
        removeItem(throwable); //removes the throwable from the backpack after it dropped
    }
    else if(typeid(*weapon) == typeid(ColdWeapon)){
        ColdWeapon *coldWeapon = dynamic_cast<ColdWeapon *>(weapon);
        if(choice ==1){
            coldWeapon->Attack(characters); //if attack, it calls the Attack function of the cold weapon
        }
        else{
            coldWeapon->Throw(characters); //if throw, it calls the Throw function of the cold weapon then removes it from the backpack
            removeItem(coldWeapon); 
        }
    }
    else{
        weapon->Attack(characters);
    }
    RajazKhani();
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

void HumanEnemy :: removeItem(Item* Item){ //deletes the items considering their numbers 
    for (int i = 0; i < Items.size(); i++){
        if (*Item == *Items[i].first){
            if(Items[i].second == 1)
                Items.erase(Items.begin()+i);
            else
                Items[i].second--;
        }
    }
    if(typeid(*Item) == typeid(Weapon))
        removeWeapon(dynamic_cast<Weapon *>(Item));
    else if(typeid(*Item) == typeid(Consumable))
        removeConsumable(dynamic_cast<Consumable *>(Item));
}


Zombie :: Zombie(string Name , int HP , int MaxHP , double Armor , int Shield , vector<pair<Item* , int>> Items
, vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipments)
: Character(Name , HP , MaxHP , Armor , Shield , Items , Weapons){
    this-> Equipments = Equipments;
}

Zombie :: ~Zombie(){
    vector<string> ZombieDeathQuotes = {"Aaauugh!!!!" , "Haaauugh!!!" , "Blauugh!" , "Guaargh!!" , "Bluargh!!!"};
    cout << ShuffleVec(ZombieDeathQuotes)[0];
}

void Zombie :: Attack(vector<Character*> &player , Punch* punch){
    punch->Attack(player);
}

Shopkeeper :: Shopkeeper(string Name){this->Name = Name;}

string Shopkeeper :: getName(){return Name;}

void Shopkeeper :: HiDialogue(){ //The shopkeeper says hi
    vector<string> ShopkeeperHi = {"Salute soldier! How can I help?" , "Hi commander! Is there anything I can provide?" , "Welcome to my shop!"};
    cout << ShuffleVec(ShopkeeperHi)[0] << endl;
}

void Shopkeeper :: ByeDialogue(){ //The shopkeeper says bye
    cout << "Good luck , Soldier." << endl;
}

void Shopkeeper :: SellDialogue(Item* item){ //The shopkeeper sells sth to the player
    vector<string> ShopkeeperSell = {"So you've bought " + item->getName() , "You choosed one of the best items." ,
    "Wish " + item->getName() + "helps you survive."};
    cout << ShuffleVec(ShopkeeperSell)[0];
} // items to be included

void Shopkeeper :: BuyDialogue(Item* item){ //The shopkeeper buys sth from the player
    double NewPrice = 0.8*item->getPrice();
    cout << "I'll buy that for " << to_string(NewPrice) << " coins.\n";
} // items to be included

void Shopkeeper :: NoMoneyDialogue(){ // What the shopkeeper says when the player has less money than the item's price
    vector<string> PoorSoldier = {"You don't have enough coins!" , "Poor soldier!!!" , "Can't get you that!" ,
    "So little for so much?!" , "..." , "You don't have enough coins!" , "Poor soldier!!!" , 
    "Can't get you that!" , "So little for so much?!"};
    cout << ShuffleVec(PoorSoldier)[0];
}

Medic :: Medic(string Name){this->Name = Name;}

string Medic :: getName(){return Name;}

void Medic :: HiDialogue(){
    vector<string> MedicSayHi = {"Hi, Soldier." , "Salute soldier! How can I help?" , "Hi commander! Are you hurt somewhere?"};
    cout << ShuffleVec(MedicSayHi)[0];
}

void Medic :: ByeDialogue(){cout << "Have a safe journy.";}

void Medic :: HealDialogue(){cout << "I've patched you up!";}

void Medic :: NoMoneyDialogue(){
    vector<string> PoorSoldier = {"You don't have enough coins!" , "Poor soldier!" , "Can't Heal you with that much coin!" , 
    "So little for so much?!" , "..." , "You don't have enough coins!" , "Poor soldier!!!" , 
    "Can't heal you with that much coin" , "So little for so much?!"};
    cout << ShuffleVec(PoorSoldier)[0];
}

void Medic :: Heal(Player player){
    player.setHP(min(player.getMaxHP() , (int)(player.getHP() + player.getMaxHP() * 0.5)));
    HealDialogue();
}

void Medic :: MaxHPIncrease(Player player){
    player.setMaxHP((int)player.getMaxHP() * 1.1);
    HealDialogue();
}
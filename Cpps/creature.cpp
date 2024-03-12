#include "../Headers/creature.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <string>
#include <typeinfo>
using namespace std;

vector<string> ShuffleVec(vector<string> vec){
    random_device rd;
    default_random_engine abs(rd());
    shuffle(vec.begin(), vec.end(), abs);
    return vec;
}

Character :: Character(int HP , int MaxHP , int Armor , int Shield ,
vector<pair<Item* , int>> Items , vector<pair<Weapon* , int>> Weapons){
    this -> HP = HP;
    this -> MaxHP = MaxHP;
    this -> Armor = Armor;
    this -> Shield = Shield;
    this -> Items = Items;
    this -> Weapons = Weapons;
    this -> Equipments = {{nullptr} , {nullptr} , {nullptr} , {nullptr}};
}

int Character :: getHP(){return HP;}

void Character :: setHP(int HP){this -> HP = HP;}

int Character :: getMaxHP(){return MaxHP;}

void Character :: setMaxHP(int MaxHP){this -> MaxHP = MaxHP;}

int Character :: getArmor(){return Armor;}

void Character :: setArmor(double Armor){this -> Armor = Armor;}

void Character :: setShield(int Shield){this->Shield = Shield;}

int Character :: getShield(){return Shield;}

void Character :: takeDamage(int damagetaken){
    if(Shield>=damagetaken){
        Shield -= damagetaken;
        damagetaken = 0;
    }
    else{
        damagetaken -= Shield;
        Shield = 0;
    }
    setHP(getHP() - (int) (damagetaken * (100 - Armor) / 100));
}

vector<pair<Item* , int>> Character :: getItems(){return Items;}

vector<pair<Weapon* , int>> Character :: getWeapons(){return Weapons;}

vector<Equipment*> Character :: getEquipments(){return Equipments;}

Player :: Player(string Name, int HP, int MaxHP, double Armor, int BackPackCapacity , int BackPackWeight
, int MaxEnergy , int Coin , int Shield ,vector<pair<Item* , int>> Items
, vector<pair<Weapon* , int>> Weapons) : Character
(HP , MaxHP , Armor , Shield , Items ,  Weapons){
    this -> Name = Name;
    this -> BackPackCapacity = BackPackCapacity;
    this -> BackPackWeight = BackPackWeight;
    this -> MaxEnergy = MaxEnergy;
    this -> Coin = Coin;
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

void Player :: addItem(Item* item){
    if(BackPackWeight + item->getCapacity() <= BackPackCapacity){
        bool IsAdded = false;
        for(int i = 0; i < Items.size(); i++)
            if(*Items[i].first== *item){
                Items[i].second++;
                IsAdded = true;
                break;
            }
        if(!IsAdded)
            Items.push_back(make_pair(item , 1));
        BackPackWeight += item->getCapacity();
    }
    else
        cout << "You can't handle this";
}

void Player :: removeItem(Item* Item){
    for (int i = 0; i < Items.size(); i++)
    {
        if (*Item == *Items[i].first)
        {
            BackPackWeight -= Items[i].first->getCapacity();
            if(Items[i].second == 1){
                Items.erase(Items.begin()+i); //this may still consume some Bytes
            }
            else
                Items[i].second--;
        }   
    }
}

vector<Relic*> Player :: getRelic(){return Relics;}

void Player :: addRelic(Relic* Relic){
    
    Relics.push_back(Relic);
    addItem(Relic);
}

void Player :: addWeapon(Weapon* Weapon){
    bool isAdded = false;
    for(int i = 0; i < Weapons.size(); i++){
        if(*Weapon == *Weapons[i].first){
            Weapons[i].second++;
            isAdded = true;
            break;
        }
    }
    if(!isAdded)
        Weapons.push_back(make_pair(Weapon , 1));
    addItem(Weapon);
}

void Player :: removeWeapon(Weapon* Weapon){
    for(int i = 0; i < Weapons.size(); i++){
        if(*Weapons[i].first == *Weapon){
            if(Weapons[i].second == 1)
                Weapons.erase(Weapons.begin()+ i);
            else
                Weapons[i].second--;
        }
    }
    removeItem(Weapon);
}

void Player :: addEquipment(Equipment* Equipment){
    
}

void Player :: removeEquipment(Equipment* Equipment){
    setArmor(getArmor() - Equipment->getAmount());
    if(typeid(Equipment) == typeid(HeadGear))
        Equipments[0] = nullptr;
    else if(typeid(Equipment) == typeid(Vest))
        Equipments[1] = nullptr;
    else if(typeid(Equipment) == typeid(FootWear))
        Equipments[2] = nullptr;
    else if(typeid(Equipment) == typeid(Boot))
        Equipments[3] = nullptr;
    removeItem(Equipment);
}

vector<pair<Consumable* , int>> Player :: getConsumables(){return Consumables;}

void Player :: addConsumable(Consumable* Consumable){
    bool isAdded = false;
    for(int i = 0; i < Consumables.size(); i++){
        if(*Consumable == *Consumables[i].first){
            Consumables[i].second++;
            isAdded = true;
            break;
        }
    }
    if(!isAdded)
        Consumables.push_back(make_pair(Consumable , 1));
    addItem(Consumable);
}

void Player :: removeConsumable(Consumable* Consumable){
    for(int i = 0; i < Consumables.size(); i++){
        if(*Consumables[i].first == *Consumable){
            if(Consumables[i].second == 1)
                Consumables.erase(Consumables.begin()+ i);
            else
                Consumables[i].second--;
        }
    }
    removeItem(Consumable);
}

void Player :: Consume(Consumable* Consumable){
    if(typeid(Consumable) == typeid(ShieldPotion)){
        setShield(getShield() + Consumable->getAmount());
        removeConsumable(Consumable);
    }
    else if(typeid(Consumable) == typeid(HealingItem)){
        setHP(min(getMaxHP() , getHP() + Consumable->getAmount()));
        removeConsumable(Consumable);
    }
    else if(typeid(Consumable) == typeid(Energizer)){
        setEnergy(min(MaxEnergy , Energy + Consumable->getAmount()));
        removeConsumable(Consumable);
    }
}
string HumanEnemy :: getName(){return Name;}

HumanEnemy :: HumanEnemy(int HP , int MaxHP , double Armor , string Name, int Shield , vector<pair<Item* , int>> Items ,
vector<pair<Weapon* , int>> , vector<Equipment*> Equipments , vector<pair<Consumable* , int>> Consumables)
: Character(HP , MaxHP , Armor , Shield , Items , Weapons){
    this->Name = Name;
    this->Consumables = Consumables;
    this->Equipments = Equipments;
}

void HumanEnemy :: removeConsumable(Consumable* Consumable){
    for(int i = 0; i < Consumables.size(); i++){
        if(*Consumables[i].first == *Consumable){
            if(Consumables[i].second == 1)
                Consumables.erase(Consumables.begin()+ i);
            else
                Consumables[i].second--;
        }
    }
    removeItem(Consumable);
}

void HumanEnemy :: Consume(Consumable* Consumable){
    if(typeid(Consumable) == typeid(ShieldPotion)){
        setShield(getShield() + Consumable->getAmount());
        removeConsumable(Consumable);
    }
    else if(typeid(Consumable) == typeid(HealingItem)){
        setHP(min(getMaxHP() , getHP() + Consumable->getAmount()));
        removeConsumable(Consumable);
    }
}

// void HumanEnemy :: Attack(Player player){}

HumanEnemy :: ~HumanEnemy(){
    vector<string> EnemyDeathQuotes = { "I can't believe this is how it all ends!", "You fucking bastard!", "Wasted!", 
    "Nooo, I can't die yet!" , "My child , take care o..." , "I'll damn you" , "My brother will get my revenge!!!" , "I'll be waiting , you SoB" , 
    "That was a fun fight" , "See you on the other side"};
    cout << ShuffleVec(EnemyDeathQuotes)[0];
    
}

//void HumanEnemy :: Consume(Consumable* consumable){}

void HumanEnemy :: removeItem(Item* Item){
    for (int i = 0; i < Items.size(); i++){
        if (*Item == *Items[i].first){
            if(Items[i].second == 1)
                Items.erase(Items.begin()+i);
            else
                Items[i].second--;
        }
    }
}


void HumanEnemy :: RajazKhani(){
    vector<string> curse ={"MOTHER FUCKER" , "BITCH" , "Asshole" };
    string RajazKhani = "Got u, " + ShuffleVec(curse)[0];
    vector<string> Rajaz = {RajazKhani , "Loser" , "Almost there!" , ""};
    if (rand() % 5 == 0){
        cout << ShuffleVec(Rajaz)[0];
    }
}

Zombie :: Zombie(int HP , int MaxHP , double Armor , string Type , int Shield , vector<pair<Item* , int>> Items 
, vector<pair<Weapon* , int>> Weapons , vector<Equipment*> Equipments)
: Character(HP , MaxHP , Armor , Shield , Items , Weapons){
    this-> Type = Type; 
    this-> Equipments = Equipments;
}

Zombie :: ~Zombie(){
    vector<string> ZombieDeathQuotes = {"Aaauugh!!!!" , "Haaauugh!!!" , "Blauugh!" , "Guaargh!!" , "Bluargh!!!"};
    cout << ShuffleVec(ZombieDeathQuotes)[0];
}

string Zombie :: getType(){return Type;}

// void Zombie :: Attack(Player player){}

Shopkeeper :: Shopkeeper(string Name){this->Name = Name;}

string Shopkeeper :: getName(){return Name;}

void Shopkeeper :: HiDialogue(){
    vector<string> ShopkeeperHi = {"Salute soldier! How can I help?" , "Hi commander! Is there anything I can provide?" , "Welcome to my shop!"};
    cout << ShuffleVec(ShopkeeperHi)[0] << endl;
}

void Shopkeeper :: ByeDialogue(){
    cout << "Good luck , Soldier." << endl;
}

void Shopkeeper :: SellDialogue(Item* item){
    vector<string> ShopkeeperSell = {"So you bought " + item->getName() , "You choosed one of the best items." ,
    "Wish " + item->getName() + "help you survive."};
    cout << ShuffleVec(ShopkeeperSell)[0];
} // items to be included

void Shopkeeper :: BuyDialogue(Item* item){
    double NewPrice = 0.8*item->getPrice();
    cout << "I'll buy that for " << to_string(NewPrice) << " coins.\n"; 
} // items to be included

void Shopkeeper :: NoMoneyDialogue(){
    vector<string> PoorSoldier = {"You don't have enough coins!" , "Poor soldier!!!" , "Can't get you that!" , "So little for so much?!" , "..." ,
    "You don't have enough coins!" , "Poor soldier!!!" , "Can't get you that!" , "So little for so much?!"};
    cout << ShuffleVec(PoorSoldier)[0];
}

Medic :: Medic(string Name){this->Name = Name;}

string Medic :: getName(){return Name;}

void Medic :: HiDialogue(){
    vector<string> MedicSayHi = {"Hi, Soldier." , "Salute soldier! How can I help?" , "Hi commander! Are you hurt anywhere?"};
    cout << ShuffleVec(MedicSayHi)[0];
}

void Medic :: ByeDialogue(){cout << "Have a safe journy.";}

void Medic :: HealDialogue(){cout << "I've patched you up!";}

void Medic :: NoMoneyDialogue(){
    vector<string> PoorSoldier = {"You don't have enough coins!" , "Poor soldier!" , "Can't Heal you with that much coin!" , "So little for so much?!" , "..." ,
    "You don't have enough coins!" , "Poor soldier!!!" , "Can't heal you with that much coin" , "So little for so much?!"};
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
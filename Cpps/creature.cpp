#include "../Headers/creature.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <string>
using namespace std;

string ShuffleQuotes(vector<string> QuotesGenerator){
    int i = rand() % QuotesGenerator.size();
    return QuotesGenerator[i];
} 
Player :: Player(string Name, int HP, int MaxHP, double Armor, int BackPackCapacity , int BackPackWeight , int Energy , int Coin , int Shield ,vector<pair<Item* , int>> Items , vector<Relic*> Relics){
    this -> Name = Name;
    this -> HP = HP;
    this -> MaxHP = MaxHP;
    this -> Armor = Armor;
    this -> BackPackCapacity = BackPackCapacity;
    this -> BackPackWeight = BackPackWeight;
    this -> Energy = Energy;
    this -> Coin = Coin;
    this -> Shield = Shield;
    this -> Items = Items;
    this -> Relics = Relics;
} 

Player :: ~Player(){
    cout << "Not good enough" << endl << "Defeated!!!" << endl << "Welcome to HELLMOS";
}

// void Player :: Attack(Enemy* enemy){} // to be filled

void Player :: takeDamage(int damagetaken){
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

void Player :: setHP(int HP){this -> HP = HP;}

int Player :: getHP(){return HP;}

void Player :: setMaxHP(int MaxHP){this -> MaxHP = MaxHP;}

int Player :: getMaxHP(){return MaxHP;}

void Player :: setArmor(double Armor){this -> Armor = Armor;}

int Player :: getArmor(){return Armor;}

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

void Player :: setShield(int Shield){this->Shield = Shield;}

int Player :: getShield(){return Shield;}

vector<pair<Item* , int>> Player :: getItem(){return Items;}

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

void Player :: removeItem(Item* item){
    for (int i = 0; i < Items.size(); i++)
    {
        if (item->getName() == Items[i].first->getName())
        {
            BackPackWeight -= Items[i].first->getCapacity();
            if(Items[i].second == 1)
                Items.erase(Items.begin()+i);
            else
                Items[i].second--;
        }   
    }
}

vector<Relic*> Player :: getRelic(){return Relics;}

void Player :: addRelic(Relic* relic){
    // relic usage to be added
    Relics.push_back(relic);
}

vector<Weapon*> Player :: getWeapons(){return weapons;}

void Player :: addWeapon(Weapon* Weopon){
    // relic usage to be added
    weapons.push_back(Weopon);
}


Enemy :: Enemy(int HP , int MaxHP , double Armor , Item* item , int Shield){
    this->HP = HP;
    this->MaxHP = MaxHP;
    this->Armor = Armor;
    this->item = item;
    this->Shield = Shield; 
}

void Enemy :: takeDamage(int damagetaken){setHP(getHP() - damagetaken * (100 - Armor) / 100);}

void Enemy :: setHP(int HP){this -> HP = HP;}

int Enemy :: getHP(){return HP;}

void Enemy :: setMaxHP(int MaxHP){this -> MaxHP = MaxHP;}

int Enemy :: getMaxHP(){return MaxHP;}

void Enemy :: setArmor(double Armor){this -> Armor = Armor;}

int Enemy :: getArmor(){return Armor;}

void Enemy :: setShield(int shield){this -> Shield = Shield;}

int Enemy :: getShield(){return Shield;}

string HumanEnemy :: getName(){return Name;}

HumanEnemy :: HumanEnemy(int HP , int MaxHP , double Armor , string Name , Item* item , int Shield) : 
Enemy(HP , MaxHP , Armor , item , Shield){this->Name = Name;}

// void HumanEnemy :: Attack(Player player){}

HumanEnemy :: ~HumanEnemy(){
    vector<string> EnemyDeathQuotes = { "I can't believe this is how it all ends!", "You fucking bastard!", "Wasted!", 
    "Nooo, I can't die yet!" , "My child , take care o..." , "I'll damn you" , "My brother will get my revenge!!!" , "I'll be waiting , you SoB" , 
    "That was a fun fight" , "See you on the other side"};
    cout << ShuffleQuotes(EnemyDeathQuotes);
    
}

//void HumanEnemy :: Consume(Consumable* consumable){}

void HumanEnemy :: removeItem(Item* item){
    for (int i = 0; i < items.size(); i++)
    {
        if (item == items[i])
        {
            items.erase(items.begin() + i);
        }
    }
}

void HumanEnemy :: RajazKhani(){
    vector<string> curse ={"MOTHER FUCKER" , "BITCH" , "Asshole" };
    string RazajKhani = "Got u, " + ShuffleQuotes(curse);
    vector<string> Rajaz = {RajazKhani , "Loser" , "Almost there!" , ""};
    if (rand() % 5 == 0)
    {
        cout << ShuffleQuotes(Rajaz);
    }
}

Zombie :: Zombie(int HP , int MaxHP , double Armor , string Type , Item* item , int Shield): Enemy(HP , MaxHP , Armor , item , Shield){
    this-> Type = Type; 
}

Zombie :: ~Zombie(){
    vector<string> ZombieDeathQuotes = {"Aaauugh!!!!" , "Haaauugh!!!" , "Blauugh!" , "Guaargh!!" , "Bluargh!!!"};
    ShuffleQuotes(ZombieDeathQuotes);
}

string Zombie :: getType(){return Type;}

// void Zombie :: Attack(Player player){}

Shopkeeper :: Shopkeeper(string Name){this->Name = Name;}

string Shopkeeper :: getName(){return Name;}

void Shopkeeper :: HiDialogue(){
    vector<string> ShopkeeperHi = {"Salute soldier! How can I help?" , "Hi commander! Is there anything I can provide?" , "Welcome to my shop!"};
    cout << ShuffleQuotes(ShopkeeperHi) << endl;
}

void Shopkeeper :: ByeDialogue(){
    cout << "Good luck , Soldier." << endl;
}

void Shopkeeper :: SellDialogue(Item* item){
    vector<string> ShopkeeperSell = {"So you bought " + item->getName() , "You choosed one of the best items." ,
     "Wish " + item->getName() + "make you win.";}
} // items to be included

void Shopkeeper :: BuyDialogue(Item* item){
    double NewPrice = 0.8*item->getPrice();
    vector ShopkeeperBuy = {"I can buy that for"};
} // items to be included

void Shopkeeper :: NoMoneyDialogue(){
    vector<string> PoorSoldier = {"You don't have enough coins!" , "Poor soldier!!!" , "Can't get you that!" , "So little for so much?!" , "..." ,
    "You don't have enough coins!" , "Poor soldier!!!" , "Can't get you that!" , "So little for so much?!"};
    cout << ShuffleQuotes(PoorSoldier);
}

Medic :: Medic(string Name){this->Name = Name;}

string Medic :: getName(){return Name;}

void Medic :: HiDialogue(){
    vector<string> MedicSayHi = {"Hi, Soldier." , "Salute soldier! How can I help?" , "Hi commander! Are you hurt anywhere?"};
    cout << ShuffleQuotes(MedicSayHi);
}

void Medic :: ByeDialogue(){cout << "Have a safe journy.";}

void Medic :: HealDialogue(){cout << "I've patched you up!";}

void Medic :: NoMoneyDialogue(){
    vector<string> PoorSoldier = {"You don't have enough coins!" , "Poor soldier!" , "Can't Heal you with that much coin!" , "So little for so much?!" , "..." ,
    "You don't have enough coins!" , "Poor soldier!!!" , "Can't heal you with that much coin" , "So little for so much?!"};
    cout << ShuffleQuotes(PoorSoldier);
}

void Medic :: Heal(Player player){
    player.setHP(min(player.getMaxHP() , (int)(player.getHP() + player.getMaxHP() * 0.5)));
    HealDialogue();
}

void Medic :: MaxHPIncrease(Player player){
    player.setMaxHP((int)player.getMaxHP() * 1.1);
}
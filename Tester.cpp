#include "Headers/items.h"
#include "Headers/creature.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

vector<string> ShuffleVec(vector<string> vec){
    random_device rd;
    default_random_engine rng(rd());
    shuffle(vec.begin(), vec.end(), rng);
    return vec;
}

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

void check_attack(){
    Weapon* weapon = new Snipe("sniper",5,20,20,4,2);
    vector<pair<Item*,int>> items = {make_pair(weapon,1)};
    vector<pair<Weapon* , int>> Weapons = {make_pair(weapon,1)};
    vector<Equipment*> Equipments;
    Player* player = new Player("O",100,100,0,100,0,100,40,50,items,weapons,Equipments);
    HumanEnemy* enemy = new HumanEnemy(30,30,0,"enemy1",0,items,Weapons,Equipments,Weapons,)
}

int main(){
    
}
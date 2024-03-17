#include "Headers/creature.h"
#include "Headers/items.h"
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

void check_dialogues(){
    Shopkeeper shopkeeper1("Ali");
    Weapon* weapon = new Snipe("sniper",5,20,20,4,2,8);
    Consumable*  consumable = new Consumable("hiHPPoition" , "HPPotion" , 1 , 10 , 30); 
    vector<pair<Item*,int>> items = {make_pair(consumable , 1),make_pair(weapon,1)};
    vector<pair<Weapon* , int>> weapons = {make_pair(weapon,1)};
    vector<pair<Consumable* , int>> consumables = {make_pair(consumable , 1)};
    Vest* vest = new Vest("vest" , 60 , 60 , 10);
    vector<Equipment*> equipments = {vest};
    Player* player1 = new Player("O", 100, 100, 0, 100, 0, 100, items, weapons, consumables, equipments);
    cout << "Shopkeeper's Dialogues: " << endl;
    cout << "Shopkeeper says hi: ";
    shopkeeper1.HiDialogue();
    cout << "The shopkeeper sells you sth: ";
    shopkeeper1.SellDialogue(weapon);
    cout << "If you have less coins than the item's price, the shopkeeper says: ";
    shopkeeper1.NoMoneyDialogue();
    cout << "The shopkeeper buys sth from you: ";
    shopkeeper1.BuyDialogue(weapon);
    cout << "Shopkeeper say bye: ";
    shopkeeper1.ByeDialogue();
    cout << "Now a human enemy wants to rajaz: " << endl;
    HumanEnemy enemy1("O", 100, 100, items, weapons, equipments, consumables);
    enemy1.RajazKhani();
    Medic medic1("B");
    cout << "Medic's Dialogues: " << endl;
    cout << "Medic says hi: ";
    medic1.HiDialogue();
    cout << "If you don't have enough money, the medic says: ";
    medic1.NoMoneyDialogue();
    cout << "If he/she heals you: ";
    medic1.HealDialogue();
    cout << "The medic says bye: ";
    medic1.ByeDialogue();
}
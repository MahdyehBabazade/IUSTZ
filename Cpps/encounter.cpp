#include "../Headers/encounter.h"
#include <iostream>


Shop :: Shop(Player* player, vector<Weapon*> weapons, vector<Consumable*> consumables, vector<Equipment*> equipments, Shopkeeper* shopkeeper){

    this -> player = player;
    this -> weapons = weapons;
    this -> consumables = consumables;
    this -> equipments = equipments;
    this -> shopkeeper = shopkeeper;
}

vector<Weapon*> Shop :: getWeapons(){return weapons;}

vector<Consumable*> Shop :: getConsumables(){return consumables;}

vector<Equipment*> Shop :: getEquipments(){return equipments;}

void Shop :: Sell(Item* item){

    if (player->getCoin() >= item->getPrice()){
        player->removeCoin(item->getPrice());
        player->addItem(item);
        cout << shopkeeper->SellDialogue(item);
    }
    else{
        cout << shopkeeper->NoMoneyDialogue();
    }
}

void Shop :: Buy(Item* item){
    player->removeItem(item);
    shopkeeper->BuyDialogue(item);
}

void Shop :: menu(){
    shopkeeper->HiDialogue();
    while (true)
    {
        cout << " \n 1. Buy \n"
                "2. Sell \n"
                "3. Upgrade \n";
    }
}
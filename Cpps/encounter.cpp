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

void Shop :: Sell(Item* item){ // Shopkeeper sells, Player buys

    if (player->getCoin() >= item->getPrice()){
        player->removeCoin(item->getPrice());
        player->addItem(item);
        cout << shopkeeper->SellDialogue(item);
    }
    else{
        cout << shopkeeper->NoMoneyDialogue();
    }
}

void Shop :: Buy(Item* item){ // Shopkeeper buys, Player sells
    
    player->removeItem(item);
    shopkeeper->BuyDialogue(item);
}

void Shop :: Menu(){
    shopkeeper->HiDialogue();
    while (true)
    {
        cout << " \n 1. Buy \n" // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                "2. Sell \n"
                "3. Upgrade \n"
                "4. Exit";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "1. Weapons" << endl;
            cout << "2. Consumables" << endl;
            cout << "3. Equipments" << endl;
            int choice1;
            cin >> choice1;
            switch (choice1)
            {
            case 1:
                for (int i = 0; i < weapons.size(); i++)
                {
                    cout << i+1 << ". " << weapons[i]->getName() << endl;
                }
                int chosenWeapon;
                cin >> chosenWeapon;
                Sell(weapons[chosenWeapon-1]);
            case 2:
                for (int i = 0; i < consumables.size(); i++)
                {
                    cout << i+1 << ". " << consumables[i]->getName() << endl;
                }
                int chosenConsumable;
                cin >> chosenConsumable;
                Sell(consumables[chosenConsumable-1]);
                break;
            case 3:
                for (int i = 0; i < equipments.size(); i++)
                {
                    cout << i+1 << equipments[i]->getName() << endl;
                }
                int chosenEquiment;
                cin >> chosenEquiment;
                Sell(equipments[chosenEquiment-1]);
                break;
            
            default:
                break;
            }   

        case 2:
            for (int i = 0; i < player->getItems().size(); i++)
            {
                cout << i+1 << ". " << player->getItems()[i].first->getName() << " " << player->getItems()[i].second << endl;
            }
            int chosenItem;
            cin >> chosenItem;
            Buy(player->getItems()[chosenItem-1].first);
            break;

        case 3: // Can be changed later
            for (int i = 0; i < player->getItems().size(); i++)
            {
                cout << i+1 << ". " << player->getItems()[i].first->getName() << " " << player->getItems()[i].second << endl;
            }
            int chosenItem;
            cin >> chosenItem;
            Upgrade(player->getItems()[chosenItem-1].first);
            break;

        case 4:
            exit(0);
            break;
        }
    }
}
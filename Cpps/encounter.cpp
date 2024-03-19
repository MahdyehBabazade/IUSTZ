#include "../Headers/encounter.h"
#include <iostream>


Shop :: Shop(Player* player, vector<Weapon*> weapons, vector<Consumable*> consumables, vector<Equipment*> equipments, Shopkeeper* shopkeeper,string Story) : Encounter(Story){

    this -> player = player;
    this -> weapons = weapons;
    this -> consumables = consumables;
    this -> equipments = equipments;
    this -> shopkeeper = shopkeeper;
    this -> WantsToQuit = false;
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
    while (!WantsToQuit){
        cout << " \n 1. Buy \n" // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                "2. Sell \n"
                "3. Upgrade \n"
                "4. Quit";
        int choice;
        cin >> choice;
        switch (choice){
            case 1: // player buys an item
                cout << "1. Weapons" << endl;
                cout << "2. Consumables" << endl;
                cout << "3. Equipments" << endl;
                cin >> choice;
                switch (choice){
                    case 1:
                        while(true){
                            for (int i = 0; i < weapons.size(); i++){
                            cout << i+1 << ". " << weapons[i]->getName() << endl;
                            }
                            cout << "choose a weapon to buy (0 to go back): ";
                            cin >> choice;
                            if(choice == 0){
                                break;
                            }
                            Sell(weapons[choice-1]);
                        }
                        break;
                    case 2:
                        while (true){
                            for (int i = 0; i < consumables.size(); i++){
                                cout << i+1 << ". " << consumables[i]->getName() << endl;
                            }
                            cout << "choose a consumable to buy (0 to go back): ";
                            cin >> choice;
                            if(choice == 0){
                                break;
                            }
                            Sell(consumables[choice-1]);
                        }
                        break;
                    case 3:
                        while(true){
                            for (int i = 0; i < equipments.size(); i++){
                                cout << i+1 << equipments[i]->getName() << endl;
                            }
                            cout << "choose a consumable to buy (0 to go back): ";
                            cin >> choice;
                            if(choice == 0){
                                break;
                            }
                            Sell(equipments[choice-1]);
                        }
                        break;
                    default:
                        continue;
                }   
    
            case 2: // player sells an item
                while(true){
                    for (int i = 0; i < player->getItems().size(); i++){
                        cout << i+1 << ". " << player->getItems()[i].first->getName() << " " << player->getItems()[i].second << endl;
                    }
                    cout << "choose an item you want to sell (0 to go back): ";
                    cin >> choice;
                    if(choice == 0){
                        break;
                    }
                    Buy(player->getItems()[choice-1].first);   
                }
                break;
            case 3: // player upgrades a gun
                while(true){
                    for (int i = 0; i < player->getWeapons().size(); i++){
                        cout << i+1 << ". " << (player->getWeapons()[i].first)->getStat()<< endl;
                    }
                    cout << "choose a weapon you want to upgrade (0 to go back): ";
                    cin >> choice;
                    if(choice == 0){
                        break;
                    }
                    Upgrade(player->getWeapons()[choice-1].first);   
                }
                break;
            case 4: //player quits
                WantsToQuit = true;
                break;
            default:
                continue;    
        }
    }
    
}
    
Hospital :: Hospital(Player* player,Medic* medic,int MaxHpIncresePrice,int FullHealPrice,int HalfHealPrice,string Story) : Encounter(Story) {
    this->player = player;
    this->medic = medic;
    this->MaxHpIncreasePrice =MaxHpIncreasePrice;
    this->FullHealPrice = FullHealPrice;
    this->HalfHealPrice = HalfHealPrice;
    this->HasHealed = false;
};


void Hospital :: FullHeal(){
    if(player->getCoin() < FullHealPrice){
        cout << medic->NoMoneyDialogue();
        return;
    }
    player->setHP(player->getMaxHP());
    cout << medic->HealDialogue();
    HasHealed = true;
}

void Hospital ::HalfHeal(){
    if(player->getCoin() < HalfHealPrice){
        cout << medic->NoMoneyDialogue();
        return;
    }
    player->setHP(player->getHP() + (player->getMaxHP()/2));
    cout << medic->HealDialogue();
    HasHealed = true;
}

void Hospital :: MaxHpIncrease(){
    if(player->getCoin() < MaxHpIncreasePrice){
        cout << medic->NoMoneyDialogue();
        return;
    }
    player->setHP(int(player->getMaxHP()*1.2));
    cout << medic->HealDialogue();
    HasHealed = true;
}

void Hospital :: Menu(){
    cout << medic->HiDialogue();
    while(!HasHealed){
        cout << "1. Restore half HP ( " << HalfHealPrice << "$)" << endl <<
                "2. Restore full HP" << FullHealPrice << "$)" << endl <<
                "3. Increase max HP by 20%" << MaxHpIncreasePrice << "$)" << endl <<
                "4.quit" << endl <<
                "choose an option: ";
        int choice;
        cin >> choice;
        
        switch (choice){
            case 1:
                HalfHeal();
                break;
            case 2:
                FullHeal();
                break;
            case 3:
                MaxHpIncrease();
                break;
            case 4:
                break;
            default:
                continue;
        }
    }
   cout <<  medic->ByeDialogue();
}
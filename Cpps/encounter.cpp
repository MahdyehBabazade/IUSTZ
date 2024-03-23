#include "../Headers/encounter.h"
#include <iostream>
#include <random>

vector<string> ShuffleVec(vector<string> vec){ // Shuffles a vector
    random_device rd;
    default_random_engine abs(rd());
    shuffle(vec.begin(), vec.end(), abs);
    return vec;
}

Encounter :: Encounter(string Story){this -> Story = Story;}

string Encounter :: getStory(){return Story;}

Shop :: Shop(Player* player, vector<Weapon*> weapons, vector<Consumable*> consumables, vector<Equipment*> equipments, Shopkeeper* shopkeeper, string Story){

    this -> player = player;
    this -> weapons = weapons;
    this -> consumables = consumables;
    this -> equipments = equipments;
    this -> shopkeeper = shopkeeper;
    this -> WantsToQuit = false;
    this -> BaseUpgradePrice = 5; // Changes later
    this -> UpgradesLeft = 6; // Changes later

    string BazaarStory = "As you wander through the crowded boulevard, getting curious about the growing number of people, "
    "you enter a traditional bazaar hall where everyone is just shouting. This place is all colorful but you are too exhasted to"
    "open your eyes widely to see all the beauty here. A man with a weird mustache out of nowhere takes you in his store. Where is "
    "here? I guess you're in where you should be.";

    string ForestStory = "While exploring the dense forest, you found this dusty open wooden door. Having entered, you saw a collection"
    " of weapons and other war stuff. It's noticable on the mat below the door <You and your shoes are welcome. Clean them ;)> "
    "There is no man, low light, weird patterns on the wall and valuable-looking items. The shopkeepr, a man of god -looking so- "
    "with long white beard came down the stairs. ";

    vector<string> Stories = {BazaarStory, ForestStory};

    this -> Story = ShuffleVec(Stories)[0];
}

vector<Weapon*> Shop :: getWeapons(){return weapons;}

vector<Consumable*> Shop :: getConsumables(){return consumables;}

vector<Equipment*> Shop :: getEquipments(){return equipments;}

string UpgradeNameChange(string name, int upgradeAmount){

    if(upgradeAmount != 0){
        int spaceIndex = name.find_last_of(' ');
        name = name.substr(0,spaceIndex);   
    }
    name += " " + to_string(upgradeAmount+1) +"+";
    return name;
}

void Shop :: Upgrade(Weapon* weapon){
    if(typeid(weapon) == typeid(Shotgun)){
        while(true){
            if(weapon->getUpgradeAmount() >= weapon->getUpgradeLimit()){
                cout << shopkeeper->UpgradeLimitDialogue(weapon);
                break;
            }
            if(UpgradesLeft <=0){
                cout << shopkeeper->UpgradeLimitDialogue();
                break;
            }
            if(player->getCoin() < BaseUpgradePrice * weapon->getUpgradeAmount()){
                cout << shopkeeper->NoMoneyDialogue();
                break;;
            }
            cout << "1. Damage" << endl <<
                    "2. Min Damage Percent" << endl <<
                    "Choose an option (0 to go back): ";
            int choice;
            cin >> choice;
            
            switch (choice){
                case 0:
                    break;
                case 1:
                    player->removeItem(weapon);
                    
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    weapon->setDamage(int(weapon->getDamage()*1.5));
                    
                    weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                    UpgradesLeft --;
                    
                    player->addItem(weapon);
                    
                    continue;
                case 2:
                    player->removeItem(weapon);
                    
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    Shotgun* shotgun = dynamic_cast<Shotgun*>(weapon);
                    shotgun->setMinDamagePercent(shotgun->getMinDamagePercent() + 10);
                    
                    shotgun->setUpgradeAmount(shotgun->getUpgradeAmount()+1);
                    UpgradesLeft --;
                    
                    player->addItem(shotgun);
                    continue;
                default:
                    continue;
            }
            break;   
        }
        
    }else if(typeid(weapon) == typeid(Rifle)){
        while(true){
            if(weapon->getUpgradeAmount() >= weapon->getUpgradeLimit()){
                cout << shopkeeper->UpgradeLimitDialogue(weapon);
                break;
            }
            if(UpgradesLeft <= 0){
                cout << shopkeeper->UpgradeLimitDialogue();
                break;
            }
            if(player->getCoin() < BaseUpgradePrice * weapon->getUpgradeAmount()){
                cout << shopkeeper->NoMoneyDialogue();
                break;;
            }
            cout << "1. Damage" << endl <<
                    "2. Max Attack Amount" << endl <<
                    "Choose an option (0 to go back): ";
            int choice;
            cin >> choice;
            
            switch (choice){
                case 0:
                    break;
                case 1:
                    player->removeItem(weapon);
                    
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    weapon->setDamage(int(weapon->getDamage()*1.5));
                    
                    weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                    UpgradesLeft --;
                    
                    player->addItem(weapon);
                    
                    continue;
                case 2:
                    player->removeItem(weapon);
                    
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    Rifle* rifle = dynamic_cast<Rifle*>(weapon);
                    rifle->setMaxAttackAmount(rifle->getMaxAttackAmount() + 10);
                    
                    rifle->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                    UpgradesLeft --;
                    
                    player->addItem(rifle);
                    continue;
                default:
                    continue;
            }
            break;   
        }
    }else{
        while(true){
            if(weapon->getUpgradeAmount() >= weapon->getUpgradeLimit()){
                cout << shopkeeper->UpgradeLimitDialogue(weapon);
                break;
            }
            if(UpgradesLeft <=0){
                cout << shopkeeper->UpgradeLimitDialogue();
                break;
            }
            if(player->getCoin() < BaseUpgradePrice * weapon->getUpgradeAmount()){
                cout << shopkeeper->NoMoneyDialogue();
                break;;
            }
            cout << "1. Damage" << endl <<
                    "Choose an option (0 to go back): ";
            int choice;
            cin >> choice;
            
            switch (choice){
                case 0:
                    break;
                case 1:
                    player->removeItem(weapon);
                    
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    weapon->setDamage(int(weapon->getDamage()*1.5));
                    
                    weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                    UpgradesLeft --;
                    
                    player->addItem(weapon);
                    
                    continue;
                default:
                    continue;
            }
            break;
        }  
    }
}

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
    player->addCoin(item->getPrice());
    player->removeItem(item);
    shopkeeper->BuyDialogue(item);
}

void Shop :: Menu(){

    shopkeeper->HiDialogue();
    while (!WantsToQuit){
        cout << "1. Buy \n" // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                "2. Sell \n"
                "3. Upgrade \n"
                "4. Quit";
        int choice;
        cin >> choice;
        switch (choice){
            case 1: // Player buys an item
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
                            cout << "Choose a weapon to buy (0 to go back): ";
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
                            cout << "Choose a consumable to buy (0 to go back): ";
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
                            cout << "Choose a consumable to buy (0 to go back): ";
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
    
            case 2: // Player sells an item
                while(true){
                    for (int i = 0; i < player->getItems().size(); i++){
                        cout << i+1 << ". " << player->getItems()[i].first->getName() << " " << player->getItems()[i].second << endl;
                    }
                    cout << "Choose an item you want to sell (0 to go back): ";
                    cin >> choice;
                    if(choice == 0){
                        break;
                    }
                    Buy(player->getItems()[choice-1].first);   
                }
                break;
            case 3: // Player upgrades a gun
                if(UpgradesLeft<=0){
                        cout << shopkeeper->UpgradeLimitDialogue();
                        break;
                }
                
                while(true){
                    for (int i = 0; i < player->getWeapons().size(); i++){
                        cout << i+1 << ". " << (player->getWeapons()[i].first)->getStat()<< endl;
                    }
                    cout << "Choose a weapon you want to upgrade (0 to go back): ";
                    cin >> choice;
                    if(choice == 0){
                        break;
                    }
                    
                    Weapon* ChosenWeapon = player->getWeapons()[choice-1].first;
                    
                    if(ChosenWeapon->getUpgradeAmount() >= ChosenWeapon->getUpgradeLimit()){
                        cout << shopkeeper->UpgradeLimitDialogue(ChosenWeapon);
                        continue;
                    }
                    if(player->getCoin() < BaseUpgradePrice * ChosenWeapon->getUpgradeAmount()){
                        cout << shopkeeper->NoMoneyDialogue();
                        continue;
                    }
                    Upgrade(ChosenWeapon);   
                }
                break;
            case 4: // Player quits
                WantsToQuit = true;
                break;
            default:
                continue;    
        }
    }
    cout << shopkeeper->ByeDialogue();
}
    
Hospital :: Hospital(Player* player, Medic* medic, int MaxHpIncresePrice, int FullHealPrice, int HalfHealPrice, string Story){
    this->player = player;
    this->medic = medic;
    this->MaxHpIncreasePrice = MaxHpIncreasePrice;
    this->FullHealPrice = FullHealPrice;
    this->HalfHealPrice = HalfHealPrice;
    this->HasHealed = false;

    string CrowdedCityStory = "As you walk through the crowded street with a limp, a baby girl screams seeing your body and face "
    "injuries but you're too exhasted to actually care. Suddenly you notice a red sign, acutually a plus (+) sign on a building. "
    "That's a hospital full of injured people. You're gonna have a long time waiting for your turn. But a good-hearted woman gives you "
    "her turn so you enter the doctor's.";

    string CaveStory = "As you're walking in darkness, injured and full of wounds, you see a pair of eyes shining out of a cave, "
    "staring at you. You are frightened and about to run away. The body of those eyes shows up. It is an old man with a kind face "
    "inviting you to his cave. A cave full of vague tools. You can't understand what they really are and who he really is untill you "
    "see a paper under some glasses filled with some beverage-looking drinks on which <Mystical Medicines> is written.";

    vector<string> Stories = {CrowdedCityStory, CaveStory};  

    this -> Story = ShuffleVec(Stories)[0];  
}


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
                "2. Restore full HP ( " << FullHealPrice << "$)" << endl <<
                "3. Increase max HP by 20% ( " << MaxHpIncreasePrice << "$)" << endl <<
                "4. quit" << endl <<
                "Choose an option: ";
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
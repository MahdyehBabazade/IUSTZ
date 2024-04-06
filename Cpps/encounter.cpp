#include "../Headers/encounter.h"
#include "functions.cpp"
#include <iostream>
#include <random>

Encounter :: Encounter(string Story){this -> Story = Story;}

string Encounter :: getStory(){return Story;}

Shop :: Shop(Player* player, vector<Weapon*> weapons, vector<Consumable*> consumables, vector<Equipment*> equipments, Shopkeeper* shopkeeper){

    this -> player = player;
    this -> weapons = weapons;
    this -> consumables = consumables;
    this -> equipments = equipments;
    this -> shopkeeper = shopkeeper;
    this -> WantsToQuit = false;
    this -> BaseUpgradePrice = 5; // Changes later
    this -> UpgradesLeft = 6; // Changes later

    string BazaarStory = "As you wander through the crowded boulevard, getting curious about the growing number of people, "
    "you enter a traditional bazaar hall \nwhere everyone is just shouting. This place is all colorful but you are too exhasted to"
    "open your eyes widely to see all the beauty here.\n A man with a weird mustache out of nowhere takes you in his store. Where is this "
    "place?\n\n";

    string ForestStory = "While exploring the dense forest, you find this dusty open wooden door. Upon entering, you see a collection"
    " of weapons and other war stuff.\nIt's noticable on the mat below the door < You and your shoes are welcome. Clean them ;) > "
    "There is no man, low light, weird patterns on the \nwall and valuable-looking items. The shopkeepr, a man of god -looking so- "
    "with long white beard comes down the stairs. \n\n";

    vector<string> Stories = {BazaarStory, ForestStory};

    this -> Story = ShuffleVec(Stories)[0];
}

vector<Weapon*> Shop :: getWeapons(){return weapons;}

vector<Consumable*> Shop :: getConsumables(){return consumables;}

vector<Equipment*> Shop :: getEquipments(){return equipments;}

void Shop :: setWeapons(vector<Weapon*> weapons){this -> weapons = weapons;}

void Shop :: setConsumables(vector<Consumable*> consumables){this -> consumables = consumables;}

void Shop :: setEquipments(vector<Equipment*> equipments){this -> equipments = equipments;}

string UpgradeNameChange(string name, int upgradeAmount){

    if(upgradeAmount > 1){
        int spaceIndex = name.find_last_of(' ');
        name = name.substr(0,spaceIndex);  
        name += " " + to_string(upgradeAmount) +"+"; 
    }
    
    return name;
}

void Shop :: Upgrade(Weapon* weapon , string dialogue){
    if(dynamic_cast<Shotgun*>(weapon) != nullptr){
        while(true){
            if(weapon->getUpgradeAmount() >= weapon->getUpgradeLimit()){
                cout << shopkeeper->UpgradeLimitDialogue(weapon);
                cout << "Press anything to continue";
                getch();
                break;
            }
            if(UpgradesLeft <=0){
                cout << shopkeeper->UpgradeLimitDialogue();
                cout << "Press anything to continue";
                getch();
                break;
            }
            if(player->getCoin() < BaseUpgradePrice * weapon->getUpgradeAmount()){
                cout << Story;
                cout << shopkeeper->NoMoneyDialogue();
                cout << "Press anything to continue";
                getch();
                break;;
            }
            int choice = Choose(Story + dialogue + "\n",
                                {"Damage",
                                "Min Damage Percent",
                                "Back"});
            switch (choice){
                case 1:
                    player->removeItem(weapon);
                    
                    weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                    weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * weapon->getUpgradeAmount() * 0.8));
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    weapon->setDamage(int(weapon->getDamage()*1.4));
                    
                    UpgradesLeft --;
                    
                    player->addItem(weapon);
                    
                    continue;
                case 2:
                {
                    player->removeItem(weapon);
                    
                    weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * weapon->getUpgradeAmount() * 0.8));
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    Shotgun* shotgun = dynamic_cast<Shotgun*>(weapon);
                    shotgun->setUpgradeAmount(shotgun->getUpgradeAmount()+1);
                    shotgun->setMinDamagePercent(shotgun->getMinDamagePercent() + 10);
                    
                    UpgradesLeft --;
                    
                    player->addItem(shotgun);
                    continue;
                }
                case 3:
                    break;
                default:
                    continue;
            }
            break;   
        }
        
    }else if(dynamic_cast<Rifle*>(weapon) != nullptr){
        while(true){
            if(weapon->getUpgradeAmount() >= weapon->getUpgradeLimit()){
                clearScreen();
                cout << Story;
                cout << shopkeeper->UpgradeLimitDialogue(weapon);
                cout << "Press anything to continue";
                getch();
                break;
            }
            if(UpgradesLeft <= 0){
                clearScreen();
                cout << Story;
                cout << shopkeeper->UpgradeLimitDialogue();
                cout << "Press anything to continue";
                getch();
                break;
            }
            if(player->getCoin() < BaseUpgradePrice * weapon->getUpgradeAmount()){
                clearScreen();
                cout << Story;
                cout << shopkeeper->NoMoneyDialogue();
                cout << "Press anything to continue";
                getch();
                break;;
            }
            int choice = Choose(Story + dialogue + "\n",
                                {"Damage",
                                "Max Attack Amount",
                                "Back"});
            
            switch (choice){
                case 1:
                    player->removeItem(weapon);
                    
                    weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                    weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * weapon->getUpgradeAmount() * 0.8));
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    weapon->setDamage(int(weapon->getDamage()*1.4));
                    
                    UpgradesLeft --;
                    
                    player->addItem(weapon);
                    
                    continue;
                case 2:
                {
                    player->removeItem(weapon);
                    
                    weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * weapon->getUpgradeAmount() * 0.8));
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    Rifle* rifle = dynamic_cast<Rifle*>(weapon);
                    rifle->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                    rifle->setMaxAttackAmount(rifle->getMaxAttackAmount() + 10);
                    
                    UpgradesLeft --;
                    
                    player->addItem(rifle);
                    continue;
                }
                case 3:
                    break;
                default:
                    continue;
            }
            break;   
        }
    }else{
        while(true){
            if(weapon->getUpgradeAmount() >= weapon->getUpgradeLimit()){
                clearScreen();
                cout << Story;
                cout << shopkeeper->UpgradeLimitDialogue(weapon);
                cout << "Press anything to continue";
                getch();
                break;
            }
            if(UpgradesLeft <=0){
                clearScreen();
                cout << Story;
                cout << shopkeeper->UpgradeLimitDialogue();
                cout << "Press anything to continue";
                getch();
                break;
            }
            if(player->getCoin() < BaseUpgradePrice * weapon->getUpgradeAmount()){
                clearScreen();
                cout << Story;
                cout << shopkeeper->NoMoneyDialogue();
                cout << "Press anything to continue";
                getch();
                break;;
            }
            
            int choice = Choose(Story + dialogue + "\n",
                                {"Damage",
                                "Back"});
            
            switch (choice){
                case 1:
                    player->removeItem(weapon);
                    
                    weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                    weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * weapon->getUpgradeAmount() * 0.8));
                    weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                    weapon->setDamage(int(weapon->getDamage()*1.4));
                    
                    UpgradesLeft --;
                    
                    player->addItem(weapon);
                    
                    continue;
                case 2:
                    break;
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
        
        item->setPrice(int(item->getPrice()*0.8));
        player->addItem(item);
        clearScreen();
        cout << Story;
        cout << shopkeeper->SellDialogue(item);
        cout << "Press anything to continue";
        getch();
        removeItem(item);
    }
    else{
        clearScreen();
        cout << Story;
        cout << shopkeeper->NoMoneyDialogue();
        cout << "Press anything to Continue\n";
        getch();
    }
}

void Shop :: Buy(Item* item){ // Shopkeeper buys, Player sells
    player->addCoin(item->getPrice());
    player->removeItem(item);
    clearScreen();
    cout << Story;
    shopkeeper->BuyDialogue(item);
    cout << "Press anything to continue";
    getch();    
    item->setPrice(int(item->getPrice()* 1.25)); // adds 20 precent to item's orignial price 
    addItem(item);
}

void Shop::addItem(Item* item){
    if(dynamic_cast<Weapon*>(item) != nullptr){
        weapons.push_back(dynamic_cast<Weapon*>(item));
    }else if(dynamic_cast<Consumable*>(item) != nullptr){
        consumables.push_back(dynamic_cast<Consumable*>(item));
    }else if(dynamic_cast<Equipment*>(item) != nullptr){
        equipments.push_back(dynamic_cast<Equipment*>(item));
    }
}

void Shop::removeItem(Item* item){
    if(dynamic_cast<Weapon*>(item) != nullptr){
        weapons.erase(remove(weapons.begin(),weapons.end(),dynamic_cast<Weapon*>(item)),weapons.end());
    }else if(dynamic_cast<Consumable*>(item) != nullptr){
        consumables.erase(remove(consumables.begin(),consumables.end(),dynamic_cast<Consumable*>(item)),consumables.end());
    }else if(dynamic_cast<Equipment*>(item) != nullptr){
        equipments.erase(remove(equipments.begin(),equipments.end(),dynamic_cast<Equipment*>(item)),equipments.end());
    }
}

void Shop :: Menu(){
    string dialogue = shopkeeper->HiDialogue();
    while (!WantsToQuit){
        int choice = Choose(Story + dialogue+ "\n" , 
                            {"Buy",           // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                            "Sell",
                            "Upgrade",
                            "Leave the shop"});
        
        switch (choice){
            case 1: // Player buys an item
                choice = Choose(Story + dialogue + "\n" ,
                                {"Weapons",           // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                                "Consumables",
                                "Equipments",
                                "Back"});
                
                switch (choice){
                    case 1:
                    {
                        while(true){
                            vector<string> Options;
                            for(Weapon* weapon: weapons){
                                Options.push_back(weapon->getStat());
                            }
                            Options.push_back("Back");
                            
                            int choice = Choose(Story + dialogue , Options);
                            if(choice == Options.size()){
                                break;
                            }
                            Sell(weapons[choice-1]);
                        }
                        continue;
                    }
                    case 2:
                    {
                        while (true){
                            vector<string> Options;
                            for(Consumable* consumable: consumables){
                                Options.push_back(consumable->getStat());
                            }
                            Options.push_back("Back");
                            
                            int choice = Choose(Story + dialogue + "\n" ,
                            Options);
                            if(choice == Options.size()){
                                break;
                            }
                            Sell(consumables[choice-1]);
                        }
                        continue;
                    }
                    case 3:
                    {
                        while(true){
                            vector<string> Options;
                            for(Equipment* equipment: equipments){
                                Options.push_back(equipment->getStat());
                            }
                            Options.push_back("Back");
                            
                            int choice = Choose(Story + dialogue + "\n" ,
                            Options);
                            if(choice == Options.size()){
                                break;
                            }
                            Sell(equipments[choice-1]);
                        }
                        continue;
                    }
                    case 4:
                        break;
                    default:
                        continue;
                }   
                continue;
            case 2: // Player sells an item
                while(true){
                    vector<string> Options;
                    for(pair<Item*,int> item: player->getItems()){
                        Options.push_back(item.first->getStat());
                    }
                    Options.push_back("Back");
                    
                    int choice = Choose(Story + dialogue + "\n" ,
                    Options);
                    if(choice == Options.size()){
                        break;
                    }
                    Buy(player->getItems()[choice-1].first);
                }
                continue;
            case 3: // Player upgrades a gun
                if(UpgradesLeft<=0){
                    clearScreen();
                    cout << Story;
                    cout << shopkeeper->UpgradeLimitDialogue();
                    cout << "Press anything to continue";
                    getch();
                    break;
                }
                
                while(true){
                    vector<string> Options;
                    for(pair<Weapon*,int> weapon: player->getWeapons()){
                        Options.push_back(weapon.first->getStat());
                    }
                    Options.push_back("Back");
                    
                    int choice = Choose(Story + dialogue + "\n",
                    Options);
                    if(choice == Options.size()){
                        break;
                    }
                    
                    Weapon* ChosenWeapon = player->getWeapons()[choice-1].first;
                    
                    if(ChosenWeapon->getUpgradeAmount() >= ChosenWeapon->getUpgradeLimit()){
                        clearScreen();
                        cout << Story;
                        cout << shopkeeper->UpgradeLimitDialogue(ChosenWeapon);
                        cout << "Press anything to continue";
                        getch();
                        continue;
                    }
                    if(player->getCoin() < BaseUpgradePrice * ChosenWeapon->getUpgradeAmount()){
                        clearScreen();
                        cout << Story;
                        cout << shopkeeper->NoMoneyDialogue();
                        cout << "Press anything to continue";
                        getch();
                        continue;
                    }
                    Upgrade(ChosenWeapon , dialogue);   
                }
                continue;
            case 4: // Player quits
                WantsToQuit = true;
                exit(0);
                break;
            default:
                continue;    
        }
    }
    clearScreen();
    cout << Story;
    cout << shopkeeper->ByeDialogue();
    cout << "Press anything to continue";
    getch();
}
    
Hospital :: Hospital(Player* player, Medic* medic){
    this->player = player;
    this->medic = medic;
    this->MaxHpIncreasePrice = 40;
    this->FullHealPrice = 30;
    this->HalfHealPrice = 20;
    this->HasHealed = false;

    string CrowdedCityStory = "As you walk through the crowded street with a limp, a little girl screams seeing your body and face "
    "injuries but you're too \nexhasted to actually care. Suddenly you notice a red sign, acutually a plus (+) sign on a building. "
    "That's a hospital full of \ninjured people. You're gonna have a long time waiting for your turn. But a good-hearted woman gives you "
    "her turn so you're now the \nnext in line.\n";
    string CaveStory = "As you're walking in darkness, injured and full of wounds, you see a pair of eyes shining out of a cave, "
    "staring at you. \nYou are frightened and about to run away when an old man with a kind face steps forward, inviting you to his cave."
    " A cave \nfull of vague tools. You can't understand what they really are and who he really is until you "
    "see a paper under \nsome glasses filled with some beverage-looking drinks on which <Mystical Medicines> is written.\n";
    vector<string> Stories = {CrowdedCityStory, CaveStory};  

    this -> Story = ShuffleVec(Stories)[0];  
}


void Hospital :: FullHeal(){
    if(player->getCoin() < FullHealPrice){
        clearScreen();
        cout << Story;
        cout << medic->NoMoneyDialogue();
        cout << "Press anything to continue";
        getch();
        return;
    }
    player->setHP(player->getMaxHP());
    clearScreen();
    cout << Story;
    cout << medic->HealDialogue();
    cout << "Press anything to continue";
    getch();
    HasHealed = true;
}

void Hospital ::HalfHeal(){
    if(player->getCoin() < HalfHealPrice){
        clearScreen();
        cout << Story;
        cout << medic->NoMoneyDialogue();
        cout << "Press anything to continue";
        getch();
        return;
    }
    player->setHP(player->getHP() + (player->getMaxHP()/2));
    clearScreen();
    cout << Story;
    cout << medic->HealDialogue();
    cout << "Press anything to continue";
    getch();
    HasHealed = true;
}

void Hospital :: MaxHpIncrease(){
    if(player->getCoin() < MaxHpIncreasePrice){
        clearScreen();
        cout << Story;
        cout << medic->NoMoneyDialogue();
        cout << "Press anything to continue";
        getch();
        return;
    }
    player->setMaxHP(int(player->getMaxHP()*1.2));
    player->setHP(int(player->getMaxHP() * 0.2 / 1.2 + player->getHP()));
    clearScreen();
    cout << Story;
    cout << medic->HealDialogue();
    cout << "Press anything to continue";
    getch();
    HasHealed = true;
}

void Hospital :: Menu(){
    while(!HasHealed){
        int choice = Choose(Story + medic->HiDialogue() , 
                {"Restore half HP ( " + to_string(HalfHealPrice) + "$)",
                "Restore full HP ( " + to_string(FullHealPrice) + "$)", 
                "Increase max HP by 20% ( " + to_string(MaxHpIncreasePrice) + "$)",
                "quit"}
                );
                
        
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
                HasHealed = true;
                exit(0);
                break;
            default:
                continue;
        }
    }
    clearScreen();
    cout << Story;
    cout << medic->ByeDialogue();
    cout << "Press anything to Continue\n";
    getch();
}

RandomEncounter :: RandomEncounter(Player* player){
    this -> player = player;
    Menu();
}

void RandomEncounter :: Menu(){

    int RandomChoice = Index_Weighted_Random({1,1,4,5});
    
    
    switch (RandomChoice)
    {
    case 0: // Fight
        Fight* fight;
        break;
    case 1: // Shop
        Shop* shop;
        break;
    case 2: // Disaster
        RandomChoice = rand() % 3;
        switch (RandomChoice)
        {
        case 0: // HP decrease
            cout << "You're looking around for a sign on this mountain when suddenly the ground under your feet shakes. The smoke rises "
            "from the peak then you see the lava coming out so you start to run but the smoke stops you and makes it hard to breath." << endl;
            player->setHP(player->getHP()-5);
            cout << "< You lost 5 health points =( >" << endl;
            break;
        case 1: // Coin decrease
            cout << "You enter a mysterious cave where its walls are all covered with strange patterns. You're actually fascinated by what "
            "you're looking at. Suddenly you hear a weird sound 'KHSH KHSH'. What was that? You put your hand in your pocket with "
            "hesistation to take your gun out. 5 coins fall down. You bend over to collect them but out of nowhere a monkey "
            "appears and takes away all those coins." << endl;
            player->removeCoin(5);
            cout << "< You lost 5 coins :( >" << endl;
            break;
        case 3: // BackpackCapacity decrease
            cout << "You're walking through this endless-looking road tiredly. You're thinking about your last fight, remembering your "
            "weaknesses and analyzing them. The sound of someone walking on the grass takes you out of your thoughts and makes you look "
            "around yourself carefully. A zombie looking exactly like the zombie you lately fought with, appears and runs after you. You "
            "get shocked but run faster and faster but your backpack gets stuck on a tree branch. Trying to remove it, the zombie gets closer "
            "but you finally succeed and find a cave to take shelter in." << endl;
            // Decreases the size ignoring if the pack is for or not
            player->setBackPackCapacity(player->getBackPackCapacity()-3); // Can be changed later 
            cout << "< Yout backpack's capacity is now decreased by 3 points =( >";
            break;
        default:
            break;
        }
        
        break;

    case 4: // Prize (Mystery Box)
        RandomChoice = rand() % 3;
        switch (RandomChoice)
        {
        case 0:
            cout << "Wandering through this dense forest, a shining object which seems to have a large part of it still underground " 
            "makes you stare at it for seconds. You go closer untill you approach enough to take it out from the soil. It seems to be "
            "a gift box. You open it and... " << endl;
            break;
        default:
            break;
        }
        RandomChoice = rand() % 5;
        switch (RandomChoice)
        {
        case 0: // Coin increase
            cout << "LUCKY YOU! You earned 10 coins." << endl;
            player->addCoin(10);
            break;
        case 1: // HP increase
            cout << "Congratulations! You've gained 5 more health points!" << endl;
            player->setHP(min(player->getHP()+5, player->getMaxHP()));
            break;
        case 2: // Max Energy increase
            cout << "Max Energy increase! (5 points)" << endl;
            player->setMaxEnergy(player->getMaxEnergy()+5);
            break;
        case 3: // Shield increase
            cout << "Feeling more secure? That's because your shield amount has been increased by 10 points!" << endl;
            player->setShield(min(player->getShield()+10, 100));
            break;
        case 4: // MaxHP increase
            cout << "Congratulations! You've gained 5 more max health points!" << endl;
            player->setMaxHP(player->getMaxHP()+5);
            break;
        default:
            break;
        }
    default:
        break;
    }
}

Fight :: Fight(Player* player, int type, vector<Character*> enemies, vector<Item*> items){
    this -> player = player;
    this -> type = type;
    this -> enemies = enemies;
    this -> items = items;
}
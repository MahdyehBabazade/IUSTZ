#pragma once
#include "../Headers/encounter.h"
#include "../Headers/factory.h"
#include "functions.cpp"
#include <iostream>
#include <random>

string Encounter :: getStory(){return Story;}

Shop :: Shop(Player* player, vector<Weapon*> weapons, vector<Consumable*> consumables, vector<Equipment*> equipments, Shopkeeper* shopkeeper){
    this -> player = player;
    this -> weapons = weapons;
    this -> consumables = consumables;
    this -> equipments = equipments;
    this -> shopkeeper = shopkeeper;
    this -> WantsToQuit = false;
    this -> BaseUpgradePrice = 30; // Changes later
    this -> UpgradesLeft = 2; // Changes later

    string BazaarStory = "As you wander through the crowded boulevard, getting curious about the growing number of people, "
    "you enter a traditional bazaar hall \nwhere everyone is just shouting. This place is all colorful but you are too exhasted to"
    "open your eyes widely to see all the beauty here.\nA man with a weird mustache out of nowhere takes you in his store. Where is this "
    "place?\n";

    string ForestStory = "While exploring the dense forest, you find this dusty open wooden door. Upon entering, you see a collection"
    " of weapons and other war stuff.\nIt's noticable on the mat below the door < You and your shoes are welcome. Clean them ;) > "
    "There is no man, low light, weird patterns on the \nwall and valuable-looking items. The shopkeepr, a man of god -looking so- "
    "with long white beard comes down the stairs. \n";

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
    if(upgradeAmount >= 3){
        int spaceIndex = name.size() - 3;
        name = name.substr(0,spaceIndex); 
        name += " " + to_string(upgradeAmount) +"+"; 
    }else if (upgradeAmount == 1){
        name += " +"; 
    }else{
        int spaceIndex = name.size() - 2;
        name = name.substr(0,spaceIndex); 
        name += " " + to_string(upgradeAmount) +"+"; 
    }
    
    return name;
}

void Shop :: Upgrade(Weapon* weapon , string dialogue){
    if(dynamic_cast<Shotgun*>(weapon) != nullptr){
        int choice = Choose(Story + "\n\n"  + getStat() + dialogue + "\n\n" + "Coins needed to Upgrade: " + 
        to_string(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount())) + "\n",
                            {"1. Damage",
                            "2. Min Damage Percent",
                            "3. Back"});
        switch (choice){
            case 1:
                player->removeItem(weapon);
                
                weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * weapon->getUpgradeAmount() * 0.8));
                weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                weapon->setDamage(int(weapon->getDamage()*1.4));
                
                UpgradesLeft --;
                
                player->addItem(weapon);
                player->removeCoin(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()));
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
                player->removeCoin(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()));
            
            }
            case 3:
                break;
            default:
                break;
        }  
        
        
    }else if(dynamic_cast<Rifle*>(weapon) != nullptr){
        if(weapon->getUpgradeAmount() >= weapon->getUpgradeLimit()){
            clearScreen();
            cout << Story << "\n\n";
            cout << shopkeeper->UpgradeLimitDialogue(weapon);
            cout << "Press anything to continue";
            getch();
        }
        if(UpgradesLeft <= 0){
            clearScreen();
            cout << Story << "\n\n";
            cout << shopkeeper->UpgradeLimitDialogue();
            cout << "Press anything to continue";
            getch();
        }
        if(player->getCoin() < BaseUpgradePrice * weapon->getUpgradeAmount()){
            clearScreen();
            cout << Story << "\n\n";
            cout << shopkeeper->NoMoneyDialogue();
            cout << "Press anything to continue";
            getch();
        }
        int choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n\n" + "Coins needed to Upgrade: " + 
        to_string(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount())) + "\n",
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
                break;
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
                break;
            }
            case 3:
                break;
            default:
                break;
        }
        
    }else{
        if(weapon->getUpgradeAmount() >= weapon->getUpgradeLimit()){
            clearScreen();
            cout << Story << "\n\n";
            cout << shopkeeper->UpgradeLimitDialogue(weapon);
            cout << "Press anything to continue";
            getch();
        }
        if(UpgradesLeft <=0){
            clearScreen();
            cout << Story << "\n\n";
            cout << shopkeeper->UpgradeLimitDialogue();
            cout << "Press anything to continue";
            getch();
        }
        if(player->getCoin() < BaseUpgradePrice * weapon->getUpgradeAmount()){
            clearScreen();
            cout << Story << "\n\n";
            cout << shopkeeper->NoMoneyDialogue();
            cout << "Press anything to continue";
            getch();
        }
        
        int choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n\n" + "Coins needed to Upgrade: " + 
        to_string(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount())) + "\n",
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
                
                break;
            case 2:
                break;
            default:
                break;
        }
             
    }
}

void Shop :: Sell(Item* item){ // Shopkeeper sells, Player buys

    if (player->getCoin() >= item->getPrice()){
        if (player->getBackPackCapacity() > item->getCapacity()+player->getBackPackWeight())
        {
            player->removeCoin(item->getPrice());

            item->setPrice(int(item->getPrice()*0.8));
            player->addItem(item);
            clearScreen();
            cout << Story << "\n\n";
            cout << shopkeeper->SellDialogue(item);
            cout << "Press anything to continue";
            getch();
            removeItem(item);
        }
    }
    else{
        clearScreen();
        cout << Story << "\n\n";
        cout << shopkeeper->NoMoneyDialogue();
        cout << "Press anything to continue\n";
        getch();
    }
}

void Shop :: Buy(Item* item){ // Shopkeeper buys, Player sells
    player->addCoin(item->getPrice());
    player->removeItem(item);
    clearScreen();
    cout << Story << "\n\n";
    cout << shopkeeper->BuyDialogue(item);
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
    if(dynamic_cast<Weapon *>(item) != nullptr)
        for(int i = 0; i < weapons.size(); i++)
            if(dynamic_cast<Weapon *>(item) == weapons[i])
                weapons.erase(weapons.begin() + i);    
    else if(dynamic_cast<Consumable *>(item) != nullptr)
        for(int i = 0; i < consumables.size(); i++)
            if(dynamic_cast<Consumable *>(item) == consumables[i])
                consumables.erase(consumables.begin() + i);
    else if(dynamic_cast<Equipment *>(item) != nullptr)
        for(int i = 0; i < equipments.size(); i++)
            if(dynamic_cast<Equipment *>(item) == equipments[i])
                equipments.erase(equipments.begin() + i);
}

void Shop :: Menu(){
    string dialogue = shopkeeper->HiDialogue();
    while (!WantsToQuit){
        int choice = Choose(Story + "\n\n"  + getStat() + dialogue+ "\n" , 
                            {"1. Buy",           // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                            "2. Sell",
                            "3. Upgrade",
                            "4. Leave the shop"});
        
        switch (choice){
            case 1: // Player buys an item
                choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n" ,
                                {"1. Weapons",           // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                                "2. Consumables",
                                "3. Equipments",
                                "4. Back"});
                
                switch (choice){
                    case 1:
                    {
                        while(true){
                            vector<string> Options;
                            for(Weapon* weapon: weapons){
                                Options.push_back(weapon->getStat());
                            }
                            Options.push_back("Back");
                            
                            int choice = Choose(Story + "\n\n" + getStat() + dialogue , Options);
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
                            
                            int choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n" ,
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
                            
                            int choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n" ,
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
                    
                    int choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n" ,
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
                    cout << Story << "\n\n";
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
                    Options.push_back("BackPack [" + to_string(player->getBackPackWeight()) + "/" + to_string(player->getBackPackCapacity()) + "]");
                    Options.push_back("Back");
                    
                    int choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n",
                    Options);
                    if(choice == Options.size()){
                        break;
                    }
                    else if(choice == Options.size() - 1){
                        if(player->getBackPackCapacity() >= 90){
                            clearScreen();
                            cout << Story << "\n\n" << shopkeeper->getName() << ": You already have the Best BackPack!!!\n";
                            cout << "Press anything to continue\n";
                            getch();
                        }
                        else if(player->getCoin() >= 30){
                            choice = Choose(Story + "\n\n" + getStat() + dialogue + "\nUpgrade price is 30 coins\n" ,
                            {"1. Upgrade" , "2. Back"});
                            if(choice = 1){
                                player->setBackPackCapacity(player->getBackPackCapacity() + 15);
                                player->removeCoin(30);
                                clearScreen();
                                cout << Story << "\n\n" << shopkeeper->getName() << ": Your backpack has been Upgraded.\n";
                                cout << "Press anything to continue\n";
                                getch();
                            }
                        }
                        else{
                            clearScreen();
                            cout << shopkeeper->NoMoneyDialogue();
                            cout << "Press anything to continue\n";
                            getch();
                        }
                        continue;
                    }
                    Weapon* ChosenWeapon = player->getWeapons()[choice-1].first;
                    
                    if(ChosenWeapon->getUpgradeAmount() >= ChosenWeapon->getUpgradeLimit()){
                        clearScreen();
                        cout << Story << "\n\n";
                        cout << shopkeeper->UpgradeLimitDialogue(ChosenWeapon);
                        cout << "Press anything to continue";
                        getch();
                        continue;
                    }
                    else if(player->getCoin() < BaseUpgradePrice * pow(1.5 , ChosenWeapon->getUpgradeAmount())){
                        clearScreen();
                        cout << Story << "\n\n";
                        cout << shopkeeper->NoMoneyDialogue();
                        cout << "Press anything to continue";
                        getch();
                        continue;
                    }
                    else{
                        Upgrade(ChosenWeapon , dialogue);
                    }   
                }
                continue;
            case 4: // Player quits
                WantsToQuit = true;
                break;
            default:
                continue;    
        }
    }
    clearScreen();
    cout << Story << "\n\n";
    cout << shopkeeper->ByeDialogue();
    cout << "Press anything to continue";
    getch();
}

string Shop :: getStat(){
    
    string output = player->getName() + ":\n" + 
                    "Coin: " + to_string(player->getCoin()) + "\n" +
                    "BackPack Weight: [" + to_string(player->getBackPackWeight()) + "/" + to_string(player->getBackPackCapacity()) + "]\n" +
                    "HP: [" + to_string(player->getHP()) + "/" + to_string(player->getMaxHP()) + "]\n\n" +
                    "Shop:\n" +
                    "Upgrades Left: " + to_string(UpgradesLeft) + "\n\n";
    
    return output;
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
        cout << Story << "\n\n";
        cout << medic->NoMoneyDialogue();
        cout << "Press anything to continue";
        getch();
        return;
    }
    player->setHP(player->getMaxHP());
    clearScreen();
    cout << Story << "\n\n";
    cout << medic->HealDialogue();
    cout << "Press anything to continue";
    getch();
    HasHealed = true;
}

void Hospital ::HalfHeal(){
    if(player->getCoin() < HalfHealPrice){
        clearScreen();
        cout << Story << "\n\n";
        cout << medic->NoMoneyDialogue();
        cout << "Press anything to continue";
        getch();
        return;
    }
    player->setHP(player->getHP() + (player->getMaxHP()/2));
    clearScreen();
    cout << Story << "\n\n";
    cout << medic->HealDialogue();
    cout << "Press anything to continue";
    getch();
    HasHealed = true;
}

void Hospital :: MaxHpIncrease(){
    if(player->getCoin() < MaxHpIncreasePrice){
        clearScreen();
        cout << Story << "\n\n";
        cout << medic->NoMoneyDialogue();
        cout << "Press anything to continue";
        getch();
        return;
    }
    player->setMaxHP(int(player->getMaxHP()*1.2));
    player->setHP(int(player->getMaxHP() * 0.2 / 1.2 + player->getHP()));
    clearScreen();
    cout << Story << "\n\n";
    cout << medic->HealDialogue();
    cout << "Press anything to continue";
    getch();
    HasHealed = true;
}

void Hospital :: Menu(){
    while(!HasHealed){
        int choice = Choose(Story + "\n\n" + medic->HiDialogue() , 
                {"1. Restore half HP ( " + to_string(HalfHealPrice) + "$)",
                "2. Restore full HP ( " + to_string(FullHealPrice) + "$)", 
                "3. Increase max HP by 20% ( " + to_string(MaxHpIncreasePrice) + "$)",
                "4. Leave the Hospital"}
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
                break;
            default:
                continue;
        }
    }
    clearScreen();
    cout << Story << "\n\n";
    cout << medic->ByeDialogue();
    cout << "Press anything to Continue\n";
    getch();
}

string Hospital :: getStat(){
    string output = "HP: " + to_string(player->getHP()) + "/" + to_string(player->getMaxHP()) + "\n" +
                    "Coin: " + to_string(player->getCoin()) + "\n";
    return output;
}

RandomEncounter :: RandomEncounter(Player* player){
    this -> player = player;
}

void RandomEncounter :: Menu(Player* player, Map* map){

    int RandomChoice = Index_Weighted_Random({1,1,4,5});
    clearScreen();
    switch (RandomChoice)
    {
    case 0:{ // Fight
        FightFactory fight(player , map);
        fight.GenerateNormalFight()->start();
        break;
    }
    case 1:{ // Shop
        ShopFactory shop(map , player);
        shop.Generate()->Menu();
        break;
    }
    case 2: // Disaster
        RandomChoice = rand() % 2;
        switch (RandomChoice)
        {
        case 0: // HP decrease
            cout << "You're looking around for a sign on this mountain when suddenly the ground under your feet shakes. The\n"
            "smoke rises from the peak then you see the lava coming out so you start to run but the smoke stops you\n"
            "and makes it hard to breath.\n\n";
            player->setHP(player->getHP()-5);
            cout << "< You lost 5 health points =( >" << endl;
            break;
        case 1: // Coin decrease
            cout << "You enter a mysterious cave where its walls are all covered with strange patterns. You're actually fascinated\n"
            "by what you're looking at. Suddenly you hear a weird sound 'KHSH KHSH'. What was that? You put your hand\nin your pocket with "
            "hesistation to take your gun out. 10 coins fall down. You bend over to collect them but \nout of nowhere a monkey "
            "appears and takes away all those coins.\n\n";
            player->removeCoin(10);
            cout << "< You lost 10 coins :( >" << endl;
            break;
        default:
            break;
        }
        
        break;

    case 3: // Prize (Mystery Box)
        RandomChoice = rand() % 1;
        switch (RandomChoice)
        {
        case 0:
            cout << "Wandering through this dense forest, a shining object which seems to have a large part of it still underground \n" 
            "makes you stare at it for seconds. You go closer untill you approach enough to take it out from the soil. \nIt seems to be "
            "a gift box. You open it and... \n\n";
            break;
        default:
            break;
        }
        RandomChoice = rand() % 4;
        switch (RandomChoice)
        {
        case 0: // Coin increase
            cout << endl << "LUCKY YOU! You earned 10 coins." << endl;
            player->addCoin(10);
            break;
        case 1: // HP increase
            cout << endl  << "Congratulations! Your injuries has healed! (10 HP gained)" << endl;
            player->setHP(player->getHP() + 10);
            break;
        case 2: // Max Energy increase
            cout << endl  << "Max Energy increase! (1 point)" << endl;
            player->setMaxEnergy(player->getMaxEnergy() + 1);
            break;
        case 3: // MaxHP increase
            cout << endl  << "Congratulations! Your MaxHP increased by 5 points" << endl;
            player->setMaxHP(player->getMaxHP()+5);
            player->setHP(player->getHP() + 5);
            break;
        default:
            break;
        }
    default:
        break;
    }
    cout << "Press anything to Continue\n";
    getch();
}

Fight :: Fight(Player* player, int type, vector<Character*> enemies, vector<Item*> items, int droppedCoins, vector<Relic*> relics){
    this -> player = player;
    this -> type = type;
    this -> enemies = enemies;
    this -> items = items;
    this -> droppedCoins = droppedCoins;
    fightControl = new Control::FightControl(player,enemies,items,droppedCoins,relics);
}

void Fight :: start(){
    fightControl->StartFight();
}
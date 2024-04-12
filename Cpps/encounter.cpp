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
    "you enter a traditional bazaar hall where\neveryone is just shouting. This place is all colorful but you are too exhausted to "
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



int getMaxWidth(vector<vector<string>> &entry){
    int width = 0;
    int rows = entry.size();
    for(int i=0 ; i<rows ; i++){
        for(int j=0; j<entry[i].size() ; j++){
            int len = entry[i][j].length();
            if(len > width)
                width = len;
        }
    }
    return width;
}

int Shop::MenuManager(string Description,vector<vector<string>> Options, vector<string> Header){
    Options.insert(Options.begin(),Header);
    
    int width = getMaxWidth(Options);
    
    int option = 1;
    int vecSize = Options[0].size();
    while(true){
        clearScreen();
        cout << Description << endl;
        
        for(int i=0 ; i<Options.size(); i++){
            if(i == option){
                cout << green;
            }
            if(i == 0)
                cout << left << setw(log(Options.size()) + 2) << "";
            else
                cout << left << setw(log(Options.size()) + 2) << to_string(i) + ". ";
            for(int j=0 ; j<vecSize ; j++){
                cout << left << setw(width) << Options[i][j] << " " ;
            }
            cout << reset << endl;
        }
        cout << "\nMove between options with W & S and choose the option with Enter.(Press Esc to Pause)\n";
            
            
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option = (Options.size() + option - 1) % Options.size();
                if(option == 0){
                    option = Options.size() -1;
                }
                continue;
            case 's':
                option++;
                option%=Options.size();
                if(option == 0){
                    option = 1;
                }
                continue;
            case '\r':
                break;
            case 27:{
                int choice = PauseMenu();
                if(choice == 0)
                    continue;
                else
                    exit(0);
            }
            default:
                continue;
        }
        break;
    }
    return option-1;
}

Weapon* Shop::ShopWeapons(string Description , string Case){
    vector<Weapon*> Weapons;
    vector<string> Header;
    vector<vector<string>> Options;
    
    if(Case == "Buy"){
        Weapons = weapons;
    }else if(Case == "Sell" || Case == "Upgrade"){
        for(pair<Weapon*,int> p:player->getWeapons()){
            Weapons.push_back(p.first);
        }
    }
    
    if(Weapons.empty()){
        clearScreen();
        cout << "No Weapons Available" << endl << endl << "Press Any Key To Continue";
        getch();
        return nullptr;
    }
    
    int option;
     //         0     1         2       3        4       5            6                  7            8             9    
    Header = {"Name","Price","Type","Capacity","Damage","Ammo","AttackEnergy","ReloadEnergy","MaxAttackAmount","MinDamagePercent"};
    for(Weapon* weapon:Weapons){        
        vector<string> row(Header.size());
        row[0] = weapon->getName();
        
        if(Case == "Buy"){
            row[1] = to_string(int(weapon->getPrice()*1.25)) + "$";
        }else if(Case == "Sell"){
            row[1] = to_string(weapon->getPrice()) + "$";
        }else if(Case == "Upgrade"){
            row[1] = to_string(int(weapon->getPrice())) + "$";
        }
        
        row[2] = " ";
        row[3] = to_string(weapon->getCapacity());
        row[4] = to_string(weapon->getDamage());
        row[5] = " ";
        row[6] = to_string(weapon->getEnergyNeeded());
        row[7] = " ";
        row[8] = " ";
        row[9] = " ";
        if(dynamic_cast<Gun*>(weapon) != nullptr){
            Gun* gun = dynamic_cast<Gun*>(weapon);
            row[7] = to_string(gun->getReloadEnergy());
            row[5] = "[" + to_string(gun->getAmmo()) + "/" + to_string(gun->getMaxAmmo()) + "]";
            
            if(dynamic_cast<Rifle*>(gun) != nullptr){
                Rifle* rifle = dynamic_cast<Rifle*>(weapon);
                row[8] = to_string(rifle->getMaxAttackAmount());
                row[2] = "Rifle";
            }else if(dynamic_cast<Shotgun*>(gun) != nullptr){
                Shotgun* shotgun = dynamic_cast<Shotgun*>(weapon);
                row[9] = to_string(shotgun->getMinDamagePercent())+ "%";
                row[2] ="Shotgun";
            }else if(dynamic_cast<SMG*>(gun) != nullptr){
                row[2] = "SMG";
            }else if(dynamic_cast<Snipe*>(gun) != nullptr){
                row[2] = "Snipe";
            }else{
                row[2] = "Gun";
            }
            
        }else{
            if(dynamic_cast<ColdWeapon*>(weapon) != nullptr){
                row[2] = "ColdWeapon";
            }else if(dynamic_cast<Throwable*>(weapon) != nullptr){
                row[2] ="Throwable";
            }else if(dynamic_cast<Throwable*>(weapon) != nullptr){
                row[2] ="Throwable";
            }
        }
        Options.push_back(row);
    }
    Options.push_back({"Back"," "," "," "," "," "," "," "," "," "});
    
    option = MenuManager(Description + "Choose A Weapon To "+Case+": ",Options,Header);

    if(option  == Options.size()-1)
        return nullptr;

    return Weapons[option];
}


Consumable* Shop::ShopConsumables(string Description , string Case){
    vector<Consumable*> Consumables;
    vector<string> Header;
    vector<vector<string>> Options;
    
    if(Case == "Buy"){
        Consumables = consumables;
    }else if(Case == "Sell"){
        for(pair<Consumable*,int> p: player->getConsumables()){
            for(int i = 1; i <= p.second;i++){
                Consumables.push_back(p.first);
            }
        }
    }
    
    if(Consumables.empty()){
        clearScreen();
        cout << "No Consumables Available" << endl << endl << "Press Any Key To Continue";
        getch();
        return nullptr;
    }
    
    int option;
    Header = {"Name","Price","Capacity","Type","Increase Amount"};
    for(Consumable* consumable : Consumables){
        vector<string> row(Header.size());
        row[0] = consumable->getName();
        
        if(Case == "Buy"){
            row[1] = to_string(int(consumable->getPrice()*1.25)) + "$";
        }else if(Case == "Sell"){
            row[1] = to_string(consumable->getPrice()) + "$";
        }
        
        row[2] = to_string(consumable->getCapacity());
        row[3] = consumable->getType();
        row[4] = to_string(consumable->getAmount());
        Options.push_back(row);
    }
    Options.push_back({"Back"," "," "," "," "});
    
    option = MenuManager(Description + "Choose A Consumable To "+Case+": ",Options,Header);

    if(option  == Options.size()-1)
        return nullptr;
    return Consumables[option];
}

Equipment* Shop::ShopEquipments(string Description , string Case){
    vector<Equipment*> Equipments;
    vector<string> Header;
    vector<vector<string>> Options;
    
    if(Case=="Buy"){
        Equipments =equipments;
        
        if(Equipments.empty()){
        clearScreen();
        cout << "No Equipments Available" << endl << endl << "Press Any Key To Continue";
        getch();
        return nullptr;
    }
    }else if(Case == "Sell"){
        Equipments =  player->getEquipments();
        
        if(player->getArmor() == 0 ){
            clearScreen();
            cout << "No Equipments Available" << endl << endl << "Press Any Key To Continue";
            getch();
            return nullptr;
        }
    }
    
    
    
    int option;
    
    Header = {"Name","Price","Type","ProtectionAmount"};
    for(Equipment* equipment : Equipments){
        
        vector<string> row(Header.size());
        row[0] = equipment->getName();
        
        if(Case=="Buy"){
            row[1] = to_string(int(equipment->getPrice()*1.25));
        }else if(Case == "Sell"){
            row[1] = to_string(equipment->getPrice());
        }
        
        if(dynamic_cast<HeadGear*>(equipment) !=nullptr){
            row[2] = "Head Gear";
        }else if(dynamic_cast<Vest*>(equipment) !=nullptr){
            row[2] = "Vest";
        }else if(dynamic_cast<FootWear*>(equipment) !=nullptr){
            row[2] = "FootWear";
        }else if(dynamic_cast<Boot*>(equipment) !=nullptr){
            row[2] = "Boots";
        }
        row[3] = to_string(equipment->getAmount());
        Options.push_back(row);
    }
    Options.push_back({"Back"," "," "," "});
    
    option = MenuManager(Description + "Choose An Equipment: ",Options,Header);
    

    if(option  == Options.size()-1)
        return nullptr;
    return Equipments[option];
}





string Shop::UpgradeNameChange(string name, int upgradeAmount){ 
    if(upgradeAmount >= 3){
        int spaceIndex = name.size() - 3;
        name = name.substr(0,spaceIndex); 
        name += " " + to_string(upgradeAmount) +"+"; 
    }else if (upgradeAmount == 0){
        name += " +"; 
    }else{
        int spaceIndex = name.size() - 2;
        name = name.substr(0,spaceIndex); 
        name += " " + to_string(upgradeAmount + 1) +"+"; 
    }
    
    return name;
}

void Shop :: Upgrade(Weapon* weapon , string dialogue){
    if(dynamic_cast<Shotgun*>(weapon) != nullptr){
        int choice = Choose(Story + "\n\n"  + getStat() + dialogue + "\n\n" + "Coins needed to Upgrade: " + 
        presicion_string(BaseUpgradePrice * int(pow(1.5 , weapon->getUpgradeAmount()))) + "\n",
                            {"Damage",
                            "Min Damage Percent",
                            "Back"});
        switch (choice){
            case 1:{
                player->removeItem(weapon);
                player->removeCoin(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()));
                Weapon* copy_weapon = new Shotgun(*dynamic_cast<Shotgun *>(weapon));
                copy_weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()) * 0.8));
                copy_weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                copy_weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                copy_weapon->setDamage(int(weapon->getDamage()*1.4));
                
                UpgradesLeft --;
                
                player->addItem(copy_weapon);
                break;
            }
            case 2:
            {
                player->removeItem(weapon);
                player->removeCoin(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()));
                Weapon* copy_weapon = new Shotgun(*dynamic_cast<Shotgun *>(weapon));
                copy_weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()) * 0.8));
                copy_weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                Shotgun* shotgun = dynamic_cast<Shotgun*>(copy_weapon);
                shotgun->setUpgradeAmount(shotgun->getUpgradeAmount()+1);
                shotgun->setMinDamagePercent(shotgun->getMinDamagePercent() + 10);
                
                UpgradesLeft --;
                
                player->addItem(shotgun);
            
            }
            case 3:
                break;
            default:
                break;
        }  
        
        
    }else if(dynamic_cast<Rifle*>(weapon) != nullptr){
        int Upgradeprice = BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount());
        int choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n\n" + "Coins needed to Upgrade: " + 
        to_string(Upgradeprice) + "\n",
                            {"Damage",
                            "Max Attack Amount",
                            "Back"});
        
        switch (choice){
            case 1:{
                player->removeItem(weapon);
                player->removeCoin(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()));
                Weapon* copy_weapon = new Rifle(*dynamic_cast<Rifle *>(weapon));
                copy_weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()) * 0.8));
                copy_weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                copy_weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                copy_weapon->setDamage(int(weapon->getDamage()*1.4));
                
                UpgradesLeft --;
                
                player->addItem(copy_weapon);
                break;
            }
            case 2:
            {
                player->removeItem(weapon);
                player->removeCoin(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()));
                
                Weapon* copy_weapon = new Rifle(*dynamic_cast<Rifle *>(weapon));
                copy_weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()) * 0.8));
                copy_weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                Rifle* rifle = dynamic_cast<Rifle*>(copy_weapon);
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
        int choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n\n" + "Coins needed to Upgrade: " + 
        presicion_string(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount())) + "\n",
                            {"Damage",
                            "Back"});
        
        switch (choice){
            case 1:
                player->removeItem(weapon);
                player->removeCoin(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()));
                Weapon* copy_weapon;
                if(dynamic_cast<Snipe *>(weapon) != nullptr)
                    copy_weapon = new Snipe(*dynamic_cast<Snipe *>(weapon));
                else if(dynamic_cast<SMG *>(weapon) != nullptr)
                    copy_weapon = new SMG(*dynamic_cast<SMG *>(weapon));
                else if(dynamic_cast<ColdWeapon *>(weapon) != nullptr)
                    copy_weapon = new ColdWeapon(*dynamic_cast<ColdWeapon *>(weapon));
                else if(dynamic_cast<Grenade *>(weapon) != nullptr)
                    copy_weapon = new Grenade(*dynamic_cast<Grenade *>(weapon));
                else if(dynamic_cast<BoomRang *>(weapon) != nullptr)
                    copy_weapon = new BoomRang(*dynamic_cast<BoomRang *>(weapon));
                copy_weapon->setPrice(weapon->getPrice() + int(BaseUpgradePrice * pow(1.5 , weapon->getUpgradeAmount()) * 0.8));
                copy_weapon->setName(UpgradeNameChange(weapon->getName(),weapon->getUpgradeAmount()));
                copy_weapon->setUpgradeAmount(weapon->getUpgradeAmount()+1);
                copy_weapon->setDamage(int(weapon->getDamage()*1.4));
                
                UpgradesLeft --;
                
                player->addItem(copy_weapon);
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
        if (player->getBackPackCapacity() >= item->getCapacity()+player->getBackPackWeight())
        {
            player->removeCoin(item->getPrice()*1.25);
            player->addItem(item);
            clearScreen();
            cout << Story << "\n\n";
            cout << shopkeeper->SellDialogue(item);
            cout << "\nPress anything to continue";
            getch();
            removeItem(item);
        }
        else{
            clearScreen();
            cout << Story << "\n\n";
            cout << "Not enough BackPack space\n\n";
            cout << "Press anything to continue";
            getch();
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
    if(dynamic_cast<Weapon *>(item) != nullptr){
        weapons.erase(remove(weapons.begin(),weapons.end(),dynamic_cast<Weapon *>(item)),weapons.end());
    }
    else if(dynamic_cast<Consumable *>(item) != nullptr){
        consumables.erase(remove(consumables.begin(),consumables.end(),dynamic_cast<Consumable *>(item)),consumables.end());
    }
    else if(dynamic_cast<Equipment *>(item) != nullptr){
        equipments.erase(remove(equipments.begin(),equipments.end(),dynamic_cast<Equipment *>(item)),equipments.end());
    }
}

void Shop :: Menu(){
    string dialogue = shopkeeper->HiDialogue();
    while (!WantsToQuit){
        int choice = Choose(Story + "\n\n"  + getStat() + dialogue+ "\n" , 
                            {"Buy",           // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                            "Sell",
                            "Upgrade",
                            "Leave the shop"});
        
        switch (choice){
            case 1: // Player buys an item
                while(true){
                        choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n" ,
                                    {"Weapons",           // Player buys, Shopkeeper sells ( Sell(Item* item) should be called ) 
                                    "Consumables",
                                    "Equipments",
                                    "Back"});
                    
                    switch (choice){
                        case 1:
                        {
                            while(true){
                                Weapon* chosenWeapon =ShopWeapons(Story + "\n\n" + getStat() + dialogue + "\n" , "Buy");
                                if(chosenWeapon == nullptr){
                                    break;
                                }
                                Sell(chosenWeapon);
                            }
                            continue;
                        }
                        case 2:
                        {
                            while (true){
                                Consumable* chosenConsumable = ShopConsumables(Story + "\n\n" + getStat() + dialogue + "\n" , "Buy");
                                if(chosenConsumable == nullptr){
                                    break;
                                }
                                Sell(chosenConsumable);
                            }
                            continue;
                        }
                        case 3:
                        {
                            while(true){
                                Equipment* chosenEquipment = ShopEquipments(Story + "\n\n" + getStat() + dialogue + "\n" , "Buy");
                                if(chosenEquipment ==nullptr){
                                    break;
                                }
                                Sell(chosenEquipment);
                            }
                            continue;
                        }
                        case 4:
                            break;
                        default:
                            continue;
                    }   
                    break;
                }
                continue;
                
            case 2: // Player sells an item
            while (true)
            {
                choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n" ,
                                    {"Weapons",           
                                    "Consumables",
                                    "Equipments",
                                    "Back"});
                    
                    switch (choice){
                        case 1:
                        {
                            while(true){
                                Weapon* chosenWeapon =ShopWeapons(Story + "\n\n" + getStat() + dialogue + "\n" , "Sell");
                                if(chosenWeapon == nullptr){
                                    break;
                                }
                                Buy(chosenWeapon);
                            }
                            continue;
                        }
                        case 2:
                        {
                            while (true){
                                Consumable* chosenConsumable = ShopConsumables(Story + "\n\n" + getStat() + dialogue + "\n" , "Sell");
                                if(chosenConsumable == nullptr){
                                    break;
                                }
                                Buy(chosenConsumable);
                            }
                            continue;
                        }
                        case 3:
                        {
                            while(true){
                                Equipment* chosenEquipment = ShopEquipments(Story + "\n\n" + getStat() + dialogue + "\n" , "Sell");
                                if(chosenEquipment ==nullptr){
                                    break;
                                }
                                Buy(chosenEquipment);
                            }
                            continue;
                        }
                        case 4:
                            break;
                        default:
                            continue;
                    }   
                    break;
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
                while(UpgradesLeft > 0){
                    choice = Choose(Story + "\n\n" + getStat() + dialogue + "\n" ,
                                {"Weapons",           
                                "BackPack",
                                "Back"});
                    switch (choice){
                        case 1:
                            while (UpgradesLeft > 0)
                            {
                                Weapon* ChosenWeapon = ShopWeapons(Story + "\n\n" + getStat() + dialogue + "\n" , "Upgrade");
                                if(ChosenWeapon == nullptr)
                                    break;
                                
                                if(ChosenWeapon->getUpgradeAmount() >= ChosenWeapon->getUpgradeLimit()){
                                    clearScreen();
                                    cout << Story << "\n\n";
                                    cout << shopkeeper->UpgradeLimitDialogue(ChosenWeapon);
                                    cout << "Press anything to continue";
                                    getch();
                                }else if(player->getCoin() < BaseUpgradePrice * pow(1.5 , ChosenWeapon->getUpgradeAmount())){
                                    clearScreen();
                                    cout << Story << "\n\n";
                                    cout << shopkeeper->NoMoneyDialogue();
                                    cout << "Press anything to continue";
                                    getch();
                                }else{
                                    Upgrade(ChosenWeapon , dialogue);
                                } 
                            }
                            continue;
                        case 2:
                            if(player->getBackPackCapacity() >= 90){
                                clearScreen();
                                cout << Story << "\n\n" << shopkeeper->getName() << ": You already have the Best BackPack!!!\n";
                                cout << "Press anything to continue\n";
                                getch();
                            }
                            else if(player->getCoin() >= 30){
                                player->setBackPackCapacity(player->getBackPackCapacity() + 15);
                                player->removeCoin(30);
                                clearScreen();
                                cout << Story << "\n\n" << shopkeeper->getName() << ": Your backpack has been Upgraded.(+15 capacity)\n";
                                cout << "Press anything to continue\n";
                                getch();
                                UpgradesLeft--;
                            }
                            else{
                                clearScreen();
                                cout << shopkeeper->NoMoneyDialogue();
                                cout << "Press anything to continue\n";
                                getch();
                            }
                            continue;
                        case 3:
                            break;
                        default:
                            break;
                    }
                    break;
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
    "injuries but you're too \nexhausted to actually care. Suddenly you notice a red sign, acutually a plus (+) sign on a building. "
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
                {"Restore half HP (" + to_string(HalfHealPrice) + "$)",
                "Restore full HP (" + to_string(FullHealPrice) + "$)", 
                "Increase max HP by 20% (" + to_string(MaxHpIncreasePrice) + "$)",
                "Leave the Hospital"}
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
        cout << "Press anything to Continue\n";
        getch();
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
    cout << "Press anything to Continue\n";
    getch();
    default:
        break;
    }
}

Fight :: Fight(string Story, Player* player, int type, vector<Character*> enemies, vector<Item*> items, int droppedCoins, vector<Relic*> relics){
    this -> Story = Story;
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
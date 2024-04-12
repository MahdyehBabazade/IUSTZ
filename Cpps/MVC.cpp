#pragma once
#include "../Headers/MVC.h"
#include "../Headers/creature.h"
#include "functions.cpp"
#include <vector>
#include <string>
#include <conio.h>
#include <iomanip>
#include <algorithm>

using namespace std;

int View::FightView::getMaxWidth(vector<vector<string>> &entry){
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

View::FightView::FightView(Model::FightModel* fightModel){this->model = fightModel;}

void View::FightView::DamageInfo(Weapon* weapon){
    clearScreen();
    cout << model->getStory() << "\n";
    cout << "Dealt " << weapon->getDamage() << " Damage" << endl;
}


int View::FightView::MenuManager(string Description,vector<string> Options){
    int option = 0;
    int vecSize = Options.size();
    while(true){
        clearScreen();
        cout << model->getStory() << "\n";
        cout << Description << endl;
        
        for(int i=0 ; i<Options.size(); i++){
            if(i == option){
                cout << green;
            }
            cout << i + 1 << ". " << Options[i];
            cout << reset << endl;
        }
        cout << "\nMove between options with W & S and choose the option with Enter.(Press Esc to Pause)\n";
        
        if(!model->getEnemies().empty())
            showCharacters();
            
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option = (Options.size() + option - 1) % Options.size();
                continue;
            case 's':
                option++;
                option%=Options.size();
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
    return option+1;
}

int View::FightView::MenuManager(string Description,vector<vector<string>> Options, vector<string> Header){
    Options.insert(Options.begin(),Header);
    
    int width = getMaxWidth(Options);
    
    int option = 1;
    int vecSize = Options[0].size();
    while(true){
        clearScreen();
        cout << model->getStory() << "\n";
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
        
        if(!model->getEnemies().empty())
            showCharacters();
        if(model->getEquipmentsMenu())
            showArmor();
            
            
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


Relic* View::FightView::ChooseRelic(vector<Relic*> Relics){
    vector<string> Header = {"Name","MaxHP","MaxEnergy"};
    vector<vector<string>> Options;
    for(Relic* relic : Relics){
        
        vector<string> row(Header.size());
        row[0] = relic->getName();
        row[1] = to_string(relic->getMaxHP());
        row[2] = to_string(relic->getMaxEnergy());
        Options.push_back(row);
    }

    int option = MenuManager("Choose A Relic: ",Options,Header);
    
    return Relics[option];
}


Consumable* View::FightView::ChooseConsumable(vector<pair<Consumable*,int>> Consumables , string Descriptions){
    if(Consumables.empty()){
        clearScreen();
        Prompt("No Consumables Left");
        return nullptr;
    }
    
    vector<string> Header;
    vector<vector<string>> Options;
    int option;
    
    if(!model->getEnemies().empty()){
        Header = {"Name","Type","Increase Amount"};
        for(pair<Consumable*,int> x : Consumables){
            Consumable* consumable = x.first;
            int amount = x.second;
            
            vector<string> row(Header.size());
            row[0] = (consumable->getName() + "(x" + to_string(amount) + ")");
            row[1] = consumable->getType();
            row[2] = to_string(consumable->getAmount());
            Options.push_back(row);
        }
        Options.push_back({"Back"," "," "});
        
        option = MenuManager("Choose A Consumable: ",Options,Header);
    }else{
        Header = {"Name","Capacity","Type","Increase Amount"};
        for(pair<Consumable*,int> x : Consumables){
            Consumable* consumable = x.first;
            int amount = x.second;
            
            vector<string> row(Header.size());
            row[0] = (consumable->getName() + "(x" + to_string(amount) + ")");
            row[1] = to_string(consumable->getCapacity());
            row[2] = consumable->getType();
            row[3] = to_string(consumable->getAmount());
            Options.push_back(row);
        }
        Options.push_back({"Back"," "," "," "});
        
        option = MenuManager("Choose A Consumable To " + Descriptions + " (Capacity: "+ to_string(model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight()) + "):"
                            ,Options,Header);
    }

    if(option  == Options.size()-1)
        return nullptr;
    return Consumables[option].first;
}


Character* View::FightView::ChooseEnemy(vector<Character*> Enemies){
    vector<vector<string>> Options;
    for(int i = 0;i < 4; i ++){
        vector<string> row;
        if(i == 0){
            for(Character* Enemy: Enemies){
                row.push_back(Enemy->getName());
            }
            row.push_back("Back");        
            
        }else if(i == 1){
            for(Character* Enemy: Enemies){
                row.push_back("HP:[" + to_string(Enemy->getHP()) + "/" + to_string(Enemy->getMaxHP()) + "]");
            }
            row.push_back(" ");
        }else if(i == 2){
            for(Character* Enemy: Enemies){
                row.push_back("Armor: " + presicion_string(Enemy->getArmor()));
            }
            row.push_back(" ");
        }else if(i == 3){
            for(Character* Enemy: Enemies){
                row.push_back("Shield: " + to_string(Enemy->getShield()));
            }
            row.push_back(" ");
        }
        Options.push_back(row);
    }
    
    int rows = Options.size();
    int width = 0;
    for(int i=0 ; i<rows ; i++){
        for(int j=0; j<Options[i].size() ; j++){
            int len = Options[i][j].length();
            if(len > width)
                width = len;
        }
    }
    
    int option = 0;
    int vecSize = Options[0].size();
    while(true){
        clearScreen();
        cout << model->getStory() << "\n";
        for(int i=0 ; i<4 ; i++){
            for(int j=0 ; j<vecSize ; j++){
                if(j == option ){
                    cout<< green ;
                    cout << left << setw(width) << Options[i][j] << " " ;
                    cout<< reset;
                }else{
                    cout << left << setw(width) << Options[i][j] << " " ;                 
                }
            }
            cout << endl;
        }
        cout << "\nMove between options with A & D and choose the option with Enter.(Press Esc to Pause)\n";
        
        char key = _getch();
        switch(tolower(key))
        {
            case 'a':
                option = (vecSize + option - 1) % vecSize;
                continue;
            case 'd':
                option++;
                option%=vecSize;
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
    
    if(option  == vecSize-1)
        return nullptr;
    return Enemies[option];
    
}

vector<Character*> View::FightView::ChooseEnemies(vector<Character*> Enemies , int amount){
    bool breaker = true;
    int vecSize = Enemies.size();
    vector<vector<string>> options;
    for(int i =0 ; i < 4;i++){
        vector<string> row;
        if(i==0){
            for(Character* Enemy:Enemies){
                row.push_back(Enemy->getName());
            }
            row.push_back("Reset");
            row.push_back("Done/Back");
        }else{
            if(i == 1){
                for(Character* Enemy:Enemies){
                    row.push_back("HP:[" + to_string(Enemy->getHP()) + "/" + to_string(Enemy->getMaxHP()) + "]");
                }
            }else if(i == 2){
                for(Character* Enemy:Enemies){
                    row.push_back("Armor:" + presicion_string(Enemy->getArmor()));
                }
            }else{
                for(Character* Enemy:Enemies){
                    row.push_back("Shield:" + Enemy->getShield());
                }
            }
            row.push_back(" ");
            row.push_back(" ");
        }
        options.push_back(row);
    }
    int rows = options.size();
    int width = 0;
    for(int i=0 ; i<rows ; i++){
        for(int j=0; j<options[i].size() ; j++){
            int len = options[i][j].length();
            if(len > width)
                width = len;
        }
    }
    vector<bool> option;
    for(int i = 0; i < vecSize + 2; i++){
        option.push_back(true);
    }
    vector<bool> Chosen;
    for(int i = 0; i < vecSize + 2; i++){
        Chosen.push_back(false);
    }
    int m = 0;
    while(true){
        clearScreen();
        cout << model->getStory() << "\n";
        vector<int> Posoptions;
        for(int i = 0;i < vecSize + 2; i++){
            if(option[i] && !Chosen[i])
                Posoptions.push_back(i);
        }
        for(int i=0 ; i<4 ; i++){
            for(int j=0 ; j<vecSize + 2 ; j++){
                if(j == Posoptions[m % Posoptions.size()])
                    cout<< green;
                if (!option[j])
                    cout<< grey;
                if(Chosen[j])
                    cout<< yellow;
                
                if( j > 0){
                    cout << left << setw(width + 4) << options[i][j] << " " ;
                }else{
                    cout<< left << setw(width + 4) << options[i][j] << " ";
                }
                cout<< reset;          
            }
            cout << endl;    
        }
        cout << "\nMove between options with A & D and choose the option with Enter.(Press Esc to Pause)\n";
    
        char key = _getch();
        switch(tolower(key))
        {
        case 'a':
                m = (m - 1 + Posoptions.size()) % Posoptions.size();
            continue;
        case 'd':
                m = (m + 1) % Posoptions.size();
            continue;
        case '\r':
            if(Posoptions[m % Posoptions.size()] == vecSize ){  // if it was reset
                for(int i=0 ; i< vecSize + 2; i++){
                    option[i] = true;
                    Chosen[i] = false;
                }
                m = 0;
            }
            else if(Posoptions[m % Posoptions.size()] == vecSize + 1){ // if it was done
                vector<Character*> selected;
                for(int i=0; i < option.size() ; i++){
                    if(Chosen[i])
                        selected.push_back(Enemies[i]);
                }
                return selected;
            }
            else{
                if(count(Chosen.begin(), Chosen.end(), true) < amount - 1){
                    Chosen[Posoptions[m % Posoptions.size()]] = true;
                }
                else if(count(Chosen.begin(), Chosen.end(), true) == amount - 1){
                    for(int i = 0; i < vecSize; i++){
                        Chosen[Posoptions[m % Posoptions.size()]] = true;
                        option[i] = false;
                    }
                }
            }
            continue;
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
    return {};
}

Weapon* View::FightView::ChooseWeapon(vector<pair<Weapon*,int>> Weapons , string Description){
    if(Weapons.empty()){
        Prompt("No Weapons Left");
        return nullptr;
    }
    vector<string> Header;
    vector<vector<string>> Options;
    
    int option;
    if(!model->getEnemies().empty()){
        //        0        1     2              3          4                  5                6               7                 
        Header = {"Name","Type","Damage","Ammo/Amount","AttackEnergy","ReloadEnergy","MaxAttackAmount","MinDamagePercent"};
        for(pair<Weapon*,int> p:Weapons){
            Weapon* weapon = p.first;
            int Amount = p.second;
            
            vector<string> row(Header.size());
            row[0] = weapon->getName();
            row[1] = " ";
            row[2] = to_string(weapon->getDamage());
            row[3] = " ";
            row[4] = to_string(weapon->getEnergyNeeded());
            row[5] = " ";
            row[6] = " ";
            row[7] = " ";
            if(dynamic_cast<Gun*>(weapon) != nullptr){
                Gun* gun = dynamic_cast<Gun*>(weapon);
                row[5] = to_string(gun->getReloadEnergy());
                row[3] = "[" + to_string(gun->getAmmo()) + "/" + to_string(gun->getMaxAmmo()) + "]";
                
                if(dynamic_cast<Rifle*>(gun) != nullptr){
                    Rifle* rifle = dynamic_cast<Rifle*>(weapon);
                    row[6] = to_string(rifle->getMaxAttackAmount());
                    row[1] = "Rifle";
                }else if(dynamic_cast<Shotgun*>(gun) != nullptr){
                    Shotgun* shotgun = dynamic_cast<Shotgun*>(weapon);
                    row[7] = to_string(shotgun->getMinDamagePercent())+ "%";
                    row[1] ="Shotgun";
                }else if(dynamic_cast<SMG*>(gun) != nullptr){
                    row[1] = "SMG";
                }else if(dynamic_cast<Snipe*>(gun) != nullptr){
                    row[1] = "Snipe";
                }else{
                    row[1] = "Gun";
                }
                
            }else{
                if(dynamic_cast<ColdWeapon*>(weapon) != nullptr){
                    row[1] = "ColdWeapon";
                }else if(dynamic_cast<Throwable*>(weapon) != nullptr){
                    row[1] ="Throwable";
                }else if(dynamic_cast<Throwable*>(weapon) != nullptr){
                    row[1] ="Throwable";
                }
                row[3] = to_string(Amount);
            }
            Options.push_back(row);
        }
        Options.push_back({"Back"," "," "," "," "," "," "," "});
        
        option = MenuManager("Choose A Weapon: ",Options,Header);
    }else{
        //         0     1           2       3          4            5            6                      7            8                 
        Header = {"Name","Type","Capacity","Damage","Ammo/Amount","AttackEnergy","ReloadEnergy","MaxAttackAmount","MinDamagePercent"};
        for(pair<Weapon*,int> p:Weapons){
            Weapon* weapon = p.first;
            int Amount = p.second;
            
            vector<string> row(Header.size());
            row[0] = weapon->getName();
            row[1] = " ";
            row[2] = to_string(weapon->getCapacity());
            row[3] = to_string(weapon->getDamage());
            row[4] = " ";
            row[5] = to_string(weapon->getEnergyNeeded());
            row[6] = " ";
            row[7] = " ";
            row[8] = " ";
            if(dynamic_cast<Gun*>(weapon) != nullptr){
                Gun* gun = dynamic_cast<Gun*>(weapon);
                row[6] = to_string(gun->getReloadEnergy());
                row[4] = "[" + to_string(gun->getAmmo()) + "/" + to_string(gun->getMaxAmmo()) + "]";
                
                if(dynamic_cast<Rifle*>(gun) != nullptr){
                    Rifle* rifle = dynamic_cast<Rifle*>(weapon);
                    row[7] = to_string(rifle->getMaxAttackAmount());
                    row[1] = "Rifle";
                }else if(dynamic_cast<Shotgun*>(gun) != nullptr){
                    Shotgun* shotgun = dynamic_cast<Shotgun*>(weapon);
                    row[8] = to_string(shotgun->getMinDamagePercent())+ "%";
                    row[1] ="Shotgun";
                }else if(dynamic_cast<SMG*>(gun) != nullptr){
                    row[1] = "SMG";
                }else if(dynamic_cast<Snipe*>(gun) != nullptr){
                    row[1] = "Snipe";
                }else{
                    row[1] = "Gun";
                }
                
            }else{
                row[4] = to_string(Amount);
                if(dynamic_cast<ColdWeapon*>(weapon) != nullptr){
                    row[1] = "ColdWeapon";
                }else if(dynamic_cast<Throwable*>(weapon) != nullptr){
                    row[1] ="Throwable";
                }else if(dynamic_cast<Throwable*>(weapon) != nullptr){
                    row[1] ="Throwable";
                }
            }
            Options.push_back(row);
        }
        Options.push_back({"Back"," "," "," "," "," "," "," "," "});
        
        option = MenuManager("Choose A Weapon To " + Description + ": (Capacity:"+ to_string(model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight()) +"):"
                            ,Options,Header);
    }

    if(option  == Options.size()-1)
        return nullptr;
    return Weapons[option].first;
}

void View::FightView::showArmor(){
    vector<Equipment*> Equipments = model->getPlayer()->getEquipments();
    vector<int> amounts;
    for(Equipment* equipment: Equipments){
        if(equipment != nullptr){
            amounts.push_back(equipment->getAmount());
        }else{
            amounts.push_back(0);
        }
    }
    clearScreen();
    cout << model->getStory() << "\n";
    cout << "[Head Gear]: " << amounts[0]<< endl;
    cout << "[Vest]: " << amounts[1] << endl;
    cout << "[Foot Wear]: " << amounts[2] << endl;
    cout << "[Boots]: " << amounts[3];
}

Equipment* View::FightView::ChooseEquipment(vector<pair<Equipment*,int>> Equipments, string Description){
    if(Equipments.empty()){
        clearScreen();
        Prompt("No Equipments Left");
        return nullptr;
    }
    
    vector<string> Header;
    vector<vector<string>> Options;
    int option;
    
    Header = {"Name","Type","ProtectionAmount"};
    for(pair<Equipment*,int> x : Equipments){
        Equipment* equipment = x.first;
        int amount = x.second;
        
        vector<string> row(Header.size());
        row[0] = (equipment->getName() + "(x" + to_string(amount) + ")");
        
        if(dynamic_cast<HeadGear*>(equipment) !=nullptr){
            row[1] = "Head Gear";
        }else if(dynamic_cast<Vest*>(equipment) !=nullptr){
            row[1] = "Vest";
        }else if(dynamic_cast<FootWear*>(equipment) !=nullptr){
            row[1] = "FootWear";
        }else if(dynamic_cast<Boot*>(equipment) !=nullptr){
            row[1] = "Boots";
        }
        row[2] = to_string(equipment->getAmount());
        Options.push_back(row);
    }
    Options.push_back({"Back"," "," "});
    
    option = MenuManager("Choose An Equipment: ",Options,Header);
    

    if(option  == Options.size()-1)
        return nullptr;
    return Equipments[option].first;
}

void View::FightView::showCharacters(){
    vector<Character*> Characters = model->getEnemies();
    Characters.insert(Characters.begin(),model->getPlayer());
    
    cout << endl;
    vector<vector<string>> Details;
    for(int i = 0;i < 4; i ++){
        vector<string> row;
        if(i == 0){
            for(Character* character: Characters){
                row.push_back(character->getName());
            }        
            
        }else if(i == 1){
            for(Character* character: Characters){
                row.push_back("HP:[" + to_string(character->getHP()) + "/" + to_string(character->getMaxHP()) + "]");
            }
        }else if(i == 2){
            for(Character* character: Characters){
                row.push_back("Armor: " + presicion_string(character->getArmor()));
            }
            
        }else if(i == 3){
            for(Character* character :Characters){
                row.push_back("Shield: " + to_string(character->getShield()));
            }
        }
        Details.push_back(row);
    }
    
    vector<string> row;
    row.push_back("Energy: [" + to_string(model->getPlayer()->getEnergy()) + "/" + to_string(model->getPlayer()->getMaxEnergy()) + "]");
    for(int i = 0; i <model->getEnemies().size();i++){
        row.push_back(" ");
    }
    Details.push_back(row);
    
    int width = getMaxWidth(Details);
    
    int vecSize = Details[0].size();
    
    for(int i=0 ; i<Details.size() ; i++){
        for(int j=0 ; j<vecSize ; j++){
            if(j == 0){
                cout << left << setw(width+40) << Details[i][j] << " " ;
                continue;
            }
            cout << left << setw(width) << Details[i][j] << " " ;
        }
        cout << endl;
    }
}

void View::FightView::Prompt(string entry){
    clearScreen();
    cout << model->getStory() << "\n";
    cout << entry << endl << endl <<"Press any key to continue...\n";
    _getch();
}
void View::FightView::Prompt(){
    cout << endl << endl <<"Press any key to continue...\n";
    _getch();
}
void View::FightView::Prompt(vector<string> entries){
    clearScreen();
    cout << model->getStory() << "\n";
    for(string& entry:entries){
        cout << entry << endl;
    }
    cout << endl << endl <<"Press any key to continue...\n";
    _getch();
}
void View::FightView::print(string entry){
    cout << entry << endl;
}


//---------------------------------------------------------------------------------------------
Model::FightModel::FightModel(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,string Story ,vector<Relic*> Relics){
    this -> player = player;
    this -> Enemies = Enemies;
    this -> Items = Items;
    this -> droppedCoins = droppedCoins;
    this -> Story = Story;
    this -> Relics = Relics;
    Round=0;
    EquipmentsMenu = false;
}

void Model::FightModel::setRound(int round){ Round = round ;}

int Model::FightModel::getRound(){ return Round; }

Player* Model::FightModel::getPlayer(){ return player;}


vector<Character*> Model::FightModel::getEnemies(){ return Enemies;}

int Model::FightModel::getCoins(){ return droppedCoins;}

string Model::FightModel::getStory(){return Story;}

vector<Item*> Model::FightModel::getItems(){return Items;}

void Model::FightModel::setItems(vector<Item*> Items){this->Items = Items;}

vector<Relic*> Model::FightModel::getRelics(){return Relics;}

void Model::FightModel::setEnemies(vector<Character*> Enemies){this -> Enemies = Enemies;}

void Model::FightModel::setPlayer(Player* player){this->player=player;};

void Model::FightModel::setEqipmentsMenu(bool entry){EquipmentsMenu = entry;}
bool Model::FightModel::getEquipmentsMenu(){return EquipmentsMenu;}
//---------------------------------------------------------------------------------------------
Control::FightControl::FightControl(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,string Story,vector<Relic*> Relics) {
    model = new Model::FightModel(player, Enemies,Items,droppedCoins,Story,Relics);
    view = new View::FightView(model);
}

void Control::FightControl::StartFight(){
    while(true){
        model->setRound(model->getRound() + 1);
        int round = model->getRound();
        if(round % 2 != 0){
            PlayerTurn();
            if(model->getEnemies().empty())
                break;
            model->getPlayer()->setEnergy(model->getPlayer()->getMaxEnergy());
        }
        else if(round % 2 == 0){
            EnemiesTurn();
            if(model->getPlayer()->getHP() <= 0){
                break;
            }
        }
    }
    if(model->getPlayer()->getHP() >0)
        EndFight();
}

void Control::FightControl::RemoveEnemies(){
    bool hascleared = false;
    vector<Character*> Enemies = model->getEnemies();
    for(int i = Enemies.size()-1 ; i >= 0  ; i--){
        Character* Enemy = Enemies[i];
        if(Enemy->getHP() <=0){
            if(!hascleared){
                clearScreen();
                hascleared = true;
            }
            Enemies.erase(Enemies.begin() + i);
            view->print(Enemy->getName() + ":" +Enemy->DeathDialogue());
            model->setEnemies(Enemies);
            delete Enemy;
        }
    }
    if(hascleared){
        view->Prompt();
    }
}

void Control::FightControl::PlayerTurn(){
    //1. weapons  2.consumables  3.end round
    while(!model->getEnemies().empty()){
        int choice = view->MenuManager("Choose An Option: ",{"Weapons","Consumables","End Round"});
        
        switch (choice)
        {
            case 1:
                while(!model->getEnemies().empty()){
                    Weapon* weapon = view->ChooseWeapon(model->getPlayer()->getWeapons() , "");
                    if(weapon == nullptr)
                        break;
    
                    if(weapon->getEnergyNeeded() > model->getPlayer()->getEnergy()){
                        view->Prompt("Not Enough Energy");
                        getch();
                        continue;
                    }
                    if(dynamic_cast<Gun *>(weapon) != nullptr){
                        Gun* gun = dynamic_cast<Gun*>(weapon);
                        
                        while (!model->getEnemies().empty())
                        {
                            // 1.attack   2.reload  3.back
                            int option = view->MenuManager("Choose An Option: ",{"Attack", "Reload", "Back"});
                            
                            switch (option)
                            {
                                case 1:
                                    if(gun->getAmmo() ==0){
                                            view->Prompt("Not Enough Ammo");
                                            continue;
                                    }
                                    
                                    if(dynamic_cast<Rifle *>(gun) != nullptr){
                                        Rifle* rifle = dynamic_cast<Rifle*>(gun);
                                        vector<Character*> chosenEnemies = view->ChooseEnemies(model->getEnemies(),min(rifle->getMaxAttackAmount(),rifle->getAmmo()));
                                        if(chosenEnemies.empty())
                                            continue;
                                        rifle->Attack(chosenEnemies);
                                        
                                    }else if(dynamic_cast<SMG *>(gun) != nullptr){
                                        SMG* smg = dynamic_cast<SMG*>(gun);
                                        vector<Character*> ShuffledEnemies = ShuffleVec(model->getEnemies());
                                        vector<Character*> ChosenEnemies(ShuffledEnemies.begin(),ShuffledEnemies.begin()+min(int(ShuffledEnemies.size()),smg->getAmmo()));
                                        smg->Attack(ChosenEnemies);
                                        
                                    }else if(dynamic_cast<Shotgun *>(gun) != nullptr){
                                        Shotgun* shotGun = dynamic_cast<Shotgun*>(gun);
                                        Character* Enemy = view->ChooseEnemy(model->getEnemies());
                                        if(Enemy == nullptr)
                                            continue;
                                        shotGun->Attack(model->getEnemies(),Enemy);
                                        
                                    }else if(dynamic_cast<Snipe *>(gun) != nullptr){
                                        Snipe* snipe = dynamic_cast<Snipe*>(gun);
                                        Character* Enemy = view->ChooseEnemy(model->getEnemies());
                                        if(Enemy == nullptr)
                                            continue;;
                                        snipe->Attack(model->getEnemies(),Enemy);
                                    }
                                    else{ 
                                        Character* Enemy = view->ChooseEnemy(model->getEnemies());
                                        if(Enemy == nullptr)
                                            continue;   
                                        
                                        gun->Attack(Enemy);
                                        
                                    }
                                    RemoveEnemies();
                                    model->getPlayer()->setEnergy(model->getPlayer()->getEnergy()-weapon->getEnergyNeeded());
                                    view->DamageInfo(weapon);
                                
                                    continue;
                                case 2:
                                    if(model->getPlayer()->getEnergy() < gun->getReloadEnergy()){
                                        view->Prompt("Not Enough Energy");
                                    }else{
                                        gun->Reload();
                                        model->getPlayer()->setEnergy(model->getPlayer()->getEnergy() - gun->getReloadEnergy());
                                    }
                                    continue;
                                case 3:
                                    break;
                                default:
                                    continue;
                            }
                            break;
                        }
                        
                            
                    }else if(dynamic_cast<Throwable *>(weapon) != nullptr){
                        Throwable* throwable = dynamic_cast<Throwable*>(weapon);
                        throwable->Attack(model->getEnemies());
                        model->getPlayer()->removeItem(throwable);
                        
                        RemoveEnemies();
                        model->getPlayer()->setEnergy(model->getPlayer()->getEnergy()-weapon->getEnergyNeeded());
                        view->DamageInfo(weapon);
                        
                    }else if(dynamic_cast<ColdWeapon *>(weapon) != nullptr){
                        ColdWeapon* coldWeapon = dynamic_cast<ColdWeapon*>(weapon);
                        while (!model->getEnemies().empty())
                        {
                            int option = view->MenuManager("Choose An Option: ",{"Attack","Throw(+20\% Damage)","Back"});
                            switch (option)
                            {
                                case 1:
                                {
                                    Character* Enemy = view->ChooseEnemy(model->getEnemies());
                                    if(Enemy == nullptr)
                                        continue;
                                    coldWeapon->Attack(Enemy);
                                    RemoveEnemies();
                                    model->getPlayer()->setEnergy(model->getPlayer()->getEnergy()-weapon->getEnergyNeeded());
                                    view->DamageInfo(weapon);
                                    break;
                                }
                                case 2:
                                {
                                    Character* Enemy = view->ChooseEnemy(model->getEnemies());
                                    if(Enemy == nullptr)
                                        continue;
                                    coldWeapon->Throw(Enemy);
                                    model->getPlayer()->removeItem(coldWeapon);
                                    RemoveEnemies();
                                    model->getPlayer()->setEnergy(model->getPlayer()->getEnergy()-weapon->getEnergyNeeded());
                                    view->DamageInfo(weapon);
                                    break;
                                }
                                case 3:
                                    break;
                                default:
                                    continue;
                            }
                            break;    
                        }  
                    }else{
                        Character* Enemy = view->ChooseEnemy(model->getEnemies());
                        if(Enemy == nullptr)
                            continue;
                        weapon->Attack(Enemy);
                        RemoveEnemies();
                        model->getPlayer()->setEnergy(model->getPlayer()->getEnergy()-weapon->getEnergyNeeded());
                        view->DamageInfo(weapon);
                    }
                    
                }
                continue;
            case 2:
                while (!model->getEnemies().empty())
                {
                    Consumable* consumable = view->ChooseConsumable(model->getPlayer()->getConsumables(), "");
                    if(consumable == nullptr)
                        break;
                    if(consumable->getType() == "HPPotion"){
                        if (model->getPlayer()->getHP() >= model->getPlayer()->getMaxHP())
                        {
                            view->Prompt("You Already Have Full HP");
                            continue;
                        }
                        
                    }else if(consumable->getType() == "ShieldPotion"){
                        if (model->getPlayer()->getShield() >= 100)
                        {
                            view->Prompt("You Already Have Full Shield");
                            continue;
                        }
                        
                    }else if(consumable->getType() == "EnergyPotion"){
                        if (model->getPlayer()->getEnergy() >= model->getPlayer()->getMaxEnergy())
                        {
                            view->Prompt("You Already Have Full Energy");
                            continue;
                        }
                    }
                    model->getPlayer()->Consume(consumable);
                }
                continue;
                
            case 3:
                break;
            default:
                continue;
        }
        break;
    }
}

void Control::FightControl::EnemiesTurn(){
    clearScreen();
    for(Character* Enemy: model->getEnemies()){
        if(dynamic_cast<HumanEnemy*>(Enemy) != nullptr){
            HumanEnemy* humanEnemy = dynamic_cast<HumanEnemy*>(Enemy);
            
            view->print(humanEnemy->getName() + ": " + humanEnemy->RajazKhani());
            humanEnemy->StateMachine(model->getPlayer(),this);
            view->print("");
        }else{
            Zombie* zombie = dynamic_cast<Zombie*>(Enemy);
            view->print(zombie->getName() + ": ");
            zombie->Attack(model->getPlayer(),this);
            view->print("");
        }
    }
    view->Prompt();
}

View::FightView* Control::FightControl::getView(){return view;}

void Control::FightControl::EndFight(){
    view->Prompt({"You Survived The Fight! (Coins +"+ to_string(model->getCoins()) + ")"," Loot What You need"});
    
    
    model->getPlayer()->addCoin(model->getCoins());
    vector<pair<Weapon*,int>> weapons;
    vector<pair<Consumable*,int>> consumables;
    vector<pair<Equipment*,int>> equipments;
    for(Item* items : model->getItems()){
        if(dynamic_cast<Weapon*>(items) != nullptr){
            weapons.push_back(make_pair(dynamic_cast<Weapon*>(items),1));
        }else if(dynamic_cast<Consumable*>(items) != nullptr){
            consumables.push_back(make_pair(dynamic_cast<Consumable*>(items),1));
        }else if(dynamic_cast<Equipment*>(items) != nullptr){
            equipments.push_back(make_pair(dynamic_cast<Equipment*>(items),1));
        }
    }
    while(true){
        int choice = view->MenuManager("Choose An Option (Capacity: "+ to_string(model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight()) +"):",
                                    {"Dropped Items","Inventory","Continue"});
        switch(choice)
        {
            case 1:
                while(true){
                    choice = view->MenuManager("Choose An Option (Capacity: "+ to_string(model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight()) +"):"
                                        ,{"Dropped Weapons","Dropped Consumables", "Dropped Equipments", "Back"}); 
                    if(choice == 1){
                        while ((true))
                        {
                            Weapon* ChosenWeapon = view->ChooseWeapon(weapons , "pick");
                            if(ChosenWeapon == nullptr)
                                break;
                            else{
                                if(ChosenWeapon->getCapacity() > (model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight())){
                                    view->Prompt("Not Enough BackPack Space");
                                    continue;
                                }else{
                                    model->getPlayer()->addItem(ChosenWeapon);
                                    weapons.erase(remove(weapons.begin(),weapons.end(),make_pair(ChosenWeapon,1)),weapons.end());
                                }
                            }
                        }
                        
                    }else if(choice == 2){
                        while (true)
                        {
                            Consumable* ChosenConsumable = view->ChooseConsumable(consumables , "pick");
                            if(ChosenConsumable == nullptr)
                                break;
                            else{
                                if(ChosenConsumable->getCapacity() > (model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight())){
                                    view->Prompt("Not Enough BackPack Space");
                                    continue;
                                }else{
                                    model->getPlayer()->addItem(ChosenConsumable);
                                    consumables.erase(remove(consumables.begin(),consumables.end(),make_pair(ChosenConsumable,1)),consumables.end());
                                }
                            } 
                        }
                        
                    }else if(choice == 3){
                        while (true)
                        {
                            model->setEqipmentsMenu(true);
                            Equipment* ChosenEquipment = view->ChooseEquipment(equipments , "pick" );
                            if(ChosenEquipment == nullptr){
                                model->setEqipmentsMenu(false);
                                break;
                            }else{
                                if(ChosenEquipment->getCapacity() > (model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight())){
                                    view->Prompt("Not Enough BackPack Space");
                                    continue;
                                }else{
                                    model->getPlayer()->addItem(ChosenEquipment);
                                    equipments.erase(remove(equipments.begin(),equipments.end(),make_pair(ChosenEquipment,1)),equipments.end());
                                }
                            }   
                        }
                        
                    }else{
                        break;
                    }
                }
                continue;
            case 2:
                while(true){
                    choice = view->MenuManager("Choose An Option (Capacity: "+ to_string(model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight()) +"):"
                                        , {"Weapon" , "Consumable" , "Back"});
                    if(choice == 1){
                        while(true){
                            Weapon* weapon = view->ChooseWeapon(model->getPlayer()->getWeapons(), "drop");
                            if(weapon == nullptr)
                                break;
                            else{
                                view->Prompt("you removed " + weapon->getName() + " from your inventory(+" + to_string(weapon->getCapacity()) + " capacity)");
                                model->getPlayer()->removeItem(weapon);
                                
                                weapons.push_back(make_pair(weapon,1));
                            }
                        }
                    }else if(choice == 2){
                        while(true){
                            Consumable* consumable = view->ChooseConsumable(model->getPlayer()->getConsumables() , "drop");
                            if(consumable == nullptr)
                                break;
                            else{
                                view->Prompt("You removed " + consumable->getName() + " from your inventory(+" + to_string(consumable->getCapacity())+ " capacity)");
                                model->getPlayer()->removeItem(consumable);
                                
                                consumables.push_back(make_pair(consumable,1));
                            }
                        }
                    }else{
                        break;
                    }
                } 
                continue;    
            case 3:
                break;
            default:
                continue;                   
        }
        break;
    }
    
    if(!model->getRelics().empty()){
        Relic* relic = view->ChooseRelic(model->getRelics());
        model->getPlayer()->addRelic(relic);
    }    
    model->getPlayer()->setEnergy(model->getPlayer()->getMaxEnergy());
    model->getPlayer()->setShield(0);
    model->getPlayer()->setHP(model->getPlayer()->getMaxHP());
    for(pair<Weapon*,int> p:model->getPlayer()->getWeapons()){
        Weapon* weapon = p.first;
        if(dynamic_cast<Gun*>(weapon) != nullptr){
            Gun* gun = dynamic_cast<Gun*>(weapon);
            gun->Reload();
        }
    }
    
    
    
}  
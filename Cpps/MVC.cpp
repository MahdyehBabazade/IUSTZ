#include "../Headers/MVC.h"
#include "../Headers/creature.h"
#include "functions.cpp"
#include <vector>
#include <string>
#include <conio.h>
#include <iomanip>
#include <algorithm>

using namespace std;

View::FightView::FightView(Model::FightModel* fightModel){
    this->model = fightModel;
}

void View::FightView::DamageInfo(Weapon* weapon){
    clearScreen();
    cout << "Dealt " << weapon->getDamage() << " Damage" << endl;
}

void View::FightView::PlayerInfo(Player* player){
    cout << "HP[" << player->getHP() + "/" +player->getMaxHP() <<endl;
    
}

Item* View::FightView::ChooseItem(vector<Item*> Items){
    vector<string> options;
    for(Item* item: Items){
        options.push_back(item->getStat());
    }
    
    options.push_back("None");
    
    int option=0;
    int vecSize = options.size();
    while(true){
        clearScreen();
        for(int i=0 ; i < vecSize; i++){
            if(i == option){
                cout << green << options[i] << reset << endl;
            }else{
                cout << options[i] << endl;
            }
        }
        
        //showCharacters();
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option = (vecSize + option - 1)  % vecSize;
                continue;
            case 's':
                option++;
                option%=vecSize;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    if(option  == vecSize-1)
        return nullptr;
        
    return Items[option];
}

Relic* View::FightView::ChooseRelic(vector<Relic*> Relics){
    vector<string> options;
    for(Item* relic: Relics){
        options.push_back(relic->getStat());
    }
    
    options.push_back("None");
    
    int option=0;
    int vecSize = options.size();
    while(true){
        clearScreen();
        for(int i=0 ; i < vecSize; i++){
            if(i == option){
                cout << green << options[i] << reset << endl;
            }else{
                cout << options[i] << endl;
            }
        }
        //showCharacters();
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option = (vecSize + option - 1)  % vecSize;
                continue;
            case 's':
                option++;
                option%=vecSize;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    if(option  == vecSize-1)
        return nullptr;
        
    return Relics[option];
}


Consumable* View::FightView::ChooseConsumable(vector<pair<Consumable*,int>> Consumables){
    vector<vector<string>> Options;
    //                   0       1         2               
    Options.push_back({"Name","Type","Amount"});
    for(pair<Consumable*,int> x : Consumables){
        Consumable* consumable = x.first;
        int amount = x.second;
        
        vector<string> row(Options[0].size());
        row[0] = (consumable->getName() + "(x" + to_string(amount) + ")");
        row[1] = consumable->getType();
        row[2] = to_string(consumable->getAmount());
        Options.push_back(row);
    }
    Options.push_back({"Back"," "," "});
    
    int rows = Options.size();
    int width = 0;
    for(int i=0 ; i<rows ; i++){
        for(int j=0; j<Options[i].size() ; j++){
            int len = Options[i][j].length();
            if(len > width)
                width = len;
        }
    }
    
    int option = 1;
    int vecSize = Options[0].size();
    while(true){
        clearScreen();
        
        for(int i=0 ; i<Options.size(); i++){
            if(i == option){
                cout << green;
            }
            for(int j=0 ; j<vecSize ; j++){
                cout << left << setw(width) << Options[i][j] << " " ;
            }
            cout << reset << endl;
        }
        showCharacters();
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
            default:
                continue;
        }
        break;
    }
    
    if(option  == Options.size()-1)
        return nullptr;
    return Consumables[option-1].first;
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
                row.push_back("Armor: " + to_string(Enemy->getArmor()));
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
        //showCharacters();
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
                    row.push_back("Armor:" + to_string(Enemy->getArmor()));
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
        vector<int> Posoptions;
        for(int i = 0;i < vecSize + 2; i++){
            if(option[i] && !Chosen[i])
                Posoptions.push_back(i);
        }
        for(int i=0 ; i<4 ; i++){
            for(int j=0 ; j<vecSize + 2 ; j++){
                if(j == Posoptions[m % Posoptions.size()])
                    cout<< green;
                else if (!option[j])
                    cout<< grey;
                else if(Chosen[j])
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
    // showCharacters();
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
        default:
            continue;
        }
        break;
    }   
    return {};
}

Weapon* View::FightView::ChooseWeapon(vector<pair<Weapon*,int>> Weapons){
    vector<vector<string>> Options;
    //                   0       1         2                3               4              5             
    Options.push_back({"Name","Damage","Ammo/Amount","EnergyNeeded","MaxAttackAmount","MinDamagePercent"});
    for(pair<Weapon*,int> p:Weapons){
        Weapon* weapon = p.first;
        int Amount = p.second;
        
        vector<string> row(Options[0].size());
        row[0] = weapon->getName();
        row[1] = to_string(weapon->getDamage());
        row[3] = to_string(weapon->getEnergyNeeded());
        row[4] = " ";
        row[5] = " ";
        if(dynamic_cast<Gun*>(weapon) != nullptr){
            Gun* gun = dynamic_cast<Gun*>(weapon);
            row[2] = "[" + to_string(gun->getAmmo()) + "/" + to_string(gun->getMaxAmmo()) + "]";
            
            if(dynamic_cast<Rifle*>(gun) != nullptr){
                Rifle* rifle = dynamic_cast<Rifle*>(weapon);
                row[4] = to_string(rifle->getMaxAttackAmount());
            }else if(dynamic_cast<Shotgun*>(gun) != nullptr){
                Shotgun* shotgun = dynamic_cast<Shotgun*>(weapon);
                row[5] = to_string(shotgun->getMinDamagePercent())+ "%";
            }
            
        }else{
            row[2] = to_string(Amount);
        }
        Options.push_back(row);
    }
    Options.push_back({"Back"," "," "," "," "," "});
    
    int rows = Options.size();
    int width = 0;
    for(int i=0 ; i<rows ; i++){
        for(int j=0; j<Options[i].size() ; j++){
            int len = Options[i][j].length();
            if(len > width)
                width = len;
        }
    }
    
    int option = 1;
    int vecSize = Options[0].size();
    while(true){
        clearScreen();
        
        for(int i=0 ; i<Options.size(); i++){
            if(i == option){
                cout << green;
            }
            for(int j=0 ; j<vecSize ; j++){
                cout << left << setw(width) << Options[i][j] << " " ;
            }
            cout << reset << endl;
        }
        showCharacters();
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
            default:
                continue;
        }
        break;
    }
    
    if(option  == Options.size()-1)
        return nullptr;
    return Weapons[option-1].first;
}

int View::FightView::PlayerMenu(){
    // 1. weapons   2.consumables  3.endround
    int option = 0;
    vector<string> options = {"Weapons","Consumables","End Round"};
    
    int vecSize = options.size();
    while(true){
        clearScreen();
        for(int i=0 ; i < vecSize; i++){
            if(i == option){
                cout << green << options[i] << reset << endl;
            }else{
                cout << options[i] << endl;
            }
        }
        showCharacters();
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option = (vecSize + option - 1) % vecSize;
                continue;
            case 's':
                option++;
                option%=vecSize;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    return (option +1);
}

int View::FightView::ColdWeaponMenu(){
    // 1.attack  2.throw  3.back
    int option = 0;
    vector<string> options = {"Attack","Throw","Back"};
    
    int vecSize = options.size();
    while(true){
        clearScreen();
        for(int i=0 ; i < vecSize; i++){
            if(i == option%vecSize){
                cout << green << options[i] << reset << endl;
            }else{
                cout << options[i] << endl;
            }
        }
        showCharacters();
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option = (vecSize+option-1)%vecSize;
                continue;
            case 's':
                option++;
                option%vecSize;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    return (option +1);
}

int View::FightView::GunMenu(){
    // 1.attack  2.reload  3.back
    int option = 0;
    vector<string> options = {"Attack","Reload","Back"};
    
    int vecSize = options.size();
    while(true){
        clearScreen();
        for(int i=0 ; i < vecSize; i++){
            if(i == option%vecSize){
                cout << green << options[i] << reset << endl;
            }else{
                cout << options[i] << endl;
            }
        }
        showCharacters();
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option = (vecSize+option-1)%vecSize;
                continue;
            case 's':
                option++;
                option%=vecSize;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    return (option+1);
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
                row.push_back("Armor: " + to_string(character->getArmor()));
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
    
    int rows = Details.size();
    int width = 0;
    for(int i=0 ; i<rows ; i++){
        for(int j=0; j<Details[i].size() ; j++){
            int len = Details[i][j].length();
            if(len > width)
                width = len;
        }
    }
    
    int vecSize = Details[0].size();
    
    for(int i=0 ; i<rows ; i++){
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
    cout << entry << endl << "Press any key to continue\n";
    _getch();
}
void View::FightView::print(string entry){
    cout << entry << endl;
}


//---------------------------------------------------------------------------------------------
Model::FightModel::FightModel(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,vector<Relic*> Relics){
    this -> player = player;
    this -> Enemies = Enemies;
    this -> Items = Items;
    this -> droppedCoins = droppedCoins;
    this -> Relics = Relics;
    Round=0;
}

void Model::FightModel::setRound(int round){ Round = round ;}

int Model::FightModel::getRound(){ return Round; }

Player* Model::FightModel::getPlayer(){ return player;}


vector<Character*> Model::FightModel::getEnemies(){ return Enemies;}

int Model::FightModel::getCoins(){ return droppedCoins;}

vector<Item*> Model::FightModel::getItems(){return Items;}

void Model::FightModel::setItems(vector<Item*> Items){this->Items = Items;}

vector<Relic*> Model::FightModel::getRelics(){return Relics;}

void Model::FightModel::setEnemies(vector<Character*> Enemies){this -> Enemies = Enemies;}

//---------------------------------------------------------------------------------------------
Control::FightControl::FightControl(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,vector<Relic*> Relics) {
    model = new Model::FightModel(player, Enemies,Items,droppedCoins,Relics);
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
        }
        else if(round % 2 == 0){
            EnemiesTurn();
            if(model->getPlayer()->getHP() <= 0){
                delete model->getPlayer();
                break;
            }
        }
    }
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
        view->Prompt("");
    }
}

void Control::FightControl::PlayerTurn(){
    //1. weapons  2.consumables  3.end round
    while(!model->getEnemies().empty()){
        int choice = view->PlayerMenu();
        
        switch (choice)
        {
            case 1:
                while(!model->getEnemies().empty()){
                    Weapon* weapon = view->ChooseWeapon(model->getPlayer()->getWeapons());
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
                            int option = view->GunMenu();
                            
                            switch (option)
                            {
                                case 1:
                                    if(gun->getAmmo() ==0){
                                            clearScreen();
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
                        int option = view->ColdWeaponMenu();
                        ColdWeapon* coldWeapon = dynamic_cast<ColdWeapon*>(weapon);
                        while (!model->getEnemies().empty())
                        {
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
                    Consumable* consumable = view->ChooseConsumable(model->getPlayer()->getConsumables());
                    if(consumable == nullptr)
                        break;
                    if(consumable->getType() == "HPPotion"){
                        if (model->getPlayer()->getHP() >= model->getPlayer()->getMaxHP())
                        {
                            view->Prompt("You Already Have Full HP");
                        }
                        
                    }else if(consumable->getType() == "ShieldPotion"){
                        if (model->getPlayer()->getShield() >= 100)
                        {
                            view->Prompt("You Already Have Full Shield");
                        }
                        
                    }else if(consumable->getType() == "EnergyPotion"){
                        if (model->getPlayer()->getEnergy() >= model->getPlayer()->getMaxEnergy())
                        {
                            view->Prompt("You Already Have Full Energy");
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
    view->Prompt("");
}

View::FightView* Control::FightControl::getView(){return view;}

void Control::FightControl::EndFight(){
    if(model->getPlayer() != nullptr)
        model->getPlayer()->addCoin(model->getCoins());
        while (!model->getItems().empty())
        {
            Item* ChosenItem = view->ChooseItem(model->getItems());
            if(ChosenItem == nullptr){
                break;
            }
            
            if (ChosenItem->getCapacity() > (model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight())){
               view->Prompt("Not Enough BackPack Space");
               continue;
            }
            
            vector<Item*> Items = model->getItems();
            Items.erase(remove(Items.begin(),Items.end(),ChosenItem),Items.end());
            model->setItems(Items);
            model->getPlayer()->addItem(ChosenItem);
            //delete ChosenItem;
        }
        
        Relic* relic = view->ChooseRelic(model->getRelics());
        if(relic != nullptr)  
            model->getPlayer()->addRelic(relic);
        
        model->getPlayer()->setHP(model->getPlayer()->getMaxHP());
        model->getPlayer()->setEnergy(model->getPlayer()->getMaxEnergy());
        model->getPlayer()->setShield(0);
        for(pair<Weapon*,int> p:model->getPlayer()->getWeapons()){
            Weapon* weapon = p.first;
            if(dynamic_cast<Gun*>(weapon) != nullptr){
                Gun* gun = dynamic_cast<Gun*>(weapon);
                gun->Reload();
            }
        }
}
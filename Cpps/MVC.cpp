#include "../Headers/MVC.h"
#include "../Headers/creature.h"
#include "functions.cpp"
#include <vector>
#include <string>
#include <conio.h>
#include <iomanip>
#include <algorithm>

using namespace std;


Item* View::FightView::ChooseItem(vector<Item*> Items){
    vector<string> options;
    for(Item* item: Items){
        options.push_back(item->getStat());
    }
    
    options.push_back("Back");
    
    int option=0;
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
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option--;
                continue;
            case 's':
                option++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    if(option % vecSize == vecSize-1)
        return nullptr;
        
    return Items[option % vecSize];
}

Relic* ChooseRelic(vector<Relic*> Relics){
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
            if(i == option%vecSize){
                cout << green << options[i] << reset << endl;
            }else{
                cout << options[i] << endl;
            }
        }
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option--;
                continue;
            case 's':
                option++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    if(option % vecSize == vecSize-1)
        return nullptr;
        
    return Relics[option % vecSize];
}


Consumable* View::FightView::ChooseConsumable(vector<pair<Consumable*,int>> Consumables){
    vector<string> options;
    for(pair<Consumable*,int> x:Consumables){
        if(x.second > 1){
            options.push_back(x.first->getShortStat() + " x" + to_string(x.second) +"\n");
        }else{
            options.push_back(x.first->getShortStat() + "\n");
        }
    }
    options.push_back("Back");
    
    int option=0;
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
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option--;
                continue;
            case 's':
                option++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    if(option % vecSize == vecSize-1)
        return nullptr;
        
    return Consumables[option % vecSize].first;
}

Character* View::FightView::ChooseEnemy(vector<Character*> Enemies){
    int vecSize = Enemies.size();
    vector<vector<string>> options(4, vector<string>(vecSize+1));
    for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<vecSize +1 ; j++){
            if(i == 0){
                if(j == vecSize)
                    options[i][j] = "Back";
                else
                    options[i][j] = Enemies[j]->getName();
            }
            else if(i == 1){
                if(j == vecSize)
                    options[i][j] = " ";
                else
                    options[i][j] = "HP:[" + to_string(Enemies[j]->getHP()) + "/" + to_string(Enemies[j]->getMaxHP()) + "]";
            }
            else if(i == 2){
                if(j == vecSize)
                    options[i][j] = " ";
                else
                    options[i][j] = "Armor:" + Enemies[j]->getArmor();
            }
            else if(i == 3){
                if(j == vecSize)
                    options[i][j] = " ";
                else
                    options[i][j] = "Shield:" + Enemies[j]->getShield();
            }
        }
    }
    // this will be function
    int rows = options.size();
    int width = 0;
    for(int i=0 ; i<rows ; i++){
        for(int j=0; j<options[i].size() ; j++){
            int len = options[i][j].length();
            if(len > width)
                width = len;
        }
    }
    int m = 0;
    while(true){
        clearScreen();
        for(int i=0 ; i<4 ; i++){
            for(int j=0 ; j<vecSize+1 ; j++){
                if(j == m % options[i].size()){
                    cout<< green ;
                    if( j > 0){
                        cout << left << setw(width) << options[i][j] << " " ;
                    }else{
                        cout<< left << setw(4) << options[i][j];
                    }
                    cout<< reset << endl;
                }else{
                    if( j > 0){
                        cout << left << setw(width) << options[i][j] << " " ;
                    }else{
                        cout<< left << setw(4) << options[i][j];
                    }
                    cout<< reset << endl;                    
                }
            }
        }
        char key = _getch();
        switch(tolower(key))
        {
            case 'a':
                m--;
                continue;
            case 'd':
                m++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    if(m % (vecSize + 1) == vecSize)
        return nullptr;
    return Enemies[m % (vecSize + 1)];    
}

vector<Character*> View::FightView::ChooseEnemies(vector<Character*> Enemies , int amount){
    bool breaker = true;
    int vecSize = Enemies.size();
    vector<vector<string>> options(4, vector<string>(vecSize+2));
    for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<vecSize +2 ; j++){
            if(i == 0){
                if(j == vecSize)
                    options[i][j] = "Reset";
                else if(j == vecSize + 1)
                    options[i][j] = "Done";
                else
                    options[i][j] = Enemies[j]->getName();
            }
            else if(i == 1){
                if(j == vecSize || j == vecSize + 1)
                    options[i][j] = " ";
                else
                    options[i][j] = "HP:[" + to_string(Enemies[j]->getHP()) + "/" + to_string(Enemies[j]->getMaxHP()) + "]";
            }
            else if(i == 2){
                if(j == vecSize || j == vecSize + 1)
                    options[i][j] = " ";
                else
                    options[i][j] = "Armor:" + Enemies[j]->getArmor();
            }
            else if(i == 3){
                if(j == vecSize || j == vecSize + 1)
                    options[i][j] = " ";
                else
                    options[i][j] = "Shield:" + Enemies[j]->getShield();
            }
        }
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
    vector<int> option;
    option.push_back(1);
    for(int i = 0; i < Enemies.size() + 1 ; i++)
        option.push_back(0);
    
    while(true){
        clearScreen();
        for(int i=0 ; i<4 ; i++){
            for(int j=0 ; j<vecSize + 2 ; j++){
                if(option[j] == 1)
                    cout<< green;
                else if(option[j] == 2)
                    cout<< yellow;
                else if(option[j] == 4)
                    cout<< grey;
                if( j > 0){
                    cout << left << setw(width) << options[i][j] << " " ;
                }else{
                    cout<< left << setw(4) << options[i][j];
                }
                cout<< reset << endl;                  
                }
            }
    int m = 0;
    char key = _getch();
    switch(tolower(key))
    {
        case 'a':
                option[m % (vecSize + 2)] = 0;
                m = find(option.rbegin() + option.size() - (m % (vecSize + 2)), option.rend(), 0) - option.rbegin();
                if(m == option.size()) {
                    m = vecSize + 1;
                    option[m] = 1;
                }else{
                    m = option.size() - (m + 1);
                    option[m] = 1;
                }
            continue;
        case 'd':
                option[m % (vecSize + 2)] = 0;
                m = find(option.begin() + (m % (vecSize + 2)) + 1 , option.end(), 0) - option.begin();
                option[m] = 1;
            continue;
        case '\r':
            if(m % (vecSize + 2) == vecSize ){  // if it was reset
                for(int i=0 ; i< vecSize + 2; i++)
                    option[i] = 0;
                option[m % (vecSize + 2)] = 1;
            }else if(m % (vecSize + 2) == vecSize + 1){ // if it was done
                vector<Character*> selected;
                for(int i=0; i < option.size() ; i++){
                    if(option[i] == 2)
                        selected.push_back(Enemies[i]);
                }
                return selected;
            }else{
                if(count(option.begin(), option.end(), 2) < amount - 1){
                    option[m % (vecSize + 2)] = 2;
                    m = find(option.begin() + (m % (vecSize + 2)) + 1 , option.end(), 0) - option.begin();
                    option[m] = 1;
                }
                else{
                    option[m % (vecSize + 2)] = 2;
                    for(int i = 0 ; i < vecSize ; i++){
                        if(option[i] != 2)
                            option[i] = 4;
                    }
                m = find(option.begin(), option.end(), 0) - option.begin();
                option[m] = 1;
                }
            }
        default:
            continue;
        }
        break;
    }   
    return {};
}

Weapon* View::FightView::ChooseWeapon(vector<pair<Weapon*,int>> Weapons){
    vector<string> options;
    for(pair<Weapon*,int> x : Weapons){
        if(x.second > 1){
            options.push_back(x.first->getShortStat() + " x" + to_string(x.second) +"\n");
        }else{
            options.push_back(x.first->getShortStat() + "\n");
        }
    }
    options.push_back("Back");
    
    int option=0;
    int vecSize = options.size();
    while(true){
        clearScreen();
        for(int i=0 ; i < vecSize; i++){
            if(i == option%vecSize){
                cout << green << options[i] << reset;
            }else{
                cout << options[i];
            }
        }
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option--;
                continue;
            case 's':
                option++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    if(option % vecSize == vecSize-1)
        return nullptr;
        
    return Weapons[option % vecSize].first;
}

int View::FightView::PlayerMenu(){
    // 1. weapons   2.consumables  3.show enemies  4.endround
    int option = 0;
    vector<string> options = {"Weapons","Consumables","show enemies","End Round"};
    
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
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option--;
                continue;
            case 's':
                option++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    return (option % vecSize +1);
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
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option--;
                continue;
            case 's':
                option++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    return (option % vecSize +1);
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
        char key = _getch();
        switch(tolower(key))
        {
            case 'w':
                option--;
                continue;
            case 's':
                option++;
                continue;
            case '\r':
                break;
            default:
                continue;
        }
        break;
    }
    
    return (option % vecSize +1);
}

void View::FightView::ShowEnemies(vector<Character*> Enemies){
    int vecSize = Enemies.size();
    vector<vector<string>> options(4, vector<string>(vecSize));
    for(int i=0 ; i<4 ; i++){
        for(int j=0 ; j<vecSize ; j++){
            if(i == 0){
                options[i][j] = Enemies[j]->getName();
            }
            else if(i == 1){
                options[i][j] = "HP:[" + to_string(Enemies[j]->getHP()) + "/" + to_string(Enemies[j]->getMaxHP()) + "]";
            }
            else if(i == 2){
                options[i][j] = "Armor:" + Enemies[j]->getArmor();
            }
            else if(i == 3){
                options[i][j] = "Shield:" + Enemies[j]->getShield();
            }
        }
    }
    int rows = options.size();
    int width = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < options[i].size(); j++) {
            int len = options[i][j].length();
            if (len > width) {
                width = len;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < options[i].size(); j++) {
            if(j > 0){
                cout << left << setw(width) << options[i][j] << " ";
            }else{
                cout << left << setw(4) << options[i][j];
            }

        }
        cout << endl;
    }
    Prompt("");
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

vector<Relic*> Model::FightModel::getRelics(){return Relics;}

//---------------------------------------------------------------------------------------------
Control::FightControl::FightControl(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,vector<Relic*> Relics) {
    model = new Model::FightModel(player, Enemies,Items,droppedCoins,Relics);
    view = new View::FightView();
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
    // a while loop that increaes model's round in each iteration and calls playerturn() or enemiesturn() functions accordingly
}

void Control::FightControl::RemoveEnemies(){
    bool hascleared = false;
    vector<Character*> Enemies = model->getEnemies();
    for(int i = 0 ; i < Enemies.size() ; i++){
        Character* Enemy = Enemies[i];
        if(Enemy->getHP() <=0){
            view->Prompt("low enemy hp");
            if(!hascleared){
                clearScreen();
                hascleared = true;
            }
            Enemies.erase(Enemies.begin() + i);
            view->print(Enemy->getName() + ":" +Enemy->DeathDialogue());
            //~Enemy();
        }
    }
    if(hascleared){
        view->Prompt("");
    }
}

void Control::FightControl::PlayerTurn(){
    //1. weapons  2.consumables  3.show enemies  4.end round
    while(true){
        int choice = view->PlayerMenu();
        switch (choice)
        {
            case 1:
                while(true){
                    Weapon* weapon = view->ChooseWeapon(model->getPlayer()->getWeapons());
                    if(weapon == nullptr)
                        break;
    
                    if(weapon->getEnergyNeeded() > model->getPlayer()->getEnergy())
                        view->Prompt("Not Enough Energy");
                        continue;
                        
                    if(dynamic_cast<Gun *>(weapon) != nullptr){
                        Gun* gun = dynamic_cast<Gun*>(weapon);
                        
                        while (true)
                        {
                            // 1.attack   2.reload  3.back
                            int option = view->GunMenu();
                            switch (option)
                            {
                                case 1:
                                    if(gun->getAmmo() ==0)
                                            view->Prompt("Not Enough Ammo");
                                            continue;
                                    
                                    if(dynamic_cast<Rifle *>(gun) != nullptr){
                                        Rifle* rifle = dynamic_cast<Rifle*>(gun);
                                        vector<Character*> chosenEnemies = view->ChooseEnemies(model->getEnemies(),min(rifle->getMaxAttackAmount(),rifle->getAmmo()));
                                        rifle->Attack(chosenEnemies);
                                        
                                    }else if(dynamic_cast<SMG *>(gun) != nullptr){
                                        SMG* smg = dynamic_cast<SMG*>(gun);
                                        vector<Character*> ShuffledEnemies = ShuffleVec(model->getEnemies());
                                        vector<Character*> ChosenEnemies;
                                        for(int i=0; i < min(int(ShuffledEnemies.size()-1),smg->getAmmo());i++){
                                            ChosenEnemies.push_back(ShuffledEnemies[i]);
                                        }
                                        smg->Attack(ChosenEnemies);
                                        
                                    }else if(dynamic_cast<Shotgun *>(gun) != nullptr){
                                        Shotgun* shotGun = dynamic_cast<Shotgun*>(gun);
                                        shotGun->Attack(model->getEnemies(),view->ChooseEnemy(model->getEnemies()));
                                        
                                    }else if(dynamic_cast<Snipe *>(gun) != nullptr){
                                        Snipe* snipe = dynamic_cast<Snipe*>(gun);
                                        snipe->Attack(model->getEnemies(),view->ChooseEnemy(model->getEnemies()));
                                        
                                    }
                                    else{    
                                        Character* enemy = view->ChooseEnemy(model->getEnemies());
                                        gun->Attack(enemy);
                                        
                                    }
                                    model->getPlayer()->setEnergy(model->getPlayer()->getEnergy() - weapon->getEnergyNeeded());
                                    RemoveEnemies();
                                
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
                        }
                        
                            
                    }else if(dynamic_cast<Throwable *>(weapon) != nullptr){
                        Throwable* throwable = dynamic_cast<Throwable*>(weapon);
                        throwable->Attack(model->getEnemies());
                        model->getPlayer()->removeItem(throwable);
                        
                    }else if(dynamic_cast<ColdWeapon *>(weapon) != nullptr){
                        int option = view->ColdWeaponMenu();
                        ColdWeapon* coldWeapon = dynamic_cast<ColdWeapon*>(weapon);
                        while (true)
                        {
                            switch (option)
                            {
                                case 1:
                                    coldWeapon->Attack(view->ChooseEnemy(model->getEnemies()));
                                    break;
                                case 2:
                                    coldWeapon->Throw(view->ChooseEnemy(model->getEnemies()));
                                    model->getPlayer()->removeItem(coldWeapon);
                                    break;
                                case 3:
                                    break;
                                default:
                                    continue;
                            }
                            break;    
                        }  
                    }else{
                        weapon->Attack(view->ChooseEnemy(model->getEnemies()));
                    }
                    model->getPlayer()->setEnergy(model->getPlayer()->getEnergy()-weapon->getEnergyNeeded());
                }
                continue;
            case 2:
                while (true)
                {
                    Consumable* consumable = view->ChooseConsumable(model->getPlayer()->getConsumables());
                    if(consumable == nullptr)
                        break;
                    model->getPlayer()->Consume(consumable);
                }
                continue;
                
            case 3:
                view->ShowEnemies(model->getEnemies());
                continue;
            case 4:
                break;
            default:
                continue;
        }
        break;
    }
}

void Control::FightControl::EnemiesTurn(){
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
        while ((true))
        {
            Item* ChosenItem = view->ChooseItem(model->getItems());
            if(ChosenItem == nullptr){
                break;
            }else{
                if (ChosenItem->getCapacity() < (model->getPlayer()->getBackPackCapacity() - model->getPlayer()->getBackPackWeight()))
                {
                   view->Prompt("Not Enough BackPack Space");
                   continue;
                }else{
                    break;
                }
                
            }
            
        }
        
        Relic* relic = ChooseRelic(model->getRelics());
        if(relic != nullptr)  
            model->getPlayer()->addRelic(relic);
        
        
        
        
}
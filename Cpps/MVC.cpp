#include "../Headers/MVC.h"
#include "../Headers/creature.h"
#include "functions.cpp"
#include <vector>
#include <string>
#include <conio.h>
#include <iomanip>
#include <algorithm>

using namespace std;

const string reset("\033[0m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string grey("\033[90m");

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
            if(option[(m - 1) % (vecSize + 2)] == 0)
            {
                option[m % (vecSize + 2)] = 0;
                m--;
                option[m % (vecSize + 2)] = 1; 
            }else{
                option[m % (vecSize + 2)] = 0;
                m = find(option.rbegin() + option.size() - (m % (vecSize + 2)), option.rend(), 0) - option.rbegin();
                if(m == option.size())  // there is not any zero
                    m = vecSize + 1;
                    option[m] = 1;
            }
            continue;
        case 'd':
            if(option[(m + 1) % (vecSize + 2)] == 0)
            {
                option[m % (vecSize + 2)] = 0;
                m++;
                option[m % (vecSize + 2)] = 1; 
            }else{
                option[m % (vecSize + 2)] = 0;
                m = find(option.begin() + (m % (vecSize + 2)) , option.end(), 0) - option.begin();
                option[m] = 1;
            }
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
                    option[(m + 1) % (vecSize + 2)] = 1;
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
    // 1. weapons  2.consumables 3.endround
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        if( m % 3 == 0)
            sizecounter += green;
        sizecounter += "1. Weapons\n";
        sizecounter += reset;

        if( m % 3 == 1)
            sizecounter += green;
        sizecounter += "2. Consumables\n";
        sizecounter += reset;

        if( m % 3 == 2)
            sizecounter += green;
        sizecounter += "3. end round\n";
        sizecounter += reset;

        cout << sizecounter;
        char key = _getch();
        switch(key)
        {
            case 'w':
                m--;
                break;
                case 's':
                m++;
                break;
            case '\r':
                breaker=false;
                break;
            default:
                break;
        }
    }
    return (m % 3 + 1);
}

int View::FightView::ColdWeaponMenu(){
    // 1.attack  2.throw  3.back
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        if( m % 3 == 0)
            sizecounter += green;
        sizecounter += "1. Attack\n";
        sizecounter += reset;

        if( m % 3 == 1)
            sizecounter += green;
        sizecounter += "2. Throw\n";
        sizecounter += reset;

        if( m % 3 == 2)
            sizecounter += green;
        sizecounter += "3. Back\n";
        sizecounter += reset;

        cout << sizecounter;
        char key = _getch();
        switch(key)
        {
            case 'w':
                m--;
                break;
                case 's':
                m++;
                break;
            case '\r':
                breaker=false;
                break;
            default:
                break;
        }
    }
    return (m % 3 + 1);
}

int View::FightView::GunMenu(){
    // 1.attack  2.reload  3.back
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        if( m % 3 == 0)
            sizecounter += green;
        sizecounter += "1. Attack\n";
        sizecounter += reset;

        if( m % 3 == 1)
            sizecounter += green;
        sizecounter += "2. Reload\n";
        sizecounter += reset;

        if( m % 3 == 2)
            sizecounter += green;
        sizecounter += "3. Back\n";
        sizecounter += reset;

        cout << sizecounter;
        char key = _getch();
        switch(key)
        {
            case 'w':
                m--;
                break;
                case 's':
                m++;
                break;
            case '\r':
                breaker=false;
                break;
            default:
                break;
        }
    }
    return (m % 3 + 1);
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
                options[i][j] = "HP:" + Enemies[j]->getHP();
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
    cout << "Press any key to continue\n";
    char key = _getch();
}

void View::FightView::Prompt(string entry){
    cout << entry << endl << "Press any key to continue\n";
    _getch();
}
void View::FightView::print(string entry){
    cout << entry << endl;
}



//---------------------------------------------------------------------------------------------
Model::FightModel::FightModel(Player* player,vector<Character*> Enemies){
    this -> player = player;
    this -> Enemies = Enemies;
    Round=0;
}

void Model::FightModel::setRound(int round){ Round = round ;}

int Model::FightModel::getRound(){ return Round; }

Player* Model::FightModel::getPlayer(){ return player;}

vector<Character*> Model::FightModel::getEnemies(){ return Enemies;}


//---------------------------------------------------------------------------------------------
Control::FightControl::FightControl(Player* player,vector<Character*> Enemies) {
    model = new Model::FightModel(player, Enemies);
    view = new View::FightView();
}


void Control::FightControl::StartFight(){
    while(true){
        int round = model->getRound();
        if(round % 2 != 0){
            if(model->getEnemies().empty())
                break;
            else
                PlayerTurn();
        }
        else if(round % 2 == 0){ // enemy turn
            if(model->getPlayer()->getHP() <= 0)
                break;
            else
                EnemiesTurn();
        }
        model->setRound(round + 1);
    }
    // a while loop that increaes model's round in each iteration and calls playerturn() or enemiesturn() functions accordingly
}

void Control::FightControl::RemoveEnemies(){
    bool hascleared = false;
    vector<Character*> Enemies = model->getEnemies();
    for(int i = 0 ; i < Enemies.size() ; i++){
        Character* Enemy = Enemies[i];
        if(Enemy->getHP() <=0){
            if(!hascleared){
                clearScreen();
                hascleared = true;
            }
            Enemies.erase(Enemies.begin() + i);
            view->print(Enemy->getName() + Enemy->DeathDialogue());
            //~Enemy();
        }
    }
    if(hascleared){
        view->Prompt("\npress any key to proceed...");
    }
}

void Control::FightControl::PlayerTurn(){
    //1. weapons  2.consumables 3.endround
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
                        
                    if(typeid(weapon) == typeid(Gun)){
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
                                    
                                    if(typeid(gun) == typeid(Rifle)){
                                        Rifle* rifle = dynamic_cast<Rifle*>(gun);
                                        vector<Character*> chosenEnemies = view->ChooseEnemies(model->getEnemies(),min(rifle->getMaxAttackAmount(),rifle->getAmmo()));
                                        rifle->Attack(chosenEnemies);
                                        
                                    }else if(typeid(gun) == typeid(SMG)){
                                        SMG* smg = dynamic_cast<SMG*>(gun);
                                        vector<Character*> ShuffledEnemies = ShuffleVec(model->getEnemies());
                                        vector<Character*> ChosenEnemies;
                                        for(int i=0; i < min(int(ShuffledEnemies.size()-1),smg->getAmmo());i++){
                                            ChosenEnemies.push_back(ShuffledEnemies[i]);
                                        }
                                        smg->Attack(ChosenEnemies);
                                        
                                    }else if(typeid(gun) == typeid(Shotgun)){
                                        Shotgun* shotGun = dynamic_cast<Shotgun*>(gun);
                                        shotGun->Attack(model->getEnemies(),view->ChooseEnemy(model->getEnemies()));
                                        
                                    }else if(typeid(gun) == typeid(Snipe)){
                                        Snipe* snipe = dynamic_cast<Snipe*>(gun);
                                        snipe->Attack(model->getEnemies(),view->ChooseEnemy(model->getEnemies()));
                                        
                                    }
                                    else{    
                                        Character* enemy = view->ChooseEnemy(model->getEnemies());
                                        gun->Attack(enemy);
                                        
                                    }
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
                        
                            
                    }else if(typeid(weapon) == typeid(Throwable)){
                        Throwable* throwable = dynamic_cast<Throwable*>(weapon);
                        throwable->Attack(model->getEnemies());
                        model->getPlayer()->removeItem(throwable);
                        
                    }else if(typeid(weapon) == typeid(ColdWeapon)){
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
                
            case 3:
                break;
            default:
                continue;
        }
        break;
    }
}

void Control::FightControl::EnemiesTurn(){
    for(Character* Enemy: model->getEnemies()){
        if(typeid(Enemy) == typeid(HumanEnemy)){
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
    view->Prompt("press any key to proceed...");
}

View::FightView* Control::FightControl::getView(){return view;}
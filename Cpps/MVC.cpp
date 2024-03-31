#include "../Headers/MVC.h"
#include "functions.cpp"
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

const string reset("\033[0m");
const string green("\033[1;32m");

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
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        sizecounter += "";
        for(int i=0 ; i < Enemies.size() + 1; i++){
            if(i < Enemies.size() )
            {
                if(i == m % (Enemies.size() + 1))
                    sizecounter += green;
                sizecounter += to_string(i+1) + ". " + Enemies[i]->getStat() + "\n";
                sizecounter += reset;
            }else{
                if(i == m % (Enemies.size() + 1))
                    sizecounter += green;
                sizecounter += "Back";
                sizecounter += reset;
            }
        }
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
    if((m % Enemies.size() + 1) == Enemies.size())
        return nullptr;
    return Enemies[m % Enemies.size()];
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

int View::FightView::GunMenu(){
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        if( m % 3 == 0)
            sizecounter += green;
        sizecounter += "1. attack\n";
        sizecounter += reset;

        if( m % 3 == 1)
            sizecounter += green;
        sizecounter += "2. reload\n";
        sizecounter += reset;

        if( m % 3 == 2)
            sizecounter += green;
        sizecounter += "3. back\n";
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

void View::FightView::Prompt(string entry){
    cout << entry << endl << "Press any key to continue\n";
    _getch();
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
    //construct a model and a view and set control's model and view to the constructed ones
}


void Control::FightControl::StartFight(){
    // a while loop that increaes model's round in each iteration and calls playerturn() or enemiesturn() functions accordingly
}

void Control::FightControl::PlayerTurn(){
    //1. weapons  2.consumables 3.endround
    while(true){
        int choice = view.PlayerMenu();
        switch (choice)
        {
            case 1:
                while(true){
                    Weapon* weapon = view.ChooseWeapon(model.getPlayer()->getWeapons());
                    if(weapon == nullptr)
                        break;
                    
                    if(weapon->getEnergyNeeded() > model.getPlayer()->getEnergy())
                        view.Prompt("Not Enough Energy");
                        continue;
                        
                    if(typeid(weapon) == typeid(Gun)){
                        Gun* gun = dynamic_cast<Gun*>(weapon);
                        
                        if(gun->getAmmo() ==0)
                                view.Prompt("Not Enough Ammo");
                                continue;
                        
                        if(typeid(gun) == typeid(Rifle)){
                            Rifle* rifle = dynamic_cast<Rifle*>(gun);
                            vector<Character*> chosenEnemies = view.ChooseEnemies(model.getEnemies(),min(rifle->getMaxAttackAmount(),rifle->getAmmo()));
                            rifle->Attack(chosenEnemies);
                            
                        }else if(typeid(gun) == typeid(SMG)){
                            SMG* smg = dynamic_cast<SMG*>(gun);
                            vector<Character*> ShuffledEnemies = ShuffleVec(model.getEnemies());
                            vector<Character*> ChosenEnemies;
                            for(int i=0; i < min(int(ShuffledEnemies.size()-1),smg->getAmmo());i++){
                                ChosenEnemies.push_back(ShuffledEnemies[i]);
                            }
                            smg->Attack(ChosenEnemies);
                            
                        }else if(typeid(gun) == typeid(Shotgun)){
                            Shotgun* shotGun = dynamic_cast<Shotgun*>(gun);
                            shotGun->Attack(model.getEnemies(),view.ChooseEnemy(model.getEnemies()));
                            
                        }else if(typeid(gun) == typeid(Snipe)){
                            Snipe* snipe = dynamic_cast<Snipe*>(gun);
                            snipe->Attack(model.getEnemies(),view.ChooseEnemy(model.getEnemies()));
                            
                        }
                        else{    
                            Character* enemy = view.ChooseEnemy(model.getEnemies());
                            gun->Attack(enemy);
                            
                        }
                    }else if(typeid(weapon) == typeid(Throwable)){
                        Throwable* throwable = dynamic_cast<Throwable*>(weapon);
                        throwable->Attack(model.getEnemies());
                        model.getPlayer()->removeItem(throwable);
                        
                    }else if(typeid(weapon) == typeid(ColdWeapon)){
                        int option = view.ColdWeaponMenu();
                        ColdWeapon* coldWeapon = dynamic_cast<ColdWeapon*>(weapon);
                        while (true)
                        {
                            switch (option)
                            {
                                case 1:
                                    coldWeapon->Attack(view.ChooseEnemy(model.getEnemies()));
                                    break;
                                case 2:
                                    coldWeapon->Throw(view.ChooseEnemy(model.getEnemies()));
                                    model.getPlayer()->removeItem(coldWeapon);
                                    break;
                                case 3:
                                    break;
                                default:
                                    continue;
                            }
                            break;    
                        }  
                    }else{
                        weapon->Attack(view.ChooseEnemy(model.getEnemies()));
                    }
                    model.getPlayer()->setEnergy(model.getPlayer()->getEnergy()-weapon->getEnergyNeeded());
                }
                continue;
            case 2:
                while (true)
                {
                    Consumable* consumable = view.ChooseConsumable(model.getPlayer()->getConsumables());
                    if(consumable == nullptr)
                        break;
                    model.getPlayer()->Consume(consumable);
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
    //iterats through the lists of enemeies and calls their attack function or state machine
}

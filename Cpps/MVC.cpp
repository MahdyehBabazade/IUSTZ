#include "../Headers/MVC.h"
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

const string reset("\033[0m");
const string green("\033[1;32m");

void clearScreen(){
    system("cls");
}

Consumable* View::FightView::ChooseConsumable(vector<pair<Consumable*,int>> Consumables){
    vector<string> options;
    for(pair<Consumable*,int> x:Consumables){
        if(x.second > 1){
            options.push_back(x.first->getShortStat() + " " + to_string(x.second) +"x");
        }else{
            options.push_back(x.first->getShortStat());
        }
    }
    options.push_back("back");
    
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
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        sizecounter += "";
        for(int i=0 ; i < Weapons.size() + 1; i++){
            if(i < Weapons.size() )
            {
                if(i == m % (Weapons.size() + 1))
                    sizecounter += green;
                sizecounter += to_string(i+1) + ". " + Weapons[i].first->getShortStat() + "\n";
                sizecounter += reset;
            }else{
                if(i == m % (Weapons.size() + 1))
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
    if((m % Weapons.size() + 1) == Weapons.size())
        return nullptr;
    return Weapons[m % Weapons.size()].first;
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

//---------------------------------------------------------------------------------------------
Control::FightControl::FightControl(Player* player,vector<Character*> Enemies){
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
                Weapon* weapon = view.ChooseWeapon(model.getPlayer()->getWeapons());
                if(weapon == nullptr)
                    continue;
                
                if(weapon->getEnergyNeeded() > weapon->getEnergyNeeded())
                    view.Prompt("Not Enough Energy");
                    continue;
                    
                if(typeid(weapon) == typeid(Gun)){
                    Gun* gun = dynamic_cast<Gun*>(weapon);
                    if(typeid(gun) == typeid(Rifle)){
                        // choose some enemies
                    }else if(typeid(gun) == typeid(SMG)){
                        // attack some enemies
                    }else{
                        
                    }
                }else if(typeid(weapon) == typeid(Throwable)){
                    
                }else{
                    
                }
                
            case 2:
            
            default:
                continue;;
        }
    }
}

void Control::FightControl::EnemiesTurn(){
    //iterats through the lists of enemeies and calls their attack function or state machine
}

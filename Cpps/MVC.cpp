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

Consumable* View::FightView::ChooseConsumable(vector<Consumable*> Consumables){
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        sizecounter += "";
        for(int i=0 ; i < Consumables.size() + 1; i++){
            if(i < Consumables.size() )
            {
                if(i == m % (Consumables.size() + 1))
                    sizecounter += green;
                sizecounter += to_string(i+1) + ". " + Consumables[i]->getShortStat() + "\n";
                sizecounter += reset;
            }else{
                if(i == m % (Consumables.size() + 1))
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
    if((m % Consumables.size() + 1) == Consumables.size())
        return nullptr;
    return Consumables[m % Consumables.size()];
    // lists enemies and the player can then navigate and choose an enemy (returns null if nothing is chosen)
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
    // lists enemies and the player can then navigate and choose an enemy (returns null if nothing is chosen)
}
Weapon* View::FightView::ChooseWeapon(vector<Weapon*> Weapons){
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
                sizecounter += to_string(i+1) + ". " + Weapons[i]->getShortStat() + "\n";
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
    return Weapons[m % Weapons.size()];
    // lists weapons and the player can then navigate and choose a weapon (returns null if nothing is chosen)
}

int View::FightView::PlayerMenu(){
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        sizecounter += "Choose one of these options:\n";
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
    // navigate through the menu below and return the option
    //1. Weapons
    //2. Consumables
    //3. end round
}

int View::FightView::GunMenu(){
    string sizecounter;
    bool breaker=true;
    int m=0;
    while(breaker){
        clearScreen();
        sizecounter += "Choose one of these options:\n";
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
    // navigate through the menu below and return the option
    //1. attack
    //2. reload(for Guns)
    //3. back
}

void View::FightView::Prompt(string entry){
    cout << entry <<endl << "Press any key to continue\n";
    char key = _getch();
    //print the entry and waits for an input to go back (like when the player wants to attack but doesnt have energy)
}



//---------------------------------------------------------------------------------------------
Model::FightModel::FightModel(Player* player,vector<Character*> Enemies){

    //set the player and enemies to the entry
}



//---------------------------------------------------------------------------------------------
Control::FightControl::FightControl(Player* player,vector<Character*> Enemies){
    //construct a model and a view and set control's model and view to the constructed ones
}


void Control::FightControl::StartFight(){
    // a while loop that increaes model's round in each iteration and calls playerturn() or enemiesturn() functions accordingly
}

void Control::FightControl::PlayerTurn(){
    //a while loop that shows different menus and alows the player to choose different options
}

void Control::FightControl::EnemiesTurn(){
    //iterats through the lists of enemeies and calls their attack function or state machine
}

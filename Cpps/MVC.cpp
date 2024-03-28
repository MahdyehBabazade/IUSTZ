#include "../Headers/MVC.h"


Consumable* View::FightView::ChooseConsumable(vector<Weapon*> Consumables){
    // lists enemies and the player can then navigate and choose an enemy (returns null if nothing is chosen)
}

Character* View::FightView::ChooseEnemy(vector<Character*> Enemies){
    // lists enemies and the player can then navigate and choose an enemy (returns null if nothing is chosen)
}
Weapon* View::FightView::ChooseWeapon(vector<Weapon*> Weapons){
    // lists weapons and the player can then navigate and choose a weapon (returns null if nothing is chosen)
}

int View::FightView::PlayerMenu(){
    // navigate through the menu below and return the option
    //1. Weapons
    //2. Consumables
    //3. end round
}
int View::FightView::GunMenu(){
    // navigate through the menu below and return the option
    //1. attack
    //2. reload(for Guns)
    //3. back
}

void View::FightView::Prompt(string entry){
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


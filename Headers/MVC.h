#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"
#include <iostream>
using namespace std;

namespace View{
    class FightView{
        public:
            FightView() = default;
            int PlayerMenu(); //player options
            int GunMenu(); //weapon options(reload and attack)
            Consumable* ChooseConsumable(vector<Consumable*> Consumables);
            Weapon* ChooseWeapon(vector<Weapon*> Weapons);
            Character* ChooseEnemy(vector<Character*> Enemies);
            
            void Prompt(string entry);
    };
}

//--------------------
namespace Model{
    class FightModel{
        private:
            vector<Character*> Enemies;
            Player* player;
            int Round;
        public:
            FightModel() = default;
            FightModel(Player* player,vector<Character*> Enemies); //sets the player and the enemies and also the round to zero
            
    };
}

//-------------------------
namespace Control{
    class FightControl{
        private:
            Model::FightModel Model;
            View::FightView view;
            void StartFight();
            void PlayerTurn();
            void EnemiesTurn();
        public:
            FightControl(Player* player,vector<Character*> Enemies); //constructs the Model and the View and also calls startFight func
    };
}
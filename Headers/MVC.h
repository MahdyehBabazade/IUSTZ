#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"
#include <iostream>
using namespace std;
class Character;
class Player;
class HumanEnemy;
class Zombie;
class ShopKeeper;
class Medic;
namespace View{
    class FightView{
        public:
            FightView() = default;
            int PlayerMenu(); //player options
            int GunMenu(); //weapon options(reload and attack)
            int ColdWeaponMenu();
            vector<Character*> ChooseEnemies(vector<Character*> Enemies,int amount);
            Consumable* ChooseConsumable(vector<pair<Consumable*,int>> Consumables);
            Weapon* ChooseWeapon(vector<pair<Weapon*,int>> Weapons);
            Character* ChooseEnemy(vector<Character*> Enemies);

            void ShowEnemies(vector<Character*> Enemies);
            void Prompt(string entry);
            void print(string entry);
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
            void setRound(int round);
            int getRound();
            FightModel() = default;
            FightModel(Player* player,vector<Character*> Enemies); //sets the player and the enemies and also the round to zero
            
            Player* getPlayer();
            vector<Character*> getEnemies();
    };
}

//-------------------------
namespace Control{
    class FightControl{
        private:
            Model::FightModel* model;
            View::FightView* view;
            void PlayerTurn();
            void EnemiesTurn();
            void RemoveEnemies();
        public:
            FightControl(Player* player,vector<Character*> Enemies); //constructs the Model and the View and also calls startFight func
            View::FightView* getView();
            void StartFight();
    };
}
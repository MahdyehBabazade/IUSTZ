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
        private:
            Model::FightModel* fightmodel;
        public:
            FightView(Model::FightModel* fightmodel);
            int PlayerMenu(); //player options
            int GunMenu(); //weapon options(reload and attack)
            int ColdWeaponMenu();
            vector<Character*> ChooseEnemies(vector<Character*> Enemies,int amount);
            Consumable* ChooseConsumable(vector<pair<Consumable*,int>> Consumables);
            Weapon* ChooseWeapon(vector<pair<Weapon*,int>> Weapons);
            Character* ChooseEnemy(vector<Character*> Enemies);
            
            
            Item* ChooseItem(vector<Item*> Items);

            void ShowEnemies(vector<Character*> Enemies);
            void Prompt(string entry);
            void print(string entry);
            void DamageInfo(Weapon* weapon);
            void PlayerInfo(Player* player);
    };
}

//--------------------
namespace Model{
    class FightModel{
        private:
            vector<Character*> Enemies;
            Player* player;
            int Round;
            
            vector<Item*> Items;
            int droppedCoins;
            
            vector<Relic*> Relics;
        public:
            void setRound(int round);
            int getRound();
            FightModel() = default;
            FightModel(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,vector<Relic*> Relics); //sets the player and the enemies and also the round to zero
            
            Player* getPlayer();
            vector<Character*> getEnemies();
            
            vector<Item*> getItems();
            int getCoins();
            
            vector<Relic*> getRelics();
            void setEnemies(vector<Character*> Enemies);
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
            void EndFight();
        public:
            FightControl(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,vector<Relic*> Relics); //constructs the Model and the View and also calls startFight func
            View::FightView* getView();
            void StartFight();
    };
}
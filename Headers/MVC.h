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

namespace Model{
    class FightModel{
        private:
            vector<Character*> Enemies;
            Player* player;
            int Round;
            
            vector<Item*> Items;
            int droppedCoins;
            string Story;    
            vector<Relic*> Relics;
            
            bool EquipmentsMenu;
        public:
            void setRound(int round);
            int getRound();
            FightModel(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,string Story,vector<Relic*> Relics); //sets the player and the enemies and also the round to zero
            
            Player* getPlayer();
            vector<Character*> getEnemies();
            
            vector<Item*> getItems();
            void setItems(vector<Item*> Items);
            int getCoins();
            string getStory();
            vector<Relic*> getRelics();
            void setEnemies(vector<Character*> Enemies);
            
            void setPlayer(Player* player);
            
            bool getEquipmentsMenu();
            void setEqipmentsMenu(bool entry);
    };
}
//--------------------
namespace View{
    class FightView{
        private:
            Model::FightModel* model;
            int MenuManager(string Description,vector<vector<string>> Options,vector<string> Header);
            void showCharacters();
            void showArmor();
            int getMaxWidth(vector<vector<string>> &entry);
        public:
            FightView(Model::FightModel* fightmodel);
            
            vector<Character*> ChooseEnemies(vector<Character*> Enemies,int amount);
            Consumable* ChooseConsumable(vector<pair<Consumable*,int>> Consumables , string Description);
            Weapon* ChooseWeapon(vector<pair<Weapon*,int>> Weapons , string Description);
            Equipment* ChooseEquipment(vector<pair<Equipment*,int>> Equipments , string Description);
            Character* ChooseEnemy(vector<Character*> Enemies);
            Relic* ChooseRelic(vector<Relic*> Relics);
            
            void Prompt();
            void Prompt(string entry);
            void Prompt(vector<string> entry);
            void print(string entry);
            void DamageInfo(Weapon* weapon);
            
            int MenuManager(string Description,vector<string> Options);
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
            FightControl(Player* player,vector<Character*> Enemies,vector<Item*> Items,int droppedCoins,string Story, vector<Relic*> Relics); //constructs the Model and the View and also calls startFight func
            View::FightView* getView();
            void StartFight();
    };
}
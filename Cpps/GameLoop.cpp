#pragma once
#include "../Headers/creature.h"
#include "../Headers/encounter.h"
#include "../Headers/factory.h"
#include "../Headers/items.h"
#include "../Headers/map.h"
#include "../Headers/MVC.h"
#include "functions.cpp"
#include <ctime>
using namespace std;

string StoryGenerate(){
    string ForestStory = "Legends speak of a forest with its mythical creatures and ancient magic. As an adventure, "
    "you must explore the forest, get into some troubles, fight with eccentric creatures or maybe some super natural human beings "
    "and save the inhabitants with your bravery. You may get into some troubles you can't ever fight against or you may never be "
    "able to get out of the forest. The creatures don't like to be touched so, as a warning, whenever you touch them or make a "
    "noise they'll notice and you must use all your skills to get rid of them. Best of luck with accomplishing your duties. ";
    string  WarStory = "A brutal war started in a battlefield and you are the only one to fight against these giant unusual "
    "creatures, defending your home and properties. There are several creatures waiting for you to fight with. None of them looks "
    "normal. There are human beings with abnormal faces and bodies, terrible-looking zombies and their never-unclosed lips, "
    "unknown giant creatures with odd faces and at the back, the monster you never thought it could exist. So you must be "
    "aware and armed. You know you've been through worst shits and you're still alive. Good luck!";
    string War2Story = "A war started and blood flew everywhere on the streets. You enter a supermarket and bend over to pick a "
    "bottle of water. The sound of walking on the broken glasses terrifies you. ";
    string ZombieStory1 = "";
    vector<string> stories = {ForestStory, WarStory};
    return ShuffleVec(stories)[0];
}

Player* PlayerGenerate(){
    cout << StoryGenerate();
    string name;
    getline(cin, name);
    vector<pair<Weapon*, int>> weapons;
    vector<pair<Item*, int>> items;
    Player* player = new Player(name, 10000, 60, 0, 400, 0, items, weapons);
    vector<Weapon*> AllWeapons = {shotgun, snipe, smg, rifle, coldweapon};
    int item_index = rand() % 5;
    player->addItem(AllWeapons[item_index]);
    player->addItem(new Rifle("lakc" , 0 , 0 , 10000 , 1 , 2 , 2 , 20 , 0));
    return player;
}

void GameLoopFunction(){
    while(true){
        int Menu_Choice = 1;
        srand(time(0));
        Player *player = PlayerGenerate();
        Map *map;
        switch(Menu_Choice){
        case 1:{
            MapFactory Mapfactory(2);
            map = Mapfactory.GenerateMap();
        }
        case 2:{
            break;
        }
        default:{
            break;
        }
        }
        for(int i = 0; i < 3; i++){
            Shopkeeper* ShopKeeper = new Shopkeeper("Amir");
            Medic* medic = new Medic("Bahram");
            FightFactory fight(player , map);
            ShopFactory shop(map , player);
            EnemyFactory enemies(map , player);
            while(map->getCurrentNode().first != 14){
                if(player->getHP() <= 0){
                   break;
                }
                map->move();
                if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Fight"){
                    fight.GenerateNormalFight()->start();
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Shop"){
                    shop.Generate()->Menu();
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Hospital"){
                    Hospital hospital(player , medic);
                    hospital.Menu();
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Random"){
                    RandomEncounter* Random = new RandomEncounter(player);
                    Random->Menu(player , map);
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "MiniBoss"){
                    // fight.GenerateMiniBoss()->start();
                }
            }
            if(player->getHP() <= 0){
                delete player;
                break;
            }
            map->move();
            fight.GenerateBoss()->start(); // to compelete later
            MapFactory Mapfactory(map->getFloor() + 1);
            map = Mapfactory.GenerateMap();
        }
    }
}

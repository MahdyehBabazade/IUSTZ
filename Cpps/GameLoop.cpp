#pragma once
#include "../Headers/creature.h"
#include "../Headers/encounter.h"
#include "../Headers/factory.h"
#include "../Headers/items.h"
#include "../Headers/map.h"
#include "../Headers/MVC.h"

using namespace std;

void GameLoopFunction(){
    // while(true){
        int Menu_Choice = 1;
        srand(time(0));
        Player *player = new Player("Amir" , 100 , 200 , 0 , 100 , 200 , {make_pair(new Shotgun("Reaper", 20, 30, 25, 1, 2, 3, 25, 3) , 1)} , {make_pair(new Shotgun("Reaper", 20, 30, 25, 1, 2, 3, 25, 3) , 1)});
        Map *map;
        switch(Menu_Choice){
        case 1:{
            MapFactory Mapfactory(1);
            map = Mapfactory.GenerateMap();
        }
        case 2:{
            break;
        }
        default:{
            break;
        }
        }
        MapFactory Mapfactory(1);
        Mapfactory.GenerateMap();
        for(int i = 0; i < 3; i++){
            Shopkeeper* ShopKeeper = new Shopkeeper("Amir");
            Medic* medic = new Medic("Bahram");
            FightFactory fight(player , map);
            ShopFactory shop(map , player);
            EnemyFactory enemies(map , player);
            while(map->getCurrentNode().first != 14){
                // if(player == nullptr)
                //    break;
                map->move();
                if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Fight"){
                    Fight* fight = new Fight(player , 1 , enemies.FightEnemy() , {} , 10 , {});
                    fight->start();
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
                    Random->Menu();
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "MiniBoss"){
                    // fight.GenerateMiniBoss()->start();
                }
            }
            map->move();
            // fight.GenerateBoss()->start(); // to compelete later
            MapFactory Mapfactory(map->getFloor() + 1);
            map = Mapfactory.GenerateMap();
            // if(player == nullptr)
            //     break;
        }
    // }
}
void PlayerGenerate(){
//---------------------------- All items --------------------------
// Weapons  
    Shotgun* shotgun = new Shotgun("Reaper", 20, 30, 25, 1, 2, 3, 25, 3);

    Snipe* snipe = new Snipe("Fury", 25, 40, 35, 1, 2, 1, 3);

    SMG* smg = new SMG("Venom", 15, 25, 20, 1, 2, 3, 2);
 
    Rifle* rifle = new Rifle("Twilight Rifle", 20, 40, 30, 2, 2, 3, 1, 2);

    ColdWeapon* coldweapon = new ColdWeapon("Blizzard Blade", 10, 30, 15, 1, 1);
// Remember to delete these variables later (include sth)
//-----------------------------------------------------------------
    string name;
    cin >> name;
    vector<Weapon*> AllWeapons = {shotgun, snipe, smg, rifle, coldweapon};
    int item_index = rand() % 5;
    vector<pair<Weapon*, int>> weapons = {make_pair(AllWeapons[item_index], 1)};
    vector<pair<Item*, int>> items = {make_pair(AllWeapons[item_index], 1)};
    Player* player = new Player(name, 100, 60, 0, 4, 0, items, weapons);
    vector<string> stories; // Stories to be added
}
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
        Player *player = new Player("Amir" , 100 , 200 , 0 , 4 , 200 , {} , {});
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
            while(map->getCurrentNode().first != 14){
                // if(player == nullptr)
                //    break;
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
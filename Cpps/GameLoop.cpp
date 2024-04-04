#include "../Headers/creature.h"
#include "../Headers/encounter.h"
#include "../Headers/factory.h"
#include "../Headers/items.h"
#include "../Headers/map.h"
#include "../Headers/MVC.h"

using namespace std;

void GameLoopFunction(){
    while(true){
        int Menu_Choice;
        srand(time(0));
        Player *player;
        Map *map;
        FightFactory fight(player , map);
        ShopFactory shop(map , player);
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
        while(map->getFloor() != 4){
            while(map->getCurrentNode().first != 15){
                map->move();
                if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Fight"){
                    // to be filled later
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Shop"){
                    shop.Generate()->Menu();
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Hospital"){
                    // to compelete later
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "Random"){
                    RandomEncounter* Random = new RandomEncounter(player);
                    Random->Menu();
                }
                else if(map->getEncounters()[map->getCurrentNode().first][map->getCurrentNode().second] == "MiniBoss"){
                    // to be filled later
                }
            }
            map->move();
            fight.GenerateBoss(); // to compelete later
            MapFactory Mapfactory(map->getFloor() + 1);
            map = Mapfactory.GenerateMap();
        }
    }
}
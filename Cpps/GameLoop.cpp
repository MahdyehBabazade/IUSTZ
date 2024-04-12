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


Player* PlayerGenerate(){
    vector<string> stories = {"Waking up confused, a soldier can't remember their name.\nAnother soldier asks, Hey, what's your name?",
    "You find yourself in a city square, surrounded by unfamiliar faces.\nA stranger approaches and says, 'Hey, sorry to bother you, but what's your name?' ",
    "Waking up confused, with a headache, you put your hand on your head and try to stand up.\nYou see a few people are around you.\nTrying to understand what they're trying to tell you, you hear one of them who looks to be an officer, ask your name.",
    "Openning your eyes feeling some pressure on your chest then feeling some water coming out of your mouth,\nan old man asks 'Are you OK? What's your name soldier?'",
    "In a situation where survival is uncertain, a soldier says, 'I want to know who fought by my side. What's your name?'",
    "After a helicopter crash, two soldiers survive. One asks the other, 'We made it out alive. What's your name, soldier'?",
    "A soldier wakes up disoriented in a field hospital and the nurse ask him, 'Can you remember anything? What's your name?'"};
    cout << ShuffleVec(stories)[0] << endl << "I'm ";
    string name;
    getline(cin, name);
    vector<pair<Weapon*, int>> weapons;
    vector<pair<Item*, int>> items;
    Player* player = new Player(name, 10000, 60, 0, 400, 1000, items, weapons);
    vector<Weapon*> AllWeapons = {new Shotgun(shotgun), new Snipe(snipe), new SMG(smg), new Rifle(rifle), new ColdWeapon(coldweapon)};
    int item_index = rand() % 5;
    player->addItem(AllWeapons[item_index]);
    player->addItem(new Rifle("lakc" , 0 , 0 , 10000 , 1 , 2 , 2 , 20 , 0));
    return player;
}

void GameLoopFunction(){
    while(true){
        string symbol = " ___  ___ ___  _______  _______ " + red + " _______ \n" + reset+
                        "|   ||   Y   ||   _   ||       |" + red + "|   _   |\n" + reset+
                        "|.  ||.  |   ||   1___||.|   | |" + red + "|___|   |\n" + reset+
                        "|.  ||.  |   ||____   |`-|.  |-'" + red + " /  ___/ \n" + reset+
                        "|:  ||:  1   ||:  1   |  |:  |  " + red + "|:  1  \\ \n" + reset+
                        "|::.||::.. . ||::.. . |  |::.|  " + red + "|::.. . |\n" + reset+
                        "`---'`-------'`-------'  `---'  " + red + "`-------'\n" + reset+"\n\n\n";

        int Menu_Choice = Choose(symbol , {"       Start" , "       Exit"});
        clearScreen();
        srand(time(0));
        Map *map;
        Player *player;
        switch(Menu_Choice){
        case 1:{
            MapFactory Mapfactory(1);
            map = Mapfactory.GenerateMap();
            player = PlayerGenerate();
        }
        break;
        case 2:{
            break;
        }
        default:{
            break;
        }
        }
        while(map->getFloor() != 4){
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
                    fight.GenerateMiniBoss()->start();
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

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
    player->addItem(new Rifle("lakc" , 0 , 0 , 10000 , 1 , 2 , 20 , 20 , 0));
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

        vector<string> Names = {"Steve" , "Donald" , "Megan" , "Myria" , "James" , "Jhon" , "Sarah" , "Jennifer" ,
        "Selena" , "Jake" , "Jimmy" , "James" , "Emma" , "Olivia" , "William" , "Ava" , "Benjamin" , "Sophia" , "Noah" ,
        "Oliver" , "Mia" , "Jackson" , "Alexander" , "Micheal" , "Ethan" , "Abigail" , "Danial" , "Lucas" , "Grace" ,
        "Henry" , "Lily" ,"Tom"};
        int Menu_Choice = 0;
        bool breaker = true;
        while(breaker){
            clearScreen();
            cout << symbol;
            if(Menu_Choice == 0){
                cout << green;
            }
            cout << "    1. Start\n" << reset;
            if(Menu_Choice == 1){
                cout << green;
            }
            cout << "    2. Exit\n" << reset;
            char key = _getch();
            switch (tolower(key))
            {
            case 'w':
                Menu_Choice = (Menu_Choice + 1) % 2 ;
                break;
            case 's':
                Menu_Choice = (Menu_Choice + 1) % 2 ;
                break;
            case '\r':
                breaker = false;
                break;
            default:
                break;
            }
        }
        Menu_Choice++;
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
            exit(0);
        }
        default:{
            break;
        }
        }
        while(map->getFloor() != 4){
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
                    Medic* medic = new Medic(ShuffleVec(Names)[0]);
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
        clearScreen();
        cout << green << "YOU'VE WON" << yellow << "!!!\n\n\n" << reset;
        cout << "A work fined by Saleh , Mahdieh , Bahar and Amir\n";
        getch();
    }
}

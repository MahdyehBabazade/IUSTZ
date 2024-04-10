#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <conio.h>

using namespace std;

const string yellow("\033[1;33m");
const string red("\033[0;31m");
const string reset("\033[0m");
const string cyan("\033[0;36m");
const string green("\033[1;32m");
const string magenta("\033[0;35m");
const string grey("\033[90m");

//---------------------------- All items --------------------------
// Guns 
    Shotgun shotgun("Peppergun", 20, 30, 25, 1, 2, 3, 25, 3);
    Shotgun shotgun2("Scatterer Supreme", 20, 40, 35, 1, 2, 5, 27, 3);
    Shotgun shotgun3("Scatter Shot", 20, 60, 50, 1, 2, 4, 28, 3); // A better shotgun

    Snipe snipe("Scope Sniper", 25, 40, 35, 1, 2, 1, 3);
    Snipe snipe2("Sharpshooter", 25, 50, 45, 1, 2, 1, 3);
    Snipe snipe3("Ghostfire", 25, 70, 60, 1, 2, 2, 3); // A better sniper

    SMG smg("Venom", 15, 25, 20, 1, 2, 3, 2);
    SMG smg2("Hurricane", 15, 35, 30, 1, 2, 4, 2);
    SMG smg3("Rapidfire", 15, 50, 45, 1, 2, 5, 3); // A better SMG

    Rifle rifle("Twilight Rifle", 20, 40, 30, 2, 2, 3, 1, 2);
    Rifle rifle2("Inferno Hunter", 20, 50, 40, 2, 2, 4, 2, 2);
    Rifle rifle3("Dawnbreaker", 20, 65, 55, 2, 2, 4, 3, 3); // A better rifle

    // Cold Weapons
    ColdWeapon coldweapon("Blizzard Blade", 10, 25, 10, 1, 1);
    ColdWeapon coldweapon2("Snowfall Sword", 10, 30, 15, 1, 1);
    ColdWeapon coldweapon3("Icebreaker Axe", 10, 35, 20, 1, 1);
    ColdWeapon coldweapon4("Frozen Blade", 10, 40, 25, 1, 2);
    ColdWeapon coldweapon5("Chill Blade", 10, 45, 30, 1, 2);
    ColdWeapon coldweapon6("Arctic Knife", 10, 50, 35, 1, 2);
    ColdWeapon coldweapon7("Frostwind Blade", 10, 55, 40, 1, 2);
    ColdWeapon coldweapon8("Arctic Sword", 10, 60, 45, 1, 3);
    ColdWeapon coldweapon9("Frost Axe", 10, 70, 50, 1, 3);
    ColdWeapon coldweapon10("Blizzard Dagger", 10, 80, 55, 1, 3); // Better

    // Throwables
    Grenade grenade("Chill Grenade", 7, 10, 30, 1, 1);
    Grenade grenade2("Firebomb", 7, 15, 40, 1, 2);
    Grenade grenade3("Snowball", 7, 25, 60, 1, 3); // Better

    BoomRang boomerang("SpinStorm", 8, 15, 15, 1, 2);
    BoomRang boomerang2("BoomerBoost", 8, 20, 20, 1, 2);
    BoomRang boomerang3("Whirlwind", 8, 30, 30, 1, 2); // Better

    // Consumables
    Consumable ShieldConsumable("ShieldBoost", "ShieldPotion", 5, 20, 20);
    Consumable ShieldConsumable2("GuardPotion", "ShieldPotion", 5, 25, 30);
    Consumable ShieldConsumable3("SafeguardSip", "ShieldPotion", 5, 35, 45);

    Consumable HPConsumable("HealthBoost", "HPPotion", 6, 25, 20);
    Consumable HPConsumable2("StaminaSip", "HPPotion", 6, 30, 50);
    Consumable HPConsumable3("Lifespring", "HPPotion", 6, 40, 75);

    Consumable EnergyConsumable("Energy Elixir", "EnergyPotion", 7, 30, 1);
    Consumable EnergyConsumable2("Energy Boost", "EnergyPotion", 7, 60, 2);

    // Equipments
    Vest vest("ShieldSkin", 0, 40, 5);
    Vest vest2("GuardianShell", 0, 50, 10);
    Vest vest3("ArmorGuard", 0, 70, 20);

    HeadGear headgear("Armor Crown", 0, 30, 5);
    HeadGear headgear2("Warding Helmet", 0, 50, 9);
    HeadGear headgear3("Helm of Valor", 0, 80, 15); 

    FootWear footwear("Safeguard Shoes", 0, 15, 3);
    FootWear footwear2("Shielded Steps", 0, 30, 7);
    FootWear footwear3("Fortress Footwear", 0, 75, 15);

    Boot boot("Defender's Boots", 0, 15, 3);
    Boot boot2("Ironstride Boots", 0, 30, 5);
    Boot boot3("Sentinel Boots", 0, 40, 10);

    // Relics
    Relic relic("Sunstone", 0, 0, 0.1, 0.25);
    Relic relic2("Earthstone", 0, 0, 0.5, 0.25);
    Relic relic3("Moonlight Amulet", 0, 0, 0.15, 0.5);
    Relic relic4("Bloodmoon Relic", 0, 0, 0.2, 0.5);
    Relic relic5("Starfall Shard", 0, 0, 0.25, 0.5);
    Relic relic6("Crystal Tear", 0, 0, 0.3, 0.5);
    Relic relic7("Crown of Destiny", 0, 0, 0.35, 0.25);
    Relic relic8("Titan's Heartstone", 0, 0, 0.4, 0.25);
    Relic relic9("Celestial Compass", 0, 0, 0.45, 0.25);

//-----------------------------------------------------------------


int random_num(int min,int max){
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(min,max); 

    return dist(rng);
}

template <typename T>
vector<T> ShuffleVec(vector<T> vec){ // Shuffles a vector
    random_device rd;
    default_random_engine abs(rd());
    shuffle(vec.begin(), vec.end(), abs);   
    return vec;
}

int Index_Weighted_Random(vector<int> weights){
    random_device rd;
    default_random_engine gen(rd());
    discrete_distribution<> dist(weights.begin(),weights.end());
    return dist(gen);
}

vector<int> Shuffle(vector<int> vec){ 
    random_device rd;
    default_random_engine abs(rd());
    shuffle(vec.begin(), vec.end(), abs);
    return vec;
}

void clearScreen(){
    system("cls");
}


int Choose(vector<string> Options){
    int option =0;
    int vecSize = Options.size();
    while(true){
        clearScreen();
        for(int i = 0; i < Options.size() ; i++){
            if(i == option % vecSize){
                cout << green <<Options[i] << reset << endl;
            }else {
                cout << Options[i] << endl;
            }
        }
        char input = _getch();
        switch(tolower(input)){
            case 'w':
            {
                option --;
                option %= vecSize;
                continue;
            }
            case 's':
            {
                option++;
                option %= vecSize;
                continue;
            }
            case '\r':
                break;
            
            default:
                continue;
                
        }
        break;
    }
    return option + 1;
}


int Choose(string Descriptions ,vector<string> Options){
    int option = 0;
    while(true){
        clearScreen();
        cout << Descriptions;
        for(int i = 0; i < Options.size() ; i++){
            if(i == option){
                cout << green << Options[i] << reset << endl;
            }else {
                cout << Options[i] << endl;
            }
        }
        char input = _getch();
        switch(tolower(input)){
            case 'w':
            {
                option = (option - 1 + Options.size()) % Options.size();
                continue;
            }
            case 's':
            {
                option++;
                option %= Options.size();
                continue;
            }
            case '\r':
                break;
            
            default:
                continue;
                
        }
        break;
    }
    return option % Options.size() + 1;
}

int Choose(vector<string> Options,vector<bool> Chooseable){
    int option =find(Chooseable.begin(),Chooseable.end(),true) - Chooseable.begin();
    int vecSize = Options.size();
    while(true){
        system("cls");
        cout << "option : " << option << endl;
        for(int i = 0; i < Options.size() ; i++){
            if(i == option){
                cout << green <<Options[i] << reset << endl;
            }else if(Chooseable[i]){
                cout << Options[i] << endl;
            }else {
                cout << red << Options[i] << reset << endl;
            }
        }
        char input = _getch();
        switch(tolower(input)){
            case 'w':
            {
                int index = find(Chooseable.rbegin() + vecSize - option,Chooseable.rend(),true) - Chooseable.rbegin();
                if(index == vecSize){
                    index = find(Chooseable.rbegin() ,Chooseable.rend(),true) - Chooseable.rbegin();
                }
                index = vecSize - index - 1;
                
                option = index;
                
                continue;
            }
            case 's':
            {
                int index = find(Chooseable.begin() + option + 1,Chooseable.end(),true) - Chooseable.begin();
                if(index == vecSize){
                    index = find(Chooseable.begin() ,Chooseable.end(),true) - Chooseable.begin();
                }
                option = index;
                continue;
            }
            case '\r':
                break;
            
            default:
                continue;
                
        }
        break;
    }
    return option + 1;
}
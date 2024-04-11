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
    Shotgun* shotgun = new Shotgun("Peppergun", 20, 30, 25, 1, 2, 3, 25, 3);
    Shotgun* shotgun2 = new Shotgun("Scatterer Supreme", 20, 40, 35, 1, 2, 5, 27, 3);
    Shotgun* shotgun3 = new Shotgun("Scatter Shot", 20, 60, 50, 1, 2, 4, 28, 3); // A better shotgun

    Snipe* snipe = new Snipe("Scope Sniper", 25, 40, 35, 1, 2, 1, 3);
    Snipe* snipe2 = new Snipe("Sharpshooter", 25, 50, 45, 1, 2, 1, 3);
    Snipe* snipe3 = new Snipe("Ghostfire", 25, 70, 60, 1, 2, 2, 3); // A better sniper

    SMG* smg = new SMG("Venom", 15, 25, 20, 1, 2, 3, 2);
    SMG* smg2 = new SMG("Hurricane", 15, 35, 30, 1, 2, 4, 2);
    SMG* smg3 = new SMG("Rapidfire", 15, 50, 45, 1, 2, 5, 3); // A better SMG

    Rifle* rifle = new Rifle("Twilight Rifle", 20, 40, 30, 2, 2, 3, 1, 2);
    Rifle* rifle2 = new Rifle("Inferno Hunter", 20, 50, 40, 2, 2, 4, 2, 2);
    Rifle* rifle3 = new Rifle("Dawnbreaker", 20, 65, 55, 2, 2, 4, 3, 3); // A better rifle

    // Cold Weapons
    ColdWeapon* coldweapon = new ColdWeapon("Blizzard Blade", 10, 25, 10, 1, 1);
    ColdWeapon* coldweapon2 = new ColdWeapon("Snowfall Sword", 10, 30, 15, 1, 1);
    ColdWeapon* coldweapon3 = new ColdWeapon("Ice Dagger", 10, 35, 20, 1, 1);
    ColdWeapon* coldweapon4 = new ColdWeapon("Ice Dagger", 10, 40, 25, 1, 2);
    ColdWeapon* coldweapon5 = new ColdWeapon("Ice Dagger", 10, 45, 30, 1, 2);
    ColdWeapon* coldweapon6 = new ColdWeapon("Ice Dagger", 10, 50, 35, 1, 2);
    ColdWeapon* coldweapon7 = new ColdWeapon("Ice Dagger", 10, 55, 40, 1, 2);
    ColdWeapon* coldweapon8 = new ColdWeapon("Ice Dagger", 10, 60, 45, 1, 3);
    ColdWeapon* coldweapon9 = new ColdWeapon("Ice Dagger", 10, 70, 50, 1, 3);
    ColdWeapon* coldweapon10 = new ColdWeapon("Ice Dagger", 10, 80, 55, 1, 3); // Better

    // Throwables
    Grenade* grenade = new Grenade("Chill Grenade", 7, 10, 30, 1, 1);
    Grenade* grenade2 = new Grenade("Firebomb", 7, 15, 40, 1, 2);
    Grenade* grenade3 = new Grenade("Snowball", 7, 25, 60, 1, 3); // Better

    BoomRang* boomerang = new BoomRang("SpinStorm", 8, 15, 15, 1, 2);
    BoomRang* boomerang2 = new BoomRang("BoomerBoost", 8, 20, 20, 1, 2);
    BoomRang* boomerang3 = new BoomRang("Whirlwind", 8, 30, 30, 1, 2); // Better

    // Consumables
    Consumable* ShieldConsumable = new Consumable("ShieldBoost", "ShieldPotion", 5, 20, 20);
    Consumable* ShieldConsumable2 = new Consumable("GuardPotion", "ShieldPotion", 5, 25, 30);
    Consumable* ShieldConsumable3 = new Consumable("SafeguardSip", "ShieldPotion", 5, 35, 45);

    Consumable* HPConsumable = new Consumable("HealthBoost", "HPPotion", 6, 25, 20);
    Consumable* HPConsumable2 = new Consumable("StaminaSip", "HPPotion", 6, 30, 50);
    Consumable* HPConsumable3 = new Consumable("Lifespring", "HPPotion", 6, 40, 75);

    Consumable* EnergyConsumable = new Consumable("Energy Elixir", "EnergyPotion", 7, 30, 1);
    Consumable* EnergyConsumable2 = new Consumable("Energy Boost", "EnergyPotion", 7, 60, 2);

    // Equipments
    Vest* vest = new Vest("ShieldSkin", 0, 40, 5);
    Vest* vest2 = new Vest("GuardianShell", 0, 50, 10);
    Vest* vest3 = new Vest("ArmorGuard", 0, 70, 20);

    HeadGear* headgear = new HeadGear("Armor Crown", 0, 30, 5);
    HeadGear* headgear2 = new HeadGear("Warding Helmet", 0, 50, 9);
    HeadGear* headgear3 = new HeadGear("Helm of Valor", 0, 80, 15); 

    FootWear* footwear = new FootWear("Safeguard Shoes", 0, 15, 3);
    FootWear* footwear2 = new FootWear("Shielded Steps", 0, 30, 7);
    FootWear* footwear3 = new FootWear("Fortress Footwear", 0, 75, 15);

    Boot* boot = new Boot("Defender's Boots", 0, 15, 3);
    Boot* boot2 = new Boot("Ironstride Boots", 0, 30, 5);
    Boot* boot3 = new Boot("Sentinel Boots", 0, 40, 10);

    // Relics
    Relic* relic = new Relic("Sunstone", 0, 0, 10, 25);
    Relic* relic2 = new Relic("Earthstone", 0, 0, 50, 25);
    Relic* relic3 = new Relic("Moonlight Amulet", 0, 0, 15, 50);
    Relic* relic4 = new Relic("Bloodmoon Relic", 0, 0, 20, 50);
    Relic* relic5 = new Relic("Starfall Shard", 0, 0, 25, 50);
    Relic* relic6 = new Relic("Crystal Tear", 0, 0, 30, 50);
    Relic* relic7 = new Relic("Crown of Destiny", 0, 0, 35, 25);
    Relic* relic8 = new Relic("Titan's Heartstone", 0, 0, 40, 25);
    Relic* relic9 = new Relic("Celestial Compass", 0, 0, 45, 25);

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
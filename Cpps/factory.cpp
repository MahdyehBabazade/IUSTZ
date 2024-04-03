#pragma once
#include "../Headers/factory.h"
#include "functions.cpp"
#include <random>
#include<algorithm>
using namespace std;

//---------------------------- All items --------------------------
// Guns 
    Shotgun* shotgun = new Shotgun("Reaper", 20, 30, 25, 1, 2, 3, 25, 3);
    Shotgun* shotgun2 = new Shotgun("Death Dealer", 20, 40, 35, 1, 2, 5, 27, 3);
    Shotgun* shotgun3 = new Shotgun("Hellfire", 20, 60, 50, 1, 2, 4, 28, 3); // A better shotgun

    Snipe* snipe = new Snipe("Fury", 25, 40, 35, 1, 2, 1, 3);
    Snipe* snipe2 = new Snipe("Sharpshooter", 25, 50, 45, 1, 2, 1, 3);
    Snipe* snipe3 = new Snipe("Ghostfire", 25, 70, 60, 1, 2, 2, 3); // A better sniper

    SMG* smg = new SMG("Venom", 15, 25, 20, 1, 2, 3, 2);
    SMG* smg2 = new SMG("Hurricane", 15, 35, 30, 1, 2, 4, 2);
    SMG* smg3 = new SMG("Rapidfire", 15, 50, 45, 1, 2, 5, 3); // A better SMG

    Rifle* rifle = new Rifle("Twilight Rifle", 20, 40, 30, 2, 2, 3, 1, 2);
    Rifle* rifle2 = new Rifle("Inferno Hunter", 20, 50, 40, 2, 2, 4, 2, 2);
    Rifle* rifle3 = new Rifle("Dawnbreaker", 20, 65, 55, 2, 2, 4, 3, 3); // A better rifle

    // Cold Weapons
    ColdWeapon* coldweapon = new ColdWeapon("Blizzard Blade", 10, 30, 15, 1, 1);
    ColdWeapon* coldweapon2 = new ColdWeapon("Snowfall Sword", 10, 40, 20, 1, 2);
    ColdWeapon* coldweapon3 = new ColdWeapon("Ice Dagger", 10, 55, 35, 1, 3); // Better

    // Throwables
    Grenade* grenade = new Grenade("Chill Grenade", 7, 10, 30, 1, 1);
    Grenade* grenade2 = new Grenade("Firebomb", 7, 15, 40, 1, 2);
    Grenade* grenade3 = new Grenade("Snowball", 7, 25, 60, 1, 3); // Better

    BoomRang* boomerang = new BoomRang("SpinStorm", 15, 15, 15, 1, 2);
    BoomRang* boomerang2 = new BoomRang("BoomerBoost", 15, 20, 20, 1, 2);
    BoomRang* boomerang3 = new BoomRang("FuryFlight", 15, 30, 30, 1, 2); // Better

    // Consumables
    Consumable* ShieldConsumable = new Consumable("ShieldBoost", "ShieldPotion", 7, 20, 20);
    Consumable* ShieldConsumable2 = new Consumable("GuardPotion", "ShieldPotion", 7, 25, 30);
    Consumable* ShieldConsumable3 = new Consumable("SafeguardSip", "ShieldPotion", 7, 35, 45);

    Consumable* HPConsumable = new Consumable("HealthBoost", "HPPotion", 8, 25, 30);
    Consumable* HPConsumable2 = new Consumable("StaminaSip", "HPPotion", 8, 30, 50);
    Consumable* HPConsumable3 = new Consumable("Lifespring", "HPPotion", 8, 40, 75);

    Consumable* EnergyConsumable = new Consumable("Energy Elixir", "EnergyPotion", 7, 30, 1);
    Consumable* EnergyConsumable2 = new Consumable("Energy Boost", "EnergyPotion", 7, 60, 2);

    // Equipments
    Vest* vest = new Vest("ShieldSkin", 0, 40, 20);
    Vest* vest2 = new Vest("GuardianShell", 0, 50, 25);
    Vest* vest3 = new Vest("ArmorGuard", 0, 70, 40);

    HeadGear* headgear = new HeadGear("Armor Crown", 0, 30, 15);
    HeadGear* headgear2 = new HeadGear("Warding Helmet", 0, 50, 25);
    HeadGear* headgear3 = new HeadGear("Helm of Valor", 0, 80, 45); 

    FootWear* footwear = new FootWear("Safeguard Shoes", 0, 15, 10);
    FootWear* footwear2 = new FootWear("Shielded Steps", 0, 30, 20);
    FootWear* footwear3 = new FootWear("Fortress Footwear", 0, 75, 50);

    Boot* boot = new Boot("Defender's Boots", 0, 15, 10);
    Boot* boot2 = new Boot("Ironstride Boots", 0, 30, 15);
    Boot* boot3 = new Boot("Sentinel Boots", 0, 40, 25);

    // Relics
    Relic* relic = new Relic("Sunstone", 0, 0, 0.1, 0.25);
    Relic* relic2 = new Relic("Earthstone", 0, 0, 0.5, 0.25);
    Relic* relic3 = new Relic("Moonlight Amulet", 0, 0, 0.15, 0.5);
    Relic* relic4 = new Relic("Bloodmoon Relic", 0, 0, 0.2, 0.5);
    Relic* relic5 = new Relic("Starfall Shard", 0, 0, 0.25, 0.5);
    Relic* relic6 = new Relic("Crystal Tear", 0, 0, 0.3, 0.5);
    Relic* relic7 = new Relic("Crown of Destiny", 0, 0, 0.35, 0.25);
    Relic* relic8 = new Relic("Titan's Heartstone", 0, 0, 0.4, 0.25);
    Relic* relic9 = new Relic("Celestial Compass", 0, 0, 0.45, 0.25);

//-----------------------------------------------------------------

ShopFactory :: ShopFactory(Map* map, Player* player, Shopkeeper* shopkeeper){
    this -> map = map;
    this -> player = player;
    this -> shopkeeper = shopkeeper;
}

Shop* ShopFactory :: Generate(){

    vector<Weapon*> AllWeapons = {shotgun, shotgun2, shotgun3, snipe, snipe2, snipe3, smg, smg2, smg3, rifle, rifle2, rifle3, 
    coldweapon, coldweapon2, coldweapon3, grenade, grenade2, grenade3, boomerang, boomerang2, boomerang3};

    vector<Consumable*> AllConsumables ={ShieldConsumable, ShieldConsumable2, ShieldConsumable3, HPConsumable, HPConsumable2, 
    HPConsumable3, EnergyConsumable, EnergyConsumable2};

    vector<Equipment*> AllEquipments = {vest, vest2, vest3, headgear, headgear2, headgear3, footwear, footwear2, footwear3, boot, 
    boot2, boot3};

    vector<Weapon*> Weapons;
    vector<Consumable*> Consumables;
    vector<Equipment*> Equipments;

    int item_index;
    switch (map->getFloor())
    {
    case 1:
        for (int i = 0; i < 5; i++)
        {
            item_index = Index_Weighted_Random({5,2,1,5,2,1,5,2,1,5,2,1,6,3,2,5,2,1,5,2,1});
            Weapons[i] = AllWeapons[item_index];
        }
        
        for (int i = 0; i < 4; i++)
        {
            item_index = Index_Weighted_Random({5,2,1,5,2,1,5,2,1});
            Consumables[i] = AllConsumables[i];
        }
        
        for (int i = 0; i < 2; i++)
        {
            item_index = Index_Weighted_Random({5,2,1,5,2,1,5,2,1,5,2,1});
            Equipments[i] = AllEquipments[item_index];
        }
        break;

    case 2:
        for (int i = 0; i < 5; i++)
        {
            item_index = Index_Weighted_Random({2,5,1,2,5,1,2,5,1,2,5,1, 3,6,2 ,2,5,1,2,5,1});
            Weapons[i] = AllWeapons[item_index];
        }
        
        for (int i = 0; i < 4; i++)
        {
            item_index = Index_Weighted_Random({2,5,1,2,5,1,2,5,1});
            Consumables[i] = AllConsumables[i];
        }
        
        for (int i = 0; i < 2; i++)
        {
            item_index = Index_Weighted_Random({2,5,1,2,5,1,2,5,1,2,5,1});
            Equipments[i] = AllEquipments[item_index];
        }
        break;

    case 3:
        for (int i = 0; i < 5; i++)
        {
            item_index = Index_Weighted_Random({1,2,5,1,2,5,1,2,5,1,2,5, 2,3,6, 1,2,5,1,2,5});
            Weapons[i] = AllWeapons[item_index];
        }
        
        for (int i = 0; i < 4; i++)
        {
            item_index = Index_Weighted_Random({1,2,5,1,2,5,1,2,5});
            Consumables[i] = AllConsumables[i];
        }
        
        for (int i = 0; i < 2; i++)
        {
            item_index = Index_Weighted_Random({1,2,5,1,2,5,1,2,5});
            Equipments[i] = AllEquipments[item_index];
        }
        break;
    
    default:
        break;
    }

    Shop* shop = new Shop(player, Weapons, Consumables, Equipments, shopkeeper);
    return shop;
}

EnemyFactory :: EnemyFactory(Map* map , Player* player){
    this -> map = map;
    this -> player = player;
}

void EnemyFactory :: setDifficulty(int Difficulty){this -> Difficulty = Difficulty;}

string EnemyFactory :: ZombieNameset(){
    vector<string> Names = {"Tank" , "Agile"};
    return ShuffleVec(Names)[0];
}

string EnemyFactory :: HumanEnemyNameset(){
    vector<string> Names = {"Steve" , "Donald" , "Megan" , "Myria" , "James" , "Jhon" , "Sarah" , "Jennifer" ,
    "Selena" , "Jake" , "Jimmy" , "James" , "Emma" , "Olivia" , "William" , "Ava" , "Benjamin" , "Sophia" , "Noah" ,
    "Oliver" , "Mia" , "Jackson" , "Alexander" , "Micheal" , "Ethan" , "Abigail" , "Danial" , "Lucas" , "Grace" ,
    "Henry" , "Lily" ,"Tom"};
    return ShuffleVec(Names)[0];
}

double EnemyFactory :: Armorset(){
    vector<int> weights = {4 , 3 , 2 , 1};
    vector<double> armorsets = {7.5 , 10 , 12.5 , 15 , 17.25 , 20 , 22.5 , 25 , 27.5 , 30 , 32.5 , 35 , 37.5 , 40 ,
    42.5 , 45 , 47.5 , 50};
    return armorsets[min(17 , Index_Weighted_Random(weights) + Difficulty/4)];
}

int EnemyFactory :: MaxHPset(){
    vector<int> weights = {4 , 3 , 2 , 1};
    return 30 + 10 * pow(1.1 , Difficulty/2 + Index_Weighted_Random(weights));
}

vector<pair<Weapon* , int>> EnemyFactory :: Weaponset(int type){
    if(type == 1){
        vector<pair<Weapon* , int>> AllWeapons;
        vector<int> weights = {4 , 3 , 2};
        for(int i = 0 ; i < 2; i++){
            int random = rand() % 2;
            if(random == 0)
                AllWeapons.push_back(make_pair(new Shotgun("Shotgun" , 0 , 0 , 
                ceil(6 + 3 * pow(1.1 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0 , 2 , 100 , 0) , 1));
            else
                AllWeapons.push_back(make_pair(new Shotgun("Shotgun" , 0 , 0 , 
                ceil(9 + 2.5 * pow(1.1 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0 , 2 , 100 , 0) , 1));
        }
        int Coldrandom = rand() % 2;
        if(Coldrandom == 0)
            AllWeapons.push_back(make_pair(new ColdWeapon("Sword" , 0 , 0 , 
            ceil(4 + 2 * pow(1.1 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0) , Index_Weighted_Random(weights) + 1));
        else
            AllWeapons.push_back(make_pair(new ColdWeapon("Katana" , 0 , 0 , 
            ceil(5.5 + 1.9 * pow(1.09 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0) , Index_Weighted_Random(weights) + 1));
        if(Difficulty >= 8){
            int random = rand() % 2 + 1;
            for(int i = 0 ; i < random; i++){
                int random = rand() % 5;
                switch(random){
                    case 0:
                        AllWeapons.push_back(make_pair(new BoomRang("boomrang" , 0 , 0 ,
                        ceil(10 + 2 * pow(1.1 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0) , 2));
                        break;
                    case 1:
                        AllWeapons.push_back(make_pair(new BoomRang("boomrang" , 0 , 0 ,
                        ceil(10 + 2 * pow(1.1 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0) , 1));
                        break;
                    case 2:
                        AllWeapons.push_back(make_pair(new Grenade("Grenade" , 0 , 0 ,
                        ceil(10 + 2.5 * pow(1.1 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0) , 2));
                        break;
                    case 3:
                        AllWeapons.push_back(make_pair(new Grenade("Grenade" , 0 , 0 ,
                        ceil(10 + 2 * pow(1.1 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0) , 1));
                        break;
                    default:
                        break;
                }
            }
        }
        return AllWeapons;
    }
    else{
        vector<pair<Weapon* , int>> Allweapons;
        vector<int> weights = {5 , 4 , 3 , 2 , 1};
        Allweapons.push_back(make_pair(new Punch("Claw" , 0 , 
        ceil(6 + 2 * pow(1.08 , Difficulty/3.5 + Index_Weighted_Random(weights))) , 0 , 0) , 1));
        Allweapons.push_back(make_pair(new Punch("Claw" , 0 , 
        ceil(8 + 2 * pow(1.09 , Difficulty/3.5 + Index_Weighted_Random(weights))) , 0 , 0) , 1));
        Allweapons.push_back(make_pair(new Punch("Claw" , 0 , 
        ceil(10 + 2 * pow(1.1 , Difficulty/3.5 + Index_Weighted_Random(weights))) , 0 , 0) , 1));
        return Allweapons;
    }
}

vector<pair<Consumable* , int>> EnemyFactory :: Consumableset(int type){
    vector<pair<Consumable* , int>> Consumables = {};
    Consumables.push_back(make_pair(new Consumable("Healing tonic" , "HPPotion" , 0 , 0 , 20) , 0));
    Consumables.push_back(make_pair(new Consumable("Elexir of vitality" , "HPPotion" , 0 , 0 , 50) , 0));
    Consumables.push_back(make_pair(new Consumable("Divin Essence" , "HPPotion" , 0 , 0 , 80) , 0));
    Consumables.push_back(make_pair(new Consumable("Barrier Shield" , "ShieldPotion" , 0 , 0 , 30) , 0));
    Consumables.push_back(make_pair(new Consumable("Gaurdian Brew" , "ShieldPotion" , 0 , 0 , 60) , 0));
    Consumables.push_back(make_pair(new Consumable("Aegis Elixir" , "ShieldPotion" , 0 , 0 , 90) , 0));
    vector<int> weights = {0 , 0 , 0 , 0 , 0 , 0};
    if(type == 1){
        if(Difficulty >= 8)
            weights = {5 , 1 , 0 , 5 , 1 , 0};
        else if(Difficulty >= 22)
            weights = {7 , 3 , 0 , 7 , 3 , 0};
        else if(Difficulty >= 36)
            weights = {10 , 5 , 1 , 10 , 5 , 1};
        else if(Difficulty >= 50)
            weights = {10 , 7 , 3 , 10 , 7 , 3};
        if(Difficulty >= 8)
            Consumables[Index_Weighted_Random(weights)].second++;
        else if(Difficulty >= 22)
            for(int i = 0 ; i < 2; i++)
                Consumables[Index_Weighted_Random(weights)].second++;
        else if(Difficulty >= 36)
            for(int i = 0; i < 3; i++)
                Consumables[Index_Weighted_Random(weights)].second++;
        else if(Difficulty >= 50)
            for(int i = 0; i < 4; i++)
                Consumables[Index_Weighted_Random(weights)].second++;
    }
    vector<pair<Consumable* , int>> Consum;
    for(int i = 0; i < 6 ; i++){
        if(Consumables[i].second != 0)
            Consum.push_back(Consumables[i]);
    }
    return Consum;
}

vector<pair<Item* , int>> EnemyFactory :: Itemset(vector<pair<Weapon* , int>> Weapons, 
vector<pair<Consumable* , int>> Consumables){
    vector<pair<Item* , int>> Items;
    for(int i = 0; i < Weapons.size(); i++)
        Items.push_back(Weapons[i]);
    for(int i = 0; i < Consumables.size(); i++)
        Items.push_back(Consumables[i]);
    return Items;
}

HumanEnemy* EnemyFactory :: HumanEnemyMaker(){
    string Name = HumanEnemyNameset();
    int MaxHP = MaxHPset();
    double Armor = Armorset();
    vector<pair<Weapon* , int>> weapons = Weaponset(1);
    vector<pair<Consumable* , int>> Consumables = Consumableset(1);
    vector<pair<Item* , int>> Items = Itemset(weapons , Consumables);
    return new HumanEnemy(Name , MaxHP , Armor , Items , weapons , Consumables);    
}

Zombie* EnemyFactory :: ZombieMaker(){
    string Name = ZombieNameset();
    int MaxHP = MaxHPset();
    double Armor = Armorset();
    vector<pair<Weapon* , int>> weapons = Weaponset(2);
    vector<pair<Consumable* , int>> Consumables = Consumableset(2);
    vector<pair<Item* , int>> Items = Itemset(weapons , Consumables);
    return new Zombie(Name , MaxHP , Armor , Items , weapons);    
}

vector<Character*> EnemyFactory :: FightEnemy(){
    setDifficulty((map->getFloor() - 1) * 15 + map->getCurrentNode().first);
    vector<Character*> Enemies;
    int ZorH = rand() % 3;
    if(ZorH == 2){
        if(Difficulty % 6 == 0 || Difficulty % 6 == 1)
            Enemies.push_back(HumanEnemyMaker());
        else if(Difficulty % 6 == 2 || Difficulty % 6 == 3){
            Enemies.push_back(HumanEnemyMaker());
            Enemies.push_back(HumanEnemyMaker());
        }
        else if(Difficulty % 6 == 4 || Difficulty % 6 == 5){
            Enemies.push_back(HumanEnemyMaker());
            Enemies.push_back(HumanEnemyMaker());
            Enemies.push_back(HumanEnemyMaker());
        }
    }
    else{
        if(Difficulty % 6 == 0 || Difficulty % 6 == 1)
            Enemies.push_back(ZombieMaker());
        else if(Difficulty % 6 == 2 || Difficulty % 6 == 3){
            Enemies.push_back(ZombieMaker());
            Enemies.push_back(ZombieMaker());
        }
        else if(Difficulty % 6 == 4 || Difficulty % 6 == 5){
            Enemies.push_back(ZombieMaker());
            Enemies.push_back(ZombieMaker());
            Enemies.push_back(ZombieMaker());
        }
    }
    return Enemies;
}

vector<Character*> EnemyFactory :: MiniBossEnemy(){
    setDifficulty((map->getFloor() - 1) * 15 + map->getCurrentNode().first + 21);
    vector<Character*> Enemies;
    int ZorH = rand() % 3;
    if(ZorH == 2){
        if(Difficulty % 6 == 0 || Difficulty % 6 == 1 || Difficulty % 6 == 2)
            Enemies.push_back(HumanEnemyMaker());
        else{
            Enemies.push_back(HumanEnemyMaker());
            Enemies.push_back(HumanEnemyMaker());
        }
    }
    else{
        if(Difficulty % 6 == 0 || Difficulty % 6 == 1 || Difficulty % 6 == 2)
            Enemies.push_back(ZombieMaker());
        else{
            Enemies.push_back(ZombieMaker());
            Enemies.push_back(ZombieMaker());
        }
    }
    return Enemies;
}

vector<Character*> EnemyFactory :: BossEnemy(){
    if(map->getBoss() == "Cowboy"){
        setDifficulty(28);
        vector<Character*> Enemies = {HumanEnemyMaker() , HumanEnemyMaker()};
        vector<pair<Weapon* , int>> weapons;
        vector<pair<Consumable* , int>> Consumables;
        vector<pair<Item* , int>> Items;
        weapons.push_back(make_pair(new Shotgun("doublebarrel" , 0 , 0 , 26 , 0 , 0 , 2 , 100 , 0) , 1));
        weapons.push_back(make_pair(new Shotgun("doublebarrel" , 0 , 0 , 28 , 0 , 0 , 2 , 100 , 0) , 1));
        weapons.push_back(make_pair(new Shotgun("doublebarrel" , 0 , 0 , 32 , 0 , 0 , 2 , 100 , 0) , 1));
        Consumables.push_back(make_pair(new Consumable("HP" , "HPPotion" , 0 , 0 , 95) , 3));
        Items = Itemset(weapons , Consumables);
        Enemies.push_back(new HumanEnemy("Cowboy" , 95 , 25 , Items , weapons , Consumables));
        return Enemies;
    }
    else if(map->getBoss() == "Zombie"){
        setDifficulty(32);
        vector<Character*> Enemies = {ZombieMaker() , ZombieMaker() , ZombieMaker() , ZombieMaker() , ZombieMaker()};
        return Enemies;
    }
    else if(map->getBoss() == "Samurai"){
        vector<Character*> Enemies = {};
        for(int i = 0; i < 4; i++){
            vector<pair<Weapon* , int>> weapons;
            weapons.push_back(make_pair(new ColdWeapon("Katana" , 0 , 0 , 20 , 0 , 0) , 2));
            weapons.push_back(make_pair(new ColdWeapon("Katana" , 0 , 0 , 23 , 0 , 0) , 2));
            weapons.push_back(make_pair(new ColdWeapon("Katana" , 0 , 0 , 28 , 0 , 0) , 2));
            vector<pair<Consumable* , int>> Consumables = {};
            Consumables.push_back(make_pair(new Consumable("HP" , "HPPotion" , 0 , 0 , 40) , 1));
            Consumables.push_back(make_pair(new Consumable("HP" , "HPPotion" , 0 , 0 , 35) , 1));
            Consumables.push_back(make_pair(new Consumable("HP" , "HPPotion" , 0 , 0 , 30) , 1));
            Consumables.push_back(make_pair(new Consumable("Shield" , "ShieldPotion" , 0 , 0 , 40) , 1));
            Consumables.push_back(make_pair(new Consumable("Shield" , "ShieldPotion" , 0 , 0 , 35) , 1));
            Consumables.push_back(make_pair(new Consumable("Shield" , "ShieldPotion" , 0 , 0 , 30) , 2));
            vector<pair<Item* , int>> Items = Itemset(weapons , Consumables);
            Enemies.push_back(new HumanEnemy(HumanEnemyNameset() , 145 + rand() % 16 , 40 , Items , weapons , Consumables));
        }
        return Enemies;
    }
    else if(map->getBoss() == "Frank"){
        vector<Character*> Enemies = {};
        vector<pair<Weapon* , int>> weapons;
        weapons.push_back(make_pair(new Punch("Punch" , 0 , 16 , 0 , 0) , 1));
        weapons.push_back(make_pair(new Punch("Punch" , 0 , 17 , 0 , 0) , 1));
        weapons.push_back(make_pair(new Punch("Punch" , 0 , 19 , 0 , 0) , 1));
        setDifficulty(47);
        Enemies.push_back(new Zombie("Frank" , 200 , 75 , Itemset(weapons , {}) , weapons));
        Enemies.push_back(ZombieMaker());
        Enemies.push_back(ZombieMaker());
        return Enemies;
    }
    else if(map->getBoss() == "Dokkaebi"){
        vector<Character*> Enemies;
        vector<pair<Weapon* , int>> weapons = {make_pair(new Punch("Punch" , 0 , 20 , 0 , 0) , 1)};
        Enemies.push_back(new HumanEnemy("Dokkaebi" , 60 , 25 , Itemset(weapons , {}) , weapons , {}));
        Enemies.push_back(new HumanEnemy(player->getName() , max(player->getMaxHP() + 15 , 200) , 
        max(player->getArmor() + 5 , 25) , player->getItems() , player->getWeapons() , player->getConsumables()));
        Enemies.push_back(new HumanEnemy(player->getName() , max(player->getMaxHP() + 30 , 230) , 
        max(player->getArmor() , 20 ) , player->getItems() , player->getWeapons() , player->getConsumables()));
        return Enemies;
    }
    else if(map->getBoss() == "Khonshu"){
        setDifficulty(60);
        vector<Character*> Enemies = {ZombieMaker() , ZombieMaker()};
        vector<pair<Weapon* , int>> weapons;
        weapons.push_back(make_pair(new Grenade("Grenade" , 0 , 0 , 35 , 0 , 0) , 5));
        weapons.push_back(make_pair(new Grenade("Grenade" , 0 , 0 , 30 , 0 , 0) , 15));
        weapons.push_back(make_pair(new Grenade("Grenade" , 0 , 0 , 38 , 0 , 0) , 5));
        weapons.push_back(make_pair(new BoomRang("BoomRang" , 0 , 0 , 17 , 0 , 0) , 5));
        weapons.push_back(make_pair(new BoomRang("BoomRang" , 0 , 0 , 15 , 0 , 0) , 15));
        weapons.push_back(make_pair(new BoomRang("BoomRang" , 0 , 0 , 18 , 0 , 0) , 5));
        vector<pair<Consumable* , int>> Consumables;
        Consumables.push_back(make_pair(new Consumable("HP" , "HPPotion" , 0 , 0 , 20) , 15));
        Enemies.push_back(new HumanEnemy("Khonshu" , 250 , 47.5 , Itemset(weapons , Consumables) , weapons , Consumables));
        return Enemies;
    }
}

string MapFactory :: BossName(){
    if(Floor == 1){
        int random = rand() % 2;
        switch (random)
        {
        case 0:
            return "Cowboy"; // complete later
            break;
        default:
            return "Zombie"; // complete later
            break;
        }
    }
    if(Floor == 2){
        int random = rand() % 2;
        switch (random)
        {
        case 0:
            return "Samurai"; // complete later
            break;
        default:
            return "Frank"; // complete later
            break;
        }
    }
    if(Floor == 3){
        int random = rand() % 2;
        switch (random)
        {
        case 0:
            return "Dokkaebi"; // complete later
            break;
        default:
            return "Khonshu"; // complete later
            break;
        }
    }
}

vector<int> MapFactory :: PathFinding1(){
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    path[0]=rand() %6;
    for(int i=1;i<15;i++){
        if(path[i-1]==0){
            vector<int> nexthome={path[i-1],path[i-1]+1};
            random_device rd;
            default_random_engine abs(rd());
            shuffle(nexthome.begin(), nexthome.end(), abs);
            path[i]=nexthome[0];
        }
        else if(path[i-1]==5){
            vector<int> nexthome={path[i-1],path[i-1]-1};
            random_device rd;
            default_random_engine abs(rd());
            shuffle(nexthome.begin(), nexthome.end(), abs);
            path[i]=nexthome[0];
        }
        else{
            vector<int> nexthome={path[i-1],path[i-1]+1,path[i-1]-1};
            random_device rd;
            default_random_engine abs(rd());
            shuffle(nexthome.begin(), nexthome.end(), abs);
            path[i]=nexthome[0];
        }
    }
    return path;
}

vector<int> MapFactory :: PathFinding2(vector<int> path1){
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    do{
        path[0]=rand() %6;
    }while(path[0]==path1[0]);
    for(int i=1;i<15;i++){
        if(path[i-1]==0){
            if((path1[i-1]==1)&&(path1[i]==0)){
                path[i]=0;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else if(path[i-1]==5){
            if((path1[i-1]==4)&&(path1[i]==5)){
                path[i]=5;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else{
            if((path1[i-1]==path[i-1]+1)&&(path1[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else if((path1[i-1]==path[i-1]-1)&&(path1[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]+1,path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
    }
    return path;
}

vector<int> MapFactory :: PathFinding3(vector<int> path1,vector<int> path2){
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    do{
        path[0]=rand() %6;
    }while(path[0]==path1[0] || path[0]==path2[0]);
    for(int i=1;i<15;i++){
        if(path[i-1]==0){
            if((path1[i-1]==1&& path1[i]==0)||(path2[i-1]==1&&path2[i]==0)){
                path[i]=0;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else if(path[i-1]==5){
            if((path1[i-1]==4 && path1[i]==5)||(path2[i-1]==4 &&path2[i]==5)){
                path[i]=5;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else{
            if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1] && path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])){
                path[i]==path[i-1];
            }
            else if((path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            ||(path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else if((path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            || (path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else{
                vector<int> nexthome={ path[i-1], path[i-1]+1, path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
    }
    return path;
}

vector<int> MapFactory :: PathFinding4(vector<int> path1,vector<int> path2,vector<int>path3){
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    path[0]=rand() %6;
    for(int i=1; i<15 ;i++){
        if(path[i-1]==0){
            if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            || (path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])){
                path[i]=0;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else if(path[i-1]==5){
            if((path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            || (path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])){
                path[i]=5;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else{
            if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            ||(path2[i-1]==path[i-1]-1 && path2[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path2[i-1]==path[i-1]+1 && path2[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])){
                path[i]=path[i-1];
            }
            else if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1]) 
            || (path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else if((path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]-1 && path2[i]==path[i-1]) 
            || (path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1,path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
    }
    return path;
}

vector<int> MapFactory :: PathFinding5(vector<int> path1,vector<int> path2,vector<int>path3 , vector<int> path4){
    vector<int> path={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    path[0]=rand() %6;
    for(int i=1; i<15 ;i++){
        if(path[i-1]==0){
            if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            || (path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            || (path4[i-1]==path[i-1]+1 && path4[i]==path[i-1])){
                path[i]=0;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else if(path[i-1]==5){
            if((path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            || (path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            || (path4[i-1]==path[i-1]-1 && path4[i]==path[i-1])){
                path[i]=5;
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
        else{
            if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path2[i-1]==path[i-1]-1 && path2[i]==path[i-1])
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path2[i-1]==path[i-1]+1 && path2[i]==path[i-1])
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            ||(path2[i-1]==path[i-1]-1 && path2[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path2[i-1]==path[i-1]+1 && path2[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            ||(path1[i-1]==path[i-1]-1 && path1[i]==path[i-1] && path4[i-1]==path[i-1]+1 && path4[i]==path[i-1])
            ||(path1[i-1]==path[i-1]+1 && path1[i]==path[i-1] && path4[i-1]==path[i-1]-1 && path4[i]==path[i-1])
            ||(path2[i-1]==path[i-1]-1 && path2[i]==path[i-1] && path4[i-1]==path[i-1]+1 && path4[i]==path[i-1])
            ||(path2[i-1]==path[i-1]+1 && path2[i]==path[i-1] && path4[i-1]==path[i-1]-1 && path4[i]==path[i-1])
            ||(path4[i-1]==path[i-1]-1 && path4[i]==path[i-1] && path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            ||(path4[i-1]==path[i-1]+1 && path4[i]==path[i-1] && path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])){
                path[i]=path[i-1];
            }
            else if((path1[i-1]==path[i-1]+1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]+1 && path2[i]==path[i-1]) 
            || (path3[i-1]==path[i-1]+1 && path3[i]==path[i-1])
            || (path4[i-1]==path[i-1]+1 && path4[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]-1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else if((path1[i-1]==path[i-1]-1 && path1[i]==path[i-1])
            || (path2[i-1]==path[i-1]-1 && path2[i]==path[i-1]) 
            || (path3[i-1]==path[i-1]-1 && path3[i]==path[i-1])
            || (path4[i-1]==path[i-1]-1 && path4[i]==path[i-1])){
                vector<int> nexthome={path[i-1],path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
            else{
                vector<int> nexthome={path[i-1],path[i-1]-1,path[i-1]+1};
                random_device rd;
                default_random_engine abs(rd());
                shuffle(nexthome.begin(), nexthome.end(), abs);
                path[i]=nexthome[0];
            }
        }
    }
    return path;
}

vector<vector<string>> MapFactory :: generateEncounters(vector<int> path1 , vector<int> path2 , vector<int> path3 , 
vector<int> path4 , vector<int> path5){
    vector<vector<string>> Encounters = {};
    vector<vector<int>> VisitedNodes = {};
    for(int i = 0; i < 15; i++){
        VisitedNodes.push_back({});
        VisitedNodes[i].push_back(path1[i]);
        if(path2[i] != path1[i])
            VisitedNodes[i].push_back(path2[i]);
        if(path3[i] != path1[i] && path2[i] != path3[i])
            VisitedNodes[i].push_back(path3[i]);
        if(path4[i] != path3[i] && path4[i] != path1[i] && path2[i] != path4[i])
            VisitedNodes[i].push_back(path4[i]);
        if(path5[i] != path3[i] && path5[i] != path1[i] && path2[i] != path5[i] && path5[i] != path4[i])
            VisitedNodes[i].push_back(path5[i]);
    }
    for(int i = 0; i < 15 ; i++){
        Encounters.push_back({});
        for(int j = 0; j < 6; j++){
            Encounters[i].push_back("");
        }
        if(i == 0){
            for(int j = 0; j < VisitedNodes[0].size();j++){
                Encounters[i][VisitedNodes[0][j]] = "Fight"; // Encounter generation to be included
            }
        }
        else if(i < 5){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {40 , 25 , 9};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                if(path5[i] == VisitedNodes[i][j])
                    Visits.push_back(path5[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(path5[i - 1] == Visits[m] && path5[i] != VisitedNodes[i][j])
                        inRow.push_back(path5[i]);
                    if(Encounters[i - 1][Visits[m]] == "Shop")
                        weights[2] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(Encounters[i][inRow[m]] == "Fight")
                        weights[0] = 0;
                    else if(Encounters[i][inRow[m]] == "Random")
                        weights[1] = 0;
                    else if(Encounters[i][inRow[m]] == "Shop")
                        weights[2] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] = "Fight"; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] = "Random"; //Random Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] = "Shop"; //Shop Constructor to be included
                }
            }
        }
        else if(i < 13){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {40 , 25 , 16 , 10 , 9};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                if(path5[i] == VisitedNodes[i][j])
                    Visits.push_back(path5[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(path5[i - 1] == Visits[m] && path5[i] != VisitedNodes[i][j])
                        inRow.push_back(path5[i]);
                    if(Encounters[i - 1][Visits[m]] == "MiniBoss")
                        weights[2] = 0;
                    else if(Encounters[i - 1][Visits[m]] == "Hospital")
                        weights[3] = 0;
                    else if(Encounters[i - 1][Visits[m]] == "Shop")
                        weights[4] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(Encounters[i][inRow[m]] == "Fight")
                        weights[0] = 0;
                    else if(Encounters[i][inRow[m]] == "Random")
                        weights[1] = 0;
                    else if(Encounters[i][inRow[m]] == "MiniBoss")
                        weights[2] = 0;
                    else if(Encounters[i][inRow[m]] == "Hospital")
                        weights[3] = 0;
                    else if(Encounters[i][inRow[m]] == "Shop")
                        weights[4] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] =  "Fight"; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] =  "Random"; //Random Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] =  "MiniBoss"; //MiniBoss Constructor to be included
                }
                if(enc == 3){
                    Encounters[i][VisitedNodes[i][j]] =  "Hospital"; //Hospital Constructor to be included
                }
                if(enc == 4){
                    Encounters[i][VisitedNodes[i][j]] =  "Shop"; //Shop Constructor to be included
                }
            }
        }
        else if(i == 13){
            for(int j = 0; j < VisitedNodes[i].size();j++){
                vector<int> Visits , inRow , weights = {40 , 25 , 16 , 9};
                if(path1[i] == VisitedNodes[i][j])
                    Visits.push_back(path1[i-1]);
                if(path2[i] == VisitedNodes[i][j])
                    Visits.push_back(path2[i-1]);
                if(path3[i] == VisitedNodes[i][j])
                    Visits.push_back(path3[i-1]);
                if(path4[i] == VisitedNodes[i][j])
                    Visits.push_back(path4[i-1]);
                if(path5[i] == VisitedNodes[i][j])
                    Visits.push_back(path5[i-1]);
                for(int m = 0; m < Visits.size(); m++){
                    if(path1[i - 1] == Visits[m] && path1[i] != VisitedNodes[i][j])
                        inRow.push_back(path1[i]);
                    if(path2[i - 1] == Visits[m] && path2[i] != VisitedNodes[i][j])
                        inRow.push_back(path2[i]);
                    if(path3[i - 1] == Visits[m] && path3[i] != VisitedNodes[i][j])
                        inRow.push_back(path3[i]);
                    if(path4[i - 1] == Visits[m] && path4[i] != VisitedNodes[i][j])
                        inRow.push_back(path4[i]);
                    if(path5[i - 1] == Visits[m] && path5[i] != VisitedNodes[i][j])
                        inRow.push_back(path5[i]);
                    if(Encounters[i - 1][Visits[m]] == "MiniBoss")
                        weights[2] = 0;
                    else if(Encounters[i - 1][Visits[m]] == "Shop")
                        weights[3] = 0;
                }
                for(int m = 0; m < inRow.size(); m++){
                    if(Encounters[i][inRow[m]] == "Fight")
                        weights[0] = 0;
                    else if(Encounters[i][inRow[m]] == "Random")
                        weights[1] = 0;
                    else if(Encounters[i - 1][inRow[m]] == "MiniBoss")
                        weights[2] = 0;
                    else if(Encounters[i][inRow[m]] == "Shop")
                        weights[3] = 0;
                }
                int enc = Index_Weighted_Random(weights);
                if(enc == 0){
                    Encounters[i][VisitedNodes[i][j]] = "Fight"; //Fight Constructor to be included
                }
                if(enc == 1){
                    Encounters[i][VisitedNodes[i][j]] = "Random"; //Random Constructor to be included
                }
                if(enc == 2){
                    Encounters[i][VisitedNodes[i][j]] = "MiniBoss"; //MiniBoss Constructor to be included
                }
                if(enc == 3){
                    Encounters[i][VisitedNodes[i][j]] = "Shop"; //Hospital Constructor to be included
                }
            }
        }
        else{
            for(int j = 0; j < VisitedNodes[i].size(); j++){
                Encounters[i][VisitedNodes[i][j]] = "Hospital"; // Hospital Constructor to be included
            }
        }
    }
    return Encounters;
}

MapFactory :: MapFactory(int floor){this -> Floor = floor;}

Map* MapFactory :: GenerateMap(){
    vector<int> path1 , path2 , path3 , path4 , path5;
    vector<vector<string>> GenerateEncounters;
    string BOSS = BossName();
    path1 = PathFinding1();
    path2 = PathFinding2(path1);
    path3 = PathFinding3(path1 , path2);
    path4 = PathFinding4(path1 , path2 , path3);
    path5 = PathFinding5(path1 , path2 , path3 , path4);
    GenerateEncounters = generateEncounters(path1 , path2 , path3 , path4 , path5);
    Map* map = new Map(Floor , BOSS , path1 , path2 , path3 , path4 , path5 , GenerateEncounters);
    return map;
}


FightFactory :: FightFactory(Player* player, Map* map){
    this -> player = player;
    this -> map = map;
}

Fight* FightFactory :: GenerateNormalFight(){

    vector<Item*> AllItems = {shotgun, shotgun2, shotgun3, snipe, snipe2, snipe3, smg, smg2, smg3, rifle, rifle2, rifle3, 
    coldweapon, coldweapon2, coldweapon3, grenade, grenade2, grenade3, boomerang, boomerang2, boomerang3, ShieldConsumable, 
    ShieldConsumable2, ShieldConsumable3, HPConsumable, HPConsumable2, HPConsumable3, EnergyConsumable, EnergyConsumable2, vest, vest2, 
    vest3, headgear, headgear2, headgear3, footwear, footwear2, footwear3, boot, boot2, boot3};

    vector<Item*> Items;

    vector<int> weights = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0};
    switch (map->getFloor())
    {
    case 1:
        weights = {6,2,1, 6,2,1, 5,2,1, 5,1,1, 5,2,1, 5,2,1, 8,3,1, 10,5,3, 12,7,3, 7,3, 5,2,1, 6,2,1, 6,2,1, 5,2,1};
        break;

    case 2:
        weights = {2,6,1, 2,6,1, 2,5,1, 1,5,1, 2,5,1, 2,5,1, 3,8,1, 5,10,3, 7,12,3, 5,5, 2,5,1, 2,6,1, 2,6,1, 2,5,1};
        break;
    case 3:
        weights = {1,2,6, 1,2,6, 1,2,5, 1,1,5, 1,2,5, 1,2,5, 1,3,8, 3,5,10, 3,7,12, 3,7, 1,2,5, 1,2,6, 1,2,6, 1,2,5};
    default:
        break;

    }
    int item_index;
    for (int i = 0; i < 5; i++)
    {
        item_index = Index_Weighted_Random(weights);
        Items[i] = AllItems[item_index];
    }

    vector<Relic*> relics = {relic, relic2, relic3, relic4, relic5, relic6, relic7, relic8, relic9};
    relics = ShuffleVec(relics);

    bool isExisted = false;
    int m = 0;
    while (m != 3)
    {
        item_index = rand() % relics.size();
        for (int j = 0; j < player->getRelic().size(); j++)
        {
            if (relics[item_index] == player->getRelic()[j])
            {
                isExisted = true;
            }   
        }
        if (!(isExisted))
        {
            relics[m] == relics[item_index];
            m++;
        }
    }
    while (relics.size() != 3)
    {
        relics.pop_back();
    }

    EnemyFactory* enemyfactory = new EnemyFactory(map , player);
    vector<Character*> Enemies = enemyfactory->FightEnemy();
    Fight* fight = new Fight(player, 0, Enemies, Items);
    return fight;
}

Fight* FightFactory :: GenerateMiniBoss(){

    vector<Item*> AllItems = {shotgun, shotgun2, shotgun3, snipe, snipe2, snipe3, smg, smg2, smg3, rifle, rifle2, rifle3, 
    coldweapon, coldweapon2, coldweapon3, grenade, grenade2, grenade3, boomerang, boomerang2, boomerang3, ShieldConsumable, 
    ShieldConsumable2, ShieldConsumable3, HPConsumable, HPConsumable2, HPConsumable3, EnergyConsumable, EnergyConsumable2, vest, vest2, 
    vest3, headgear, headgear2, headgear3, footwear, footwear2, footwear3, boot, boot2, boot3};

    vector<Item*> Items;

    vector<int> weights = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0};
    switch (map->getFloor())
    {
    case 1:
        weights = {6,2,1, 6,2,1, 5,2,1, 5,1,1, 5,2,1, 5,2,1, 8,3,1, 10,5,3, 12,7,3, 7,3, 5,2,1, 6,2,1, 6,2,1, 5,2,1};
        break;

    case 2:
        weights = {2,6,1, 2,6,1, 2,5,1, 1,5,1, 2,5,1, 2,5,1, 3,8,1, 5,10,3, 7,12,3, 5,5, 2,5,1, 2,6,1, 2,6,1, 2,5,1};
        break;
    case 3:
        weights = {1,2,6, 1,2,6, 1,2,5, 1,1,5, 1,2,5, 1,2,5, 1,3,8, 3,5,10, 3,7,12, 3,7, 1,2,5, 1,2,6, 1,2,6, 1,2,5};
    default:
        break;

    }
    int item_index;
    for (int i = 0; i < 7; i++)
    {
        item_index = Index_Weighted_Random(weights);
        Items[i] = AllItems[item_index];
    }

    vector<Relic*> relics = {relic, relic2, relic3, relic4, relic5, relic6, relic7, relic8, relic9};
    relics = ShuffleVec(relics);

    bool isExisted = false;
    int m = 0;
    while (m != 3)
    {
        item_index = rand() % relics.size();
        for (int j = 0; j < player->getRelic().size(); j++)
        {
            if (relics[item_index] == player->getRelic()[j])
            {
                isExisted = true;
            }   
        }
        if (!(isExisted))
        {
            relics[m] == relics[item_index];
            m++;
        }
    }
    while (relics.size() != 3)
    {
        relics.pop_back();
    }

    EnemyFactory* enemyfactory = new EnemyFactory(map , player);
    vector<Character*> Enemies = enemyfactory->MiniBossEnemy();
    Fight* fight = new Fight(player, 1, Enemies, Items);
    return fight;
}

Fight* FightFactory :: GenerateBoss(){

    vector<Item*> AllItems = {shotgun, shotgun2, shotgun3, snipe, snipe2, snipe3, smg, smg2, smg3, rifle, rifle2, rifle3, 
    coldweapon, coldweapon2, coldweapon3, grenade, grenade2, grenade3, boomerang, boomerang2, boomerang3, ShieldConsumable, 
    ShieldConsumable2, ShieldConsumable3, HPConsumable, HPConsumable2, HPConsumable3, EnergyConsumable, EnergyConsumable2, vest, vest2, 
    vest3, headgear, headgear2, headgear3, footwear, footwear2, footwear3, boot, boot2, boot3};

    vector<Item*> Items;

    vector<int> weights = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0};
    switch (map->getFloor())
    {
    case 1:
        weights = {6,2,1, 6,2,1, 5,2,1, 5,1,1, 5,2,1, 5,2,1, 8,3,1, 10,5,3, 12,7,3, 7,3, 5,2,1, 6,2,1, 6,2,1, 5,2,1};
        break;

    case 2:
        weights = {2,6,1, 2,6,1, 2,5,1, 1,5,1, 2,5,1, 2,5,1, 3,8,1, 5,10,3, 7,12,3, 5,5, 2,5,1, 2,6,1, 2,6,1, 2,5,1};
        break;
    case 3:
        weights = {1,2,6, 1,2,6, 1,2,5, 1,1,5, 1,2,5, 1,2,5, 1,3,8, 3,5,10, 3,7,12, 3,7, 1,2,5, 1,2,6, 1,2,6, 1,2,5};
    default:
        break;

    }
    int item_index;
    for (int i = 0; i < 8; i++)
    {
        item_index = Index_Weighted_Random(weights);
        Items[i] = AllItems[item_index];
    }
    
    vector<Relic*> relics = {relic, relic2, relic3, relic4, relic5, relic6, relic7, relic8, relic9};
    relics = ShuffleVec(relics);

    bool isExisted = false;
    int m = 0;
    while (m != 3)
    {
        item_index = rand() % relics.size();
        for (int j = 0; j < player->getRelic().size(); j++)
        {
            if (relics[item_index] == player->getRelic()[j])
            {
                isExisted = true;
            }   
        }
        if (!(isExisted))
        {
            relics[m] == relics[item_index];
            m++;
        }
    }
    while (relics.size() != 3)
    {
        relics.pop_back();
    }
    
    EnemyFactory* enemyfactory = new EnemyFactory(map , player);
    vector<Character*> Enemies = enemyfactory->BossEnemy();
    Fight* fight = new Fight(player, 2, Enemies, Items);
    return fight;
}

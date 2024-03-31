#include "../Headers/factory.h"
#include <random>
#include<algorithm>

using namespace std;

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

void ShopFactory :: Generate(Shop* shop){
    // Guns 
    Shotgun* shotgun = new Shotgun("shotgun", 19, 25, 25, 1, 2, 3, 25, 3);
    Shotgun* shotgun2 = new Shotgun("shotgun2", 19, 30, 30, 1, 2, 5, 27, 3);
    Shotgun* shotgun3 = new Shotgun("shotgun3", 19, 35, 35, 1, 2, 4, 28, 3); // A better shotgun

    Snipe* snipe = new Snipe("snipe", 23, 20, 21, 1, 2, 4, 3);
    Snipe* snipe2 = new Snipe("snipe2", 23, 20, 20, 1, 2, 5, 3);
    Snipe* snipe3 = new Snipe("snipe3", 23, 25, 23, 1, 2, 6, 3); // A better sniper

    SMG* smg = new SMG("smg", 15, 18, 18, 1, 2, 3, 2);
    SMG* smg2 = new SMG("smg2", 15, 19, 18, 1, 2, 4, 2);
    SMG* smg3 = new SMG("smg3", 15, 22, 19, 1, 2, 5, 3); // A better SMG

    Rifle* rifle = new Rifle("rifle", 20, 24, 25, 2, 2, 3, 1, 2);
    Rifle* rifle2 = new Rifle("rifle2", 20, 27, 27, 2, 2, 4, 2, 2);
    Rifle* rifle3 = new Rifle("rifle3", 20, 30, 28, 2, 2, 4, 3, 3); // A better rifle

    // Cold Weapons
    ColdWeapon* coldweapon = new ColdWeapon("coldweapon", 10, 15, 15, 1, 1);
    ColdWeapon* coldweapon2 = new ColdWeapon("coldweapon2", 10, 15, 17, 1, 2);
    ColdWeapon* coldweapon3 = new ColdWeapon("coldweapon3", 10, 18, 20, 1, 3); // Better

    // Throwables
    Grenade* grenade = new Grenade("grenade", 7, 16, 17, 1, 1);
    Grenade* grenade2 = new Grenade("grenade2", 7, 18, 18, 1, 2);
    Grenade* grenade3 = new Grenade("grenade3", 7, 20, 20, 1, 3); // Better

    BoomRang* boomerang = new BoomRang("boomerang", 15, 16, 10, 1, 2);
    BoomRang* boomerang2 = new BoomRang("boomerang2", 15, 17, 11, 1, 2);
    BoomRang* boomerang3 = new BoomRang("boomerabg3", 15, 18, 13, 1, 2); // Better

    // Consumables
    Consumable* ShieldConsumable = new Consumable("ShieldConsumable", "ShieldPotion", 7, 25, 10);
    Consumable* ShieldConsumable2 = new Consumable("ShieldConsumable2", "ShieldPotion", 7, 30, 12);
    Consumable* ShieldConsumable3 = new Consumable("ShieldConsumable3", "ShieldPotion", 7, 35, 14);

    Consumable* HPConsumable = new Consumable("HPConsumable", "HPPotion", 8, 20, 6);
    Consumable* HPConsumable2 = new Consumable("HPConsumable2", "HPPotion", 8, 25, 7);
    Consumable* HPConsumable3 = new Consumable("HPConsumable3", "HPPotion", 8, 30, 8);

    Consumable* EnergyConsumable = new Consumable("EnergyConsumable", "EnergyPotion", 7, 30, 4);
    Consumable* EnergyConsumable2 = new Consumable("EnergyConsumable2", "EnergyPotion", 7, 35, 5);
    Consumable* EnergyConsumable3 = new Consumable("EnergyConsumable3", "EnergyPotion", 7, 40, 6);

    // Equipments
    Vest* vest = new Vest("vest", 0, 40, 15);
    Vest* vest2 = new Vest("vest2", 0, 45, 17);
    Vest* vest3 = new Vest("vest3", 0, 50, 19);

    HeadGear* headgear = new HeadGear("headgear", 0, 35, 10);
    HeadGear* headgear2 = new HeadGear("headgear2", 0, 40, 13);
    HeadGear* headgear3 = new HeadGear("headgear3", 0, 45, 16); 

    FootWear* footwear = new FootWear("footwear", 0, 30, 7);
    FootWear* footwear2 = new FootWear("footwear2", 0, 35, 10);
    FootWear* footwear3 = new FootWear("footwear3", 0, 40, 13);

    Boot* boot = new Boot("boot", 0, 34, 5);
    Boot* boot2 = new Boot("boot2", 0, 36, 8);
    Boot* boot3 = new Boot("boot3", 0, 38, 11);

    vector<Weapon*> AllWeapons = {shotgun, shotgun2, shotgun3, snipe, snipe2, snipe3, smg, smg2, smg3, rifle, rifle2, rifle3, 
    coldweapon, coldweapon2, coldweapon3, grenade, grenade2, grenade3, boomerang, boomerang2, boomerang3};

    vector<Consumable*> AllConsumables ={ShieldConsumable, ShieldConsumable2, ShieldConsumable3, HPConsumable, HPConsumable2, 
    HPConsumable3, EnergyConsumable, EnergyConsumable2, EnergyConsumable3};

    vector<Equipment*> AllEquipments = {vest, vest2, vest3, headgear, headgear2, headgear3, footwear, footwear2, footwear3, boot, 
    boot2, boot3};

    vector<Weapon*> Weapons;
    vector<Consumable*> Consumables;
    vector<Equipment*> Equipments;

    int item_index;
    
    if (map->getFloor() == 1)
    {
        item_index = Index_Weighted_Random({3,2,1,3,2,1,3,2,1,3,2,1,3,2,1,3,2,1,3,2,1});
        for (int i = 0; i < 7; i++)
        {
            Weapons[i] = AllWeapons[item_index];
        }
        item_index = Index_Weighted_Random({3,2,1,3,2,1,3,2,1});
        for (int i = 0; i < 3; i++)
        {
            Consumables[i] = AllConsumables[i];
        }
        item_index = Index_Weighted_Random({3,2,1,3,2,1,3,2,1,3,2,1});
        for (int i = 0; i < 2; i++)
        {
            Equipments[i] = AllEquipments[item_index];
        }
    }
    else if (map->getFloor() == 2)
    {
        item_index = Index_Weighted_Random({2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1});
        for (int i = 0; i < 7; i++)
        {
            Weapons[i] = AllWeapons[item_index];
        }
        item_index = Index_Weighted_Random({2,3,1,2,3,1,2,3,1});
        for (int i = 0; i < 3; i++)
        {
            Consumables[i] = AllConsumables[i];
        }
        item_index = Index_Weighted_Random({2,3,1,2,3,1,2,3,1,2,3,1});
        for (int i = 0; i < 2; i++)
        {
            Equipments[i] = AllEquipments[item_index];
        }
    }
    else if (map->getFloor() == 3)
    {
        item_index = Index_Weighted_Random({1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3});
        for (int i = 0; i < 7; i++)
        {
            Weapons[i] = AllWeapons[item_index];
        }
        item_index = Index_Weighted_Random({1,2,3,1,2,3,1,2,3});
        for (int i = 0; i < 3; i++)
        {
            Consumables[i] = AllConsumables[i];
        }
        item_index = Index_Weighted_Random({1,2,3,1,2,3,1,2,3});
        for (int i = 0; i < 2; i++)
        {
            Equipments[i] = AllEquipments[item_index];
        }
    }

    shop->setWeapons(Weapons);
    shop->setConsumables(Consumables);
    shop->setEquipments(Equipments);

     
}

EnemyFactory :: EnemyFactory(Map* map){this -> map = map;}

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
        AllWeapons.push_back(make_pair(new ColdWeapon("Sword" , 0 , 0 , 
        ceil(4 + 2 * pow(1.1 , Difficulty/3 + Index_Weighted_Random(weights))) , 0 , 0) , Index_Weighted_Random(weights) + 1));
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
    if(type == 1){}
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
    path1 = PathFinding1();
    path2 = PathFinding2(path1);
    path3 = PathFinding3(path1 , path2);
    path4 = PathFinding4(path1 , path2 , path3);
    path5 = PathFinding5(path1 , path2 , path3 , path4);
    GenerateEncounters = generateEncounters(path1 , path2 , path3 , path4 , path5);
    Map* map = new Map(Floor , path1 , path2 , path3 , path4 , path5 , GenerateEncounters);
    return map;
}
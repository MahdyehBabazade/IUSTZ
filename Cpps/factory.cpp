#include "../Headers/factory.h"
#include <random>

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
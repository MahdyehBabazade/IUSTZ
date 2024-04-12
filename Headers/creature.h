#pragma once
#include "../Headers/items.h"
#include "../Headers/MVC.h"
#include <vector>
#include <string>
using namespace std;
namespace Control{
    class FightControl;
}

// explainings to be included
class Character{
private:
    string Name;
    int HP;
    int MaxHP;
    double Armor;
    int Shield;
protected:
    vector<pair<Item* , int>> Items;
    vector<pair<Weapon* , int>> Weapons;
    vector<Equipment*> Equipments;
public:
    
    // Constructor
    Character(string Name , int MaxHP , vector<pair<Item* , int>> Items ,
    vector<pair<Weapon*,int>> Weapons);
    
    // getters
    string getName();
    int getHP();
    int getMaxHP();
    double getArmor();
    int getShield();
    vector<pair<Item* , int>> getItems(); 
    vector<pair<Weapon* , int>> getWeapons();
    vector<Equipment*> getEquipments();
    
    // setters
    void setName(string Name);
    void setHP(int HP);
    void setMaxHP(int MaxHP);
    void setArmor(double Armor);
    void setShield(int Shield);

    void takeDamage(int damageTaken); // Reduces the hp of characters based on their Armor and Shield
    void death(); // Character dies

    string getStat(); // To be deleted later
    virtual string DeathDialogue();
    
};

class Player : public Character{

private:
    int BackPackCapacity;
    int BackPackWeight;
    int Energy;
    int MaxEnergy;
    int Coin;
    vector<Relic*> Relics;
    vector<pair<Consumable* , int>> Consumables;
    
    // Updates the list of specific types of Items based on what item is picked in a sorted manner
    void addWeapon(Weapon* Weapon);
    void removeWeapon(Weapon* Weapon);
    void addEquipment(Equipment* Equipment);
    void removeEquipment(Equipment* Equipment);
    void addConsumable(Consumable* Consumable);
    void removeConsumable(Consumable* Consumable);

public:
    // Constructor and Destructor
    Player(string Name, int MaxHP, int BackPackCapacity , int BackPackWeight , int MaxEnergy
    , int Coin , vector<pair<Item* , int>> Items , vector<pair<Weapon* , int>> Weapons); // Equipments to be included
    ~Player();

    // getters
    int getBackPackCapacity();
    int getBackPackWeight();
    int getEnergy();
    int getMaxEnergy();
    int getCoin();
    vector<Relic*> getRelic();
    vector<pair<Consumable* , int>> getConsumables();
    
    // setters
    void setBackPackCapacity(int BackPackCapacity);
    void setBackPackWeight(int BackPackWeight);
    void setEnergy(int Energy);
    void setMaxEnergy(int MaxEnergy);

    // Updates the amount of Coins the player has
    void addCoin(int CoinToBeAdded);
    void removeCoin(int CoinToBeAdded);

    // Updates the list of Relics and their Aplications
    void addRelic(Relic* relic);

    // Updates the list of Items in a sorted manner
    void addItem(Item* item);
    void removeItem(Item* item);

    void Consume(Consumable* Consumable); // the function for when a Consumable is used
    Weapon* ChooseWeapon(); // to be deleted later (?)
    void Attack(vector<Character*> &characters , Weapon* weapon , int choice); // Attack function
};


enum State{
        Heal,
        Shield,
        Attack,
        Reload,
        GunAttack,
        NoneGunAttack,
};
class HumanEnemy: public Character{
private:
    vector<pair<Consumable* , int>> Consumables;
    vector<pair<Gun*,int>> Guns;
    vector<pair<Weapon*,int>> noneGuns;
    
    // Updates the list of Specific types of Items after they are thrown or used
    void removeConsumable(Consumable* Consumable);
    void removeWeapon(Weapon* Weapon);
    
    
    State state;

public:
    
    // Constructor and Destructor
    HumanEnemy(string Name , int MaxHP , double Armor, vector<pair<Item* , int>> Items ,
    vector<pair<Weapon* , int>> Weapons , vector<pair<Consumable* , int>> Consumables); //items to add?!
    
    //~HumanEnemy();
    string DeathDialogue() override;
    
    // fun little Dialogues :)
    string RajazKhani();
    
    void StateMachine(Player* player,Control::FightControl* fightControl);
    void Attack(Player* player , Weapon* weapon , int choice); // Attack function
    void Consume(Consumable* consumable); // When a Consumable is used
    void removeItem(Item* item); // when a throwable is thrown or a Consumable is used;
};

class Zombie: public Character{

public:
    // Constructor and Destructor
    Zombie(string Name , int MaxHP , double Armor, vector<pair<Item* , int>> Items , 
    vector<pair<Weapon* , int>> Weapons);
    //~Zombie();
    string DeathDialogue() override;

    void Attack(Player* player,Control::FightControl* fightControl); // Attack function for zombie it can only attack with its Punch
};

class Shopkeeper{

private:
    string Name;

public:
    // Constructor
    Shopkeeper(string Name);

    string getName();
    // Dialogues
    string HiDialogue();
    string ByeDialogue();
    string SellDialogue(Item* item);
    string BuyDialogue(Item* item);
    string NoMoneyDialogue();
    string UpgradeLimitDialogue(Weapon* weapon);
    string UpgradeLimitDialogue();
};

class Medic{

private:
    string Name;
public:
    // Constructor
    Medic(string Name);

    string getName();
    // Dialogues
    string HiDialogue();
    string HealDialogue();
    string ByeDialogue();
    string NoMoneyDialogue();
};
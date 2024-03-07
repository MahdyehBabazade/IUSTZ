#include "../Headers/creature.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

Player :: Player(string Name, int HP, int MaxHP, double Armor, int BackPackCapacity , int Energy , int Coin){
    this -> Name = Name;
    this -> HP = HP;
    this -> MaxHP = MaxHP;
    this -> Armor = Armor;
    this -> BackPackCapacity = BackPackCapacity;
    this -> Energy = Energy;
    this -> Coin = Coin;
} // items to be included

Player :: ~Player(){
    cout << "Not good enough" << endl << "Defeated!!!" << endl << "Welcome to hellmos";
}

// void Player :: Attack(Enemy* enemy){} // to be filled

void Player :: takeDamage(int damagetaken){setHP(getHP() - damagetaken * (100 - Armor) / 100);}

void Player :: setHP(int HP){this -> HP = HP;}

int Player :: getHP(){return HP;}

void Player :: setMaxHP(int MaxHP){this -> MaxHP = MaxHP;}

int Player :: getMaxHP(){return MaxHP;}

void Player :: setArmor(double Armor){this -> Armor = Armor;}

int Player :: getArmor(){return Armor;}

void Player :: setBackPackCapacity(int BackPackCapacity){this -> BackPackCapacity = BackPackCapacity;}

int Player :: getBackPackCapacity(){return BackPackCapacity;}

void Player :: setEnergy(int Energy){this -> Energy = Energy;}

int Player :: getEnergy(){return Energy;}

void Player :: addCoin(int CoinToBeAdded){this -> Coin += CoinToBeAdded;}

void Player :: removeCoin(int CoinToBeRemoved){this -> Coin -= CoinToBeRemoved;}

int Player :: getCoin(){return Coin;}

Enemy :: Enemy(int HP , int MaxHP , double Armor){
    this->HP = HP;
    this->MaxHP = MaxHP;
    this->Armor = Armor; 
}
void Enemy :: takeDamage(int damagetaken){setHP(getHP() - damagetaken * (100 - Armor) / 100);}

void Enemy :: setHP(int HP){this -> HP = HP;}

int Enemy :: getHP(){return HP;}

void Enemy :: setMaxHP(int MaxHP){this -> MaxHP = MaxHP;}

int Enemy :: getMaxHP(){return MaxHP;}

void Enemy :: setArmor(double Armor){this -> Armor = Armor;}

int Enemy :: getArmor(){return Armor;}

string HumanEnemy :: getName(){return Name;}

HumanEnemy :: HumanEnemy(int HP , int MaxHP , double Armor , string Name) : Enemy(HP , MaxHP , Armor){this->Name = Name;}

// void HumanEnemy :: Attack(Player player){}

HumanEnemy :: ~HumanEnemy(){
    vector<string> EnemyDeathQuotes = { "I can't believe this is how it all ends!", "You fucking bastard!", "Wasted!", 
    "Nooo, I can't die yet!" , "My child , take care o..." , "I'll damn you" , "My brother will get my revenge!!!" , "I'll be waiting , you SoB" , 
    "That was a fun fight" , "See you on the other side"};
    random_device rd;
    mt19937 gen(rd());
    shuffle(EnemyDeathQuotes.begin(), EnemyDeathQuotes.end(), gen);
    cout << EnemyDeathQuotes[0] << endl;
}


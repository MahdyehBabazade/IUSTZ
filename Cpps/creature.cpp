#include "../Headers/creature.h"
#include <iostream>
using namespace std;

Player :: Player(string Name, int HP, int MaxHp, int Armor, int BackPackCapacity , int Energy , int Coin){
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

void Player :: Attack(Enemy* enemy){

} // to be filled

void Player :: takeDamage(int damagetaken){
    setHP(getHP() - damagetaken);
}

void Player :: setHP(int HP){
    this -> HP = HP;
}

int Player :: getHP(){return HP;}
#include "Headers/creature.h"
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

void clearScreen(){
    system("cls");
}

void AddItem(Player* Player);

void RemoveItem(Player* Player);

void ShowLists(Player* Player);

void Item_removal_Tester(){
    while(true){
        cout <<"Choose:\n\t1. Add Item\n\t2. Remove Item\n\t3. Show The Lists\n\t4. Exit";
        vector<pair<Item* , int>> Items = {};
        vector<pair<Weapon* , int>> Weapons = {};
        vector<pair<Consumable* , int>> Consumables = {};
        vector<Equipment*> Equipments ={nullptr , nullptr , nullptr , nullptr};
        Player* player = new Player("Herbod" , 100 , 0.0 , 100 , 0 , 0 ,0 , Items , Weapons , Consumables , Equipments);
        int choice;
        cin >> choice;
        clearScreen();
        switch (choice){
        case 1:
            AddItem(player);
            break;
        case 2:
            RemoveItem(player);
            break;
        case 3:
            ShowLists(player);
            break;
        default:
            exit;
            break;
        }
    }
}

void AddItem(Player* Player){

}

void RemoveItem(Player* Player){

}

void ShowLists(Player* Player){

}

int main(){
    Item_removal_Tester();
}
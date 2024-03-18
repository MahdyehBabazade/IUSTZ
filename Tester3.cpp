#include "Cpps/creature.cpp"
#include "Cpps/items.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

void check_dialogues(){
    Shopkeeper shopkeeper1("A");
    Medic medic1("B");

    Weapon* weapon = new Snipe("sniper",5,20,20,4,2,8);
    Consumable*  consumable = new Consumable("hiHPPoition" , "HPPotion" , 1 , 10 , 30); 
    vector<pair<Item*,int>> items = {make_pair(consumable , 1),make_pair(weapon,1)};
    vector<pair<Weapon* , int>> weapons = {make_pair(weapon,1)};
    vector<pair<Consumable* , int>> consumables = {make_pair(consumable , 1)};
    Vest* vest = new Vest("vest" , 60 , 60 , 10);
    vector<Equipment*> equipments = {vest};

    HumanEnemy enemy1("C", 100, 100, items, weapons, equipments, consumables);

    cout << "Choose the character you want to talk: ";
    while (true)
    {
        cout << endl << "1. Shopkeeper" << endl << "2. Medic" << endl << "3. Human Enemy" << endl << "4. Exit" << endl;
        int n;
        cin >> n;
        int choice;
        switch (n)
        {
        case 1:
            cout << "1. Hi \n"
                    "2. Bye \n"
                    "3. Sell \n"
                    "4. Buy \n"
                    "5. No Money \n";
            int choice;
            cin >> choice;
            switch (choice)
            {
                case 1:
                    shopkeeper1.HiDialogue();
                    break;
                case 2:
                    shopkeeper1.ByeDialogue();
                    break;
                case 3:
                    shopkeeper1.SellDialogue(weapon);
                    break;
                case 4: 
                    shopkeeper1.BuyDialogue(weapon);
                    break;
                case 5: 
                    shopkeeper1.NoMoneyDialogue();
                default:
                    break;
            }
        case 2:
            cout << "1. Hi \n"
                    "2. Bye \n"
                    "3. Heal \n"
                    "4. No Money \n";
            cin >> choice;
            switch (choice)
            {
                case 1:
                    medic1.HiDialogue();
                    break;
                case 2:
                    medic1.ByeDialogue();
                    break;
                case 3:
                    medic1.HealDialogue();
                    break;
                case 4:
                    medic1.NoMoneyDialogue();
                default:
                    break;
            }
            break;
        case 3:
            cout << "1. Rajaz Khani \n";
            cin >> choice;
            switch (choice)
            {
                case 1:
                    enemy1.RajazKhani();
                    break;
                default:
                    break;
            }
            break;
        case 4:
            exit(0);
            break; 
        default:
            break;
        }    
    }
}

int main(){
    check_dialogues();
}
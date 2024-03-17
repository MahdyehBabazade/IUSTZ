#include "Headers/creature.h"
#include "Headers/items.h"
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

void clearScreen(){
    system("cls");
}

void AddItem(Player* Player);

Weapon* AddWeapon();

Equipment* AddEquipment();

Consumable* AddConsumable();

void RemoveItem(Player* Player);

void ShowLists(Player* Player);

void Item_Changes_Tester(){
    while(true){
        clearScreen();
        cout <<"Choose: (Enter the number)\n\t1. Add Item\n\t2. Remove Item\n\t3. Show The Lists\n\t4. Exit";
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
    cout << "Choose what kind of Item you wanna add:(Enter the number)\n"
    << "\t1. Weapon\n\t2. Equipment\n\t3. Consumable\n\t4. Back";
    int choice;
    cin >> choice;
    clearScreen();
    switch (choice){
    case 1:
        Player->addItem(AddWeapon());        
        break;
    case 2:
        Player->addItem(AddEquipment());
        break;
    case 3:
        Player->addItem(AddConsumable());
        break;
    default:
        break;
    }
}

Weapon* AddWeapon(){
    cout << "What type of Weapon do you wanna Add?\n"
    << "\t1. Shotgun\n\t2. Sniper Rifle\n\t3. SMG\n\t4. Rifle\n\t5. Cold Weapon \n\t6. Grenade\n\t7. Boomrang\n"
    << "(Enter a number)\n";
    int choice;
    cin >> choice;
    clearScreen();
    cout << "What's the name of the Item?\n";
    string Name;
    getline(cin , Name);
    cout << "What's the weight of the Item?(positive integer)\n";
    int weight;
    cin >> weight;
    switch(choice){
    case 1:{
        Shotgun* shotgun = new Shotgun(Name , weight , 0 , 0 , 0 , 0 , 10);
        return shotgun;
        break;
    }
    case 2:{
        Snipe* snipe = new Snipe(Name , weight , 0 , 0 , 0 , 0 , 10);
        return snipe;
        break;
    }
    case 3:{
        SMG* Smg = new SMG(Name , weight , 0 , 0 , 0 , 0 , 10);
        return Smg;
        break;
    }
    case 4:{
        Rifle* rifle = new Rifle(Name , weight , 0 , 0 , 0 , 0 , 10);
        return rifle;
        break;
    }
    case 5:{
        ColdWeapon* Coldweapon = new ColdWeapon(Name , weight , 0 , 0 , 0);
        return Coldweapon;
        break;
    }
    case 6:{
        Grenade* grenade = new Grenade(Name , weight , 0 , 0 , 0);
        return grenade;
        break;
    }
    default:{
        BoomRang* Boomrang = new BoomRang(Name , weight , 0 , 0 , 0);
        return Boomrang;
        break;
    }
    }
}

Consumable* AddConsumable(){
    cout << "What type of potion do you wanna add?\n"
    << "\n\t1. HP Potion\n\t2. Shield Potion\n\t3. Energy Potion\nEnter the number of your choice\n";
    int choice;
    cin >> choice;
    clearScreen();
    cout << "Enter the Name of the Potion:\n";
    string Name;
    getline(cin , Name);
    int weight;
    cout << "Enter the weight of the Potion:(positive integer)\n";
    cin >> weight;
    switch (choice)
    {
    case 1:
        return new Consumable(Name , "HPPotion" , weight , 0 , 0);
        break;
    case 2:
        return new Consumable(Name , "ShieldPotion" , weight , 0 , 0);
        break;
    default:
        return new Consumable(Name , "EnergyPotion" , weight , 0 , 0);
        break;
    }
}

Equipment* AddEquipment(){
    cout << "What type of Equipment do you wanna add?\n"
    << "\n\t1. Head Gear \n\t2. Vest \n\t3. Foot Wear\n\t4. Boot\nEnter the number of your choice\n";
    int choice;
    cin >> choice;
    clearScreen();
    cout << "Enter the Name of the Equipment:\n";
    string Name;
    getline(cin , Name);
    int weight;
    cout << "Enter the weight of the Equipment:(positive integer)\n";
    cin >> weight;
    switch (choice)
    {
    case 1:
        return new HeadGear(Name, weight , 0 , 0);
        break;
    case 2:
        return new Vest(Name , weight , 0 , 0);
        break;
    case 3:
        return new FootWear(Name , weight , 0 , 0);
        break;
    default:
        return new Boot(Name , weight , 0 , 0);
        break;
    }
}

void RemoveItem(Player* Player){
    vector<pair<Item* , int>> Items = Player->getItems();
    cout << "Items:\n";
    for(int i = 0; i < Items.size(); i++){
        cout << "\t" << i + 1 << Items[i].first->getName() << "\n";
    }
    cout << "\t" << Items.size() + 1 << "Back\n";
    cout << "Choose what to remove with their number on the list:\n";
    int choice;
    cin >> choice;
    if(choice <= Items.size())
        Player->removeItem(Items[choice - 1].first);
}

void ShowLists(Player* Player){
    cout << "Which List do you wanna see? (Enter the number)\n" << 
    "\t1. Items\n\t2. Weapons\n\t3. Consumables\n\t4. Equipments\n\t5. Back\n";
    int choice;
    cin >> choice;
    clearScreen();
    switch (choice){
    case 1:{
        vector<pair<Item* , int>> Items = Player->getItems();
        for(int i = 0; i < Items.size(); i++){
            cout << "\t" << i + 1 << " " << Items[i].first->getName() << "\n";
        }
        cout << "Press anything to continue";
        getch();
        break;
    }
    case 2:{
        vector<pair<Weapon* , int>> Weapons = Player->getWeapons();
        for(int i = 0; i < Weapons.size(); i++){
            cout << "\t" << i + 1 << " " << Weapons[i].first->getName() << "\n";
        }
        cout << "Press anything to continue";
        getch();
        break;
    }
    case 3:{
        vector<pair<Consumable* , int>> Consumables = Player->getConsumables();
        for(int i = 0; i < Consumables.size(); i++){
            cout << "\t" << i + 1 << " " << Consumables[i].first->getName() << "\n";
        }
        cout << "Press anything to continue";
        getch();
        break;
    }
    case 4:{
        vector<Equipment*> Equipments = Player->getEquipments();
        for(int i = 0; i < Equipments.size(); i++){
            cout << "\t" << i + 1 << " " << Equipments[i]->getName() << "\n";
        }
        cout << "Press anything to continue";
        getch();
        break;
    }
    default:
        break;
    }
}

int main(){
    Item_Changes_Tester();
}
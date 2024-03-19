#include "Cpps/creature.cpp"
#include "Cpps/items.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

void getStat(vector<Character*> &enemies) {
    for (auto* Enemy : enemies) {
        cout << Enemy->getStat() << endl;
    }
}

int main() {
    vector<pair<Item*, int>> Items = {};
        vector<pair<Weapon*, int>> Weapons = {};
        vector<pair<Consumable*, int>> Consumables = {};
        vector<Equipment*> Equipments = { nullptr , nullptr , nullptr , nullptr };
        //auto* player = new Player("Herbod", 100, 0.0, 100, 0, 50, 0, Items, Weapons, Consumables, Equipments);

        auto* enemy = new HumanEnemy("enemy", 100, 0, Items, Weapons, Equipments, Consumables);
        auto* enemy1 = new HumanEnemy("enemy", 100, 0, Items, Weapons, Equipments, Consumables);
        auto* enemy2 = new HumanEnemy("enemy", 100, 0, Items, Weapons, Equipments, Consumables);
        auto* enemy3 = new HumanEnemy("enemy", 100, 0, Items, Weapons, Equipments, Consumables);
        vector<Character*> enemies = { enemy1,enemy2,enemy3,enemy };
        
        auto* punch = new Punch();
        auto* rifle = new Rifle();
        auto* sniper = new Snipe();
        auto* shotgun = new Shotgun();
        auto* smg = new SMG();
        auto* grenade = new Grenade();
        auto* boomRang = new BoomRang();
        auto* knife = new ColdWeapon();
    while (true) {
        system("cls");
        getStat(enemies);
        cout << "choose a weapon you want to attack with: \n"
            "1. " << punch->getStat() << endl << 
            "2. " << rifle->getStat() << endl << 
            "3. " << sniper->getStat() << endl <<
            "4. " << shotgun->getStat() << endl <<
            "5. " << smg->getStat() << endl << 
            "6. " << grenade->getStat() << endl <<
            "7. " << boomRang->getStat() << endl << 
            "8. " << knife->getStat() << endl <<
            "choose: ";
        int choice;
        cin >> choice;
        system("cls");
        if(choice == 1){
            punch->Attack(enemies);
        }else if(choice == 2){
            rifle->Attack(enemies);
        }
        else if (choice == 3) {
            sniper->Attack(enemies);
        }else if(choice == 4){
            shotgun->Attack(enemies);
        }else if(choice ==5){
            smg->Attack(enemies);
        }
        else if (choice == 6) {
            grenade->Attack(enemies);
        }
        else if (choice == 7){
            boomRang->Attack(enemies);
        }
        else if (choice == 8) {
            knife->Attack(enemies);
        }else{
            break;
        }
    }
}
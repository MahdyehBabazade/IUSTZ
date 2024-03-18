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
    while (true) {
        vector<pair<Item*, int>> Items = {};
        vector<pair<Weapon*, int>> Weapons = {};
        vector<pair<Consumable*, int>> Consumables = {};
        vector<Equipment*> Equipments = { nullptr , nullptr , nullptr , nullptr };
        //auto* player = new Player("Herbod", 100, 0.0, 100, 0, 50, 0, Items, Weapons, Consumables, Equipments);

        auto* enemy = new HumanEnemy("enemy", 100, 0, Items, Weapons, Equipments, Consumables);
        vector<Character*> enemies = { enemy,enemy,enemy,enemy };

        getStat(enemies);
        cout << "choose a weapon you want to attack with: \n"
            "1. punch \n"
            "2. Rifle \n"
            "3. Sniper \n"
            "4. ShotGun \n"
            "5. SMG \n"
            "6. Grenade \n"
            "7. BoomRang \n"
            "8. Knife \n"
            "choose: \n";
        int choice;
        cin >> choice;
        if(choice == 1){
            auto* punch = new Punch();
            punch->Attack(enemies);
        }else if(choice == 2){
            auto* rifle = new Rifle();
            rifle->Attack(enemies);
        }
        else if (choice == 3) {
            auto* sniper = new Snipe();
            sniper->Attack(enemies);
        }else if(choice == 4){
            auto* shotgun = new Shotgun();
            shotgun->Attack(enemies);
        }else if(choice ==5){
            auto* smg = new SMG();
            smg->Attack(enemies);
        }
        else if (choice == 6) {
            auto* grenade = new Grenade();
            grenade->Attack(enemies);
        }
        else if (choice == 7) {
            auto* boomRang = new BoomRang();
            boomRang->Attack(enemies);
        }
        else if (choice == 8) {
            auto* knife = new ColdWeapon();
            knife->Attack(enemies);
        }else{
            break;
        }
        getStat(enemies);
    }
}
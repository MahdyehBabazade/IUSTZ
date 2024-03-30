#pragma once
#include "../Headers/items.h"
#include "../Headers/creature.h"
#include "../Headers/map.h"
using namespace std;

class ShopFactory{
private:
    Map* map;
    Shop* shop;
public:
    ShopFactory() = default;
    ShopFactory(Map* map, Shop* shop);
    void Generate(Shop* shop);
};


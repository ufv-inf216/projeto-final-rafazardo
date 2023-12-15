#ifndef PROJETO_FINAL_INF216_GLOBAL_H
#define PROJETO_FINAL_INF216_GLOBAL_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <SDL.h>
#include "Json.h"

// Item struct declarations
struct ARMOR {
    int id;
    std::string name;
    float kg;
    int ac;
    int mdex;
};
struct FOOD {
    int id;
    std::string name;
    float kg;
    int heal;
};
struct ITEM {
    int id;
    std::string name;
    float kg;
};
struct POTION {
    int id;
    std::string name;
    float kg;
    int heal;
    std::string dir;
};
struct WEAPON {
    int id;
    std::string name;
    int dam;
    float kg;
    std::string dir;
};

// Item vector declarations
extern std::vector<ARMOR> ARMORS;
extern std::vector<FOOD> FOODS;
extern std::vector<ITEM> ITEMS;
extern std::vector<POTION> POTIONS;
extern std::vector<WEAPON> WEAPONS;

// Recipes declaration
struct INGREDIENT {
    std::string type;
    int id;
    int requiredAmount;
};
extern std::map<std::string, std::vector<std::vector<INGREDIENT>>> RECIPES;

// Armor ID declarations
extern const int PADDED_ARMOR_ID;
extern const int LEATHER_ARMOR_ID;
extern const int STUDDED_ARMOR_ID;
extern const int CHAIN_ARMOR_ID;
extern const int SCALE_MALE_ARMOR_ID;
extern const int HALFPLATE_ARMOR_ID;
extern const int PLATE_ARMOR_ID;

// Food ID declarations
extern const int APPLE_ID;
extern const int BREAD_ID;

// Item ID declarations
extern const int STICK_ID;

// Potion ID declarations
extern const int HEALING_ELIXIR_ID;
extern const int BETTER_HEALING_ID;
extern const int GREATER_HEALING_ID;
extern const int SUPERIOR_HEALING_ID;
extern const int SUPREME_HEALING_ID;

// Weapon ID declarations
extern const int SHORT_SWORD_ID;
extern const int GREAT_SWORD_ID;

extern const std::string GLOBAL_DIAG_DIRS[3];

#define TOTAL_ENEMY_ATTACKS 2
extern std::vector<class Attack*> EnemyAttacks;

#define TOTAL_ENEMIES 2
extern std::vector<std::vector<int>>EnemyAttackOptions;

#define START_DEX 4

extern std::vector<int> GLOBAL_TotalEnemiesKilled;

// Function to be used in main file
void DefineGlobalVariables();

// Returns a random enemy
class Enemy* GenerateRandomEnemy(class MyGame *game);

#endif //PROJETO_FINAL_INF216_GLOBAL_H

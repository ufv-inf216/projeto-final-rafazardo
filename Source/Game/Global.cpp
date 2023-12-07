#include "Global.h"
#include "../GameSpecific/Characters/Enemies/Bat.h"
#include "../GameSpecific/Characters/Enemies/Slime.h"
#include "Random.h"

std::vector<ARMOR> ARMORS;
std::vector<FOOD> FOODS;
std::vector<ITEM> ITEMS;
std::vector<POTION> POTIONS;
std::vector<WEAPON> WEAPONS;

// nlohmann::json enemiesData;

// Armor ID definitions
const int PADDED_ARMOR_ID = 0;
const int LEATHER_ARMOR_ID = 1;
const int STUDDED_ARMOR_ID = 2;
const int CHAIN_ARMOR_ID = 3;
const int SCALE_MALE_ARMOR_ID = 4;
const int HALFPLATE_ARMOR_ID = 5;
const int PLATE_ARMOR_ID = 6;

// Food ID definitions
const int APPLE_ID = 0;
const int BREAD_ID = 1;

// Item ID definitions
const int STICK_ID = 0;

// Potion ID definitions
const int HEALING_ELIXIR_ID = 0;
const int BETTER_HEALING_ID = 1;
const int GREATER_HEALING_ID = 2;
const int SUPERIOR_HEALING_ID = 3;
const int SUPREME_HEALING_ID = 4;

// Weapon ID definitions
const int SHORT_SWORD_ID = 0;
const int GREAT_SWORD_ID = 1;

std::map<std::string, std::vector<std::vector<INGREDIENT>>> RECIPES;

void DefineGlobalVariables() {
    std::ifstream armorsFile("../Assets/JsonFiles/Items/armors.json");
    nlohmann::json armorsData;
    armorsFile >> armorsData;
    armorsFile.close();

    for (const auto& it : armorsData) {
        ARMOR armor;
        armor.id = it["id"];
        armor.name = it["name"];
        armor.kg = it["kg"];
        armor.ac = it["ac"];
        armor.mdex = it["mdex"];
        ARMORS.push_back(armor);
    }

    std::ifstream foodsFile("../Assets/JsonFiles/Items/foods.json");
    nlohmann::json foodsData;
    foodsFile >> foodsData;
    foodsFile.close();

    for (const auto& it : foodsData) {
        FOOD food;
        food.id = it["id"];
        food.name = it["name"];
        food.kg = it["kg"];
        food.heal = it["heal"];
        FOODS.push_back(food);
    }

    std::ifstream itemsFile("../Assets/JsonFiles/Items/items.json");
    nlohmann::json itemsData;
    itemsFile >> itemsData;
    itemsFile.close();

    for (const auto& it : itemsData) {
        ITEM item;
        item.id = it["id"];
        item.name = it["name"];
        item.kg = it["kg"];
        ITEMS.push_back(item);
    }

    std::ifstream potionsFile("../Assets/JsonFiles/Items/potions.json");
    nlohmann::json potionsData;
    potionsFile >> potionsData;
    potionsFile.close();

    for (const auto& it : potionsData) {
        POTION potion;
        potion.id = it["id"];
        potion.name = it["name"];
        potion.kg = it["kg"];
        potion.heal = it["heal"];
        POTIONS.push_back(potion);
    }

    std::ifstream weaponsFile("../Assets/JsonFiles/Items/weapons.json");
    nlohmann::json weaponsData;
    weaponsFile >> weaponsData;
    weaponsFile.close();

    for (const auto& it : weaponsData) {
        WEAPON weapon;
        weapon.id = it["id"];
        weapon.name = it["name"];
        weapon.dam = it["dam"];
        weapon.kg = it["kg"];
        WEAPONS.push_back(weapon);
    }

    //Definir RECIPES
    std::ifstream weaponsRecipesFile("../Assets/JsonFiles/Recipes/weapons_recipes.json");
    nlohmann::json weaponsRecipesData;
    weaponsRecipesFile >> weaponsRecipesData;
    weaponsRecipesFile.close();

    for (const auto& it : weaponsRecipesData) {

        std::vector<INGREDIENT> ingredients;
        for (const auto& ingd : it["ingredients"]) {
            INGREDIENT ingredient;
            ingredient.type = ingd["type"];
            ingredient.id = ingd["id"];
            ingredient.requiredAmount = ingd["required_amount"];
            ingredients.push_back(ingredient);
        }
        RECIPES["weapon"].push_back(ingredients);
    }


    //Fazer para os outros tipos de item também
}

nlohmann::json enemiesData;
Enemy* GenerateRandomEnemy(MyGame *game) {
    std::ifstream enemiesJson("../Assets/JsonFiles/Enemies/enemies.json");
    enemiesData = nlohmann::json::parse(enemiesJson);

     // Chooses a random enemy.
     int pos = Random::GetIntRange(0, 1);
     Enemy *enemy;
     int attr[] = {Random::GetIntRange(enemiesData[pos]["min_attrs"][0], enemiesData[pos]["max_attrs"][0]),
                   Random::GetIntRange(enemiesData[pos]["min_attrs"][1], enemiesData[pos]["max_attrs"][1]),
                   Random::GetIntRange(enemiesData[pos]["min_attrs"][2], enemiesData[pos]["max_attrs"][2]),
                   Random::GetIntRange(enemiesData[pos]["min_attrs"][3], enemiesData[pos]["max_attrs"][3]),
                   Random::GetIntRange(enemiesData[pos]["min_attrs"][4], enemiesData[pos]["max_attrs"][4]),
                   Random::GetIntRange(enemiesData[pos]["min_attrs"][5], enemiesData[pos]["max_attrs"][5])};

     auto img_dims = Vector2(enemiesData[pos]["img_dims"][0],enemiesData[pos]["img_dims"][1]);

     // Creates the chosen enemy.
     switch(pos) {
         // Slime
         case 0:
            enemy = new Slime(game, enemiesData[pos]["img_dir"], img_dims, attr);
            break;

         // Bat
         case 1:
            enemy = new Bat(game, enemiesData[pos]["img_dir"], img_dims, attr);
            break;
     }

     return enemy;
}
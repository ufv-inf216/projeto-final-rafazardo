// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Inventory module for saving and managing characters items
// ----------------------------------------------------------------
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../Game/Global.h"

class Inventory {
private:
    // Current weight of the inventory
    float mWeight;

    // Maximum weight the inventory can support
    float mMaxWeight;

    // Vectors to map an item to his current amount
    std::vector<int> mArmors;
    std::vector<int> mFoods;
    std::vector<int> mItems;
    std::vector<int> mPotions;
    std::vector<int> mWeapons;

public:
    // Inventory constructor
    // @param maxWeight is the maximum weight the inventory can support.
    Inventory(float maxWeight);

    // Update the amount of items in the inventory
    // @param type "armor", "food", "item", "potion or "weapon"
    // @param id The global ID
    // @param amount The amount (positive or negative) to add or subtract from inventory.
    // @return true if the item's amount is not negative and weight doesn't exceed the limit.
    bool UpdateItems(std::string type, int id, int amount);

    // @param type "armor", "food", "item", "potion or "weapon"
    // @param id The global ID
    // @return amount How many of the specified item can be added.
    int GetAvailableSpace(std::string type, int id);

    // @param type "armor", "food", "item", "potion or "weapon"
    // @param id The global ID
    // @return The amount of the specified item.
    int GetItemAmount(std::string type, int id);

    // @return mWeight
    float GetWeight();

    // @return mMaxWeight
    float GetMaxWeight();

    // Set the attribute mMaxWeight
    // @param maxWeight Will be the new value for mMaxWeight.
    void SetMaxWeight(float maxWeight);

    void PrintInventory();
};
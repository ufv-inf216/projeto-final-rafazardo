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
#include "../Interfaces/HUDs/InventoryHUD.h"

class Inventory : public GameObject {
private:
    // Current weight of the inventory
    int mWeightPotion = 0;
    int mWeightWeapon = 0;

    // Maximum weight the inventory can support
    int mMaxWeightPotion;
    int mMaxWeightWeapon;

    // Vectors to map an item to his current amount
    std::vector<int> mItems;
    std::vector<int> mPotions;
    std::vector<int> mWeapons;

    InventoryHUD *mInventoryHUD;

    bool mIsOpen = false;

public:
    // Inventory constructor
    // @param maxWeight is the maximum weight the inventory can support.
    Inventory(MyGame *myGame, int maxWeightPotion, int maxWeightWeapon);

    // Update the amount of items in the inventory
    // @param type "armor", "food", "item", "potion or "weapon"
    // @param id The global ID
    // @param amount The amount (positive or negative) to add or subtract from inventory.
    // @return true if the item's amount is not negative and weight doesn't exceed the limit.
    bool UpdateItems(std::string type, int id, int amount);

    // @param type "armor", "food", "item", "potion or "weapon"
    // @param id The global ID
    // @return The amount of the specified item.
    int GetItemAmount(std::string type, int id);

    // @return mWeight
    float GetWeight();

    // @return mMaxWeightPotion
    int GetMaxWeightPotion() { return mMaxWeightPotion; }

    // @return mMaxWeightWeapon
    int GetMaxWeightWeapon() { return mMaxWeightWeapon; }

    // @return mWeightPotion
    int GetWeightPotion() { return mWeightPotion; }

    // @return mMaxWeightWeapon
    int GetWeightWeapon() { return mWeightWeapon; }

    // Set the attribute mMaxWeight
    // @param maxWeight Will be the new value for mMaxWeight.
    void SetMaxWeight(int maxWeight);

    void PrintInventory();

    void Open();

    void Close();

    bool IsOpen() { return mIsOpen; }
};
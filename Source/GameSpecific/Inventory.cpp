// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Inventory method definitions
// ----------------------------------------------------------------

#include "Inventory.h"

Inventory::Inventory(float maxWeight) {
    mMaxWeight = maxWeight;
    mArmors.resize(ARMORS.size());
    mFoods.resize(FOODS.size());
    mItems.resize(ITEMS.size());
    mPotions.resize(POTIONS.size());
    mWeapons.resize(WEAPONS.size());
}

bool Inventory::UpdateItems(std::string type, int id, int amount) {

    if(type == "armor") {
        mArmors[id] += amount;
        mWeight += amount * ARMORS[id].kg;

        if(mArmors[id] < 0 || mWeight > mMaxWeight) {
            mArmors[id] -= amount;
            mWeight -= amount * ARMORS[id].kg;
            return false;
        }
        return true;
    }
    else if(type == "food") {
        mFoods[id] += amount;
        mWeight += amount * FOODS[id].kg;

        if(mFoods[id] < 0 || mWeight > mMaxWeight) {
            mFoods[id] -= amount;
            mWeight -= amount * FOODS[id].kg;
            return false;
        }
        return true;
    }
    else if(type == "item") {
        mItems[id] += amount;
        mWeight += amount * ITEMS[id].kg;

        if(mItems[id] < 0 || mWeight > mMaxWeight) {
            mItems[id] -= amount;
            mWeight -= amount * ITEMS[id].kg;
            return false;
        }
        return true;
    }
    else if(type == "potion") {
        mPotions[id] += amount;
        mWeight += amount * POTIONS[id].kg;

        if(mPotions[id] < 0 || mWeight > mMaxWeight) {
            mPotions[id] -= amount;
            mWeight -= amount * POTIONS[id].kg;
            return false;
        }
        return true;
    }
    else if(type == "weapon") {
        mWeapons[id] += amount;
        mWeight += amount * WEAPONS[id].kg;

        if(mWeapons[id] < 0 || mWeight > mMaxWeight) {
            mWeapons[id] -= amount;
            mWeight -= amount * WEAPONS[id].kg;
            return false;
        }
        return true;
    }
    else return false;
}

int Inventory::GetItemAmount(std::string type, int id) {
    if(type == "armor")
        return mArmors[id];
    if(type == "food")
        return mFoods[id];
    if(type == "item")
        return mItems[id];
    if(type == "potion")
        return mPotions[id];
    if(type == "weapon")
        return mWeapons[id];

    return 0;
}

int Inventory::GetAvailableSpace(std::string type, int id) {
    int amount = 0;

    if(type == "armor")
        amount = (mMaxWeight - mWeight) / ARMORS[id].kg;
    else if(type == "food")
        amount = (mMaxWeight - mWeight) / FOODS[id].kg;
    else if(type == "item")
        amount = (mMaxWeight - mWeight) / ITEMS[id].kg;
    else if(type == "potion")
        amount = (mMaxWeight - mWeight) / POTIONS[id].kg;
    else if(type == "weapon")
        amount = (mMaxWeight - mWeight) / WEAPONS[id].kg;

    return amount;
}

float Inventory::GetWeight() { return mWeight; }

float Inventory::GetMaxWeight() { return mMaxWeight; }

void Inventory::SetMaxWeight(float maxWeight) { mMaxWeight = maxWeight; }

void Inventory::PrintInventory() {
    for(int i=0; i<ARMORS.size(); i++) {
        if(mArmors[i] > 0)
            std::cout << ARMORS[i].name << ": " << mArmors[i] << std::endl;
    }

    for(int i=0; i<FOODS.size(); i++) {
        if(mFoods[i] > 0)
            std::cout << FOODS[i].name << ": " << mFoods[i] << std::endl;
    }

    for(int i=0; i<ITEMS.size(); i++) {
        if(mItems[i] > 0)
            std::cout << ITEMS[i].name << ": " << mItems[i] << std::endl;
    }

    for(int i=0; i<POTIONS.size(); i++) {
        if(mPotions[i] > 0)
            std::cout << POTIONS[i].name << ": " << mPotions[i] << std::endl;
    }

    for(int i=0; i<WEAPONS.size(); i++) {
        if(mWeapons[i] > 0)
            std::cout << WEAPONS[i].name << ": " << mWeapons[i] << std::endl;
    }
}
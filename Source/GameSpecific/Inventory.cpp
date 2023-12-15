// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Inventory method definitions
// ----------------------------------------------------------------

#include "Inventory.h"
#include "../GameSpecific/MyGame.h"

Inventory::Inventory(MyGame *myGame, int maxWeightPotion, int maxWeightWeapon) : GameObject(myGame) {
    mMaxWeightPotion = maxWeightPotion;
    mMaxWeightWeapon = maxWeightWeapon;
    mItems.resize(ITEMS.size());
    mPotions.resize(POTIONS.size());
    mWeapons.resize(WEAPONS.size());

    mInventoryHUD = new InventoryHUD(mGame);
    mInventoryHUD->Disable();
}

bool Inventory::UpdateItems(std::string type, int id, int amount) {

    if(type == "item") {
        mItems[id] += amount;

        if(mItems[id] < 0) {
            mItems[id] -= amount;
            return false;
        }
        return true;
    }
    else if(type == "potion") {
        mPotions[id] += amount;
        mWeightPotion += amount;

        if(mPotions[id] < 0 || mWeightPotion > mMaxWeightPotion) {
            mPotions[id] -= amount;
            mWeightPotion -= amount;
            return false;
        }
        return true;
    }
    else if(type == "weapon") {
        mWeapons[id] += amount;
        mWeightWeapon += amount;

        if(mWeapons[id] < 0 || mWeightWeapon > mMaxWeightWeapon) {
            mWeapons[id] -= amount;
            mWeightWeapon -= amount;
            return false;
        }
        return true;
    }
    else return false;
}

int Inventory::GetItemAmount(std::string type, int id) {

    if(type == "item")
        return mItems[id];
    else if(type == "potion")
        return mPotions[id];
    else if(type == "weapon")
        return mWeapons[id];

    return 0;
}

void Inventory::PrintInventory() {

    std::cout << "Weapon w = " << mWeightWeapon << std::endl;
    std::cout << "Potion w = " << mWeightPotion << std::endl;

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

void Inventory::Open() {
    if(mPressCounter < .5f) return;

    mInventoryHUD->SetPosition(mGame->GetCamera()->GetPosition());
    mIsOpen = true;
    mInventoryHUD->Enable();
    mPressCounter = .0f;
    mGame->GetCamera()->Disable();
}

void Inventory::Close() {
    if(mPressCounter < .5f) return;

    mIsOpen = false;
    mInventoryHUD->Disable();
    mPressCounter = .0f;
    mGame->GetCamera()->Enable();
}
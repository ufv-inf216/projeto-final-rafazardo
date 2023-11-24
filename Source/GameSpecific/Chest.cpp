// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Chest module methods implementation
// ----------------------------------------------------------------

#include "Chest.h"
Chest::Chest(class MyGame *game, const std::string &texturePath, Inventory *inventory):
        GameObject(game) {

    mSpriteComponent = new SpriteComponent(this, texturePath, 32, 32);
    mBoxColliderComponent = new BoxColliderComponent(this, 0, 0, 32, 32, ColliderLayer::Chest);
    mInventory = inventory;
}

void Chest::Interact(Inventory *inventory) {

    for(int id=0; id<ARMORS.size(); id++) {
        int maximumAmount = std::min(inventory->GetAvailableSpace("armor", id), mInventory->GetItemAmount("armor", id));
        // Transfers to inventory the maximum amount of the item
        inventory->UpdateItems("armor", id, maximumAmount);
        // Remove the items from chest
        mInventory->UpdateItems("armor", id, -maximumAmount);
    }

    for(int id=0; id<FOODS.size(); id++) {
        int maximumAmount = std::min(inventory->GetAvailableSpace("food", id), mInventory->GetItemAmount("food", id));
        // Transfers to inventory the maximum amount of the item
        inventory->UpdateItems("food", id, maximumAmount);
        // Remove the items from chest
        mInventory->UpdateItems("food", id, -maximumAmount);
    }

    for(int id=0; id<ITEMS.size(); id++) {
        int maximumAmount = std::min(inventory->GetAvailableSpace("item", id), mInventory->GetItemAmount("item", id));
        // Transfers to inventory the maximum amount of the item
        inventory->UpdateItems("item", id, maximumAmount);
        // Remove the items from chest
        mInventory->UpdateItems("item", id, -maximumAmount);
    }

    for(int id=0; id<POTIONS.size(); id++) {
        int maximumAmount = std::min(inventory->GetAvailableSpace("potion", id), mInventory->GetItemAmount("potion", id));
        // Transfers to inventory the maximum amount of the item
        inventory->UpdateItems("potion", id, maximumAmount);
        // Remove the items from chest
        mInventory->UpdateItems("potion", id, -maximumAmount);
    }

    for(int id=0; id<WEAPONS.size(); id++) {
        int maximumAmount = std::min(inventory->GetAvailableSpace("weapon", id), mInventory->GetItemAmount("weapon", id));
        // Transfers to inventory the maximum amount of the item
        inventory->UpdateItems("weapon", id, maximumAmount);
        // Remove the items from chest
        mInventory->UpdateItems("weapon", id, -maximumAmount);
    }
}

Inventory *Chest::GetChest() {
    return mInventory;
}

void Chest::SetChest(Inventory *inventory) {
    mInventory = inventory;
}
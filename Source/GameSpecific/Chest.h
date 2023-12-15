// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Chest module to model an item's container
// ----------------------------------------------------------------

#pragma once

#include <algorithm>
#include "Inventory.h"
#include "../GameObjects/GameObject.h"
#include "../Components/DrawComponents/SpriteComponent.h"
#include "../GameSpecific/MyGame.h"

class Chest : public GameObject{
private:
    SpriteComponent *mSpriteComponent;
    BoxColliderComponent *mBoxColliderComponent;
    Inventory *mInventory;

public:
    // Chest constructor
    Chest(class MyGame *game, const std::string &texturePath, Inventory *inventory);

    // Transfer all the possible items from chest to an inventory
    // @param *inventory Is the destination of the chest items
    void Interact(Inventory *inventory);

    // @return The chest's inventory
    Inventory *GetChest();

    void SetChest(Inventory *inventory);
};
// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Crafter method definitions
// ----------------------------------------------------------------

#include "Crafter.h"

Crafter::Crafter(class MyGame *game, const std::string &texturePath, int attrs[6]):
        NPC(game, texturePath, attrs) { }

bool Crafter::Craft(std::string type, int id, Inventory *inventory) {

    // Verify if the weight is acceptable by adding the new item
    if(inventory->GetAvailableSpace(type, id) == 0)
        return false;

    // Verify if it's possible to craft the item based on the player's inventory. Returns false if there are missing ingredients
    for(auto ingredient : RECIPES[type][id])
        if(inventory->GetItemAmount(ingredient.type, ingredient.id) < ingredient.requiredAmount) return false;

    // Knowing that is possible to craft, we deduct the items required for the crafting from inventory
    for(auto ingredient : RECIPES[type][id])
        inventory->UpdateItems(ingredient.type, ingredient.id, -ingredient.requiredAmount);

    inventory->UpdateItems(type, id, 1);
    return true;
}

void Crafter::Interact() {
    return;
}

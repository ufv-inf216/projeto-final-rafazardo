// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Crafter module for defining the carfter NPC behavior and
// assignments
// ----------------------------------------------------------------

#pragma once

#include <map>
#include <vector>
#include <string>
#include "NPC.h"
#include "Character.h"
#include "../Inventory.h"
#include "../../Game/Global.h"

class Crafter : public NPC {
public:
    // Constructor
    // @param game The current game
    // @params texturePath The NPC texture directory
    // @params attrs A array containing NPC attributes (STR, DEX, CON, WIS, INT, CHA).
    Crafter(class MyGame *game, const std::string &texturePath, const std::string &spriteSheetData, int attrs[6]);

    // Craft a specified item and transfers to the player's inventory
    // @param type "armor", "food", "item", "potion or "weapon"
    // @param id The global ID of the item to be crafted
    // @return true if the crafting is successful
    bool Craft(std::string type, int id, Inventory *inventory);

    void Interact() override;
};
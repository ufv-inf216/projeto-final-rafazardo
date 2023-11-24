// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// NPC module for defining atributes and methods regarding NPCs
// behavior and mechanincs.
// ----------------------------------------------------------------

#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include "../../GameObjects/GameObject.h"
#include "../../Components/DrawComponents/SpriteComponent.h"

class NPC : public Character {
    public:
        // Constructor
        // @param game The current game
        // @params texturePath The NPC texture directory
        // @params attrs A array containing NPC attributes (STR, DEX, CON, WIS, INT, CHA).
        NPC(class MyGame *game, const std::string &texturePath, int attrs[6]);

        virtual void Interact();
};

#endif

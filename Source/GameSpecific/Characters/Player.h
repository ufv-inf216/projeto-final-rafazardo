// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Player module for defining atributes and methods regarding player
// behavior and mechanincs.
// ----------------------------------------------------------------

#pragma once

#include <iostream>
#include "Character.h"
#include "../../GameObjects/GameObject.h"
#include "../../Components/DrawComponents/SpriteComponent.h"
#include "../../GameSpecific/MyGame.h"

class Player : public Character {
    private:
        std::string mName;

    public:
        // Constructor
        // @param game The current game
        // @params texturePath The player texture directory
        // @params attrs A array containing player attributes (STR, DEX, CON, WIS, INT, CHA).
        Player(class MyGame *game, const std::string &texturePath, int attrs[6], Inventory *inventory);

        // Define player's behaviour for each input
        // @param state A array that stores pressed keys
        void OnProcessInput(const uint8_t* state) override;
};
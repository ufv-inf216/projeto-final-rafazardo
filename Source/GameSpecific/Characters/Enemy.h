// -----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Enemy module for defining atributes and methods regarding enemies
// behavior and mechanincs.
// -----------------------------------------------------------------

#pragma once

#include "Character.h"
#include "../../GameObjects/GameObject.h"
#include "../../Components/DrawComponents/SpriteComponent.h"

class Enemy : public Character {
    public:
        // Constructor
        // @param game The current game
        // @params texturePath The enemy texture directory
        // @params attrs A array containing enemy attributes (STR, DEX, CON, WIS, INT, CHA).
        Enemy(class MyGame *game, const std::string &texturePath, int attrs[6]);

        void OnCollision(std::unordered_map<CollisionSide, BoxColliderComponent::Overlap>& responses) override;
};

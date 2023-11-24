// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Sheet module for storing each character data, such as attributes,
// health points etc.
// ----------------------------------------------------------------

#pragma once

#include "Character.h"
#include "../../GameObjects/GameObject.h"
#include "../../Components/DrawComponents/SpriteComponent.h"
#include "../Inventory.h"

struct CharacterSheet {
    // Character attributes
    int str, strMod, dex, dexMod, con, conMod,   // Physical attributes
        intc, intcMod, wis, wisMod, cha, chaMod; // Non-physical attributes

    // Constructor
    // @param attrs A integer array storing the attributes values
    CharacterSheet(int attrs[6]) {
        str = attrs[0]; dex = attrs[1]; con = attrs[2];
        intc = attrs[3]; wis = attrs[4]; cha = attrs[5];

        // Calculating modifiers.
        strMod = (str-10)/2; dexMod = (dex-10)/2; conMod = (con-10)/2;
        intcMod = (intc-10)/2; wisMod = (wis-10)/2; chaMod = (cha-10)/2;
    };
};

class Character : public GameObject {
    protected:
        // Boolean values for storing current character movement state.
        bool mIsWalkingHorizontal,
             mIsWalkingUp,
             mIsWalkingDown;

        // Character's speed
        float mSpeed;

        // Character sheet.
        CharacterSheet *mSheet;

        Inventory *mInventory;

        // Collision Layer;
        ColliderLayer mCollisionLayer;

        // Character components.
        RigidBodyComponent *mRigidBodyComponent;
        SpriteComponent *mSpriteComponent;
        BoxColliderComponent *mBoxColliderComponent;

    public:
        // Constructor
        // @param game The current game
        // @params texturePath The player texture directory
        // @params attrs A array containing player attributes (STR, DEX, CON, WIS, INT, CHA).
        Character(class MyGame *game, const std::string &texturePath, int attrs[6], ColliderLayer coll_layer);

        // @returns The character's sheet.
        CharacterSheet* GetCharacterSheet() { return mSheet; }

        Inventory* GetInventory() { return mInventory; }
};

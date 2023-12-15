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
    private:
        std::string mDialogue;

        float mPressCounter = .0f;
        bool mIsHUDOpen = false;

        class Quest *mQuest;

    public:
        // Constructor
        // @param game The current game
        // @params texturePath The NPC texture directory
        // @params attrs A array containing NPC attributes (STR, DEX, CON, WIS, INT, CHA).
        NPC(class MyGame *game, const std::string &texturePath, const std::string &spriteSheetData, int attrs[6]);

        void SetDialogue(std::string &dialogue) { mDialogue = dialogue; }
        std::string& GetDialogue() { return mDialogue; }

        virtual void Interact();

        void SetQuest(class Quest *quest);

        void OnProcessInput(const Uint8 *state) override;

        void OnUpdate(float deltaTime) override { mPressCounter += deltaTime; }
};

#endif

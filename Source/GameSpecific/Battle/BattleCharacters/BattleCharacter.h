// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// BattleCharacter module for defining the basics attributes for
// each character during a battle.
// ----------------------------------------------------------------

#pragma once

#include "../../../GameObjects/GameObject.h"
#include "../../Characters/Character.h"
#include "../Action.h"

class BattleCharacter : public GameObject {
    protected:
        // Character sheet.
        CharacterSheet *mSheet;

        // Character components.
        SpriteComponent *mSpriteComponent;

        std::vector<Attack *> mAttacks;
        std::vector<Heal *> mHeals;

        Action *mCurrentAction;
        class Battle *mBattle;

        bool mHasAttacked;

        int mHP = 20;    // default.
        int mMaxHP = 20; // default.

        int mRemoveHeal = -1;
        int mInitiative;

    public:
        // Constructor
        // @param game The current game
        // @params character The source character
        BattleCharacter(class MyGame *game, class Battle *battle);

        // @returns The character's sheet.
        CharacterSheet* GetCharacterSheet() { return mSheet; }

        virtual Action* GetAction() { return mCurrentAction; }

        // @returns a Random number from 1 to 20 + DEX mod.
        int RollInitiative();
        int GetInitiative() { return mInitiative; }

        bool IsAlive() { return mHP > 0; }

        void SetHP(int new_hp) { mHP = new_hp; }
        float GetHP() { return (float)mHP; }

        virtual Character* GetCharacter() { return nullptr; }

        void RemoveHeal(int id) { mRemoveHeal = id; }
        void SetInitiative(int init) { mInitiative = init; }

        float GetMaxHP() { return (float)mMaxHP; }

        Battle *GetBattle() { return mBattle; }
};

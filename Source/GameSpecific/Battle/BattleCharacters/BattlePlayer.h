// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// BattlePlayer module for storing player's data during a battle
// ----------------------------------------------------------------

#pragma once

#include "../../Characters/Player.h"
#include "BattleCharacter.h"

class BattlePlayer : public BattleCharacter {
    private:
        Player *mPlayer;

    public:
        BattlePlayer(class MyGame *game, Battle *battle, Player *player);

        // Define player's behaviour for each input
        // @param state A array that stores pressed keys
        void OnProcessInput(const uint8_t* state) override;

        Action* GetAction() override;

        Character* GetCharacter() override { return mPlayer; }
};

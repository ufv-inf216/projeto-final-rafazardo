// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// BattleEnemy module for storing enemies' data during a battle
// ----------------------------------------------------------------

#pragma once

#include "../../../GameObjects/GameObject.h"
#include "../../Characters/Enemy.h"
#include "BattleCharacter.h"
#include "../../../Components/DrawComponents/SpriteComponent.h"

class BattleEnemy : public BattleCharacter {
    private:
        SpriteComponent *mSpriteComponent;

        Enemy *mEnemy;

    public:
        BattleEnemy(class MyGame *game, Battle *battle, Enemy *enemy);

        Action* GetAction() override;

        Character* GetCharacter() override { return mEnemy; }
};
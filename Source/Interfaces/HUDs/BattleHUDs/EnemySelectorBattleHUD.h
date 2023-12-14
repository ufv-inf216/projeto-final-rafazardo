//
// Created by andre on 14/12/2023.
//

#pragma once
#include "../../Interface.h"
#include "../../../Components/DrawComponents/SpriteComponent.h"

class EnemySelectorBattleHUD : public Interface {
    private:
        SpriteComponent *mSelector;
        class Battle *mBattle;

        int mTarget = 0;

    public:
        EnemySelectorBattleHUD(MyGame *game, class Battle *battle):
            Interface(game) { }

        void OnProcessInput(const Uint8 *state) override;
};

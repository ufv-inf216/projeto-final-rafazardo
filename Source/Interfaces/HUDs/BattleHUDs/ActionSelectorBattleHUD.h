

#include "../../../GameSpecific/MyGame.h"
#include "../../../GameObjects/GameObject.h"
#include "../../../GameSpecific/Battle/BattleCharacters/BattlePlayer.h"
#include "../../../Components/DrawComponents/SpriteComponent.h"

#pragma once

enum Option {
    Attack,
    Item,
    Run
};

class ActionSelectorBattleHUD : public GameObject {
    private:
        SpriteComponent *mFrame;
        SpriteComponent *mSelector;
        Option mOption = Option::Attack;
        bool mIsMovable = true;
        float mMovingDelay = 0.85f;
        float mCounter = 0;

    public:
        ActionSelectorBattleHUD(MyGame *myGame);

        void OnProcessInput(const uint8_t *state) override;

        void OnUpdate(float deltaTime) { if(!mIsMovable) mCounter += deltaTime; }
};
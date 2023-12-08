

#include "../../../GameSpecific/MyGame.h"
#include "../../../GameObjects/GameObject.h"
#include "../../../GameSpecific/Battle/BattleCharacters/BattlePlayer.h"
#include "../../../Components/DrawComponents/SpriteComponent.h"

#pragma once

enum ItemOption {
    Item1,
    Item2,
    Item3
};

class ItemSelectorBattleHUD : public GameObject {
private:
    SpriteComponent *mFrame;
    SpriteComponent *mSelector;
    ItemOption mItemOption = ItemOption::Item1;
    bool mIsMovable = true;
    float mMovingDelay = 0.85f;
    float mCounter = 0;
    BattlePlayer *mBattlePlayer;

public:
    ItemSelectorBattleHUD(MyGame *myGame, BattlePlayer *battlePlayer);

    void OnProcessInput(const uint8_t *state) override;

    void OnUpdate(float deltaTime) { if(!mIsMovable) mCounter += deltaTime; }
};
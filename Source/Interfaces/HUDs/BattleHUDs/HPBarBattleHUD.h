
#include "../../../GameSpecific/MyGame.h"
#include "../../../GameObjects/GameObject.h"
#include "../../../GameSpecific/Battle/BattleCharacters/BattlePlayer.h"
#include "../../../Components/DrawComponents/SpriteComponent.h"

#pragma once

class HPBarBattleHUD : public GameObject {
    private:
        SpriteComponent *mFrame;
        SpriteComponent *mBar;
        BattlePlayer *mBattlePlayer;

    public:
        HPBarBattleHUD(MyGame *myGame, BattlePlayer *battlePlayer);

        void OnUpdate(float deltaTime) override;
};

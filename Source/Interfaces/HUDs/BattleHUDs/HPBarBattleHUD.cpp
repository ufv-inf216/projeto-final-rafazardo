

#include "HPBarBattleHUD.h"
#define MAX_BAR_WIDTH 225

HPBarBattleHUD::HPBarBattleHUD(MyGame *myGame, BattlePlayer *battlePlayer) : GameObject(myGame){

    mFrame = new SpriteComponent(this, "../Assets/Sprites/HUDs/BattleHUD/frame.png", 257, 48);
    mFrame->SetOffset(Vector2(10, mGame->GetWindowHeight()/2 + 100));
    mBar = new SpriteComponent(this, "../Assets/Sprites/HUDs/BattleHUD/hp_bar.png", 225, 16);
    mBar->SetOffset(Vector2(26, mGame->GetWindowHeight()/2 + 116));
    mBattlePlayer = battlePlayer;
}

void HPBarBattleHUD::OnUpdate(float deltaTime) {
    mBar->SetDimensions(MAX_BAR_WIDTH * mBattlePlayer->GetHP() / mBattlePlayer->GetMaxHP(), mBar->GetDimensions().y);
}

#include "ActionSelectorBattleHUD.h"

ActionSelectorBattleHUD::ActionSelectorBattleHUD(MyGame *myGame): GameObject(myGame) {

    mFrame = new SpriteComponent(this, "../Assets/Sprites/HUDs/BattleHUD/action_frame.png", 259, 217);
    mFrame->SetOffset(Vector2(10, myGame->GetWindowHeight()/2 + 160));
    mSelector = new SpriteComponent(this, "../Assets/Sprites/HUDs/BattleHUD/selector.png", 151, 24);
    mSelector->SetOffset(Vector2(60, myGame->GetWindowHeight()/2 + 227));

    SDL_Log("%d", mState == GameObjectState::Active);
}

void ActionSelectorBattleHUD::OnProcessInput(const uint8_t *state) {

    if(mCounter >= mMovingDelay) {
        mCounter = 0;
        mIsMovable = true;
    }

    if(mIsMovable) {
        switch (mOption) {
            case Option::Attack:
                if (state[SDL_SCANCODE_S])
                    mOption = Option::Item;
                break;

            case Option::Item:
                if (state[SDL_SCANCODE_W])
                    mOption = Option::Attack;

                else if (state[SDL_SCANCODE_S])
                    mOption = Option::Run;
                break;

            case Option::Run:
                if (state[SDL_SCANCODE_W])
                    mOption = Option::Item;

                break;
        }
    }
    mIsMovable = !state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S];

    if(mOption == Option::Attack)
        mSelector->SetOffset(Vector2(60, mGame->GetWindowHeight()/2 + 227));
    else if(mOption == Option::Item)
        mSelector->SetOffset(Vector2(60, mGame->GetWindowHeight()/2 + 270));
    else
        mSelector->SetOffset(Vector2(60, mGame->GetWindowHeight()/2 + 313));
}
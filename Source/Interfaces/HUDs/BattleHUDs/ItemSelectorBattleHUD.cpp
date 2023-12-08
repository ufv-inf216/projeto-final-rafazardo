

#include "ItemSelectorBattleHUD.h"
#include "../../../GameSpecific/Battle/Battle.h"

ItemSelectorBattleHUD::ItemSelectorBattleHUD(MyGame *myGame, BattlePlayer *battlePlayer): GameObject(myGame) {

    mFrame = new SpriteComponent(this, "../Assets/Sprites/HUDs/BattleHUD/item_frame.png", 551, 176);
    mFrame->SetOffset(Vector2(280, myGame->GetWindowHeight()/2 + 200));
    mSelector = new SpriteComponent(this, "../Assets/Sprites/HUDs/BattleHUD/selector.png", 151, 24);
    mSelector->SetOffset(Vector2(320, myGame->GetWindowHeight()/2 + 290));
    mBattlePlayer = battlePlayer;
}

void ItemSelectorBattleHUD::OnProcessInput(const uint8_t *state) {

    if(mCounter >= mMovingDelay) {
        mCounter = 0;
        mIsMovable = true;
    }

    int data[3];

    if(mIsMovable) {
        switch (mItemOption) {
            case ItemOption::Item1:
                if (state[SDL_SCANCODE_D])
                    mItemOption = ItemOption::Item2;
                else if (state[SDL_SCANCODE_RETURN]) {
                    data[0] = 6;
                    data[1] = 1;
                    data[2] = 0;
                    mBattlePlayer->SetAction(new Attack("sword", mBattlePlayer->GetBattle()->GetEnemy(0), data)); //TEM QUE MUDAR AQUI OWO
                }

                break;

            case ItemOption::Item2:
                if (state[SDL_SCANCODE_A])
                    mItemOption = ItemOption::Item1;

                else if (state[SDL_SCANCODE_D])
                    mItemOption = ItemOption::Item3;

                else if (state[SDL_SCANCODE_RETURN]) {
                    data[0] = 6;
                    data[1] = 1;
                    data[2] = 1;
                    mBattlePlayer->SetAction(new Attack("bow", mBattlePlayer->GetBattle()->GetEnemy(0), data)); //TEM QUE MUDAR AQUI =D
                }
                break;

            case ItemOption::Item3:
                if (state[SDL_SCANCODE_A])
                    mItemOption = ItemOption::Item2;
                else if (state[SDL_SCANCODE_RETURN]) {
                    data[0] = 4;
                    data[1] = 1;
                    data[2] = 0;
                    mBattlePlayer->SetAction(new Attack("dagger", mBattlePlayer->GetBattle()->GetEnemy(0), data)); //TEM QUE MUDAR AQUI (͡°͜ʖ͡°)
                }

                break;
        }
    }
    mIsMovable = !state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D];

    if(mItemOption == ItemOption::Item1)
        mSelector->SetOffset(Vector2(320, mGame->GetWindowHeight()/2 + 290));
    else if(mItemOption == ItemOption::Item2)
        mSelector->SetOffset(Vector2(485, mGame->GetWindowHeight()/2 + 290));
    else
        mSelector->SetOffset(Vector2(648, mGame->GetWindowHeight()/2 + 290));
}
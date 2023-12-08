// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Battle.h"
#include "Action.h"
#include "../../Game/Random.h"
#include "../../Interfaces/HUDs/BattleHUDs/BattleHUD.h"

Battle::Battle(class MyGame *game, Player *player, Enemy *enemy):
    GameObject(game),
    mMainEnemy(enemy) {

    mFade = new Fade(mGame, .3f);

    // Allocate the player
    mBattlePlayer = new BattlePlayer(mGame, this, player);
    mBattlePlayer->Disable();

    // Allocate the enemies
    GenerateEnemies();

    // Allocate the background.
    mBattleBackground = new SpriteComponent(this, "../Assets/Sprites/Misc/battlebackground.png",
                                            mGame->GetWindowWidth(),mGame->GetWindowHeight(), 10);
    mBattleBackground->SetEnabled(false);

    int color[] = {255, 0, 0, 255};

    int pos_x = mGame->GetWindowWidth()/2 - mBattleEnemies.size()*(mBattleEnemies[0]->GetImgDims().x / 2 + 5);
    int pos_y = mGame->GetWindowHeight() / 2 - mBattleEnemies[0]->GetImgDims().y / 2;
    for(auto e : mBattleEnemies) {
        e->SetPosition(Vector2(pos_x, pos_y));

        SDL_Rect *rect = new SDL_Rect;
        rect->w = mBattleEnemies[0]->GetImgDims().x;
        rect->h = 7;
        rect->x = pos_x;
        rect->y = pos_y - 20;
        mHpBars.push_back(new DrawRectComponent(this, rect, color));

        mHpBars.back()->SetAlpha(0);

        pos_x += mBattleEnemies[0]->GetImgDims().x + 10;
    }

    // Rolls initiative for each character.
    mInitiatives[mBattlePlayer->RollInitiative()] = mBattlePlayer;
    for(auto e : mBattleEnemies) {
        int init = e->RollInitiative();
        while(mInitiatives.find(init) != mInitiatives.end()) init++;
        mInitiatives[init] = e;
        e->SetInitiative(init);
    }
    mCurrentInitiative = mInitiatives.begin();
    mIsRunning = true;

}

Battle::~Battle() {
    mMainEnemy->SetState(GameObjectState::Destroy);
    mBattlePlayer->SetState(GameObjectState::Destroy);
    for(auto enemy : mBattleEnemies) enemy->SetState(GameObjectState::Destroy);
}

void Battle::Start() {
    mGame->Pause(true);

    mGame->SetCurrentBattle(this);

    mFade->In(nullptr, GetPosition());
//    SetPosition(Vector2(0, 0));
//    mGame->GetCamera()->SetPosition(GetPosition());
    mBattleState = BattleState::Starting;

    SetPosition(Vector2(0, 0));
}

void Battle::End() {
    mIsRunning = false;

    mGame->Resume(true);

    mGame->GetCamera()->SetTarget(mGame->GetPlayer(), Vector2(12, 12));
    mGame->GetCamera()->SetWindow(60, 40);
    mGame->GetCamera()->SetScale(2.0f);

}

void Battle::OnUpdate(float deltaTime) {
    Action *action;

    for(int i=0; i<mHpBars.size(); i++) {
        mHpBars[i]->SetRectDimension(mBattleEnemies[i]->GetImgDims().x * mBattleEnemies[i]->GetHP() / mBattleEnemies[i]->GetMaxHP(), 7);
    }

    switch(mBattleState) {
        // Starting the battle with a Fade.
        case Starting:
            if(mFade->IsFadding()) return;
            if(mFade->GetFadeState() == FadeState::In) {
                mBattlePlayer->Enable();
                for(auto e : mBattleEnemies) e->Enable();
                mBattleBackground->SetEnabled(true);

                mGame->GetCamera()->SetScale(1.f);

                for(auto hp : mHpBars)
                    hp->SetAlpha(255);

                mFade->Out(false);

                mGame->GetCamera()->SetPosition(GetPosition());

                mBattleHUD = new BattleHUD(mGame, this);

            } else if(mFade->GetFadeState() == FadeState::Out) {
                mBattleState = BattleState::Running;
            }
            break;

        // The battle procedure
        case Running:

            if(!mInitiatives[mCurrentInitiative->first]) {
                mCurrentInitiative++;
                if(mCurrentInitiative == mInitiatives.end()) {
                    mCurrentInitiative = mInitiatives.begin();
                    SDL_Log("\n\n");
                }
                return;
            }

            action = mCurrentInitiative->second->GetAction();
            if(!action) return;

            action->Apply(mCurrentInitiative->second);
            delete action;

            // === FOR TESTING PURPOSES ====
            for(int i = 0; i < 1000000000; i++);

            SDL_Log("==========================");
            SDL_Log("Iniciativa: %d", mCurrentInitiative->first);
            SDL_Log("Player: %lf", mBattlePlayer->GetHP());
            for(int i = 0; i < mBattleEnemies.size(); i++) {
                SDL_Log("Enemy %d: %lf", i, mBattleEnemies[i]->GetHP());
            }
            SDL_Log("==========================");

            // === FOR TESTING PURPOSES ====

            mCurrentInitiative++;
            if(mCurrentInitiative == mInitiatives.end()) {
                mCurrentInitiative = mInitiatives.begin();
                SDL_Log("\n\n");
            }

            if(!mBattlePlayer->IsAlive()) {
                mGame->Shutdown();
                return;
            }
            for(int i = 0; i < mBattleEnemies.size(); i++)
                if(!mBattleEnemies[i]->IsAlive()) {
                    mInitiatives[mBattleEnemies[i]->GetInitiative()] = nullptr;
                    mBattleEnemies[i]->SetState(GameObjectState::Destroy);
                    mBattleEnemies.erase(mBattleEnemies.begin()+i);
                }
            if(!mBattleEnemies.size())
                mBattleState = BattleState::Ending;

            break;

        // Finishing the battle with a Fade.
        case Ending:
            if(mFade->IsFadding()) return;
            if(mFade->GetFadeState() == FadeState::In) {
                End();
                mBattleHUD->SetState(GameObjectState::Destroy);
                mFade->Out(false);
            } else if(mFade->GetFadeState() == FadeState::Out) {
                SetState(GameObjectState::Destroy);
                return;
            }

            break;
    }
}

void Battle::GenerateEnemies() {
     mBattleEnemies = std::vector<BattleEnemy*>(Random::GetIntRange(1, 1));

    for(int i = 0; i < mBattleEnemies.size(); i++) {
        mBattleEnemies[i] = new BattleEnemy(mGame, this, mMainEnemy);
        mBattleEnemies[i]->Disable();
    }
}
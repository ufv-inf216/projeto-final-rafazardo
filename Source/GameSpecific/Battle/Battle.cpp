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

    int pos_x = mGame->GetWindowWidth()/2 - 16*mBattleEnemies.size()+3;
    for(auto e : mBattleEnemies) {
        e->SetPosition(Vector2(pos_x, mGame->GetWindowHeight() / 2 - 16));
        pos_x += 38;
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
    mBattleState = BattleState::Starting;
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

    switch(mBattleState) {
        // Starting the battle with a Fade.
        case Starting:
            if(mFade->IsFadding()) return;
            if(mFade->GetFadeState() == FadeState::In) {
                mBattlePlayer->Enable();
                for(auto e : mBattleEnemies) e->Enable();
                mBattleBackground->SetEnabled(true);

                mGame->GetCamera()->SetScale(1.f);
                SetPosition(mGame->GetCamera()->GetPosition());

                mFade->Out(false);
            } else if(mFade->GetFadeState() == FadeState::Out)
                mBattleState = BattleState::Running;

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
            SDL_Log("Player: %d", mBattlePlayer->GetHP());
            for(int i = 0; i < mBattleEnemies.size(); i++) {
                SDL_Log("Enemy %d: %d", i, mBattleEnemies[i]->GetHP());
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
                mFade->Out(false);
            } else if(mFade->GetFadeState() == FadeState::Out) {
                SetState(GameObjectState::Destroy);
                return;
            }

            break;
    }
}

void Battle::GenerateEnemies() {
     mBattleEnemies = std::vector<BattleEnemy*>(Random::GetIntRange(1, 4));

    for(int i = 0; i < mBattleEnemies.size(); i++) {
        mBattleEnemies[i] = new BattleEnemy(mGame, this, mMainEnemy);
        mBattleEnemies[i]->Disable();
    }
}
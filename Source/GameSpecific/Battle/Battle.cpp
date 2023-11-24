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

Battle::Battle(class MyGame *game, Player *player, Enemy *enemy, const std::string &texturePath):
    GameObject(game),
    mMainEnemy(enemy) {

    mBattlePlayer = new BattlePlayer(mGame, this, player);
    GenerateEnemies();

    mBattleBackground = new SpriteComponent(this, texturePath, mGame->GetWindowWidth(),
                                            mGame->GetWindowHeight());

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

    for(auto val : mInitiatives)
        SDL_Log("%d", val.first);
}

Battle::~Battle() {
    mMainEnemy->SetState(GameObjectState::Destroy);
    mBattlePlayer->SetState(GameObjectState::Destroy);
    for(auto enemy : mBattleEnemies) enemy->SetState(GameObjectState::Destroy);
}

void Battle::OnUpdate(float deltaTime) {
    if(!mIsRunning) return;
    if(!mInitiatives[mCurrentInitiative->first]) {
        mCurrentInitiative++;
        if(mCurrentInitiative == mInitiatives.end()) {
            mCurrentInitiative = mInitiatives.begin();
            SDL_Log("\n\n");
        }
        return;
    }

    Action *action = mCurrentInitiative->second->GetAction();
    if(!action) return;

    action->Apply();

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

    if(!mBattlePlayer->IsAlive()) { mGame->EndBattle(); return; }
    for(int i = 0; i < mBattleEnemies.size(); i++)
        if(!mBattleEnemies[i]->IsAlive()) {
            mInitiatives[mBattleEnemies[i]->GetInitiative()] = nullptr;
            mBattleEnemies[i]->SetState(GameObjectState::Destroy);
            mBattleEnemies.erase(mBattleEnemies.begin()+i);
        }
    if(!mBattleEnemies.size()) mGame->EndBattle();
}

void Battle::GenerateEnemies() {
    Random::Seed(time(NULL));
     mBattleEnemies = std::vector<BattleEnemy*>(Random::GetIntRange(1, 4));

    for(int i = 0; i < mBattleEnemies.size(); i++)
        mBattleEnemies[i] = new BattleEnemy(mGame, this, mMainEnemy, "../Assets/Sprites/Test/test_Enemy.png");
}
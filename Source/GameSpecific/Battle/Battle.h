// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Battle module for managing and running battles.
// ----------------------------------------------------------------

#pragma once

#include "../../GameObjects/GameObject.h"
#include "BattleCharacters/BattlePlayer.h"
#include "BattleCharacters/BattleEnemy.h"
#include <map>
#include "../../Components/DrawComponents/SpriteComponent.h"
#include "../../Components/AIComponents/FSMComponent.h"

enum BattleState {
    Starting,
    Running,
    Ending
};

class Battle : public GameObject {
    private:
        BattleState mBattleState;

        FSMComponent *mFSM;

        BattlePlayer *mBattlePlayer;
        std::vector<BattleEnemy*> mBattleEnemies;
        Enemy *mMainEnemy;

        std::map<int, BattleCharacter*> mInitiatives;
        std::map<int, BattleCharacter*>::iterator mCurrentInitiative;

        SpriteComponent *mBattleBackground;

        class BattleHUD *mBattleHUD;

        void GenerateEnemies();

        bool mIsRunning = false;
        Fade *mFade;

        std::vector<DrawRectComponent*> mHpBars;

        SoundHandle battle_music;

    public:
        Battle(class MyGame *game, Player *player, Enemy *enemy);
        ~Battle();

        Enemy *GetMainEnemy() { return mMainEnemy; }

        void OnUpdate(float deltaTime) override;

        void End(); void Start();

        BattleEnemy* GetEnemy(int idx) { return mBattleEnemies[idx]; }
        BattlePlayer* GetPlayer() { return mBattlePlayer; }

        int GetNumEnemies() { return mBattleEnemies.size(); }
};

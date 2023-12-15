// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Game Specific module for storing and initializing general game
// data, such as player, npcs and current map.
// ----------------------------------------------------------------

#pragma once

#include "../Game/Game.h"
#include "Maps/Map.h"
#include "Characters/Player.h"
#include "Chest.h"
#include "Maps/Dungeons/DungeonGeneration/DungeonGenerator.h"
#include <queue>
#include "Characters/Enemy.h"
#include "../Interfaces/Fade.h"
#include "../Interfaces/Menus/MainMenu.h"
#include "../Interfaces/Menus/GameOver.h"
#include "../Game/AudioSystem.h"

class MyGame : public Game {
    private:
        // The main character
        class Player *mPlayer;

        class Battle *mCurrentBattle;

        // The map that is currently being rendered.
        class Map *mCurrentMap;

        // Chest
        //Chest *mChest;

        // Dungeons generation stuff.
        DungeonGenerator *mDungeonGenerator;
        std::queue<Dungeon*> mDungeonsQueue;

        // Initialize all game objects.
        void InitializeGameObjects() override;

        std::vector<class BattleEnemy*> GenerateEnemies(Enemy *enemy);

        // Menus dos Jogo.
        MainMenu *mMainMenu;
        GameOverScreen *mGameOverScreen;

        AudioSystem *mAudioSystem = new AudioSystem();

    public:
        // Constructor
        // @params windowWidth and windowHeight The input integers the represents the window width and height
        MyGame(int windowWidth, int windowHeight);

        void Pause(bool draw=true);
        void Resume(bool draw=true);

        // Returns the game map which is currently being rendered.
        // @return A pointer for the current map object.
        Map* GetCurrentMap() { return mCurrentMap; }
        void SetCurrentMap(Map *map) { mCurrentMap = map; }

        Player *GetPlayer() { return mPlayer; }

        //Chest* GetChest() { return mChest; }

        // Battle stuff.
        void SetCurrentBattle(Battle *battle) { mCurrentBattle = battle; }

        MainMenu* GetMainMenu() { return mMainMenu; }
        void GameOver() { mGameOverScreen->Open(); }

        void Save();

        AudioSystem* GetAudioSystem() { return mAudioSystem; }
};
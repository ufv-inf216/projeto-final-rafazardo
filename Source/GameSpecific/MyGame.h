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
#include "Characters/Crafter.h"
#include "Characters/Player.h"
#include "Chest.h"
#include "Maps/Dungeons/DungeonGeneration/DungeonGenerator.h"
#include <queue>
#include "Characters/Enemy.h"

class MyGame : public Game {
    private:
        // The main character
        class Player *mPlayer;

        class Battle *mCurrentBattle;

        // The map that is currently being rendered.
        Map *mCurrentMap;

        // The crafter NPC
        Crafter *mCrafter;

        // Chest
        //Chest *mChest;

        // Dungeons generation stuff.
        DungeonGenerator *mDungeonGenerator;
        std::queue<Dungeon*> mDungeonsQueue;

        // Initialize all game objects.
        void InitializeGameObjects() override;

        std::vector<class BattleEnemy*> GenerateEnemies(Enemy *enemy);

    public:
        // Constructor
        // @params windowWidth and windowHeight The input integers the represents the window width and height
        MyGame(int windowWidth, int windowHeight);

        // Returns the game map which is currently being rendered.
        // @return A pointer for the current map object.
        Map* GetCurrentMap() { return mCurrentMap; }

        Crafter* GetCrafter() { return mCrafter; }

        //Chest* GetChest() { return mChest; }

        // Battle stuff.
        void StartBattle(Enemy *enemy);
        void EndBattle();

        void Save();
};
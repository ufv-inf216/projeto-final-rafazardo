// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include <functional>
#include <iostream>
#include "MyGame.h"
#include "../GameSpecific/Maps/Map.h"
#include "../GameSpecific/Characters/Player.h"
#include "../GameSpecific/Characters/Enemy.h"
#include "../GameSpecific/Characters/Enemies/Bat.h"
#include "../GameSpecific/Characters/NPC.h"
#include "../GameSpecific/Characters/Crafter.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Game/Global.h"
#include "Inventory.h"
#include "Chest.h"
#include "Saver.h"
#include "../GameObjects/Trigger.h"
#include "../GameObjects/Door.h"
#include "../Components/ColliderComponents/BoxColliderComponent.h"
#include "../Components/ColliderComponents/CollisionUtils.h"
#include "Battle/Battle.h"
#include "Battle/BattleCharacters/BattlePlayer.h"
#include "Battle/BattleCharacters/BattleEnemy.h"
#include "../Game/Random.h"

// Tile dimension constant
#define TILE_SIZE 24
#define TOTAL_DUNGEON_LAYERS 4

#define TOTAL_DUNGEONS 1

MyGame::MyGame(int windowWidth, int windowHeight):
    Game(windowWidth, windowHeight) {

    mDungeonGenerator = new DungeonGenerator(this);
}

void MyGame::InitializeGameObjects() {
    Random::Seed(time(NULL));
    DefineGlobalVariables();

    // Initialize main map, loading its texture and collision matrix.
    mDungeonsQueue.push(mDungeonGenerator->Generate(1));
    mCurrentMap = mDungeonsQueue.front()->GetFirstLayer()->GetFirstRoom();

    // Allocate main character
    int a[] = {0, 0, 0, 0, 0, 0};
    Inventory *inventory = new Inventory(100);
    inventory->UpdateItems("item", 0, 1);
    inventory->UpdateItems("item", 1, 1);
    mPlayer = new Player(this, "../Assets/Sprites/Player/sprite_sheet.png",
                         "../Assets/Sprites/Player/sprite_sheet_data.json", a, inventory);
    mPlayer->SetPosition(Vector2(180, 180));

    // Set Camera settings.
    mCamera = new Camera(this, Vector2(0,0), Vector2(30*TILE_SIZE, 15*TILE_SIZE),2.f);
    mCamera->SetTarget(mPlayer, Vector2(TILE_SIZE/2, TILE_SIZE/2));
    mCamera->SetWindow(120, 100);
    mCamera->SetScale(2.0f);

    mCurrentMap->Enable();
}

void MyGame::Pause(bool draw) {
    for(auto gameobj : mGameObjects)
        gameobj->SetState(GameObjectState::Paused);
    if(!draw)
        for(auto drawable : mDrawables)
            drawable->SetIsVisible(false);
}

void MyGame::Resume(bool draw) {
    for(auto gameobj : mGameObjects)
        gameobj->SetState(GameObjectState::Active);
    if(draw)
        for(auto drawable : mDrawables)
            drawable->SetIsVisible(true);
}

void MyGame::StartBattle(Enemy *enemy) {
    Pause(false);

    mCamera->SetScale(1.0f);

    mCurrentBattle = new Battle(this, mPlayer, enemy, "../Assets/Sprites/Test/test_battle.png");
    mCurrentBattle->SetPosition(Vector2(0,0));
    mCamera->SetPosition(mCurrentBattle->GetPosition());
}

void MyGame::EndBattle() {
    mCurrentBattle->StopBattle();

    Resume(true);
    mCurrentBattle->SetState(GameObjectState::Destroy);

    mCamera->SetTarget(mPlayer, Vector2(TILE_SIZE/2, TILE_SIZE/2));
    mCamera->SetWindow(120, 100);
    mCamera->SetScale(2.0f);
}

void MyGame::Save() {
    // Salvar os dados em um arquivo
}
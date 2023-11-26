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
#define TILE_SIZE 32
#define TOTAL_DUNGEON_LAYERS 4

#define TOTAL_DUNGEONS 1

MyGame::MyGame(int windowWidth, int windowHeight):
    Game(windowWidth, windowHeight) {

    mDungeonGenerator = new DungeonGenerator(this);
}

void MyGame::InitializeGameObjects() {
    Random::Seed(time(NULL));
    DefineGlobalVariables();

    for(int i = 0; i < TOTAL_DUNGEONS; i++)
        mDungeonsQueue.push(mDungeonGenerator->Generate(TOTAL_DUNGEON_LAYERS));

    // Initialize main map, loading its texture and collision matrix.
    mCurrentMap = new Map(this, "../Assets/Sprites/Test/test_map.png",
            "../Assets/Collisions/Test/test_collision.collmat", 30*TILE_SIZE, 15*TILE_SIZE);

    // Allocate main character
    int a[] = {0, 0, 0, 0, 0, 0};
    Inventory *inventory = new Inventory(100);
    inventory->UpdateItems("item", 0, 1);
    inventory->UpdateItems("item", 1, 1);
    mPlayer = new Player(this, "../Assets/Sprites/Test/test_player.png", a, inventory);
    mPlayer->SetPosition(Vector2(448, 224));

    // Allocate NPCs.
    auto n = new NPC(this, "../Assets/Sprites/Test/test_NPC.png", a);
    n->SetPosition(Vector2(608, 64));

    // Allocate Enemy.
    auto e = new Enemy(this, "../Assets/Sprites/Test/test_Enemy.png", a);
    e->SetPosition(Vector2(480, 288));

    // Allocate Crafter
    auto c = new Crafter(this, "../Assets/Sprites/Test/test_crafter.png", a);
    c->SetPosition(Vector2(672, 64));
    mCrafter = c;

    // Allocate Chest
    auto b = new Chest(this, "../Assets/Sprites/Test/test_chest.png", inventory);
    b->SetPosition(Vector2(672, 128));

    // Allocate Save
    auto s = new Saver(this, "../Assets/Sprites/Test/test_saver.png", 32, 32, ColliderLayer::Player);
    s->SetPosition(Vector2(32, 32));

    // Allocate Trigger
    auto t = new Trigger<std::function<void()>>(this, 64, 64, ColliderLayer::Player);
    t->SetPosition(Vector2(96, 32));
    std::function<void()> funcao = []() { std::cout << "trigger acionado\n"; };
    t->SetFunction(funcao); //tem que ver isso aqui

    // Set Camera settings.
    mCamera = new Camera(this, Vector2(0,0), Vector2(30*TILE_SIZE, 15*TILE_SIZE),2.f);
    mCamera->SetTarget(mPlayer, Vector2(TILE_SIZE/2, TILE_SIZE/2));
    mCamera->SetWindow(120, 100);
    mCamera->SetScale(2.0f);

    // Allocate Door
    auto d = new Door(this, "../Assets/Sprites/Test/test_door.png", Vector2(32, 64));
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
// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Room.h"
#include <fstream>
#include "../../../Game/Json.h"
#include "../../../Game/Random.h"
#include "../../Characters/Enemies/Bat.h"
#include "../../../GameObjects/Door.h"
#include "../../../Game/Global.h"

#define TOP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Room::Room(class MyGame *game, const std::string &jsonPath): Map(game) {
    mConnectedRooms = { nullptr, nullptr, nullptr, nullptr };

    std::ifstream json(jsonPath);
    nlohmann::json jsonData = nlohmann::json::parse(json);

    int pos = Random::GetIntRange(0, 3);

    // Set map dimensions.
    mWidth = jsonData[pos]["width"]; mHeight = jsonData[pos]["height"];
    mWidth *= 24;
    mHeight *= 24;

    // Set map components.
    mSpriteComponent = new SpriteComponent(this, jsonData[pos]["dirImg"], mWidth, mHeight, 0);
    mCollisionMatrixComponent = new CollisionMatrixComponent(this, jsonData[pos]["dirColl"]);

    // All maps will be placed on (0, 0)
    mPosition = Vector2(0,0);

    // Setting doors positions.
    mDoorTop = 24 * Vector2(jsonData[pos]["doors"][0], jsonData[pos]["doors"][1]);
    mDoorDown = 24 * Vector2(jsonData[pos]["doors"][2], jsonData[pos]["doors"][3]);
    mDoorRight = 24 * Vector2(jsonData[pos]["doors"][4], jsonData[pos]["doors"][5]);
    mDoorLeft = 24 * Vector2(jsonData[pos]["doors"][6], jsonData[pos]["doors"][7]);

    // Setting areas vertices.
    auto v1 = Vector2(jsonData[pos]["areas"][0], jsonData[pos]["areas"][1]);
    mArea1 = { v1, v1 + Vector2(jsonData[pos]["areas"][2], jsonData[pos]["areas"][3]) };

    auto v2 = Vector2(jsonData[pos]["areas"][4], jsonData[pos]["areas"][5]);
    mArea2 = { v2, v2 + Vector2(jsonData[pos]["areas"][6], jsonData[pos]["areas"][7]) };

    auto v3 = Vector2(jsonData[pos]["areas"][8], jsonData[pos]["areas"][9]);
    mArea3 = { v3, v3 + Vector2(jsonData[pos]["areas"][10], jsonData[pos]["areas"][11]) };

    auto v4 = Vector2(jsonData[pos]["areas"][12], jsonData[pos]["areas"][13]);
    mArea4 = { v4, v4 + Vector2(jsonData[pos]["areas"][14], jsonData[pos]["areas"][15]) };
}

void Room::Connect(Room *other, ConnectionSide connection) {

    Door *door;

    switch(connection) {
        case ConnectionSide::Top:
            mConnectedRooms[TOP] = other;
            door = new Door(mGame, "../Assets/Sprites/Misc/door.png", mDoorTop,
                            other->GetDoorPosition(ConnectionSide::Down) - Vector2(0, 24));
            AddGameObject(door);
            break;
        case ConnectionSide::Down:
            mConnectedRooms[DOWN] = other;
            door = new Door(mGame, "../Assets/Sprites/Misc/door.png", mDoorDown,
                            other->GetDoorPosition(ConnectionSide::Top) + Vector2(0, 48));
            AddGameObject(door);
            break;
        case ConnectionSide::Right:
            mConnectedRooms[RIGHT] = other;
            door = new Door(mGame, "../Assets/Sprites/Misc/door.png", mDoorRight,
                            other->GetDoorPosition(ConnectionSide::Left) + Vector2(24, 0));
            AddGameObject(door);
            break;
        case ConnectionSide::Left:
            mConnectedRooms[LEFT] = other;
            door = new Door(mGame, "../Assets/Sprites/Misc/door.png", mDoorLeft,
                            other->GetDoorPosition(ConnectionSide::Right) - Vector2(24, 0));
            AddGameObject(door);
            break;
        default:
            break;
    }
    door->Disable();
    door->SetNextMap(other);
}

Vector2 Room::GetDoorPosition(ConnectionSide side) {
    switch(side) {
        case ConnectionSide::Top: return mDoorTop;
        case ConnectionSide::Down: return mDoorDown;
        case ConnectionSide::Right: return mDoorRight;
        case ConnectionSide::Left: return mDoorLeft;
    }

    return Vector2(0, 0);
}

Room *Room::GetNextRoom(ConnectionSide side) {
    switch(side) {
        case ConnectionSide::Top:
            return mConnectedRooms[TOP];
        case ConnectionSide::Down:
            return mConnectedRooms[DOWN];
        case ConnectionSide::Right:
            return mConnectedRooms[RIGHT];
        case ConnectionSide::Left:
            return mConnectedRooms[LEFT];
    }

    return nullptr;
}

void Room::Print() {
    int cnt = 0;
    for(auto room : mConnectedRooms) {
        if(room)
            cnt++;
    }
    SDL_Log("Room: %d", cnt);
}

void Room::Initialize(bool enable) {
    if(Random::GetIntRange(0, 1)) {
        auto enemy = GenerateRandomEnemy(mGame);
        enemy->SetPosition(Vector2(Random::GetIntRange(mArea1.first.x, mArea1.second.x)*24,
                                      Random::GetIntRange(mArea1.first.y, mArea1.second.y)*24));
        AddGameObject(enemy);
    }
    if(Random::GetIntRange(0, 1)) {
        auto enemy = GenerateRandomEnemy(mGame);
        enemy->SetPosition(Vector2(Random::GetIntRange(mArea2.first.x, mArea2.second.x)*24,
                                 Random::GetIntRange(mArea2.first.y, mArea2.second.y)*24));
        AddGameObject(enemy);
    }
    if(Random::GetIntRange(0, 1)) {
        auto enemy = GenerateRandomEnemy(mGame);
        enemy->SetPosition(Vector2(Random::GetIntRange(mArea3.first.x, mArea3.second.x)*24,
                                 Random::GetIntRange(mArea3.first.y, mArea3.second.y)*24));
        AddGameObject(enemy);
    }
    if(Random::GetIntRange(0, 1)) {
        auto enemy = GenerateRandomEnemy(mGame);
        enemy->SetPosition(Vector2(Random::GetIntRange(mArea4.first.x, mArea4.second.x)*24,
                                 Random::GetIntRange(mArea4.first.y, mArea4.second.y)*24));
        AddGameObject(enemy);
    }

    if(!enable) Disable();
}
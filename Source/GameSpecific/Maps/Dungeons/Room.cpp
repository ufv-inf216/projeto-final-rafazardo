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

    mDoorTop = 24 * Vector2(jsonData[pos]["doors"][0], jsonData[pos]["doors"][1]);
    mDoorDown = 24 * Vector2(jsonData[pos]["doors"][2], jsonData[pos]["doors"][3]);
    mDoorRight = 24 * Vector2(jsonData[pos]["doors"][4], jsonData[pos]["doors"][5]);
    mDoorLeft = 24 * Vector2(jsonData[pos]["doors"][6], jsonData[pos]["doors"][7]);
}

void Room::Connect(Room *other, ConnectionSide connection) {

    Door *door;

    switch(connection) {
        case ConnectionSide::Top:
            mConnectedRooms[TOP] = other;
            door = new Door(mGame, "../Assets/Sprites/Misc/door.png", mDoorTop, Vector2(180, 180));
            AddGameObject(door);
            break;
        case ConnectionSide::Down:
            mConnectedRooms[DOWN] = other;
            door = new Door(mGame, "../Assets/Sprites/Misc/door.png", mDoorDown, Vector2(180, 180));
            AddGameObject(door);
            break;
        case ConnectionSide::Right:
            mConnectedRooms[RIGHT] = other;
            door = new Door(mGame, "../Assets/Sprites/Misc/door.png", mDoorRight, Vector2(180, 180));
            AddGameObject(door);
            break;
        case ConnectionSide::Left:
            mConnectedRooms[LEFT] = other;
            door = new Door(mGame, "../Assets/Sprites/Misc/door.png", mDoorLeft, Vector2(180, 180));
            AddGameObject(door);
            break;
        default:
            break;
    }
    door->Disable();
    door->SetNextMap(other);
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
    int a[] = {0, 0, 0, 0, 0, 0};
    auto bat = new Bat(mGame, a);
    bat->SetPosition(Vector2(210, 210));
    AddGameObject(bat);

    if(!enable)
        Disable();
}
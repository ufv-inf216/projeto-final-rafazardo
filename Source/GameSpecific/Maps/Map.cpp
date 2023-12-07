// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Map.h"
#include "../../Game/Game.h"

Map::Map(class MyGame *game, const std::string &texturePath, const std::string &collisionPath, int width, int height):
    GameObject(game) {

    // Set map dimensions.
    mWidth = width; mHeight = height;

    // Set map components.
    mSpriteComponent = new SpriteComponent(this, texturePath, width, height, 0);
    mCollisionMatrixComponent = new CollisionMatrixComponent(this, collisionPath);

    // All maps will be placed on (0, 0)
    mPosition = Vector2(0,0);
}
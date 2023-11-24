// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Spawner.h"
#include "../Game/Game.h"

const float GOOMBA_FORWARD_SPEED = 100.0f;

Spawner::Spawner(MyGame* game, float spawnDistance)
        : GameObject(game)
        , mSpawnDistance(spawnDistance) { }

void Spawner::OnUpdate(float deltaTime) {

}
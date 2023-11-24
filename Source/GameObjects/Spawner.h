// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Spawner module for allocating Game Objects in game.
// ----------------------------------------------------------------

#pragma once

#include "GameObject.h"

class Spawner : public GameObject {
    private:
        // The distance that the spawner must be from player to spawn a
        // GameObject
        float mSpawnDistance;

    public:
        explicit Spawner(MyGame* game, float spawnDistance);

        void OnUpdate(float deltaTime) override;
};

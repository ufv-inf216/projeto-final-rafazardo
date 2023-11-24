// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "DungeonGenerator.h"
#include <fstream>
#include <climits>

#include <iostream>

// For pseudorandom generation stuff
#include "../../../../Game/Random.h"
#include <ctime>

DungeonGenerator::DungeonGenerator(class MyGame *game):
    mGame(game) {}

Dungeon* DungeonGenerator::Generate(int total_layers) {
    Dungeon *dungeon;
    Layer *curr = nullptr, *first = nullptr;

    char **grid; Coord start, end;
    int gw = Random::GetIntRange(7, 12),
        gh = Random::GetIntRange(7, 12);

    Random::Seed(abs(time(NULL)));
    grid = GenerateLayerGrid(gw, gh, start, end);
    first = curr = GenerateLayer(grid, gw, gh, start, end, nullptr);

    for(int j = 0; j < gh; j++) delete grid[j];
    delete[] grid;

    for(int i = 1; i < total_layers; i++) {
        Random::Seed(abs(time(NULL)*(i+1)));
        grid = GenerateLayerGrid(gw, gh, start, end);
        curr = GenerateLayer(grid, gw, gh, start, end, curr);

        for(int j = 0; j < gh; j++) delete grid[j];
        delete[] grid;
    }
    dungeon = new Dungeon(mGame, first, curr);

    return dungeon;
}
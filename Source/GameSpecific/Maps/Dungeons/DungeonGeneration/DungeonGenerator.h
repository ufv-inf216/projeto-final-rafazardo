// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// DungeonGenerator module for creating a procedural dungeon.
// ----------------------------------------------------------------

#pragma once

#include "../Dungeon.h"
#include <map>

#define Coord std::pair<int, int>

class DungeonGenerator {
    private:
        // The current Game.
        class MyGame *mGame;

        // === MAP GENERATION ===
        // Generates a grid for a procedural Dungeon Layer
        // @param gridWidth and gridHeight Grid dimensions.
        // @param V A reference to an integer that will represent the number of
        //          vertices in the final graph.
        // @return A two-dimentional array that represents a grid.
        char** GenerateLayerGrid(int gridWidth, int gridHeight, Coord &cstart, Coord &cend);

        // Generates a procedural Dungeon Layer
        // @param grid The source grid
        // @param gridWidth and gridHeight Grid dimensions.
        // @param V The number of allocated rooms
        // @param prev The previous layer.
        // @return A pointer to the generated layer.
        Layer* GenerateLayer(char **grid, int gridWidth, int gridHeight, Coord &start, Coord &end, Layer* prev);

        // === END OF MAP GENERATION METHODS ===

    public:
        // Constructor
        // @params game The current game
        DungeonGenerator(class MyGame *game);

        // Generates a procedural Dungeon
        // @params total_layers The number of layers to this dungeon.
        // @return A pointer to the procedural generated dungeon.
        Dungeon* Generate(int total_layers);
};
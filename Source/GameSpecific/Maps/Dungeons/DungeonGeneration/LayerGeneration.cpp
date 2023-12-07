// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "DungeonGenerator.h"
#include "iostream"
#include "../../../../Game/Random.h"

#define x first
#define y second

std::string tpaths[] = {
        "../Assets/Sprites/DungeonMaps/Sq/sq18_18.png",
        "../Assets/Sprites/DungeonMaps/Sq/sq20_20.png",
};

std::string cpaths[] = {
        "../Assets/Collisions/Dungeons/sq18_18.collmat",
        "../Assets/Collisions/Dungeons/sq20_20.collmat",
};

Layer* DungeonGenerator::GenerateLayer(char **grid, int gridWidth, int gridHeight, Coord &start, Coord &end, Layer* prev) {
    std::map<Coord, Room*> coord2room;

    std::cout << "==============================\n";
    for(int i = 0; i < gridHeight; i++) {
        for (int j = 0; j < gridWidth; j++)
            std::cout << grid[i][j] << " ";
        std::cout << "\n";
    }
    std::cout << "\n\n";
    std::cout << "==============================\n\n";

    // Create a Room object for each '1' char on the grid.
    for(int i = 0; i < gridHeight; i++)
        for (int j = 0; j < gridWidth; j++) {
            if(grid[i][j] != '1') continue;
            int idx = Random::GetIntRange(0, 1);
            coord2room[{i, j}] = new Room(mGame, tpaths[idx], cpaths[idx],
                                          18*24, 18*24);
        }

    int t, b, r, l;
    for(int i = 0; i < gridHeight; i++)
        for (int j = 0; j < gridWidth; j++) {
            if(grid[i][j] != '1') continue;
            r = l = j;
            t = b = i;

            while(--t > 1) {
                if(grid[t][j] == '0') break;
                if(grid[t][j] == '1') {
                    coord2room[{i, j}]->Connect(coord2room[{t, j}], ConnectionSide::Top);
                    break;
                }
            }
            while(++b < gridHeight) {
                if(grid[b][j] == '0') break;
                if(grid[b][j] == '1') {
                    coord2room[{i, j}]->Connect(coord2room[{b, j}], ConnectionSide::Down);
                    break;
                }
            }

            while(--l > -1) {
                if(grid[i][l] == '0') break;
                if(grid[i][l] == '1') {
                    coord2room[{i, j}]->Connect(coord2room[{i, l}], ConnectionSide::Left);
                    break;
                }
            }
            while(++r < gridWidth) {
                if(grid[i][r] == '0') break;
                if(grid[i][r] == '1') {
                    coord2room[{i, j}]->Connect(coord2room[{i, r}], ConnectionSide::Right);
                    break;
                }
            }
        }

    Layer *layer = new Layer(mGame, prev, coord2room[start], coord2room[end]);

    return layer;
}
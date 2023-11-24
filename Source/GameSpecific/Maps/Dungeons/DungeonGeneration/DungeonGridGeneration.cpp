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

char** DungeonGenerator::GenerateLayerGrid(int gridWidth, int gridHeight, Coord &cstart, Coord &cend) {
    // === PROCEDURAL DUNGEON GENEARTION: 1ST STEP ===
    // This step consists in defining a starting and ending point for the layer. Also, we
    // define a middle point, so we can get more interesting shapes.
    int start, end, mid;

    char **grid = new char*[gridHeight];
    for(int i = 0; i < gridHeight; i++) {
        grid[i] = new char[gridWidth];
        for (int j = 0; j < gridWidth; j++)
            grid[i][j] = '0';
    }

    // Finally, choose then.
    start = Random::GetIntRange(0, gridWidth-1); grid[gridHeight-1][start] = '1';
    mid = Random::GetIntRange(0, gridWidth-1);   grid[gridHeight/2][mid] = '1';
    end = Random::GetIntRange(0, gridWidth-1);   grid[0][end] = '1';

    cstart = {gridHeight-1, start};
    cend = {0, end};

    // === END OF 1ST STEP ===


    // === PROCEDURAL DUNGEON GENEARTION: 2ND STEP ===
    // Now, the objective is to find cells that build a path between the start and ending
    // points, and contains the middle one.
    int row = gridHeight-1, col = start, new_row, new_col;

    // First, create a path between the first point and the middle one.
    while((row != gridHeight/2) && (col != mid)) {
        if(Random::GetIntRange(0, 1)) {                              // If it's true, then change column
            if (col < mid) new_col = Random::GetIntRange(col+1, mid);
            else if(col > mid) new_col = Random::GetIntRange(mid, col-1);
            else new_col = col;

            for(int k = fmin(col, new_col)+1; k < fmax(col, new_col); k++)
                grid[row][k] = '*';

            col = new_col;
        } else {
            new_row = Random::GetIntRange(gridHeight/2, row-1);     // Else, change its row.

            for(int k = new_row+1; k < row; k++)
                grid[k][col] = '*';

            row = new_row;
        }

        grid[row][col] = '1';
    }
    for(int k = fmin(col, mid)+1; k < fmax(col, mid); k++)
        grid[row][k] = '*';
    for(int k = gridHeight/2+1; k < row; k++)
        grid[k][col] = '*';

    // Now, define a path between the middle point and the ending one.
    row = gridHeight/2; col = mid;

    while(row && (col != end)) {
        if(Random::GetIntRange(0, 1) & (row - gridHeight/2)) {
            if (col < end) new_col = Random::GetIntRange(col+1, end);
            else if(col > end) new_col = Random::GetIntRange(end, col-1);
            else col = end;

            for(int k = fmin(col, new_col)+1; k < fmax(col, new_col); k++)
                grid[row][k] = '*';

            col = new_col;
        } else {
            new_row = Random::GetIntRange(0, row - 1);

            for(int k = new_row+1; k < row; k++)
                grid[k][col] = '*';

            row = new_row;
        }

        grid[row][col] = '1';
    }
    for(int k = fmin(col, end)+1; k < fmax(col, end); k++)
        grid[row][k] = '*';
    for(int k = 1; k < row; k++)
        grid[k][col] = '*';

    // === END OF 2ND STEP ===


    // === PROCEDURAL DUNGEON GENEARTION: 3RD STEP ===
    // Finally, we add some loops and extra rooms to te dungeon. Since we don't want to add
    // shortcuts, we won't create loops by using the set of points chosen.
    int x, y, tries = 20;

    while(tries--) {
        x = Random::GetIntRange(0, gridWidth-1);
        y = Random::GetIntRange(2, gridHeight-1);
        if(grid[y][x] != '0') continue;

        // === TRYING VERTICAL CONNECTIONS ===
        // Top connection.
        for(int k = y-1; k > 1; k--) {
            if(grid[k][x] == '1') {
                if(Random::GetIntRange(0, 1)) {
                    for (int c = k + 1; c < y; c++)
                        grid[c][x] = '*';
                    grid[y][x] = '1';
                }
                break;
            }
            else if(grid[k][x] == '*') break;
        }

        // Bottom Connection.
        for(int k = y+1; k < gridHeight; k++) {
            if(grid[k][x] == '1') {
                if(Random::GetIntRange(0, 1)) {
                    for (int c = y + 1; c < k; c++)
                        grid[c][x] = '*';
                    grid[y][x] = '1';
                }
                break;
            }
            else if(grid[k][x] == '*') break;
        }

        // === END OF VERTICAL CONNECTIONS ===

        // === TRYING A HORIZONTAL CONNECTIONS ===
        // Left connection.
        for(int k = x-1; k > 0; k--) {
            if(grid[y][k] == '1') {
                if(Random::GetIntRange(0, 1)) {
                    for (int c = k + 1; c < x; c++)
                        grid[y][c] = '*';
                    grid[y][x] = '1';
                }
                break;
            }
            else if(grid[y][k] == '*') break;
        }

        // Right connection.
        for(int k = x+1; k < gridWidth; k++) {
            if(grid[y][k] == '1') {
                if(Random::GetIntRange(0, 1)) {
                    for (int c = x + 1; c < k; c++)
                        grid[y][c] = '*';
                    grid[y][x] = '1';
                }
                break;
            }
            else if(grid[y][k] == '*') break;
        }

        // === END OF HORIZONTAL CONNECTIONS ===
    }

    // === END OF 3RD STEP ===

    return grid;
}
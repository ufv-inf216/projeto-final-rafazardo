// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "CollisionMatrixComponent.h"
#include "BoxColliderComponent.h"
#include "../../Game/Math.h"
#include <string>
#include <fstream>
#include "../../GameObjects/GameObject.h"
#include <iostream>

CollisionMatrixComponent::CollisionMatrixComponent(class GameObject *owner, const std::string &path, int cellSize):
    Component(owner),
    mCellSize(cellSize) {

    std::ifstream fin(path);

    if(!fin.is_open())
        SDL_Log("Unable to open matrix file");

    bool value;
    int numRows, numColumns;
    fin >> numRows >> numColumns;
    mMatrix = std::vector<std::vector<bool>>(numRows, std::vector<bool>(numColumns));

    for(int i=0; i<numRows; i++)
        for (int j = 0; j < numColumns; j++) {
            fin >> value;
            mMatrix[i][j] = value;
        }

    fin.close();
}

Vector2 CollisionMatrixComponent::ResolveCollision(std::vector<Vector2> &vertices) {
    // If v1 is perfectly on grid, then we need to ajust v2, v3 and v4 cells.
    bool onGridY = (int)(vertices[0].y/mCellSize) == (vertices[0].y/mCellSize),
         onGridX = (int)(vertices[0].x/mCellSize) == (vertices[0].x/mCellSize);

    Vector2 v1 = Vector2((int)(vertices[0].y/mCellSize), (int)(vertices[0].x/mCellSize));
    Vector2 v2 = Vector2((int)(vertices[1].y/mCellSize), (int)(vertices[1].x/mCellSize)-onGridX);
    Vector2 v3 = Vector2((int)(vertices[2].y/mCellSize)-onGridY, (int)(vertices[2].x/mCellSize));
    Vector2 v4 = Vector2((int)(vertices[3].y/mCellSize)-onGridY, (int)(vertices[3].x/mCellSize)-onGridX);

    // Left and Top collision...
    if(mMatrix[v1.x][v1.y]) return Vector2(vertices[0].x-(v1.y+1)*mCellSize,vertices[0].y-(v1.x+1)*mCellSize);

    // Right and Top collision...
    if(mMatrix[v2.x][v2.y]) return Vector2(vertices[1].x-(v2.y)*mCellSize,vertices[1].y-(v2.x+1)*mCellSize);

    // Left and Down collisions...
    if(mMatrix[v3.x][v3.y]) return Vector2(vertices[2].x-(v3.y+1)*mCellSize,vertices[2].y-(v3.x*mCellSize));

    // Right and Down collisions...
    if(mMatrix[v4.x][v4.y]) return Vector2(vertices[3].x-(v4.y)*mCellSize,vertices[3].y-(v4.x*mCellSize));

    return Vector2(0, 0);
}
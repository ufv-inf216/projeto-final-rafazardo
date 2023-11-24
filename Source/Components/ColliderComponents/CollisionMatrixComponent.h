// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// Collision Matrix module for implementing a binary matrix which
// defines whether there is a collision or not.
// ----------------------------------------------------------------

#pragma once
#include "../Component.h"
#include "SDL.h"
#include "../../Game/Math.h"
#include <vector>
#include <string>
#include "CollisionUtils.h"

class CollisionMatrixComponent : public Component {
    private:
        // Collision matrix.
        std::vector<std::vector<bool>> mMatrix;

        // Dimension of each cell.
        int mCellSize;

    public:
        // TextureComponent's constructor.
        // @param owner The actor that owns the component.
        // @param path The path to the matrix file.
        CollisionMatrixComponent(class GameObject *owner, const std::string &path, int cellSize = 32);

        // Resolve a collision for a given vertices vector from a box collider component
        // @param The vector of vertices v1, v2, v3 and v4.
        // @return A Vector2 storing the collision resolution in x and y.
        Vector2 ResolveCollision(std::vector<Vector2> &vertices);
};

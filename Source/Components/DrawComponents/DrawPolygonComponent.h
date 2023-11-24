// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Lucas N. Ferreira, Pedro Fiorio and Rafael
// Crevelari.
//
// Created: October, 2023
// Draw a polygon, mainly for debbuging.
// ----------------------------------------------------------------

#pragma once
#include "DrawComponent.h"

class DrawPolygonComponent : public DrawComponent {
    public:
        // (Lower draw order corresponds with further back)
        DrawPolygonComponent(class GameObject* owner, std::vector<Vector2> &vertices, int drawOrder = 100);

        void Draw(SDL_Renderer* renderer) override;
        std::vector<Vector2>& GetVertices() { return mVertices; }
    protected:
        int mDrawOrder;
        std::vector<Vector2> mVertices;
};
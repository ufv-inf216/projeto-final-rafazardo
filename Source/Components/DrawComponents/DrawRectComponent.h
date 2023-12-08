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

class DrawRectComponent : public DrawComponent {
    public:
        // (Lower draw order corresponds with further back)
        DrawRectComponent(class GameObject* owner, SDL_Rect *rect, int color[4], int drawOrder = 100);

        void SetRectPosition(Vector2 pos) { mRect->x = pos.x; mRect->y = pos.y; }
        void SetRectDimension(int width, int height) { mRect->w = width; mRect->h = height; }
        void SetAlpha(int alpha) { mColor[3] = alpha; }

        void Draw(SDL_Renderer* renderer) override;

        Vector2 GetRectDimentions() { return Vector2(mRect->w, mRect->h); }

    protected:
        int mDrawOrder;

        SDL_Rect *mRect;
        int mColor[4];
};
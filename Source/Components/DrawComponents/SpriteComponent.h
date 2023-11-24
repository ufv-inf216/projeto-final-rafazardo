// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Lucas N. Ferreira, Pedro Fiorio and Rafael
// Crevelari.
//
// Created: October, 2023
// Sprite Component module defining data for rendering sprites.
// ----------------------------------------------------------------

#pragma once
#include "DrawComponent.h"
#include <string>

class SpriteComponent : public DrawComponent {
    public:
        // (Lower draw order corresponds with further back)
        SpriteComponent(class GameObject* owner, const std::string &texturePath, int width = 0, int height = 0,
                        int drawOrder = 100);

        void Draw(SDL_Renderer* renderer) override;

    protected:
        // Map of textures loaded
        SDL_Texture* mSpriteSheetSurface;

        int mWidth;
        int mHeight;
};
// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Lucas N. Ferreira, Pedro Fiorio and Rafael
// Crevelari.
//
// Created: October, 2023
// Draw Component module for defining the basic structure for drawer
// components.
// ----------------------------------------------------------------

#pragma once
#include "../Component.h"
#include "../../Game/Math.h"
#include <vector>
#include <SDL.h>

class DrawComponent : public Component {
    public:
        // (Lower draw order corresponds with further back)
        explicit DrawComponent(class GameObject* owner, int drawOrder = 100);
        ~DrawComponent() override;

        virtual void Draw(SDL_Renderer* renderer);

        bool IsVisible() const { return mIsVisible; }
        void SetIsVisible(const bool isVisible) { mIsVisible = isVisible; }

        int GetDrawOrder() const { return mDrawOrder; }

    protected:
        bool mIsVisible;
        int mDrawOrder;
};

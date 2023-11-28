//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "DrawRectComponent.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameSpecific/MyGame.h"

DrawRectComponent::DrawRectComponent(class GameObject* owner, SDL_Rect *rect, int color[4], int drawOrder)
        :DrawComponent(owner)
        ,mRect(rect)
        ,mDrawOrder(drawOrder) {

    mColor[0] = color[0]; mColor[1] = color[1];
    mColor[2] = color[2]; mColor[3] = color[3];
    SDL_SetRenderDrawBlendMode(mOwner->GetGame()->GetRenderer(), SDL_BLENDMODE_BLEND);
}

void DrawRectComponent::Draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, mColor[0], mColor[1], mColor[2], mColor[3]);
    SDL_RenderFillRect(renderer, mRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
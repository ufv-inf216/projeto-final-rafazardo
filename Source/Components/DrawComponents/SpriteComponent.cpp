//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "SpriteComponent.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameSpecific/MyGame.h"

SpriteComponent::SpriteComponent(class GameObject* owner, const std::string &texturePath, const int width, const int height, const int drawOrder)
        :DrawComponent(owner, drawOrder)
        ,mWidth(width)
        ,mHeight(height) {

    this->mSpriteSheetSurface = this->mOwner->GetGame()->LoadTexture(texturePath);
    if(!this->mSpriteSheetSurface) SDL_Log("Couldn't load texture");
}

void SpriteComponent::Draw(SDL_Renderer *renderer) {
    Vector2 pos = mOwner->GetPosition();
    Vector2 cam_pos = this->mOwner->GetGame()->GetCamera()->GetPosition();

    SDL_Rect dstrect;
    dstrect.w = this->mWidth; dstrect.h = this->mHeight;
    dstrect.x = pos.x-cam_pos.x; dstrect.y = pos.y-cam_pos.y;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(this->mOwner->GetRotation() == Math::Pi)
        flip = SDL_FLIP_HORIZONTAL;

    SDL_RenderCopyEx(renderer, this->mSpriteSheetSurface, nullptr, &dstrect,
                     .0f, nullptr, flip);
}
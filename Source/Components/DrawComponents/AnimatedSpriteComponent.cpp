//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "AnimatedSpriteComponent.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameSpecific/MyGame.h"
#include "../../Game/Json.h"
#include <fstream>

AnimatedSpriteComponent::AnimatedSpriteComponent(class GameObject* owner, const std::string &spriteSheetPath, const std::string &spriteSheetData, int drawOrder)
        : SpriteComponent(owner, spriteSheetPath, 0, 0, drawOrder)
{
    LoadSpriteSheet(spriteSheetPath, spriteSheetData);
}

AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
    for (const auto& rect : mSpriteSheetData)
    {
        delete rect;
    }
    mSpriteSheetData.clear();
}

void AnimatedSpriteComponent::LoadSpriteSheet(const std::string& texturePath, const std::string& dataPath)
{
    // Load sprite sheet texture
    mSpriteSheetSurface = mOwner->GetGame()->LoadTexture(texturePath);
    if(!mSpriteSheetSurface) SDL_Log("Couldn't open Sprite Sheet");

    // Load sprite sheet data
    std::ifstream spriteSheetFile(dataPath);
    nlohmann::json spriteSheetData = nlohmann::json::parse(spriteSheetFile);

    SDL_Rect* rect = nullptr;
    for(const auto& frame : spriteSheetData["frames"]) {

        int x = frame["frame"]["x"].get<int>();
        int y = frame["frame"]["y"].get<int>();
        int w = frame["frame"]["w"].get<int>();
        int h = frame["frame"]["h"].get<int>();
        rect = new SDL_Rect({x, y, w, h});

        mSpriteSheetData.emplace_back(rect);
    }
}

void AnimatedSpriteComponent::Draw(SDL_Renderer *renderer) {

    if(!mIsEnabled) return;

    int spriteIdx = this->mAnimations[mAnimName][(int)this->mAnimTimer];

    Vector2 pos = mOwner->GetPosition();
    Vector2 cam_pos = this->mOwner->GetGame()->GetCamera()->GetPosition();

    SDL_Rect dstrect;
    dstrect.w = 24; dstrect.h = 24;
    dstrect.x = pos.x-cam_pos.x; dstrect.y = pos.y-cam_pos.y;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(this->mOwner->GetRotation() == Math::Pi)
        flip = SDL_FLIP_HORIZONTAL;

    SDL_RenderCopyEx(renderer, this->mSpriteSheetSurface, mSpriteSheetData[spriteIdx], &dstrect,
                     .0f, nullptr, flip);
}

void AnimatedSpriteComponent::Update(float deltaTime) {
    if(this->mIsPaused) return;

    this->mAnimTimer += this->mAnimFPS*deltaTime;

    if(this->mAnimTimer >= mAnimations[mAnimName].size()) this->mAnimTimer = 0;
}

void AnimatedSpriteComponent::SetAnimation(const std::string& name) {
    this->mAnimName = name;
    this->Update(0);
}

void AnimatedSpriteComponent::AddAnimation(const std::string& name, const std::vector<int>& spriteNums) {
    mAnimations.emplace(name, spriteNums);
}

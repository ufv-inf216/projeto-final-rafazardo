// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Lucas N. Ferreira, Pedro Fiorio and Rafael
// Crevelari.
//
// Created: October, 2023
// Sprite Component module defining data for rendering animated
// sprites.
// ----------------------------------------------------------------

#pragma once

#include "SpriteComponent.h"
#include <unordered_map>

class AnimatedSpriteComponent : public SpriteComponent {
public:
    // (Lower draw order corresponds with further back)
    AnimatedSpriteComponent(class GameObject* owner, const std::string &spriteSheetPath,
                            const std::string &spriteSheetData, int drawOrder = 100);
    ~AnimatedSpriteComponent() override;

    void Draw(SDL_Renderer* renderer) override;
    void Update(float deltaTime) override;

    // Use to change the FPS of the animation
    void SetAnimFPS(float fps) { mAnimFPS = fps; }

    // Set the current active animation
    void SetAnimation(const std::string& name);

    // Use to pause/unpause the animation
    void SetIsPaused(bool pause) { mIsPaused = pause; }

    // Add an animation of the corresponding name to the animation map
    void AddAnimation(const std::string& name, const std::vector<int>& images);

private:
    void LoadSpriteSheet(const std::string& texturePath, const std::string& dataPath);

    // Vector of sprites
    std::vector<SDL_Rect*> mSpriteSheetData;

    // Map of animation name to vector of textures corresponding to the animation
    std::unordered_map<std::string, std::vector<int>> mAnimations;

    // Name of current animation
    std::string mAnimName;

    // Tracks current elapsed time in animation
    float mAnimTimer = 0.0f;

    // The frames per second the animation should run at
    float mAnimFPS = 10.0f;

    // Whether or not the animation is paused (defaults to false)
    bool mIsPaused = false;
};

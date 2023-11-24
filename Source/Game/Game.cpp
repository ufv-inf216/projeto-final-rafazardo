// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "SDL_image.h"
#include "Random.h"
#include "Game.h"
#include "../GameObjects/GameObject.h"
#include "../Components/DrawComponents/DrawComponent.h"
#include "../GameObjects/Spawner.h"

Game::Game(int windowWidth, int windowHeight)
        :mWindow(nullptr)
        ,mRenderer(nullptr)
        ,mTicksCount(0)
        ,mIsRunning(true)
        ,mUpdatingGameObjects(false)
        ,mWindowWidth(windowWidth)
        ,mWindowHeight(windowHeight) { }

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("P4: Super Mario Bros", 150, 40, mWindowWidth, mWindowHeight, 0);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    Random::Init();

    mTicksCount = SDL_GetTicks();

    // Init all game gameObjects
    InitializeGameObjects();

    return true;
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
        switch (event.type) {
            case SDL_QUIT:
                Quit();
                break;
        }

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    for (auto gameObject : mGameObjects)
        gameObject->ProcessInput(state);
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    deltaTime = deltaTime > 0.05f? 0.05f : deltaTime;

    mTicksCount = SDL_GetTicks();

    // Update all gameObjects and pending gameObjects
    UpdateGameObjects(deltaTime);
}

void Game::UpdateGameObjects(float deltaTime) {
    mUpdatingGameObjects = true;
    for (auto gameObject : mGameObjects)
        gameObject->Update(deltaTime);
    mUpdatingGameObjects = false;

    for (auto pending : mPendingGameObjects)
        mGameObjects.emplace_back(pending);
    mPendingGameObjects.clear();

    std::vector<GameObject*> deadGameObjects;
    for (auto gameObject : mGameObjects)
        if (gameObject->GetState() == GameObjectState::Destroy)
            deadGameObjects.emplace_back(gameObject);

    for (auto gameObject : deadGameObjects)
        delete gameObject;
}

void Game::AddGameObject(GameObject* gameObject) {
    if (mUpdatingGameObjects)
        mPendingGameObjects.emplace_back(gameObject);
    else
        mGameObjects.emplace_back(gameObject);
}

void Game::RemoveGameObject(GameObject* gameObject) {
    auto iter = std::find(mPendingGameObjects.begin(), mPendingGameObjects.end(), gameObject);
    if (iter != mPendingGameObjects.end()) {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingGameObjects.end() - 1);
        mPendingGameObjects.pop_back();
    }

    iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
    if (iter != mGameObjects.end()) {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mGameObjects.end() - 1);
        mGameObjects.pop_back();
    }
}

void Game::AddDrawable(class DrawComponent *drawable) {
    mDrawables.emplace_back(drawable);

    std::sort(mDrawables.begin(), mDrawables.end(),[](DrawComponent* a, DrawComponent* b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveDrawable(class DrawComponent *drawable) {
    auto iter = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    mDrawables.erase(iter);
}

void Game::AddCollider(class BoxColliderComponent* collider) {
    mColliders.emplace_back(collider);
}

void Game::RemoveCollider(class BoxColliderComponent* collider) {
    auto iter = std::find(mColliders.begin(), mColliders.end(), collider);
    mColliders.erase(iter);
}

void Game::GenerateOutput() {
    // Set draw color to black
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

    // Clear back buffer
    SDL_RenderClear(mRenderer);

    for (auto drawable : mDrawables)
        if (drawable->IsVisible())
            drawable->Draw(mRenderer);

    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
}

SDL_Texture* Game::LoadTexture(const std::string& texturePath) {
    // Cria uma surface, a partir do endereço de textura passado.
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if(!surface) return nullptr;

    // Cria uma textura a partir da surface criada.
    SDL_Texture* texture =  SDL_CreateTextureFromSurface(this->mRenderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void Game::Shutdown() {
    while (!mGameObjects.empty())
        delete mGameObjects.back();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

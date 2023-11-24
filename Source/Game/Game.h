// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "Math.h"
#include "../GameObjects/Camera.h"

class Game {
    protected:
        // All the actors in the game
        std::vector<class GameObject*> mGameObjects;
        std::vector<class GameObject*> mPendingGameObjects;

        // All the draw components
        std::vector<class DrawComponent*> mDrawables;

        // All the collision components
        std::vector<class BoxColliderComponent*> mColliders;

        // SDL stuff
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        // Main Camera
        Camera * mCamera;

        // Window properties
        int mWindowWidth;
        int mWindowHeight;

        // Track elapsed time since game start
        Uint32 mTicksCount;

        // Track if we're updating actors right now
        bool mIsRunning;
        bool mUpdatingGameObjects;

        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();

    public:
        Game(int windowWidth, int windowHeight);

        bool Initialize();
        void RunLoop();
        void Shutdown();
        void Quit() { mIsRunning = false; }

        SDL_Renderer* GetRenderer() { return mRenderer; }

        // Draw functions
        void AddDrawable(class DrawComponent* drawable);
        void RemoveDrawable(class DrawComponent* drawable);

        // Collider functions
        void AddCollider(class BoxColliderComponent* collider);
        void RemoveCollider(class BoxColliderComponent* collider);
        std::vector<class BoxColliderComponent*>& GetColliders() { return mColliders; }

        // Window functions
        int GetWindowWidth() const { return mWindowWidth; }
        int GetWindowHeight() const { return mWindowHeight; }

        Camera* GetCamera() { return mCamera; }

        SDL_Texture* LoadTexture(const std::string& texturePath);

        void UpdateGameObjects(float deltaTime);
        void AddGameObject(class GameObject* gameObject);
        void RemoveGameObject(class GameObject* gameObject);

        // Virtual functions for further game specific implementations.
        virtual void InitializeGameObjects() { }
};

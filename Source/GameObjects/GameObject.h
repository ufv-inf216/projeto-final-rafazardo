// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// Game Object module for defining each object that has a Update
// method and can process input
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include <SDL_stdinc.h>
#include "../Game/Math.h"
#include "../Components/ColliderComponents/BoxColliderComponent.h"
#include <unordered_map>

enum class GameObjectState {
    Active,
    Paused,
    Destroy
};

class GameObject {
    public:
        GameObject(class MyGame* game);
        virtual ~GameObject();

        // Update function called from Game (not overridable)
        virtual void Update(float deltaTime);
        // ProcessInput function called from Game (not overridable)
        void ProcessInput(const Uint8* keyState);

        // Position getter/setter
        const Vector2& GetPosition() const { return mPosition; }
        void SetPosition(const Vector2& pos) { mPosition = pos; }

        Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

        // Scale getter/setter
        float GetScale() const { return mScale; }
        void SetScale(float scale) { mScale = scale; }

        // Rotation getter/setter
        float GetRotation() const { return mRotation; }
        void SetRotation(float rotation) { mRotation = rotation; }

        // State getter/setter
        GameObjectState GetState() const { return mState; }
        void SetState(GameObjectState state) { mState = state; }

        // Game getter
        class MyGame* GetGame() { return mGame; }

        // Returns component of type T, or null if doesn't exist
        template <typename T>
        T* GetComponent() const {
            for (auto c : mComponents) {
                T* t = dynamic_cast<T*>(c);
                if (t != nullptr)
                    return t;
            }

            return nullptr;
        }

        // Any actor-specific collision code (overridable)
        virtual void OnCollision(std::unordered_map<CollisionSide, BoxColliderComponent::Overlap>& responses);

        // Disale this game pbject.
        virtual void Disable() {
            SetState(GameObjectState::Paused);
            for(auto c : mComponents)
                c->SetEnabled(false);
        }

        // Enable this game object.
        virtual void Enable() {
            SetState(GameObjectState::Active);
            for(auto c : mComponents)
                c->SetEnabled(true);
        }


    protected:
        class MyGame* mGame;

        // Any actor-specific update code (overridable)
        virtual void OnUpdate(float deltaTime);
        // Any actor-specific update code (overridable)
        virtual void OnProcessInput(const Uint8* keyState);

        // GameObject's state
        GameObjectState mState;

        // Transform
        Vector2 mPosition;
        float mScale;
        float mRotation;

        // Components
        std::vector<class Component*> mComponents;

        // Game specific
        bool mIsOnGround;

    private:
        friend class Component;

        // Adds component to GameObject (this is automatically called
        // in the component constructor)
        void AddComponent(class Component* c);
};
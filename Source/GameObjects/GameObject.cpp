// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#include "GameObject.h"
#include "../GameSpecific/MyGame.h"
#include "../Components/Component.h"
#include <algorithm>

GameObject::GameObject(MyGame* game)
        : mState(GameObjectState::Active)
        , mPosition(Vector2::Zero)
        , mScale(1.0f)
        , mRotation(0.0f)
        , mGame(game) {
    mGame->AddGameObject(this);
}

GameObject::~GameObject() {
    mGame->RemoveGameObject(this);

    for(auto component : mComponents)
        delete component;
    mComponents.clear();
}

void GameObject::Update(float deltaTime) {
    if (mState == GameObjectState::Active) {
        for (auto comp : mComponents)
            comp->Update(deltaTime);
        OnUpdate(deltaTime);
    }
}

void GameObject::OnUpdate(float deltaTime) { }

void GameObject::ProcessInput(const Uint8* keyState) {
    if (mState == GameObjectState::Active) {
        for (auto comp : mComponents)
            comp->ProcessInput(keyState);
        OnProcessInput(keyState);
    }
}

void GameObject::OnProcessInput(const Uint8* keyState) { }

void GameObject::OnCollision(std::unordered_map<CollisionSide, BoxColliderComponent::Overlap>& responses) { }

void GameObject::AddComponent(Component* c) {
    mComponents.emplace_back(c);
    std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
        return a->GetUpdateOrder() < b->GetUpdateOrder();
    });
}

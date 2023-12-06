// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023
// ----------------------------------------------------------------

#include "Layer.h"
#include <queue>
#include <map>

Layer::Layer(class MyGame *game, Layer* prev, Room *first, Room *last):
    GameObject(game),
    mFirstRoom(first),
    mLastRoom(last),
    mNextLayer(nullptr) {

    mPreviousLayer = prev;
}

void Layer::Print() {

    SDL_Log("Entrei no print do layer");

    std::queue<Room*> q;
    q.push(mFirstRoom);
    std::map<Room*, bool> m;
    while(!q.empty()) {
        auto ptr = q.front();
        q.pop();
        if(m.find(ptr) != m.end()) continue;
        ptr->Print();

        m[ptr] = true;

        if(ptr->GetNextRoom(ConnectionSide::Right)) {
            q.push(ptr->GetNextRoom(ConnectionSide::Right));
        }
        if(ptr->GetNextRoom(ConnectionSide::Left)) {
            q.push(ptr->GetNextRoom(ConnectionSide::Left));
        }
        if(ptr->GetNextRoom(ConnectionSide::Down)) {
            q.push(ptr->GetNextRoom(ConnectionSide::Down));
        }
        if(ptr->GetNextRoom(ConnectionSide::Top)) {
            q.push(ptr->GetNextRoom(ConnectionSide::Top));
        }
    }

}
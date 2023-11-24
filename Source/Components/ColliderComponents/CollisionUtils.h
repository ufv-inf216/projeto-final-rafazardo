// ----------------------------------------------------------------
// From Sine Exitus Game, developed during the INF216 course at the
// Federal University of Viçosa.
// Authors: André Feijó, Pedro Fiorio and Rafael Crevelari.
//
// Created: October, 2023.
// ----------------------------------------------------------------

#pragma once

enum class ColliderLayer {
    Player,
    NPC,
    Enemy,
    Chest,
    Saver
};

enum class CollisionSide {
    Top,
    Down,
    Left,
    Right
};
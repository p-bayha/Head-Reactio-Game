#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Utils.hpp" // Includes Position, Size, etc. if needed

// Abstract base class for all game objects
class GameObject {
public:
    virtual void draw() = 0;
    virtual bool checkCollision(const GameObject& other) const = 0;
    virtual Position getPosition() const = 0;
    // Virtual destructor for safe polymorphic deletion
    virtual ~GameObject() {}
};

#endif

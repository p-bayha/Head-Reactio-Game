#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Utils.hpp" // Falls du Position, Size usw. brauchst

class GameObject {
public:
    virtual void draw() = 0;
    virtual bool checkCollision(const GameObject& other) const = 0;
    virtual Position getPosition() const = 0;
    virtual ~GameObject() {}
};

#endif

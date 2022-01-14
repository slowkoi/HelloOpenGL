#include "node.h"

Node::Node()
{
}

void Node::setPosition(float x, float y, float z)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

void Node::setScale(float scale)
{
    this->scale = scale;
}
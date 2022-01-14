#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Node
{
private:
public:
    glm::vec3 position;
    float scale;
    Node();

    void setPosition(float, float, float);
    void setScale(float);
};
#endif
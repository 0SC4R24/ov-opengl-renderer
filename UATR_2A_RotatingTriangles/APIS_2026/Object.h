#pragma once
#include "mapi/common.h"
#include "vertex.h"
class Object
{

public:
    static inline int objectCounter = 0;

    int objectId;

    glm::vec4  pos;
    glm::vec4  rot;
    glm::vec4  scaling;

    std::vector<vertex_t> vertexList;
    std::vector<int>      vertexIndexList;

    Object();

    glm::mat4 getModelMatrix();

    void step(float timeStep);
};


//
// U-TAD. Master en Computacion Grafica, Simulacion y Realidad Virtual.
// 2025-2026
// Miguel Gutierrez Ruano miguel.gutierrez@live.u-tad.com
// Oscar Viudez Cuevas oscar.viudez@live.u-tad.com
//

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


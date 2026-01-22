#pragma once

#include "common.h"
#include "vertex.h"
#include "GLFWKeyManager.h"
#include "Program.h"

namespace old
{
	class Object
	{
	public:
		static inline int objectCounter = 0;

		int objectId;

		glm::vec4 position;
		glm::vec4 rotation;
		glm::vec4 scale;

		std::vector<vertex_t> vertexList;
		std::vector<int> vertexIndexList;

		Program* renderProgram;

		Object();

		glm::mat4 getModelMatrix();

		void step(float timeStep);
	};
}
///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Object.h"
#include "GLFWKeyManager.h"

class Object3D : public Object
{
public:
	Object3D();

	void loadDataFromFile(std::string file) override;
	void step(double deltaTime) override;
};
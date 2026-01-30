///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Object.h"

class Object3D : public Object
{
public:
	Object3D();

	virtual void loadDataFromFile(std::string file) {};
	virtual void step(double deltaTime) {};
};
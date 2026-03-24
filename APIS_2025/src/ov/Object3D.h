///
/// OV-OpenGL-Renderer
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

	void loadDataFromMshFile(std::string file) override;

	void loadDataFromObjFile(std::string file, MaterialPtr material);

	void recomputeNormals();

	virtual void step(double deltaTime) {};
};
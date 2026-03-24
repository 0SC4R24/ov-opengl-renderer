///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Object3D.h"

class TrianguloRot : public Object3D
{
public:
	TrianguloRot();

	void step(double deltaTime) override;
};
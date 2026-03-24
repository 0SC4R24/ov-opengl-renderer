///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"

typedef struct
{
	glm::vec4 vertexPosition;
	glm::vec4 vertexColor;
	glm::vec2 vertexTextureCoordinates;
	glm::vec4 vertexNormal;
} vertex_t;
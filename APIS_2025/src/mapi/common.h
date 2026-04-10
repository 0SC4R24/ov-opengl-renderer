#pragma once
#include <iostream>
#pragma once
#define _USE_MATH_DEFINES
#ifdef GLAD_BIN
#define GLAD_GL_IMPLEMENTATION
#endif
#include <glad/gl.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

#include <iostream>
#include <vector>
#include <list>

#include <map>
#include <fstream>
#include <string>
#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

/// <summary>
/// Program Type Enumerator
/// </summary>
typedef enum
{
	OV_PROGRAM_TYPE_VERTEX,
	OV_PROGRAM_TYPE_FRAGMENT
} OV_ProgramType_e;

/// <summary>
/// Object Type Enumerator
/// </summary>
typedef enum
{
	OV_OBJECT_TYPE_OBJECT,
	OV_OBJECT_TYPE_CAMERA,
	OV_OBJECT_TYPE_LIGHT
} OV_ObjectType_e;

/// <summary>
/// Light Type Enumerator
/// </summary>
typedef enum
{
	OV_LIGHT_TYPE_POINT,
	OV_LIGHT_TYPE_DIRECTIONAL,
	OV_LIGHT_TYPE_SPOT
} OV_LightType_e;

/// <summary>
/// Enum to select InputManager
/// </summary>
typedef enum 
{
	OV_INPUT_MANAGER_TYPE_GLFW
} OV_InputManagerType_e;

/// <summary>
/// Enum to select Render
/// </summary>
typedef enum
{
	OV_RENDER_ENGINE_TYPE_GL1,
	OV_RENDER_ENGINE_TYPE_GL2,
	OV_RENDER_ENGINE_TYPE_GL3,
	OV_RENDER_ENGINE_TYPE_GL4
} OV_RenderEngineType_e;

/// <summary>
/// Projection type enum
/// </summary>
typedef enum
{
	OV_PROJECTION_TYPE_PERSPECTIVE,
	OV_PROJECTION_TYPE_ORTHOGRAPHIC
} OV_ProjectionType_e;

/// <summary>
/// Blend mode enum
/// </summary>
typedef enum
{
	OV_BLEND_MODE_ALPHA,
	OV_BLEND_MODE_ADD,
	OV_BLEND_MODE_MULTIPLY,
	OV_BLEND_MODE_NONE
} OV_BlendMode_e;

template <typename T>
std::vector<T> splitString(const std::string& str, char delim) {
	std::vector<T> elems;
	std::stringstream sstream(str);
	std::string item;
	T tipoDato;
	
	if (str != "") {
		while (std::getline(sstream, item, delim))
		{
			std::istringstream str(item);
			str >> tipoDato;
			elems.push_back(tipoDato);
		}
	}
	
	return elems;
}
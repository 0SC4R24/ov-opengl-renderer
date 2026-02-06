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
	MO_PROGRAM_TYPE_VERTEX,
	MO_PROGRAM_TYPE_FRAGMENT
} MO_ProgramType_e;

/// <summary>
/// Object Type Enumerator
/// </summary>
typedef enum
{
	MO_OBJECT_TYPE_OBJECT,
	MO_OBJECT_TYPE_CAMERA,
	MO_OBJECT_TYPE_LIGHT
} MO_ObjectType_e;

/// <summary>
/// Light Type Enumerator
/// </summary>
typedef enum
{
	MO_LIGHT_TYPE_POINT,
	MO_LIGHT_TYPE_DIRECTIONAL,
	MO_LIGHT_TYPE_SPOT
} MO_LightType_e;

/// <summary>
/// Enum to select InputManager
/// </summary>
typedef enum 
{
	MO_INPUT_MANAGER_TYPE_GLFW
} MO_InputManagerType_e;

/// <summary>
/// Enum to select Render
/// </summary>
typedef enum
{
	MO_RENDER_ENGINE_TYPE_GL1,
	MO_RENDER_ENGINE_TYPE_GL2,
	MO_RENDER_ENGINE_TYPE_GL3,
	MO_RENDER_ENGINE_TYPE_GL4
} MO_RenderEngineType_e;

/// <summary>
/// Projection type enum
/// </summary>
typedef enum
{
	MO_PROJECTION_TYPE_PERSPECTIVE,
	MO_PROJECTION_TYPE_ORTHOGRAPHIC
} MO_ProjectionType_e;

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
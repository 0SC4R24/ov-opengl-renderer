///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "mapi/Object.h" // Change to new object
#include "mapi/vertex.h"

#include "GL4Render.h"

GL4Render::GL4Render(const int& width, const int& height)
{
	// Initialize OpenGL
	init();

	// Create window
	m_window = createGLFWWindow(width, height);
}

void GL4Render::init()
{
	// Initialize OpenGL
	if (not glfwInit())
	{
		std::cout << "ERROR: Unable to initialize GLFW\n"; // TODO: Make logger
		exit(0);
	}

	// Set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MO_GL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MO_GL_MINOR_VERSION);

	// Set modern OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Set not resizable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void GL4Render::setupObject(std::shared_ptr<old::Object> objectPtr)
{
	bufferObject_t bo = { 0, 0, 0 };

	// Generate VAO, VBO and IBO
	glGenVertexArrays(1, &bo.vertexArrayId);
	glGenBuffers(1, &bo.vertexBufferId);
	glGenBuffers(1, &bo.vertexIndexArrayId);

	// Bind in OpenGL state machine VAO, VBO and IBO
	glBindVertexArray(bo.vertexArrayId);
	glBindBuffer(GL_ARRAY_BUFFER, bo.vertexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIndexArrayId);

	// Get pointer
	old::Object* obj = objectPtr.get();

	// Fill vertex buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(old::vertex_t) * obj->vertexList.size(), obj->vertexList.data(), GL_STATIC_DRAW);

	// Fill index buffer data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * obj->vertexIndexList.size(), obj->vertexIndexList.data(), GL_STATIC_DRAW);

	m_bufferObjectMap[obj->objectId] = bo;
}

void GL4Render::removeObject(std::shared_ptr<old::Object> objectPtr)
{
	// Free buffers from object
}

void GL4Render::drawObjects(std::vector<ObjectPtr>* objectVectorPtr)
{
	// Clean window buffer
	// Model matrix set (object)
	// Swap buffers
}

GLFWwindow* GL4Render::createGLFWWindow(const int& width, const int& height)
{
	// Create window
	GLFWwindow* window = glfwCreateWindow(width, height, WINDOW_NAME.data(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Load OpenGL function pointers
	gladLoadGL(glfwGetProcAddress);

	// Enable Z buffer
	glEnable(GL_DEPTH_TEST);

	return window;
}

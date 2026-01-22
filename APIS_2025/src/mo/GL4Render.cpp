///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

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

void GL4Render::setupObject(std::shared_ptr<Object> objectPtr)
{

}

void GL4Render::removeObject(std::shared_ptr<Object> objectPtr)
{

}

void GL4Render::drawObjects(std::vector<ObjectPtr>* objectVectorPtr)
{

}

GLFWwindow* GL4Render::createGLFWWindow(const int& width, const int& height)
{
	// Create window
	GLFWwindow* window = glfwCreateWindow(width, height, WINDOW_NAME.data(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Load OpenGL function pointers
	gladLoadGL(glfwGetProcAddress);

	// Enable depth
	glEnable(GL_DEPTH_TEST);

	return window;
}

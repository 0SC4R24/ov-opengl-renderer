///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "mapi/Object.h" // Change to new object
#include "mapi/vertex.h"

#include "GL4Render.h"

GL4Render::GL4Render(const int& width, const int& height) :
	m_camera{ nullptr }
{
	// Initialize OpenGL
	init();

	// Create window
	m_window = createGLFWWindow(width, height);
}

GL4Render::~GL4Render()
{
	for (auto& [objectId, bo] : m_bufferObjectMap)
	{
		// Delete GPU buffers
		glDeleteBuffers(1, &bo.vertexBufferId);
		glDeleteBuffers(1, &bo.vertexIndexArrayId);
		glDeleteVertexArrays(1, &bo.vertexArrayId);
	}
}

void GL4Render::init()
{
	// Initialize OpenGL
	if (not glfwInit())
	{
		std::cout << "ERROR: Unable to initialize GLFW\n";
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
	if (not objectPtr)
	{ return; }

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

	// Set shader data. Move to material class
	obj->renderProgram->setAttributeMetaData("vPos", 4, GL_FLOAT, false, sizeof(old::vertex_t), (void*)offsetof(old::vertex_t, vPosition));
	obj->renderProgram->setAttributeMetaData("vColor", 4, GL_FLOAT, false, sizeof(old::vertex_t), (void*)offsetof(old::vertex_t, vColor));

	// Reset bindings
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GL4Render::removeObject(std::shared_ptr<old::Object> objectPtr)
{
	if (not objectPtr)
	{ return; }

	int objectId = objectPtr->objectId;
	auto bufferObjectMapIterator = m_bufferObjectMap.find(objectId);

	if (bufferObjectMapIterator == m_bufferObjectMap.end())
	{ return; }

	// Get object buffers
	bufferObject_t bo = bufferObjectMapIterator->second;

	// Free object buffers
	glDeleteBuffers(1, &bo.vertexBufferId);
	glDeleteBuffers(1, &bo.vertexIndexArrayId);
	glDeleteVertexArrays(1, &bo.vertexArrayId);
}

void GL4Render::drawObjects(std::list<ObjectPtr>& objectVectorPtr)
{
	// Clean window buffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_camera != nullptr)
	{
		for (auto& objPtr : objectVectorPtr)
		{
			// Continue if object is not set up
			auto bufferObjectMapIterator = m_bufferObjectMap.find(objPtr->objectId);
			if (bufferObjectMapIterator == m_bufferObjectMap.end())
			{
				continue;
			}

			// Calculate projection matrix
			glm::mat4 model = objPtr->getModelMatrix();

			objPtr->renderProgram->activate();
			objPtr->renderProgram->setMVP(m_camera->cameraProjection * m_camera->cameraView * model);

			// Bind buffers
			bufferObject_t bo = m_bufferObjectMap[objPtr->objectId];
			glBindVertexArray(bo.vertexArrayId);
			glBindBuffer(GL_ARRAY_BUFFER, bo.vertexBufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIndexArrayId);

			// Draw call
			glDrawElements(GL_TRIANGLES, objPtr->vertexIndexList.size(), GL_UNSIGNED_INT, nullptr);
		}
	}

	// Swap buffers
	glfwSwapBuffers(m_window);
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

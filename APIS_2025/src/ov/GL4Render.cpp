#include "ov/Object.h"
#include "mapi/vertex.h"
#include "System.h"
#include "GL4Render.h"

GL4Render::GL4Render(std::string windowName, const int& width, const int& height)
{
	WINDOW_NAME = windowName;
	
	m_width = width;
	m_height = height;
	
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
	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "[ERROR] Unable to initialize GLFW\n";
		exit(0);
	}

	// Set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OV_GL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OV_GL_MINOR_VERSION);

	// Set modern OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Set not resizable
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void GL4Render::setupObject(std::shared_ptr<Object> objectPtr)
{
	if (not objectPtr)
	{ return; }

	for (auto& mesh : objectPtr->getMeshes())
	{
		if (not mesh) continue;

		if (m_bufferObjectMap.find(mesh->getMeshID()) != m_bufferObjectMap.end()) continue;

		bufferObject_t bo = { 0, 0, 0 };

		// Generate VAO, VBO and IBO
		glGenVertexArrays(1, &bo.vertexArrayId);
		glGenBuffers(1, &bo.vertexBufferId);
		glGenBuffers(1, &bo.vertexIndexArrayId);

		// Bind in OpenGL state machine VAO, VBO and IBO
		glBindVertexArray(bo.vertexArrayId);
		glBindBuffer(GL_ARRAY_BUFFER, bo.vertexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIndexArrayId);

		// Fill vertex buffer data
		auto vertList = mesh->getVertList();
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * vertList->size(), vertList->data(), GL_STATIC_DRAW);

		// Fill index buffer data
		auto vertIndexList = mesh->getVTriangleIdxList();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vertIndexList->size(), vertIndexList->data(), GL_STATIC_DRAW);

		m_bufferObjectMap[mesh->getMeshID()] = bo;

		// Set shader data
		auto renderProgram = mesh->getMaterial()->getRenderProgram();
		renderProgram->use();
		renderProgram->setVertexAttrib("vPos", sizeof(vertex_t), (void*)offsetof(vertex_t, vertexPosition), 4, GL_FLOAT);
		renderProgram->setVertexAttrib("vColor", sizeof(vertex_t), (void*)offsetof(vertex_t, vertexColor), 4, GL_FLOAT);
		renderProgram->setVertexAttrib("vTexCoord", sizeof(vertex_t), (void*)offsetof(vertex_t, vertexTextureCoordinates), 2, GL_FLOAT);
		renderProgram->setVertexAttrib("vNormal", sizeof(vertex_t), (void*)offsetof(vertex_t, vertexNormal), 4, GL_FLOAT);

		// Reset bindings
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void GL4Render::removeObject(std::shared_ptr<Object> objectPtr)
{
	if (not objectPtr)
	{ return; }

	for (auto& mesh : objectPtr->getMeshes())
	{
		if (not mesh) continue;

		int meshId = mesh->getMeshID();
		auto bufferObjectMapIterator = m_bufferObjectMap.find(meshId);

		if (bufferObjectMapIterator == m_bufferObjectMap.end()) continue;

		// Get object buffers
		bufferObject_t bo = bufferObjectMapIterator->second;

		// Free object buffers
		glDeleteBuffers(1, &bo.vertexBufferId);
		glDeleteBuffers(1, &bo.vertexIndexArrayId);
		glDeleteVertexArrays(1, &bo.vertexArrayId);

		// Delete from map
		m_bufferObjectMap.erase(bufferObjectMapIterator);
	}
}

void GL4Render::drawObjects(std::list<ObjectPtr>& objectVectorPtr)
{
	// Clean window buffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& objPtr : objectVectorPtr)
	{
		drawObject(objPtr);
	}

	// Swap buffers
	glfwSwapBuffers(m_window);
}

void GL4Render::drawObject(std::shared_ptr<Object> objectPtr)
{
	if (not objectPtr) return;

	// Get and set model matrix
	glm::mat4 model = objectPtr->getModelMatrix();
	System::setModelMatrix(model);

	for (auto& mesh : objectPtr->getMeshes())
	{
		if (not mesh) continue;

		auto bufferObjectMapIterator = m_bufferObjectMap.find(mesh->getMeshID());
		if (bufferObjectMapIterator == m_bufferObjectMap.end()) continue;

		// Prepare material
		mesh->getMaterial()->prepare();

		// Bind buffers
		bufferObject_t bo = bufferObjectMapIterator->second;
		glBindVertexArray(bo.vertexArrayId);
		glBindBuffer(GL_ARRAY_BUFFER, bo.vertexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIndexArrayId);

		// Draw call
		glDrawElements(GL_TRIANGLES, mesh->getVTriangleIdxList()->size(), GL_UNSIGNED_INT, nullptr);
	}

	// Unbind after drawing all meshes
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool GL4Render::isClosed()
{
	return glfwWindowShouldClose(m_window);
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

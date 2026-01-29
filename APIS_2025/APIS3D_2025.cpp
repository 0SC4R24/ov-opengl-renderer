#define GLAD_BIN

#include "mapi/common.h"
#include "mapi/GLFWKeyManager.h"
#include "mapi/Object.h"
#include "mapi/Camera.h"
#include "mapi/vertex.h"

#include "mo/GL4Render.h"
#include "mo/GLFWInputManager.h"

std::vector<old::Object*> objectList;
std::list<std::shared_ptr<old::Object>> objectPtrList;
std::map<int, bufferObject_t> bufferObjectList;

void setupObject(old::Object* obj)
{
    bufferObject_t bo = { 0, 0, 0 };

    glGenVertexArrays(1, &bo.vertexBufferId);
    glGenBuffers(1, &bo.vertexArrayId);
    glGenBuffers(1, &bo.vertexIndexArrayId);

    glBindVertexArray(bo.vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIndexArrayId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(old::vertex_t) * obj->vertexList.size(), obj->vertexList.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * obj->vertexIndexList.size(), obj->vertexIndexList.data(), GL_STATIC_DRAW);

    bufferObjectList[obj->objectId] = bo;

    obj->renderProgram->setAttributeMetaData("vPos", 4, GL_FLOAT, false, sizeof(old::vertex_t), (void*)offsetof(old::vertex_t, vPosition));
    obj->renderProgram->setAttributeMetaData("vColor", 4, GL_FLOAT, false, sizeof(old::vertex_t), (void*)offsetof(old::vertex_t, vColor));
}

void updateObjects(float deltaTime, old::Camera& cam)
{
    cam.step(deltaTime);

    for (auto &obj : objectList)
    {
        obj->step(deltaTime);
    }

    for (auto &obj : objectList)
    {
        glm::mat4 model = obj->getModelMatrix();

        /*glPushMatrix();
        glLoadIdentity();
        glMultMatrixf(&model[0][0]);*/

        obj->renderProgram->activate();
        obj->renderProgram->setMVP(cam.cameraProjection * cam.cameraView * model);

        bufferObject_t bo = bufferObjectList[obj->objectId];
        glBindVertexArray(bo.vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIndexArrayId);

        /*glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*) offsetof(vertex_t, vPosition));
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, sizeof(vertex_t), (void*) offsetof(vertex_t, vColor));*/
        
        glDrawElements(GL_TRIANGLES, (GLsizei)objectList[obj->objectId]->vertexIndexList.size(), GL_UNSIGNED_INT, nullptr);
        
        //glPopMatrix();

        /*glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);*/
    }
}

int main(int argc, char** argv)
{
    GL4Render render{ 640, 480 };

    auto window = render.getWindow();

    old::Object* ground = new old::Object();
    ground->rotation.x = 90.0f;
    ground->scale = glm::vec4(1000);
    ground->position.y = -1.5f;

    objectList.push_back(ground);
	objectPtrList.push_back(std::make_shared<old::Object>(*ground));
    objectList.push_back(new old::Object());
	objectPtrList.push_back(std::make_shared<old::Object>());

    for (auto& obj : objectPtrList)
    {
        //setupObject(obj);
        render.setupObject(obj);
        // render.removeObject(objPtr);
    }

    old::GLFWKeyManager::initKeyManager(window);
	GLFWInputManager inputManager(window);

    float newTime = static_cast<float>(glfwGetTime());
    float deltaTime = 0;
    float lastTime = newTime;

    old::Camera cam(glm::vec4(0, 0, 3, 1), glm::vec4(0, 0, 0, 1));
	render.setCamera(&cam);

    cam.cameraView = glm::lookAt(glm::vec3(cam.position), glm::vec3(cam.lookAt), glm::vec3(0, 1, 0));

    while (!glfwWindowShouldClose(window) && !InputManager::isKeyPressed(GLFW_KEY_ESCAPE))
    {
        newTime = static_cast<float>(glfwGetTime());
        deltaTime = newTime - lastTime;
        lastTime = newTime;

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cam.step(deltaTime);
        //updateObjects(deltaTime, cam);
        render.drawObjects(objectPtrList);

		inputManager.updateEvents();
        //old::GLFWKeyManager::updateEvents();

        //glfwSwapBuffers(window);
    }

    glfwTerminate();

	return 0;
}
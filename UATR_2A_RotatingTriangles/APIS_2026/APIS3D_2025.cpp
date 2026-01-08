#define GLAD_BIN

#include "mapi/common.h"
#include "GLFWKeyManager.h"
#include "Object.h"

typedef struct
{
    unsigned int arrayBufferId;
    unsigned int vertexArrayId;
    unsigned int vertexIndexArrayId;
} bufferObject_t;

std::vector<Object*> objectList;
std::map<int, bufferObject_t> bufferObjectList;

void setupObject(Object* obj)
{
    bufferObject_t bo = { 0, 0, 0 };

    glGenVertexArrays(1, &bo.arrayBufferId);
    glGenBuffers(1, &bo.vertexArrayId);
    glGenBuffers(1, &bo.vertexIndexArrayId);

    glBindVertexArray(bo.arrayBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIndexArrayId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * obj->vertexList.size(), obj->vertexList.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * obj->vertexIndexList.size(), obj->vertexIndexList.data(), GL_STATIC_DRAW);

    bufferObjectList[obj->objectId] = bo;
}

void updateObjects(float deltaTime)
{
    std::cout << 1.0f / deltaTime << "fps\n";

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
        obj->renderProgram->setMVP(model);

        bufferObject_t bo = bufferObjectList[obj->objectId];
        glBindVertexArray(bo.arrayBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIndexArrayId);

        /*glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(4, GL_FLOAT, sizeof(vertex_t), (void*) offsetof(vertex_t, vPosition));
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, sizeof(vertex_t), (void*) offsetof(vertex_t, vColor));*/
        
        obj->renderProgram->setAttributeMetaData("vPos", 4, GL_FLOAT, false, sizeof(vertex_t), (void*) offsetof(vertex_t, vPosition));
        obj->renderProgram->setAttributeMetaData("vColor", 4, GL_FLOAT, false, sizeof(vertex_t), (void*) offsetof(vertex_t, vColor));
        
        glDrawElements(GL_TRIANGLES, objectList[obj->objectId]->vertexIndexList.size(), GL_UNSIGNED_INT, nullptr);
        
        //glPopMatrix();

        /*glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);*/
    }
}

int main(int argc, char** argv)
{
    if (glfwInit() != GLFW_TRUE) {
        std::cout << "ERROR GLFW no iniciada\n";
        exit(0);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(640, 480, "Codigo Clase", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    
    gladLoadGL(glfwGetProcAddress);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glEnable(GL_DEPTH_TEST);

    objectList.push_back(new Object());
    for (auto& obj : objectList)
    {
        setupObject(obj);
    }

    GLFWKeyManager::initKeyManager(window);

    float newTime = static_cast<float>(glfwGetTime());
    float deltaTime = 0;
    float lastTime = newTime;

    while (!glfwWindowShouldClose(window) && !GLFWKeyManager::keyboardState[GLFW_KEY_ESCAPE])
    {
        newTime = static_cast<float>(glfwGetTime());
        deltaTime = newTime - lastTime;
        lastTime = newTime;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateObjects(deltaTime);

        GLFWKeyManager::updateEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();

	return 0;
}
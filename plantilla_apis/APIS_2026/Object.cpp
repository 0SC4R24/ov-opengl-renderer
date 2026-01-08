#include "Object.h"
#include "GLFWKeyManager.h"
Object::Object()
{
    this->objectId = objectCounter++;

    this->vertexList = 
    { 
      {{ 0.5f, 0.5f,0.0f,1.0f},{ 1.0f,0.0f,0.0f,1.0f}},//superior derecha
      {{-0.5f, 0.5f,0.0f,1.0f},{ 1.0f,0.0f,0.0f,1.0f}},//superior izquierda
      {{-0.5f,-0.5f,0.0f,1.0f},{ 1.0f,0.0f,1.0f,1.0f}},//inferior izquierda 
      {{ 0.5f,-0.5f,0.0f,1.0f},{ 0.0f,0.0f,1.0f,1.0f}} //inferior derecha
    }; //posiciones de vertices

    this->vertexIndexList = { 2,1,0, 2,0,3 };

    this->pos = { 0.0f,0.0f,0.0f,1.0f };
    this->rot = { 0.0f,0.0f,0.0f,1.0f };
    this->scaling = { 1.0f,1.0f,1.0f,1.0f };

}

glm::mat4 Object::getModelMatrix()
{
    glm::mat4  model= glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(pos));//aplicar posicion

    model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f)); //rotar x
    model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f)); //rotar y
    model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f)); //rotar z

    model = glm::scale(model, glm::vec3(scaling));//aplicar posicion


    return model;
}

void Object::step(float timeStep)
{
    float vel = 0.1f; //unidadesGl segundo
    float velRot = 40.0f;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_D])
        this->pos.x += vel * timeStep;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_A])
        this->pos.x -= vel * timeStep;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_W])
        this->pos.y += vel * timeStep;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_S])
        this->pos.y -= vel * timeStep;

    if (GLFWKeyManager::keyboardState[GLFW_KEY_R])
        this->rot.x += velRot * timeStep;
    if (GLFWKeyManager::keyboardState[GLFW_KEY_T])
        this->rot.x -= velRot * timeStep;

}





#define GLAD_BIN
#include "mapi/common.h"
#include "GLFWKeyManager.h"
#include "Object.h"

using namespace std;

typedef struct {

	//id de array de buffers
	unsigned int arrayBufferId;
	//id de vertex array buffer
	unsigned int vertexArrayId;
	//id de vertex index buffer
	unsigned int vertexIdxArrayId;
}bo_t; //datos de buffer objects

vector<Object*> objectList; //lista de objetos en el mundo 3D
map<int, bo_t> bufferObjectList; //listas de datos en GPU, indexadas por Identificador único de Objeto


void setupObject(Object* obj)
{
	bo_t bo = { 0,0,0 };

	//crear buffers objects
	glGenVertexArrays(1, &bo.arrayBufferId);
	glGenBuffers(1, &bo.vertexArrayId);
	glGenBuffers(1, &bo.vertexIdxArrayId);
	//copiar datos a GPU
	glBindVertexArray(bo.arrayBufferId); //activar lista de arrays
	glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);//activar lista de vértices
	int numElements = obj->vertexList.size();
	glBufferData(GL_ARRAY_BUFFER, numElements *sizeof(vertex_t), obj->vertexList.data(), GL_STATIC_DRAW); //copiar vertices

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIdxArrayId);//activar lista de indices de vértices
	numElements = obj->vertexIndexList.size();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof(unsigned int), obj->vertexIndexList.data(), GL_STATIC_DRAW); //copiar indices de vertices
	//guardar ids de buffers
	bufferObjectList[obj->objectId] = bo;

}

void updateObjects(float timeStep)
{

	//por cada objeto
		//actualizar eventos
	for (auto &obj : objectList)
	{
		obj->step(timeStep);
	}

	//por cada objeto
		//dibujar
	for (auto& obj : objectList)
	{
		//calcular matriz modelo
		auto model = obj->getModelMatrix();
		//copiar matriz a GPU
		glPushMatrix(); //añadir una matriz en GPU
		glLoadIdentity(); //cargar identidad
		glMultMatrixf(&model[0][0]); //multiplicar por modelo

		//activar buffers de datos
		auto bo = bufferObjectList[obj->objectId]; //recuperar ids de buffers de este objeto
		glBindVertexArray(bo.arrayBufferId); //activar lista de arrays
		glBindBuffer(GL_ARRAY_BUFFER, bo.vertexArrayId);//activar lista de vértices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.vertexIdxArrayId);//activar lista de indices de vértices
		//describir buffers
		glEnableClientState(GL_VERTEX_ARRAY);//voy a describir listas de posiciones de vértices
		glVertexPointer(4, GL_FLOAT, sizeof(vertex_t),(void*)offsetof(vertex_t,vPosition) ); //4 floats al inicio de la estructura
		
		glEnableClientState(GL_COLOR_ARRAY);//voy a describir listas de color de vértice
		glColorPointer(4, GL_FLOAT, sizeof(vertex_t), (void*)offsetof(vertex_t, vColor)); //4 floats después de 4 floats (posición)

		//ordenar a dibujar
		glDrawElements(GL_TRIANGLES, obj->vertexIndexList.size(), GL_UNSIGNED_INT, nullptr);
		//borrar matriz cargada
		glPopMatrix();
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		/*
		//por cada vertice
		glBegin(GL_TRIANGLES);
		for(auto idVertex: obj->vertexIndexList){
			//multiplicar matriz
			vertex_t v=obj->vertexList[idVertex];
			v.vPosition = model*v.vPosition;
			//añadir a lista de dibujado
			glVertex3f(v.vPosition.x, v.vPosition.y, v.vPosition.z);
		}
		glEnd();*/
	}
}


int main(int argc, char** argv)
{
	
	if (glfwInit() != GLFW_TRUE)
	{	
		std::cout << "ERROR iniciando glfw\n";
	}
	else {
	
		
		//iniciar opengl
#ifdef __APPLE__
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
		
		GLFWwindow* window= glfwCreateWindow(640, 480, "Tutorial APIS3D",nullptr, nullptr);
		glfwMakeContextCurrent(window);

		
		gladLoadGL(glfwGetProcAddress);
		
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		//iniciar eventos
		GLFWKeyManager::initKeyManager(window);
		//bucle principal

		float newTime = static_cast<float>(glfwGetTime());
		float deltaTime = 0;
		float lastTime = newTime;


		bool salir = false;

		objectList.push_back(new Object()); //añadir un nuevo objeto generico
		//por cada objeto
			//copiar a GPU
		for (auto& obj : objectList)
		{
			setupObject(obj);
		}

		while (!salir)
		{
			newTime = static_cast<float>(glfwGetTime());
			deltaTime = newTime - lastTime;
			lastTime = newTime;

			//capturar eventos
			GLFWKeyManager::updateEvents();
			//actualizar estado aplicacion
			//limpiar buffer de imagen
			glClear(GL_COLOR_BUFFER_BIT);
			updateObjects(deltaTime);
			//dibujar

			glfwSwapBuffers(window);//una vez dibujado, intercambiar buffer de imagen en ventana
			salir = glfwWindowShouldClose(window);
			
		}
		//cerrar librerías gráficas

		glfwTerminate();
	
	}
	return 0;

}
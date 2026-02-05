#include "common.h"

#include <pugixml.hpp>

#include "mo/InputManager.h"
#include "mo/FactoryEngine.h"

#include "Object3D.h"

Object3D::Object3D()
{
	m_position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_rotation = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_type = MO_OBJECT_TYPE_OBJECT;

	computeModelMatrix();
}

void Object3D::loadDataFromMshFile(std::string file)
{
	auto mesh = std::make_shared<Mesh3D>();

    // Open .msh file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file.c_str());

    if (result == true)
    {
        // Successfully opened
        pugi::xml_node buffersNode = doc.child("mesh").child("buffers");

        // Iterate through each buffer node
        for (pugi::xml_node bufferNode = buffersNode.child("buffer");
             bufferNode;
             bufferNode = bufferNode.next_sibling("buffer"))
        {
            auto mesh = std::make_shared<Mesh3D>();

            // Create material
            auto materialNode = bufferNode.child("material");
            auto materialPtr = FactoryEngine::getNewMaterial();

            // Set material texture
            auto textureNode = materialNode.child("texture");
            auto texturePtr = FactoryEngine::getNewTexture();
            if (textureNode)
            {
                texturePtr->load(textureNode.child("layer").text().as_string());
                materialPtr->setColorTexture(texturePtr);
            }

            // Set material shader
            auto shaderNode = materialNode.child("shader");
            if (shaderNode)
            {
                // Miguel: Optimize shader usage
                materialPtr->loadPrograms({ "data/shader.vert", "data/shader.frag" });
            }

            // Set mesh material
            mesh->setMaterial(materialPtr);
            m_meshes.push_back(mesh);
        }
    }
    else
    {
        // Could not load xml
        std::cout << result.description() << std::endl;
    }
}

void Object3D::loadDataFromObjFile(std::string file)
{
}

void Object3D::recomputeNormals()
{
    // For each vertex reset normals
    //for (auto& v : ) //por cada vértice, resetear sus normales
    //{
    //    v.vNormal = { 0,0,0,0 };
    //}
    //for (auto it = this->vertexIndexList.begin(); it != vertexIndexList.end();)//recorrer la lista de índices de vértices
    //{
    //    vertex_t& v1 = this->vertexList[*it]; it++; //cada tres vértices, una faceta
    //    vertex_t& v2 = this->vertexList[*it]; it++;
    //    vertex_t& v3 = this->vertexList[*it]; it++;
    //    glm::vec3 l1 = glm::normalize(v2.vPosition - v1.vPosition); //obtener dos aristas
    //    glm::vec3 l2 = glm::normalize(v2.vPosition - v3.vPosition);
    //    glm::vec3 norm = glm::normalize(glm::cross(l2, l1)); //obtener la normal
    //    v1.vNormal = glm::normalize(v1.vNormal + glm::vec4(norm, 0.0f)); //acumular la normal, en caso de ser vértices compartidos
    //    v2.vNormal = glm::normalize(v2.vNormal + glm::vec4(norm, 0.0f));
    //    v3.vNormal = glm::normalize(v3.vNormal + glm::vec4(norm, 0.0f));
    //}
}

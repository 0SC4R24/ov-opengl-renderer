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
            std::string meshData = bufferNode.child("meshData").text().as_string();
            loadDataFromObjFile(meshData, materialPtr);
        }
    }
    else
    {
        // Could not load xml
        std::cout << result.description() << std::endl;
    }
}

void Object3D::loadDataFromObjFile(std::string file, MaterialPtr material)
{
    std::ifstream f(file, std::ios_base::in);
    std::vector<glm::vec4> vPos;
    std::vector<glm::vec2> vTC;
    std::vector<glm::vec4> vNorm;
    std::string line;

    Mesh3DPtr m = nullptr;
    auto vertList = std::make_shared<std::vector<vertex_t>>();
    auto vertIndexList = std::make_shared<std::vector<glm::uint32>>();

    int vertexOffset = 0;
    bool computeNormals = false;
    while (std::getline(f, line, '\n'))
    {
        std::istringstream str(line);
        std::string key;
        str >> key;
        if (key[0] != '#')
        {
            if (key == "o")
            {
                if (m)
                {
                    m->setVertList(vertList);
                    m->setVTriangleIdxList(vertIndexList);
                    m_meshes.push_back(m);
                }
                m = std::make_shared<Mesh3D>();
                m->setMaterial(material);
                vertexOffset = vPos.size();
            }
            else if (key == "v")
            {
                glm::vec4 v(1.0f);
                str >> v.x >> v.y >> v.z;
                vPos.push_back(v);
                vertList->push_back(vertex_t{});
            }
            else if (key == "vn")
            {
                glm::vec4 v(0);
                str >> v.x >> v.y >> v.z;
                vNorm.push_back(v);
            }
            else if (key == "vt")
            {
                glm::vec2 v(0);
                str >> v.x >> v.y;
                vTC.push_back(v);
            }
            else if (key == "f")
            {
                std::string vert;
                vertex_t v[3];
                int vIndex[3] = { 0 };

                glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

                for (int i = 0; i < 3; i++)
                {
                    str >> vert;
                    auto indexes = splitString<int>(vert, '/');
                    if (indexes.size() == 3) //si hay tres índices por faceta, se carga la información de normales y textura
                    {
                        v[i] = { vPos[indexes[0] - 1],color,vTC[indexes[1] - 1],vNorm[indexes[2] - 1] };
                    }
                    else if (indexes.size() == 1)//si no, no hay textura y sólo se carga el dato de posición de vértice
                    {
                        v[i] = { vPos[indexes[0] - 1],color, {0,0}, { 0,0,0,0 }};
                        computeNormals = true; //se deben recalcular las normales al acabar de cargar información
                    }
                    vertList->at(indexes[0] - 1 - vertexOffset) = v[i];
                    vertIndexList->push_back(indexes[0] - 1 - vertexOffset);
                }
            }
        }
    }

    if (computeNormals)
        this->recomputeNormals();

    if (m)
    {
        m->setVertList(vertList);
        m->setVTriangleIdxList(vertIndexList);
        m_meshes.push_back(m);
    }
}

void Object3D::recomputeNormals()
{
    for (auto& mesh : m_meshes)
    {
        // For each vertex reset normals
        auto vertListCopy = *mesh->getVertList();
        for (auto& v : vertListCopy)
        {
            v.vertexNormal = { 0,0,0,0 };
        }

        // For each triangle defined by vertex indexes
        auto& vertIndexListCopy = *mesh->getVTriangleIdxList();
        for (auto it = vertIndexListCopy.begin(); it != vertIndexListCopy.end();)
        {
            // Each three vertices, one face
            vertex_t& v1 = vertListCopy[*it]; it++; //cada tres vértices, una faceta
            vertex_t& v2 = vertListCopy[*it]; it++;
            vertex_t& v3 = vertListCopy[*it]; it++;

            // Get two edges
            glm::vec3 l1 = glm::normalize(v2.vertexPosition - v1.vertexPosition);
            glm::vec3 l2 = glm::normalize(v2.vertexPosition - v3.vertexPosition);

            // Get normal with cross product
            glm::vec3 norm = glm::normalize(glm::cross(l2, l1));

            // Set vertex normals
            v1.vertexNormal = glm::normalize(v1.vertexNormal + glm::vec4(norm, 0.0f));
            v2.vertexNormal = glm::normalize(v2.vertexNormal + glm::vec4(norm, 0.0f));
            v3.vertexNormal = glm::normalize(v3.vertexNormal + glm::vec4(norm, 0.0f));
        }
    }
}

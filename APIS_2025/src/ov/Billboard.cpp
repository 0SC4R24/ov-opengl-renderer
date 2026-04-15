#include "Billboard.h"

#include <pugixml.hpp>
#include "FactoryEngine.h"
#include "System.h"
#include "World.h"

Billboard::Billboard(std::string fileName, float spin)
{
    m_spin = spin;
    
    loadDataFromMshFile(fileName);
}

void Billboard::loadDataFromObjFile(std::string file, MaterialPtr material)
{
    std::ifstream f(file, std::ios_base::in);
    
    if (!f.is_open())
    {
        std::cerr << "[ERROR] Cannot open OBJ file: " << file << "\n";
        return;
    }
    
    std::vector<glm::vec4> vPos;
    std::vector<glm::vec2> vTC;
    std::vector<glm::vec4> vNorm;

    auto vertList = std::make_shared<std::vector<vertex_t>>();
    auto vertIndexList = std::make_shared<std::vector<glm::uint32>>();

    Mesh3DPtr m = std::make_shared<Mesh3D>();
    m->setMaterial(material);

    bool computeNormals = false;

    std::string line;
    std::cout << "[INFO] Reading " << file << "\n";
    
    while (std::getline(f, line))
    {
        std::istringstream str(line);
        std::string key;
        str >> key;
        
        if (key.empty() || key[0] == '#') continue;
        
        if (key == "v")
        {
            glm::vec4 v(1.0f);
            str >> v.x >> v.y >> v.z;
            vPos.push_back(v);
        }
        else if (key == "vn")
        {
            glm::vec4 n(0.0f);
            str >> n.x >> n.y >> n.z;
            vNorm.push_back(n);
        }
        else if (key == "vt")
        {
            glm::vec2 t(0.0f);
            str >> t.x >> t.y;
            vTC.push_back(t);
        }
        else if (key == "f")
        {
            std::string vert;
            glm::vec4 color = material->getColor();

            for (int i = 0; i < 3; i++)
            {
                str >> vert;
                auto idx = splitString<int>(vert, '/');

                vertex_t v{};
                v.vertexColor = color;

                v.vertexPosition = vPos[idx[0] - 1];

                if (idx.size() > 1 && idx[1] > 0) v.vertexTextureCoordinates = vTC[idx[1] - 1];
                else v.vertexTextureCoordinates = { 0, 0 };

                if (idx.size() > 2 && idx[2] > 0) v.vertexNormal = vNorm[idx[2] - 1];
                else v.vertexNormal = { 0, 0, 0, 0 }; computeNormals = true;

                vertList->push_back(v);
                vertIndexList->push_back(static_cast<uint32_t>(vertList->size() - 1));
            }
        }
    }
    
    std::cout << "[INFO] Done reading " << file << " \n";

    m->setVertList(vertList);
    m->setVTriangleIdxList(vertIndexList);
    m_meshes.push_back(m);

    if (computeNormals) recomputeNormals();
    
    std::cout << "[INFO] Object instantiated from file correctly\n";
}

void Billboard::recomputeNormals()
{
    std::cout << "[INFO] Recomputing normals\n";
    
    for (auto& mesh : m_meshes)
    {
        // For each vertex reset normals
        auto& vertListCopy = *mesh->getVertList();
        for (auto& v : vertListCopy)
        {
            v.vertexNormal = { 0,0,0,0 };
        }

        // For each triangle defined by vertex indexes
        auto& vertIndexListCopy = *mesh->getVTriangleIdxList();
        for (auto it = vertIndexListCopy.begin(); it != vertIndexListCopy.end();)
        {
            // Each three vertices, one face
            vertex_t& v1 = vertListCopy[*it++]; //cada tres v�rtices, una faceta
            vertex_t& v2 = vertListCopy[*it++];
            vertex_t& v3 = vertListCopy[*it++];

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

void Billboard::loadDataFromMshFile(std::string file)
{
    auto mesh = std::make_shared<Mesh3D>();

    // Open .msh file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file.c_str());
    
    if (result == true)
    {
        std::cout << "[INFO] Reading " << file << "\n";
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
            if (textureNode)
            {
                auto texturePtr = FactoryEngine::getNewTexture();
                texturePtr->load(textureNode.child("layer").text().as_string());
                texturePtr->setup();
                materialPtr->setColorTexture(texturePtr);
            }
            
            // Set color material
            auto colorNode = materialNode.child("color");
            if (colorNode)
            {
                auto colors = splitString<float>(colorNode.text().as_string(), ',');
                materialPtr->setColor(glm::vec4(colors[0], colors[1], colors[2], colors[3]));
            }
            
            // Set shininess material
            auto shininessNode = materialNode.child("shininess");
            if (shininessNode)
            {
                int shiny = shininessNode.text().as_int();
                materialPtr->setShininess(shiny);
            }

            // Set material shader
            auto shaderNode = materialNode.child("shader");
            auto shaders = std::vector<std::string>();
            if (shaderNode)
            {
                shaders = splitString<std::string>(shaderNode.text().as_string(), ',');
                materialPtr->loadPrograms(shaders);
            }
            
            // Set light mode
            auto lightNode = materialNode.child("light");
            if (lightNode)
            {
                materialPtr->setLighting(lightNode.text().as_bool());
            }
            
            // Set blend mode
            auto blendNode = materialNode.child("blendMode");
            if (blendNode)
            {
                std::string blendModeStr = blendNode.text().as_string();
                OV_BlendMode_e blendType;
                
                if (blendModeStr == "alpha" || blendModeStr == "transparency") blendType = OV_BLEND_MODE_ALPHA;
                else if (blendModeStr == "add" || blendModeStr == "additive")  blendType = OV_BLEND_MODE_ADD;
                else if (blendModeStr == "mul" || blendModeStr == "multiply")  blendType = OV_BLEND_MODE_MULTIPLY;
                else                                                           blendType = OV_BLEND_MODE_NONE;
                
                materialPtr->setBlendMode(blendType);
            }
            
            // Set culling mode
            auto cullingNode = materialNode.child("culling");
            if (cullingNode)
            {
                materialPtr->setLighting(cullingNode.text().as_bool());
            }
            
            // Set depth write mode
            auto depthWriteNode = materialNode.child("depthWrite");
            if (depthWriteNode)
            {
                materialPtr->setDepthWrite(depthWriteNode.text().as_bool());
            }

            // Set mesh material
            std::string meshData = bufferNode.child("meshData").text().as_string();
            loadDataFromObjFile(meshData, materialPtr);
        }
    }
    else
    {
        // Could not load xml
        std::cout << result.description() << "\n";
    }
}

void Billboard::computeModelMatrix()
{
    m_modelMatrix = glm::transpose(System::getWorld()->getActiveCamera()->getViewMatrix());
    
    m_modelMatrix[0][3] = 0;
    m_modelMatrix[1][3] = 0;
    m_modelMatrix[2][3] = 0;
    
    m_modelMatrix[3] = getPosition();
}
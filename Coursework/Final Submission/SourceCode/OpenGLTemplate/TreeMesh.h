#pragma once

// file is identical to COpenAssetImportMesh.h
// The reason for this is to allow for instanced rendering to only be applied to the tree model and not to every mesh

#include <map>
#include <vector>
#include "include/gl/glew.h"
#include <Importer.hpp>      // C++ importer interface
#include <scene.h>       // Output data structure
#include <PostProcess.h> // Post processing flags

#include "Common.h"
#include "Texture.h"

#define INVALID_OGL_VALUE 0xFFFFFFFF
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }



struct Vertex1
{
    glm::vec3 m_pos;
    glm::vec2 m_tex;
    glm::vec3 m_normal;

    Vertex1() {}

    Vertex1(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
    {
        m_pos = pos;
        m_tex = tex;
        m_normal = normal;
    }
};

class CTreeMesh
{
public:
    CTreeMesh();
    ~CTreeMesh();
    bool Load(const std::string& Filename);
    void Render();

private:
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();


#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry {
        MeshEntry();

        ~MeshEntry();

        void Init(const std::vector<Vertex1>& Vertices,
            const std::vector<unsigned int>& Indices);
        GLuint vbo;
        GLuint ibo;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> m_Entries;
    std::vector<CTexture*> m_Textures;
    GLuint m_vao;
};
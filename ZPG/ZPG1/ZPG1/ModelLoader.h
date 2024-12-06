#pragma once
#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags
class ModelLoader
{

public:
    struct Vertex
    {
        float Position[3];
        float Normal[3];
        float Texture[2];
    };
	void load(std::string fileName);
    Vertex* getModel();
    int getVertexCount();
    unsigned int* getIndeces();
    unsigned int getNumVertices();
    ~ModelLoader();
private:
    int vertex_count;
    unsigned int* pIndices;
    unsigned int mNumVertices;
    Vertex* model;
};


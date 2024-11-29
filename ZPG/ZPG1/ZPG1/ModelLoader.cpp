#include "ModelLoader.h"
void ModelLoader::load(std::string fileName)
{
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate //Converts polygons to triangles
        | aiProcess_OptimizeMeshes              // Reduces the number of submeshes
        | aiProcess_JoinIdenticalVertices;       // Removes duplicate vertices

    //aiProcess_GenNormals/ai_Process_GenSmoothNormals - Generates flat/Smooth normals

    const aiScene* scene = importer.ReadFile(fileName, importOptions);

    if (scene) { //pokud bylo nacteni uspesne
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        /*printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);
        //Materials
        for (unsigned int i = 0; i < scene->mNumMaterials; i++)
        {
            const aiMaterial* mat = scene->mMaterials[i];
            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name %s\n", i, name.C_Str());
            aiColor4D d;
            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);
        }*/
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];
            model = new Vertex[mesh->mNumVertices];
            std::memset(model, 0, sizeof(Vertex) * mesh->mNumVertices);
            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions()) {
                    model[i].Position[0] = mesh->mVertices[i].x;
                    model[i].Position[1] = mesh->mVertices[i].y;
                    model[i].Position[2] = mesh->mVertices[i].z;
                }

                if (mesh->HasNormals()) {
                    model[i].Normal[0] = mesh->mNormals[i].x;
                    model[i].Normal[1] = mesh->mNormals[i].y;
                    model[i].Normal[2] = mesh->mNormals[i].z;
                }

                if (mesh->HasTextureCoords(0)) {
                    model[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                    model[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                }
            }

            pIndices = nullptr;
            if (mesh->HasFaces()) {
                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }
            vertex_count = mesh->mNumFaces * 3;
        }
    }
    else {
        printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
    }
}

ModelLoader::Vertex* ModelLoader::getModel()
{
	return model;
}

int ModelLoader::getVertexCount()
{
    return this->vertex_count;
}

unsigned int* ModelLoader::getIndeces()
{
    return this->pIndices;
}

ModelLoader::~ModelLoader()
{
    delete[] model;
    delete[] pIndices;
}

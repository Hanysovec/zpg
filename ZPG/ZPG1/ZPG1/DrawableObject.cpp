#include "DrawableObject.h"
#include "Camera.h"

DrawableObject::DrawableObject(const float* vertices, size_t size, int vertexCount, ShaderProgram* shader, Material* mat) {
    this->model = new Model(vertices, size, vertexCount);
    this->shaderProgram = shader;
    this->transform = new Transformation();
    this->mat = mat;
    this->texture = nullptr;
    this->offset = NULL;
}

DrawableObject::DrawableObject(const float* vertices, size_t size, int vertexCount, ShaderProgram* shader, Material* mat, Texture* texture, GLuint offset) {

    this->model = new TextureModel(vertices, size, vertexCount);
    this->shaderProgram = shader;
    this->transform = new Transformation();
    this->mat = mat;
    this->texture = texture;
    this->offset = offset;
}
DrawableObject::DrawableObject(const float* vertices, size_t size, int vertexCount, ShaderProgram* shader, Texture* texture, GLuint offset) {

    this->model = new SkyboxModel(vertices, size, vertexCount);
    this->shaderProgram = shader;
    this->transform = new Transformation();
    this->mat = nullptr;
    this->texture = texture;
    this->offset = offset;
}

DrawableObject::DrawableObject(std::string fileName, ShaderProgram* shader, Texture* texture, GLuint offset)
{
    ModelLoader* ml = new ModelLoader();
    ml->load(fileName);
    this->model = new ObjectModel(ml->getModel(), ml->getVertexCount(), ml->getIndeces());
    this->shaderProgram = shader;
    this->transform = new Transformation();
    this->mat = nullptr;
    this->texture = texture;
    this->offset = offset;
}

DrawableObject::~DrawableObject() {
    delete model;
}

void DrawableObject::draw() const {
    //LightSource* light = dynamic_cast<LightSource*>(subject);
    TextureModel* texModel = dynamic_cast<TextureModel*>(model);
    SkyboxModel* skybox = dynamic_cast<SkyboxModel*>(model);
    ObjectModel* objModel = dynamic_cast<ObjectModel*>(model);
    if (texModel) {
        shaderProgram->use();
        shaderProgram->setTexture(texture->getID(), offset);
        shaderProgram->setModelMatrix(transform->getMatrix());
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(transform->getMatrix())));
        shaderProgram->setNormalMatrix(normalMatrix);
        shaderProgram->setDiffuse(this->mat->getDiffuse());
        shaderProgram->setAmbient(this->mat->getAmbient());
        shaderProgram->setSpecular(this->mat->getSpecular());
        model->draw();
        shaderProgram->stop();
    }
    else if (skybox){
        shaderProgram->use();
        shaderProgram->setSkyboxTexture(texture->getID(), offset);
        shaderProgram->setModelMatrix(transform->getMatrix());
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(transform->getMatrix())));
        shaderProgram->setNormalMatrix(normalMatrix);
        model->draw();
        shaderProgram->stop();
    }
    else if (objModel) {
        shaderProgram->use();
        shaderProgram->setTexture(texture->getID(), offset);
        shaderProgram->setModelMatrix(transform->getMatrix());
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(transform->getMatrix())));
        shaderProgram->setNormalMatrix(normalMatrix);
        model->draw();
        shaderProgram->stop();
    }
    else {
        shaderProgram->use();
        shaderProgram->setModelMatrix(transform->getMatrix());
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(transform->getMatrix())));
        shaderProgram->setNormalMatrix(normalMatrix);
        shaderProgram->setDiffuse(this->mat->getDiffuse());
        shaderProgram->setAmbient(this->mat->getAmbient());
        shaderProgram->setSpecular(this->mat->getSpecular());
        model->draw();
        shaderProgram->stop();
    }
}
void DrawableObject::draw(int a) const {
    shaderProgram->use();
    shaderProgram->setSkyboxTexture(texture->getID(), offset);
    shaderProgram->setModelMatrix(transform->getMatrix());
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(transform->getMatrix())));
    shaderProgram->setNormalMatrix(normalMatrix);
    shaderProgram->setDiffuse(this->mat->getDiffuse());
    shaderProgram->setAmbient(this->mat->getAmbient());
    shaderProgram->setSpecular(this->mat->getSpecular());
    model->draw();
    shaderProgram->stop();
}

void DrawableObject::setMaterial(Material* mat) {
    this->mat = mat;
}

/*void DrawableObject::translate(const glm::vec3& offset) {
    transform.addTranslate(offset);
}

void DrawableObject::rotate(float angle, const glm::vec3& axis) {
    transform.addRotate(angle, axis);
}

void DrawableObject::scale(const glm::vec3& scale) {
    transform.addScale(scale);
}*/
Transformation* DrawableObject::getTransformation() {
    return this->transform;
}

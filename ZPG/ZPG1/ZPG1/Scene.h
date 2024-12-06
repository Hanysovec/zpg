#pragma once
#include <vector>
#include <glm/glm.hpp>  
#include "DrawableObject.h"
#include "sphere.h"
#include "tree.h"
#include "bushes.h"
#include "Camera.h"
#include "LightSource.h"

class Scene {
public:
    Scene(int sceneNum);
    ~Scene();
    void initialize();
    void addObject(DrawableObject* object);
    void draw();
    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void rotate(float yaw, float pitch);
    void addLight(glm::vec3 position, ShaderProgram* shader);
    void addLight(glm::vec3 position, std::vector<ShaderProgram*> shaders);
    void moveBezier(int objectId, std::vector<glm::vec3> bezPoints);
    Camera* getCamera();
    std::vector<glm::vec3> getLightPositions();
private:
    std::vector<DrawableObject*> objects;
    std::vector<LightSource*> lights;
    int sceneNum;
    Camera* camera;
    glm::mat4 A;
    glm::mat4x3 B;
    int selectedObjectId;
    bool bezMove;
    float t = 0.5f;
    float step = 0.01f;
};

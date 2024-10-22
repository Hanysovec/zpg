#pragma once
#include <vector>
#include <glm/glm.hpp>  
#include "DrawableObject.h"
#include "sphere.h"
#include "tree.h"
#include "bushes.h"
#include "Camera.h"

class Scene {
public:
    Scene(int sceneNum);
    ~Scene();
    void initialize();
    void addObject(DrawableObject* object);
    void draw() const;
    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void rotate(float yaw, float pitch);
private:
    std::vector<DrawableObject*> objects;
    int sceneNum;
    Camera* camera;
};

#include "Scene.h"
#include "DrawableObject.h"
#include <GL/glew.h>
#include <cstdlib>
#include <ctime>
#include "Camera.h"
#include "Observer.h"
#include "plain.h"
#include "suzi_flat.h"
#include "gift.h"
#include "LightSource.h"


const char* vertex_shader_src = "vertex_shader_src.txt";
const char* fragment_shader_src = "fragment_shader_src.txt";
const char* fragment_shader_src_floor = "fragment_shader_floor.txt";
const char* vertex_shader_light = "vertex_shader_light.txt";
const char* fragment_shader_light = "fragment_shader_light.txt";

const char* vertex_shader_phong = "vertex_shader_phong.txt";
const char* fragment_shader_phong = "fragment_shader_phong.txt";
const char* vertex_shader_blinn = "vertex_shader_blinn.txt";
const char* fragment_shader_blinn = "fragment_shader_blinn.txt";

float points1[] = {
        -0.5f,  0.0f, 0.0f, 0,0,1,
         0.5f,  0.0f, 0.0f, 0,0,1,
        -0.5f, -0.5f, 0.0f, 0,0,1,
        -0.5f, -0.5f, 0.0f, 0,0,1,
         0.5f, -0.5f, 0.0f, 0,0,1,
         0.5f,  0.0f, 0.0f, 0,0,1
};

float points2[] = {
        0.0f,  0.5f, 0.0f, 0,0,1,
        0.5f,  0.0f, 0.0f, 0,0,1,
       -0.5f,  0.0f, 0.0f, 0,0,1
};

const char* vertex_shader = "vertex_shader.txt";
const char* fragment_shader = "fragment_shader.txt";
const char* vertex_shader2 = "vertex_shader2.txt";
const char* fragment_shader2 = "fragment_shader2.txt";

Scene::Scene(int sceneNum) { this->sceneNum = sceneNum; camera = new Camera(); }

Scene::~Scene() {
    for (auto object : objects) {
        delete object;
    }
    for (auto light : lights) {
        delete light;
    }
}

void Scene::moveForward() {
    camera->moveForward(0.02);
}

void Scene::moveBackward() {
    camera->moveBackward(0.02);
}

void Scene::moveLeft() {
    camera->moveLeft(0.02);
}

void Scene::moveRight() {
    camera->moveRight(0.02);
}
void Scene::rotate(float yaw, float pitch) {
    camera->rotate(yaw, pitch);
}
void Scene::addLight(glm::vec3 position, ShaderProgram* shader) {
    LightSource* newLight = new LightSource(position);
    newLight->addObserver(shader);
    lights.push_back(newLight);
}
void Scene::addLight(glm::vec3 position, std::vector<ShaderProgram*> shaders) {
    LightSource* newLight = new LightSource(position);
    for (auto shader : shaders) {
        newLight->addObserver(shader);
    }
    lights.push_back(newLight);
}

std::vector<glm::vec3> Scene::getLightPositions() {
    std::vector<glm::vec3> positions;
    for (const LightSource* light : lights) {
        positions.push_back(light->getPosition());
    }
    return positions;
}
Camera* Scene::getCamera() {
    return this->camera;
}

void Scene::initialize() {
    if (sceneNum == 1) { // Roztočit 1 strom kolem své osy
        ShaderProgram* shader1 = new ShaderProgram(vertex_shader_phong, fragment_shader_phong);
        camera->addObserver(shader1);
        shader1->use();
        addLight(glm::vec3(0.0f, 5.0f, 0.0f), shader1);
        shader1->setLightPositions(getLightPositions());
        shader1->setProjectionMatrix(camera->getProjectionMatrix());
        shader1->setViewMatrix(camera->getViewMatrix());
        shader1->stop();
        ShaderProgram* shader2 = new ShaderProgram(vertex_shader_src, fragment_shader_src_floor);
        camera->addObserver(shader2);
        shader2->use();
        shader2->setProjectionMatrix(camera->getProjectionMatrix());
        shader2->setViewMatrix(camera->getViewMatrix());
        shader2->stop();
        std::srand(std::time(0));
        for (int i = 0; i < 50; i++) {
            float randX = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            float randZ = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            float randScale = 0.05f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (0.2f - 0.05f)));
            int randAngle = std::rand() % 361;

            DrawableObject* treeObject = new DrawableObject(tree, sizeof(tree), 92814, shader1);
            treeObject->translate(glm::vec3(randX, 0.0f, randZ));
            treeObject->rotate(randAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            treeObject->scale(glm::vec3(randScale));

            addObject(treeObject);
        }
        for (int i = 0; i < 50; i++) {
            float randX = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            float randZ = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            float randScale = 0.3f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (0.8f - 0.3f)));
            int randAngle = std::rand() % 361;

            DrawableObject* bushObject = new DrawableObject(bushes, sizeof(bushes), 8730, shader1);
            bushObject->translate(glm::vec3(randX, 0.0f, randZ));
            bushObject->rotate(randAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            bushObject->scale(glm::vec3(randScale));

            addObject(bushObject);
        }
        DrawableObject* floor = new DrawableObject(plain, sizeof(plain), 6, shader2);
        floor->scale(glm::vec3(4));
        addObject(floor);
    }
    else if (sceneNum == 2) {
        ShaderProgram* shader1 = new ShaderProgram(vertex_shader, fragment_shader);
        ShaderProgram* shader2 = new ShaderProgram(vertex_shader2, fragment_shader2);
        addObject(new DrawableObject(points1, sizeof(points1), 6, shader1));
        addObject(new DrawableObject(points2, sizeof(points2), 3, shader2));
    }
    else if (sceneNum == 3) {
        ShaderProgram* shader1 = new ShaderProgram(vertex_shader_phong, fragment_shader_phong);
        camera->addObserver(shader1);
        shader1->use();
        addLight(glm::vec3(0.0f, 0.0f, 0.0f), shader1);
        shader1->setLightPositions(getLightPositions());
        shader1->setProjectionMatrix(camera->getProjectionMatrix());
        shader1->setViewMatrix(camera->getViewMatrix());
        shader1->setViewPosition(camera->getPosition());
        shader1->stop();

        glm::vec3 positions[] = {
            glm::vec3(0.0f, 2.0f, 0.0f),
            glm::vec3(-2.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, -2.0f, 0.0f)
        };
        for (const auto& pos : positions) {
            DrawableObject* spheres = new DrawableObject(sphere, sizeof(sphere), 2880, shader1);
            spheres->scale(glm::vec3(0.3));
            spheres->translate(pos);
            addObject(spheres);
        }
    }
    else if (sceneNum == 4) {
        std::vector<ShaderProgram*> shaders;
        shaders.push_back(new ShaderProgram(vertex_shader_src, fragment_shader_src));
        shaders.push_back(new ShaderProgram(vertex_shader_light, fragment_shader_light));
        shaders.push_back(new ShaderProgram(vertex_shader_phong, fragment_shader_phong));
        shaders.push_back(new ShaderProgram(vertex_shader_blinn, fragment_shader_blinn));
        addLight(glm::vec3(0.0f, 0.0f, 0.0f), shaders);
        addLight(glm::vec3(-2.0f, 2.0f, 0.0f), shaders);
        for (int i = 0; i < 4; i++) {
            camera->addObserver(shaders[i]);

            shaders[i]->use();
            shaders[i]->setLightPositions(getLightPositions());
            shaders[i]->setProjectionMatrix(camera->getProjectionMatrix());
            shaders[i]->setViewMatrix(camera->getViewMatrix());
            shaders[i]->setViewPosition(camera->getPosition());
            shaders[i]->stop();
        }

        glm::vec3 positions[] = {
            glm::vec3(0.0f, 2.0f, 0.0f),
            glm::vec3(-2.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, -6.0f, 0.0f)
        };
        DrawableObject* sphere1 = new DrawableObject(sphere, sizeof(sphere), 2880, shaders[2]);
        sphere1->scale(glm::vec3(0.2));
        sphere1->translate(positions[0]);
        addObject(sphere1);
        DrawableObject* suzi = new DrawableObject(suziFlat, sizeof(suziFlat), 2904, shaders[1]);
        suzi->scale(glm::vec3(0.3));
        suzi->translate(positions[1]);
        addObject(suzi);
        DrawableObject* bush = new DrawableObject(bushes, sizeof(bushes), 8730, shaders[0]);
        bush->scale(glm::vec3(0.5));
        bush->translate(positions[2]);
        addObject(bush);
        DrawableObject* tree1 = new DrawableObject(tree, sizeof(tree), 92814, shaders[3]);
        tree1->scale(glm::vec3(0.05));
        tree1->translate(positions[3]);
        addObject(tree1);


    }

}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::draw() const {
    if (sceneNum == 1) {
        objects[0]->rotate(0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    for (const auto& object : objects) {
        object->draw();
    }
}

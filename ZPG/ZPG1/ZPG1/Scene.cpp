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
#include "Material.h"
#include "BasicModel.h"
#include "plain_texture.h"
#include "skycube.h"


const char* vertex_shader_src = "vertex_shader_src.txt";
const char* fragment_shader_src = "fragment_shader_src.txt";
const char* fragment_shader_src_floor = "fragment_shader_floor.txt";
const char* vertex_shader_light = "vertex_shader_light.txt";
const char* fragment_shader_light = "fragment_shader_light.txt";

const char* vertex_shader_phong = "vertex_shader_phong.txt";
const char* fragment_shader_phong = "fragment_shader_phong.txt";
const char* vertex_shader_blinn = "vertex_shader_blinn.txt";
const char* fragment_shader_blinn = "fragment_shader_blinn.txt";
const char* fragment_shader_phong_floor = "fragment_shader_phong_floor.txt";

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

const char* vertex_shader_floor = "PhongVertexShader.glsl";
const char* fragment_shader_floor = "PhongFragmentShader.glsl";

const char* vertex_shader_phong_texture = "PhongVertexShader_Texture.txt";
const char* fragment_shader_phong_texture = "PhongFragmentShader_Texture.txt";

Material* matSphere = new Material(
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.385f, 0.647f, 0.812f),
    glm::vec3(1.0f, 1.0f, 1.0f)
);
Material* matTree = new Material(
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.1f, 0.8f, 0.1f),
    glm::vec3(1.0f, 1.0f, 1.0f)
);
Material* matFloor = new Material(
    glm::vec3(0.1f, 0.1f, 0.1f),
    glm::vec3(0.0f, 0.5f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
);
//Texture* texture_floor = new Texture("..\..\ZPG1\grass.png");


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
    Texture* texture_floor = new Texture("negy.jpg");
    if (sceneNum == 1) {
        Texture* texture_box = new Texture("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg");
        ShaderProgram* boxShader = new ShaderProgram("vertex_shader_box.txt", "fragment_shader_box.txt");
        DrawableObject* skyBox = new DrawableObject(skycube, sizeof(skycube), 108, boxShader, texture_box, 0);
        Texture* texture_house = new Texture("house.png");
        camera->addObserver(boxShader);
        addObject(skyBox);
        ShaderProgram* shader1 = new ShaderProgram(vertex_shader_phong, fragment_shader_phong);
        ShaderProgram* shader2 = new ShaderProgram(vertex_shader_floor, fragment_shader_floor);
        ShaderProgram* shader3 = new ShaderProgram(vertex_shader_floor, fragment_shader_floor);
        camera->addObserver(shader1);
        shader1->use();
        addLight(glm::vec3(0.0f, 5.0f, 0.0f), { shader1, shader2, shader3 });
        addLight(glm::vec3(2.3f, 0.3f, 0.0f), { shader1, shader2, shader3 });
        addLight(glm::vec3(0.8f, 0.3f, 2.4f), { shader1, shader2, shader3 });
        addLight(glm::vec3(-1.6f, 0.3f, -3.2f), { shader1, shader2, shader3 });
        shader1->setLightPositions(getLightPositions());
        shader1->setProjectionMatrix(camera->getProjectionMatrix());
        shader1->setViewMatrix(camera->getViewMatrix());
        shader1->stop();
        camera->addObserver(shader2);
        shader2->use();
        shader2->setLightPositions(getLightPositions());
        shader2->setProjectionMatrix(camera->getProjectionMatrix());
        shader2->setViewMatrix(camera->getViewMatrix());
        shader2->stop();
        camera->addObserver(shader3);
        shader3->use();
        shader3->setLightPositions(getLightPositions());
        shader3->setProjectionMatrix(camera->getProjectionMatrix());
        shader3->setViewMatrix(camera->getViewMatrix());
        shader3->stop();
        std::srand(std::time(0));
        for (int i = 0; i < 50; i++) {
            float randX, randZ;
            do {
                randX = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
                randZ = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            } while (randX >= -0.7f && randX <= 0.7f && randZ >= -1.7f && randZ <= 1.7f);

            float randScale = 0.05f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (0.2f - 0.05f)));
            int randAngle = std::rand() % 361;

            DrawableObject* treeObject = new DrawableObject(tree, sizeof(tree), 92814, shader1, matTree);
            treeObject->getTransformation()->addTranslate(glm::vec3(randX, 0.0f, randZ));
            treeObject->getTransformation()->addRotate(randAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            treeObject->getTransformation()->addScale(glm::vec3(randScale));

            addObject(treeObject);
        }
        for (int i = 0; i < 50; i++) {
            float randX, randZ;
            do {
                randX = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
                randZ = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            } while (randX >= -0.7f && randX <= 0.7f && randZ >= -1.7f && randZ <= 1.7f);
            float randScale = 0.3f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (0.8f - 0.3f)));
            int randAngle = std::rand() % 361;

            DrawableObject* bushObject = new DrawableObject(bushes, sizeof(bushes), 8730, shader1, matTree);
            bushObject->getTransformation()->addTranslate(glm::vec3(randX, 0.0f, randZ));
            bushObject->getTransformation()->addRotate(randAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            bushObject->getTransformation()->addScale(glm::vec3(randScale));

            addObject(bushObject);
        }
        DrawableObject* floor = new DrawableObject(plain_texture, sizeof(plain_texture), 6, shader2, matFloor, texture_floor, 1);
        floor->getTransformation()->addScale(glm::vec3(4));
        addObject(floor);

        DrawableObject* house = new DrawableObject("house.obj", shader3, texture_house, 2);
        house->getTransformation()->addScale(glm::vec3(0.15));
        addObject(house);

        DrawableObject* login = new DrawableObject("login.obj", shader2, texture_floor, 1);
        login->getTransformation()->addTranslate(glm::vec3(0.0f, 1.0f, 0.0f));
        addObject(login);
    }
    else if (sceneNum == 2) { // Roztočit 1 strom kolem své osy
        ShaderProgram* shader1 = new ShaderProgram(vertex_shader_phong, fragment_shader_phong);
        ShaderProgram* shader2 = new ShaderProgram(vertex_shader_phong_texture, fragment_shader_phong_texture);
        SpotLight* spotLight = new SpotLight(camera->getPosition(), camera->getForward(), 12.5f, 17.5f);
        camera->addObserver(shader1);
        camera->addObserver(spotLight);
        spotLight->addObserver(shader1);
        shader1->use();
        addLight(glm::vec3(2.3f, 0.3f, 0.0f), { shader1, shader2 });
        addLight(glm::vec3(0.8f, 0.3f, 2.4f), { shader1, shader2 });
        addLight(glm::vec3(-1.6f, 0.3f, -3.2f), { shader1, shader2 });
        shader1->setLightPositions(getLightPositions());
        shader1->setProjectionMatrix(camera->getProjectionMatrix());
        shader1->setViewMatrix(camera->getViewMatrix());
        shader1->setSpotlight(spotLight->getPosition(), spotLight->getDirection(), spotLight->getInnerCutOff(), spotLight->getOuterCutOff());
        shader1->stop();

        camera->addObserver(shader2);
        spotLight->addObserver(shader2);
        shader2->use();
        shader2->setLightPositions(getLightPositions());
        shader2->setProjectionMatrix(camera->getProjectionMatrix());
        shader2->setViewMatrix(camera->getViewMatrix());
        shader2->setSpotlight(spotLight->getPosition(), spotLight->getDirection(), spotLight->getInnerCutOff(), spotLight->getOuterCutOff());
        shader2->stop();
        std::srand(std::time(0));
        for (int i = 0; i < 50; i++) {
            float randX = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            float randZ = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            float randScale = 0.05f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (0.2f - 0.05f)));
            int randAngle = std::rand() % 361;

            DrawableObject* treeObject = new DrawableObject(tree, sizeof(tree), 92814, shader1, matTree);
            treeObject->getTransformation()->addTranslate(glm::vec3(randX, 0.0f, randZ));
            treeObject->getTransformation()->addRotate(randAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            treeObject->getTransformation()->addScale(glm::vec3(randScale));

            addObject(treeObject);
        }
        for (int i = 0; i < 50; i++) {
            float randX = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            float randZ = -3.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (6.0f)));
            float randScale = 0.3f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (0.8f - 0.3f)));
            int randAngle = std::rand() % 361;

            DrawableObject* bushObject = new DrawableObject(bushes, sizeof(bushes), 8730, shader1, matTree);
            bushObject->getTransformation()->addTranslate(glm::vec3(randX, 0.0f, randZ));
            bushObject->getTransformation()->addRotate(randAngle, glm::vec3(0.0f, 1.0f, 0.0f));
            bushObject->getTransformation()->addScale(glm::vec3(randScale));

            addObject(bushObject);
        }
        DrawableObject* floor = new DrawableObject(plain_texture, sizeof(plain_texture), 6, shader2, matFloor, texture_floor, 1);
        floor->getTransformation()->addScale(glm::vec3(4));
        addObject(floor);
    }
    else if (sceneNum == 3) {
        ShaderProgram* shader1 = new ShaderProgram(vertex_shader, fragment_shader);
        ShaderProgram* shader2 = new ShaderProgram(vertex_shader2, fragment_shader2);
        addObject(new DrawableObject(points1, sizeof(points1), 6, shader1, matSphere));
        addObject(new DrawableObject(points2, sizeof(points2), 3, shader2, matSphere));
    }
    else if (sceneNum == 4) {
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
            DrawableObject* spheres = new DrawableObject(sphere, sizeof(sphere), 2880, shader1, matSphere);
            spheres->getTransformation()->addScale(glm::vec3(0.3));
            spheres->getTransformation()->addTranslate(pos);
            addObject(spheres);
        }
    }
    else if (sceneNum == 5) {
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
        DrawableObject* sphere1 = new DrawableObject(sphere, sizeof(sphere), 2880, shaders[2], matSphere);
        sphere1->getTransformation()->addScale(glm::vec3(0.2));
        sphere1->getTransformation()->addTranslate(positions[0]);
        addObject(sphere1);
        DrawableObject* suzi = new DrawableObject(suziFlat, sizeof(suziFlat), 2904, shaders[1], matSphere);
        suzi->getTransformation()->addScale(glm::vec3(0.3));
        suzi->getTransformation()->addTranslate(positions[1]);
        addObject(suzi);
        DrawableObject* bush = new DrawableObject(bushes, sizeof(bushes), 8730, shaders[0], matSphere);
        bush->getTransformation()->addScale(glm::vec3(0.5));
        bush->getTransformation()->addTranslate(positions[2]);
        addObject(bush);
        DrawableObject* tree1 = new DrawableObject(tree, sizeof(tree), 92814, shaders[3], matSphere);
        tree1->getTransformation()->addScale(glm::vec3(0.05));
        tree1->getTransformation()->addTranslate(positions[3]);
        addObject(tree1);


    }

}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::draw() const {
    if (sceneNum == 1) {
        objects[1]->getTransformation()->addRotate(0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    for (const auto& object : objects) {
        object->draw();
    }
}

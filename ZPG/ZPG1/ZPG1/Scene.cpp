#include "Scene.h"
#include "DrawableObject.h"
#include <GL/glew.h>
#include <cstdlib>
#include <ctime>
#include "Camera.h"
#include "Observer.h"



const char* vertex_shader_src =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=0) in vec3 vn;"
"out vec3 color;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"void main () {"
"       color = vn;"
"       gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
"}";

const char* fragment_shader_src =
"#version 330\n"
"out vec4 frag_colour;"
"in vec3 color;"
"void main () {"
"       frag_colour = vec4 (color, 1.0);"
"}";

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

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"uniform mat4 modelMatrix;"
"void main () {"
"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";
const char* vertex_shader2 =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"uniform mat4 modelMatrix;"
"void main () {"
"     gl_Position = modelMatrix * vec4 (vp, 1.0);"
"}";

const char* fragment_shader2 =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.5, 0.0, 1.0, 1.0);"
"}";

Scene::Scene(int sceneNum) { this->sceneNum = sceneNum; camera = new Camera(); }

Scene::~Scene() {
    for (auto object : objects) {
        delete object;
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

void Scene::initialize() {
    if (sceneNum == 1) {
        ShaderProgram* shader1 = new ShaderProgram(vertex_shader_src, fragment_shader_src);
        camera->addObserver(shader1);
        shader1->use();
        shader1->setProjectionMatrix(camera->getProjectionMatrix());
        shader1->setViewMatrix(camera->getViewMatrix());
        shader1->stop();

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
    }
    else if (sceneNum == 2) {
        ShaderProgram* shader1 = new ShaderProgram(vertex_shader, fragment_shader);
        ShaderProgram* shader2 = new ShaderProgram(vertex_shader2, fragment_shader2);
        addObject(new DrawableObject(points1, sizeof(points1), 6, shader1));
        addObject(new DrawableObject(points2, sizeof(points2), 3, shader2));
    }

}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::draw() const {
    for (const auto& object : objects) {
        object->draw();
    }
}

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();
    void run();

private:
    GLFWwindow* window;
    Scene* scene;
    Scene* scene2;
    Scene* scene3;
    Scene* scene4;
    Scene* scene5;
    int currentSceneIndex;
    void render();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void swapScene();
    Scene* getCurrentScene() const;
    static Application* instance;
    bool moveForwardPressed = false;
    bool moveBackwardPressed = false;
    bool moveRightPressed = false;
    bool moveLeftPressed = false;
    bool rightMouseButtonPressed = false;
};

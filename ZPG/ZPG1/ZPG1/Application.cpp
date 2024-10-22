#include "Application.h"
#include "Scene.h"
Application* Application::instance = nullptr;
Application::Application(int width, int height, const char* title) {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, window_size_callback);

    scene = new Scene(1);
    scene->initialize();
    sceneUsed = 1;
    scene2 = new Scene(2);
    scene2->initialize();
    Application::instance = this;
}

Application::~Application() {
    delete scene;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        render();
    }
}

void Application::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (moveForwardPressed) {
        instance->scene->moveForward();
    }
    if (moveBackwardPressed) {
        instance->scene->moveBackward();
    }
    if (moveRightPressed) {
        instance->scene->moveRight();
    }
    if (moveLeftPressed) {
        instance->scene->moveLeft();
    }
    scene->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::swapScene() {
    Scene* temp = scene;
    scene = scene2;
    scene2 = temp;
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        if (instance) {
            instance->swapScene();
        }
    }
    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS) {
            instance->moveForwardPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            instance->moveForwardPressed = false;
        }
    }
    if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            instance->moveBackwardPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            instance->moveBackwardPressed = false;
        }
    }
    if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            instance->moveLeftPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            instance->moveLeftPressed = false;
        }
    }
    if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            instance->moveRightPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            instance->moveRightPressed = false;
        }
    }
}
void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static float lastX = xpos;
    static float lastY = ypos;
    float offsetX = xpos - lastX;
    float offsetY = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    instance->scene->rotate(offsetX, offsetY);
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

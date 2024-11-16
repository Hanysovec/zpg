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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // dodelat na leve tlacitko
    glfwSetFramebufferSizeCallback(window, window_size_callback);

    scene = new Scene(1);
    scene->initialize();
    scene2 = new Scene(2);
    scene2->initialize();
    scene3 = new Scene(3);
    scene3->initialize();
    scene4 = new Scene(4);
    scene4->initialize();
    scene5 = new Scene(5);
    scene5->initialize();

    currentSceneIndex = 1;
    Application::instance = this;
}

Application::~Application() {
    delete scene;
    delete scene2;
    delete scene3;
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
        instance->getCurrentScene()->moveForward();
    }
    if (moveBackwardPressed) {
        instance->getCurrentScene()->moveBackward();
    }
    if (moveRightPressed) {
        instance->getCurrentScene()->moveRight();
    }
    if (moveLeftPressed) {
        instance->getCurrentScene()->moveLeft();
    }

    getCurrentScene()->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::swapScene() {
    currentSceneIndex = (currentSceneIndex % 5) + 1;
}

Scene* Application::getCurrentScene() const {
    switch (currentSceneIndex) {
    case 1: return scene;
    case 2: return scene2;
    case 3: return scene3;
    case 4: return scene4;
    case 5: return scene5;
    default: return nullptr;
    }
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

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            instance->leftMouseButtonPressed = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else if (action == GLFW_RELEASE) {
            instance->leftMouseButtonPressed = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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

    if (instance->leftMouseButtonPressed) {
        instance->getCurrentScene()->rotate(offsetX, offsetY);
    }
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    instance->getCurrentScene()->getCamera()->setAspectRatio(aspectRatio);
}

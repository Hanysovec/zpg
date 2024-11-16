#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Subject;
class Observer
{
public:
    virtual void update(Subject* subject) = 0;
};


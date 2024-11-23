#pragma once
#include <GL/glew.h>
class BasicModel
{
public:
    virtual ~BasicModel() {}
    virtual void draw() const = 0;
};


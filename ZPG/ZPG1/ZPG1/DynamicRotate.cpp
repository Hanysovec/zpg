#include "DynamicRotate.h"

DynamicRotate::DynamicRotate(float angle, float speed, const glm::vec3& axis)
{
    this->angle = angle;
    this->rotationSpeed = speed;
    this->axis = axis;
}

glm::mat4 DynamicRotate::getMatrix(const glm::mat4& matrix)
{
    angle += rotationSpeed;
    return glm::rotate(matrix, angle, axis);
}

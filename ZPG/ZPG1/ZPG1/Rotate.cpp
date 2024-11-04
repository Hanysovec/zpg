#include "Rotate.h"

Rotate::Rotate(float angle, const glm::vec3& axis)
{
	this->axis = axis;
	this->angle = angle;
}

glm::mat4 Rotate::apply(const glm::mat4& matrix) const
{
	return glm::rotate(matrix, angle, axis);
}

#include "Scale.h"
Scale::Scale(const glm::vec3& scale)
{
	this->scale = scale;
}

glm::mat4 Scale::apply(const glm::mat4& matrix) const
{
	return glm::scale(matrix, scale);
}

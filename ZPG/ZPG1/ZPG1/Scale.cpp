#include "Scale.h"
Scale::Scale(const glm::vec3& scale)
{
	this->scale = scale;
}

glm::mat4 Scale::getMatrix(const glm::mat4& matrix)
{
	return glm::scale(matrix, scale);
}

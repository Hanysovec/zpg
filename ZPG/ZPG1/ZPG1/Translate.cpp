#include "Translate.h"


Translate::Translate(const glm::vec3& offset)
{
	this->offset = offset;
}

glm::mat4 Translate::getMatrix(const glm::mat4& matrix)
{
	return glm::translate(matrix, offset);
}

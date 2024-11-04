#include "Translate.h"


Translate::Translate(const glm::vec3& offset)
{
	this->offset = offset;
}

glm::mat4 Translate::apply(const glm::mat4& matrix) const
{
	return glm::translate(matrix, offset);
}

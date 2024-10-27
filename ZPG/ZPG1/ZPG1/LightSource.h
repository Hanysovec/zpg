#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Subject.h"
class LightSource : public Subject
{
public:
	LightSource(glm::vec3 position);
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;
private:
	glm::vec3 position;
};


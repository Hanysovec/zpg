#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Subject.h"
#include "Observer.h"
#include "Camera.h"
class SpotLight : public Subject, public Observer
{
public:
	SpotLight(glm::vec3 position, glm::vec3 direction, float innerAngle, float outerAngle);
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;
	void setDirection(glm::vec3 direction);
	glm::vec3 getDirection();
	void update(Subject* subject);
	float getOuterCutOff();
	float getInnerCutOff();
private:
	glm::vec3 position;
	glm::vec3 direction;
	float innerAngle;
	float outerAngle;
};


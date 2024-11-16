#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float innerAngle, float outerAngle)
{
    this->position = position;
    this->direction = direction;
    this->innerAngle = innerAngle;
    this->outerAngle = outerAngle;
}

void SpotLight::setPosition(glm::vec3 position)
{
    this->position = position;
    notifyObservers();
}

glm::vec3 SpotLight::getPosition() const
{
    return this->position;
}

void SpotLight::setDirection(glm::vec3 direction)
{
    this->direction = direction;
    notifyObservers();
}

glm::vec3 SpotLight::getDirection()
{
    return this->direction;
}

void SpotLight::update(Subject* subject) {
    Camera* camera = dynamic_cast<Camera*>(subject);
    if (camera) {
        setPosition(camera->getPosition());
        setDirection(camera->getForward());
    }
}

float SpotLight::getOuterCutOff()
{
    return outerAngle;
}

float SpotLight::getInnerCutOff()
{
    return innerAngle;
}

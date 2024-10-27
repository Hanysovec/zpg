#include "LightSource.h"

LightSource::LightSource(glm::vec3 position){
    this->position = position;
}

void LightSource::setPosition(glm::vec3 position){
    this->position = position;
    notifyObservers(position);
}

glm::vec3 LightSource::getPosition() const{
    return this->position;
}

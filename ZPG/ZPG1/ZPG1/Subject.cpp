#include "Subject.h"

void Subject::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notifyObservers(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition) {
    for (Observer* observer : observers) {
        observer->onCameraUpdate(viewMatrix, projectionMatrix, cameraPosition);
    }
}
void Subject::notifyObservers(const glm::vec3& position) {
    for (Observer* observer : observers) {
        observer->onLightUpdate(position);
    }
}

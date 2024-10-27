#pragma once
#include "Observer.h"
#include <vector>

class Subject {
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);

protected:
    void notifyObservers(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition);
    void notifyObservers(const glm::vec3& position);

private:
    std::vector<Observer*> observers;
};

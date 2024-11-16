#pragma once
#include "Observer.h"
#include <vector>

class Subject {
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    virtual ~Subject() = default;

protected:
    /*void notifyObservers(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition); //vlozit jenom int co oznaci co se stalo
    void notifyObservers(const glm::vec3& position);
    void notifyObservers(const glm::vec3& position, const glm::vec3& direction);*/
    void notifyObservers();

private:
    std::vector<Observer*> observers;
};

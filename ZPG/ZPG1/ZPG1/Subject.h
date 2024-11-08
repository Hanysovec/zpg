#pragma once
#include "Observer.h"
#include <vector>

class Subject {
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);

protected:
    void notifyObservers(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition); //vlozit jenom int co oznaci co se stalo
    void notifyObservers(const glm::vec3& position);
    //void notifyObservers(int i);

private:
    std::vector<Observer*> observers;
};

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformation { // vector transformaci(objektu) a muzu kdykoliv pristoupit, rodicovska trida a z te dedi rotate atd.
public:
    Transformation();
    void translate(const glm::vec3& offset);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scale);
    const glm::mat4& getMatrix() const;

private:
    glm::mat4 modelMatrix;
};



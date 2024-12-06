#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "BaseTransform.h"
#include <vector>
#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"
#include "DynamicRotate.h"

/*class Transformation { // vector transformaci(objektu) a muzu kdykoliv pristoupit, rodicovska trida a z te dedi rotate atd.
public:
    Transformation();
    void translate(const glm::vec3& offset);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scale);
    const glm::mat4& getMatrix() const;

private:
    glm::mat4 modelMatrix;
};*/
class Transformation {
    std::vector<BaseTransform*> transforms;
    mutable glm::mat4 modelMatrix = glm::mat4(1.0f);

public:
    void addTranslate(const glm::vec3& offset);
    void addRotate(float angle, const glm::vec3& axis);
    void addScale(const glm::vec3& scaleF);
    void addDynamicRotate(float angle, float speed, const glm::vec3& axis);
    const glm::mat4& getMatrix() const;
};



#include "Material.h"

Material::Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs)
{
    this->ra = ra;
    this->rd = rd;
    this->rs = rs;
}

glm::vec3 Material::getAmbient()
{
    return this->ra;
}

glm::vec3 Material::getDiffuse()
{
    return this->rd;
}

glm::vec3 Material::getSpecular()
{
    return this->rs;
}

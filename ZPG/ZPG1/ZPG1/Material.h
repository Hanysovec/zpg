#pragma once
#include <glm/glm.hpp>
class Material
{
public:
	Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs);
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
private:
	glm::vec3 ra;
	glm::vec3 rd;
	glm::vec3 rs;
};


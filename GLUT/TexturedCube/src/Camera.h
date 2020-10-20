#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();
    glm::mat4 getViewMatrix();

    void setCentre(glm::vec3 coordinates);
    void setEye(glm::vec3 coordinates);
    void setUpVector(glm::vec3 vector);

    glm::vec3 getCentre();
    glm::vec3 getEye();
    glm::vec3 getUpVector();

private:
    glm::vec3 centre;
    glm::vec3 eye;
    glm::vec3 upVector;
};

#endif // CAMERA_H

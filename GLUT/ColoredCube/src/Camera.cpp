#include "camera.h"

Camera::Camera()
{
    centre = glm::vec3(0.0f, 0.0f, 0.0f);
    eye = glm::vec3(0.0f, 0.0f, 0.0f);
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(centre, eye, upVector);
}

void Camera::setCentre(glm::vec3 coordinates)
{
    centre = coordinates;
}

void Camera::setEye(glm::vec3 coordinates)
{
    eye = coordinates;
}

void Camera::setUpVector(glm::vec3 vector)
{
    upVector = vector;
}

glm::vec3 Camera::getCentre()
{
    return centre;
}

glm::vec3 Camera::getEye()
{
    return eye;
}

glm::vec3 Camera::getUpVector()
{
    return upVector;
}



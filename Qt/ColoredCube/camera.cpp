#include "camera.h"

Camera::Camera()
{
    centre = QVector3D(0.0f, 0.0f, 0.0f);
    eye = QVector3D(0.0f, 0.0f, 0.0f);
    upVector = QVector3D(0.0f, 1.0f, 0.0f);
}

QMatrix4x4 Camera::getViewMatrix()
{
    QMatrix4x4 M;
    M.lookAt(centre, eye, upVector);
    return M;
}

void Camera::setCentre(QVector3D coordinates)
{
    centre = coordinates;
}

void Camera::setEye(QVector3D coordinates)
{
    eye = coordinates;
}

void Camera::setUpVector(QVector3D vector)
{
    upVector = vector;
}

QVector3D Camera::getCentre()
{
    return centre;
}

QVector3D Camera::getEye()
{
    return eye;
}

QVector3D Camera::getUpVector()
{
    return upVector;
}



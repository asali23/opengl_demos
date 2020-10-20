#include "object3d.h"

Object3D::Object3D()
{
    model = new Model();
    position = QVector3D(0.0f, 0.0f, 0.0f);
    orientation = QVector3D(qDegreesToRadians(0.0f), qDegreesToRadians(0.0f), qDegreesToRadians(0.0f));
}

Model* Object3D::getModel()
{
    return model;
}

QMatrix4x4 Object3D::getModelMatrix()
{
    QMatrix4x4 M;
    M.rotate(orientation.x(), QVector3D(0.0f, 0.0f, 1.0f));
    M.rotate(orientation.y(), QVector3D(1.0f, 0.0f, 0.0f));
    M.rotate(orientation.z(), QVector3D(0.0f, 1.0f, 0.0f));
    M.translate(position);
    return M;
}

void Object3D::setPosition(QVector3D coordinates)
{
    position = coordinates;
}

void Object3D::setOrientation(QVector3D angles)
{
    orientation = angles;
}

QVector3D Object3D::getPosition()
{
    return position;
}

QVector3D Object3D::getOrientation()
{
    return orientation;
}

void Object3D::initializeCubeObject()
{
    model->initializeCubeModel();
}

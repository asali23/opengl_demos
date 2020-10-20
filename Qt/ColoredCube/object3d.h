#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "model.h"

class Object3D
{
public:
    Object3D();
    Model* getModel();
    QMatrix4x4 getModelMatrix();

    void setPosition(QVector3D coordinates);
    void setOrientation(QVector3D angles);

    QVector3D getPosition();
    QVector3D getOrientation();

    void initializeCubeObject();

private:
    Model *model;
    QVector3D position;
    QVector3D orientation;
};

#endif // OBJECT3D_H

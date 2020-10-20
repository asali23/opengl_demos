#ifndef CAMERA_H
#define CAMERA_H

#include <QtMath>
#include <QMatrix4x4>
#include <QVector3D>

class Camera
{
public:
    Camera();
    QMatrix4x4 getViewMatrix();

    void setCentre(QVector3D coordinates);
    void setEye(QVector3D coordinates);
    void setUpVector(QVector3D vector);

    QVector3D getCentre();
    QVector3D getEye();
    QVector3D getUpVector();

private:
    QVector3D centre;
    QVector3D eye;
    QVector3D upVector;
};

#endif // CAMERA_H

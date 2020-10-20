#ifndef MODEL_H
#define MODEL_H

#include <QtMath>
#include <QMatrix4x4>
#include <QVector4D>
#include <QVector3D>

class Model
{
public:
    Model();
    void initializeVertices(unsigned int numberOfVertices);
    void setVertexCoordinates(unsigned int n, QVector3D value);
    void setVertexColor(unsigned int n, QVector3D value);

    QVector3D *getVertexCoordinatesArray();
    QVector3D *getVertexColorsArray();
    unsigned int getVertexCount();

    void rotateModel(float angle, QVector3D axis);

    void initializeCubeModel();

private:
    void initializeCubeVertices();
    void initializeCubeColors();

private:
    QVector3D *coordinates;
    unsigned int nVertices;
    QVector3D *colors;
};

#endif // MODEL_H

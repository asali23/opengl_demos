#ifndef MODEL_H
#define MODEL_H

#include <QtMath>
#include <QMatrix4x4>
#include <QVector4D>
#include <QVector3D>
#include <QVector2D>
#include <QString>
#include <QImage>
#include <QFile>

#include <vector>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

class Model
{
public:
    Model();
    void initializeVertices(unsigned int numberOfVertices);
    void setVertexCoordinates(unsigned int n, QVector3D value);
    void setVertexTextureCoordinates(unsigned int n, QVector2D value);
    void setTextureImage(QString filePath);

    QVector3D *getVertexCoordinatesArray();
    QVector2D *getVertexTextureCoordinatesArray();
    QImage getTextureImage();
    unsigned int getVertexCount();

    void rotateModel(float angle, QVector3D axis);
    void loadModelFromOBJFile(QString filePath);

    void initializeCubeModel();

private:
    void initializeCubeVertices();
    void initializeCubeTextureCoordinates();

private:
    QVector3D *coordinates;
    unsigned int nVertices;
    QVector2D *texCoords;
    QString textureImageFilePath;
};

#endif // MODEL_H

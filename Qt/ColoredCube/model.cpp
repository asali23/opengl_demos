#include "model.h"

Model::Model()
{
    nVertices = 0;
}

void Model::initializeVertices(unsigned int numberOfVertices)
{
    nVertices = numberOfVertices;
    coordinates = new QVector3D[nVertices];
    colors = new QVector3D[nVertices];
}

void Model::setVertexCoordinates(unsigned int n, QVector3D value)
{
    if (nVertices > 0 && n < nVertices)
        coordinates[n] = value;
}

void Model::setVertexColor(unsigned int n, QVector3D value)
{
    if (nVertices > 0 && n < nVertices)
        colors[n] = value;
}

QVector3D *Model::getVertexCoordinatesArray()
{
    return coordinates;
}

QVector3D *Model::getVertexColorsArray()
{
    return colors;
}

unsigned int Model::getVertexCount()
{
    return nVertices;
}

void Model::rotateModel(float angle, QVector3D axis)
{
    QMatrix4x4 R;
    R.rotate(angle, axis);
    for (int i = 0; i < nVertices; i++)
    {
        QVector4D w = R * QVector4D(coordinates[i], 1.0f);
        coordinates[i] = QVector3D(w);
    }
}

void Model::initializeCubeModel()
{
    initializeVertices(36);// 3 * 2 * 6 (12 triangles)
    initializeCubeVertices();
    initializeCubeColors();
}

void Model::initializeCubeVertices()
{
    QVector3D A(-0.5f, -0.5f, 0.5f), B(0.5f, -0.5f, 0.5f), C(0.5f, 0.5f, 0.5f), D(-0.5f, 0.5f, 0.5f);
    QVector3D E(-0.5f, 0.5f, -0.5f), F(0.5f, 0.5f, -0.5f), G(0.5f, -0.5f, -0.5f), H(-0.5f, -0.5f, -0.5f);
    QVector3D v[] = {
        A, B, C,
        C, D, A,
        B, G, F,
        B, F, C,
        C, F, E,
        C, E, D,
        D, E, A,
        A, E, H,
        H, F, E,
        H, G, F,
        A, B, H,
        H, B, G
    };
    for (unsigned int i = 0; i < 36; i++)
        setVertexCoordinates(i, v[i]);
}

void Model::initializeCubeColors()
{
    QVector3D black(0.0f, 0.0f, 0.0f), white(1.0f, 1.0f, 1.0f);
    QVector3D red(1.0f, 0.0f, 0.0f), green(0.0f, 1.0f, 0.0f), blue(0.0f, 0.0f, 1.0f);
    QVector3D yellow(1.0f, 1.0f, 0.0f), magenta(1.0f, 0.0f, 1.0f), cyan(0.0f, 1.0f, 1.0f);
    QVector3D c[] = {
        red, red, red,    // ABC
        red, red, red,    // CDA
        green, green, green,    // BGF
        green, green, green,    // BFC
        blue, blue, blue,    // CFE
        blue, blue, blue,    // CED
        yellow, yellow, yellow,    // DEA
        yellow, yellow, yellow,    // AEH
        magenta, magenta, magenta,    // HFE
        magenta, magenta, magenta,    // HGF
        cyan, cyan, cyan,    // ABH
        cyan, cyan, cyan    // HBG
    };
    for (unsigned int i = 0; i < 36; i++)
        setVertexColor(i, c[i]);
}

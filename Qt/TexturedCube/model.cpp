#include "model.h"

Model::Model()
{
    nVertices = 0;
    textureImageFilePath = QString();
}

void Model::initializeVertices(unsigned int numberOfVertices)
{
    nVertices = numberOfVertices;
    coordinates = new QVector3D[nVertices];
    texCoords = new QVector2D[nVertices];
}

void Model::setVertexCoordinates(unsigned int n, QVector3D value)
{
    if (nVertices > 0 && n < nVertices)
        coordinates[n] = value;
}

void Model::setVertexTextureCoordinates(unsigned int n, QVector2D value)
{
    if (nVertices > 0 && n < nVertices)
        texCoords[n] = value;
}

void Model::setTextureImage(QString filePath)
{
    textureImageFilePath = filePath;
}

QVector3D *Model::getVertexCoordinatesArray()
{
    return coordinates;
}

QVector2D *Model::getVertexTextureCoordinatesArray()
{
    return texCoords;
}

QImage Model::getTextureImage()
{
    return QImage(textureImageFilePath);
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

void Model::loadModelFromOBJFile(QString filePath)
{
    QVector<unsigned int> vertexIndices, uvIndices, normalIndices;
    QVector<QVector3D> temp_vertices;
    QVector<QVector2D> temp_uvs;
    QVector<QVector3D> temp_normals;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if (line.startsWith(QString("v ")))
            {
                float x, y, z;
                sscanf(line.toStdString().c_str(), "v %f %f %f", &x, &y, &z);
                temp_vertices.push_back(QVector3D(x, y, z));
            }
            else if (line.startsWith(QString("vt")))
            {
                float x, y;
                sscanf(line.toStdString().c_str(), "vt %f %f", &x, &y);
                temp_uvs.push_back(QVector2D(x, y));
            }
            else if (line.startsWith(QString("vn")))
            {
                float x, y, z;
                sscanf(line.toStdString().c_str(), "vn %f %f %f", &x, &y, &z);
                temp_normals.push_back(QVector3D(x, y, z));
            }
            else if (line.startsWith(QString("f ")))
            {
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                sscanf(line.toStdString().c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                       &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                        &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                        &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);

                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);

                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }
        file.close();

        unsigned int n = vertexIndices.size();
        initializeVertices(n);
        for (unsigned int i=0; i < n; i++)
        {
            coordinates[i] = temp_vertices[vertexIndices[i] - 1];
            texCoords[i] = temp_uvs[uvIndices[i] - 1];
        }
    }
    else
        qDebug(QString("Could not open %1").arg(filePath).toStdString().c_str());
}

void Model::initializeCubeModel()
{
    initializeVertices(36);// 3 * 2 * 6 (12 triangles)
    //initializeCubeVertices();
    //initializeCubeTextureCoordinates();
    loadModelFromOBJFile(QString(":/models/Cube.obj"));
    setTextureImage(QString(":/images/texture.png"));
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

void Model::initializeCubeTextureCoordinates()
{
    QVector2D A(0.25f, 0.0f), B(0.5f, 0.0f), C(0.5f, 0.25f), D(0.25f, 0.25f);
    QVector2D E(0.0f, 0.25f), F(0.75f, 0.25f), G(0.75f, 0.0f), H(0.0f, 0.0f);
    QVector2D A_(0.25f, 1.0f), B_(0.5f, 1.0f), E_(0.25f, 0.5f), F_(0.5f, 0.5f);
    QVector2D G_(0.5f, 0.75f), H_(0.25f, 0.75f);
    QVector2D t[] = {
        A, B, C,
        C, D, A,
        B, G, F,
        B, F, C,
        C, F_, E_,
        C, E_, D,
        D, E, A,
        A, E, H,
        H_, F_, E_,
        H_, G_, F_,
        A_, B_, H_,
        H_, B_, G_
    };
    for (unsigned int i = 0; i < 36; i++)
        setVertexTextureCoordinates(i, t[i]);
}

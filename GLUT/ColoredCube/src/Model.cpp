#include "model.h"

Model::Model()
{
    nVertices = 0;
}

void Model::initializeVertices(unsigned int numberOfVertices)
{
    nVertices = numberOfVertices;
    coordinates = new glm::vec3[nVertices];
    colors = new glm::vec3[nVertices];
}

void Model::setVertexCoordinates(unsigned int n, glm::vec3 value)
{
    if (nVertices > 0 && n < nVertices)
        coordinates[n] = value;
}

void Model::setVertexColor(unsigned int n, glm::vec3 value)
{
    if (nVertices > 0 && n < nVertices)
        colors[n] = value;
}

glm::vec3 *Model::getVertexCoordinatesArray()
{
    return coordinates;
}

glm::vec3 *Model::getVertexColorsArray()
{
    return colors;
}

unsigned int Model::getVertexCount()
{
    return nVertices;
}

void Model::rotateModel(float angle, glm::vec3 axis)
{
    glm::mat4 R = glm::rotate(glm::mat4(1.0), angle, axis);
    for (int i = 0; i < nVertices; i++)
    {
        glm::vec3 v = coordinates[i];
        glm::vec4 w = R * glm::vec4(v.x, v.y, v.z, 1.0f);
        coordinates[i] = glm::vec3(w.x, w.y, w.z);
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
    glm::vec3 A(-0.5f, -0.5f, 0.5f), B(0.5f, -0.5f, 0.5f), C(0.5f, 0.5f, 0.5f), D(-0.5f, 0.5f, 0.5f);
    glm::vec3 E(-0.5f, 0.5f, -0.5f), F(0.5f, 0.5f, -0.5f), G(0.5f, -0.5f, -0.5f), H(-0.5f, -0.5f, -0.5f);
    glm::vec3 v[] = {
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
    glm::vec3 black(0.0f, 0.0f, 0.0f), white(1.0f, 1.0f, 1.0f);
    glm::vec3 red(1.0f, 0.0f, 0.0f), green(0.0f, 1.0f, 0.0f), blue(0.0f, 0.0f, 1.0f);
    glm::vec3 yellow(1.0f, 1.0f, 0.0f), magenta(1.0f, 0.0f, 1.0f), cyan(0.0f, 1.0f, 1.0f);
    glm::vec3 c[] = {
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

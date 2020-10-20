#include "texture.h"

Texture::Texture(const char* textureFilePath)
{
    textureImageFilePath = new QString(textureFilePath);
    coordinateCount = 0;
}

void Texture::initializeCoordinates(unsigned int nCoordinates)
{
    coordinateCount = nCoordinates;
    coordinates = new glm::vec2[coordinateCount];
}

glm::vec2& Texture::operator[](unsigned int i)
{
    return coordinates[i];
}

unsigned int Texture::getCoordinatesCount()
{
    return coordinateCount;
}

QString Texture::getFilePath()
{
    return (*textureImageFilePath);
}

void Texture::initializeCubeCoordinates()
{
    textureImageFilePath = new QString(":/images/cubeTexture.png");

    glm::vec2 texA(0.25f, 0.0f), texB(0.5f, 0.0f), texC(0.5f, 0.25f), texD(0.25f, 0.25f);
    glm::vec2 texE(0.0f, 0.25f), texF(0.75f, 0.25f), texG(0.75f, 0.0f), texH(0.0f, 0.0f);
    glm::vec2 texA_(0.25f, 1.0f), texB_(0.5f, 1.0f), texE_(0.25f, 0.5f);
    glm::vec2 texF_(0.5f, 0.5f), texG_(0.5f, 0.75f), texH_(0.25f, 0.75f);

    initializeCoordinates(36);     // 3 * 2 * 6 (12 triangles)

    coordinates[0] = texA; coordinates[1] = texB; coordinates[2] = texC;
    coordinates[3] = texC; coordinates[4] = texD; coordinates[5] = texA;
    coordinates[6] = texB; coordinates[7] = texG; coordinates[8] = texF;
    coordinates[9] = texB; coordinates[10] = texF; coordinates[11] = texC;
    coordinates[12] = texC; coordinates[13] = texF_; coordinates[14] = texE_;
    coordinates[15] = texC; coordinates[16] = texE_; coordinates[17] = texD;
    coordinates[18] = texD; coordinates[19] = texE; coordinates[20] = texA;
    coordinates[21] = texA; coordinates[22] = texE; coordinates[23] = texH;
    coordinates[24] = texH_; coordinates[25] = texF_; coordinates[26] = texE_;
    coordinates[27] = texH_; coordinates[28] = texG_; coordinates[29] = texF_;
    coordinates[30] = texA_; coordinates[31] = texB_; coordinates[32] = texH_;
    coordinates[33] = texH_; coordinates[34] = texB_; coordinates[35] = texG_;
}

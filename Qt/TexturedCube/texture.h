#ifndef TEXTURE_H
#define TEXTURE_H

#include <QString>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture
{
public:
    Texture(const char* textureFilePath);
    void initializeCoordinates(unsigned int nCoordinates);
    glm::vec2& operator[](unsigned int i);
    unsigned int getCoordinatesCount();
    QString getFilePath();
    void initializeCubeCoordinates();

private:
    QString *textureImageFilePath;
    glm::vec2 *coordinates;
    unsigned int coordinateCount;
};

#endif // TEXTURE_H

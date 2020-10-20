#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "TextureImage.h"

class Model
{
public:
    Model();
	~Model();
    void initializeVertices(unsigned int numberOfVertices);
    void setVertexCoordinates(unsigned int n, glm::vec3 value);
    void setVertexTextureCoordinates(unsigned int n, glm::vec2 value);
	void setTextureImage(const char* filePath);

    glm::vec3 *getVertexCoordinatesArray();
    glm::vec2 *getVertexTextureCoordinatesArray();
	TextureImage *getTextureImage();
    unsigned int getVertexCount();
	void loadModelFromOBJFile(const char* filePath);
private:
    glm::vec3 *coordinates;
    unsigned int nVertices;
	glm::vec2 *textureCoordinates;
	TextureImage *textureImage;
};

#endif // MODEL_H
#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    void setVertexCoordinates(unsigned int n, glm::vec3 value);
    void setVertexColor(unsigned int n, glm::vec3 value);

    glm::vec3 *getVertexCoordinatesArray();
    glm::vec3 *getVertexColorsArray();
    unsigned int getVertexCount();
	
    void rotateModel(float angle, glm::vec3 axis);
	
    void initializeCubeModel();

private:
    void initializeCubeVertices();
    void initializeCubeColors();

private:
    glm::vec3 *coordinates;
    unsigned int nVertices;
    glm::vec3 *colors;
};

#endif // MODEL_H
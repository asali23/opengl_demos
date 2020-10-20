#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.h"

static char TEXTURE_IMAGE_FILE_PATH[] = "C:/workspace/learning/OpenGL/TexturedCube/images/texture.png";
static char MODEL_OBJ_FILE_PATH[] = "C:/workspace/learning/OpenGL/TexturedCube/models/Cube.obj";

class Object3D
{
public:
    Object3D();
    Model* getModel();
    glm::mat4 getModelMatrix();

    void setPosition(glm::vec3 coordinates);
    void setOrientation(glm::vec3 angles);

    glm::vec3 getPosition();
    glm::vec3 getOrientation();

    void initializeCubeObject();

private:
    Model *model;
    glm::vec3 position;
    glm::vec3 orientation;
};

#endif // OBJECT3D_H
#include "object3d.h"

Object3D::Object3D()
{
    model = new Model();
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    orientation = glm::vec3(0.0f, 0.0f, 0.0f);
}

Model* Object3D::getModel()
{
    return model;
}

glm::mat4 Object3D::getModelMatrix()
{
    glm::mat4 t(1.0);
    t = glm::rotate(t, orientation.x, glm::vec3(0.0f, 0.0f, 1.0f));
    t = glm::rotate(t, orientation.y, glm::vec3(1.0f, 0.0f, 0.0f));
    t = glm::rotate(t, orientation.z, glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::translate(t, position);
    return t;
}

void Object3D::setPosition(glm::vec3 coordinates)
{
    position = coordinates;
}

void Object3D::setOrientation(glm::vec3 angles)
{
    orientation = angles;
}

glm::vec3 Object3D::getPosition()
{
    return position;
}

glm::vec3 Object3D::getOrientation()
{
    return orientation;
}

void Object3D::initializeCubeObject()
{
	model->loadModelFromOBJFile(MODEL_OBJ_FILE_PATH);
	model->setTextureImage(TEXTURE_IMAGE_FILE_PATH);
}

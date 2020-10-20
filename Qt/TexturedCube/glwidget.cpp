#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    fov = 45.0f;
    zNear = 0.01f;
    zFar = 100.0f;

    cubeObject = new Object3D();
    cubeObject->initializeCubeObject();

    float r = 4.0;
    float a = qDegreesToRadians(30.0f);
    camera = new Camera();
    camera->setCentre(QVector3D(0.0f, 0.0f, 6.0f));

    hAngle = 0.0f; vAngle = 0.0f;
}

GLWidget::~GLWidget()
{

}

void GLWidget::loadObjects()
{
    shader = new QOpenGLShaderProgram();
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_shader.glsl");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment_shader.glsl");
    shader->link();
    shader->bind();

    VAO = new QOpenGLVertexArrayObject();
    VAO->create();
    VAO->bind();

    vertexCoordsVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vertexCoordsVBO->create();
    vertexCoordsVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexCoordsVBO->bind();
    vertexCoordsVBO->allocate(cubeObject->getModel()->getVertexCoordinatesArray(), cubeObject->getModel()->getVertexCount() * sizeof(QVector3D));
    vertexCoordsVBO->write(0, cubeObject->getModel()->getVertexCoordinatesArray(), cubeObject->getModel()->getVertexCount() * sizeof(QVector3D));

    shader->enableAttributeArray("position");
    shader->setAttributeBuffer("position", GL_FLOAT, 0, 3, 0);

    texCoordsVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    texCoordsVBO->create();
    texCoordsVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    texCoordsVBO->bind();
    texCoordsVBO->allocate(cubeObject->getModel()->getVertexTextureCoordinatesArray(), cubeObject->getModel()->getVertexCount() * sizeof(QVector2D));
    texCoordsVBO->write(0, cubeObject->getModel()->getVertexTextureCoordinatesArray(), cubeObject->getModel()->getVertexCount() * sizeof(QVector2D));

    shader->enableAttributeArray("texCoords");
    shader->setAttributeBuffer("texCoords", GL_FLOAT, 0, 2, 0);

    texture = new QOpenGLTexture(cubeObject->getModel()->getTextureImage().mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    vertexCoordsVBO->release();
    texCoordsVBO->release();
    VAO->release();
    shader->release();
}

void GLWidget::initializeGL()
{
    this->setGeometry(QRect(100, 100, 600, 600));
    initializeOpenGLFunctions();    //Initializes OpenGL function resolution for the current context.
    loadObjects();
    glClearColor(0.0, 0.0, 0.0, 0);
}

void GLWidget::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    shader->bind();
    VAO->bind();
    texture->bind();

    QMatrix4x4 modelMatrix;
    modelMatrix = cubeObject->getModelMatrix();
    shader->setUniformValue("Model", modelMatrix);

    QMatrix4x4 viewMatrix = camera->getViewMatrix();
    shader->setUniformValue("View", viewMatrix);

    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(fov, (float)this->height()/this->width(), zNear, zFar);
    shader->setUniformValue("Projection", projectionMatrix);

    glDrawArrays(GL_TRIANGLES, 0, cubeObject->getModel()->getVertexCount());

    texture->release();
    VAO->release();
    shader->release();
}

void GLWidget::resizeGL(int width, int height)
{
    float aspect = (float)width / (height ? height : 1);
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(fov, (float)this->height()/this->width(), zNear, zFar);
    shader->setUniformValue("Projection", projectionMatrix);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    isMouseButtonPressed = true;
    mousePosition.x = event->localPos().x();
    mousePosition.y = event->localPos().y();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    isMouseButtonPressed = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isMouseButtonPressed)
    {
        //qDebug(QString("Mouse: [%1 %2]").arg(event->x()).arg(event->y()).toStdString().c_str());
        if (up.y() > 0)
            hAngle += -3.14/2.0f * (event->localPos().x() - mousePosition.x) / this->width();
        else
            hAngle -= -3.14/2.0f * (event->localPos().x() - mousePosition.x) / this->width();
        vAngle += 3.14/2.0f * (event->localPos().y() - mousePosition.y) / this->height();
        //qDebug(QString("hAngle = %1 vAngle = %2").arg(hAngle).arg(vAngle).toStdString().c_str());

        QVector3D c = camera->getCentre();
        float r = (float)sqrt((double)c.x() * c.x() + c.y() * c.y() + c.z() * c.z());
        QVector3D direction = QVector3D(r * sin(hAngle) * cos(vAngle), r * sin(vAngle), r * cos(hAngle) * cos(vAngle));
        camera->setCentre(direction);

        QVector3D right = QVector3D(sin(hAngle - 1.67f), 0, cos(hAngle - 1.67f));
        up = QVector3D::crossProduct(right, direction);
        //qDebug(QString("up: [%1 %2 %3]").arg(up.x).arg(up.y).arg(up.z).toStdString().c_str());
        camera->setUpVector(up);

        this->update();
    }
    mousePosition.x = event->localPos().x();
    mousePosition.y = event->localPos().y();
}

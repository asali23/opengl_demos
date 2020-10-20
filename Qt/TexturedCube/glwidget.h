#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QtMath>
#include <QMatrix4x4>
#include <QVector4D>
#include <QVector3D>

#include "object3d.h"
#include "camera.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void loadObjects();
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    float fov, zNear, zFar;
    Object3D *cubeObject;
    Camera *camera;
    QOpenGLVertexArrayObject* VAO;
    QOpenGLBuffer* vertexCoordsVBO;
    QOpenGLBuffer* texCoordsVBO;
    QOpenGLShaderProgram* shader;
    struct point
    {
        int x;
        int y;
    } mousePosition;
    bool isMouseButtonPressed;
    float hAngle, vAngle;
    QVector3D up;
    QOpenGLTexture *texture;
};

#endif // GLWIDGET_H

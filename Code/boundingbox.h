#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QVector3D>
#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_1>
#include <QWidget>

// On fait une BoundingBox AABB
class BoundingBox : protected QOpenGLFunctions_3_1
{
    QVector3D _min;
    QVector3D _max;

    bool isValid(const QVector3D & min, const QVector3D &max);

public:
    BoundingBox();
    BoundingBox(const QVector3D & min, const QVector3D &max);

    QVector3D center();
    QVector3D extents(); // distances entre le centre et chaque face

    void render(QOpenGLShaderProgram *program);
    void print();
};

#endif // BOUNDINGBOX_H

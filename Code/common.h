#ifndef COMMON_H
#define COMMON_H

#include <QVector3D>
#include <QVector2D>#include <QVector3D>
#include <QVector4D>
#include <QMatrix3x3>
#include <QMatrix4x4>

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_1>

#include <QWidget>
#include <QDebug>
#include <math.h>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;

    VertexData(){
        position = QVector3D(0,0,0);
        texCoord = QVector2D(0,0);
    }

    VertexData(QVector3D p, QVector2D t){
        position = p;
        texCoord = t;
    }
};

class Common
{
public:
    Common();
};

#endif // COMMON_H

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


#include "common.h"
#include "Transform.h"


// On fait une BoundingBox AABB
class BoundingBox : protected QOpenGLFunctions_3_1
{
    QVector3D _min;
    QVector3D _max;

    bool isValid(const QVector3D & min, const QVector3D &max);

public:
    // Methods
    BoundingBox();
    BoundingBox(const BoundingBox& bb);
    BoundingBox(const QVector3D & min, const QVector3D &max);

    QVector3D center();
    QVector3D extents(); // distances entre le centre et chaque face

    QVector3D min();
    void min(QVector3D & min);

    QVector3D max();
    void max(QVector3D & max);

    void print();
};

#endif // BOUNDINGBOX_H

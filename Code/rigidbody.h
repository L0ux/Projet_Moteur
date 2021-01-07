#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QVector3D>

class RigidBody
{
    bool hasGravity;
    bool isMovable;
    float mass;
    QVector3D centroid;
    QVector3D mass_center; // is the same as centroid if the object is uniform

public:
    RigidBody();
};

#endif // RIGIDBODY_H

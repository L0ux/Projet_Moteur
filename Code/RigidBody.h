#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <QVector3D>
#include <QDebug>
#include "Boundingbox.h"
#include "Mesh.h"

class RigidBody
{
    bool _hasGravity;
    bool _isMovable;
    bool _detectsCollisions;
    float _speed;
    float _acceleration;
    float _mass;
    QVector3D _centroid;
    QVector3D _mass_center; // is the same as centroid if the object is uniform
    Mesh mesh;

public:
    RigidBody(bool hasG = true, bool isMov = true, float sp = 0.0f, float acc = 0.0f, float mass = 1.0f);

    void print();

    bool hasGravity();
    void hasGravity(bool value);

    bool isMovable();
    void isMovable(bool value);

    bool detectsCollision();
    void detectsCollision(bool value);

    float speed();
    void speed(float sp);

    float acceleration();
    void acceleration(float acc);

    float mass();
    void mass(float m);
};

#endif // RIGIDBODY_H

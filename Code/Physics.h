#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector3D>
class Physics
{
public:
    Physics();

    static constexpr QVector3D gravityDirection = {0,-1,0}; // on va vers en bas
    static constexpr float gravityAcceleration = 0.03;//9.80665; // valeur moyenne sur terre
    static void computeGravityEffect(QVector3D & origin, float & sp);
};

#endif // PHYSICS_H

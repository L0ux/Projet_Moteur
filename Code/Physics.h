#ifndef PHYSICS_H
#define PHYSICS_H

#include <QVector3D>
class Physics
{
public:
    Physics();

    static QVector3D gravityDirection; // on va vers en bas
    static float gravityAcceleration;//9.80665; // valeur moyenne sur terre
    static void computeGravityEffect(QVector3D & origin, float & sp);
};

#endif // PHYSICS_H

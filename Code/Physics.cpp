#include "Physics.h"

Physics::Physics()
{

}

void Physics::computeGravityEffect(QVector3D & origin, float & sp){
    sp += gravityAcceleration;
    origin = origin + gravityDirection * sp;
}

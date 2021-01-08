#include "Physics.h"

QVector3D Physics::gravityDirection{0,-1,0};
float Physics::gravityAcceleration{0.03};

Physics::Physics()
{

}

void Physics::computeGravityEffect(QVector3D & origin, float & sp){
    sp += gravityAcceleration;
    origin = origin + gravityDirection * sp;
}

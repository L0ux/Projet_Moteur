#include "RigidBody.h"

RigidBody::RigidBody(bool hasG, bool isMov, float sp, float acc, float mass)
    : _hasGravity{hasG},_isMovable{isMov},_speed{sp},_acceleration{acc},_mass{mass}
{
}

bool RigidBody::hasGravity(){
    return _hasGravity;
}

void RigidBody::hasGravity(bool value){
    _hasGravity = value;
}

bool RigidBody::isMovable(){
    return _isMovable;
}

void RigidBody::isMovable(bool value){
    _isMovable = value;
}

float RigidBody::speed(){
    return _speed;
}

void RigidBody::speed(float sp){
    _speed = sp;
}

float RigidBody::acceleration(){
    return _acceleration;
}

void RigidBody::acceleration(float acc){
    _acceleration = acc;
}

float RigidBody::mass(){
    return _mass;
}

void RigidBody::mass(float m){
    _mass = m;
}

void RigidBody::print(){
    qInfo() << "RigidBody:";
}

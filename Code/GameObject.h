#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "common.h"
#include "Transform.h"
#include "RigidBody.h"
#include <QtDebug>

class GameObject
{

protected:
    Transform transform;
    BoundingBox bbox;

    BoundingBox transformBoundingBox(BoundingBox & bb, QMatrix4x4 & m);

public:
    GameObject(QString n);
    GameObject(QString n,GameObject * pere);

    //Attribut
    RigidBody rigidBody;


    std::vector<GameObject*> fils;
    GameObject* pere;
    QString nom;

    //Methode
    void print();
    void addFils(GameObject* f);
    void printFils();
    GameObject* getObject(QString n);
    void addPere(GameObject* p);
    QVector3D getWorldPosition();
    static GameObject * _world;

    Transform Transform();
    void Translate(QVector3D v);
    void Rotate(QVector3D r);
    void Scale(float s);

private:
    GameObject(); // only use to create world


};

#endif // GAMEOBJECT_H

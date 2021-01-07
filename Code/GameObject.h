#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"
#include "rigidbody.h"
#include <QtDebug>

class GameObject
{
public:
    GameObject(QString n);
    GameObject(QString n,GameObject * pere);

    //Attribut
    Transform transform;
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

private:
    GameObject(); // only use to create world


};

#endif // GAMEOBJECT_H

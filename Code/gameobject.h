#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"
#include <QtDebug>

class GameObject
{
public:
    GameObject(QString n);

    //Attribut
    Transform transform;
    std::vector<GameObject*> fils;
    QString nom;


    //Methode
    void addFils(GameObject* f);
    void printFils();
    void setTransform(Transform t);
    GameObject* getObject(QString n);
};

#endif // GAMEOBJECT_H

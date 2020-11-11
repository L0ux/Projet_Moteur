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
    GameObject* pere;
    QString nom;


    //Methode
    void addFils(GameObject* f);
    void printFils();
    GameObject* getObject(QString n);
    void addPere(GameObject* p);
};

#endif // GAMEOBJECT_H

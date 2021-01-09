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

    BoundingBox transformBoundingBox(QMatrix4x4 & m);

public:
    GameObject(QString n);
    GameObject(QString n,GameObject * pere);

    //Attribut
    static GameObject * _world;
    static std::vector<GameObject*> aabbSortedObjects;
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

    Transform Transform();
    QVector3D getWorldPosition();
    void Translate(QVector3D v);
    void Rotate(QVector3D r);
    void Scale(float s);
    bool collides(GameObject * other,QVector3D direction);


    static ushort findHighestVarianceAxis();
    static void sortAABBs(ushort axis);
    static bool compareBBs(const BoundingBox& lhs, const BoundingBox&rhs,ushort axis);

private:
    GameObject(); // only use to create world


};

struct AABBComparator{
    ushort axis;
    AABBComparator(ushort ax) : axis{ax}{}
    bool operator()(GameObject a,GameObject b){

    }
};

#endif // GAMEOBJECT_H

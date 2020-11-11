#ifndef CAMERA_H
#define CAMERA_H

#include "gameobject.h"

class Camera : public GameObject
{
public:
    //Attribu
    Camera(QString nom);
    QMatrix4x4 projection;

    //Methode
    QMatrix4x4 mv();
    QMatrix4x4 vue();
    QMatrix4x4 model();
};

#endif // CAMERA_H

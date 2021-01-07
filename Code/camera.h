#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera : public GameObject
{
public:
    //Attribu
    Camera(QString nom);
    Camera(QString nom, GameObject * pere);
    QMatrix4x4 projection;
    QMatrix4x4 v;

    //Methode
    void lookAt(QVector3D  position,QVector3D target,QVector3D up);
    QMatrix4x4 mv();
    QMatrix4x4 vue();
    QMatrix4x4 model();
};

#endif // CAMERA_H

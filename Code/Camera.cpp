#include "Camera.h"

Camera::Camera(QString nom) : GameObject(nom)
{
    projection = QMatrix4x4();
    v = QMatrix4x4();
    rigidBody.hasGravity(false);
}

Camera::Camera(QString nom,GameObject * father) : GameObject(nom,father)
{
    rigidBody.hasGravity(false);
    projection = QMatrix4x4();
    v = QMatrix4x4();
}


QMatrix4x4 Camera::mv(){
    return projection * transform.computeModel();
}

QMatrix4x4 Camera::vue(){
    //QMatrix3x3 v2 = this->pere->transform.computeModel().normalMatrix().transposed();
    QMatrix4x4 v = this->pere->Transform().computeModel() * this->v; //.inverted() * this->v;
    GameObject* p = this->pere->pere;
    while( p != nullptr ){
        //v2 = v2 * p->transform.computeModel().normalMatrix().transposed();
        v = v * p->Transform().computeModel();//.inverted();
        p = p->pere;
    }
    QMatrix4x4 vue(v);
    return vue;
}


QMatrix4x4 Camera::model(){
    return this->pere->Transform().computeModel() * this->transform.computeModel();
}

void Camera::lookAt(QVector3D  position,QVector3D target,QVector3D up){
    v = QMatrix4x4();
    v.lookAt(position,target,up);
}

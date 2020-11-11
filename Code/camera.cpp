#include "camera.h"

Camera::Camera(QString nom) : GameObject(nom)
{
    projection = QMatrix4x4();
}


QMatrix4x4 Camera::mv(){
    return projection * transform.computeModel();
}

QMatrix4x4 Camera::vue(){
    //QMatrix4x4 vue = this->pere->transform.computeModel().inverted();
    QMatrix3x3 v = this->pere->transform.computeModel().inverted().normalMatrix().transposed();
    GameObject* p = this->pere->pere;
    while( p != nullptr ){
        v = v * p->transform.computeModel().inverted().normalMatrix().transposed();
        p = p->pere;
    }
    QMatrix4x4 vue(v);
    return vue;
}


QMatrix4x4 Camera::model(){
    return this->pere->transform.computeModel() * this->transform.computeModel();
}

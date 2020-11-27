#include "camera.h"

Camera::Camera(QString nom) : GameObject(nom)
{
    projection = QMatrix4x4();
    v = QMatrix4x4();
}


QMatrix4x4 Camera::mv(){
    return projection * transform.computeModel();
}

QMatrix4x4 Camera::vue(){
    //QMatrix3x3 v2 = this->pere->transform.computeModel().normalMatrix().transposed();
    QMatrix4x4 v = this->pere->transform.computeModel().inverted() * this->v;
    GameObject* p = this->pere->pere;
    while( p != nullptr ){
        //v2 = v2 * p->transform.computeModel().normalMatrix().transposed();
        v = v * p->transform.computeModel().inverted();
        p = p->pere;
    }
    QMatrix4x4 vue(v);
    return vue;
}


QMatrix4x4 Camera::model(){
    return this->pere->transform.computeModel() * this->transform.computeModel();
}

void Camera::lookAt(QVector3D  position,QVector3D target,QVector3D up){
    v.lookAt(position,target,up);
}

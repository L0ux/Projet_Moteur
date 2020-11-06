#include "transform.h"


// Constructeur
Transform::Transform(){
    lModel = QMatrix4x4();
    model = QMatrix4x4();
    localScale = 1.f;
    localRotation = {0,0,0};
    localTranslation = {0,0,0};
}

QMatrix4x4 Transform::applyTranslation(){
    QMatrix4x4 m;
    m(0,3) = localTranslation[0];
    m(1,3) = localTranslation[1];
    m(2,3) = localTranslation[2];
    return m;
}

QMatrix4x4 Transform::applyScale(){
    QMatrix4x4 m;
    m(0,0) = localScale;
    m(1,1) = localScale;
    m(2,2) = localScale;
    //m(0,0) = localScale;
    return m;
}

QMatrix4x4 Transform::applyRotation(){
    QMatrix4x4 rX;
    QMatrix4x4 rY;
    QMatrix4x4 rZ;

    if(localRotation[0] !=0){
        rX(1,1) = cos(localRotation[0]);
        rX(1,2) = -sin(localRotation[0]);
        rX(2,1) = sin(localRotation[0]);
        rX(2,2) = cos(localRotation[0]);
    }
    if(localRotation[1] != 0){
        rY(0,0) = cos(localRotation[1]);
        rY(0,2) = sin(localRotation[1]);
        rY(2,0) = -sin(localRotation[1]);
        rY(2,2) = cos(localRotation[1]);
    }
    if(localRotation[2] != 0){
        rZ(0,0) = cos(localRotation[2]);
        rZ(0,1) = -sin(localRotation[2]);
        rZ(1,0) = sin(localRotation[2]);
        rZ(1,1) = cos(localRotation[2]);
    }

    return rZ * rY * rX; // peut-être qu'il faudra inverser l'ordre
}

float Transform::getScale(){
    return localScale;
};

Transform Transform::scale(float s){
    localScale = s;
    return *this;
}

QVector3D Transform::getRotation(){
    return localRotation;
};

Transform Transform::rotate(QVector3D r){
    qDebug() << "rotation" << r;
    localRotation = r;
    qDebug() << "local" << localRotation;
    return *this;
}

QVector3D Transform::getTranslation(){
    return localTranslation;
}

Transform Transform::translate(QVector3D v){
    localTranslation = v;
    return *this;
}

QMatrix4x4 Transform::getModel(){
    return model;
}

void Transform::setModel(QMatrix4x4 m){
    model = m;
}

// Methods

QMatrix4x4 Transform::computeModel(){
    model = applyTranslation() * applyRotation() * applyScale();
    return model;
}

Transform Transform::combine_with(Transform & t){
    model = t.getModel() * this->model;
    return *this;
};

void Transform::printTransform(){
    qDebug() << "Scale =" << localScale;
    qDebug() << "Rotation =" << localRotation;
    qDebug() << "Translation =" << localTranslation;
}

void Transform::lRotate(QVector3D r){
    QMatrix4x4 rX;
    QMatrix4x4 rY;
    QMatrix4x4 rZ;
    if(localRotation[0] !=0){
        rX(1,1) = cos(r[0]);
        rX(1,2) = -sin(r[0]);
        rX(2,1) = sin(r[0]);
        rX(2,2) = cos(r[0]);
    }
    if(localRotation[1] != 0){
        rY(0,0) = cos(r[1]);
        rY(0,2) = sin(r[1]);
        rY(2,0) = -sin(r[1]);
        rY(2,2) = cos(r[1]);
    }
    if(localRotation[2] != 0){
        rZ(0,0) = cos(r[2]);
        rZ(0,1) = -sin(r[2]);
        rZ(1,0) = sin(r[2]);
        rZ(1,1) = cos(r[2]);
    }

    /*qDebug() << "RZ" << rZ;
    qDebug() << "RY" << rY;
    qDebug() << "RX" << rX;*/

    lModel =  lModel * rZ * rY * rX;
}

void Transform::lTranslate(QVector3D t){
    QMatrix4x4 m;
    m(0,3) = t[0];
    m(1,3) = t[1];
    m(2,3) = t[2];

    lModel = lModel + m;
}

void Transform::lScale(float s){
    QMatrix4x4 m;
    m(0,0) = s;
    m(1,1) = s;
    m(2,2) = s;

    lModel = lModel + m;
}

void Transform::lPrintModel(){
    qDebug() << lModel;
}


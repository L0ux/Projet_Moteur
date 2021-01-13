#pragma once

#include "Common.h"

// --V2
class Transform{

private:
    QMatrix4x4 model;
    float localScale;
    QVector3D localRotation;
    QVector3D localTranslation;
    QMatrix4x4 applyTranslation();
    QMatrix4x4 applyScale();
    QMatrix4x4 applyRotation();

public:
    Transform();
    float getScale();
    Transform scale(float s);
    QVector3D getRotation();
    Transform rotate(QVector3D& r);
    QVector3D getTranslation();
    Transform translate(QVector3D& v);
    QMatrix4x4 getModel();
    void setModel(QMatrix4x4 m);
    QMatrix4x4 computeModel();
    Transform combine_with(Transform & t);
    void print();

    //Version LOUX
    QMatrix4x4 lModel;
    void lRotate(QVector3D& r);
    void lTranslate(QVector3D& t);
    void lScale(float s);
    void lPrintModel();

};

/* // -- V1
class Transform{
    QMatrix4x4 model;
    float localScale;
    QVector3D localRotation;
    QVector3D localTranslation;

    QMatrix4x4 applyTranslation(){
       QMatrix4x4 m;
       m(0,3) = localTranslation[0];
       m(1,3) = localTranslation[1];
       m(2,3) = localTranslation[2];
       return m;
    }

    QMatrix4x4 applyScale(){
        QMatrix4x4 m;
        m(0,0) = localScale;
        m(1,1) = localScale;
        m(2,2) = localScale;
        //m(0,0) = localScale;

        return m;
    }

    QMatrix4x4 applyRotation(){
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

        return rZ * rY * rX;
    }

public:

    // Constructeur
    Transform(){
        model = QMatrix4x4();
        localScale = 1.f;
        localRotation = {0,0,0};
        localTranslation = {0,0,0};
    }

    // Getters & Setters
    float getScale(){
        return localScale;
    };

    Transform scale(float s){
        localScale = s;
        return *this;
    }

    QVector3D getRotation(){
        return localRotation;
    };

    Transform rotate(QVector3D r){
        localRotation = r;
        return *this;
    }

    QVector3D getTranslation(){
        return localTranslation;
    }

    Transform translate(QVector3D v){
        localTranslation = v;
        return *this;
    }

    QMatrix4x4 getModel(){
        return model;
    }

    void setModel(QMatrix4x4 m){
        model = m;
    }

    // Methods

    QMatrix4x4 computeModel(){
        model = applyTranslation() * applyRotation() * applyScale();
        return model;
    }

    Transform combine_with(Transform & t){
        model = t.getModel() * this->model;
        return *this;
    };

    void printTransform(){
        qDebug() << "Scale =" << localScale;
        qDebug() << "Rotation =" << localRotation;
        qDebug() << "Translation =" << localTranslation;
    }


    // methods which i have no idea
    // what to do with but they were in the class course
    Transform inverse();

    QVector4D apply(QVector4D p);

    QVector3D applyToPoint(QVector3D p);
    QVector3D applyToVector(QVector3D v);
    QVector3D applyToVersor(QVector3D v);
    Transform interpolate_with(Transform& t, float k);*/

//};*/

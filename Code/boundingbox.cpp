#include "boundingbox.h"

BoundingBox::BoundingBox() : _min{0,0,0},_max{1,1,1}
{
}

BoundingBox::BoundingBox(const BoundingBox & bb)
{
    _min = bb._min;
    _max = bb._max;
}

BoundingBox::BoundingBox(const QVector3D & min, const QVector3D & max){
    if(isValid(min,max)){
        _min = min;
        _max = max;
    }
    else{
        if(isValid(max,min)){
            _min = max;
            _max = min;
        }
        else{
            qDebug() << "BoundingBox: Vous avez une erreur dans vos min et max,\net ce n'est pas juste une inversion des deux.";
            exit(1);
        }
    }
}

QVector3D BoundingBox::center(){
    return QVector3D(   (_min.x() + _max.x())/2
                      , (_min.y() + _max.y())/2
                      , (_min.z() + _max.z())/2);
}

QVector3D BoundingBox::extents(){
    QVector3D c = center();
    return QVector3D(   (_max.x() - c.x())
                      , (_max.y() - c.y())
                      , (_max.z() - c.z()));
}

bool BoundingBox::isValid(const QVector3D & min, const QVector3D & max){
    return min.x() < max.x() && min.y() < max.y() && min.z() < max.z();
}

QVector3D BoundingBox::min(){
    return _min;
}

void BoundingBox::min(QVector3D min){
    _min = min;
}

QVector3D BoundingBox::max(){
    return _max;
}

void BoundingBox::max(QVector3D max){
    _max = max;
}

void BoundingBox::print(){
    qDebug() << "BoundingBox:";
    qDebug() << "\tMin: (" << _min.x() << "," << _min.y() << "," << _min.z() << ")";
    qDebug() << "\tMax: (" << _max.x() << "," << _max.y() << "," << _max.z() << ")";

}

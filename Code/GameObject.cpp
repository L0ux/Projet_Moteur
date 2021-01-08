#include "GameObject.h"

GameObject::GameObject()
{
    nom = "World";
    transform = Transform();
    rigidBody = RigidBody();
    pere = nullptr;
}

GameObject * GameObject::_world = new GameObject();

GameObject::GameObject(QString n)
{
    nom = n;
    transform = Transform();
    rigidBody = RigidBody();
    GameObject::_world->addFils(this);
}

GameObject::GameObject(QString n, GameObject * father)
{
    nom = n;
    transform = Transform();
    rigidBody = RigidBody();
    father->addFils(this);
}

void GameObject::addFils(GameObject* f){
    fils.push_back(f);
    //qDebug() << "Je suis" << this->nom << "et j'ajoute" << f->nom << "en fils";
    f->addPere(this);
}

void GameObject::addPere(GameObject* p){
    pere = nullptr;
    pere = p;
    //qDebug() << "Je suis" << this->nom << "et j'ajoute" << p->nom << "comme père";;
}

GameObject* GameObject::getObject(QString n){
    for( unsigned int i = 0; i < fils.size(); i++ ){
        if(fils[i]->nom == n){
            return fils[i];
        }
    }
    return nullptr;
}

QVector3D GameObject::getWorldPosition(){
    QVector3D position = this->transform.getTranslation();
    GameObject* p = this->pere;
    while ( p != nullptr ){
        position = position + pere->transform.getTranslation();
        p = p->pere;
    }
    return position;
}

Transform GameObject::Transform(){
    return transform;
}

void GameObject::Translate(QVector3D v){
    transform.translate(v);
    QMatrix4x4 m =transform.computeModel();
    transformBoundingBox(bbox,m);
}

void GameObject::Rotate(QVector3D r){
    transform.rotate(r);
    QMatrix4x4 m = transform.computeModel();
    transformBoundingBox(bbox,m);
}

void GameObject::Scale(float s){
    transform.scale(s);
    QMatrix4x4 m = transform.computeModel();
    transformBoundingBox(bbox,m);
}

BoundingBox GameObject::transformBoundingBox(BoundingBox & bb, QMatrix4x4 & m){
    qDebug() << m;
    QVector4D right{m(0,0),m(1,0),m(2,0),m(3,0)};
    QVector4D up{m(0,1),m(1,1),m(2,1),m(3,1)};
    QVector4D back{m(0,2),m(1,2),m(2,2),m(3,2)};

    QVector3D translation{m(0,3),m(1,3),m(2,3)};
    QVector3D scale{m(0,0),m(1,1),m(2,2)};

    QVector4D xa = right * bb.min().x();
    QVector4D xb = right * bb.max().x();

    QVector4D ya = up * bb.min().y();
    QVector4D yb = up * bb.max().y();

    QVector4D za = back * bb.min().z();
    QVector4D zb = back * bb.max().z();

    qDebug() << xa << xb << ya << yb << za << zb;


    return BoundingBox();
}

void GameObject::printFils(){
    //qDebug() << "Noeud courant ->" <<  nom;
    if( fils.size() == 0 ){
        qDebug()  << "Je n'ai pas d'enfants";
    }else{
        qInfo()  << "J'ai " << fils.size() << " fils";
        for( unsigned long i = 0; i < fils.size(); i++ ){
            qDebug() << fils[i]->nom;
            fils[i]->printFils();
        }
    }
}

void GameObject::print(){
    qInfo() << "\nJe m'appelle " << nom;
    if(pere == nullptr){
        qInfo() << "Je n'ai pas de père";
    }
    else{
        qInfo() << "Fils de " << pere->nom;
    }

    transform.print();
    qInfo() << "Position Reelle: " << getWorldPosition();
    rigidBody.print();
    bbox.print();

    printFils();
}

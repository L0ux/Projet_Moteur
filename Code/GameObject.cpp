#include "GameObject.h"



GameObject::GameObject()
{
    nom = "World";
    transform = Transform();
    pere = nullptr;
}


GameObject * GameObject::_world = new GameObject();

GameObject::GameObject(QString n)
{
    nom = n;
    transform = Transform();
    GameObject::_world->addFils(this);
}

GameObject::GameObject(QString n, GameObject * father)
{
    nom = n;
    transform = Transform();
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

    printFils();
}

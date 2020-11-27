#include "gameobject.h"

GameObject::GameObject(QString n)
{
    nom = n;
    transform = Transform();
    pere = nullptr;
}

void GameObject::addFils(GameObject* f){
    fils.push_back(f);
    //qDebug() << "Je suis" << this->nom << "et j'ajoute" << f->nom << "en fils";
    f->addPere(this);
}

void GameObject::printFils(){
    qDebug() << "Noeud courant ->" <<  nom;
    if( fils.size() == 0 ){
        qDebug("Aucun fils");
    }else{
        qDebug() << "J'ai " << fils.size() << " fils";
        for( unsigned long i = 0; i < fils.size(); i++ ){
            fils[i]->printFils();
        }
    }
}

GameObject* GameObject::getObject(QString n){
    for( unsigned int i = 0; i < fils.size(); i++ ){
        if(fils[i]->nom == n){
            return fils[i];
        }
    }
    return nullptr;
}

void GameObject::addPere(GameObject* p){
    pere = p;
    //qDebug() << "Je suis" << this->nom << "et j'ajoute" << p->nom << "comme père";;
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

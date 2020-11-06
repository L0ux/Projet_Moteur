#include "gameobject.h"

GameObject::GameObject(QString n)
{
    nom = n;
    transform = Transform();
}

void GameObject::addFils(GameObject* f){
    fils.push_back(f);
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

void GameObject::setTransform(Transform t){
    transform = t;
}

GameObject* GameObject::getObject(QString n){
    for( unsigned int i = 0; i < fils.size(); i++ ){
        if(fils[i]->nom == n){
            return fils[i];
        }
    }
    return nullptr;
}

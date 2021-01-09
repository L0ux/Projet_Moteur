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
    transformBoundingBox(m);
}

void GameObject::Rotate(QVector3D r){
    transform.rotate(r);
    QMatrix4x4 m = transform.computeModel();
    transformBoundingBox(m);
}

void GameObject::Scale(float s){
    transform.scale(s);
    QMatrix4x4 m = transform.computeModel();
    transformBoundingBox(m);
}

// fonction generale, translate et scale devrait pouvoir se passer
// de la deuxieme partie, a voir pour optimisations
BoundingBox GameObject::transformBoundingBox(QMatrix4x4 & m){
    QVector3D v1 = bbox.min();
    QVector3D v8 = bbox.max();
    QVector3D vertices[8] = {v1,v8,
                           QVector3D(v1.x(),v8.y(),v1.z()),
                           QVector3D(v1.x(),v8.y(),v8.z()),
                           QVector3D(v1.x(),v1.y(),v8.z()),
                           QVector3D(v8.x(),v1.y(),v1.z()),
                           QVector3D(v8.x(),v8.y(),v1.z()),
                           QVector3D(v8.x(),v1.y(),v8.z())};

    // calcul de la nouvelle position des sommets de la bounding box
    for(auto i = 0; i < 8;++i){
        vertices[i] = vertices[i] * m;
    }

    float minX = vertices[0].x();
    float minY = vertices[0].y();
    float minZ = vertices[0].z();

    float maxX = vertices[0].x();
    float maxY = vertices[0].y();
    float maxZ = vertices[0].z();

    // recalcul des extremas car en cas de rotation ils changent
    for(auto i = 0; i < 8;++i){
        minX = std::min(minX,vertices[i].x());
        minY = std::min(minY,vertices[i].y());
        minZ = std::min(minZ,vertices[i].z());

        maxX = std::max(maxX,vertices[i].x());
        maxY = std::max(maxY,vertices[i].y());
        maxZ = std::max(maxZ,vertices[i].z());
    }

    return BoundingBox(QVector3D(minX,minY,minZ),QVector3D(maxX,maxY,maxZ));
}

bool GameObject::collides(GameObject *other, QVector3D direction){
    return false;
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

#include "GameObject.h"

GameObject::GameObject()
{
    nom = "World";
    transform = Transform();
    rigidBody = RigidBody();
    pere = nullptr;
}

GameObject * GameObject::_world = new GameObject();
std::vector<GameObject *> GameObject::aabbSortedObjects;

GameObject::GameObject(QString n)
{
    nom = n;
    transform = Transform();
    rigidBody = RigidBody();
    GameObject::_world->addFils(this);
    if(!n.toLower().contains("camera")){
        GameObject::aabbSortedObjects.push_back(this);
    }

}

GameObject::GameObject(QString n, GameObject * father)
{
    nom = n;
    transform = Transform();
    rigidBody = RigidBody();
    father->addFils(this);
    if(!n.toLower().contains("camera")){
        GameObject::aabbSortedObjects.push_back(this);
    }
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

ushort GameObject::findHighestVarianceAxis(){
    float minX = GameObject::aabbSortedObjects[0]->bbox.min().x();
    float minY = GameObject::aabbSortedObjects[0]->bbox.min().y();
    float minZ = GameObject::aabbSortedObjects[0]->bbox.min().z();

    float maxX = GameObject::aabbSortedObjects[0]->bbox.max().x();
    float maxY = GameObject::aabbSortedObjects[0]->bbox.max().y();
    float maxZ = GameObject::aabbSortedObjects[0]->bbox.max().z();

    for(auto i = 0; i < GameObject::aabbSortedObjects.size();++i){
        GameObject::aabbSortedObjects[i]->print();
        minX = std::min(minX,GameObject::aabbSortedObjects[i]->bbox.min().x());
        minY = std::min(minY,GameObject::aabbSortedObjects[i]->bbox.min().y());
        minZ = std::min(minZ,GameObject::aabbSortedObjects[i]->bbox.min().z());

        maxX = std::max(maxX,GameObject::aabbSortedObjects[i]->bbox.max().x());
        maxY = std::max(maxY,GameObject::aabbSortedObjects[i]->bbox.max().y());
        maxZ = std::max(maxZ,GameObject::aabbSortedObjects[i]->bbox.max().z());
    }

    //qDebug() << minX;
    //qDebug() << minY;
    //qDebug() << minZ;
    //qDebug() << maxX;
    //qDebug() << maxY;
    //qDebug() << maxZ;

    float varianceX = maxX - minX;
    float varianceY = maxY - minY;
    float varianceZ = maxZ - minZ;
    //qDebug() << varianceX;
    //qDebug() << varianceY;
    //qDebug() << varianceZ;

    if(varianceX > varianceY && varianceX > varianceZ){
        return 0;
    }
    if(varianceY > varianceX && varianceY > varianceZ){
        return 1;
    }
    if(varianceZ > varianceX && varianceZ > varianceY){
        return 2;
    }
    return 3;
}

void GameObject::sortAABBs(ushort axis){
    /*std::sort(GameObject::aabbSortedObjects.begin(),
              GameObject::aabbSortedObjects.end(),
              compareBBs);*/
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
        vertices[i] = m * vertices[i];
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

    bbox.min(QVector3D(minX,minY,minZ));
    bbox.max(QVector3D(maxX,maxY,maxZ));

    return bbox;
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

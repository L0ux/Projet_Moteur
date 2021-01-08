#include "mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh( std::vector<QVector3D>& v, std::vector<QVector3D>& t){
    vertices = v;
    triangles = t;
}

std::vector<QVector3D> Mesh::Vertices(){
    return vertices;
}

void Mesh::Vertices(std::vector<QVector3D> & v){
    vertices = v;
}

std::vector<QVector3D> Mesh::Triangles(){
    return triangles;
}

void Mesh::Triangles(std::vector<QVector3D> & t){
    triangles = t;
}

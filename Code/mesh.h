#ifndef MESH_H
#define MESH_H

#include "common.h"

class Mesh
{
    std::vector<QVector3D> vertices;
    std::vector<QVector3D> triangles;
public:
    Mesh();
    Mesh( std::vector<QVector3D>& vertices, std::vector<QVector3D>& triangles);

    std::vector<QVector3D> Vertices();
    void Vertices(std::vector<QVector3D>& v);

    std::vector<QVector3D> Triangles();
    void Triangles(std::vector<QVector3D>& v);
};

#endif // MESH_H

#include "boundingbox.h"

BoundingBox::BoundingBox()
{
    _min = {0,0,0};
    _max = {1,1,1};
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

void BoundingBox::render(QOpenGLShaderProgram *program){
    initializeOpenGLFunctions();

    GLfloat blue[] = {0.0,0.0,1.0};
    GLfloat purple[] = {0.8,0.3,0.9};
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
    //glBegin(GL_POLYGON);
      //  glNormal3d( 0.0, 0.1, 0.0);
        //glVertex3d(_min.x(), _min.y(), _min.z());//FRIGHT
        //glVertex3d(_max.x(), _max.y(), _max.z());//FLEFT
        //glVertex3d( -x1,  y1,  z1);//NLEFT
        //glVertex3d(  x1,  y1,  z1);//NRIGHT
    //glEnd();

/*    //Front face of cube

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
    glBegin(GL_POLYGON);
        glNormal3d( 0.0, 0.0, 0.3);
        glVertex3d( -x2,  y1,  z1);//top right corner
        glVertex3d( -x1,  y1,  z1);//top left corner
        glVertex3d( -x1, -y1,  z1);//bottom left corner
        glVertex3d( -x2, -y1,  z1);//bottom right corner
    glEnd();



    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glBegin(GL_POLYGON);
        glNormal3d( 0.0, 0.0,  0.2);
        glVertex3d( -x3,  y1,  z1);	//top right corner
        glVertex3d( -x2,  y1,  z1); //top left corner
        glVertex3d( -x2, -y1,  z1); //bottom left corner
        glVertex3d( -x3, -y1,  z1); //bottom right corner
    glEnd();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
    glBegin(GL_POLYGON);
        glNormal3d( 0.0, 0.0,  0.3);
        glVertex3d(  x3,  y1,  z1);//top right corner
        glVertex3d( -x3,  y1,  z1);//top left corner
        glVertex3d( -x3, -y1,  z1);//bottom left corner
        glVertex3d(  x3, -y1,  z1);//bottom right corner
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glBegin(GL_POLYGON);
        glNormal3d( 0.0, 0.0, 0.2);
        glVertex3d( x2,  y1,  z1); //top right corner
        glVertex3d( x3,  y1,  z1); //top left corner
        glVertex3d( x3, -y1,  z1); //bottom left corner
        glVertex3d( x2, -y1,  z1); //bottom right corner
    glEnd();


    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple);
    glBegin(GL_POLYGON);
        glNormal3d( 0.0, 0.0,  0.3);
        glVertex3d(  x1,  y1,  z1);//top right corner
        glVertex3d(  x2,  y1,  z1);//top left corner
        glVertex3d(  x2, -y1,  z1);//bottom left corner
        glVertex3d(  x1, -y1,  z1);//bottom right corner
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    //horizontal right face
    glBegin(GL_POLYGON);
         glNormal3d(  0.3, 0.0,  0.0);
         glVertex3d(  x1,  y1, -z1);//FTOP
         glVertex3d(  x1,  y1,  z1);//NTOP
         glVertex3d(  x1, -y1,  z1);//NBOTTOM
         glVertex3d(  x1, -y1, -z1);//FBOTTOM

    glEnd();

    //Back face of cube
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glBegin(GL_POLYGON);
        glNormal3d(  0.0, 0.0, -0.3);
        glVertex3d( -x1,  y1, -z1);//top left
        glVertex3d(  x1,  y1, -z1);//top right
        glVertex3d(  x1, -y1, -z1);//bottom right
        glVertex3d( -x1, -y1, -z1);//bottom left
    glEnd();

    //horizontal left face
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glBegin(GL_POLYGON);
         glNormal3d( -0.4, 0.0, 0.0);
         glVertex3d( -x1,  y1,  z1);//NTOP
         glVertex3d( -x1,  y1, -z1);//FTOP
         glVertex3d( -x1, -y1, -z1);//FBOTTOM
         glVertex3d( -x1, -y1,  z1);//NBOTTOM
    glEnd();
    //Bottom face of cube
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
    glBegin(GL_POLYGON);
        glNormal3d( 0.0, -0.1, 0.0);
        glVertex3d(  x1, -y1,  z1);//NRIGHT
        glVertex3d( -x1, -y1,  z1);//NLEFT
        glVertex3d( -x1, -y1, -z1);//FLEFT
        glVertex3d(  x1, -y1, -z1);//FRIGHT
    glEnd();*/
}

void BoundingBox::print(){
    qDebug() << "BoundingBox:";
    qDebug() << "\tMin: (" << _min.x() << "," << _min.y() << "," << _min.z() << ")";
    qDebug() << "\tMax: (" << _max.x() << "," << _max.y() << "," << _max.z() << ")";

}

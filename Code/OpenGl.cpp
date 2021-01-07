/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "OpenGl.h"



float angle_rotation = 0.f;

OpenGl::OpenGl(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0)
{
    world = GameObject::_world;
/*
    GameObject* soleil = new GameObject("Soleil");
    GameObject* terre = new GameObject("Terre",soleil);
    GameObject* lune = new GameObject("Lune",terre);


    lune->transform.scale(0.3);
    lune->transform.translate({0,2,2});
    lune->transform.rotate({6.68,3.f,0});

    terre->transform.scale(0.3);
    terre->transform.translate({10,0,0});
    terre->transform.rotate({23.44,-2.f,0});

    soleil->transform.scale(7);

    camera = new Camera("Camera");
    camera->transform.translate({0.0, 0.0, -70.0});
    camera->lookAt(camera->getWorldPosition(),soleil->getWorldPosition(),QVector3D(0.0f, 1.0f, 0.0f));*/

    //terre->addFils(camera);
    //world.addFils(camera);
    //world.addFils(soleil);
    //world.printFils();

    GameObject * cube_1 = new GameObject("Cube_1");
    GameObject * cube_2 = new GameObject("Cube_2");
    GameObject * cube_3 = new GameObject("Cube_3");
    GameObject * cube_4 = new GameObject("Cube_4",cube_1);

    cube_1->transform.translate({0,20,0});
    cube_2->transform.translate({0,10,0});
    cube_3->rigidBody.hasGravity(false);
    cube_4->transform.translate({5,0,0});

    camera = new Camera("Camera");
    camera->transform.translate({0,10,-70});
    camera->lookAt(camera->getWorldPosition(),cube_2->getWorldPosition(),QVector3D(0.0f, 1.0f, 0.0f));

}

OpenGl::~OpenGl()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    delete world;
    doneCurrent();
}

void OpenGl::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void OpenGl::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void OpenGl::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }

    angle_rotation += 0.002f;
    update();
}

void OpenGl::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    geometries = new MeshBuilder;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void OpenGl::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void OpenGl::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/Ressources/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void OpenGl::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 500.0, fov = 45.0;

    // Reset projection
    //projection.setToIdentity();
    camera->projection.setToIdentity();

    // Set perspective projection
    //projection.perspective(fov, aspect, zNear, zFar);
    camera->projection.perspective(fov, aspect, zNear, zFar);
}

void OpenGl::draw(QMatrix4x4 mvp,GameObject* object){
    QMatrix4x4 matrice = mvp * object->transform.computeModel();
    if( object != camera){                                          //Pour ne pas dessiner la camera
        program.setUniformValue("mvp_matrix", matrice);
        geometries->drawCubeGeometry(&program);
    }
    for( unsigned int i = 0; i < object->fils.size(); i++){
        draw(matrice,object->fils[i]);
    }
}

void OpenGl::paintGL()
{

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    texture->bind();

   /* GameObject* soleil = world->getObject("Soleil");
    GameObject* terre = soleil->getObject("Terre");
    GameObject* lune =  terre->getObject("Lune");

    lune->transform.rotate({6.68,3.f * angle_rotation,0});
    terre->transform.rotate({23.44,-2.f * angle_rotation,0});
    soleil->transform.rotate({0,angle_rotation,0});

    qDebug() << "soleil" << soleil->transform.computeModel();
    qDebug() << "camera" << camera->projection*camera->vue();
    qDebug() << "terre" << terre->getWorldPosition();*/


    // Actual Rendering
    for( unsigned long i = 0; i < world->fils.size(); i++){
        if(world->fils[i]->rigidBody.isMovable()){
            if(world->fils[i]->rigidBody.hasGravity()){
                QVector3D position = world->fils[i]->transform.getTranslation();
                float speed = world->fils[i]->rigidBody.speed();
                qDebug() << "ancienne position " << position;
                qDebug() << "ancienne vitesse " << speed;
                Physics::computeGravityEffect(position,speed);
                world->fils[i]->transform.translate(position);
                world->fils[i]->rigidBody.speed(speed);
                qDebug() << "nouvelle position " << position;
                qDebug() << "nouvelle vitesse " << speed;
            }
        }
        draw(camera->projection*camera->vue(),world->fils[i]);
    }

    timerEvent(new QTimerEvent(0));
}

void OpenGl::keyPressEvent(QKeyEvent *event)
{
    if(event->text() == QString::fromStdString("r")){
         qDebug("Appuie sur R");
    }

    update();
    event->accept();
};

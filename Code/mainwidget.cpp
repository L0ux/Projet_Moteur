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

#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

float angle_rotation = 0.f;

QVector3D r_soleil{0,0,0};
QVector3D r_terre{0,0,0};
QVector3D r_lune{0,0,0};


MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0),
    world("World")
{

    Transform t_lune;
    t_lune.scale(0.3);
    t_lune.translate({0,2,2});
    t_lune.rotate({6.68,3.f,0});
    GameObject lune("Lune");
    lune.setTransform(t_lune);

    Transform t_terre;
    t_terre.scale(0.3);
    t_terre.translate({10,0,0});
    t_terre.rotate({23.44,-2.f,0});
    GameObject terre("Terre");
    terre.setTransform(t_terre);
    terre.addFils(lune);

    Transform t_soleil;
    t_soleil.scale(5);
    t_soleil.rotate({0,0,0});
    GameObject soleil("Soleil");
    soleil.setTransform(t_soleil);
    soleil.addFils(terre);

    world.addFils(soleil);
    world.printFils();
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
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
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
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
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
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
//! [3]

//! [4]
void MainWidget::initTextures()
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
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 500.0, fov = 70.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::draw(QMatrix4x4 mvp){
    program.setUniformValue("mvp_matrix", mvp);
    geometries->drawCubeGeometry(&program);
}

void MainWidget::paintGL()
{


    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    texture->bind();

    QMatrix4x4 view;
    view.translate(0.0, 0.0, -70.0);
    //view.rotate(QQuaternion::fromAxisAndAngle({0,1,0}, -45.f)); // camera axis & camera angle

//! [6]
    /*std::stack<Transform> hierarchie;

    Transform soleil;
    Transform terre;
    Transform lune;

    soleil.scale(5);
    r_soleil = {0,angle_rotation,0};
    soleil.rotate(r_soleil);

    draw(projection * view * soleil.computeModel());
    hierarchie.push(soleil);

    terre.scale(0.3);
    terre.translate({10,0,0});

    r_terre = {23.44,-2.f * angle_rotation,0};
    terre.rotate(r_terre);



    hierarchie.push(terre);
    draw(projection * view * soleil.getModel() * terre.computeModel());


    lune.scale(0.3);
    lune.translate({0,2,2});


    r_lune = {6.68,3.f * angle_rotation,0};
    lune.rotate(r_lune);


    draw(projection * view * soleil.getModel() * terre.getModel() * lune.computeModel());*/

    for( unsigned long i = 0; i < world.fils.size(); i++){
        world.fils[i].transform.rotate({0,angle_rotation,0});
        draw(projection * view * world.fils[i].transform.computeModel());
        world.fils[i].fils[i].transform.rotate({23.44,-2.f * angle_rotation,0});
        draw(projection * view * world.fils[i].transform.computeModel() * world.fils[i].fils[i].transform.computeModel());
        world.fils[i].fils[i].fils[i].transform.rotate({6.68,3.f * angle_rotation,0});
        draw(projection * view * world.fils[i].transform.computeModel() * world.fils[i].fils[i].transform.computeModel()  * world.fils[i].fils[i].fils[i].transform.computeModel());
    }

    timerEvent(new QTimerEvent(0));

    //hierarchie.pop();
    //hierarchie.pop();


    /* **** How to
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * view * model);

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);

    // Draw cube geometry
    geometries->drawCubeGeometry(&program);
    */

}

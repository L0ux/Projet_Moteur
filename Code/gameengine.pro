QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    Camera.cpp \
    GameObject.cpp \
    Physics.cpp \
    RigidBody.cpp \
    Transform.cpp \
    boundingbox.cpp \
    vertex.cpp

SOURCES += \
    MeshBuilder.cpp \
    OpenGl.cpp

HEADERS += \
    Camera.h \
    GameObject.h \
    MeshBuilder.h \
    OpenGl.h \
    Physics.h \
    RigidBody.h \
    Transform.h \
    boundingbox.h \
    vertex.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

FORMS += \
    mainwindow.ui

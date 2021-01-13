QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    Boundingbox.cpp \
    Camera.cpp \
    Common.cpp \
    GameObject.cpp \
    Mesh.cpp \
    Physics.cpp \
    RigidBody.cpp \
    Transform.cpp

SOURCES += \
    MeshBuilder.cpp \
    OpenGl.cpp

HEADERS += \
    Boundingbox.h \
    Camera.h \
    Common.h \
    GameObject.h \
    Mesh.h \
    MeshBuilder.h \
    OpenGl.h \
    Physics.h \
    RigidBody.h \
    Transform.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

FORMS += \
    mainwindow.ui

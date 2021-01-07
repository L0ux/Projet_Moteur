QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    boundingbox.cpp \
    camera.cpp \
    gameobject.cpp \
    rigidbody.cpp \
    transform.cpp \
    vertex.cpp

SOURCES += \
    OpenGl.cpp \
    geometryengine.cpp

HEADERS += \
    OpenGl.h \
    boundingbox.h \
    camera.h \
    gameobject.h \
    geometryengine.h \
    rigidbody.h \
    transform.h \
    vertex.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

FORMS += \
    mainwindow.ui

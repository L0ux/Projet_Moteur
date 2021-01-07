QT       += core gui widgets

TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    GameObject.cpp \
    boundingbox.cpp \
    camera.cpp \
    rigidbody.cpp \
    transform.cpp \
    vertex.cpp

SOURCES += \
    OpenGl.cpp \
    geometryengine.cpp

HEADERS += \
    GameObject.h \
    OpenGl.h \
    boundingbox.h \
    camera.h \
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

include(VBE/VBE.pro)
INCLUDEPATH += .

SOURCES += main.cpp \
    commons.cpp \
    SceneMain/SceneMain.cpp \
    SceneMain/Prop.cpp \
    SceneMain/Camera.cpp

HEADERS += \
    commons.hpp \
    SceneMain/SceneMain.hpp \
    SceneMain/Prop.hpp \
    SceneMain/Camera.hpp

OTHER_FILES += \
	data/shaders/propShader.vert \
	data/shaders/propShader.frag


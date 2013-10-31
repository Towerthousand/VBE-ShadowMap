include(VBE/VBE.pro)
INCLUDEPATH += .

SOURCES += main.cpp \
    commons.cpp \
    SceneMain/SceneMain.cpp \
    SceneMain/Prop.cpp \
    SceneMain/Camera.cpp \
    SceneMain/ShadowMapContainer.cpp

HEADERS += \
    commons.hpp \
    SceneMain/SceneMain.hpp \
    SceneMain/Prop.hpp \
    SceneMain/Camera.hpp \
    SceneMain/ShadowMapContainer.hpp

OTHER_FILES += \
	data/shaders/propShader.vert \
	data/shaders/propShader.frag


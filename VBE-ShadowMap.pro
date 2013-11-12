include(VBE/VBE.pro)

INCLUDEPATH += .

SOURCES += main.cpp \
    commons.cpp \
    SceneMain/SceneMain.cpp \
    SceneMain/Camera.cpp \
    SceneMain/ShadowMapContainer.cpp \
    SceneMain/ShadowModel.cpp \
    SceneMain/PlayerCamera.cpp

HEADERS += \
    commons.hpp \
    SceneMain/SceneMain.hpp \
    SceneMain/Camera.hpp \
    SceneMain/ShadowMapContainer.hpp \
    SceneMain/ShadowModel.hpp \
    SceneMain/PlayerCamera.hpp

OTHER_FILES += \
	data/shaders/propShader.vert \
	data/shaders/propShader.frag \
    data/shaders/depthShader.frag \
    data/shaders/depthShader.vert


#include "SceneMain/SceneMain.hpp"

int main() {
	ZNEAR = 0.1f;
	ZFAR = 1000.0f;
	WINDOW_TITLE = "Shadow Map Test";
	Game game;
	SceneMain* sc = new SceneMain();
	sc->addTo(&game);
	game.run();
	return 42;
}

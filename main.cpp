#include "SceneMain/SceneMain.hpp"

int main() {
	WINDOW_TITLE = "Shadow Map Test";
	Game game;
	SceneMain* sc = new SceneMain();
	sc->addTo(&game);
	game.run();
	return 42;
}

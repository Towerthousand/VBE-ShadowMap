#include "SceneMain.hpp"
#include "Camera.hpp"
#include "Prop.hpp"

SceneMain::SceneMain() : debugCounter(0.0), fpsCount(0) {
	this->setName("SCENE");

	if (!loadResources())
	{VBE_ASSERT(false, "Could not load resources for SceneMain" );}

	//GL stuff..:
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE); //enable backface culling
	glCullFace(GL_BACK);

	//add player cam
	Camera* cam = new Camera(vec3f(0,10,15),vec3f(45,0,0));
	cam->addTo(this);

	//add ball
	Prop* prop = new Prop("ball","lava");
	prop->addTo(this);

	//add floor
	Prop* prop2 = new Prop("box","awesome");
	prop2->scale = vec3f(10,1,10);
	prop2->pos = vec3f(0,-3,0);
	prop2->rot = vec3f(0,0,180);
	prop2->addTo(this);
}

SceneMain::~SceneMain() {
	Textures.clear();
	Meshes.clear();
	Programs.clear();
	AudioManager::clear();
}

bool SceneMain::loadResources() {
	ShaderProgram* s = new ShaderProgram();
	s->makeProgramFromFile("data/shaders/propShader.vert","data/shaders/propShader.frag");
	Programs.add("propShader",s);

	Meshes.add("ball",new Mesh("data/meshes/ball.obj"));
	Meshes.add("box",new Mesh("data/meshes/cube.obj"));

	Texture* t = new Texture(1);
	t->loadFromFile("data/textures/lava.png");
	Textures.add("lava",t);

	t = new Texture(1);
	t->loadFromFile("data/textures/awesome.png");
	Textures.add("awesome",t);
	return true;
}

void SceneMain::update(float deltaTime) {
	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		VBE_LOG("FPS: " << fpsCount << ". Amount of GameObjects: " << getGame()->getObjectCount());
		debugCounter--;
		fpsCount = 0;
	}

	Camera* cam = (Camera*)getGame()->getObjectByName("cam");
	if(Input::isKeyDown(sf::Keyboard::S)) { //sun camera
		cam->projection = glm::ortho<float>(-15,15,-15,15,0.1,100);
		cam->pos = vec3f(-10,10,10);
		cam->rot = vec3f(45,45,0);
	}
	else { //player camera
		cam->projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
		cam->pos = vec3f(0,10,15);
		cam->rot = vec3f(45,0,0);
	}
}

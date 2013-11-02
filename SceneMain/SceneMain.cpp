#include "SceneMain.hpp"
#include "Camera.hpp"
#include "Prop.hpp"
#include "ShadowMapContainer.hpp"

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

	//container for shadowmapping
	ShadowMapContainer* shadow = new ShadowMapContainer();
	shadow->addTo(this);

	//add player cam
	Camera* pCam = new Camera("playerCam",vec3f(0,10,15),vec3f(45,0,0));
	pCam->projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	pCam->addTo(this);

	//add sun camera
	Camera* sCam = new Camera("sunCam",vec3f(-10,10,10),vec3f(45,45,0));
	sCam->projection = glm::ortho<float>(-20,20,-20,20,0.1,100);
	sCam->addTo(this);

	//add ball
	Prop* prop = new Prop("ball","lava");
	prop->addTo(shadow);
	prop->setName("ball");

	//add floor
	Prop* prop2 = new Prop("box","awesome");
	prop2->scale = vec3f(10,10,10);
	prop2->pos = vec3f(0,-13,0);
	prop2->rot = vec3f(0,0,180);
	prop2->addTo(shadow);
}

SceneMain::~SceneMain() {
	Textures.clear();
	Meshes.clear();
	Programs.clear();
	AudioManager::clear();
}

bool SceneMain::loadResources() {
	//programs
	ShaderProgram* s = new ShaderProgram();
	s->makeProgramFromFile("data/shaders/propShader.vert","data/shaders/propShader.frag");
	Programs.add("propShader",s);
	s = new ShaderProgram();
	s->makeProgramFromFile("data/shaders/depthShader.vert","data/shaders/depthShader.frag");
	Programs.add("depthShader",s);

	//meshes
	Meshes.add("ball",new Mesh("data/meshes/ball.obj"));
	Meshes.add("box",new Mesh("data/meshes/cube.obj"));

	//textures
	Texture* t = new Texture(0);
	t->loadFromFile("data/textures/lava.png");
	Textures.add("lava",t);
	t = new Texture(0);
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
	Prop* ball = (Prop*)getGame()->getObjectByName("ball");
	ball->pos = vec3f(sin(GLOBALCLOCK.getElapsedTime().asSeconds()*10),
					  0,
					  cos(GLOBALCLOCK.getElapsedTime().asSeconds()*10))*2.0f;
}

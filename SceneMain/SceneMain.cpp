#include "SceneMain.hpp"
#include "PlayerCamera.hpp"
#include "ShadowModel.hpp"
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
	PlayerCamera* pCam = new PlayerCamera("playerCam",vec3f(0,10,15),vec3f(45,0,0));
	pCam->projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	pCam->addTo(this);

	//add sun camera
	Camera* sCam = new Camera("sunCam",vec3f(-10,10,10),vec3f(45,45,0));
	sCam->projection = glm::ortho<float>(-20,20,-20,20,ZNEAR,ZFAR);
	sCam->addTo(this);

	//add ball
	ShadowModel* ball = new ShadowModel("ball","lava");
	ball->addTo(shadow);
	ball->setName("ball");

	//add ball2
	ShadowModel* ball2 = new ShadowModel("ball","awesome");
	ball2->scale = vec3f(3,3,3);
	ball2->addTo(shadow);

	//add ball3
	ShadowModel* ball3 = new ShadowModel("ball","awesome");
	ball3->pos = vec3f(2,-3,7);
	ball3->scale = vec3f(3,3,3);
	ball3->addTo(shadow);

	//add floor
	ShadowModel* floor = new ShadowModel("box","awesome");
	floor->scale = vec3f(10,10,10);
	floor->pos = vec3f(0,-13,0);
	floor->rot = vec3f(0,0,180);
	floor->addTo(shadow);

	//add random box
	ShadowModel* box = new ShadowModel("box","lava");
	box->scale = vec3f(2,2,2);
	box->pos = vec3f(-5,3,5);
	box->rot = vec3f(0,0,180);
	box->addTo(shadow);
	box->setName("randomBox");
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
	Meshes.add("ball",ResourceLoader::makeMeshFromOBJ("data/meshes/lol.obj"));
	Meshes.add("box",ResourceLoader::makeMeshFromOBJ("data/meshes/cube.obj"));

	//textures
	Texture* t = new Texture();
	t->loadFromFile("data/textures/lava.png");
	Textures.add("lava",t);
	t = new Texture();
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

	//move objects around
	ShadowModel* ball = (ShadowModel*)getGame()->getObjectByName("ball");
	ball->pos = vec3f(0,2,cos(GLOBALCLOCK.getElapsedTime().asSeconds()*3)*3)*2.0f;
	ShadowModel* box = (ShadowModel*)getGame()->getObjectByName("randomBox");
	box->rot = vec3f(0,180*sin(GLOBALCLOCK.getElapsedTime().asSeconds()),180);
}

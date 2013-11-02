#include "ShadowMapContainer.hpp"
#include "Prop.hpp"
#include "Camera.hpp"

ShadowMapContainer::ShadowMapContainer() : depthBuffer(NULL) {
	setName("smc");
	depthBuffer = new RenderTarget();
	depthBuffer->attachTexture(SCRWIDTH,SCRHEIGHT,RenderTarget::DEPTH,Texture::DEPTH_COMPONENT,2);
	depthBuffer->noDrawingTargets();
	VBE_ASSERT(depthBuffer->isUsable(),"Failed FBO creation");
	RenderTarget::bindScreen();
}

ShadowMapContainer::~ShadowMapContainer() {
}

void ShadowMapContainer::draw() const {
	std::vector<const Prop*> targets;
	this->getAllObjectsOfType<Prop>(targets);
	//DEPTH BUFFER
	depthBuffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(unsigned int i = 0; i < targets.size(); ++i) {
		targets[i]->drawMode = Prop::ShadowMap;
		targets[i]->draw();
	}
	//REAL DRAWING
	RenderTarget::bindScreen();
	for(unsigned int i = 0; i < targets.size(); ++i) {
		targets[i]->drawMode = Prop::Real;
		targets[i]->draw();
	}
}

Texture*ShadowMapContainer::getDepthTexture() {
	return depthBuffer->getAttachedTexture(RenderTarget::DEPTH);
}

#ifndef SHADOWMAPCONTAINER_HPP
#define SHADOWMAPCONTAINER_HPP
#include "commons.hpp"

class ShadowMapContainer : public ContainerObject {
	public:
		ShadowMapContainer();
		~ShadowMapContainer();

		void draw() const;
		Texture* getDepthTexture();

	private:
		RenderTarget* depthBuffer;
		Model screenQuad;
		friend class Prop;
};

#endif // SHADOWMAPCONTAINER_HPP

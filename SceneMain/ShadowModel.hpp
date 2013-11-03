#ifndef SHADOWMODEL_HPP
#define SHADOWMODEL_HPP
#include "commons.hpp"

class ShadowModel : public GameObject {
	public:
		enum Technique {
			ShadowMap = 0,
			Real
		};

		ShadowModel(std::string meshID, std::string texId);

		void update(float deltaTime);
		void draw() const;

		vec3f pos;
		vec3f rot;
		vec3f scale;
	private:
		Texture* tex;
		mutable Model model;
		mutable Technique drawMode;

	friend class ShadowMapContainer;
};

#endif // SHADOWMODEL_HPP

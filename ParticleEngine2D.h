#pragma once

#include<vector>

namespace Adina{

	class ParticleBatch2D;
	class SpriteBatch;

	class ParticleEngine2D
	{
		std::vector<ParticleBatch2D*> m_batches;
	public:
		ParticleEngine2D();
		
		~ParticleEngine2D();

		//After adding a particle batch, the ParticleEngine2D becomes
		//responsible for deallocation
		void addParticleBatch(ParticleBatch2D* particleBatch2D);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);
	};

}

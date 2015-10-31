#include "ParticleBatch2D.h"

namespace Adina{
	////==================================================================================
	////==================================================================================
	////==================================================================================
	ParticleBatch2D::ParticleBatch2D()
	{
	}
	////==================================================================================
	////==================================================================================
	////==================================================================================
	ParticleBatch2D::~ParticleBatch2D()
	{
		delete[] m_Particles;
	}
	////==================================================================================
	////==================================================================================
	////==================================================================================
	void ParticleBatch2D::update(float deltaTime){
		for (int i = 0; i < m_maxParticles; i++){
			if (m_Particles[i].life > 0.0f){
				m_updateFunc(m_Particles[i], deltaTime);
				m_Particles[i].life -= m_decayRate * deltaTime;
			}
		}
	}
	////==================================================================================
	////==================================================================================
	////==================================================================================
	void ParticleBatch2D::draw(SpriteBatch* spriteBatch){
		
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

		for (int i = 0; i < m_maxParticles; i++){
			if (m_Particles[i].life > 0.0f)
			{
				glm::vec4 destRect(
					m_Particles[i].position.x,
					m_Particles[i].position.y,
					m_Particles[i].width,
					m_Particles[i].width);
				spriteBatch->draw(
					destRect,
					uvRect, 
					m_texture.id,
					0,
					m_Particles[i].color);
			}
		}
	}
	////==================================================================================
	////==================================================================================
	////==================================================================================
	void ParticleBatch2D::init(
			int maxParticles,
			float decayRate,
			GLTexture texture,
			std::function<void(Particle2D&, float)> updateFunc /* = defaultParticleUpdate */
		){
		m_maxParticles = maxParticles;
		m_Particles = new Particle2D[m_maxParticles];
		m_decayRate = decayRate;
		m_texture = texture;
		m_updateFunc = updateFunc;
	}
	////==================================================================================
	////==================================================================================
	////==================================================================================
	void ParticleBatch2D::addParticle(
		const glm::vec2& position,
		const glm::vec2& velocity, 
		const ColorRGBA8& color,
		float width){

		int particleIndex = findFreeParticle();
		auto& p = m_Particles[particleIndex];
		p.life = 1.0f;
		p.position = position;
		p.velocity = velocity;
		p.color = color;
		p.width = width;
	}
	////==================================================================================
	////==================================================================================
	////==================================================================================
	int ParticleBatch2D::findFreeParticle(){
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++){
			if (m_Particles[i].life <= 0.0){
				m_lastFreeParticle = i;
				return i;
			}
		}
		for (int i = 0; i < m_lastFreeParticle; i++){
			if (m_Particles[i].life <= 0.0){
				m_lastFreeParticle = i;
				return i;
			}
		}
		//No particle are free, overwrite first particle
		return 0;
	}
	////==================================================================================
	////==================================================================================
	////==================================================================================
}/*Adina*/
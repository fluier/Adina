#include"Timing.h"

#include<SDL2\SDL.h>

namespace Adina{
	//==================================================================================
	FpsLimiter::FpsLimiter(){
		/// Empty
	}
	//==================================================================================
	void FpsLimiter::init(float maxFPS){
		setMaxtFPS(maxFPS);
	}
	//==================================================================================
	void FpsLimiter::setMaxtFPS(float maxFPS){
		m_maxFPS = maxFPS;
	}
	//==================================================================================
	void FpsLimiter::begin(){
		m_startTicks = SDL_GetTicks();
	}
	//==================================================================================
	/// return the current FPS
	float FpsLimiter::end(){
		calculateFPS();

		float frameTicks = SDL_GetTicks() - m_startTicks;
		if (1000.0f / m_maxFPS > frameTicks){
			SDL_Delay(1000.0f / m_maxFPS - frameTicks);
		}
		return m_fps;
	}
	//==================================================================================
	void FpsLimiter::calculateFPS(){
		static const int NUM_SAMPLES = 10;
		static float framesTimes[NUM_SAMPLES];
		static int currentFrame = 0;
		static float prevTicks = SDL_GetTicks();

		float currentTicks = SDL_GetTicks();
		m_frameTime = currentTicks - prevTicks;

		framesTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

		prevTicks = currentTicks;
		int count;
		currentFrame++;

		if (currentFrame < NUM_SAMPLES){
			count = currentFrame;
		}
		else{
			count = NUM_SAMPLES;
		}
		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++){
			frameTimeAverage += framesTimes[i];
		}
		frameTimeAverage /= count;
		if (frameTimeAverage > 0){
			m_fps = 1000.0f / frameTimeAverage;
		}
		else{
			m_fps = 1.1f;
		}
	}
	//==================================================================================
}/*Adina*/
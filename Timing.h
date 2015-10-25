#pragma once

namespace Adina{
	class FpsLimiter{
	private:
		unsigned int m_startTicks;

		float m_fps;
		float m_maxFPS;
		float m_frameTime;
	public:
		FpsLimiter();

		void init(float maxFPS);
		void setMaxtFPS(float maxFPS);
		void begin();

		/// return the current FPS
		float end();
	private:
		void calculateFPS();
	};
}
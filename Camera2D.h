#pragma once

#include<glm\glm.hpp>
#include <SDL2/SDL_events.h>

namespace Adina{
	class Camera2D
	{
	private:
		glm::vec2 m_position;
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
		float m_scaleFactor;
		bool m_needMatrixUpdate;
		int m_screenWidth, m_screenHeight;
	public:
		Camera2D();
		~Camera2D();
		void init(int i_screenWidth, int i_screenHeight);
		void update();

		void onSDLEvent(SDL_Event& evnt);

		glm::vec2 convertScreenToWorld(glm::vec2 i_screenCoords);

		bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

		/// setters
		void setPosition(const glm::vec2& i_newPosition);
		void setScaleFactor(const float i_newScaleFactor);

		/// getters
		glm::vec2 getPosition();
		float getScaleFactor();
		glm::mat4 getCameraMatrix();
	};
}/*Adina*/


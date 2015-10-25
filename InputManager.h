#pragma once

#include<unordered_map>

#include<glm\glm.hpp>

namespace Adina{
	class InputManager
	{
	private:
		std::unordered_map<unsigned int, bool> m_keyMap;
		glm::vec2 m_mouseCoords;
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		/// setters
		void setMouseCoords(float x, float y);

		bool isKeyPressed(unsigned int keyID);

		/// getters
		glm::vec2 getMouseCoords()const;
	};
}


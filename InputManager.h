#pragma once

#include<glm\glm.hpp>

#include<unordered_map>


namespace Adina{
	class InputManager
	{
	private:
		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		glm::vec2 m_mouseCoords;
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		/// return true if the key in held down
		bool isKeyDown(unsigned int keyID);

		/// return true is the key was just pressed
		bool isKeyPressed(unsigned int keyID);

		/// setters
		void setMouseCoords(float x, float y);

		/// getters
		glm::vec2 getMouseCoords()const;
	private:
		bool wasKeyPressed(unsigned int keyID);
	};
}


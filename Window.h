#pragma once

#include<string>

#include<SDL2\SDL.h>

namespace Adina{


	class Window
	{
	private:
		SDL_Window* m_sdlWindow;
		int m_screenWidth, m_screenHeight;
	public:

		enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();

		int getScreenWidth();
		int getScreenHeight();
	private:
		void enableBlend();

		void VSYNC(int value);
	};

}

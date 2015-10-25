#include<GL\glew.h>

#include "Window.h"

#include <iostream>

#define someDefaultValue  500

namespace Adina{
	Window::Window():
		m_screenWidth(someDefaultValue),
		m_screenHeight(someDefaultValue)
	{

	}


	Window::~Window()
	{
	}
	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

		Uint32 flags = SDL_WINDOW_OPENGL;
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		//Open an SDL window
		m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (m_sdlWindow == nullptr) {
			std::cerr << "SDL Window could not be created! " << std::endl;
		}

		//Set up our OpenGL context
		SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
		if (glContext == nullptr) {
			std::cerr << "SDL_GL context could not be created!" << std::endl;
		}

		//Set up glew (optional but recommended)
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			std::cerr << "Could not initialize glew!" << std::endl;
		}

		//Check the OpenGL version
		std::printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

		//Set the background color to blue
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


		VSYNC(0);

		enableBlend();

		return 0;
	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(m_sdlWindow);
	}

	int Window::getScreenWidth() {
		return m_screenWidth; 
	}

	int Window::getScreenHeight() {
		return m_screenHeight; 
	}
	void Window::enableBlend(){
		// Enable alpha blend, this will make the black box arownd character to desapear
		// every PNG have an alpha chanel,
		// if it is 0, no back ground color will be overwrite with PNG color
		// if it is 1, the back ground color will be overwrite with PNG color
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// the function that will calculate de alpha
	}
	void Window::VSYNC(int value){
		//Set VSYNC, vertical sincronisation
		// if the value = 0, no vertical sincronisation is enabled
		// if the value = 1, vertical sincronisation is enabled
		int swapInterval = SDL_GL_SetSwapInterval(value);

		//something for debug purpose
		//std::cout << "VSYNK: " << swapInterval << std::endl;
	}
}

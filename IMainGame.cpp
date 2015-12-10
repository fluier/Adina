#include <GL\glew.h>

#include "IMainGame.h"
#include "Timing.h"

#include "ScreenList.h"
#include "IGameScreen.h"

#include <iostream>
#include <algorithm>


namespace Adina {

    IMainGame::IMainGame() 
	{
        m_screenList = std::make_unique<ScreenList>(this);
    }

    IMainGame::~IMainGame() 
	{
        // Empty
    }

    void IMainGame::run() 
	{

        if (!init()) return;

		// Some helpful constants.
		const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
		const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
		const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
		const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
		const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime

        FpsLimiter limiter;
		limiter.setMaxtFPS(DESIRED_FPS);

		// Start our previousTicks variable
		float previousTicks = SDL_GetTicks();
        
		// Game loop
        m_isRunning = true;
        while (m_isRunning) 
		{
            limiter.begin();
			// Calculate the frameTime in milliseconds
			float newTicks = SDL_GetTicks();
			float frameTime = newTicks - previousTicks;
			previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame
			// Get the total delta time
			float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

            // Call the custom update and draw method
            inputManager.update();
			int i = 0; // This counter makes sure we don't spiral to death!
			// Loop while we still have steps to process.
			while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {

				// The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
				float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
				update(deltaTime);
				// Since we just took a step that is length deltaTime, subtract from totalDeltaTime
				totalDeltaTime -= deltaTime;
				// Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
				i++;
			}
			draw();
            m_fps = limiter.end();
            m_window.swapBuffer();
        }
    }

    void IMainGame::exitGame() 
	{
        m_currentScreen->onExit();
        if (m_screenList)
		{
            m_screenList->destroy();
            m_screenList.reset();
        }
        m_isRunning = false;
    }

    void IMainGame::onSDLEvent(SDL_Event& evnt) {
        switch (evnt.type) {
            case SDL_QUIT:
				exitGame();
                break;
            case SDL_MOUSEMOTION:
                inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
                break;
            case SDL_KEYDOWN:
				inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
				inputManager.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
				inputManager.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
				inputManager.releaseKey(evnt.button.button);
                break;
        }
    }

    bool IMainGame::init() {
		Adina::init();

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        if (!initSystems()) return false;

        onInit();
        addScreens();

        m_currentScreen = m_screenList->getCurrent();
        m_currentScreen->onEntry();
        m_currentScreen->setRunning();

        return true;
    }

    bool IMainGame::initSystems() {
        m_window.create("Default", 1350, 700, 0);
        return true;
    }


	void IMainGame::update(float deltaTim) {
        if (m_currentScreen) {
            switch (m_currentScreen->getState()) {
                case ScreenState::RUNNING:
					m_currentScreen->update(deltaTim);
                    break;
                case ScreenState::CHANGE_NEXT:
                    m_currentScreen->onExit();
                    m_currentScreen = m_screenList->moveNext();
                    if (m_currentScreen) {
                        m_currentScreen->setRunning();
                        m_currentScreen->onEntry();
                    }
                    break;
                case ScreenState::CHANGE_PREVIOUS:
                    m_currentScreen->onExit();
                    m_currentScreen = m_screenList->movePrevious();
                    if (m_currentScreen) {
                        m_currentScreen->setRunning();
                        m_currentScreen->onEntry();
                    }
                    break;
                case ScreenState::EXIT_APPLICATION:
                    exitGame();
                    break;
                default:
                    break;
            }
        } else {
            exitGame();
        }
    }

    void IMainGame::draw() {
        glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());
        if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING) {
            m_currentScreen->draw();
        }
    }
}
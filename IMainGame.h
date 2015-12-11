
#pragma once

#include "Adina.h"
#include "Window.h"
#include "InputManager.h"
#include <memory>

#include<string>


namespace Adina {

    class ScreenList;
    class IGameScreen;

    class IMainGame {
    public:
        IMainGame();
        virtual ~IMainGame();

        // Runs and initializes the game
        void run(std::string windowName = "Default");
        // Exits the game
        void exitGame();

        // Called on initialization
        virtual void onInit() = 0;
        // For adding all screens
        virtual void addScreens() = 0;
        // Called when exiting
        virtual void onExit() = 0;

		void onSDLEvent(SDL_Event& evnt);

        const float getFps() const {
            return m_fps;
        }

		InputManager inputManager;
    protected:
        // Custom update function
		virtual void update(float deltaTim);
        // Custom render function
        virtual void draw();
		
		bool init(std::string windowName);
		bool initSystems(std::string windowName);

        std::unique_ptr<ScreenList> m_screenList = nullptr;
        IGameScreen* m_currentScreen = nullptr;
        bool m_isRunning = false;
        float m_fps = 0.0f;
        Window m_window;
    };

}
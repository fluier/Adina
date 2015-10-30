#pragma once

#include<string>
#include<map>

#include<SDL2\SDL_mixer.h>

namespace Adina{
	//==================================================================================
	//==================================================================================
	class SoundEffect{
		Mix_Chunk* m_chunk = nullptr;
	public:
		friend class AudioEngine;
		/// Plays the effect file
		/// @ param loops: If loops = -1, loop forever, otherwise it loops + 1 time
		void play(int loops = 0);
	};
	//==================================================================================
	//==================================================================================
	class Music
	{
	private:
		Mix_Music* m_music = nullptr;
	public:
		friend class AudioEngine;
		/// Plays the music file
		/// @ param loops: If loops = -1, loop forever, otherwise it loops time
		void play(int loops = -1);
		static void pause();
		static void stop();
		static void resume();
	};
	//==================================================================================
	//==================================================================================
	class AudioEngine
	{
		bool m_isInitialized = false;
		/// You can play multiple efects at a time
		std::map<std::string, Mix_Chunk*> m_effectMap;
		/// You can play only one music at a time
		std::map<std::string, Mix_Music*> m_musicMap;
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void distroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);
	};

}

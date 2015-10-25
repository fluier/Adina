#pragma once

#include<GL/glew.h>

#include"GLTexture.h"

#include<string>

namespace Adina{
	class Sprite
	{
	private:
		float m_x;
		float m_y;
		float m_width;
		float m_height;
		GLuint m_vboID;
		GLTexture m_texture;
		
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height,std::string texturePath);

		void draw();
	};
}


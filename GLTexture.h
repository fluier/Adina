#pragma once

typedef unsigned int GLuint;

namespace Adina{
	struct  GLTexture
	{
		GLuint id;
		int width;
		int height;
		void bind();
		void unbind();
	};
}
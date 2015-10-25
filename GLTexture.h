#pragma once

#include<GL\glew.h>

namespace Adina{
	struct  GLTexture
	{
		GLuint id;
		int width;
		int height;
		void bind(){
			glBindTexture(GL_TEXTURE_2D, id);
		}
		void unbind(){
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	};
}
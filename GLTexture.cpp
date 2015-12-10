#include"GLTexture.h"

#include<GL\glew.h>

namespace Adina{
	void GLTexture::bind(){
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void GLTexture::unbind(){
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
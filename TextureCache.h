#pragma once

#include"GLTexture.h"


#include<map>


namespace Adina{
	class TextureCache
	{
	private:
		std::map<std::string, GLTexture> m_textureMap;
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);
	};

}

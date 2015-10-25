#pragma once

#include<map>

#include"GLTexture.h"

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

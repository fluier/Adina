#pragma once

#include"TextureCache.h"

#include<string>

namespace Adina{
	class ResourceManager
	{
		static TextureCache m_textureCache;
	public:
		static GLTexture getTexture(std::string texturePath);
	};

}


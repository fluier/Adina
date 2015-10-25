#include "ResourceManager.h"


namespace Adina{

	TextureCache ResourceManager::m_textureCache;

	GLTexture ResourceManager::getTexture(std::string texturePath){
		// a wrap function
		return m_textureCache.getTexture(texturePath);
	}
}

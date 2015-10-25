#include "TextureCache.h"

#include "ImageLoader.h"

namespace Adina{
	TextureCache::TextureCache(){
	}


	TextureCache::~TextureCache(){
	}
	GLTexture TextureCache::getTexture(std::string texturePath){
		//std::map<std::string,GLTexture>::iterator mit =  m_textureMap.find(texturePath);
		auto mit = m_textureMap.find(texturePath);// lookup the texture and see if is in the map

		// check if is in the map
		if (mit == m_textureMap.end()){
			// load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//std::pair<std::string, GLTexture> newPair(texturePath, newTexture);
			//m_textureMap.insert(newPair);
			m_textureMap.insert(std::make_pair(texturePath, newTexture));

			return newTexture;
		}

		return mit->second;// second is the pointer to the texture,
						   //first it the pointer to the key
	}
}
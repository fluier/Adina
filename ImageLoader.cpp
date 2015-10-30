#include<GL/glew.h>
#include "ImageLoader.h"

#include"my_Errors.h"

#include "PicoPNG.h"
#include "IOManager.h"

#include<iostream>
#include<vector>

/*
//Loading a PNG into a TEXTURE
*/
namespace Adina{
	//==================================================================================
	GLTexture ImageLoader::loadPNG(std::string filePath){
		/// create a texture on the stack, and will return a copy of it at the end
		GLTexture texture = {}; // initialize all the field of structure with 0

		std::vector<unsigned char> in_inputData;
		std::vector<unsigned char> out_outputData;
		unsigned long width, height;

		// read the file path and put all the bites in in_inputData variable
		if (IOManager::readFileToBuffer(filePath, in_inputData) == false){
			fatalError("Failed to load PNG file to buffer!" );
		}

		// take all the bites from in variable, decode it and put the texture in out_outputData variable
		int errorCode = decodePNG(out_outputData, width, height, &(in_inputData[0]), in_inputData.size());
		if (errorCode != 0){
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		// generate the textures

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		//upload the texture to openGL texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out_outputData[0]));
		//Set some texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//Generate the mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		//Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		//Return a copy of the texture data
		return texture;
	}
	//==================================================================================
}
#include "IOManager.h"

#include <fstream>
namespace Adina{
	//==================================================================================
	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
		// reading in binary format, takeing the exact content of the file
		std::ifstream file(filePath, std::ios::binary);

		// error check
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);

		//Get the file size
		int fileSize = file.tellg();
		//seek back to the begining
		file.seekg(0, std::ios::beg);

		//Reduce the file size by any header bytes that might be present(date when was modify, etc.)
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}
	//==================================================================================
	bool IOManager::readFileToBuffer(std::string filePath, std::string& buffer) {
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);

		//Get the file size
		unsigned int fileSize = (unsigned int)file.tellg();
		file.seekg(0, std::ios::beg);

		//Reduce the file size by any header bytes that might be present
		fileSize -= (unsigned int)file.tellg();

		buffer.resize(fileSize);
		file.read((char *)&(buffer[0]), fileSize);
		file.close();

		return true;
	}

	//==================================================================================
}/*Adina*/
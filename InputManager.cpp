#include "InputManager.h"

namespace Adina{
	//==================================================================================
	InputManager::InputManager():
		m_mouseCoords(0.0f)
	{
	}
	//==================================================================================
	InputManager::~InputManager()
	{
	}
	//==================================================================================
	void InputManager::update(){
		///for (auto it = m_keyMap.begin(); it != m_keyMap.end(); it++){
		///	m_previousKeyMap[it->first] = it->second;
		///}

		// this code work in c++11
		/// Loop through m_keyMap using for each loop, and copy it over to m_previowsKeyMap
		for (auto& it: m_keyMap){
			m_previousKeyMap[it.first] = it.second;
		}
	}
	//==================================================================================
	void InputManager::pressKey(unsigned int keyID){
		m_keyMap[keyID] = true;
	}
	//==================================================================================
	void InputManager::releaseKey(unsigned int keyID){
		m_keyMap[keyID] = false;
	}
	//==================================================================================
	bool InputManager::isKeyDown(unsigned int keyID){
		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end()){
			return it->second;
		}
		else{
			return false;
		}
	}
	//==================================================================================
	bool InputManager::isKeyPressed(unsigned int keyID){
		if ((isKeyDown(keyID) == true) && (wasKeyPressed(keyID) == false)){
			return true;
		}
		return false;
	}
	//==================================================================================
	void InputManager::setMouseCoords(float x, float y){
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;
	}
	//==================================================================================
	glm::vec2 InputManager::getMouseCoords()const{
		return m_mouseCoords;
	}
	//==================================================================================
	bool InputManager::wasKeyPressed(unsigned int keyID){
		auto it = m_previousKeyMap.find(keyID);
		if (it != m_previousKeyMap.end()){
			return it->second;
		}
		else{
			return false;
		}
	}
}/*Adina*/

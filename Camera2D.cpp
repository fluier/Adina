#include "Camera2D.h"

#include"InputManager.h"

#include<glm\gtc\matrix_transform.hpp>

/// #include<iostream>

#define someDefaultValue  500

namespace Adina{
	//==================================================================================
	//==================================================================================
	//==================================================================================
	Camera2D::Camera2D():
		m_position(0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_scaleFactor(1.0f),
		m_needMatrixUpdate(true),
		m_screenWidth(someDefaultValue),
		m_screenHeight(someDefaultValue)
	{
		/// Empty
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	Camera2D::~Camera2D()
	{
		/// Empty
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	void Camera2D::init(int i_screenWidth, int i_screenHeight){
		m_screenWidth = i_screenWidth;
		m_screenHeight = i_screenHeight;
		/// the ortoMatrix need to be calculated only once, not taken into calcul the resize windows
		m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	void Camera2D::update(){
		if (m_needMatrixUpdate){
			//calculate the translation
			glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

			//calculate the scale
			glm::vec3 scale(m_scaleFactor, m_scaleFactor, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
			m_needMatrixUpdate = false;
		}
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	void Camera2D::onSDLEvent(SDL_Event& evnt)
	{
		float SCALE_CHANGING_SPEED = 0.1f;
		float SCALE_MINIM_VALUE = 0.2f; // bug if less than
		switch (evnt.type) {
			case SDL_MOUSEWHEEL :
				if (evnt.wheel.y > 0){
					m_scaleFactor += SCALE_CHANGING_SPEED;
				}
				else{
					if (m_scaleFactor > SCALE_MINIM_VALUE){
						m_scaleFactor -= SCALE_CHANGING_SPEED;
					}
				}
				m_needMatrixUpdate = true;
				///std::cout << "m_scaleFactor: " << m_scaleFactor << std::endl;
			break;
		}
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 i_screenCoords){
		/// invert the Y coordonates
		i_screenCoords.y = m_screenHeight - i_screenCoords.y;
		/// Make it so that 0 is the center
		i_screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		/// Scale the coordinates
		i_screenCoords /= m_scaleFactor;
		/// Translate with camera position
		i_screenCoords += m_position;
		/// return the resul
		return i_screenCoords;
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	/// simple AABB 
	bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions){

		/// for debug purpos
		/// glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / (m_scaleFactor * 2.0f);
		glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight) / m_scaleFactor;

		// The minimum distance before a collision occurs
		const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
		const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

		// Center position of the parameters
		glm::vec2 centerPos = position + dimensions/2.0f;
		// Center position of the camera
		glm::vec2 centerCameraPos = m_position;
		// Vector from the inut to the camera
		glm::vec2 distVec = centerPos - centerCameraPos;

		// Get the depth of the collision
		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		// If either the depths are > 0, then we collided
		if (xDepth > 0 && yDepth > 0) {
			/// there was a collision
			return true;
		}
		return false;
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	void Camera2D::setPosition(const glm::vec2& i_newPosition){
		m_position = i_newPosition;
		m_needMatrixUpdate = true;
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	void Camera2D::setScaleFactor(const float i_newScaleFactor){
		m_scaleFactor = i_newScaleFactor;
		m_needMatrixUpdate = true;
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	glm::vec2 Camera2D::getPosition(){
		return m_position;
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	float Camera2D::getScaleFactor(){
		return m_scaleFactor;
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
	glm::mat4 Camera2D::getCameraMatrix(){
		return m_cameraMatrix;
	}
	//==================================================================================
	//==================================================================================
	//==================================================================================
}/*Adina*/
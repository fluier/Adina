#include "Camera2D.h"
#define someDefaultValue  500

namespace Adina{
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


	Camera2D::~Camera2D()
	{
		/// Empty
	}
	void Camera2D::init(int i_screenWidth, int i_screenHeight){
		m_screenWidth = i_screenWidth;
		m_screenHeight = i_screenHeight;
		/// the ortoMatrix need to be calculated only once, not taken into calcul the resize windows
		m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
	}
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
	void Camera2D::setPosition(const glm::vec2& i_newPosition){
		m_position = i_newPosition;
		m_needMatrixUpdate = true;
	}
	void Camera2D::setScaleFactor(const float i_newScaleFactor){
		m_scaleFactor = i_newScaleFactor;
		m_needMatrixUpdate = true;
	}
	glm::vec2 Camera2D::getPosition(){
		return m_position;
	}
	float Camera2D::getScaleFactor(){
		return m_scaleFactor;
	}
	glm::mat4 Camera2D::getCameraMatrix(){
		return m_cameraMatrix;
	}
}/*Adina*/
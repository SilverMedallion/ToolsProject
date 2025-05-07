#include "Camera.h"
#include <iostream>
#include <algorithm>

//these must be initialized in the member initializer list as used before the the assignemnt in constructor body will occur.
Camera::Camera() : m_movementInput(Vector3(0.f))
{

	m_cameraMoveSpeed = .3f;
	m_cameraRotateRate = .1f;

	m_cameraPos = Vector3(4.0f, 3.7f, -12.5f);

	m_cameraLookAt.x = 0.0f;
	m_cameraLookAt.y = 0.0f;
	m_cameraLookAt.z = 0.0f;

	m_cameraLookDirection.x = 0.0f;
	m_cameraLookDirection.y = 0.0f;
	m_cameraLookDirection.z = 0.0f;

	m_cameraRight.x = 0.0f;
	m_cameraRight.y = 0.0f;
	m_cameraRight.z = 0.0f;

	m_cameraOrientation.x = 0.0f;
	m_cameraOrientation.y = 0.0f;
	m_cameraOrientation.z = 0.0f;

	
}

Camera::~Camera()
{
}



void Camera::Update(InputCommands input)
{

	//Vector3 planarMotionVector = m_cameraLookDirection;
	//planarMotionVector.y = 0.0;


	if (input.mouse_right)
	{
		//only calculate rotation if right mouse was down in previous frame, prevents big jump on initial right click

			float rotX = input.mouse_x - m_lastX;
			float rotY = input.mouse_y - m_lastY;

			m_cameraOrientation.y -= rotX * m_cameraRotateRate;
			m_cameraOrientation.x -= rotY * m_cameraRotateRate;

			//clamp vertical rotation to prevent flipping
			if (m_cameraOrientation.x > 90)
			{
				m_cameraOrientation.x = 90;
			}
			if (m_cameraOrientation.x < -90)
			{
				m_cameraOrientation.x = -90;
			}
		

			

	}
	

	// Add keyboard rotation controls
	if (input.rotLeft)
	{
		m_cameraOrientation.y += 2.0f;
	}
	if (input.rotRight)
	{
		m_cameraOrientation.y -= 2.0f;
	}
	if (input.lookUp)
	{
		m_cameraOrientation.x += 2.0f;
		if (m_cameraOrientation.x > 89.0f)
			m_cameraOrientation.x = 89.0f;
	}
	if (input.lookDown)
	{
		m_cameraOrientation.x -= 2.0f;
		if (m_cameraOrientation.x < -89.0f)
			m_cameraOrientation.x = -89.0f;
	}

	//calculate the look direction based on orientation agles
	float angleY = m_cameraOrientation.y * 3.1415 / 180.0f;
	float angleX = m_cameraOrientation.x * 3.1415 / 180.0f;
	m_cameraLookDirection.x = sin(angleY) * cos(angleX);
	m_cameraLookDirection.y = sin(angleX);
	m_cameraLookDirection.z = cos(angleY) * cos(angleX);
	m_cameraLookDirection.Normalize();


	//create right vector from look Direction
	m_cameraLookDirection.Cross(Vector3::UnitY, m_cameraRight);


	//process input
	Vector3 moveDirection = Vector3::Zero;
	if (input.forward)   moveDirection += m_cameraLookDirection;
	if (input.back)      moveDirection -= m_cameraLookDirection;
	if (input.right)     moveDirection += m_cameraRight;
	if (input.left)      moveDirection -= m_cameraRight;
	if (input.up)        moveDirection.y += 1.0f;
	if (input.down)      moveDirection.y -= 1.0f;

	m_cameraPos += moveDirection * m_cameraMoveSpeed;

	//update lookat point
	m_cameraLookAt = m_cameraPos + m_cameraLookDirection;

	m_lastX = input.mouse_x;
	m_lastY = input.mouse_y;
	
	
}

#pragma once

#include "pch.h"
#include "InputCommands.h"


typedef DirectX::SimpleMath::Vector3 Vector3;
typedef DirectX::SimpleMath::Matrix Matrix;

class Camera
{
public:

	Camera();
	~Camera();
	void Update(InputCommands input);
	const Vector3& Camera::GetCameraPosition()  //just used for setting display(not needed since public
	{
		return m_cameraPos;
	}
	const Vector3& Camera::GetCameraLookAt()   //not used
	{
		return m_cameraLookAt;
	}



	Vector3 m_movementInput;
	float m_pitchInput;
	float m_yawInput;
	float m_cameraMouseSensitivity;

	Vector3 m_mouseInput;
	float m_cameraMoveSpeed;
	float m_cameraRotateRate;

	Vector3 m_cameraPos;
	Vector3 m_cameraOrientation;
	Vector3 m_cameraLookAt;
	Vector3 m_cameraLookDirection;
	Vector3 m_cameraRight;


	float m_lastX;
	float m_lastY;
	
};
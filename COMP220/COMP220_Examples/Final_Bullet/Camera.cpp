#include "Camera.h"

Camera::Camera()
{
	// Camera Properties
	m_CameraPosition = glm::vec3(0.0f, 8.0f, -30.0f);
	m_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_CameraDirection = glm::vec3(0.0f);
	m_FPScameraPos = glm::vec3(0.0f);
	m_CameraX = 0.0f;
	m_CameraY = 0.0f;
	m_CameraDistance = (float)(m_CameraTarget - m_CameraPosition).length();

	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraTarget, m_CameraUp);
	m_ProjectionMatrix = glm::perspective(glm::radians(90.0f), float(800 / 600), 0.1f, 100.0f);

	m_ShaderProgramID = 0;
}

Camera::~Camera()
{
}

void Camera::FPSUpdate()
{
	m_CameraPosition += m_FPScameraPos;
	m_CameraTarget += m_FPScameraPos;
}

void Camera::Update()
{
	m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraTarget, m_CameraUp);
}

void Camera::Render(GLint ShaderID) //GLint view, GLint project, GLint pos
{
	glUseProgram(ShaderID);

	GLint viewMatrixLocation = glGetUniformLocation(ShaderID, "viewMatrix");
	GLint projectionMatrixLocation = glGetUniformLocation(ShaderID, "projectionMatrix");
	GLint cameraPositionLocation = glGetUniformLocation(ShaderID, "cameraPosition");

	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(m_ViewMatrix));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(m_ProjectionMatrix));
	glUniform3fv(cameraPositionLocation, 1, value_ptr(m_CameraPosition));
}

void Camera::Mouse(float X,float Y)
{
	// Get Mouse Motion of X and Y
	m_CameraX += X / 200.0f;
	m_CameraY += Y / 200.0f;
	// Limit camera range
	if (m_CameraY > 150.0f) m_CameraY = 150.0f; else if (m_CameraY < -150.0f) m_CameraY = -150.0f;
	// Calculate camera target using CameraX and CameraY
	m_CameraTarget = m_CameraPosition + m_CameraDistance * glm::vec3(cos(m_CameraX), tan(m_CameraY), sin(m_CameraX));
	// Normalised camera direction
	m_CameraDirection = normalize(m_CameraTarget - m_CameraPosition);
}

void Camera::Forward()
{
	m_FPScameraPos = m_CameraDirection * 0.2f;
}

void Camera::Backward()
{
	m_FPScameraPos = -m_CameraDirection * 0.2f;
}

void Camera::Right()
{
	m_FPScameraPos = cross(m_CameraDirection, m_CameraUp) * 0.5f;
}

void Camera::Left()
{
	m_FPScameraPos = -cross(m_CameraDirection, m_CameraUp) * 0.5f;
}



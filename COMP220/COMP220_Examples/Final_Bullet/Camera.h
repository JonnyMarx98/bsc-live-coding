#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"

class Camera
{
public:
	Camera();
	~Camera();

	// Get/Set Position
	void setPosition(const glm::vec3& position)
	{
		m_CameraPosition = position;
	};
	glm::vec3& getPosition()
	{
		return m_CameraPosition;
	};
	// Get/Set Target
	void setTarget(const glm::vec3& target)
	{
		m_CameraTarget = target;
	};
	glm::vec3& getTarget()
	{
		return m_CameraTarget;
	};
	// Get/Set Up
	void setUp(const glm::vec3& up)
	{
		m_CameraUp = up;
	};
	glm::vec3& getUp()
	{
		return m_CameraUp;
	};
	// Get/Set Direction
	void setDirection(const glm::vec3& direction)
	{
		m_CameraDirection = direction;
	};
	glm::vec3& getDirection()
	{
		return m_CameraDirection;
	};
	// Get/Set FPScameraPos
	void setFPScameraPos(const glm::vec3& fps)
	{
		m_FPScameraPos = fps;
	};
	glm::vec3& getFPScameraPos()
	{
		return m_FPScameraPos;
	};
	// Get/Set X
	void setX(float cameraX)
	{
		m_CameraX = cameraX;
	};
	float getX()
	{
		return m_CameraX;
	};
	// Get/Set Y
	void setY(float cameraY)
	{
		m_CameraY = cameraY;
	};
	float getY()
	{
		return m_CameraY;
	};
	// Get/Set Distance
	void setDistance(float Distance)
	{
		m_CameraDistance = Distance;
	};
	float getDistance()
	{
		return m_CameraDistance;
	};
	// Get/Set viewMatrix
	void setViewMatrix(const glm::mat4& view)
	{
		m_ViewMatrix = view;
	};
	glm::mat4& getViewMatrix()
	{
		return m_ViewMatrix;
	};
	// Get/Set projectionMatrix
	void setProjectionMatrix(const glm::mat4& projection)
	{
		m_ProjectionMatrix = projection;
	};
	glm::mat4& getProjectionMatrix()
	{
		return m_ProjectionMatrix;
	};

	glm::vec3 Cross(const glm::vec3& a, const glm::vec3& b)
	{
		return cross(a, b);
	}
	// Get shader ID
	GLuint getShaderProgramID()
	{
		return m_ShaderProgramID;
	};

	void CameraTransformUpdate();
	void Update();
	void Render(GLint ShaderID);
	void Mouse(float X, float Y);
	void Forward();
	void Backward();
	void Right();
	void Left();

private:
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraTarget;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraDirection;
	glm::vec3 m_FPScameraPos;
	float m_CameraX;
	float m_CameraY;
	float m_CameraDistance;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	GLuint m_ShaderProgramID;
};
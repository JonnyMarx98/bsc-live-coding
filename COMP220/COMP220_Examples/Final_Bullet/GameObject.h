#pragma once

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"


class GameObject
{
public:
		GameObject();
		~GameObject();
		// Get/Set Position
		void setPosition(const glm::vec3& position)
		{
			m_Position = position;
		};
		glm::vec3& getPosition()
		{
			return  m_Position;
		};
		// Get/Set Scale
		void setScale(glm::vec3& scale)
		{
			m_Scale = scale;
		};
		glm::vec3& getScale()
		{
			return  m_Scale;
		};
		// Get/Set Rotation
		void setRotation(glm::vec3& rotation)
		{
			m_Rotation = rotation;
		};
		glm::vec3& getRotation()
		{
			return  m_Rotation;
		};

		// get/set ambient, diffuse and specular

		// Get model matrix
		glm::mat4 getModelMatrix()
		{
			return m_ModelMatrix;
		};
		// Get/Set specular power
		void setSpecularPower(float power)
		{
			m_SpecularPower = power;
		};
		float getSpecularPower()
		{
			return m_SpecularPower;
		};
		// Get shader ID
		GLuint getShaderProgramID()
		{
			return m_ShaderProgramID;
		};
		 
		void loadMeshes(const std::string& filename);
		void loadDiffuseMap(const std::string& filename);
		void loadShaderProgram(const std::string& vertShaderFilename, const std::string& fragShaderFilename);

		void destroy();

		void Update();
		void preRender();
		void Render();

private:
	std::vector<Mesh*> m_Meshes;

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;
	glm::mat4 m_ModelMatrix;

	GLuint m_DiffuseMapID;
	glm::vec4 m_DiffuseMaterialColour;
	glm::vec4 m_SpecularMaterialColour;
	glm::vec4 m_AmbientMaterialColour;
	float m_SpecularPower;
	GLuint m_ShaderProgramID;
};
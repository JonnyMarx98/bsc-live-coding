#include "GameObject.h"

GameObject::GameObject()
{
	m_Meshes.clear();
	m_DiffuseMapID = 0;

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ModelMatrix = glm::mat4(1.0f);

	m_AmbientMaterialColour = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	m_DiffuseMaterialColour = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	m_SpecularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularPower = 25.0f;

	m_ShaderProgramID = 0;
	

}

GameObject::~GameObject()
{

}

void GameObject::loadMeshes(const std::string & filename)
{
	loadMeshesFromFile(filename, m_Meshes);
}

void GameObject::loadDiffuseMap(const std::string & filename)
{
	m_DiffuseMapID = loadTextureFromFile(filename);
}

void GameObject::loadShaderProgram(const std::string & vertShaderFilename, const std::string & fragShaderFilename)
{
	m_ShaderProgramID = LoadShaders(vertShaderFilename.c_str(), fragShaderFilename.c_str());
}

void GameObject::destroy()
{
	glDeleteTextures(1, &m_DiffuseMapID);
	glDeleteProgram(m_ShaderProgramID);
	

	auto iter = m_Meshes.begin();
	while (iter != m_Meshes.end())
	{
		if ((*iter))
		{
			(*iter)->destroy();
			delete (*iter);
			iter = m_Meshes.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void GameObject::Update()
{
	glm::mat4 translationMatrix = glm::translate(m_Position);
	glm::mat4 scaleMatrix = glm::scale(m_Scale);
	glm::mat4 rotationMatrix = glm::rotate(m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))*
							   glm::rotate(m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))*
							   glm::rotate(m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	m_ModelMatrix = translationMatrix*rotationMatrix*scaleMatrix;
}

void GameObject::preRender()
{
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseMapID);
	
	glUseProgram(m_ShaderProgramID);

	
	GLint modelMatrixLocation = glGetUniformLocation(m_ShaderProgramID, "modelMatrix");
	GLint textureLocation = glGetUniformLocation(m_ShaderProgramID, "baseTexture");
	GLint ambientMaterialColourLocation = glGetUniformLocation(m_ShaderProgramID, "ambientMaterialColour");
	GLint diffuseMaterialColourLocation = glGetUniformLocation(m_ShaderProgramID, "diffuseMaterialColour");
	GLint specularMaterialColourLocation = glGetUniformLocation(m_ShaderProgramID, "specularMaterialColour");
	GLint specularPowerLocation = glGetUniformLocation(m_ShaderProgramID, "specularPower");
	
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(m_ModelMatrix));	
	glUniform1i(textureLocation, 0);
	glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(m_DiffuseMaterialColour));
	glUniform4fv(specularMaterialColourLocation, 1, value_ptr(m_SpecularMaterialColour));
	glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(m_AmbientMaterialColour));
	glUniform1f(specularPowerLocation, m_SpecularPower);
	// We're gonna fix that in a couple of seconds
	
}

void GameObject::Render()
{
	for (Mesh* currentMesh : m_Meshes)
	{
		currentMesh->render();
	}
}

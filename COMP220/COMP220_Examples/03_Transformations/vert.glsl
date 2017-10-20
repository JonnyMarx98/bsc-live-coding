#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 modelMatrix = mat4(1.0f);

void main()
{
	// gl_position.xyz = vertexPosition;
	// gl_Position.w = 1.0;

	vec4 modelVertexPosition=modelMatrix*vec4(vertexPosition,2.0f);

	gl_Position = modelVertexPosition;
}
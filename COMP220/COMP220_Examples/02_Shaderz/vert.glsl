#version 330 core

layout(location = 0) in vec3 vertexPosition;

void main()
{
	// gl_position.xyz = vertexPosition;
	// gl_Position.w = 1.0;

	gl_Position = vec4(vertexPosition,1.0);
}
#version 330 core

in vec2 textureCoordsOut;

out vec4 colour;

uniform sampler2D texture0;

float greyScale(vec3 colour)
{
	return (colour.r + colour.g + colour.b)/3.0f;
}

void main()
{
	vec4 textureColour = texture(texture0,textureCoordsOut);
	float grey = greyScale(textureColour.rgb);
	colour = vec4(grey, grey, grey, 1.0f);
}
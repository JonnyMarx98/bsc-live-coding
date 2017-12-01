#version 330 core

in vec2 textureCoordsOut;

out vec4 colour;

uniform sampler2D texture0;

float decreaseRed(vec3 colour, float amount)
{
	return (colour.r / amount);
}

void main()
{
	vec4 textureColour = texture(texture0,textureCoordsOut);
	float lessRed = decreaseRed(textureColour.rgb, 3.0f);
	colour = vec4(lessRed, textureColour.g, textureColour.b, 1.0f);
}
#version 330 core

in vec2 textureCoordsOut;

out vec4 colour;

uniform sampler2D texture0;

float greyScale(vec3 colour)
{
	return (colour.r + colour.g + colour.b)/1.5f;
}

vec4 Sepia(vec3 colour)
{
	// Convert image to greyscale
	float grey = greyScale(colour);
	vec3 greyscale = vec3 (grey,grey,grey);

	// Tint shadows
	if (greyscale.r < 0.25)
	{
		greyscale.r *= 1.1f;
		greyscale.b *= 0.9f;
	}
	// Tint midtones
	if (greyscale.r > 0.24 && colour.r < 0.75)
	{
		greyscale.r *= 1.15f;
		greyscale.b *= 0.85f;
	}
	// Tint highlights
	if (greyscale.r > 0.74)
	{
		greyscale.r *= 1.08f;
		greyscale.b *= 0.93f;
		if (greyscale.r > 1)
		{
			greyscale.r = 1.0f;
		}
	}
	// return Sepia Colour
	return vec4 (greyscale.r,greyscale.b,greyscale.g,1.0f);
}

void main()
{
	vec4 textureColour = texture(texture0,textureCoordsOut);
	vec4 sepia = Sepia(textureColour.rgb);
	colour = vec4(sepia);
}

// It doesn't look like sepia, but it looks cool :D
#version 330 core
out vec4 fragColor;

in vec2 Texture;

//uniform vec4 color;
uniform sampler2D  tex_sampler;

void main()
{
	fragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f) * texture(tex_sampler, Texture);
}
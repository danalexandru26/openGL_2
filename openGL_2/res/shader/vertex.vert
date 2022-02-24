#version 330 core

layout ( location = 0 ) in vec3 aPos;
//layout ( location = 1) in vec2 aTex;

out vec2 Texture;
uniform mat4 transform;

void main()
{
//	float angle_offset = atan(aPos.y, aPos.x);
//
//	float x = 0.5 * cos(angle + angle_offset);
//	float y =  0.5 * sin(angle + angle_offset);

	//gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) * transform;
	//Texture = aTex;

	gl_Position = vec4(aPos, 1.0) * transform;
}
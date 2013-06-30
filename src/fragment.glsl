#version 330

out vec4 outputColor;

void main()
{
	if (gl_FrontFacing) {
		outputColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	} else {
		outputColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
}

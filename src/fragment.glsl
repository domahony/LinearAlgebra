#version 330

in vec4 color;
out vec4 outputColor;

void main()
{
	if (gl_FrontFacing) {
		//outputColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
		outputColor = color;
	} else {
		outputColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
}

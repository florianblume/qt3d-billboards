#version 150

uniform sampler2D tex0;

in vec2 UV;

void main(void)
{
    gl_FragColor = texture(tex0, UV);
}

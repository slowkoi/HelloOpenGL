#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = texture(text, TexCoords);
    if(sampled.w > 0.5){
        color = vec4(1.0,1.0,1.0, 1.0);
    }else{
        color = vec4(0.0,0.0,0.0, 1.0);
    }
}
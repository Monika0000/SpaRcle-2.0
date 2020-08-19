#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D Texture;
uniform vec4      color;

void main(){ 
    vec4 result = texture(Texture, TexCoords);
    //vec4 result = vec4(1.0, 0.0, 1.0, 0.6);

    FragColor = result * color;
}
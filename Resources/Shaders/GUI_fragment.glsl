#version 330 core
#extension GL_EXT_gpu_shader4 : enable
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D Texture;
uniform vec4      color;

void main(){ 
    //vec4 _texture = texture(Texture, TexCoords);
    //ivec2 size = textureSize2D(Texture,0) / 20;
    //float total = floor(TexCoords.x*float(size.x)) +
    //              floor(TexCoords.y*float(size.y));
    //bool isEven = mod(total,2.0)==0.0;

    //vec4 col = vec4(0.0, 0.0, 0.0, _texture.a);
    //vec4 result = (isEven)? col:_texture;

    vec4 result = texture(Texture, TexCoords);
    //vec4 result = vec4(1.0, 0.0, 1.0, 0.6);

    FragColor = result * color;
}
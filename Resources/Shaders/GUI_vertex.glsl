#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
uniform vec2 size;
uniform vec2 offset;

void main()
{
    gl_Position = vec4( 
        (aPos * size) + offset, 
        0.0, 1.0); 
    TexCoords = aTexCoords;
}  

//    gl_Position = vec4( 
//        vec2(
//            aPos.x + offset.x, 
//            aPos.y + offset.y
//        ) * size, 
//        0.0, 1.0); 
//    TexCoords = aTexCoords;
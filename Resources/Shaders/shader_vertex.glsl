#version 420 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
//uniform vec3 ObjPos;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
//out vec4 vertex_vs;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    //vec3 T = normalize(vec3(vec4(aTangent,   0.0)));
    //vec3 N = normalize(vec3(vec4(aNormal,    0.0)));
    //vec3 B = cross(N, T);
    //TBN = transpose(mat3(T, B, N)); //TBN = mat3(T, B, N);

    //vertex_vs = projMat * viewMat * vec4(aPosition + ObjPos, 1.0);
    //gl_Position = projMat * viewMat * vec4(aPosition + ObjPos, 1.0);
    //gl_Position = projMat * viewMat * vec4(aPosition, 1.0) * modelMat;
    FragPos = vec3(modelMat * vec4(aPosition, 1.0));
    gl_Position = projMat * viewMat * vec4(FragPos, 1.0);
    //gl_Position = projMat * viewMat * modelMat * vec4(aPosition, 1.0);
    
    //gl_Position = projMat * viewMat * modelMat * 
    //   vec4(aPosition + aNormal, 1.0);
    
    //gl_Position = projMat * viewMat * modelMat * 
    //    vec4(aPosition + Normal, 1.0);
    
    TexCoords = aTexCoords;
    Normal = mat3(transpose(inverse(modelMat))) * aNormal; 
    //Normal    = aNormal;
}
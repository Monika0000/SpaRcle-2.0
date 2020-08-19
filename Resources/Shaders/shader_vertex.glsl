#version 420 core

const int MAX_BONES = 128;

struct Light {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;

    float intensity;
};

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
uniform vec3 viewPos;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec3 Normal0;
} vs_out;

uniform Light light;

uniform int use_anim;
uniform mat4[MAX_BONES] Bones;

void main() {
    //vec3 T = normalize(vec3(vec4(aTangent,   0.0)));
    //vec3 N = normalize(vec3(vec4(aNormal,    0.0)));
    //vec3 B = cross(N, T);
    //TBN = transpose(mat3(T, B, N)); //TBN = mat3(T, B, N);

    //vertex_vs = projMat * viewMat * vec4(aPosition + ObjPos, 1.0);
    //gl_Position = projMat * viewMat * vec4(aPosition + ObjPos, 1.0);
    //gl_Position = projMat * viewMat * vec4(aPosition, 1.0) * modelMat;
    //vs_out.FragPos   = vec3(modelMat * vec4(aPosition, 1.0));
    vs_out.FragPos   = vec3(modelMat * vec4(aPosition, 1.0));
    vs_out.TexCoords = aTexCoords;
    //vs_out.Normal0   = (modelMat * vec4(aNormal, 1.0)).xyz;;
    vs_out.Normal0   = (mat3(transpose(inverse(modelMat))) * aNormal).xyz;

    //////////////////////////////////////////////////////////////
    mat3 normalMatrix = transpose(inverse(mat3(modelMat)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.TangentLightPos = TBN * light.position;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
    //////////////////////////////////////////////////////////////

    gl_Position = projMat * viewMat * vec4(vs_out.FragPos, 1.0);
}
#version 330 core
out vec4 Color;

in vec2 TexCoords;
in vec3 Normal;
//in vec4 vertex_vs;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;
uniform vec4      color;

const vec3 black = vec3(0,0,0);

vec3 RGB(vec4 c) {
    return vec3(c.r, c.g, c.b);
}

float lenght(vec3 v){
    return sqrt(
        pow(v.x, 2) + 
        pow(v.y, 2) +
        pow(v.z, 2)
    );
}

void main(void) {
    //vec3 lightColor = vec3(1, 1, 1);
    //float lightIntensity = 1.f;
    
    //vec3 ambient = lightIntensity * lightColor;
    
    /*vec3 normal = texture(NormalMap, TexCoords).rgb;*/
    
    vec3 N = normalize(Normal);
    vec3 L = normalize(vec3(2, 3, 0));
    
    float diffuse_intensity = max(dot(N, L), 0.0);
    
    //normal = normalize(normal * 2.0 - 1.0);   
    //normal = normalize(TBN * normal);  
    
    vec3 diffuse = texture(DiffuseMap, TexCoords).rgb;
    
    if (diffuse == black)
        diffuse = RGB(color);
    else diffuse *= RGB(color);
    
    diffuse *= diffuse_intensity;

    Color = vec4(diffuse, 1); // - vec3(n, n, n)
}
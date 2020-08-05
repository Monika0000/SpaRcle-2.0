#version 330 core
out vec4 FragColor;
in vec3 FragPos;  

struct Light {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoords;
in vec3 Normal;
//in vec4 vertex_vs;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;
uniform vec4      color;

uniform Light light;

const vec3 black = vec3(0,0,0);
vec3 RGB(vec4 c) { return vec3(c.r, c.g, c.b); }

void main(void) {
    vec3 ambient = light.ambient * texture(DiffuseMap, TexCoords).rgb;

    vec3 N = normalize(Normal);
    vec3 L = normalize(light.position - FragPos);
    float diffuse_intensity = max(dot(N, L), 0.0);
    

    vec3 diffuse = texture(DiffuseMap, TexCoords).rgb;
    //if (diffuse == black)
    //    diffuse = RGB(color);
    //else diffuse *= RGB(color);
    
    diffuse *= diffuse_intensity;

    FragColor = vec4(diffuse, 1); // - vec3(n, n, n)
}



    //vec3 lightColor = vec3(1, 1, 1);
    //float lightIntensity = 1.f;
    
    //vec3 ambient = lightIntensity * lightColor;
    
    /*vec3 normal = texture(NormalMap, TexCoords).rgb;*/
        //normal = normalize(normal * 2.0 - 1.0);   
    //normal = normalize(TBN * normal);  
    
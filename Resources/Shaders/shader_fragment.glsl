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

    float intensity;
};

in vec2 TexCoords;
in vec3 Normal;
//in vec4 vertex_vs;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;
uniform sampler2D SpecularMap;
uniform vec4      color;

uniform vec3 viewPos;

uniform int use_light;
uniform Light light;
//const vec3 black = vec3(0,0,0);
//vec3 RGB(vec4 c) { return vec3(c.r, c.g, c.b); }

void main(void) {
    if(use_light == 1) {
        // ambient
        vec3 ambient = light.ambient * texture(DiffuseMap, TexCoords).rgb;

        // diffuse 
        vec3 N = normalize(Normal);
        vec3 L = normalize(light.position - FragPos); // lightDir 
        float diffuse_intensity = max(dot(N, L), 0.0);
        vec3 diffuse = texture(DiffuseMap, TexCoords).rgb * color.rgb * light.diffuse * diffuse_intensity;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 R = reflect(-L, N); // reflectDir 
        float spec = pow(max(dot(viewDir, R), 0.0), 5); //material.shininess
        vec3 specular = light.specular * spec * texture(SpecularMap, TexCoords).rgb; 

        // attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)) * light.intensity; 

        diffuse  *= attenuation;
        ambient  *= attenuation;
        specular *= attenuation;

        FragColor = vec4(diffuse + ambient + specular, 1.0);
    } else {
        FragColor = vec4(texture(DiffuseMap, TexCoords).rgb * color.rgb, 1.0); // - vec3(n, n, n)
    }
}

//  if (diffuse == vec3(0,0,0)) diffuse = color.rgb;
  // else diffuse *= color.rgb;


    //vec3 lightColor = vec3(1, 1, 1);
    //float lightIntensity = 1.f;
    
    //vec3 ambient = lightIntensity * lightColor;
    
    /*vec3 normal = texture(NormalMap, TexCoords).rgb;*/
        //normal = normalize(normal * 2.0 - 1.0);   
    //normal = normalize(TBN * normal);  
    
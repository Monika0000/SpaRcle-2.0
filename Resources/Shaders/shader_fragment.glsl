#version 330 core
out vec4 FragColor;
//in vec3 FragPos;  

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

//in vec2 TexCoord0;
//in vec3 Normal0;
//in vec3 Tangent0;
//in vec4 vertex_vs;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec3 Normal0;
} fs_in;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;
uniform sampler2D SpecularMap;
uniform vec4      color;

uniform mat4 modelMat;
uniform vec3 viewPos;

uniform int use_light;
uniform Light light;

//const vec3 black = vec3(0,0,0);
//vec3 RGB(vec4 c) { return vec3(c.r, c.g, c.b); }

//mat3 TBN;

//vec3 CalcBumpedNormal() {
//void CalcTBN() {
//    vec3 Normal = normalize(Normal0);
//    vec3 Tangent = normalize(Tangent0);
//    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
//    vec3 Bitangent = cross(Tangent, Normal);
//    vec3 BumpMapNormal = texture(NormalMap, TexCoord0).xyz;
//    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    //vec3 NewNormal;
    //mat3 TBN = mat3(Tangent, Bitangent, Normal);
//    TBN = mat3(Tangent, Bitangent, Normal);
    //NewNormal = TBN * BumpMapNormal;
    //NewNormal = normalize(NewNormal);
    //return NewNormal;
//}


//void CalcTBN() {
//    mat3 normalMatrix = transpose(inverse(mat3(modelMat)));
//    vec3 T = normalize(normalMatrix * Tangent0);
//    vec3 N = normalize(normalMatrix * Normal0);
//    T = normalize(T - dot(T, N) * N);
//    vec3 B = cross(N, T);

//    TBN = transpose(mat3(T, B, N));    

    //TangentLightPos = TBN * light.position;
    //TangentViewPos  = TBN * viewPos;
    //TangentFragPos  = TBN * FragPos;
//}

void main(void) {
    if(use_light == 1) {
        // ambient
        vec3 ambient = light.ambient * texture(DiffuseMap, fs_in.TexCoords).rgb;

        // diffuse 
        vec3 N = normalize(fs_in.Normal0);
        vec3 lightDir  = normalize(light.position - fs_in.FragPos); // lightDir 
        float diffuse_intensity = max(dot(N, lightDir ), 0.0);
        vec4 _texture = texture(DiffuseMap, fs_in.TexCoords);
        if(_texture.a < 0.1)
            discard;
        vec3 diffuse = _texture.rgb * color.rgb * light.diffuse * diffuse_intensity;

        // specular
        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        vec3 halfwayDir = normalize(lightDir  + viewDir);  
        float spec = pow(max(dot(N, halfwayDir), 0.0), 16.0);
        vec3 specular = light.specular * spec * texture(SpecularMap, fs_in.TexCoords).rgb; 

        // attenuation
        float distance    = length(light.position - fs_in.FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)) * light.intensity; 

        diffuse  *= attenuation;
        ambient  *= attenuation;
        specular *= attenuation;

        FragColor = vec4(diffuse + ambient + specular, _texture.a);
    } else if (use_light == 2) {
        // ambient
        vec3 ambient = light.ambient * texture(DiffuseMap, fs_in.TexCoords).rgb;

        // diffuse 
        vec3 N = texture(NormalMap, fs_in.TexCoords).rgb;
        N = normalize(N * 2.0 - 1.0);// * normalize(fs_in.Normal0); // перевод вектора нормали в интервал [-1,1]  

        //vec3 lightDir  = normalize(light.position - fs_in.FragPos); // lightDir 
        vec3 lightDir = normalize(fs_in.TangentLightPos  - fs_in.TangentFragPos);
        float diffuse_intensity = max(dot(N, lightDir ), 0.0);
        vec4 _texture = texture(DiffuseMap, fs_in.TexCoords);
        if(_texture.a < 0.1)
            discard;
        vec3 diffuse = _texture.rgb * color.rgb * light.diffuse * diffuse_intensity;

        // specular
        vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
        //vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        //vec3 reflectDir = reflect(-L, N); // reflectDir 
        //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 5); //material.shininess
        vec3 halfwayDir = normalize(lightDir  + viewDir);  
        float spec = pow(max(dot(N, halfwayDir), 0.0), 16.0);
        vec3 specular = light.specular * spec * texture(SpecularMap, fs_in.TexCoords).rgb; 

        // attenuation
        float distance    = length(light.position - fs_in.FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)) * light.intensity; 

        diffuse  *= attenuation;
        ambient  *= attenuation;
        specular *= attenuation;

        FragColor = vec4(diffuse + ambient + specular, _texture.a);
    } else {
        vec4 _texture = texture(DiffuseMap, fs_in.TexCoords);
        if(_texture.a < 0.1)
            discard;
        FragColor = vec4(_texture.rgb * color.rgb, _texture.a); // - vec3(n, n, n)
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
    
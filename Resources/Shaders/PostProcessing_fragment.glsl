#version 330 core
#extension GL_EXT_gpu_shader4 : enable

out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0;  
const vec2 offsets[9] = vec2[](
    vec2(-offset,  offset), // top-left
    vec2( 0.0f,    offset), // top-center
    vec2( offset,  offset), // top-right
    vec2(-offset,  0.0f),   // center-left
    vec2( 0.0f,    0.0f),   // center-center
    vec2( offset,  0.0f),   // center-right
    vec2(-offset, -offset), // bottom-left
    vec2( 0.0f,   -offset), // bottom-center
    vec2( offset, -offset)  // bottom-right    
);


const float kernel[9] = float[](
    1.0 / 16,   2.0 / 16,   1.0 / 16,

    2.0 / 16,   4.0 / 16,   2.0 / 16,

    1.0 / 16,   2.0 / 16,   1.0 / 16  
);

const float gamma = 0.8;

void main(){ 

    //vec4 color = texelFetch(screenTexture, TexCoords, 3);  // считывание из 4ой точки подвыборки
    vec3 result = texture(screenTexture, TexCoords).rgb;
    //result = result / 2;
    // if (result.r < 0.6 && result.g < 0.6 && result.b > 0.5)
    //    result.b += 0.25;

    //FragColor = texture(screenTexture, TexCoords);
    //FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}
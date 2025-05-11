#version 330 core

in vec3 TexCoords;
out vec4 FragColor;

uniform samplerCube skybox1;  // <- Debe coincidir con C++
uniform samplerCube skybox2;
uniform float blendFactor;

void main()
{
    vec4 tex1 = texture(skybox1, TexCoords);
    vec4 tex2 = texture(skybox2, TexCoords);
    FragColor = mix(tex1, tex2, blendFactor);
}

#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec3 vertexPos;
// output data
out vec3 color;
uniform float ambientStrength;
uniform mat4 Model;
uniform vec3 PlayerPosition;
uniform vec3 viewPos;
uniform float specularStrength = 0.7;
void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    vec3 FragPos = vec3(Model * vec4(vertexPos, 1.0));
    vec3 viewDir = normalize(FragPos+vec3(0.0f,0.0f,1.0f) - FragPos);
    vec3 norm=vec3(0.0f,0.0f,-1.0f);
    vec3 lightDir=normalize(PlayerPosition-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 512);
    vec3 specular = specularStrength * spec*vec3(1.0f,1.0f,1.0f);  
    color =(ambientStrength+specular)* fragColor;
}

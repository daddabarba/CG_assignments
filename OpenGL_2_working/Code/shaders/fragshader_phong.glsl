#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertCoord;
in vec3 vertNorm;
in vec2 texCoord;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

uniform mat4 modelTransform;
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform vec3 lightCol;
uniform vec3 objCol;
uniform vec3 material;
uniform sampler2D sampler;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fNorm;

void main()
{
    vec3 N = normalize(normalMatrix * vertNorm);
    vec3 P = vec3(modelTransform * vec4(vertCoord, 1.0));

    vec3 IA = objCol*material.x;

    vec3 L = normalize(lightPos - vertCoord);
    vec3 ID = objCol*lightCol*(material.y)*max(0.0,dot(L,vertNorm));

    vec3 R = normalize(2*dot(vertNorm,L)*vertNorm - L);
    vec3 V = normalize(vec3(0.0,0.0,0.0) - P);
    vec3 IS = lightCol*material.z*pow(max(0.0,dot(R,V)), 16);

    vec4 textureColor = texture2D(sampler, texCoord);

    fNorm = vec4((IA+ID+IS), 1.0) * textureColor;
}

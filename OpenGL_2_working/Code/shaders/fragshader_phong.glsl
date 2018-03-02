#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertCoord;
in vec3 vertNorm;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

uniform vec3 lightPos;
uniform vec3 lightCol;
uniform vec3 objCol;
uniform vec3 material;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fNorm;

void main()
{
    vec3 P = vec3(vertCoord);

    vec3 IA = objCol*material.x;

    vec3 L = normalize(lightPos-P);
    vec3 ID = objCol*lightCol*(material.y)*max(0.0,dot(L,vertNorm));

    vec3 R = 2*dot(vertNorm,L)*vertNorm - L;
    vec3 V = normalize(vec3(0.0,0.0,0.0) - P);
    vec3 IS = lightCol*material.z*max(0.0,dot(R,V));

    fNorm = vec4(IA+ID+IS, 1.0);
}

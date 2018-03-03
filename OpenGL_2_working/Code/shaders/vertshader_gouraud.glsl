#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNorm_in;
layout (location = 2) in vec2 vertTexCoord_in;

// Specify the Uniforms of the vertex shader
// uniform mat4 modelTransform; for example
uniform mat4 modelTransform;  //uniform for model transformation matrix (rotation, translation, and scaling)
uniform mat4 projection; //uniform for projection transformation matrix
uniform mat3 normalMatrix;

uniform vec3 lightPos;
uniform vec3 lightCol;
uniform vec3 objCol;
uniform vec3 material;

// Specify the output of the vertex stage
out vec3 color;
out vec2 texCoord;

void main()
{
    vec3 N = normalize(vertNorm_in);
    vec4 newCoordinates = modelTransform * vec4(vertCoordinates_in, 1.0);
    vec3 P = vec3(newCoordinates);

    vec3 IA = objCol*material.x;

    vec3 L = normalize(lightPos - vertCoordinates_in);
    vec3 ID = objCol*lightCol*material.y*max(0.0,dot(L,N));

    vec3 R = 2*dot(N,L)*N - L;
    vec3 V = normalize(vec3(0.0,0.0,0.0) - P);
    vec3 IS = lightCol*material.z*pow(max(0.0,dot(R,V)), 16);

    gl_Position = projection*newCoordinates;
    color = (IA+ID+IS);
    texCoord = vertTexCoord_in;
}

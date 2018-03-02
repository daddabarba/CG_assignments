#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNorm_in;

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

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation

    vec3 N = vertNorm_in;
    vec4 newCoordinates = modelTransform * vec4(vertCoordinates_in, 1.0);

    vec3 IA = objCol*material.x;

    vec3 L = normalize(lightPos-vertCoordinates_in);
    vec3 ID = objCol*lightCol*material.y*max(0.0,dot(L,N));

    vec3 R = 2*dot(N,L)*N - L;
    vec3 V = normalize(vec3(0.0,0.0,0.0) - vertCoordinates_in);
    vec3 IS = lightCol*material.z*max(0.0,dot(R,V));

    gl_Position = projection*newCoordinates;
    color = (IA+ID+IS);
}

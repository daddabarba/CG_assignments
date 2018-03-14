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
uniform mat4 viewTransform; //uniform for view transformation matrix
uniform mat3 viewTransformNormal;
uniform mat3 normalMatrix;

// Specify the output of the vertex stage
out vec3 vertNorm;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation


    //first apply model tranfromation, then project on window
    gl_Position = projection * viewTransform * modelTransform * vec4(vertCoordinates_in, 1.0);
    //return transfornmed normal as color
    vertNorm = viewTransformNormal * normalMatrix * vertNorm_in;
}

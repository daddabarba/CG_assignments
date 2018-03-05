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
uniform vec4 material;

// Specify the output of the vertex stage
out vec3 color;
out vec2 texCoord;

void main()
{
    //transforming normal
    vec3 N = normalize(normalMatrix * vertNorm_in);
    //transformin point
    vec4 newCoordinates = modelTransform * vec4(vertCoordinates_in, 1.0);
    //clipping point to r3
    vec3 P = vec3(newCoordinates);

    //computing ambience coefficent
    vec3 IA = objCol*material.x;

    //computing light vector
    vec3 L = normalize(vec3(modelTransform * vec4(lightPos,1.0)) - P);
    //computing diffuse coefficent
    vec3 ID = objCol*lightCol*material.y*max(0.0,dot(L,N));

    //reflecting light vector
    vec3 R = normalize(-reflect(L,N));
    //computing p.o.v. vector
    vec3 V = normalize(vec3(0.0,0.0,0.0) - P);
    //computing specular coefficent
    vec3 IS = lightCol*material.z*pow(max(0.0,dot(R,V)), material.w);

    //applying projection transform
    gl_Position = projection*newCoordinates;
    //computing final color
    color = (IA+ID+IS);
    //passing texture to frag. shader
    texCoord = vertTexCoord_in;
}

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

// Specify the output of the vertex stage
out vec3 vertCoord;
out vec3 vertNorm;
out vec2 texCoord;

void main()
{
    //easier to transform the interpolate (automatic), then interpolate and
    //then transform (every interpolation in frag. shader)

    //transform point coordinates
    vec4 vertCoord_transformed = modelTransform * vec4(vertCoordinates_in, 1.0);
    //return position after adding projection transformation
    gl_Position = projection * vertCoord_transformed;

    //trasnformed vertex coordinates for fragment shader
    vertCoord = vec3(vertCoord_transformed);
    //transforming normal
    vertNorm = normalize(normalMatrix * vertNorm_in);
    //texture mapping
    texCoord = vertTexCoord_in;
}

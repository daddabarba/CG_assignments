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
uniform mat4 viewTransform; //uniform for view transformation matrix
uniform mat3 viewTransformNormal;
uniform mat3 normalMatrix;

uniform int num_waves;
uniform float amplitude[4];
uniform float phi[4];
uniform float omega[4];
uniform float time;

// Specify the output of the vertex stage
out vec3 vertCoord;
out vec3 vertNorm;
out vec2 texCoord;

//double A = 5; //NORMALS
//double phi = 3.14; //NORMALS
//double omega = 6.28; //NORMALS

float du = 0.0f, dv = 0.0f;

float waveHeight(int waveIdx, float uValue){
    return amplitude[waveIdx]*sin(omega[waveIdx]*uValue + phi[waveIdx] + time);
}

float waveDU(int waveIdx, float uValue){
    return amplitude[waveIdx]*cos(omega[waveIdx]*uValue + phi[waveIdx] + time)*omega[waveIdx];
}

void main()
{
    //easier to transform the interpolate (automatic), then interpolate and
    //then transform (every interpolation in frag. shader)

    vec3 mapped_coord = vertCoordinates_in;

    //mapped_coord.z = A*sin(omega*vertTexCoord_in.x + phi); //NORMALS
    for(int i=0; i<num_waves; i++){
        mapped_coord.z += waveHeight(i, vertTexCoord_in.x);
        du += waveDU(i, vertTexCoord_in.x);
    }

    //transform point coordinates
    vec4 vertCoord_transformed = modelTransform * vec4(mapped_coord, 1.0);
    //return position after adding projection transformation
    gl_Position = projection * viewTransform * vertCoord_transformed;

    //transformed vertex coordinates for fragment shader
    vertCoord = vec3(vertCoord_transformed);

    //du = A*cos(omega*vertTexCoord_in.x + phi)*omega; //NORMALS

    //transforming normal
    vertNorm = normalize(normalMatrix * vec3(-du,-dv, 1.0));


    //texture mapping
    texCoord = vertTexCoord_in;
}

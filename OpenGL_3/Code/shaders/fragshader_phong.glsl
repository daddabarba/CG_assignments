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
uniform mat4 viewTransform;
uniform mat3 normalMatrix;
uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightCol;
uniform vec3 objCol;
uniform vec4 material;
uniform sampler2D sampler;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fNorm;

void main()
{
    //Computing ambient illuminance
    vec3 IA = objCol*material.x;

    //applying model transform to light too, while also computing L itself
    vec3 L = normalize(lightPos - vertCoord);
    //compute diffuse term
    vec3 ID = objCol*lightCol*(material.y)*max(0.0,dot(L,vertNorm));

    //Reflecting light vector
    vec3 R = normalize(-reflect(L, vertNorm));
    //getting p.o.v. vector
    vec3 V = normalize(cameraPos - vertCoord);
    //computing specular coefficent
    vec3 IS = lightCol*material.z*pow(max(0.0,dot(R,V)), material.w);

    //getting texture (mapping)
    vec4 textureColor = texture2D(sampler, texCoord);

    //returning color
    fNorm = vec4((IA+ID+IS), 1.0) * textureColor;
}

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
out vec4 fColor;

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

    //returning color

    //Computing water color according to height
    float val = smoothstep(-2.0f, 2.0f, vertCoord.y);
    vec4 waveCol = vec4(mix(0.0f, 1.0f, val), mix(0.2f, 1.0f, val), 1.0f, 1.0f);
    fColor = vec4((IA+ID+IS), 1.0) * waveCol;

    //vertNorm = vertNorm*0.5 + 0.5; //NORMAL
    //fColor = vec4(vertNorm, 1.0); //NORMAL

    //fColor = vec4(texCoord,0.0,1.0);//HEIGHT MAP
}
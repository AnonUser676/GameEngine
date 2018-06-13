#version 410

layout( location = 0) in vec4 Position;
layout( location = 1) in vec4 Normal;
//layout( location = 2) in vec2 TexCoord;
//layout( location = 3) in vec4 Tangent;

//out vec2 vTexCoord;
out vec4 vPosition;
out vec3 vNormal;
//out vec3 vTangent;
//out vec3 vBiTangent;

uniform mat4 ProjectionViewModel;

//we need this matrix to transform the position of light and normal
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;

void main()
{
vPosition = ModelMatrix * Position;
vNormal = NormalMatrix * Normal.xyz;
//vTexCoord = TexCoord;
//vTexCoord.y = 1-vTexCoord.y;
//vTangent = NormalMatrix * Tangent.xyz;
//vBiTangent = cross(vNormal, vTangent) * Tangent.w;
gl_Position = ProjectionViewModel * Position;
}
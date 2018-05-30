#version 410

layout( location = 0) in vec4 Position;
layout( location = 1) in vec4 Normal;
layout( location = 2) in vec2 TexCoord;

out vec2 vTexCoord;

out vec3 vNormal;

uniform mat4 ProjectionViewModel;

uniform mat3 NormalMatrix;

void main()
{
vNormal = NormalMatrix * Normal.xyz;
vTexCoord = TexCoord;
vTexCoord.y = 1-vTexCoord.y;
gl_Position = ProjectionViewModel * Position;
}
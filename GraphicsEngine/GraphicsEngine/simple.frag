#version 410

in vec2 vTexCoord;
in vec4 vPosition;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;

uniform vec3 Ia; //ambient light color
uniform vec3 Id; //diffuse light color
uniform vec3 Is; //specular light color
uniform vec3 LightDirection;

uniform vec3 Ka; //ambient material color
uniform vec3 Kd; //diffuse material color
uniform vec3 Ks; //specular material color
uniform vec3 cameraPosition;
uniform float specularPower; //material specular power

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

out vec4 FragColour;

void main()
{
//ensure normal and light direction are normalised
vec3 N = normalize(vNormal);
vec3 L = normalize(LightDirection);
vec3 B = normalize(vBiTangent);
vec3 T = normalize(vTangent);
mat3 TBN = mat3(T,B,N);

vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
vec3 texNormal = texture(normalTexture, vTexCoord).rgb;

N = TBN * (texNormal * 2 - 1);

//calculate lambert term (negate light direction)
float lambertTerm = max( 0, dot(N, -L));

//calculate view vector and reflection vector
vec3 V = normalize(cameraPosition - vPosition.xyz);
vec3 R = reflect(L,N);

//calculate specular term
float specularTerm = pow(max(0, dot(R,V)), specularPower);

//calculate diffuse
vec3 ambient = Ia * Ka;
vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
vec3 specular = Is * Ks * texSpecular * specularTerm;

//output final colour
FragColour = vec4(ambient + diffuse + specular, 1);
}
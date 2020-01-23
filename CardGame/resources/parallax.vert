#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;
uniform vec3 model;
uniform mat4 mvp;
out vec2 fragTexCoord;
out vec4 fragColor;
out vec3 worldPosition;

void main()
{
    worldPosition = (vertexPosition + model)*vec3(1,0,1);
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    gl_Position = mvp*vec4(vertexPosition, 1.0);
}
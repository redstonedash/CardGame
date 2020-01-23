#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 worldPosition;
// Input uniform values
uniform sampler2D texture0; //albedo
uniform sampler2D texture1; //depth
uniform sampler2D texture2; //emmision
uniform sampler2D texture3; //layer
uniform sampler2D texture4; //normal
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = vec4(texture(texture3, fragTexCoord).xyz,1);
    
    // NOTE: Implement here your fragment shader code
    
    finalColor = texelColor;
}


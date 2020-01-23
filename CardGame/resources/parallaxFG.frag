#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 worldPosition;

uniform sampler2D texture0; //albedo
uniform sampler2D texture1; //depth
uniform sampler2D texture2; //emmision
uniform sampler2D t3; //layer
uniform sampler2D t4; //normal
uniform vec3 model; //position of center of card    
uniform float thickness;
uniform float scale;
//camera position = 0,1,0

out vec4 finalColor;
int stepAmmount = 100; //make a uniform so it can be in quality settings

vec2 getTexturePosition(vec2 worldPos){
    return ((worldPos-model.xz)/scale + vec2(0.5,0.5));
} 

void main(){
    float actualThickness = thickness;
    vec3 dir = normalize(vec3(0,1,0)-worldPosition);
    vec3 rayPos = vec3(worldPosition.x,0,worldPosition.z) + (dir * (actualThickness / dir.y));
    vec2 hitPos = vec2(-1,-1);
    float height = -100;
    for(int i = stepAmmount; i >= 0; i--){
        vec2 tempPos = getTexturePosition(mix(worldPosition, rayPos, float(i)/float(stepAmmount)).xz);
        float rayHeight = mix(worldPosition, rayPos, float(i)/float(stepAmmount)).y/actualThickness;
        if( rayHeight <= texture(texture1, tempPos).x && !(tempPos.x >= 1 || tempPos.x<=0 || tempPos.y<=0 || tempPos.y>=1) && (texture(texture1, tempPos).x-rayHeight)<0.2){
            hitPos = tempPos;
            break;
        }
    }
    if((hitPos.x >= 1 || hitPos.x<=0 || hitPos.y<=0 || hitPos.y>=1) || texture(t3,hitPos).x<0.5)
    {
       discard;
    }
    finalColor = vec4(texture(texture2,hitPos).xyz, 1);
}
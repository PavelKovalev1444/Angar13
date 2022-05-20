#version 330 core

in vec4 myColor;
in vec3 Normal;
in vec3 FragPos;

uniform int type;

uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform vec3 cameraPos;

uniform vec3 ambientLight;
uniform vec3 diffuseLight;
uniform vec3 specularLight;

uniform float lightConstant;
uniform float lightLinear;
uniform float lightQuadratic;

uniform float lightCutOff;

out vec4 outColor;

void directedLight(){
    float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * ambientLight;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseLight;

    float specularStrength = 0.6;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
    vec3 specular = specularStrength * spec * specularLight;

    outColor = vec4((ambient + diffuse + specular) * vec3(myColor.xyz), 1.0);
}

void pointLight(){
    float distance = length(lightPosition - FragPos);
    float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));

    float ambientStrength = 0.8;
    vec3 ambient = attenuation * ambientStrength * ambientLight;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = attenuation * diff * diffuseLight;

    float specularStrength = 0.7;
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
    vec3 specular = attenuation * specularStrength * spec * specularLight;

    outColor = vec4((ambient + diffuse + specular) * vec3(myColor.xyz), 1.0);
}

void projector(){
    vec3 lightDir = normalize(lightPosition - FragPos);
    float theta = dot(lightDir, normalize(-lightDirection));
    if(theta < lightCutOff){

        float distance = length(lightPosition - FragPos);
        float attenuation = 1.0 / (lightConstant + lightLinear * distance + lightQuadratic * (distance * distance));

        float ambientStrength = 0.8;
        vec3 ambient = ambientStrength * ambientLight;

        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPosition - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = attenuation * diff * diffuseLight;

        float specularStrength = 0.7;
        vec3 viewDir = normalize(cameraPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
        vec3 specular = attenuation * specularStrength * spec * specularLight;

        outColor = vec4((ambient + diffuse + specular) * vec3(myColor.xyz), 1.0);
    }else{
        float ambientStrength = 0.8;
        vec3 ambient = ambientStrength * ambientLight;
        outColor = vec4((ambient) * vec3(myColor.xyz), 1.0);
    }
}

void main(void)
{
    switch(type){
        case 1:
            directedLight();
            break;
        case 2:
            pointLight();
            break;
        case 3:
            projector();
            break;
        case 4:
            outColor = myColor;
            break;
        case 0:
        default:
            outColor = myColor;
            break;
    }

}

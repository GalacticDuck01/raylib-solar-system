#version 330

uniform vec3 tint;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

out vec4 FragColor;

in vec3 FragPosition;

void main() {
    vec3 lightAmbient = vec3(0.5, 0.5, 0.5);
    vec3 lightDiffuse = vec3(1.0, 1.0, 1.0);
    vec3 lightSpecular = vec3(0.5, 0.5, 0.5);

    vec3 blockAmbient = vec3(0.4, 0.4, 0.4);
    vec3 blockDiffuse = vec3(0.5, 0.5, 0.5);
    vec3 blockSpecular = vec3(1.0, 1.0, 1.0);

    vec3 ambient = lightAmbient * blockAmbient;

    // Rebuild a face normal from world-space position derivatives so the
    // lighting stays constant across the entire triangle.
    vec3 positionDx = dFdx(FragPosition);
    vec3 positionDy = dFdy(FragPosition);
    vec3 normal = normalize(cross(positionDx, positionDy));

    vec3 lightDirection = normalize(lightPosition - FragPosition);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diff * lightDiffuse * blockDiffuse;

    vec3 viewDirection = normalize(cameraPosition - FragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32.0);
    vec3 specular = spec * lightSpecular * blockSpecular;

    FragColor = vec4((ambient + diffuse + specular) * tint, 1.0);
}

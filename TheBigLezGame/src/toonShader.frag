#version 330 core

#define NUMBER_OF_POINT_LIGHTS 1

struct PointLight
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Light
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;

    float shininess;
	float transparency; //?
};


in vec3 FragPos;		// Replaces frag_pos
in vec3 Normal;			// Replaces normal
in vec2 TexCoords;		// Replaces text_coords
in vec4 ModelView;		// Replaces viewSpace
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform DirLight dirLight;
uniform PointLight pointLights[1];

//fog variables
const vec3 fogColor = vec3(0.5, 0.5,0.5);
const float FogDensity = 0.1;

vec3 CalcSpotLight( Light light, vec3 normal, vec3 fragPos, vec3 viewDir )
{
    vec3 lightDir = normalize( light.position - fragPos );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), material.shininess );
    
    // Attenuation
    float distance = length( light.position - fragPos );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Spotlight intensity
    float theta = dot( lightDir, normalize( -light.direction ) );
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp( ( theta - light.outerCutOff ) / epsilon, 0.0, 1.0 );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( material.texture_diffuse1, TexCoords ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( material.texture_diffuse1, TexCoords ) );
    vec3 specular = light.specular * spec * vec3( texture( material.texture_specular1, TexCoords ) );
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return ( ambient + diffuse + specular );
}

vec3 CalcDirLight( DirLight light, vec3 normal, vec3 viewDir )
{
    vec3 lightDir = normalize( -light.direction );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), material.shininess );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( material.texture_diffuse1, TexCoords ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( material.texture_diffuse1, TexCoords ) );
    vec3 specular = light.specular * spec * vec3( texture( material.texture_specular1, TexCoords ) );
    
    return ( ambient + diffuse + specular );
}

// Calculates the color when using a point light.
vec3 CalcPointLight( PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir )
{
    vec3 lightDir = normalize( light.position - fragPos );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), material.shininess );
    
    // Attenuation
    float distance = length( light.position - fragPos );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( material.texture_diffuse1, TexCoords ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( material.texture_diffuse1, TexCoords ) );
    vec3 specular = light.specular * spec * vec3( texture( material.texture_specular1, TexCoords ) );
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ( ambient + diffuse + specular );
}

void main( )
{
    // Properties
   // vec3 norm = normalize( Normal );
    vec3 viewDir = normalize( viewPos - FragPos );
    
	//vec3 calcLight = vec3(0.0f, 0.0f, 0.0f);


    // Directional lighting
   vec3 calcLight = CalcDirLight( dirLight, Normal, viewDir );
    
    
    // Spot light
   //calcLight += CalcSpotLight( light, Normal, FragPos, viewDir );

    // Point lights
    for ( int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++ )
    {
     //   calcLight += CalcPointLight( pointLights[i], Normal, FragPos, viewDir );
    }

	
////////////////////////////////fog shading //////////////////////////////

vec3 RimColor = vec3(0.2, 0.2, 0.2);
vec3 tex1 = texture(material.texture_diffuse1, TexCoords).rgb;


//get light an view directions
vec3 L = normalize(LightDirection_cameraspace);
vec3 V = normalize(EyeDirection_cameraspace);

//diffuse lighting
vec3 fogNorm = normalize(Normal);
vec3 diffuse = light.diffuse * max(0, dot(L, fogNorm));

//rim lighting
float rim = 1 - max(dot(V, fogNorm), 0.0);
rim = smoothstep(0.6, 1.0, rim);
vec3 finalRim = RimColor * vec3(rim, rim, rim);
//get all lights and texture
vec3 lightColor = finalRim + diffuse + tex1;

vec3 finalColor = vec3(0, 0, 0);

//distance
float dist = 0;
float fogFactor = 0;

//compute distance used in fog equations

//range based
dist = length(ModelView);

fogFactor = 1.0 / exp((dist * FogDensity)* (dist * FogDensity));
fogFactor = clamp(fogFactor, 0.0, 1.0);
finalColor = mix(fogColor, vec3(calcLight), fogFactor);

color = vec4(finalColor, 1);

}



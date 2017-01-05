uniform vec4 eyePosW;   
uniform vec4 eyeNormalW; 
uniform vec4 lightPosW; 
uniform vec4 lightColor; 

uniform vec4 materialEmissive;
uniform vec4 materialDiffuse;
uniform vec4 materialSpecular;
uniform float materialShininess;

uniform vec4 ambient; 

varying vec4 f_position;
varying vec4 f_normal;
varying vec2 f_texcoord;

uniform sampler2D mytexture;

// void main()
// {
//     vec4 emissive = materialEmissive;

//     vec4 N = normalize(f_normal);
//     vec4 L = normalize(lightPosW - f_position);
//     float NdotL =  max(dot(N, L), 0);
//     vec4 diffuse =  NdotL * lightColor * materialDiffuse;
    
//     vec4 V = normalize( eyePosW - f_position );
//     vec4 H = normalize( L + V );
//     vec4 R = reflect( -L, N );
//     float RdotV = max(dot( R, V ), 0);
//     float NdotH = max(dot( N, H ), 0);
//     vec4 specular = pow(RdotV, materialShininess);// * lightColor * materialSpecular;
    
//     gl_FragColor = (emissive + ambient + diffuse /*+ specular*/) * texture2D(mytexture, f_texcoord);
// }

// uniform vec3 uAmbient;
// uniform vec3 uDiffuse;
// uniform vec3 uSpecular;
// uniform float uSpecIntensity;
// uniform float uTransparency;

// uniform vec3 uSunPos;
// uniform vec3 uEyePos;
// varying vec3 varEyeNormal;

// void main(void)
// {
//     vec3 uEyePos = eyePosW.xyz;
//     vec3 varEyeNormal = eyeNormalW.xyz;
//     vec3 uSunPos = lightPosW.xyz;
//     float uSpecIntensity = 1;
//     vec3 N = varEyeNormal;
//     vec3 L = normalize(uSunPos);
//     vec3 H = normalize(L + uEyePos);

//     float df = max(0.0, dot(N, L));
//     float sf = max(0.0, dot(N, H));
//     sf = pow(sf, uSpecIntensity);

//     vec3 uAmbient  = vec3(0.3, 0.3, 0.3);
//     vec3 uSpecular = vec3(0.3, 0.3, 0.3);
//     vec3 uDiffuse  = vec3(0.3, 0.3, 0.3);

//     vec3 col = uAmbient + uDiffuse * df + uSpecular * sf;

//     gl_FragColor = vec4(col, 1) * vec4(1, 0.5, 0.5, 1);
// }



vec4 position = f_position;  // position of the vertex (and fragment) in world space
vec3 varyingNormalDirection = f_normal;  // surface normal vector in world space
// uniform mat4 m, v, p;
mat4 v_inv = mat4(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);



struct lightSource
{
  vec4 position;
  vec4 diffuse;
  vec4 specular;
  float constantAttenuation, linearAttenuation, quadraticAttenuation;
  float spotCutoff, spotExponent;
  vec3 spotDirection;
};
lightSource light0 = lightSource(
  vec4(0.0,  1.0,  2.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  vec4(1.0,  1.0,  1.0, 1.0),
  0.0, 1.0, 0.0,
  180.0, 0.0,
  vec3(0.0, 0.0, 0.0)
);
vec4 scene_ambient = vec4(0.4, 0.2, 0.2, 1.0);
 
struct material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};
material frontMaterial = material(
  vec4(0.2, 0.2, 0.2, 1.0),
  vec4(2.0, 1.8, 1.8, 1.0),
  vec4(1.0, 1.0, 1.0, 1.0),
  5.0
);

void main()
{
  vec3 normalDirection = normalize(varyingNormalDirection);
  vec3 viewDirection = normalize(vec3(v_inv * eyePosW - position));
  vec3 lightDirection;
  float attenuation;
  
  if (0.0 == light0.position.w) // directional light?
    {
      attenuation = 1.0; // no attenuation
      lightDirection = normalize(vec3(light0.position));
    } 
  else // point light or spotlight (or other kind of light) 
    {
      vec3 positionToLightSource = vec3(light0.position - position);
      float distance = length(positionToLightSource);
      lightDirection = normalize(positionToLightSource);
      attenuation = 1.0 / (light0.constantAttenuation
                           + light0.linearAttenuation * distance
                           + light0.quadraticAttenuation * distance * distance);
      
      if (light0.spotCutoff <= 90.0) // spotlight?
    {
      float clampedCosine = max(0.0, dot(-lightDirection, light0.spotDirection));
      if (clampedCosine < cos(radians(light0.spotCutoff))) // outside of spotlight cone?
        {
          attenuation = 0.0;
        }
      else
        {
          attenuation = attenuation * pow(clampedCosine, light0.spotExponent);   
        }
    }
    }
  
  vec3 ambientLighting = vec3(scene_ambient) * vec3(frontMaterial.ambient);
  
  vec3 diffuseReflection = attenuation 
    * vec3(light0.diffuse) * vec3(frontMaterial.diffuse)
    * max(0.0, dot(normalDirection, lightDirection));
  
  vec3 specularReflection;
  if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
    {
      specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
    }
  else // light source on the right side
    {
      specularReflection = attenuation * vec3(light0.specular) * vec3(frontMaterial.specular) 
    * pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), frontMaterial.shininess);
    }
  
  gl_FragColor = vec4(ambientLighting + diffuseReflection + specularReflection, 1.0) * texture2D(mytexture, f_texcoord);
}

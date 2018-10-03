#ifndef LIGHT_H
#define LIGHT_H


#include "Ray.h"
#include "Hitable.h"

// Light class, for Blinn-Phong model
class Light
{
public:

    Light();
    Light(vec3 &pos, vec3 &amb, vec3 &dif, vec3 &spe, float a, float b, float c);
    ~Light();


    vec3 pos;// lighsource position in scene
    vec3 ambient; // ambient component
    vec3 diffuse;// diffuse component
    vec3 specular; //specular component
    float a; // abc params of light attenuation
    float b;
    float c;

};

#endif // LIGHT_H

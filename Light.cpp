
#include "Light.h"

//default params
Light::Light(){
    this->pos=vec3(0,0,0);
    this->ambient=vec3(0.1,0.1,0.1);
    this->diffuse=vec3(0.1,0.1,0.1);
    this->specular=vec3(0.1,0.1,0.1);
    this->a=  1;
    this->b=  1;
    this->c=  1;
}

Light::~Light(){
    delete &pos;
    delete &ambient;
    delete &diffuse;
    delete &specular;
}
Light::Light(vec3 & pos, vec3 & amb, vec3 & dif, vec3 & spe, float a, float b, float c){
    this->pos=pos;
    this->ambient=amb;
    this->diffuse=dif;
    this->specular=spe;
    this->a=  a;
    this->b=  b;
    this->c=  c;
}

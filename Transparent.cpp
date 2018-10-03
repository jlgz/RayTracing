#include "Transparent.h"

Transparent::Transparent(const vec3& transparency,const float idr,float dmax):Material()
{
    this->dmax = dmax;
    this->transparency = transparency;
    this->especular=vec3(1.0f)-transparency;// Ks=1-Kt
    this->idr=idr;
}

Transparent::~Transparent()
{}

bool Transparent::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    float nit=1.0f/this->idr;
    float cosf=dot(-1.0f*normalize(r_in.direction),rec.normal);
    float root=1.0f-nit*nit*(1.0f-cosf*cosf);
    if (root<0){
        color=vec3(0.0f);
        scattered = Ray(rec.p , rec.normal);//not important
    }
    else{
        vec3 result = nit*r_in.direction+rec.normal*(nit*cosf-sqrt(root));
        color=this->transparency;
        scattered = Ray(rec.p+result*EPSILON, result);
    }

    return true;
}

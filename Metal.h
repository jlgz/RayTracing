#ifndef METAL_H
#define METAL_H
#include "Material.h"

class Metal : public Material
{

public:
    float scPrecision; //presision of a scattered ray - used to ajust RandomInSphere()
    Metal(const vec3& color,const float scPrecision);
    virtual ~Metal();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

};

#endif // METAL_H

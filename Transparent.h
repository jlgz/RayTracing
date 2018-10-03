#ifndef TRANSPARENT_H
#define TRANSPARENT_H

#include "Material.h"
class Transparent : public Material
{

public:
    vec3 transparency; //transparency value
    float idr; // refraction index
    Transparent(const vec3& transparency,const float idr,float dmax);
    virtual ~Transparent();
    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const;

};
#endif // TRANSPARENT_H

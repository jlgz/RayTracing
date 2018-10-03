#include "Plane.h"
#include "math.h"
Plane::Plane(vec3 nor, vec3 p, Material *m) : Object(m)  {
    nor = normalize(nor);
    normal = nor;
    point =p;
}

bool Plane::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {
    float t;
    float divisor = (r.direction[0]*normal[0]+r.direction[1]*normal[1]+r.direction[2]*normal[2]);
    if(divisor != 0){
        t = -(normal[0]*(r.origin[0] - point[0] ) + normal[1]*(r.origin[1] - point[1] )+ normal[2]*(r.origin[2] - point[2] ))/ divisor;
        if (t<=0){return false;}
        rec.t = t;
        rec.p = r.pointAtParameter(t);
        rec.normal = normal;
        rec.mat_ptr = material;
        return true;
    }
    else
        return false;
}


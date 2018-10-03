#ifndef PLANE_H
#define PLANE_H
#include "Object.h"

class Plane: public Object  {
public:
        Plane(vec3 nor, vec3 p, Material *m);
        ~Plane() {}
        bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
private:
        // vector normal
        vec3 normal;
        // punt de pas
        vec3 point;

};


#endif // PLANE_H

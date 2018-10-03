#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Object.h"

class Triangle: public Object  {
public:
        Triangle(vec3 nv1, vec3 nv2, vec3 nv3, Material *m);
        ~Triangle() {}
        bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
private:
        vec3 v1;
        vec3 v2;
        vec3 v3;
        vec3 normal;

};
 //cross - producle vectorial

#endif // TRIANGLE_H

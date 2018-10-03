#ifndef CUBE_H
#define CUBE_H
#include "Object.h"

class Cube: public Object  {
public:
        Cube(vec3 v1, vec3 v2, Material *m);
        ~Cube() {}
        bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const;
private:
        // 2 vertices extremos del cubo
        vec3 v1;
        vec3 v2;

};
#endif // CUBE_H

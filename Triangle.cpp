#include "Triangle.h"
#define EPSILON 0.000001

Triangle::Triangle(vec3 nv1, vec3 nv2, vec3 nv3, Material *m) : Object(m)  {
    v1 = nv1;
    v2 = nv2;
    v3 = nv3;
    normal = normalize(cross(nv2 - nv1, nv3 - nv1));
}
//Möller–Trumbore intersection algorithm, for better performance
bool Triangle::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {
    if (dot(r.direction,this->normal)>=0.0f)
        return false;
    vec3 e1, e2;  //Edge1, Edge2
    vec3 P, Q, T;
    float det, inv_det, u, v;
    float t;

    e1 = v2-v1;
    e2 = v3-v1;
    P= cross(r.direction,e2);
    det = dot(e1,P);

    if(det > -EPSILON && det < EPSILON) return false;
    inv_det = 1.f / det;

    T = r.origin-v1;
    u = dot(T, P) * inv_det;
    if(u < 0.f || u > 1.f) return false;

    Q = cross(T, e1);
    v = dot(r.direction, Q) * inv_det;


    if(v < 0.f || u + v  > 1.f) return false;

    t = dot(e2, Q) * inv_det;

    if(t > EPSILON) { //ray intersection
        rec.t = t;
        rec.p = r.pointAtParameter(t);
        rec.normal= this->normal;
        rec.mat_ptr=this->material;
        return true;
      }
    return false;
}



/*
 * костыли-костылики...
 * LIBS += -lGL
LIBS +=-lglut32
LIBS += -LC:\Qt\Qt5.6.2\5.6\mingw49_32\lib
#define drand48() (((double)rand())/((double)RAND_MAX))
*/

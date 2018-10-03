#include "Material.h"



Material::Material():
    diffuse(0.8f), especular(1.0f), ambient(0.7f), exp_especular(200), alfa(0.1),dmax(0)
  {}

Material::~Material()
{}

vec3 Material::RandomInSphere() const {
    vec3 p;
    do {
        p = 2.0f*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    } while (glm::length(p) >=  1.0f);
    return p;
}


#include "Lambertian.h"

Lambertian::Lambertian(const vec3& color):Material()
{
    diffuse = color;
}

Lambertian::~Lambertian()
{}

bool Lambertian::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    vec3 target = rec.p + rec.normal + this->RandomInSphere();
    vec3 res=target-rec.p;
    scattered = Ray(rec.p+res*EPSILON, res);
    color = diffuse;
    return true;
}


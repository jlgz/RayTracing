#include "Metal.h"

Metal::Metal(const vec3& color, const float shineness):Material()
{
    diffuse = color;
    this->scPrecision = shineness;
}

Metal::~Metal()
{}

bool Metal::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const  {
    vec3 dir  = r_in.direction - 2.0f*dot(r_in.direction, rec.normal)*rec.normal + this->RandomInSphere()*this->scPrecision;
    scattered = Ray(rec.p+dir*EPSILON, dir);
    color = especular;
    return true;
}

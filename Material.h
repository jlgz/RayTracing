#ifndef MATERIAL_H
#define MATERIAL_H
#define EPSILON 0.001f //epsilon for point displacement to combat acne

#include "Ray.h"
#include "Hitable.h"

// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Material
{
public:

    Material();
    ~Material();

    virtual bool scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray& scattered) const = 0;

    vec3 diffuse;
    vec3 especular;
    vec3 ambient;
    int exp_especular;
    float alfa;
    float dmax;

protected:
    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H

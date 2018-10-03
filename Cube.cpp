#include "Cube.h"
#include "math.h"
Cube::Cube(vec3 v1, vec3 v2, Material *m) : Object(m)  {
    this->v1 = v1;
    this->v2 = v2;
}

bool Cube::hit(const Ray& r, float t_min, float t_max, HitInfo& rec) const {
    float t1=0,t2=0,t=0;
    int i,normal;
    float aux;
    vec3 v;
    vec3 normals[3] = {vec3(1,0,0),vec3(0,1,0),vec3(0,0,1)};
    vec3 mini = vec3(min(v1[0],v2[0]),min(v1[1],v2[1]),min(v1[2],v2[2]));
    vec3 maxi = vec3(max(v1[0],v2[0]),max(v1[1],v2[1]),max(v1[2],v2[2]));
    for(i = 0;i<3;i++){
        aux = (r.direction[0]*normals[i][0]+r.direction[1]*normals[i][1]+r.direction[2]*normals[i][2]);
        if(aux != 0){
            t1 = -(normals[i][0]*(r.origin[0] - v1[0] ) + normals[i][1]*(r.origin[1] - v1[1] )+ normals[i][2]*(r.origin[2] - v1[2] ))/ aux;
            t2 = -(normals[i][0]*(r.origin[0] - v2[0] ) + normals[i][1]*(r.origin[1] - v2[1] )+ normals[i][2]*(r.origin[2] - v2[2] ))/ aux;
            if(t1 <= 0 && t2 <= 0){continue;}
            else if(t1 <= 0 && t2 > 0){aux = t2;}
            else if(t2 <= 0 && t1 > 0){aux = t1;}
            else{aux = min(t1,t2);}
            v = r.pointAtParameter(aux);
            if((i != 0  && (v[0]> maxi[0] || v[0]<mini[0])) || (i != 1  && (v[1]> maxi[1] || v[1]<mini[1])) || (i != 2  && (v[2]> maxi[2] || v[2]<mini[2])))
                continue;
            else if (t == 0 || t > aux){
                normal = i;
                t = aux;
                if (aux == t2){
                    v = v2 - v1;
                }
                else{
                    v = v1 - v2;
                }
            }
        }
    }
    if(t != 0){
        if (normals[normal][0]* v[0] + normals[normal][1]* v[1]+ normals[normal][2]* v[2]< 0)
            normals[normal] *= -1;
        rec.t = t;
        rec.p = r.pointAtParameter(t);
        rec.normal = normals[normal];
        rec.mat_ptr = material;
        return true;
    }
    else
        return false;
}


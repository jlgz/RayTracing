#include "Scene.h"
#include "math.h"

#define MAX_DEPH 10 //max depth of ComputeColor recursion
#define MAX_TRANSP 5 //max depth of ComputeColor recursion of transparency component

#define MAXOBJECTS 20 // max objects for random scene

#define SKYCOLOR vec3(0.0f,0.75f,1.0f)/1.5f //VOID color

#define MAXPX 1000 //final image width in pixels
#define MAXPY 1000 //final image height in pixels
Scene::Scene()
{
    // creacio de la camera
    vec3 lookfrom(30, 5.5f, 50);
    vec3 lookat(5, 0, -1);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    int pixelsX = MAXPX;
    int pixelsY = MAXPY;
    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);
    this->ambientLight = vec3(0.01,0.01,0.01);
   // TODO: Cal crear els objectes de l'escena
    vec3 *s = new vec3(2.0f,8.0f,10.0f);
    vec3 *h = new vec3(0.5,0.5,0.5);
    vec3 *k = new vec3(0.4,0.4,0.4);
    vec3 *j = new vec3(1.0f,1.0f,1.0f);
    this->lights.push_back(new Light(*s,*k,*h,*j,0.01f,0.0f,0.5f));
    // TODO: Cal afegir llums a l'escena (Fase 2)
    //RandomScene(); // random objects
    //DemoScene1(); // 4 spheres 2 mirror planes - Use it for dmax tests
    CubeTest();


}

Scene::~Scene()
{
    for(unsigned int i = 0; i < objects.size(); ++i){
        if(objects[i]){
            if (dynamic_cast<Sphere*>(objects[i]))
                    delete (Sphere *)(objects[i]);
            else if (dynamic_cast<Triangle*>(objects[i]))
                    delete (Triangle *)(objects[i]);
            else if (dynamic_cast<Cube*>(objects[i]))
                    delete (Cube *)(objects[i]);
            else if (dynamic_cast<Plane*>(objects[i]))
                    delete (Plane *)(objects[i]);
            else if (dynamic_cast<BoundaryObject*>(objects[i]))
                    delete (BoundaryObject *)(objects[i]);
        }
    }
    for(unsigned int i = 0; i < lights.size(); ++i){
        if(lights[i]){
                delete lights[i];
        }
    }
    delete cam;
}

// TODO: Metode que genera una escena random de numObjects de tipus esfera, a diferents posicions,
// amb diferents radis i diferents materials. S'usa drand48 per generar numeros random

void Scene::RandomScene() {


    std::srand (MAXOBJECTS);
    vec3 lookfrom(30, 5.5f, 50);
    vec3 lookat(5, 0, -1);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    int pixelsX = MAXPX;
    int pixelsY = MAXPY;
    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);
    objects.push_back(new Sphere(vec3(0,-1,-1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5))));
    Metal *mTest = new Metal(vec3(0.9, 0.9, 0.9),0.0f);
    mTest->exp_especular=10;
    mTest->diffuse=vec3(0.7,0.6,0.0);
    mTest->ambient=vec3(0.2);
    mTest->especular=vec3(1.0f);
    objects.push_back(new Plane(vec3(0,1,0.0),vec3(-1,-3,-1),mTest));
    for (int i=0;i<MAXOBJECTS;i++){
        int mtype =(int)(drand48()*3);
        switch(mtype){
            case 0:{
                Metal *mTest1 = new Metal(vec3(drand48(), drand48(), drand48()),0.0f);
                mTest1->exp_especular=10+drand48()*70;
                mTest1->diffuse=vec3(drand48(),drand48(),drand48());
                mTest1->ambient=vec3(drand48()/10.0f);
                mTest1->especular=vec3(1.0f-drand48()/20.0f);
                objects.push_back(new Sphere(vec3(-10.0f+drand48()*20.0f,-2.0f+drand48()*3.0f,-10.0f+drand48()*20.0f), drand48(), mTest1));
                break;}
        case 1:{
                Lambertian *s1 = new Lambertian(vec3(drand48(), drand48(), drand48()));
                s1->exp_especular=10+drand48()*70;
                s1->ambient=vec3(drand48()/10.0f);
                s1->especular=vec3(1.0f-drand48()/20.0f);
                objects.push_back(new Sphere(vec3(-10.0f+drand48()*20.0f,-2.0f+drand48()*3.0f,-10.0f+drand48()*20.0f), drand48(), s1));
                break;}
        case 2:{
                Transparent *tr = new Transparent(vec3((float)drand48(), (float)drand48(), (float)drand48()),1.0f+1.5f*(float)drand48(),1.0f+1.5f*(float)drand48());
                tr->exp_especular=10+drand48()*70;
                tr->ambient=vec3(drand48()/10.0f);
                tr->especular=vec3(1.0f-drand48()/5.0f);
                tr->diffuse=vec3(drand48(), drand48(), drand48());
                objects.push_back(new Sphere(vec3(-10.0f+drand48()*20.0f,-2.0f+drand48()*3.0f,-10.0f+drand48()*20.0f), drand48(), tr));
                break;}

        }


        //objects.push_back(new BoundaryObject("../F_09-master/resources/peo1K.obj", mTest));





    }
}

/*
** TODO: Metode que testeja la interseccio contra tots els objectes de l'escena (Fase 1)
**
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/
bool Scene::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {
    HitInfo infotmp;
    HitInfo infotmp2;
    vec3 dsv;
    Ray rtmp;
    float min = 0;
    bool bf=false,b;
    for(int i = 0; i< objects.size();i++){
           b = objects[i]->hit(raig,t_min,t_max,infotmp);
           if(b){
               bf =true;
               if(min == 0 || infotmp.t< min){
                    min = infotmp.t;
                    info = infotmp;
                    if(infotmp.mat_ptr->dmax != 0){ //computing ds to use it in transparent shadows
                        rtmp = Ray(infotmp.p+raig.direction*EPSILON,raig.direction);
                        if(objects[i]->hit(rtmp,t_min,t_max,infotmp2)){
                            dsv = infotmp2.p - info.p;
                            info.ds = sqrt(dot(dsv,dsv));
                        }
                        else{info.ds = 0;}
                    }
               }
           }
    }
    return bf;
    // TODO: Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode hit per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Cada vegada que s'intersecta un objecte s'ha d'actualitzar el HitInfo del raig,
    // pero no en aquesta funcio.

}

/*
** TODO: Funcio ComputeColor es la funcio recursiva del RayTracing.
** A modificar en la Fase 2 de l'enunciat per incloure Blinn-Phong  i ombres
** A modificar en la Fase 2 per a tractar reflexions
**
*/


vec3 Scene::ComputeColor (Ray &ray, int depth ) {

    vec3 color;

    /* TODO: Canviar aquesta assignacio pel color basat amb la il.luminacio basada amb Phong-Blinn segons
     * el material de l'objecte i les llums per la fase 2 de la practica
     * En aquestesta fase 2,  cal fer que tambe es tinguin en compte els rebots de les reflexions.

       Inicialment s'ha posat la direccio del raig per tenir un color diferents per a cada pixel pero
       hitInfo ha d'anar tenint el color actualitzat segons els rebots.
    */
     //color = 0.5f*vec3(ray.direction.x+1, ray.direction.y+1, ray.direction.z+1);
     HitInfo info;
     vec3 colorn(0.0,0.0,0.0);
     if(this->hit(ray,0.0f,1000.0f,info)){
        color = this->blinnPhong(info.p,info.normal,info.mat_ptr,true);
        Ray sc= Ray(); //scattered ray
        vec3 colorsc;// scatter method modifies this color if  we have transparency
        info.mat_ptr->scatter(ray,info,colorsc,sc); //scattered ray calculation
        if(depth >= MAX_DEPH )
            return color;
        return color +ComputeColor(sc,depth+1)*colorsc ; // Ipa+Ksa*Ipb  on pa - punt de hit inicial, pb - punt de hit secundari Ksa - especular del punt a
     }
    else{
        color =SKYCOLOR; //(1-ray.direction.y-1)*vec3(1.0, 1.0, 1.0)+ (ray.direction.y+1)*vec3(0.5,0.7,1.0);
        return color;
     }
     /*Ray sc= Ray();
     //const HitInfo infoc = info;
     vec3 colorsc=info.mat_ptr->diffuse;
     sc.origin=info.p+info.normal*EPSILON;
     sc.direction=info.normal;
     //info.mat_ptr->scatter(ray,info,colorsc,sc); //Crashes process with segmentation fault error - f-ing "const"

     if(depth >= MAX_DEPH )
         return color;
     return color + ComputeColor(sc,depth+1)*colorsc ;*/
}
vec3 Scene::blinnPhong(vec3 point,vec3 normal,const Material *material,bool ombra) {
    float d,s=1;
    HitInfo info;
    Light * l;
    vec3 L,V,H;
    vec3 i = this->ambientLight * material->ambient;
    for(int j = 0; j< this->lights.size();j++  ){
        l = this->lights[j];
        L = l->pos - point;
        d = sqrt(dot(L,L));
        L /= d;
        if(ombra){
           Ray r(point+(EPSILON)*L,L);
           if(this->hit(r,0.0f,1000.0f,info)){
                if(info.mat_ptr->dmax == 0){s = 0;}
                else if(info.ds <info.mat_ptr->dmax){s= 1 - (1.0f/info.mat_ptr->dmax)*info.ds;}
                else{s = 0;}
           }
        }
        V =normalize(this->cam->origin - point);
        H = normalize(L+V);
        i += 1.0f/(d*d*l->a + d*l->b + l->c) * ((l->diffuse*material->diffuse* glm::max(dot(L , normal),0.0f) +l->specular*material->especular*float(pow(glm::max(dot(normal,H),0.0f),material->exp_especular)))*s +l->ambient * material->ambient);
    }
    return i;
}
void Scene::setAmbientLight(vec3 & ambient) {
    this->ambientLight = ambient;
}

/*
 *Predetermined set of objects to show a scene (4 spheres and 2 mirror planes)
*/
void Scene::DemoScene1(){
    //valuesof camera

    vec3 lookfrom(1, 2.5f, 15);
    vec3 lookat(0, 0, -1);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    int pixelsX = MAXPX;
    int pixelsY = MAXPY;
    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);

    //Melat material test
    Metal *mTest = new Metal(vec3(0.5, 0.6, 0.4),0.0f);
    mTest->exp_especular=10;
    mTest->diffuse=vec3(0.7,0.6,0.5);
    mTest->ambient=vec3(0.2);
    mTest->especular=vec3(1.0f);
    Metal *mTest2 = new Metal(vec3(0.4, 0, 1.0f),0.0f);
    mTest2->exp_especular=20;
    mTest2->diffuse=vec3(0.1,0.3,0.8);
    mTest2->ambient=vec3(0.1);
    mTest2->especular=vec3(1.0f);
    //s1 material
    Lambertian *s1 = new Lambertian(vec3(1,1,1));
    s1->exp_especular=10;
    s1->ambient=vec3(0.2f);
    s1->especular=vec3(0.1f);
    //s2 mat
    Lambertian *s2 = new Lambertian(vec3(0.8, 0.8, 0)/2.0f);
    s2->exp_especular=10;
    s2->ambient=vec3(0.2f);
    s2->especular=vec3(0.1f);

    //transparent mat
    Transparent *tr = new Transparent(vec3(1.0f),1.2f,1.2f);
    tr->exp_especular=10;
    tr->ambient=vec3(0.0f);
    tr->diffuse=vec3(0.9,0.9,0.9);
    tr->especular=vec3(0.9,0.9,0.9);

    objects.push_back(new Sphere(vec3(0,0,-1), 0.5, mTest));// metal sphere 1
    objects.push_back(new Sphere(vec3(0,0,1), 0.5, s1)); // lambertian sphere
    objects.push_back(new Sphere(vec3(1,0,-1), 0.5, mTest2));// metal sphere 2

    objects.push_back(new Sphere(vec3(1.0f,0.0f,1.0f), 0.5, tr));//transparent sphere
    objects.push_back(new Plane(vec3(0,1,0.0),vec3(-1,-1,-1),mTest));
    objects.push_back(new Plane(vec3(0,0,1.0),vec3(-1,-1,-5),mTest2));

    }
// testing cubes
void Scene::CubeTest(){
    vec3 lookfrom(8, 4.5f, -15);
    vec3 lookat(0, 0, -1);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    int pixelsX = MAXPX;
    int pixelsY = MAXPY;
    cam = new Camera(lookfrom, lookat, vec3(0,1,0), 20, pixelsX, pixelsY, aperture, dist_to_focus);

    Metal *mTest = new Metal(vec3(0.9, 0.9, 0.9),0.0f);
    mTest->exp_especular=10;
    mTest->diffuse=vec3(0.8,0.1,0.1);
    mTest->ambient=vec3(0.2);
    mTest->especular=vec3(1.0f);
    Metal *mTest2 = new Metal(vec3(0.9, 1, 1.0f),0.0f);
    mTest2->exp_especular=20;
    mTest2->diffuse=vec3(0.4, 0, 1.0f);
    mTest2->ambient=vec3(0.1);
    mTest2->especular=vec3(1.0f);
    //s1 material
    Lambertian *s1 = new Lambertian(vec3(1,1,1));
    s1->exp_especular=10;
    s1->ambient=vec3(0.2f);
    s1->especular=vec3(0.1f);
    //s2 mat
    Lambertian *s2 = new Lambertian(vec3(0.8, 0.8, 0)/2.0f);
    s2->exp_especular=10;
    s2->ambient=vec3(0.2f);
    s2->especular=vec3(0.1f);

    //transparent mat
    Transparent *tr = new Transparent(vec3(1.0f),1.2f,1.2f);
    tr->exp_especular=10;
    tr->ambient=vec3(0.0f);
    tr->diffuse=vec3(0.9,0.9,0.9);
    tr->especular=vec3(0.9,0.9,0.9);

    objects.push_back(new Cube(vec3(-1,0,-1), vec3(1,1,1), mTest));// metal sphere 1
    objects.push_back(new Cube(vec3(-0.5,1,-2), vec3(0.5,2,-1.0f), tr));
    objects.push_back(new Sphere(vec3(0,0,-2), 0.5, mTest));
    objects.push_back(new Triangle(vec3(-1,0,-4),vec3(-1,3,-1),vec3(-1,0,1), mTest));
    objects.push_back(new Sphere(vec3(0,1,2), 0.5, s1)); // lambertian sphere
    objects.push_back(new Sphere(vec3(1.5f,-0.5f,-1.5f), 0.5, mTest2));// metal sphere 2

    objects.push_back(new Sphere(vec3(1.5f,0.5f,0.5f), 0.5, tr));//transparent sphere

    objects.push_back(new Plane(vec3(0,1,0.0),vec3(-1,-3,-1),mTest2)); // reflective plane
}

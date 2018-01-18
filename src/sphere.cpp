#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    // Use the equations from Pre-Lab 
    vec3 u, w, v, center;
    w = ray.endpoint;
    u = ray.direction;
    center = this->center;
    v = w - center;
    
    
    double a, b, c;
    a = dot(u, u);
    b = dot(u, v);
    c = dot(v, v) - r*r;
    
    double disc;
    disc = (b * b) - c;
    
    if(disc > 0) {
        double t1, t2;
        t1 = -b - pow(disc, 1/2);
        t2 = -b + pow(disc, 1/2);
        
        if(t1 > 0) {
            Hit hit1 = {this, t1, true};
            hits.push_back(hit1);
        }
        if(t2 > 0) {
            Hit hit2 = {this, t2, true};
            hits.push_back(hit2);
        }
    }
    
    //return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    
    // TODO: set the normal
    
    return normal;
}

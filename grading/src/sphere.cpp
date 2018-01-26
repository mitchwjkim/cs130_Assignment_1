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
    double r = this->radius;
    
    double a, b, c;
    a = 1;
    b = 2 * dot(u, v);
    c = dot(v, v) - r*r;
    
    double disc = b * b - 4 * a * c;
    
    if(disc > 0) {
        Hit hit1, hit2;
        if(disc == 0) {
            double t = (-b / (2 * a));
            if(t > 0) {
                hit1 = {this, 0, false};
                hit2 = {this, t, true};
                hits.push_back(hit1);
                hits.push_back(hit2);
            }
        }
        else {
            double t1, t2;
            t1 = (-b - pow(disc, 0.5)) / (2 * a);
            t2 = (-b + pow(disc, 0.5)) / (2 * a);
            
            if(t1 > 0) {
                hit1 = {this, t1, false};
                hits.push_back(hit1);
            }
            if(t2 > 0) {
                hit2 = {this, t2, true};
                hits.push_back(hit2);
            }
        }
        return true;
    }
    
    return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    
    // TODO: set the normal
    normal = (point - this->center).normalized();


    return normal;
}
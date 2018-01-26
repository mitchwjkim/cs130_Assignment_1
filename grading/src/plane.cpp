#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    // If perpendicular than = 0
    // Check if != 0

    vec3 u, w, normal, x1;
    w = ray.endpoint;
    u = ray.direction;
    normal = this->normal;
    x1 = this->x1;

    double intersect = dot(normal, u);

    double t = (dot(normal, (x1 - w)) / intersect);
    Hit t1 = {this, t, true};

    if(intersect == 0) {
        t1 = {this, 0, true};
        hits.push_back(t1);
        return true;
    }
    else {
        if (t > 0) {
            hits.push_back(t1);
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}

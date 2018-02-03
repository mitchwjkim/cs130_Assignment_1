#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
    vec3 color;
    // TODO: determine the color
    // Phong = Ambient + Diffuse + Specular

    // Ambient
    // world.ambient_color ; world.ambient_intensity ; color_ambient
    color = world.ambient_color * world.ambient_intensity * this->color_ambient;

    vec3 l, light_color, n, r, c;
    n = same_side_normal;

    Ray r_shadow;

    for(uint i = 0; i < world.lights.size(); i++) {
        l = world.lights.at(i)->position - intersection_point;
        double dist = (intersection_point - world.lights.at(i)->position).magnitude_squared();

        if(world.enable_shadows) {
            Hit hits;
            Ray r_shadow(intersection_point, l.normalized());
            if(world.Closest_Intersection(r_shadow, hits)){
                if(sqrt(dist) > hits.t) {continue;}
            }
        }

        light_color = world.lights.at(i)->Emitted_Light(r_shadow) / dist;

        double prod_ln = dot(n, l.normalized());

        color += std::max(0.0, prod_ln) * color_diffuse * light_color;

        r = 2*dot(l.normalized(),n)*n - l.normalized();
        // c = world.camera.position - intersection_point;
        c = ray.direction.normalized() * -1.0;

        double prod_rc = dot(r, c.normalized());
        double spec_intensity = pow(std::max(0.0, prod_rc),specular_power);
        color += spec_intensity * color_specular * light_color;
    }
        

    return color;
}
#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{
    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;
    if(!world.disable_fresnel_refraction)
    {
        //TODO (Test 27+): Compute the refraction_color:
        // - Check if it is total internal reflection. 
        //      If so update the reflectance_ratio for total internal refraction
        //
        //      else, follow the instructions below
        //
        //        (Test 28+): Update the reflectance_ratio 
        //
        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        //
        vec3 n;
        double nr, ni;

        if(!is_exiting) {
            nr = refractive_index;
            ni = REFRACTIVE_INDICES::AIR;
            n = same_side_normal;
        }
        else {
            ni = refractive_index;
            nr = REFRACTIVE_INDICES::AIR;
            n = -1.0 * same_side_normal;
        }

        double n_frac = ni / nr;
        double cos_i = (dot(-1.0 * ray.direction, n) /*/ ray.direction.magnitude()*/);
        double cos_r = sqrt(1.0 - n_frac * n_frac * (1.0 - pow(cos_i, 2.0)));

        if((1 - n_frac * n_frac * (1.0 - pow(cos_i, 2.0))) < 0.0) {
            reflectance_ratio = 1.0;
            refraction_color = vec3(0.0, 0.0, 0.0);
        }
        else { 
            vec3 t = n_frac * (ray.direction.normalized() - dot(ray.direction.normalized(), n) * n) - (cos_r * n);

            Ray r_refracted(intersection_point, t);

            refraction_color = shader->world.Cast_Ray(r_refracted, recursion_depth);

            double r_parallel = pow(((nr*cos_i - ni*cos_r)/(nr*cos_i + ni*cos_r)),2.0);
            double r_perp = pow(((ni*cos_i - nr*cos_r)/(ni*cos_i + nr*cos_r)),2.0);

            double k = (r_parallel + r_perp) / 2.0;
            reflectance_ratio = k;
        }
    }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray andd get color
        //

        vec3 r = ray.direction.normalized() - 2.0 * dot(ray.direction.normalized(), same_side_normal) * same_side_normal;

        Ray r_reflected(intersection_point, r);
        //r_reflected.endpoint = r_reflected.Point(0.0001);

        reflection_color = shader->world.Cast_Ray(r_reflected, recursion_depth);
    }

    Enforce_Refractance_Ratio(reflectance_ratio);
    vec3 color;
    // TODO: (Test 26+) Compute final 'color' by blending reflection_color and refraction_color using 
    //                  reflectance_ratio
    //

    color = reflectance_ratio * reflection_color + (1.0 - reflectance_ratio) * refraction_color;

    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}


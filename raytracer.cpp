/*
** EPITECH PROJECT, 2024
** mirror_repo [WSL: kali-linux]
** File description:
** raytracer.cpp
*/

#include "raytracer.hpp"
#include <cmath>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <limits>
#include <stdexcept>

void write_color(Math::Vector3D vector)
{
    std::cout << vector._x << " " << vector._y << " " << vector._z << std::endl;
    return;
}

int main()
{
    double image_width = 400;
    double image_height = 400;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    Math::Raytracer::Camera cam;
    Math::Raytracer::Sphere sphere1(Math::Point3D(0.0, 0.0, -1.0), 0.5);
    // RayTracer::Sphere sphere2(Math::Point3D(0.0, 0.0, -0.7), 0.5);
    // RayTracer::Sphere sphere2(Math::Point3D(0.0, 0.0, -0.8), 0.5);

        for (double y = 0; y < image_width; y++) {
            for (double x = 0; x < image_width; x++) {
            double u = x / (image_width - 1);
            double v = y / (image_height - 1);

            Math::Ray ray = cam.ray(u, v);
            
            Math::Vector3D pixel_color(0, 0, 0);

            double t = 0;
            if (sphere1.intersect(ray, t)) {
                pixel_color = Math::Vector3D(255, 0, 0);
            }
            // if (sphere2.hits(ray)) {
            //     pixel_color = Math::Vector3D(0, 0, 255);
            // }
            write_color(pixel_color);
        }
    }

    return 0;
}

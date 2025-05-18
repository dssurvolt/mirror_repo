/*
** EPITECH PROJECT, 2024
** mirror_repo [WSL: kali-linux]
** File description:
** raytracer.hpp
*/

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_
#include <cmath>
#include <iostream>
#include <initializer_list>
namespace Math{
    class Vector2D {
    public:
        double _x;
        double _y;

        Vector2D(double x = 0, double y = 0) : _x(x), _y(y) {}

        double length() const {
            return sqrt(_x * _x + _y * _y);
        }

        double dot(const Vector2D& other) const {
            return _x * other._x + _y * other._y;
        }

        Vector2D operator+(const Vector2D& other) const {
            return Vector2D(_x + other._x, _y + other._y);
        }

        Vector2D operator+=(const Vector2D& other) const {
            return Vector2D(_x + other._x, _y + other._y);
        }

        Vector2D operator-(const Vector2D& other) const {
            return Vector2D(_x - other._x, _y - other._y);
        }

        Vector2D operator-=(const Vector2D& other) const {
            return Vector2D(_x - other._x, _y - other._y);
        }

        Vector2D operator*(const Vector2D& other) const {
            return Vector2D(_x * other._x, _y * other._y);
        }

        Vector2D operator*(double l) const {
            return Vector2D(_x * l, _y * l);
        }

        Vector2D operator*=(const Vector2D& other) const {
            return Vector2D(_x * other._x, _y * other._y);
        }

        Vector2D operator*=(double l) const {
            return Vector2D(_x * l, _y * l);
        }

        Vector2D operator/(const Vector2D& other) const {
            return Vector2D(_x / other._x, _y / other._y);
        }

        Vector2D operator/(double l) const {
            return Vector2D(_x / l, _y / l);
        }

        Vector2D operator/=(const Vector2D& other) const {
            return Vector2D(_x / other._x, _y / other._y);
        }

        Vector2D operator/=(double l) const {
            return Vector2D(_x / l, _y / l);
        }
    };

    class Vector3D {
    public:
        double _x;
        double _y;
        double _z;

        Vector3D(double x = 0, double y = 0, double z = 0) : _x(x), _y(y), _z(z) {}

        double length() const {
            return sqrt(_x * _x + _y * _y + _z * _z);
        }

        double dot(const Vector3D& other) const {
            return _x * other._x + _y * other._y + _z * other._z;
        }

        Vector3D operator+(const Vector3D& other) const {
            return Vector3D(_x + other._x, _y + other._y, _z + other._z);
        }

        Vector3D operator+=(const Vector3D& other) const {
            return Vector3D(_x + other._x, _y + other._y, _z + other._z);
        }

        Vector3D operator-(const Vector3D& other) const {
            return Vector3D(_x - other._x, _y - other._y, _z - other._z);
        }

        Vector3D operator-=(const Vector3D& other) const {
            return Vector3D(_x - other._x, _y - other._y, _z - other._z);
        }

        Vector3D operator*(const Vector3D& other) const {
            return Vector3D(_x * other._x, _y * other._y, _z * other._z);
        }

        Vector3D operator*(double l) const {
            return Vector3D(_x * l, _y * l, _z * l);
        }

        Vector3D operator*=(const Vector3D& other) const {
            return Vector3D(_x * other._x, _y * other._y, _z * other._z);
        }

        Vector3D operator*=(double l) const {
            return Vector3D(_x * l, _y * l, _z * l);
        }

        Vector3D operator/(const Vector3D& other) const {
            return Vector3D(_x / other._x, _y / other._y, _z / other._z);
        }

        Vector3D operator/(double l) const {
            return Vector3D(_x / l, _y / l, _z / l);
        }

        Vector3D operator/=(const Vector3D& other) const {
            return Vector3D(_x / other._x, _y / other._y, _z / other._z);
        }

        Vector3D operator/=(double l) const {
            return Vector3D(_x / l, _y / l, _z / l);
        }
    };

    class Point3D {
    public:
        double _x;
        double _y;
        double _z;

        Point3D(double x = 0, double y = 0, double z = 0) : _x(x), _y(y), _z(z) {}

        Point3D operator+(const Vector3D& other) const {
            return Point3D(_x + other._x, _y + other._y, _z + other._z);
        }

        Point3D operator-(const Vector3D& other) const {
            return Point3D(_x - other._x, _y - other._y, _z - other._z);
        }
        Point3D operator+=(const Vector3D& other) const {
            return Point3D(_x + other._x, _y + other._y, _z + other._z);
        }
        Point3D operator-=(const Vector3D& other) const {
            return Point3D(_x - other._x, _y - other._y, _z - other._z);
        }
        Point3D operator*(const Vector3D& other) const {
            return Point3D(_x * other._x, _y * other._y, _z * other._z);
        }
        Point3D operator*(double l) const {
            return Point3D(_x * l, _y * l, _z * l);
        }
        Point3D operator*=(const Vector3D& other) const {
            return Point3D(_x * other._x, _y * other._y, _z * other._z);
        }
        Point3D operator*=(double l) const {
            return Point3D(_x * l, _y * l, _z * l);
        }
        Point3D operator/(const Vector3D& other) const {
            return Point3D(_x / other._x, _y / other._y, _z / other._z);
        }
        Point3D operator/(double l) const {
            return Point3D(_x / l, _y / l, _z / l);
        }
        Point3D operator/=(const Vector3D& other) const {
            return Point3D(_x / other._x, _y / other._y, _z / other._z);
        }
        Point3D operator/=(double l) const {
            return Point3D(_x / l, _y / l, _z / l);
        }
        double distance(const Point3D& other) const {
            return sqrt((_x - other._x) * (_x - other._x) + (_y - other._y) * (_y - other._y) + (_z - other._z) * (_z - other._z));
        }
    };

    template <size_t N>
    class Vector {
    public:
        double _data[N];

        Vector() {
            for (size_t i = 0; i < N; ++i) {
                _data[i] = 0;
            }
        }

        Vector(const std::initializer_list<double>& values) {
            size_t i = 0;
            for (auto val : values) {
                if (i < N) {
                    _data[i++] = val;
                }
            }
            for (; i < N; ++i) {
                _data[i] = 0;
            }
        }

        double length() const {
            double sum = 0;
            for (size_t i = 0; i < N; ++i) {
                sum += _data[i] * _data[i];
            }
            return sqrt(sum);
        }

        double dot(const Vector<N>& other) const {
            double result = 0;
            for (size_t i = 0; i < N; ++i) {
                result += _data[i] * other._data[i];
            }
            return result;
        }

        Vector<N> operator+(const Vector<N>& other) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                result._data[i] = _data[i] + other._data[i];
            }
            return result;
        }

        Vector<N>& operator+=(const Vector<N>& other) {
            for (size_t i = 0; i < N; ++i) {
                _data[i] += other._data[i];
            }
            return *this;
        }

        Vector<N> operator-(const Vector<N>& other) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                result._data[i] = _data[i] - other._data[i];
            }
            return result;
        }

        Vector<N>& operator-=(const Vector<N>& other) {
            for (size_t i = 0; i < N; ++i) {
                _data[i] -= other._data[i];
            }
            return *this;
        }

        Vector<N> operator*(double scalar) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                result._data[i] = _data[i] * scalar;
            }
            return result;
        }

        Vector<N>& operator*=(double scalar) {
            for (size_t i = 0; i < N; ++i) {
                _data[i] *= scalar;
            }
            return *this;
        }

        Vector<N> operator/(double scalar) const {
            Vector<N> result;
            for (size_t i = 0; i < N; ++i) {
                result._data[i] = _data[i] / scalar;
            }
            return result;
        }

        Vector<N>& operator/=(double scalar) {
            for (size_t i = 0; i < N; ++i) {
                _data[i] /= scalar;
            }
            return *this;
        }

        double& operator[](size_t index) {
            return _data[index];
        }

        const double& operator[](size_t index) const {
            return _data[index];
        }
    };

    class Ray {
    public:
        Point3D _origin;
        Vector3D _direction;

        Ray(const Point3D& origin, const Vector3D& direction) : _origin(origin), _direction(direction) {}

        Point3D getPoint(double t) const {
            return Point3D(_origin._x + t * _direction._x, _origin._y + t * _direction._y, _origin._z + t * _direction._z);
        }
    };

    namespace Raytracer {
        class Sphere {
        public:
            Point3D _center;
            double _radius;
 
            Sphere(const Point3D& center, double radius) : _center(center), _radius(radius) {}

            bool intersect(const Ray& ray, double& t) const {
                Vector3D oc = Vector3D(ray._origin._x - _center._x, ray._origin._y - _center._y, ray._origin._z - _center._z);
                double a = ray._direction.length() * ray._direction.length();
                double b = 2.0 * oc.dot(ray._direction);
                double c = oc.length() * oc.length() - _radius * _radius;
                double discriminant = b * b - 4 * a * c;
                if (discriminant < 0) {
                    return false;
                } else {
                    t = (-b - sqrt(discriminant)) / (2.0 * a);
                    return true;
                }
            }
        };

        class Rectangle3D {
            public:
            Point3D _origin;
            Vector3D _bottomSide;
            Vector3D _leftSide;

            Rectangle3D() : _origin(Point3D(0, 0, 0)), _bottomSide(Vector3D(1, 0, 0)), _leftSide(Vector3D(0, 1, 0)) {}
            Rectangle3D(const Point3D& origin, const Vector3D& bottomSide, const Vector3D& leftSide) : _origin(origin), _bottomSide(bottomSide), _leftSide(leftSide) {}
            Point3D pointAt(double u, double v) const {
                return Point3D(_origin._x + u * _bottomSide._x + v * _leftSide._x,
                               _origin._y + u * _bottomSide._y + v * _leftSide._y,
                               _origin._z + u * _bottomSide._z + v * _leftSide._z);
            }
        };

        class Camera {
            Point3D _origin = Point3D(0, 0, 0);
            Rectangle3D _screen;

            public:
            Camera() {
                _origin = Point3D(0, 0, 0);
            }
            Camera(double x, double y, double z) {
                _origin = Point3D(x, y, z);
            }

            Ray ray(double x, double y) {
                auto point = _screen.pointAt(x, y);
                Vector3D direction(point._x - _origin._x, point._y - _origin._y, point._z - _origin._z);
                return Ray(_origin, direction);
            }
        };
    }
}

#endif /* !RAYTRACER_HPP_ */
#pragma once
#include <array>
#include "helpers.h"
namespace spacely {
    using mat3x3 = std::array<std::array<double, 3>, 3>;
    class Vec3d {
        public:
            double e[3];

            Vec3d();
            Vec3d(double e0, double e1, double e2);
            
            double x() const;
            double y() const;
            double z() const;

            Vec3d operator-() const;
            double operator[](int i) const;
            double& operator[](int i);

            Vec3d& operator+=(const Vec3d& v);
            Vec3d& operator-=(const Vec3d& v);

            Vec3d& operator*=(double t);
            Vec3d& operator*=(const Vec3d& v);

            Vec3d& operator/=(double t);
            Vec3d& operator/=(const Vec3d& v) ;
            
            double length() const ;
            static Vec3d min(const Vec3d& a, const Vec3d& b);
            static Vec3d max(const Vec3d& a, const Vec3d& b);
            double length_squared() const;
            bool near_zero() const;


            Vec3d operator+(const Vec3d& v) const;
            Vec3d operator-(const Vec3d& v) const;

            Vec3d operator*(const Vec3d& v) const;
            Vec3d operator*(double t) const;

            Vec3d operator/(double t) const;
            Vec3d operator/(const Vec3d& v) const;

            static double dot(const Vec3d& u, const Vec3d& v);
            static double distance(const Vec3d& u, const Vec3d& v);
            static Vec3d cross(const Vec3d& u, const Vec3d& v);
            static Vec3d unit_vector(const Vec3d& v);
            static mat3x3 mat3x3_identity();
            static double mat3x3_det(const mat3x3& m);
            static mat3x3 mat3x3_inverse(const mat3x3& m);
            static mat3x3 mat3x3_mult(const mat3x3& left, const mat3x3& right);
            static Vec3d  mat3x3_times(const mat3x3& left, const Vec3d& right);
            static mat3x3 mat3x3_times(const mat3x3& left, const mat3x3& right);
            static mat3x3 mat3x3_transpose(const mat3x3& m);
    };
    
}

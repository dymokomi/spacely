#include "vec3d.h"
#include <cmath>
#include <limits>
namespace spacely {
    Vec3d::Vec3d() : e{0,0,0} {}
    Vec3d::Vec3d(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double Vec3d::x() const { return e[0]; }
    double Vec3d::y() const { return e[1]; }
    double Vec3d::z() const { return e[2]; }

    Vec3d Vec3d::operator-() const { return Vec3d(-e[0], -e[1], -e[2]); }
    double Vec3d::operator[](int i) const { return e[i]; }
    double& Vec3d::operator[](int i) { return e[i]; }

    Vec3d& Vec3d::operator+=(const Vec3d& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    Vec3d& Vec3d::operator-=(const Vec3d& v) {
        e[0] -= v.e[0];
        e[1] -= v.e[1];
        e[2] -= v.e[2];
        return *this;
        }

    Vec3d& Vec3d::operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
        }

    Vec3d& Vec3d::operator/=(double t) {
        return *this *= 1/t;
    }
    Vec3d& Vec3d::operator/=(const Vec3d& v) {
        e[0] /= v.e[0];
        e[1] /= v.e[1];
        e[2] /= v.e[2];
        return *this;
    }

    Vec3d Vec3d::operator+(const Vec3d& v) const {
        return Vec3d(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
    }

    Vec3d Vec3d::operator-(const Vec3d& v) const {
        return Vec3d(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
    }

    Vec3d Vec3d::operator*(const Vec3d& v) const {
        return Vec3d(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
    }

    Vec3d Vec3d::operator*(double t) const {
        return Vec3d(t*e[0], t*e[1], t*e[2]);
    }
    Vec3d Vec3d::operator/(double t) const {
        return Vec3d(e[0] / t, e[1] / t, e[2] / t);
    }
    Vec3d Vec3d::operator/(const Vec3d& v) const {
        return Vec3d(e[0] / v.e[0], e[1] / v.e[1], e[2] / v.e[2]);
    }
    double Vec3d::dot(const Vec3d& u, const Vec3d& v) {
        return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
    }
    double Vec3d::distance(const Vec3d& u, const Vec3d& v) {
        return (u - v).length();
    }

    Vec3d Vec3d::cross(const Vec3d& u, const Vec3d& v) {
        return Vec3d(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    Vec3d Vec3d::unit_vector(const Vec3d& v) {
        return v / v.length();
    }
        
    double Vec3d::length() const {
        return std::sqrt(length_squared());
    }
    Vec3d Vec3d::min(const Vec3d& a, const Vec3d& b) {
        return Vec3d(std::min(a.e[0], b.e[0]),
                     std::min(a.e[1], b.e[1]),
                     std::min(a.e[2], b.e[2]));
    }

    Vec3d Vec3d::max(const Vec3d& a, const Vec3d& b) {
        return Vec3d(std::max(a.e[0], b.e[0]),
                     std::max(a.e[1], b.e[1]),
                     std::max(a.e[2], b.e[2]));
    }
    double Vec3d::length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    bool Vec3d::near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }
    double Vec3d::mat3x3_det(const mat3x3& m) {
        return m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1]) - m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0]) + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
    }
    mat3x3 Vec3d::mat3x3_identity() {
        return {{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}}};
    }
    mat3x3 Vec3d::mat3x3_inverse(const mat3x3& m) {

        double d = 1.0/(m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1]) - m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0]) + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]));

        mat3x3 inv_m;

        inv_m[0][0] = d*(m[1][1]*m[2][2] - m[1][2]*m[2][1]);
        inv_m[0][1] = d*(m[0][2]*m[2][1] - m[0][1]*m[2][2]);
        inv_m[0][2] = d*(m[0][1]*m[1][2] - m[0][2]*m[1][1]);

        inv_m[1][0] = d*(m[1][2]*m[2][0] - m[1][0]*m[2][2]);
        inv_m[1][1] = d*(m[0][0]*m[2][2] - m[0][2]*m[2][0]);
        inv_m[1][2] = d*(m[0][2]*m[1][0] - m[0][0]*m[1][2]);

        inv_m[2][0] = d*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
        inv_m[2][1] = d*(m[0][1]*m[2][0] - m[0][0]*m[2][1]);
        inv_m[2][2] = d*(m[0][0]*m[1][1] - m[0][1]*m[1][0]);

        return inv_m;
    }
    mat3x3 Vec3d::mat3x3_mult(const mat3x3& left, const mat3x3& right) {
        mat3x3 m;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = left[i][0]*right[0][j] + left[i][1]*right[1][j] + left[i][2]*right[2][j];
            }
        }
        return m;
    }
    Vec3d Vec3d::mat3x3_times(const mat3x3& left, const Vec3d& right){
        Vec3d result(   left[0][0]*right.x() + left[0][1]*right.y() + left[0][2]*right.z(),
                        left[1][0]*right.x() + left[1][1]*right.y() + left[1][2]*right.z(),
                        left[2][0]*right.x() + left[2][1]*right.y() + left[2][2]*right.z());
        return result;
    }
    mat3x3 Vec3d::mat3x3_times(const mat3x3& left, const mat3x3& right){
        mat3x3 result;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                result[i][j] = left[i][j]*right[i][j];
            }
        }
        return result;
    }
    mat3x3 Vec3d::mat3x3_transpose(const mat3x3& m) {
        mat3x3 mt;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mt[i][j] = m[j][i];
            }
        }
        return mt;
    }
}